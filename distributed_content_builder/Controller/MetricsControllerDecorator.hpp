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
//        controller_->logger_->LogDebug("Folder size: " + std::filesystem::file_size("../../test_content/agents"));
        size_t cash_size = 0;
        for (auto dir_entry : std::filesystem::recursive_directory_iterator("../../test_directory/agents"))
        {
            if (!std::filesystem::is_directory(dir_entry)) {
                cash_size += dir_entry.file_size();
            }
        }
        controller_->logger_->LogInfo("Average cash size: " + std::to_string(float(cash_size) / 1024 / 1024 / 3) + "mb");
    }

};

#endif /* DebugController_hpp */
