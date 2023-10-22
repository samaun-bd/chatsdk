/* 
 * File:   DuplicateChecker.h
 * Author: towhid
 *
 * Created on April 20, 2016, 12:11 PM
 */

#ifndef DUPLICATECHECKER_H
#define	DUPLICATECHECKER_H

#include <string>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <set>
#include <chrono>


namespace imsdk {
class DuplicateChecker {
public:
    DuplicateChecker();
    bool isSafe(std::string hash, int time=15);
    static const int allowedDuplicateDuration{5};
    void removeDuplicateInfo(std::string hash);
    void clear();
private:
    static const int maxQueueSize{100};
    std::queue<std::string> q;

    struct hashTime
    {
        std::string hash;
        std::chrono::steady_clock::time_point lastAccessTime;
        int allowedTimeDuration;
    };
    struct classcomp {
        bool operator() (const hashTime& lowTime, const hashTime& hightTime) const
        {return lowTime.lastAccessTime<hightTime.lastAccessTime;}
    };
//        std::unordered_map<string,std::chrono::steady_clock::time_point> m;
    std::unordered_map<std::string,hashTime> m;
    std::set<hashTime, classcomp> s;
};
}

#endif	/* DUPLICATECHECKER_H */

