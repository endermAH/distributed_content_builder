//
//  ILogger.h
//  distributed_content_builder
//
//  Created by Евгений Курятов on 02.02.2022.
//

#ifndef ILogger_h
#define ILogger_h

class ILogger {
public:
    virtual ~ILogger() {};
    
    virtual void LogError(std::string&& message) = 0;
    virtual void LogSuccess(std::string&& message) = 0;
    virtual void LogWarning(std::string&& message) = 0;
    virtual void LogInfo(std::string&& message) = 0;
};

#endif /* ILogger_h */
