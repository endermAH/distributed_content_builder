//
// Created by Евгений Курятов on 10.03.2022.
//

#ifndef DISTRIBUTED_CONTENT_BUILDER_IHASHMANAGER_HPP
#define DISTRIBUTED_CONTENT_BUILDER_IHASHMANAGER_HPP

#include <vector>
#include <string>

#include "ILogger.hpp"
#include "HashList.hpp"
//#include "INetwork.hpp"

class IHashManager {
public:
    ILogger *logger_;
//    INetwork *network_;
public:
    virtual std::vector<FileHash> GetArtifactsFromHashlist(HashList* local_hashes, std::vector<FileHash> requested_hashes) = 0;
    virtual std::string GenerateFileHash(std::string path) = 0;

};

#endif //DISTRIBUTED_CONTENT_BUILDER_IHASHMANAGER_HPP
