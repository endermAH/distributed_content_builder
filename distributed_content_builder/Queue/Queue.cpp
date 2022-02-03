//
//  Queue.cpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 16.12.2021.
//

#include <iostream>
#include <unistd.h>
#include <thread>
#include <time.h>
#include <cstdlib>
#include "Queue.hpp"
#include "Agent.hpp"
#include "TestNetwork.hpp"

Queue::Queue(int count, ILogger* logger)
    :logger_(logger)
{
    task_count_ = count;
    task_list_ = static_cast<Task*>(malloc(sizeof(Task)*count));
    for(int i = 0; i < count; i++) {
        new(task_list_ + i) Task(1);
    }
}

Queue::Queue(int min, int max, int count, ILogger* logger)
    :logger_(logger)
{
    std::srand(std::time(nullptr));
    int* task_sizes_ = static_cast<int*>(malloc(sizeof(int)*count));
    int tmp_count = count;
    task_count_ = 0;
    int rand_count;
    
    while (tmp_count > max) {
        rand_count = min + std::rand() % (max-min);
        task_sizes_[task_count_] = rand_count;
        tmp_count -= rand_count;
        task_count_++;
    }
    task_sizes_[task_count_] = tmp_count;
    task_count_++;
    
    task_list_ = static_cast<Task*>(malloc(sizeof(Task)*task_count_));
    for(int i = 0; i < task_count_; i++) {
        new(task_list_ + i) Task(task_sizes_[i]);
    }
    
    std::cout << "Jobs to do: \n";
    for (int i=0; i<task_count_; i++){
        std::cout << task_list_[i].GetSize() << " ";
    }
    std::cout << std::endl;
    
    free(task_sizes_);
}

bool Queue::AssignTask(IRemoteAgent* agent){
    Task* task;
    bool task_assigned = false;
    for(int i = 0; i < task_count_; i++) {
        if (task_list_[i].GetStatus() == ITask::TaskStatus::TASK_READY_FOR_BUILD || task_list_[i].GetStatus() == ITask::TaskStatus::TASK_FAILED) {
            task = &task_list_[i];
            task->assigned_agent_ = agent;
            task->status_ = ITask::TaskStatus::TASK_IN_PROGRESS;
            task_assigned = true;
            TestNetwork* network = new TestNetwork(logger_);
            network->SendTaskToRemoteAgent(agent, task);
            break;
        }
    }
    return task_assigned;
}

bool Queue::AllTasksComplete() {
    bool done = true;
    for(int i = 0; i < task_count_; i++) {
        if (task_list_[i].status_ != ITask::TaskStatus::TASK_DONE) {
            done = false;
        }
    }
    return done;
}
