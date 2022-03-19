//
//  Controller.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 02.02.2022.
//

#ifndef Controller_hpp
#define Controller_hpp

#include <stdio.h>

#include "IController.hpp"

class Controller : public IController {
public:
    std::vector<ITask*> task_list_;
public:
    Controller(ILogger *logger, INetwork* network, IHashManager* hash_manager);
    
    std::vector<IRemoteAgent*> GetAvailableAgents();
    
    bool AssignTask(IRemoteAgent* agent);
    bool AllTasksComplete();
    
    void BuildContent(IContent* content);
};

#endif /* Controller_hpp */
