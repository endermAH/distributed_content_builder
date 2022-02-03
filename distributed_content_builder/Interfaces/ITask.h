//
//  ITask.h
//  distributed_content_builder
//
//  Created by Евгений Курятов on 02.02.2022.
//

#ifndef ITask_h
#define ITask_h

class ITask {
public:
    enum class TaskStatus: char {
        TASK_IN_PROGRESS, TASK_DONE, TASK_READY_FOR_BUILD, TASK_FAILED
    };
    
    virtual TaskStatus GetStatus() = 0;
    virtual void SetStatus(TaskStatus new_status) = 0;
    virtual int GetSize() = 0;
};

#endif /* ITask_h */
