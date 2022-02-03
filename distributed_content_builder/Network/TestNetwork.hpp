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
#include "ILogger.h"
#include "INetwork.h"
#include "IRemoteAgent.h"
#include "RemoteAgent.hpp"

class Agent;

class TestNetwork: public INetwork {
public:
    ILogger* logger_;
public:
    TestNetwork(ILogger *logger)
        :logger_(logger) {}
    
    bool SendTaskToRemoteAgent(IRemoteAgent *target_agent, ITask *task) {
        logger_->LogInfo("Sending task to agent[" + std::to_string(target_agent->id_) + "]");
        target_agent->DoTask(task);
        return true;
    }
    
    IRemoteAgent::AgentStatus CheckAgentStatus(IRemoteAgent *target_agent) {
        return target_agent->state_;
    }
    
    void CollectTaskResult(IRemoteAgent *target_agent){
        return;
    }
};
#endif /* TestNetwork_hpp */
