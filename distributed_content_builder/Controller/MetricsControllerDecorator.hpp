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
#include <fstream>

#include "IController.hpp"
#include "MetricCollector.hpp"

class MetricsControllerDecorator : public IController {
protected:
    IController* controller_;
public:
    MetricsControllerDecorator(IController* controller)
    : controller_(controller) {}
    
    std::vector<IRemoteAgent*> GetAvailableAgents() {
        return controller_->GetAvailableAgents();
    }
    
    void BuildContent(IContent* content) {
        auto start = std::chrono::system_clock::now();
        controller_->BuildContent(content);
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> build_time = end - start;
        controller_->logger_->LogSuccess("Build time: " + std::to_string(build_time.count()) + "s");
//        controller_->logger_->LogDebug("Folder size: " + std::filesystem::file_size("../../test_content_unix/agents"));


//        float average_cash_size = float(cash_size) / 1024 / 1024 / 3;

//        MetricCollector::AddIterationMetric("BuildDuration", iteration, std::to_string(build_time.count()));


//        controller_->logger_->LogInfo("Average cash size: " + std::to_string(average_cash_size) + "mb");
    }

};

#endif /* DebugController_hpp */
