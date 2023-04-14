//
// Created by Евгений Курятов on 10.03.2022.
//

#include <openssl/md5.h>
#include <openssl/sha.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <fstream>

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

/*std::string HashManager::GenerateFileHash(std::string path){
    unsigned char result[SHA_DIGEST_LENGTH];
    int file_descript;
    unsigned long file_size;
    void* file_buffer;

    file_descript = open(path.c_str(), O_RDONLY);
    if(file_descript < 0) exit(-1);

    FILE *f = fopen(path.c_str(), "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    unsigned char *string = (unsigned char *)malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);

    string[fsize] = 0;

    struct stat statbuf;
    if(fstat(file_descript, &statbuf) < 0) exit(-1);
    file_size = statbuf.st_size;
    SHA256((unsigned char*) string, file_size, result);

    return StringFromBuffer(result);
}*/

std::string HashManager::GenerateFileHash(std::string path) {
    std::ifstream file(path, std::ios::binary);

    if (!file) {
        logger_->LogError("Error opening file: " + path);
        return "";
    }

    // get file length
    file.seekg(0, std::ios::end);
    std::streampos length = file.tellg();
    file.seekg(0, std::ios::beg);

    // allocate buffer and read file data
    char* buffer = new char[length];
    file.read(buffer, length);

    // calculate hash
    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5((const unsigned char*)buffer, length, hash);

    // convert hash to string
    std::stringstream ss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    // clean up and return result
    delete[] buffer;
    return ss.str();
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

