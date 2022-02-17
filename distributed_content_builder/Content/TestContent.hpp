//
//  TestContent.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 03.02.2022.
//

#ifndef TestContent_hpp
#define TestContent_hpp

#include <stdio.h>

#include "IContent.hpp"
#include "ILogger.hpp"

class TestContent : public IContent {
public:
    int size_;
    ILogger* logger_;
    
    int task_min_;
    int task_max_;
    
    int content_size_;
public:
    TestContent(int min, int max, int size, ILogger* logger)
        :task_min_(min)
        ,task_max_(max)
        ,content_size_(size)
        ,logger_(logger)
    {}

    // Deprecated
    TestContent(int size) {
        size_ = size;
    }
    
    int GetSize() {
        return size_;
    }
    
    std::vector<ITask*> GetTasks();
};

#endif /* TestContent_hpp */
