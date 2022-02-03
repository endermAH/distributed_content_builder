//
//  IQueue.h
//  distributed_content_builder
//
//  Created by Евгений Курятов on 02.02.2022.
//

#ifndef IQueue_h
#define IQueue_h

#include "IRemoteAgent.h"

class IQueue {
public:
    virtual bool AssignTask(IRemoteAgent* a) = 0;
    virtual bool AllTasksComplete() = 0;
};

#endif /* IQueue_h */
