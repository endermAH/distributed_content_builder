//
//  Queue.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 16.12.2021.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <stdio.h>
#include <vector>

#include "IRemoteAgent.h"
#include "IQueue.h"
#include "ILogger.h"

class Agent;

class Task: public ITask {
public:
    int size_;
    IRemoteAgent* assigned_agent_;
    TaskStatus status_;
public:
    Task(int count) {
        size_ = count;
        status_ = TaskStatus::TASK_READY_FOR_BUILD;
    }
    
    TaskStatus GetStatus(){
        return status_;
    }
    
    void SetStatus(TaskStatus new_status){
        status_ = new_status;
    }
    
    int GetSize(){
        return size_;
    }
};

class Queue: public IQueue {
public:
    ILogger* logger_;
    std::vector<Task*> task_list_;
    int task_count_;
    
public:
    Queue(int count, ILogger* logger);
    Queue(int min, int max, int count, ILogger* logger);
    
    bool AssignTask(IRemoteAgent* a);
    bool AllTasksComplete();
    
};

#endif /* Queue_hpp */
