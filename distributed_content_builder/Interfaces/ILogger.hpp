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
    enum LogLevel {
        Debug, Info, Success, Warning, Error
    };
public:
    virtual ~ILogger() {};
    
    virtual void PushMessage(LogLevel level, std::string msg) = 0;
    
    void LogDebug(std::string&& message){
        PushMessage(Debug, message);
    };
    
    void LogInfo(std::string&& message){
        PushMessage(Info, message);
    };
    
    void LogSuccess(std::string&& message){
        PushMessage(Success, message);
    };
    
    void LogWarning(std::string&& message){
        PushMessage(Warning, message);
    };
    
    void LogError(std::string&& message) {
        PushMessage(Error, message);
    };
};

#endif /* ILogger_h */
