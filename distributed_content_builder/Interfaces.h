//
//  Interfaces.h
//  distributed_content_builder
//
//  Created by Евгений Курятов on 19.01.2022.
//

#ifndef Interfaces_h
#define Interfaces_h

#include <string>

class ITask {
public:
    enum class TaskStatus {
        TASK_IN_PROGRESS, TASK_DONE, TASK_READY_FOR_BUILD, TASK_FAILED
    };
    
    virtual TaskStatus GetStatus() = 0;
    virtual void SetStatus(TaskStatus new_status) = 0;
    virtual int GetSize() = 0;
};

// TODO: Split IAgent to IHost and IRemoteAgent
class IAgent {
public:
    enum class AgentStatus {
        STATE_AVAILABLE, STATE_BUSY, STATE_OFFLINE, STATE_TASK_COMPLETE
    };
    
    virtual void DoTask(ITask* job) = 0;
    virtual IAgent* GetAvailableAgents() = 0;
    virtual double BuildContent(int content_size) = 0;
};

class IQueue {
public:
    virtual bool AssignTask(IAgent* a) = 0;
    virtual bool AllTasksComplete() = 0;
};

class ILogger {
public:
    virtual ~ILogger() {};
    
    virtual void LogError(std::string message) = 0;
    virtual void LogSuccess(std::string message) = 0;
    virtual void LogWarning(std::string message) = 0;
    virtual void LogInfo(std::string message) = 0;
};

class INetwork {
public:
    virtual bool SendTaskToRemoteAgent(IAgent *target_agent, ITask *task) = 0;
    virtual IAgent::AgentStatus CheckAgentStatus(IAgent *target_agent) = 0;
    virtual void CollectTaskResult(IAgent *target_agent) = 0;
};

#endif /* Interfaces_h */
