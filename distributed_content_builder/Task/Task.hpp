//
// Created by Евгений Курятов on 17.02.2022.
//

#ifndef DISTRIBUTED_CONTENT_BUILDER_TASKCOMPRESS_PPH
#define DISTRIBUTED_CONTENT_BUILDER_TASKCOMPRESS_PPH

#include <string>
#include <thread>
#include <cstdlib>

#include "ITask.hpp"

class Task: public ITask {
private:
    std::string params_;
    std::string executor_;
public:
    Task(std::string executor, std::string params) {
        status_ = TaskStatus::TASK_READY_FOR_BUILD;
        executor_ = executor;
        params_ = params;
        size_ = 0;
    }

    TaskStatus GetStatus(){
        return status_;
    }

    void SetStatus(TaskStatus new_status){
        status_ = new_status;
    }

    int GetSize(){
        return size_;
    }

    void GetPayload() {
        std::string exec_command = executor_ + " " + params_;
        std::system(exec_command.c_str());
    }
};

#endif //DISTRIBUTED_CONTENT_BUILDER_TASKCOMPRESS_PPH
