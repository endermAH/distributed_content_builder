//
//  main.cpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 16.12.2021.
//

#include <cstdlib>

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <openssl/md5.h>
#include <getopt.h>

#include "HashList/HashList.hpp"
#include "MacLogger.hpp"
#include "UnixLogger.hpp"
#include "Controller.hpp"
#include "TestContent.hpp"
#include "Content.hpp"
#include "MetricsControllerDecorator.hpp"
#include "TestNetwork.hpp"
#include "HashManager.hpp"

const int kAgentCount = 3; // Wat if we have more than 22 nodes?
const int kBuildSize = 100;
const int kTestsCount = 1;
const std::filesystem::path kTestContentPath = std::filesystem::path("../../test_content");
const std::string kWorkflowExecutor = "/Users/evgenijkuratov/CLionProjects/distributed_content_builder/tools/workflow_imitation.py";
const bool kRecreateDir = false;

int main(int argc, char *argv[]) {
    std::srand(std::time(nullptr));

    // === DEFAULTS
    int agent_count = 3;
    std::filesystem::path work_directory = std::filesystem::path("../../test_directory");
    std::filesystem::path agents_root = work_directory/"agents";
    // === DEFAULTS

    auto* logger = new UnixLogger();
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

        if (kRecreateDir) {
            std::filesystem::remove_all(project_path);
            std::filesystem::create_directory(project_path);
            std::filesystem::copy(kTestContentPath, project_path);
        }

        auto* content = new Content(logger, project_path.string());
        agent_contents.push_back(content);

        // Prepare controllers
        std::filesystem::path result_dir = std::filesystem::path(agent->base_directory_)/"build_result";
        auto* controller = new Controller(logger, network, hash_manager, result_dir);
        auto* d_controller = new MetricsControllerDecorator(controller);
        agent_controllers.push_back(d_controller);
    }
    
    for (int i = 0; i < agent_contents.size(); i++){
        std::string exec_command = "python " + kWorkflowExecutor + " " + agent_contents[i]->content_path_;
        logger->LogInfo("[SIMULATION] Updating project in: " + agent_contents[i]->content_path_);
        std::system(exec_command.c_str());
    }

    logger->LogInfo("[SIMULATION] Start builds");
    std::vector<std::thread*> threads;

    for (int i = 0; i < 1; i++){// agent_contents.size()
        auto payload = [](IController* controller, IContent* content, int i){
            std::this_thread::sleep_for(std::chrono::seconds(i + std::rand()/((RAND_MAX + 1u)/10)));
            controller->BuildContent(content);
        };
        threads.push_back(new std::thread(payload, agent_controllers[i], agent_contents[i], i));
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
