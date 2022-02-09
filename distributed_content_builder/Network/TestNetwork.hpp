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
#include <vector>

#include "Interfaces.h"
#include "ILogger.h"
#include "INetwork.h"
#include "IRemoteAgent.h"
#include "RemoteAgent.hpp"

class Agent;

class TestNetwork: public INetwork {
public:
    ILogger* logger_;
    int agent_count_;
public:
    TestNetwork(ILogger *logger, int agent_count)
        :logger_(logger)
        ,agent_count_(agent_count){}
    
    std::vector<IRemoteAgent*> GetAvailableAgents() {
        std::vector<IRemoteAgent*> remote_agents;
        for(int i = 0; i < agent_count_; i++){
            remote_agents.push_back(new RemoteAgent(i));
        }
        
        return remote_agents;
    }
    
    bool SendTaskToRemoteAgent(IRemoteAgent *target_agent, ITask *task) {
        logger_->LogDebug("Sending task to agent[" + std::to_string(target_agent->id_) + "]");
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
