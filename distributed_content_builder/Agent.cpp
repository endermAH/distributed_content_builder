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
#include "Agent.hpp"
#include "Queue.hpp"

Agent::Agent(int id) {
    state_ = AgentStates::STATE_AVAILABLE;
    identity_ = id;
}

void Agent::DoTask(Task* job) {
    auto payload = [](Task* job, Agent* agent){
        agent->state_ = AgentStates::STATE_BUSY;
        printf("[%d] Task started (%d)\n", agent->identity_, job->size_);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 * job->size_));
        printf("[%d] Task finished\n", agent->identity_);
        job->status_ = Task::TaskStatus::TASK_DONE;
        agent->state_ = AgentStates::STATE_AVAILABLE;
    };
    std::thread thread(payload, job, this);
    thread.detach();
}

Agent* Agent::GetAllAgents(int count) {
    return GenerateAgents(count);
}

double Agent::BuildContent(int content_size, int count) {
    Agent* a_list = GetAllAgents(count);
    Queue* queue = new Queue(1, 10, content_size);
    time_t start, end;
    time(&start);
    while (!queue->AllTasksComplete()) {
        for (int i = 0; i < count; i++) {
            if(a_list[i].state_ == AgentStates::STATE_AVAILABLE) {
                queue->AssignTask(&a_list[i]);
            }
        }
        usleep(1000);
    }
    time(&end);
    double build_time = difftime(end, start);
    std::cout << "Build time: " << build_time << "s" << std::endl;
    return build_time;
}

Agent* Agent::GenerateAgents(int count) {
    Agent* agents;
    agents = static_cast<Agent*>(malloc(sizeof(Agent)*count));
    for(int i = 0; i < count; i++){
        new(agents + i) Agent(i);
    }
    return agents;
}
