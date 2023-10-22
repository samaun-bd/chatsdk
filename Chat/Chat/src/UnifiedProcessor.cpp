/* 
 * File:   UnifiedProcessor.cpp
 * Author: mashroor
 * 
 * Created on February 11, 2016, 3:49 PM
 */

#include "UnifiedProcessor.h"
#include "ResendProcessor.h"
#include "KeepaliveProcessor.h"
#include "PacketProcessor.h"
#include "PacketDTO.h"
#include "ResourceManager.h"
#include "Logger.h"

namespace imsdk {
    
UnifiedProcessor::UnifiedProcessor() {
    this->setThreadName("IM_UF_PROC");
    auto currentTime = ResourceManager::getInstance().gettime();
    lastResendTime = currentTime;
    lastKeepAliveTime = currentTime;
    lastNetworkDataTime = currentTime;
}

UnifiedProcessor::~UnifiedProcessor() {
}

UnifiedProcessor& UnifiedProcessor::getInstance()
{
    static UnifiedProcessor unifiedProcessor;
    return unifiedProcessor;
}

void UnifiedProcessor::runner(){
  
#ifdef IMSDK_LOG
#ifdef __APPLE__
    pthread_setname_np(getThreadName().c_str());
#endif
#endif

    while (isRunning())
    {
        // thread task func() here)
        auto timeEpoch = std::chrono::system_clock::now().time_since_epoch();
        auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeEpoch).count();

        if(currentTime - lastNetworkDataTime >= 60000)
        {
            ResourceManager::getInstance().countNetworkData();
            lastNetworkDataTime = currentTime;
        }
        
        if(currentTime - lastResendTime >= 2000)
        {
            ResendProcessor::getInstance().processResendTasks();
            lastResendTime = currentTime;
        }
        
		if(currentTime - lastKeepAliveTime >= 15000)
        {
            KeepaliveProcessor::getInstance().processKeepaliveTasks();
            lastKeepAliveTime = currentTime;
        }
        
        PacketProcessor::getInstance().processPacketProcessTasks();
               
#ifndef WINDOWS_PHONE_8
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
#else
        Sleep(10);
#endif
    }
    
    //cout << "UnifiedProcessor while loop breaking - " << getThreadName() << endl;
}

}