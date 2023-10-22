/* 
 * File:   Logger.h
 * Author: dipal
 *
 * Created on October 7, 2015, 5:07 PM
 */

#ifndef LOGGER_H
#define	LOGGER_H

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <fstream>
#include <mutex>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <iostream>
#include <ostream>
#include <sstream>

#ifdef __ANDROID__
#include <android/log.h>
#elif __APPLE__
void iosConsoleLog(std::string s);
#endif

static std::mutex logMutex;

inline std::string getCurrentTimeString()
{
    auto curTime = std::chrono::system_clock::now();
    auto curTime_t = std::chrono::system_clock::to_time_t(curTime);
    std::string timestr = std::ctime(&curTime_t);
    timestr.pop_back();
    
    return timestr;
}

#ifdef IMSDK_LOG
    #ifdef __ANDROID__
#define Log(module, x) \
logMutex.lock(); \
if (imsdk::Logger::getInstance().getLogEnabled()) \
{std::stringstream s; s<<"["<<module<<"]"<<x; __android_log_print(ANDROID_LOG_VERBOSE, "imsdk", "%s", s.str().c_str()); \
imsdk::Logger::getInstance().isOpen() && imsdk::Logger::getInstance().log() <<"["<<getCurrentTimeString()<<"] ["<<module<<"] "<< x << std::endl;} \
logMutex.unlock()
    #elif __APPLE__
#define Log(module, x) \
logMutex.lock(); \
if (imsdk::Logger::getInstance().getLogEnabled()) \
{std::stringstream s; s<<"["<<module<<"] "<< x; iosConsoleLog(s.str());\
imsdk::Logger::getInstance().isOpen() && imsdk::Logger::getInstance().log() <<"["<<getCurrentTimeString()<<"] ["<<module<<"] "<< x << std::endl;} \
logMutex.unlock()
    #else
#define Log(module, x) \
logMutex.lock(); \
if (imsdk::Logger::getInstance().getLogEnabled()) \
{imsdk::Logger::getInstance().isOpen() && imsdk::Logger::getInstance().log() <<"["<<getCurrentTimeString()<<"] ["<<module<<"] "<< x << std::endl;} \
logMutex.unlock()

    #endif
#else
#define Log(module, x) ;
#endif

enum LogLevel
{
    trace=5,
    debug=4,
    info=3,
    warning=2,
    error=1
};

namespace imsdk {
class Logger {
public:
    
    static Logger& getInstance();
    
    virtual ~Logger();
    
    void init(std::string fileName);
    void setLogLevel(int logLevel);
    bool isOpen();
    std::ofstream& log();
    bool isEnabled(int logLevel);
    
    void setLogEnabled(bool enableDisable);
    bool getLogEnabled();
    
    static const std::string getOs();

private:
    std::ofstream fout;
    Logger();
    
    LogLevel logLevel;
    bool isLogEnabled;
};
}

#endif	/* LOGGER_H */

