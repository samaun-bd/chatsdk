/* 
 * File:   Thread.cpp
 * Author: dipal
 * 
 * Created on August 31, 2015, 3:49 PM
 */

#include "Thread.h"
#include <iostream>

namespace imsdk {
Thread::Thread() {
    running = false;
}

Thread::~Thread() {
}

void Thread::start()
{
    running = true;
    t=spawn();    
}

void Thread::setThreadName(std::string name)
{
    threadName = name;
}

std::string Thread::getThreadName()
{
    return threadName;
}

void Thread::stop()
{
    running = false;
}

bool Thread::isRunning()
{
    return running;
}

void Thread::waitForComplete()
{
    if (t.joinable())
    {
        t.join();
    }
}

void Thread::detach()
{
    t.detach();
}

std::thread Thread::spawn()
{
    return std::thread(&Thread::runner, this);
}
}
