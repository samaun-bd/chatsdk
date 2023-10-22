/* 
 * File:   InternetChecker.h
 * Author: towhid
 *
 * Created on December 5, 2016, 3:53 PM
 */

#ifndef INTERNETCHECKER_H
#define	INTERNETCHECKER_H

#include <list>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>

#ifdef _WIN32
#include <ws2tcpip.h>
#include <winsock2.h> //can also be winsock.h
#pragma comment(lib,"Ws2_32.lib")

#if !(defined(WINDOWS_UNIVERSAL) || defined(WINDOWS_PHONE_8))
#include <iphlpapi.h>
#endif
#else
#include <cerrno>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef __APPLE__
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#endif

typedef int SOCKET;
#endif


namespace internetchecker{
class InternetChecker {
public:
    static InternetChecker& getInstance();

    InternetChecker();
    ~InternetChecker();
    bool setNonBlockingMode(int sockfd);
    void populateIPListIfNeeded();
    void populateConnectionTestIPList();
    bool isInternetConnectionAvailable(std::vector<std::string> &ipList);
    bool checkInternetConnection();

    void setIpList(std::vector<std::string> ipList);
    std::vector<std::string> getIpList() const;
    void setIpListFilePath(std::string ipListFilePath);
    std::string getIpListFilePath() const;
    void setPopulatingIPList(bool populatingIPList);
    void setIpListLastUpdateTime(long long ipListLastUpdateTime);
    long long getIpListLastUpdateTime() const;
    bool isPopulatingIPList() const;
    
private:
    long long ipListLastUpdateTime{0};
    std::string ipListFilePath;
    bool populatingIPList{false};
    std::vector<std::string> ipList;
    const int dnsCacheTimeout{6*60*60*1000}; //6 hours
    long long lastCheckInternetTime{0};
};
}

#endif	/* INTERNETCHECKER_H */


