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
    RemoteAgent(int id, std::string base_dir);
    void DoTask(ITask* job);
    std::vector<FileHash> CheckHashes(std::vector<FileHash> hashes);
};

#endif /* RemoteAgent_hpp */
