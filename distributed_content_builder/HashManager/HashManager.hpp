//
// Created by Евгений Курятов on 10.03.2022.
//

#ifndef DISTRIBUTED_CONTENT_BUILDER_HASHMANAGER_HPP
#define DISTRIBUTED_CONTENT_BUILDER_HASHMANAGER_HPP


#include "IHashManager.hpp"
#include "HashList.hpp"

class HashManager : public IHashManager {
public:
    ILogger* logger_;
public:
    HashManager(ILogger* logger):logger_(logger){};
    std::vector<std::string> GetArtifactsFromHashlist(HashList* local_hashes, std::vector<std::string> requested_hashes);
    std::string GenerateFileHash(std::string path);
private:
    std::string StringFromBuffer(unsigned char* md);
};


#endif //DISTRIBUTED_CONTENT_BUILDER_HASHMANAGER_HPP
