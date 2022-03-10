//
//  main.cpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 16.12.2021.
//

#include <cstdlib>

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>

#include "HashList/HashList.hpp"
#include "MacLogger.hpp"
#include "UnixLogger.hpp"
#include "Controller.hpp"
#include "TestContent.hpp"
#include "Content.hpp"
#include "DebugControllerDecorator.hpp"
#include "TestNetwork.hpp"
#include <openssl/md5.h>

const int kAgentCount = 5; // Wat if we have more than 22 nodes?
const int kBuildSize = 100;
const int kTestsCount = 0;

// ========================================
unsigned char result[MD5_DIGEST_LENGTH];

template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

// Print the MD5 sum as hex-digits.
std::string print_md5_sum(unsigned char* md) {
    std::string hash_result;
    for(int i=0; i < MD5_DIGEST_LENGTH; i++) {
        hash_result += string_format("%02x", md[i]);
    }
    return hash_result;
}

// Get the size of the file by its file descriptor
unsigned long get_size_by_fd(int fd) {
    struct stat statbuf;
    if(fstat(fd, &statbuf) < 0) exit(-1);
    return statbuf.st_size;
}
// ========================================

int main() {

    int file_descript;
    unsigned long file_size;
    void* file_buffer;

    file_descript = open("/Users/evgenijkuratov/CLionProjects/distributed_content_builder/test_content/tex_2.png", O_RDONLY);
    if(file_descript < 0) exit(-1);

    file_size = get_size_by_fd(file_descript);
    printf("file size:\t%lu\n", file_size);

    file_buffer = mmap(0, file_size, PROT_READ, MAP_SHARED, file_descript, 0);
    MD5((unsigned char*) file_buffer, file_size, result);
    munmap(file_buffer, file_size);

    UnixLogger* l = new UnixLogger();
    l->LogInfo(print_md5_sum(result));
//    printf("  %s\n", argv[1]);


    UnixLogger* logger = new UnixLogger();
    TestNetwork* network = new TestNetwork(logger, kAgentCount);
    Content* content = new Content(logger, "/Users/evgenijkuratov/CLionProjects/distributed_content_builder/test_content");
    Controller* controller = new Controller(logger, network);
    DebugControllerDecorator* d_controller = new DebugControllerDecorator(controller);
    
    
//    double time[kTestsCount];
//    double summ = 0;
    for(int i = 0; i < kTestsCount; i++) {
//        time[i] = controller->BuildContent(kBuildSize);
        d_controller->BuildContent(content);
//        summ += time[i];
    }
    
//    double avg = summ / kTestsCount;
    
//    std::cout << "Agent count: " << kAgentCount << std::endl;
//    std::cout << "Build count: " << kBuildSize << std::endl;
//    std::cout << "Average build time: " << avg << std::endl;
//    std::cout << "Time for each build: " << std::endl;
//    for(int i = 0; i < kTestsCount; i++) {
//        std::cout << time[i] << " ";
//    }
    
    
    return 0;
}
