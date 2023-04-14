//
//  UnixLogger.h
//  distributed_content_builder
//
//  Created by Евгений Курятов on 02.02.2022.
//

#ifndef WinLogger_h
#define WinLogger_h

#include <stdio.h>
#include <iostream>
#include "Interfaces.hpp"
#include "ILogger.hpp"

class WinLogger: public ILogger {
private:
    const std::string RESET = "[0m";
    const std::string GREEN = "[32m";
    const std::string RED = "[31m";
    const std::string YELLOW = "[33m";
public:
    WinLogger() {
    }
    
    void PushMessage(LogLevel level, std::string msg) {
        std::string prefix;
        switch (level) {
            case ILogger::LogLevel::Debug:
                prefix = "[DEBUG]: ";
                break;
            case ILogger::LogLevel::Info:
                prefix = "[INFO]: ";
                break;
            case ILogger::LogLevel::Success:
                prefix = GREEN + "[SUCCESS]: ";
                break;
            case ILogger::LogLevel::Warning:
                prefix = YELLOW + "[WARNING]: ";
                break;
            case ILogger::LogLevel::Error:
                prefix = RED + "[ERROR]: ";
                break;
        }
        std::string message_;
        message_ = prefix + msg + RESET;
        std::cout << message_ << std::endl;
    }
};

#endif /* WinLogger_h */
