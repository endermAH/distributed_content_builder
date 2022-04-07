//
//  Controller.cpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 02.02.2022.
//

#include <vector>
#include <unistd.h>
#include <chrono>
#include <thread>

#include "Controller.hpp"
#include "RemoteAgent.hpp"
#include "Queue.hpp"

Controller::Controller(ILogger *logger, INetwork *network, IHashManager *hash_manager) {
    logger_ = logger;
    network_ = network;
    hash_manager_ = hash_manager;
};

std::vector<IRemoteAgent*> Controller::GetAvailableAgents() {
    return network_->GetAvailableAgents();
};

void Controller::BuildContent(IContent* content) {
    std::vector<IRemoteAgent*> agent_list = GetAvailableAgents();
    task_list_ = content->GetTasks();

    // TODO: Move to UpdateTaskListWithExistsng
    std::vector<FileHash> content_hashes;
    for (auto* task :  task_list_){
        FileHash content_hash = FileHash(hash_manager_->GenerateFileHash(task->file_path_), task->file_path_);
        content_hashes.push_back(content_hash);
    }

    logger_->LogDebug("[Controller]: Content hashes: ");
    for (auto hash: content_hashes) {
        logger_->LogDebug(hash.file_path_.c_str());
    }

    std::vector<FileHash> existing_hashes = network_->CollectExistingFiles(content_hashes, agent_list);

    logger_->LogDebug("[Controller]: Existing files: ");
    for (auto hash: existing_hashes) {
        logger_->LogDebug(hash.file_path_.c_str());
    }

    logger_->LogDebug("[Controller]: Removing tasks");
    for (int i = task_list_.size()-1; i >= 0; i--) {
        FileHash task_file_hash = FileHash(task_list_[i]->file_hash_, task_list_[i]->file_path_);
        if (std::find(existing_hashes.begin(), existing_hashes.end(), task_file_hash) != existing_hashes.end()) {
            task_list_.erase(task_list_.begin() + i);
        }
    }

    while (!AllTasksComplete()) {
        for (int i = 0; i < agent_list.size(); i++) {
            IRemoteAgent* agent = agent_list[i];
            IRemoteAgent::AgentStatus status = network_->CheckAgentStatus(agent);
            switch ( status )
            {
                case IRemoteAgent::AgentStatus::STATE_TASK_COMPLETE:
                    AssignTask(agent);
                    break;
                case IRemoteAgent::AgentStatus::STATE_AVAILABLE:
                    AssignTask(agent);
                    break;
                case IRemoteAgent::AgentStatus::STATE_BUSY:
                    continue;
                    break;
                case IRemoteAgent::AgentStatus::STATE_OFFLINE:
                    logger_->LogWarning("Node " + std::to_string(agent->id_) + " is now offline!");
                    break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

bool Controller::AssignTask(IRemoteAgent* agent){
    ITask* task;
    bool task_assigned = false;
    for(int i = 0; i < task_list_.size(); i++) {
        task = task_list_[i];
        if (task->GetStatus() == ITask::TaskStatus::TASK_READY_FOR_BUILD || task->GetStatus() == ITask::TaskStatus::TASK_FAILED) {
            task->status_ = ITask::TaskStatus::TASK_IN_PROGRESS;
            task_assigned = true;
            network_->SendTaskToRemoteAgent(agent, task);
            break;
        }
    }
    return task_assigned;
}

bool Controller::AllTasksComplete() {
    bool done = true;
    for(int i = 0; i < task_list_.size(); i++) {
        if (task_list_[i]->GetStatus() != ITask::TaskStatus::TASK_DONE) {
            done = false;
        }
    }
    return done;
}
