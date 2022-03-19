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

#include "Interfaces.hpp"
#include "ILogger.hpp"
#include "INetwork.hpp"
#include "IRemoteAgent.hpp"
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
            remote_agents.push_back(new RemoteAgent(i, "../../test_content/agents/"));
        }
        
        return remote_agents;
    }
    
    bool SendTaskToRemoteAgent(IRemoteAgent *target_agent, ITask *task) {
        logger_->LogDebug("[Network]: Sending task to agent[" + std::to_string(target_agent->id_) + "]");
        target_agent->DoTask(task);
        return true;
    }
    
    IRemoteAgent::AgentStatus CheckAgentStatus(IRemoteAgent *target_agent) {
        return target_agent->state_;
    }
    
    void CollectTaskResult(IRemoteAgent *target_agent){
        return;
    }

    std::vector<std::string> CollectExistingFiles(std::vector<std::string> content_hashes, std::vector<IRemoteAgent*> agents){
        std::vector<std::string> existing_hashes;
        for (IRemoteAgent* agent : agents) {
            std::vector<std::string> existing_agent_hashes = agent->CheckHashes(content_hashes);
            for (auto hash: existing_agent_hashes) {
                if (std::find(existing_hashes.begin(), existing_hashes.end(), hash) == existing_hashes.end()){
                    existing_hashes.push_back(hash);
                }
            }
        }
        return existing_hashes;
    };
};
#endif /* TestNetwork_hpp */
