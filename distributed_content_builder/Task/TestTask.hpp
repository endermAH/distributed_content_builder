//
//  TestTask.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 09.02.2022.
//

#ifndef TestTask_hpp
#define TestTask_hpp

#include <cstdio>
#include <cstdlib>
#include <thread>

#include "IRemoteAgent.hpp"

class TestTask: public ITask {
public:
    TestTask(int count) {
        size_ = count;
        status_ = TaskStatus::TASK_READY_FOR_BUILD;
    }

    TaskStatus GetStatus() {
        return status_;
    }

    void SetStatus(TaskStatus new_status) {
        status_ = new_status;
    }

    int GetSize() {
        return size_;
    }

    void Do(std::string result_dir) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 * GetSize()));
    }
};
#endif /* TestTask_hpp */