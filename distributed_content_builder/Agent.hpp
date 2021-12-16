//
//  Agent.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 16.12.2021.
//

#ifndef Agent_hpp
#define Agent_hpp

#include <stdio.h>

class Queue;
class Task;

class Agent {
public:
    enum class AgentStates {
        STATE_AVAILABLE, STATE_BUSY, STATE_OFFLINE
    };
    AgentStates state_;
    int identity_;
public:
    Agent(int id);
    
    void DoTask(Task* job);
    Agent* GetAllAgents(); // Not implemented !!!
    Agent* GetAllAgents(int count);
    double BuildContent(int content_size, int count);
    
private:
    Agent* GenerateAgents(int count);
};

#endif /* Agent_hpp */
