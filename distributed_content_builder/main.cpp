//
//  main.cpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 16.12.2021.
//

#include <iostream>
#include <cstdlib>
#include <thread>
#include "Queue.hpp"
#include "Agent.hpp"

const int kAgentCount = 16; // Wat if we have more than 22 nodes?
const int kBuildSize = 50;
const int kTestsCount = 1;

int main(int argc, const char * argv[]) {
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";
    Agent* current_agent = new Agent(999, kAgentCount);
    
    double time[kTestsCount];
    double summ = 0;
    for(int i = 0; i < kTestsCount; i++) {
        time[i] = current_agent->BuildContent(kBuildSize);
        summ += time[i];
    }
    double avg = summ / kTestsCount;
    
    std::cout << "Agent count: " << kAgentCount << std::endl;
    std::cout << "Build count: " << kBuildSize << std::endl;
    std::cout << "Average build time: " << avg << std::endl;
    std::cout << "Time for each build: " << std::endl;
    for(int i = 0; i < kTestsCount; i++) {
        std::cout << time[i] << " ";
    }
    
    
    return 0;
}
