//
//  Agent.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 16.12.2021.
//

#ifndef Agent_hpp
#define Agent_hpp

#include <stdio.h>
#include "Interfaces.hpp"
#include "MacLogger.hpp"

class Queue;
class Task;

class Agent: public IAgent {
public:
    MacLogger *logger_;
    AgentStatus state_;
    int identity_;
    int count_;
public:
    Agent(int id, int count);
    
    void DoTask(ITask* job);
    Agent* GetAllAgents(); // Not implemented !!!
    Agent* GetAvailableAgents();
    double BuildContent(int content_size);
    
private:
    Agent* GenerateAgents(int count);
};

#endif /* Agent_hpp */
