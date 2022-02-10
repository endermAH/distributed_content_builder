//
//  TestTask.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 09.02.2022.
//

#ifndef TestTask_hpp
#define TestTask_hpp

#include <stdio.h>
#include "IRemoteAgent.h"

class Task: public ITask {
public:
    Task(int count) {
        size_ = count;
        status_ = TaskStatus::TASK_READY_FOR_BUILD;
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
};

#endif /* TestTask_hpp */
