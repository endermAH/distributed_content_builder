//
//  IRemoteAgent.h
//  distributed_content_builder
//
//  Created by Евгений Курятов on 02.02.2022.
//

#ifndef IRemoteAgent_h
#define IRemoteAgent_h

#include "ITask.h"

class IRemoteAgent {
public:
    enum class AgentStatus: char {
        STATE_AVAILABLE, STATE_BUSY, STATE_OFFLINE, STATE_TASK_COMPLETE
    };

public:
    AgentStatus state_;
    int id_;
public:
    virtual void DoTask(ITask* job) = 0;
};

#endif /* IRemoteAgent_h */
