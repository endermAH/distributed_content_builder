//
// Created by Евгений Курятов on 10.03.2022.
//

#include <openssl/md5.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

#include "HashManager.hpp"
#include "HashList.hpp"

std::vector<FileHash> HashManager::GetArtifactsFromHashlist(HashList* local_hashes, std::vector<FileHash> requested_hashes){
    std::vector<FileHash> existing_files;
    for (auto hash : requested_hashes) {
        std::vector<FileHash> local_file_hashes = local_hashes->hash_list_;
        auto result = std::find(local_file_hashes.begin(), local_file_hashes.end(), hash);
        if(result != local_file_hashes.end()){
            existing_files.push_back(*result);
        }
    }
    return existing_files;
}

std::string HashManager::GenerateFileHash(std::string path){
    unsigned char result[MD5_DIGEST_LENGTH];
    int file_descript;
    unsigned long file_size;
    void* file_buffer;

    file_descript = open(path.c_str(), O_RDONLY);
    if(file_descript < 0) exit(-1);

    struct stat statbuf;
    if(fstat(file_descript, &statbuf) < 0) exit(-1);
    file_size = statbuf.st_size;

    MD5((unsigned char*) file_buffer, file_size, result);

    return StringFromBuffer(result);
}

std::string HashManager::StringFromBuffer(unsigned char* md) {
    std::string hash_result;
    for(int i=0; i < MD5_DIGEST_LENGTH; i++) {

        int size_s = std::snprintf( nullptr, 0, "%02x", md[i] ) + 1; // Extra space for '\0'
        if( size_s <= 0 ){ logger_->LogError( "[HashManager]: Error during formatting." ); }
        auto size = static_cast<size_t>( size_s );
        std::unique_ptr<char[]> buf( new char[ size ] );
        std::snprintf( buf.get(), size, "%02x", md[i] );

        hash_result += std::string( buf.get(), buf.get() + size - 1 );
    }
    return hash_result;
}

