//
//  IRemoteAgent.h
//  distributed_content_builder
//
//  Created by Евгений Курятов on 02.02.2022.
//

#ifndef IRemoteAgent_h
#define IRemoteAgent_h

#include "ITask.hpp"
#include "ILogger.hpp"
#include "IHashManager.hpp"

class IRemoteAgent {
public:
    enum class AgentStatus: char {
        STATE_AVAILABLE, STATE_BUSY, STATE_OFFLINE, STATE_TASK_COMPLETE
    };
public:
    AgentStatus state_;
    int id_;
    ILogger* logger_;
    IHashManager* hash_manager_;
    std::string base_directory_;
public:
    virtual void DoTask(ITask* job) = 0;
    virtual std::vector<FileHash> CheckHashes(std::vector<FileHash> hashes) = 0;
};

#endif /* IRemoteAgent_h */
