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

Controller::Controller(ILogger *logger, INetwork *network) {
    logger_ = logger;
    network_ = network;
};

std::vector<IRemoteAgent*> Controller::GetAvailableAgents() {
    return network_->GetAvailableAgents();
};

void Controller::BuildContent(IContent* content) {
    std::vector<IRemoteAgent*> agent_list = GetAvailableAgents();
    
    // TODO: move Content splitting to IContent
    
    Queue* queue = new Queue(1, 10, content->GetSize(), logger_);
    
    while (!queue->AllTasksComplete()) {
        for (int i = 0; i < agent_list.size(); i++) {
            IRemoteAgent* agent = agent_list[i];
            IRemoteAgent::AgentStatus status = network_->CheckAgentStatus(agent);
            switch ( status )
            {
                case IRemoteAgent::AgentStatus::STATE_TASK_COMPLETE:
                    network_->CollectTaskResult(agent);
                    queue->AssignTask(agent);
                    break;
                case IRemoteAgent::AgentStatus::STATE_AVAILABLE:
                    queue->AssignTask(agent);
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
//    return build_time;
};
