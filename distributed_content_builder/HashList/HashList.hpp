//
// Created by Евгений Курятов on 10.03.2022.
//

#ifndef DISTRIBUTED_CONTENT_BUILDER_HASHLIST_HPP
#define DISTRIBUTED_CONTENT_BUILDER_HASHLIST_HPP

#include <string>
#include <vector>

#include "ILogger.hpp"

class FileHash {
public:
    std::string file_hash_;
    std::string file_path_;
public:
    FileHash(std::string file_hash, std::string file_path)
        : file_hash_(std::move(file_hash))
        , file_path_(std::move(file_path)){};
};

class HashList {
public:
    std::string hashfile_path_;
    std::vector<FileHash> hash_list_;
    ILogger *logger_;
public:
    HashList(ILogger *logger);
    HashList(std::string path, ILogger *logger);

    void Save();
    void Save(std::string path);

    int Length();

    void AddHash(std::string hash, std::string file_path);
    bool ContainsHash(std::string hash);
    std::string GetFileByHash(std::string hash);
};


#endif //DISTRIBUTED_CONTENT_BUILDER_HASHLIST_HPP
