//
// Created by Евгений Курятов on 10.03.2022.
//

#ifndef DISTRIBUTED_CONTENT_BUILDER_IHASHMANAGER_HPP
#define DISTRIBUTED_CONTENT_BUILDER_IHASHMANAGER_HPP

#include "ILogger.hpp"
#include "INetwork.hpp"

class IHashManager {
public:
    ILogger *logger_;
    INetwork *network_;
public:
    virtual std::vector<IRemoteAgent*> GetAvailableAgents() = 0;
    virtual void BuildContent(IContent* content) = 0;
};

#endif //DISTRIBUTED_CONTENT_BUILDER_IHASHMANAGER_HPP
