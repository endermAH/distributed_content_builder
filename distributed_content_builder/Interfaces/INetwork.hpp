//
//  INetwork.h
//  distributed_content_builder
//
//  Created by Евгений Курятов on 02.02.2022.
//

#ifndef INetwork_h
#define INetwork_h

#include "IRemoteAgent.hpp"

class INetwork {
public:
    virtual std::vector<IRemoteAgent*> GetAvailableAgents() = 0;
    virtual bool SendTaskToRemoteAgent(IRemoteAgent *target_agent, ITask *task) = 0;
    virtual IRemoteAgent::AgentStatus CheckAgentStatus(IRemoteAgent *target_agent) = 0;
    virtual void SendTaskResult(IRemoteAgent *target_agent, ITask *task) = 0;
    virtual std::vector<FileHash> CollectExistingFiles(std::vector<FileHash> content_hashes, std::vector<IRemoteAgent*> agents) = 0;
};

#endif /* INetwork_h */
