//
//  TestContent.cpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 03.02.2022.
//

#include <time.h>
#include <cstdlib>
#include <string>

#include "TestContent.hpp"
#include "ILogger.hpp"
#include "TestTask.hpp"

std::vector<ITask*> TestContent::GetTasks() {
    std::srand(std::time(nullptr));
    
    std::vector<int> task_sizes_;
    std::vector<ITask*> task_list_;
    
    int tmp_content_size = content_size_;
    int task_count_ = 0;
    int rand_count;
    
    while (tmp_content_size > task_max_) {
        rand_count = task_min_ + std::rand() % (task_max_ - task_min_);
        task_sizes_.push_back(rand_count);
        tmp_content_size -= rand_count;
        task_count_++;
    }
    task_sizes_.push_back(tmp_content_size);
    task_count_++;
    
    for(int i = 0; i < task_count_; i++) {
        task_list_.push_back(new Task(task_sizes_[i]));
    }
    
    std::string tasks_string;
    for (int i=0; i<task_count_; i++){
        tasks_string.append(" ");
        tasks_string.append(std::to_string(task_list_[i]->GetSize()));
    }
    
//    std::string msg = "Jobs to do: " + tasks_string;
    logger_->LogInfo("Jobs to do:" + tasks_string);
    
    return task_list_;
}
