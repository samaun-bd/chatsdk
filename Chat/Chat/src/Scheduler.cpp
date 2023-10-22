/* 
 * File:   Scheduler.cpp
 * Author: dipal
 * 
 * Created on August 23, 2015, 5:15 PM
 */

#include "Scheduler.h"

namespace imsdk {
Scheduler::Scheduler() {
    time=1;
}

unsigned long long Scheduler::getTime() {
    return time++;
}

Scheduler::~Scheduler() {
}
}

