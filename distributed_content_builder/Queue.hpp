//
//  Queue.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 16.12.2021.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <stdio.h>

class Agent;

class Task {
public:
    enum class TaskStatus {
        TASK_IN_PROGRESS, TASK_DONE, TASK_READY_FOR_BUILD, TASK_FAILED
    };
    int size_;
    Agent* assigned_agent_;
    TaskStatus status_;
public:
    Task(int count) {
        size_ = count;
        status_ = TaskStatus::TASK_READY_FOR_BUILD;
    }
};

class Queue {
public:
    Task* task_list_;
    int task_count_;
    
public:
    Queue(int count);
    Queue(int min, int max, int count);
    
    bool AssignTask(Agent* a);
    bool AllTasksComplete();
    
};

#endif /* Queue_hpp */
