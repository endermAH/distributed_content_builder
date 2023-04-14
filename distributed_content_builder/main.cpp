//
//  main.cpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 16.12.2021.
//

#include <cstdlib>

#include <sys/stat.h>
//#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <openssl/md5.h>
#include <getopt.h>
#include <windows.h>

#include "HashList/HashList.hpp"
#include "MacLogger.hpp"
#include "UnixLogger.hpp"
#include "WinLogger.hpp"
#include "Controller.hpp"
#include "TestContent.hpp"
#include "Content.hpp"
#include "MetricsControllerDecorator.hpp"
#include "TestNetwork.hpp"
#include "HashManager.hpp"

const int kAgentCount = 1; // Wat if we have more than 22 nodes?
const int kBuildSize = 100;
const int kTestsCount = 3;
const std::filesystem::path kTestContentPath = std::filesystem::path("..\\..\\test_content_win");
const std::filesystem::path kWorkflowExecutor = std::filesystem::path(R"(..\..\tools\workflow_imitation.py)");
const bool kRecreateDir = true;

int main(int argc, char *argv[]) {
    std::srand(std::time(nullptr));

    // === DEFAULTS
    int agent_count = 1;
    std::filesystem::path work_directory = std::filesystem::path("../../test_directory");
    std::filesystem::path agents_root = work_directory/"agents";
    // === DEFAULTS

    auto* logger = new WinLogger();
    auto* hash_manager = new HashManager(logger);

    // === READ OPTIONS
    int rez = 0;
    while ( (rez = getopt(argc, argv, "a:")) != -1){
        switch (rez) {
            case 'a': agent_count = std::stoi(optarg); break;
            case '?': printf("!\n"); break;
        }
    }
    // === READ OPTIONS

    std::filesystem::path file_path("../../test_directory/metrics.csv");
    std::ofstream metrics_file(file_path);
    metrics_file << "Finish time" << ";" << "Duration" << ";" << "Average cash size" << std::endl;
    metrics_file.close();

    std::vector<IRemoteAgent*> remote_agents;
    for(int i = 0; i < agent_count; i++){
        remote_agents.push_back(new RemoteAgent(i, agents_root.string()));
    }
    auto* network = new TestNetwork(logger, remote_agents);

    std::vector<MetricsControllerDecorator*> agent_controllers;
    std::vector<Content*> agent_contents;

    for (auto* agent : remote_agents) {
        // Prepare content
        std::filesystem::path project_path = std::filesystem::path(agent->base_directory_)/"project";
        logger->LogInfo(agent->base_directory_.c_str());
        if (kRecreateDir) {
            std::filesystem::remove_all(project_path);
            logger->LogInfo("Cleaned...");
//            std::filesystem::create_directory(project_path);
//            logger->LogInfo("Created...");
            std::filesystem::copy(kTestContentPath, project_path, std::filesystem::copy_options::recursive | std::filesystem::copy_options::update_existing);
            logger->LogInfo("Copied...");
        }


        auto* content = new Content(logger, project_path.string());
        agent_contents.push_back(content);

        // Prepare controllers
        std::filesystem::path result_dir = std::filesystem::path(agent->base_directory_)/"build_result";
        auto* controller = new Controller(logger, network, hash_manager, result_dir);
        auto* d_controller = new MetricsControllerDecorator(controller);
        agent_controllers.push_back(d_controller);
    }

    logger->LogInfo("[SIMULATION] Start builds");
    std::vector<std::thread*> threads;

    for (int i = 0; i < agent_contents.size(); i++){// agent_contents.size()
        logger->LogInfo("[SIMULATION] Start simulation for agent[" + std::to_string(i) + "]");
        auto payload = [](IController* controller, Content* content, int i, int tests_count){
            for (int j = 0; j < tests_count; j++) {
//                std::cout << "C:\\Windows\\py.exe " + kWorkflowExecutor.string() + " " + content->content_path_ << std::endl;
//                controller->logger_->LogInfo("[SIMULATION] Constructing string...");
                std::cout << "[SIMULATION] Constructing string..." << std::endl;
                std::string exec_command = "C:\\Windows\\py.exe " + kWorkflowExecutor.string() + " " + content->content_path_ + " >> test.out";
                //controller->logger_->LogInfo("[SIMULATION] Updating project in: " + content->content_path_);
//                FILE* test = _popen(exec_command.c_str(), "r");
//                pclose(test);
                std::cout << "[SIMULATION] Executing content modification..." << std::endl;
//                ShellExecute(NULL, exec_command.c_str(), NULL, NULL, NULL, SW_SHOWNORMAL);
                system(exec_command.c_str());
                std::this_thread::sleep_for(std::chrono::seconds(i + std::rand()/((RAND_MAX + 1u)/10)));
                std::cout << "[SIMULATION] Building content..." << std::endl;
                controller->BuildContent(content);
            }
        };
        threads.push_back(new std::thread(payload, agent_controllers[i], agent_contents[i], i, kTestsCount));
    }


    for (auto* thread : threads) {
        thread->join();
    }

//    for(int i = 0; i < kTestsCount; i++) {
////        time[i] = controller->BuildContent(kBuildSize);
//        d_controller->BuildContent(content);
////        summ += time[i];
//    }
    
//    double avg = summ / kTestsCount;
    
//    std::cout << "Agent count: " << kAgentCount << std::endl;
//    std::cout << "Build count: " << kBuildSize << std::endl;
//    std::cout << "Average build time: " << avg << std::endl;
//    std::cout << "Time for each build: " << std::endl;
//    for(int i = 0; i < kTestsCount; i++) {
//        std::cout << time[i] << " ";
//    }
    
    
    return 0;
}