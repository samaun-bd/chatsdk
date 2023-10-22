/* 
 * File:   Scheduler.h
 * Author: dipal
 *
 * Created on August 23, 2015, 5:15 PM
 */

#ifndef SCHEDULER_H
#define	SCHEDULER_H

namespace imsdk {
class Scheduler {
public:
    Scheduler();
    virtual unsigned long long getTime();
    virtual ~Scheduler();
protected:
    unsigned long long time;
};
}

#endif	/* SCHEDULER_H */

