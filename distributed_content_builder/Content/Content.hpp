//
// Created by Евгений Курятов on 17.02.2022.
//

#ifndef DISTRIBUTED_CONTENT_BUILDER_CONTENT_H
#define DISTRIBUTED_CONTENT_BUILDER_CONTENT_H

#include <string>

#include "IContent.hpp"
#include "ILogger.hpp"

class Content : public IContent {
public:
    int size_;
    ILogger* logger_;

//    int content_size_;
    std::string content_path_;
public:
    Content(ILogger* logger, std::string content_path)
            :logger_(logger)
            ,content_path_(content_path)
            ,size_(0)
    {}

    int GetSize() {
        return size_;
    }

    std::vector<ITask*> GetTasks(std::filesystem::path result_dir);
};


#endif //DISTRIBUTED_CONTENT_BUILDER_CONTENT_H
