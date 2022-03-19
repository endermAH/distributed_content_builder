//
//  RemoteAgent.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 03.02.2022.
//

#ifndef RemoteAgent_hpp
#define RemoteAgent_hpp

#include <stdio.h>

#include "IRemoteAgent.hpp"

class RemoteAgent: public IRemoteAgent {
public:
    std::string base_directory_;
public:
    RemoteAgent(int id, std::string base_dir);
    void DoTask(ITask* job);
    std::vector<std::string> CheckHashes(std::vector<std::string> hashes);
};

#endif /* RemoteAgent_hpp */
