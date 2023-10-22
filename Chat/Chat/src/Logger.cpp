/* 
 * File:   Logger.cpp
 * Author: dipal
 * 
 * Created on October 7, 2015, 5:07 PM
 */

#include "Logger.h"

namespace imsdk {
Logger::Logger() {
    logLevel = LogLevel::info;
    
    //isLogEnabled = true;
}

Logger::~Logger() {
    fout.close();
}

Logger& Logger::getInstance()
{
    static Logger logger;
    return logger;
}

void Logger::init(std::string fileName)
{
    if (fout.is_open()) 
    {
        fout.close();
    }
    
    fout.open(fileName, std::ofstream::out);
}

bool Logger::isOpen()
{
    return fout.is_open();
}

void Logger::setLogLevel(int logLevel)
{
    this->logLevel = static_cast<LogLevel>(logLevel);
}

std::ofstream& Logger::log()
{
    return fout;
}

bool Logger::isEnabled(int logLevel)
{
    return this->logLevel >= logLevel;
}

const std::string Logger::getOs()
{

    #if defined(_WIN32)
     return "Windows";
    #elif defined(__APPLE__)
    #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
     return "iOS";
    #else
     return "MacOS";
    #endif
    #elif defined(__ANDROID__)
     return "Android";
    #elif defined(__linux__)
     return "Linux";
    #else
     return "Unknown";

    #endif

}

void Logger::setLogEnabled(bool enableDisable)
{
	isLogEnabled = enableDisable;
}

bool Logger::getLogEnabled()
{
	return isLogEnabled;
}
}
