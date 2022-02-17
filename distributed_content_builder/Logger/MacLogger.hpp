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
#include "Interfaces.hpp"
#include "ILogger.hpp"


class MacLogger: public ILogger {
public:
    MacLogger() {
    }
    
    void PushMessage(LogLevel level, std::string msg) {
        std::string prefix;
        switch (level) {
            case ILogger::LogLevel::Debug:
                prefix = "🌚: ";
                break;
            case ILogger::LogLevel::Info:
                prefix = "ℹ️: ";
                break;
            case ILogger::LogLevel::Success:
                prefix = "✅: ";
                break;
            case ILogger::LogLevel::Warning:
                prefix = "⚠️: ";
                break;
            case ILogger::LogLevel::Error:
                prefix = "⛔: ";
                break;
        }
        std::string message_;
        message_ = prefix + msg;
        std::cout << message_ << std::endl;
    }
};

#endif /* Logger_hpp */
