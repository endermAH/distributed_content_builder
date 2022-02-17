//
//  IContent.h
//  distributed_content_builder
//
//  Created by Евгений Курятов on 02.02.2022.
//

#ifndef IContent_h
#define IContent_h

#include <vector>

#include "ITask.hpp"

class IContent {
public:
    virtual int GetSize() = 0;
    virtual std::vector<ITask*> GetTasks() = 0;
};
#endif /* IContent_h */
