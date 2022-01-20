//
//  TestNetwork.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 20.01.2022.
//

#ifndef TestNetwork_hpp
#define TestNetwork_hpp

#include <stdio.h>
#include <string>
#include "Interfaces.h"
#include "Agent.hpp"

class Agent;

class TestNetwork: public INetwork {
public:
    ILogger* logger_;
public:
    TestNetwork(ILogger *logger)
        :logger_(logger) {}
    
    bool SendTaskToRemoteAgent(IAgent *target_agent, ITask *task) {
        logger_->LogInfo("Sending task to agent");
        target_agent->DoTask(task);
        return true;
    }
    
    IAgent::AgentStatus CheckAgentStatus(IAgent *target_agent) {
        return IAgent::AgentStatus::STATE_AVAILABLE;
    }
    
    IAgent::AgentStatus CheckAgentStatus(Agent *target_agent) {
        return target_agent->state_;
    }
    
    void CollectTaskResult(IAgent *target_agent){
        return;
    }
};
#endif /* TestNetwork_hpp */
