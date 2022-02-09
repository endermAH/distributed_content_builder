//
//  Agent.cpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 16.12.2021.
//

#include <iostream>
#include <unistd.h>
#include <thread>
#include <time.h>
#include <cstdlib>
#include <string>

#include "Agent.hpp"
#include "Queue.hpp"
#include "MacLogger.hpp"
#include "TestNetwork.hpp"

Agent::Agent(int id, int count){
    state_ = AgentStatus::STATE_AVAILABLE;
    identity_ = id;
    count_ = count;
    logger_ = new MacLogger();
}

void Agent::DoTask(ITask* job) {
    auto payload = [](ITask* job, Agent* agent){
        agent->state_ = AgentStatus::STATE_BUSY;
//        printf("[%d] Task started (%d)\n", agent->identity_, job->GetSize());
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 * job->GetSize()));
//        printf("[%d] Task finished\n", agent->identity_);
        job->SetStatus(ITask::TaskStatus::TASK_DONE);
        agent->state_ = AgentStatus::STATE_TASK_COMPLETE;
    };
    std::thread thread(payload, job, this);
    thread.detach();
}

Agent* Agent::GetAvailableAgents() {
    return GenerateAgents(count_); // TODO: Replace to INetwork->GetAvailableAgents
}

double Agent::BuildContent(int content_size) {
//    Agent* a_list = GetAvailableAgents();
//    Queue* queue = new Queue(1, 10, content_size, logger_);
//    TestNetwork* network = new TestNetwork(logger_);
//    time_t start, end;
//    time(&start);
//    while (!queue->AllTasksComplete()) {
//        for (int i = 0; i < count_; i++) {
//            Agent* agent = &a_list[i];
//            AgentStatus status = network->CheckAgentStatus(agent);
//            switch ( status )
//            {
//                case AgentStatus::STATE_TASK_COMPLETE:
//                    network->CollectTaskResult(agent);
//                    queue->AssignTask(agent);
//                    break;
//                case AgentStatus::STATE_AVAILABLE:
//                    queue->AssignTask(agent);
//                    break;
//                case AgentStatus::STATE_BUSY:
//                    continue;
//                    break;
//                case AgentStatus::STATE_OFFLINE:
//                    logger_->LogWarning("Node " + std::to_string(agent->identity_) + " is now offline!");
//                    break;
//            }
//        }
//        usleep(1000); // TODO replace with c++ style
//    }
//    time(&end);
//    double build_time = difftime(end, start);
//    logger_->LogSuccess("Build time: " + std::to_string(build_time) + "s");
    return 1;
}

Agent* Agent::GenerateAgents(int count) {
    Agent* agents;
    agents = static_cast<Agent*>(malloc(sizeof(Agent)*count));
    for(int i = 0; i < count; i++){
        new(agents + i) Agent(i, count);
    }
    return agents;
}
