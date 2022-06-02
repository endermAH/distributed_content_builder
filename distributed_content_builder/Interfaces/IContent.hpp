//
//  IContent.h
//  distributed_content_builder
//
//  Created by Евгений Курятов on 02.02.2022.
//

#ifndef IContent_h
#define IContent_h

#include <vector>
#include <filesystem>

#include "ITask.hpp"

class IContent {
public:
    virtual int GetSize() = 0;
    virtual std::vector<ITask*> GetTasks(std::filesystem::path result_dir) = 0;
};
#endif /* IContent_h */
