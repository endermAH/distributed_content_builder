//
//  RemoteAgent.cpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 03.02.2022.
//

#include <iostream>
#include <unistd.h>
#include <thread>
#include <time.h>
#include <cstdlib>
#include <string>
#include <filesystem>

#include "RemoteAgent.hpp"
#include "HashManager.hpp"
#include "UnixLogger.hpp"
#include "HashList.hpp"
#include "TestNetwork.hpp"

#include <cstdlib>
#include <iostream>
#include <ctime>

RemoteAgent::RemoteAgent(int id, std::string base_dir) {
    id_ = id;
    state_ = AgentStatus::STATE_AVAILABLE;
    base_directory_ = std::filesystem::absolute(base_dir).string() + "/RemoteAgent" + std::to_string(id);
    std::string dir_struct_to_create = base_directory_ + "/ready";
    std::filesystem::create_directories(dir_struct_to_create);
    dir_struct_to_create = base_directory_ + "/raw";
    std::filesystem::create_directories(dir_struct_to_create);

    // TODO: use IHashManager and ILogger
    logger_ = new UnixLogger();
    hash_manager_ = new HashManager(logger_);
}

void RemoteAgent::DoTask(ITask* task) {
    // TODO: implement DoTask using INetwork

    auto payload = [](ITask* task, RemoteAgent* agent){
        agent->state_ = AgentStatus::STATE_BUSY;

        task->Do(agent->base_directory_ + "/ready");
        task->SetStatus(ITask::TaskStatus::TASK_DONE);

        HashList hash_list = HashList(agent->base_directory_ + "/hash.list", agent->logger_);
        hash_list.AddHash(task->file_hash_, task->result_path_);
        hash_list.Save();

        TestNetwork* network = new TestNetwork(agent->logger_, 0);
        network->SendTaskResult(agent, task);

        agent->state_ = AgentStatus::STATE_TASK_COMPLETE;
    };
    std::thread thread(payload, task, this);
    thread.detach();
}

std::vector<FileHash> RemoteAgent::CheckHashes(std::vector<FileHash> hashes) {
    auto* hash_list = new HashList(base_directory_ + "/hash.list", logger_);
    return hash_manager_->GetArtifactsFromHashlist(hash_list, hashes);
}
