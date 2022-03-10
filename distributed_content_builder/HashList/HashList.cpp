//
// Created by Евгений Курятов on 10.03.2022.
//

#include <fstream>

#include "HashList.hpp"

HashList::HashList(ILogger *logger) {
    logger_ = logger;
}

HashList::HashList(std::string path, ILogger *logger) {
    logger_ = logger;
    std::ifstream infile(path);
    std::string result_path, hash;
    while (infile >> result_path >> hash)
    {
        hash_list_.push_back(FileHash(hash, result_path));
    }
}

int HashList::Length() {
    return hash_list_.size();
}

void HashList::Save(std::string path) {
    hashfile_path_ = path;
    std::ofstream outfile(path);
    for (int i = 0; i < Length(); i++) {
        outfile << hash_list_[i].file_path_ << " " << hash_list_[i].file_hash_ << "\n";
    }
    outfile.close();
}

void HashList::Save() {
    if (hashfile_path_.empty()) {
        logger_->LogError("No hashfile path configured, use HashList::Save(std::string path)");
    } else {
        Save(hashfile_path_);
    }
}

void HashList::AddHash(std::string hash, std::string file_path) {
    hash_list_.push_back(FileHash(hash, file_path));
}

bool HashList::ContainsHash(std::string hash) {
    bool result = false;
    for (int i = 0; i < Length(); i++) {
        if (hash_list_[i].file_hash_ == hash) {
            result = true;
            break;
        }
    }
    return result;
}

std::string HashList::GetFileByHash(std::string hash) {
    std::string file_path;
    for (int i = 0; i < Length(); i++) {
        if (hash_list_[i].file_hash_ == hash) {
            file_path = hash_list_[i].file_path_;
            break;
        }
    }
    return file_path;
}



