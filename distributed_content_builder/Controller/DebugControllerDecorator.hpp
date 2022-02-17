//
//  DebugController.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 03.02.2022.
//

#ifndef DebugController_hpp
#define DebugController_hpp

#include <stdio.h>
#include <chrono>
#include <string>

#include "IController.hpp"

class DebugControllerDecorator : public IController {
protected:
    IController* controller_;
public:
    DebugControllerDecorator(IController* controller)
    : controller_(controller) {}
    
    std::vector<IRemoteAgent*> GetAvailableAgents() {
        return controller_->GetAvailableAgents();
    }
    
    void BuildContent(IContent* content) {
        time_t start, end;
        time(&start);
        controller_->BuildContent(content);
        time(&end);
        double build_time = difftime(end, start);
        controller_->logger_->LogSuccess("Build time: " + std::to_string(build_time) + "s");
    }
};

#endif /* DebugController_hpp */
