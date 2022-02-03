//
//  Logger.hpp
//  distributed_content_builder
//
//  Created by Евгений Курятов on 20.01.2022.
//

#ifndef Logger_hpp
#define Logger_hpp

#include <stdio.h>
#include <iostream>
#include "Interfaces.h"
#include "ILogger.h"


class MacLogger: public ILogger {
public:
    MacLogger() {
    }
    
    void LogError(std::string&& message) {
        std::string message_;
        message_ = "❌: " + message;
        std::cout << message_ << std::endl;
    };
    
    void LogSuccess(std::string&& message) {
        std::string message_;
        message_ = "⚡: " + message;
        std::cout << message_ << std::endl;
    };
    
    void LogWarning(std::string&& message) {
        std::string message_;
        message_ = "⚠️: " + message;
        std::cout << message_ << std::endl;
    };
    
    void LogInfo(std::string&& message) {
        std::string message_;
        message_ = "ℹ️: " + message;
        std::cout << message_ << std::endl;
    };
};

#endif /* Logger_hpp */
