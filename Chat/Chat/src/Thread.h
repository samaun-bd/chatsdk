/* 
 * File:   Thread.h
 * Author: dipal
 *
 * Created on August 31, 2015, 3:49 PM
 */

#ifndef THREAD_H
#define	THREAD_H

#include <thread>
#include <chrono>
#include <string>


namespace imsdk {
class Thread {
public:
    Thread();
    virtual ~Thread();
    
    void start();
    void stop();
    void waitForComplete();
    void detach();
    bool isRunning();
    
    void setThreadName(std::string name);
    std::string getThreadName();
    
private:
    bool running;
    std::thread t;
    std::string threadName;

    std::thread spawn();
protected:    
    virtual void runner()=0;
    
    /**
     *     
    
    void runner()
    {
        while (running)
        {
            //do run 
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
     }
     */

};
}

#endif	/* THREAD_H */

