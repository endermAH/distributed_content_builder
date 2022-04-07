//
//  TestNetwork.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 20.01.2022.
//

#ifndef TestNetwork_hpp
#define TestNetwork_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <filesystem>
#include <thread>

#include "Interfaces.hpp"
#include "ILogger.hpp"
#include "INetwork.hpp"
#include "IRemoteAgent.hpp"
#include "RemoteAgent.hpp"

class Agent;

const float human_connection_speed = 1; // In mb/s
const float connection_speed = (human_connection_speed * 1024 * 1024) / 1000; // In byte/ms

class TestNetwork: public INetwork {
public:
    ILogger* logger_;
    int agent_count_;
public:
    TestNetwork(ILogger *logger, int agent_count)
        :logger_(logger)
        ,agent_count_(agent_count){}
    
    std::vector<IRemoteAgent*> GetAvailableAgents() {
        std::vector<IRemoteAgent*> remote_agents;
        for(int i = 0; i < agent_count_; i++){
            remote_agents.push_back(new RemoteAgent(i, "../../test_content/agents/"));
        }
        
        return remote_agents;
    }
    
    bool SendTaskToRemoteAgent(IRemoteAgent *target_agent, ITask *task) {
        auto copy_from = std::filesystem::path(task->file_path_);
        auto copy_to = std::filesystem::path(target_agent->base_directory_)/"raw"/copy_from.filename();

        auto file_size = std::filesystem::file_size(copy_from);
        long time_to_sleep = file_size / connection_speed;

        logger_->LogDebug("[Network]: Sending " + copy_from.filename().string() + " to agent[" + std::to_string(target_agent->id_) + "]"
            "\n --- File size: " + std::to_string(file_size ) + " byte "
            "\n --- Time to sleep: " + std::to_string(time_to_sleep ) + " ms"
            "\n --- Network speed: " + std::to_string(connection_speed ) + " byte/ms"
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep));
        std::filesystem::copy(copy_from, copy_to);
        logger_->LogSuccess("[Network]: Successfully sent " + copy_from.filename().string() + " to agent[" + std::to_string(target_agent->id_) + "] at " + std::to_string(float(time_to_sleep) / 1000) + "s");
        task->file_path_ = copy_to.string();
        target_agent->DoTask(task);
        return true;
    }
    
    IRemoteAgent::AgentStatus CheckAgentStatus(IRemoteAgent *target_agent) {
        return target_agent->state_;
    }
    
    void SendTaskResult(IRemoteAgent *target_agent, ITask *task){
        auto copy_to = std::filesystem::path(std::filesystem::path("../../test_content/ready"));
        auto copy_from =  std::filesystem::path(target_agent->base_directory_)/"ready"/std::filesystem::path(task->file_path_).filename();

        auto file_size = std::filesystem::file_size(copy_from);
        long time_to_sleep = file_size / connection_speed;

        logger_->LogDebug("[Network]: Collecting " + copy_from.filename().string() + " from agent[" + std::to_string(target_agent->id_) + "]"
            "\n --- File size: " + std::to_string(file_size ) + " byte "
            "\n --- Time to sleep: " + std::to_string(time_to_sleep ) + " ms"
            "\n --- Network speed: " + std::to_string(connection_speed ) + " byte/ms"
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep));
        logger_->LogSuccess("[Network]: Successfully collected "  + copy_from.filename().string() + " from agent[" + std::to_string(target_agent->id_) + "] at " + std::to_string(float(time_to_sleep) / 1000) + "s");
        std::filesystem::copy(copy_from, copy_to);
    }

    std::vector<FileHash> CollectExistingFiles(std::vector<FileHash> content_hashes, std::vector<IRemoteAgent*> agents){
        std::vector<FileHash> existing_hashes;
        for (IRemoteAgent* agent : agents) {
            std::vector<FileHash> existing_agent_hashes = agent->CheckHashes(content_hashes);
            for (auto hash : existing_agent_hashes) {
                logger_->LogDebug("[Network]: Found " + std::filesystem::path(hash.file_path_).filename().string() + " on agent[" + std::to_string(agent->id_) + "]");
            }
            for (auto hash: existing_agent_hashes) {
                if (std::find(existing_hashes.begin(), existing_hashes.end(), hash) == existing_hashes.end()){
                    existing_hashes.push_back(hash);
                    auto copy_from = std::filesystem::path(agent->base_directory_)/"ready"/std::filesystem::path(hash.file_path_).filename();
                    auto copy_to = std::filesystem::path(std::filesystem::path("../../test_content/ready"));
                    auto file_size = std::filesystem::file_size(copy_from);
                    long time_to_sleep = file_size / connection_speed;

                    logger_->LogDebug("[Network]: Collecting from" + copy_from.string() + " to " + copy_to.string());
                    logger_->LogDebug("[Network]: Collecting " + copy_from.filename().string() + " from agent[" + std::to_string(agent->id_) + "]"
                        "\n --- File size: " + std::to_string(file_size ) + " byte "
                        "\n --- Time to sleep: " + std::to_string(time_to_sleep ) + " ms"
                        "\n --- Network speed: " + std::to_string(connection_speed ) + " bit/ms"
                    );

                    std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep));
                    logger_->LogSuccess("[Network]: Successfully collected "  + copy_from.filename().string() + " from agent[" + std::to_string(agent->id_) + "] at " + std::to_string(float(time_to_sleep) / 1000) + "s");
                    std::filesystem::copy(copy_from, copy_to);
                }
            }
        }

        return existing_hashes;
    };
};
#endif /* TestNetwork_hpp */
