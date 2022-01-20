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

class UnixLogger: public ILogger {
private:
    const std::string RESET = "\033[0m";
    const std::string GREEN = "\033[32m";
    const std::string RED = "\033[31m";
    const std::string YELLOW = "\033[33m";
public:
    UnixLogger() {
    }
    
    void LogError(std::string message) {
        std::string message_;
        message_ = RED + "[INFO]: " + message + RESET;
        std::cout << message_ << std::endl;
    };
    
    void LogSuccess(std::string message) {
        std::string message_;
        message_ = GREEN + "[SUCCESS]: " + message + RESET;
        std::cout << message_ << std::endl;
    };
    
    void LogWarning(std::string message) {
        std::string message_;
        message_ = YELLOW + "[ERROR]: " + message + RESET;
        std::cout << message_ << std::endl;
    };
    
    void LogInfo(std::string message) {
        std::string message_;
        message_ = "[INFO]: " + message;
        std::cout << message_ << std::endl;
    };
};

class MacLogger: public ILogger {
public:
    MacLogger() {
    }
    
    void LogError(std::string message) {
        std::string message_;
        message_ = "❌: " + message;
        std::cout << message_ << std::endl;
    };
    
    void LogSuccess(std::string message) {
        std::string message_;
        message_ = "⚡: " + message;
        std::cout << message_ << std::endl;
    };
    
    void LogWarning(std::string message) {
        std::string message_;
        message_ = "⚠️: " + message;
        std::cout << message_ << std::endl;
    };
    
    void LogInfo(std::string message) {
        std::string message_;
        message_ = "ℹ️: " + message;
        std::cout << message_ << std::endl;
    };
};

#endif /* Logger_hpp */
