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

#include "HashList/HashList.hpp"
#include "MacLogger.hpp"
#include "UnixLogger.hpp"
#include "Controller.hpp"
#include "TestContent.hpp"
#include "Content.hpp"
#include "DebugControllerDecorator.hpp"
#include "TestNetwork.hpp"
#include "HashManager.hpp"

const int kAgentCount = 5; // Wat if we have more than 22 nodes?
const int kBuildSize = 100;
const int kTestsCount = 1;


int main() {

    auto* logger = new UnixLogger();
    auto* hash_manager = new HashManager(logger);
    auto* network = new TestNetwork(logger, kAgentCount);
    auto* content = new Content(logger, "../../test_content");
    auto* controller = new Controller(logger, network, hash_manager);
    auto* d_controller = new DebugControllerDecorator(controller);

//    std::vector<std::string> content_hashes = {"4df9723f643893b5575cf55fd18ea34c"};
//    logger->LogInfo(std::to_string(content_hashes.size()));
//    auto* hl = new HashList("/Users/evgenijkuratov/CLionProjects/distributed_content_builder/cmake-build-debug/distributed_content_builder/../../test_content/agents//RemoteAgent0/hash.list", logger);
//    for (auto file : hl->hash_list_) {
//        logger->LogInfo(file.file_hash_.c_str());
//    }
//
//    hash_manager->GetArtifactsFromHashlist(hl, content_hashes);

//    return 0;
//    double time[kTestsCount];
//    double summ = 0;
    for(int i = 0; i < kTestsCount; i++) {
//        time[i] = controller->BuildContent(kBuildSize);
        d_controller->BuildContent(content);
//        summ += time[i];
    }
    
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
