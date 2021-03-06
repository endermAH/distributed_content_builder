//
//  Queue.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 16.12.2021.
//  Deprecated

#ifndef Queue_hpp
#define Queue_hpp

#include <stdio.h>
#include <vector>

#include "IRemoteAgent.hpp"
#include "IQueue.hpp"
#include "ILogger.hpp"
#include "TestTask.hpp"

class Agent;

class Queue: public IQueue {
public:
    ILogger* logger_;
    std::vector<TestTask*> task_list_;
    int task_count_;
    
public:
    Queue(int count, ILogger* logger);
    Queue(int min, int max, int count, ILogger* logger);
    
    bool AssignTask(IRemoteAgent* a);
    bool AllTasksComplete();
    
};

#endif /* Queue_hpp */
