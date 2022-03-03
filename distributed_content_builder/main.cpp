//
//  main.cpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 16.12.2021.
//

#include <iostream>
#include <cstdlib>
#include <thread>

#include "MacLogger.hpp"
#include "UnixLogger.hpp"
#include "Controller.hpp"
#include "TestContent.hpp"
#include "Content.hpp"
#include "DebugControllerDecorator.hpp"
#include "TestNetwork.hpp"
#include <openssl/sha.h>

#include <stdio.h>
#include <string.h>

const int kAgentCount = 5; // Wat if we have more than 22 nodes?
const int kBuildSize = 100;
const int kTestsCount = 1;

int main() {
    unsigned char ibuf[] = "compute sha1";
    unsigned char obuf[20];

    SHA1(ibuf, std::strlen((char*)ibuf), obuf);

    int i;
    for (i = 0; i < 20; i++) {
        printf("%02x ", obuf[i]);
    }
    printf("\n");

    UnixLogger* logger = new UnixLogger();
    TestNetwork* network = new TestNetwork(logger, kAgentCount);
    Content* content = new Content(logger, "/Users/evgenijkuratov/CLionProjects/distributed_content_builder/test_content");
    Controller* controller = new Controller(logger, network);
    DebugControllerDecorator* d_controller = new DebugControllerDecorator(controller);
    
    
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
