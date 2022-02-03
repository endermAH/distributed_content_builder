//
//  UnixLogger.h
//  distributed_content_builder
//
//  Created by Евгений Курятов on 02.02.2022.
//

#ifndef UnixLogger_h
#define UnixLogger_h

#include <stdio.h>
#include <iostream>
#include "Interfaces.h"
#include "ILogger.h"

class UnixLogger: public ILogger {
private:
    const std::string RESET = "\033[0m";
    const std::string GREEN = "\033[32m";
    const std::string RED = "\033[31m";
    const std::string YELLOW = "\033[33m";
public:
    UnixLogger() {
    }
    
    void LogError(std::string&& message) {
        std::string message_;
        message_ = RED + "[INFO]: " + message + RESET;
        std::cout << message_ << std::endl;
    };
    
    void LogSuccess(std::string&& message) {
        std::string message_;
        message_ = GREEN + "[SUCCESS]: " + message + RESET;
        std::cout << message_ << std::endl;
    };
    
    void LogWarning(std::string&& message) {
        std::string message_;
        message_ = YELLOW + "[ERROR]: " + message + RESET;
        std::cout << message_ << std::endl;
    };
    
    void LogInfo(std::string&& message) {
        std::string message_;
        message_ = "[INFO]: " + message;
        std::cout << message_ << std::endl;
    };
};

#endif /* UnixLogger_h */
