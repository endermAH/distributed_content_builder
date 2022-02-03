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

#include "RemoteAgent.hpp"

RemoteAgent::RemoteAgent(int id) {
    id_ = id;
    state_ = AgentStatus::STATE_AVAILABLE;
}

void RemoteAgent::DoTask(ITask* job) {
    // TODO: implement DoTask using INetwork
    auto payload = [](ITask* job, RemoteAgent* agent){
        agent->state_ = AgentStatus::STATE_BUSY;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 * job->GetSize()));
        job->SetStatus(ITask::TaskStatus::TASK_DONE);
        agent->state_ = AgentStatus::STATE_TASK_COMPLETE;
    };
    std::thread thread(payload, job, this);
    thread.detach();
}
