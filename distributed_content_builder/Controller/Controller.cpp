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
#include "MacLogger.hpp"
#include "TestNetwork.hpp"

Controller::Controller(ILogger *logger) {
    logger_ = logger;
};

std::vector<IRemoteAgent*> Controller::GetAvailableAgents() {
    
    // TODO: Use Network to get available agents
    
    int count_ = 3;
    std::vector<IRemoteAgent*> remote_agents;
    for(int i = 0; i < count_; i++){
        remote_agents.push_back(new RemoteAgent(i));
    }

    return remote_agents;
};

void Controller::BuildContent(IContent* content) {
    std::vector<IRemoteAgent*> agent_list = GetAvailableAgents();
    
    // TODO: move Content splitting to IContent
    
    Queue* queue = new Queue(1, 10, content->GetSize(), logger_);
    TestNetwork* network = new TestNetwork(logger_);
    time_t start, end;
    time(&start);
    while (!queue->AllTasksComplete()) {
        for (int i = 0; i < agent_list.size(); i++) {
            IRemoteAgent* agent = agent_list[i];
            IRemoteAgent::AgentStatus status = network->CheckAgentStatus(agent);
            switch ( status )
            {
                case IRemoteAgent::AgentStatus::STATE_TASK_COMPLETE:
                    network->CollectTaskResult(agent);
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
    time(&end);
    double build_time = difftime(end, start);
    logger_->LogSuccess("Build time: " + std::to_string(build_time) + "s");
//    return build_time;
};
