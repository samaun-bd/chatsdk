/* 
 * File:   Processor.h
 * Author: dipal
 *
 * Created on August 18, 2015, 3:46 PM
 */

#ifndef PROCESSOR_H
#define	PROCESSOR_H

#include <set>

#include "QueueElement.h"
#include "Scheduler.h"
#include "Thread.h"
#include <vector>
#include <mutex>


namespace imsdk {
template <class CLASS_TYPE, class SCHEDULER = Scheduler> 
class Processor : public Thread {
public:
    Processor();
    virtual ~Processor();
    
    void push(CLASS_TYPE element, Priority priority = Priority::l3);
    CLASS_TYPE top();
    std::vector<CLASS_TYPE> getAll();
    void pop();
    bool empty();
    int size();
    void clear();
    
    void setExecutionDelay(int milliSeconds);
    void runner();
    virtual void run()=0;
    
    virtual void onThreadStopped();
    
private:
    std::multiset<QueueElement<CLASS_TYPE> > s;
    SCHEDULER scheduler;    
    int executionDelay;
    std::mutex processorMutex;

};




/**
 * Template Impl
 */

template <class CLASS_TYPE, class SCHEDULER>
Processor<CLASS_TYPE, SCHEDULER>::Processor() {
    executionDelay = 10;
}

template <class CLASS_TYPE, class SCHEDULER>
Processor<CLASS_TYPE, SCHEDULER>::~Processor() {
    stop();
}

template <class CLASS_TYPE, class SCHEDULER>
void Processor<CLASS_TYPE, SCHEDULER>::push(CLASS_TYPE element, Priority priority)
{
    processorMutex.lock();
    s.insert(QueueElement<CLASS_TYPE>(element, scheduler.getTime(), priority));
    processorMutex.unlock();
}

template <class CLASS_TYPE, class SCHEDULER>
CLASS_TYPE Processor<CLASS_TYPE, SCHEDULER>::top()
{
    QueueElement<CLASS_TYPE> topElement(CLASS_TYPE(), scheduler.getTime());

    processorMutex.lock();
    if(!s.empty())
    {
        topElement = *s.begin();
    }

    processorMutex.unlock();

    return topElement.value();
}

template <class CLASS_TYPE, class SCHEDULER>
std::vector<CLASS_TYPE> Processor<CLASS_TYPE, SCHEDULER>::getAll()
{
    std::vector<CLASS_TYPE> dataVector;
    processorMutex.lock();
    for (auto it = s.begin(); it!=s.end(); it++)
    {
        dataVector.push_back((*it).value());
    }
    processorMutex.unlock();
    return dataVector;
}

template <class CLASS_TYPE, class SCHEDULER>
void Processor<CLASS_TYPE, SCHEDULER>::pop()
{
    processorMutex.lock();
    if(!s.empty())
    {
        s.erase(s.begin());
    }
    processorMutex.unlock();
}

template <class CLASS_TYPE, class SCHEDULER>
bool Processor<CLASS_TYPE, SCHEDULER>::empty()
{
    processorMutex.lock();
    bool isEmpty = s.empty();
    processorMutex.unlock();
    return isEmpty;
}

template <class CLASS_TYPE, class SCHEDULER>
int Processor<CLASS_TYPE, SCHEDULER>::size()
{
    processorMutex.lock();
    int processorSetSize = s.size();
    processorMutex.unlock();
    return processorSetSize;
}

template <class CLASS_TYPE, class SCHEDULER>
void Processor<CLASS_TYPE, SCHEDULER>::clear()
{
    processorMutex.lock();
    s.clear();
    processorMutex.unlock();
}

template <class CLASS_TYPE, class SCHEDULER>
void Processor<CLASS_TYPE, SCHEDULER>::setExecutionDelay(int milliSeconds)
{
    executionDelay = milliSeconds;
}

template <class CLASS_TYPE, class SCHEDULER>
void Processor<CLASS_TYPE, SCHEDULER>::runner()
{
#ifdef IMSDK_LOG
#ifdef __APPLE__
    pthread_setname_np(getThreadName().c_str());
#endif
#endif
    while (isRunning())
    {
        run();
#ifndef WINDOWS_PHONE_8
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
#else
        Sleep(10);
#endif

    }
    
    onThreadStopped();
}

template <class CLASS_TYPE, class SCHEDULER>
void Processor<CLASS_TYPE, SCHEDULER>::onThreadStopped()
{
    
}
}

#endif	/* PROCESSOR_H */

