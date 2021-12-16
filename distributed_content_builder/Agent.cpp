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
    state_ = STATE_AVAILABLE;
    identity_ = id;
}

void Agent::DoTask(Task* job) {
    auto payload = [](Task* j, Agent* a){
        a->state_ = STATE_BUSY;
        printf("[%d] Job started (%d)\n", a->identity_, j->size_);
        usleep(1000000 * j->size_);
        printf("[%d] Job finished\n", a->identity_);
        j->status_ = Task::TASK_DONE;
        a->state_ = STATE_AVAILABLE;
    };
    std::thread thread(payload, job, this);
    thread.detach();
}

Agent* Agent::GetAllAgents(int count) {
    return GenerateAgents(count);
}

double Agent::BuildContent(int content_size, int count) {
    Agent* a_list = GetAllAgents(count);
    Queue* q = new Queue(1, 10, content_size);
    time_t start, end;
    time(&start);
    while (!q->AllTasksComplete()) {
        for (int i = 0; i < count; i++) {
            if(a_list[i].state_ == STATE_AVAILABLE) {
                q->AssignTask(&a_list[i]);
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
