/* 
 * File:   UnifiedProcessor.h
 * Author: mashroor
 *
 * Created on February 11, 2016, 3:49 PM
 */

#ifndef UNIFIEDPROCESSOR_H
#define	UNIFIEDPROCESSOR_H

#include <set>

#include "QueueElement.h"
#include "Scheduler.h"
#include "Thread.h"
#include <vector>

#include <iostream>

#include <mutex>


namespace imsdk {

class UnifiedProcessor: public Thread {
    
public:
    UnifiedProcessor();
    virtual ~UnifiedProcessor();
    
    static UnifiedProcessor& getInstance();
    
    void runner();
    
private:
    long long lastResendTime{0};
    long long lastKeepAliveTime{0};
    long long lastNetworkDataTime{0};
};

}
#endif	/* UNIFIEDPROCESSOR_H */

