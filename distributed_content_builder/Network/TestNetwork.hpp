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
#include <utility>
#include <vector>
#include <filesystem>
#include <thread>
#include <ctime>
#include <chrono>

#include "Interfaces.hpp"
#include "ILogger.hpp"
#include "INetwork.hpp"
#include "IRemoteAgent.hpp"
#include "RemoteAgent.hpp"
#include "HashManager.hpp"

class Agent;

const float human_connection_speed = 1; // In mb/s
const float connection_speed = (human_connection_speed * 1024 * 1024) / 1000; // In byte/ms

class TestNetwork: public INetwork {
public:
    ILogger* logger_;
    int agent_count_;
    std::vector<IRemoteAgent*> remote_agents_;
public:
    TestNetwork(ILogger *logger, std::vector<IRemoteAgent*> remote_agents)
        :logger_(logger)
        ,remote_agents_(remote_agents){}
    
    std::vector<IRemoteAgent*> GetAvailableAgents() {
        return remote_agents_;
    }
    
    bool SendTaskToRemoteAgent(IRemoteAgent *target_agent, ITask *task) {
        auto copy_from = std::filesystem::path(task->file_path_);
        std::string filename = std::to_string(std::time(0)) + "-" + copy_from.filename().string();
        logger_->LogDebug(filename.c_str());
        auto copy_to = std::filesystem::path(target_agent->base_directory_)/"raw"/filename;

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
        logger_->LogInfo("target_agent->DoTask(task);");
        target_agent->DoTask(task);
        logger_->LogInfo("target_agent->DoTask(task); Completed");
        return true;
    }
    
    IRemoteAgent::AgentStatus CheckAgentStatus(IRemoteAgent *target_agent) {
        return target_agent->state_;
    }
    
    void SendTaskResult(IRemoteAgent *target_agent, ITask *task){
        auto copy_to = task->controller_result_path_;
        auto copy_from = std::filesystem::path(target_agent->base_directory_)/"ready"/task->file_name_;

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

    std::vector<FileHash> CollectExistingFiles(std::vector<ITask*> task_list, std::vector<IRemoteAgent*> agents, std::filesystem::path result_dir){
        std::vector<FileHash> existing_hashes_total;
        std::filesystem::path copy_to_dir = result_dir;
        std::filesystem::remove_all(copy_to_dir);
        std::filesystem::create_directory(copy_to_dir);

//        std::vector<FileHash> content_hashes;
//        for (auto task : task_list){
//            auto* hash_manager = new HashManager(logger_);
//            FileHash content_hash = FileHash(hash_manager->GenerateFileHash(task->file_hash_), task->file_path_);
//            content_hashes.push_back(content_hash);
//        }
//
//        logger_->LogDebug("[Controller]: Content hashes: ");
//        for (auto hash: content_hashes) {
//            logger_->LogDebug(hash.file_path_ + " " + hash.file_hash_);
//        }

        for (auto task : task_list) {
            std::vector<FileHash> task_hash;
            std::vector<FileHash> existing_hashes;
            task_hash.emplace_back(task->file_hash_, task->file_path_);
            logger_->LogInfo("[Network]: searching for " + task->file_name_ + " (hash: " + task->file_hash_ + ")");

            for (IRemoteAgent *agent: agents) {
                std::vector<FileHash> existing_agent_hashes = agent->CheckHashes(task_hash);

                for (auto hash: existing_agent_hashes) {
                    if (std::find(existing_hashes.begin(), existing_hashes.end(), hash) == existing_hashes.end()) {
                        existing_hashes_total.push_back(hash);
                        existing_hashes.push_back(hash);
                        auto copy_from = std::filesystem::path(agent->base_directory_) / "ready" /
                                         std::filesystem::path(hash.file_path_).filename();
                        auto copy_to = copy_to_dir/task->file_name_;
                        auto file_size = std::filesystem::file_size(copy_from);
                        long time_to_sleep = file_size / connection_speed;

                        logger_->LogDebug(
                                "[Network]: Collecting from" + copy_from.string() + " to " + copy_to.string());
                        logger_->LogDebug("[Network]: Collecting " + copy_from.filename().string() + " from agent[" +
                                          std::to_string(agent->id_) + "]"
                                                                       "\n --- File size: " +
                                          std::to_string(file_size) + " byte "
                                                                      "\n --- Time to sleep: " +
                                          std::to_string(time_to_sleep) + " ms"
                                                                          "\n --- Network speed: " +
                                          std::to_string(connection_speed) + " bit/ms"
                        );

                        std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep));
                        logger_->LogSuccess(
                                "[Network]: Successfully collected existing " + copy_from.filename().string() +
                                " from agent[" + std::to_string(agent->id_) + "] at " +
                                std::to_string(float(time_to_sleep) / 1000) + "s");
//                        logger_->LogDebug(absolute(copy_from));
//                        logger_->LogDebug(absolute(copy_to));
                        std::filesystem::copy(absolute(copy_from), absolute(copy_to));
                    }
                }
            }
        }

        return existing_hashes_total;
    };
};
#endif /* TestNetwork_hpp */
