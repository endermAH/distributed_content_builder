//
//  IController.h
//  distributed_content_builder
//
//  Created by Евгений Курятов on 02.02.2022.
//

#ifndef IController_h
#define IController_h

#include <vector>

#include "IContent.h"
#include "IRemoteAgent.h"
#include "ILogger.h"
#include "INetwork.h"

class IController {
public:
    ILogger *logger_;
    INetwork *network_;
public:
    virtual std::vector<IRemoteAgent*> GetAvailableAgents() = 0;
    virtual void BuildContent(IContent* content) = 0;
};

#endif /* IController_h */
