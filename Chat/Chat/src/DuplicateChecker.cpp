/* 
 * File:   DuplicateChecker.cpp
 * Author: towhid
 * 
 * Created on April 20, 2016, 12:11 PM
 */

#include "DuplicateChecker.h"

namespace imsdk {
DuplicateChecker::DuplicateChecker() {
    
}

//bool EventProcessor::DuplicateEventQueue::isSafe(std::string h, int t)
//{
//    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
//    
//    auto it = m.find(h);
//    if (it != m.end() && std::chrono::duration_cast<std::chrono::seconds>(currentTime - (*it).second).count() < allowedDuplicateDuration) {
//        m[h] = currentTime;
//        return false;
//    }
//
//    q.push(h);
//    m[h] = currentTime;
//
//    if (q.size()>maxQueueSize) {
//        std::string pop = q.front(); q.pop();
//        auto it = m.find(pop);
//        if (it!=m.end()) {
//            m.erase(it);
//        }
//    }
//    
//    return true;
//}
bool DuplicateChecker::isSafe(std::string h, int t)
{
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    
    auto it = m.find(h);
    if (it != m.end() && std::chrono::duration_cast<std::chrono::seconds>(currentTime - (*it).second.lastAccessTime).count() < (*it).second.allowedTimeDuration) {
        m[h] = {h, currentTime, t};
        return false;
    }
    
    hashTime newHash;
    newHash.hash = h;
    newHash.lastAccessTime = currentTime;
    newHash.allowedTimeDuration = t;
    
    s.insert(newHash);
    
    m[h] = {h, currentTime, t};

    if (s.size()>maxQueueSize) {
        auto pop = s.begin();
        auto it = m.find((*pop).hash);
        if (it!=m.end() && std::chrono::duration_cast<std::chrono::seconds>(currentTime - (*it).second.lastAccessTime).count() > (*it).second.allowedTimeDuration) {
            m.erase(it);
            s.erase(s.begin());
        }
    }
    
    return true;
}

void DuplicateChecker::removeDuplicateInfo(std::string hash)
{
    auto it = m.find(hash);
    if (it != m.end())
    {
        m.erase(it);
    }
}

void DuplicateChecker::clear()
{
    m.clear();
    s.clear();
}

}