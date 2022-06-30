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

        std::filesystem::path file_path("../../test_directory/metrics.csv");
//        std::ofstream metrics_file(file_path);
//        metrics_file.close();

        std::ofstream metrics_file(file_path, std::ios_base::app);

        float average_cash_size = float(cash_size) / 1024 / 1024 / 3;

        metrics_file << std::to_string(std::chrono::system_clock::to_time_t(end)) << ";" << build_time.count() << ";" << average_cash_size << ";" << float(cash_size) / 1024 / 1024 << std::endl;

        metrics_file.close();

        controller_->logger_->LogInfo("Average cash size: " + std::to_string(average_cash_size) + "mb");
    }

};

#endif /* DebugController_hpp */
