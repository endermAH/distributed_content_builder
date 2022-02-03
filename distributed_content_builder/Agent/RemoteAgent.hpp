//
//  RemoteAgent.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 03.02.2022.
//

#ifndef RemoteAgent_hpp
#define RemoteAgent_hpp

#include <stdio.h>

#include "IRemoteAgent.h"

class RemoteAgent: public IRemoteAgent {

public:
    RemoteAgent(int id);
    void DoTask(ITask* job);
};

#endif /* RemoteAgent_hpp */
