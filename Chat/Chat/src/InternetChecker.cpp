#include "InternetChecker.h"
#include "ResourceManager.h"
#ifdef __linux__
#include <bits/error_constants.h>
#include <vector>
#endif
#include "Logger.h"
#include "Types.h"
#include <mutex>
#include <thread>

#define module "InternetChecker"

namespace internetchecker{

std::mutex ipListFileMutex;
std::mutex ipListMutex;
std::mutex commonMtx;


InternetChecker& InternetChecker::getInstance(){
    static InternetChecker internetChecker;
    return internetChecker;
    }

InternetChecker::InternetChecker() {
#if defined(_WIN32) || defined(_WIN32_WCE)
   WSADATA wsaData;
   int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
   if (iResult != NO_ERROR) {
       Log(module, "Error: WSAStartup failed");
   }
#endif
}

InternetChecker::~InternetChecker() {
#if defined(_WIN32) || defined(_WIN32_WCE)
    WSACleanup();
#endif
}

void InternetChecker::setIpList(std::vector<std::string> ipList) {
    ipListMutex.lock();
    this->ipList = ipList;
    ipListMutex.unlock();
}

std::vector<std::string> InternetChecker::getIpList() const {
    std::vector<std::string> retIpList;

    ipListMutex.lock();
    retIpList = ipList;
    ipListMutex.unlock();

    return retIpList;
}

void InternetChecker::setIpListFilePath(std::string ipListFilePath) {
    commonMtx.lock();
    this->ipListFilePath = ipListFilePath + PATH_SEPARATOR + "internet_checker.settings";
    commonMtx.unlock();
}

std::string InternetChecker::getIpListFilePath() const {
    std::string filePath;

    commonMtx.lock();
    filePath = ipListFilePath;
    commonMtx.unlock();

    return filePath;
}

void InternetChecker::setPopulatingIPList(bool populatingIPList) {
    commonMtx.lock();
    this->populatingIPList = populatingIPList;
    commonMtx.unlock();
}

bool InternetChecker::isPopulatingIPList() const {
    bool isPopulating;

    commonMtx.lock();
    isPopulating = populatingIPList;
    commonMtx.unlock();

    return isPopulating;
}

void InternetChecker::setIpListLastUpdateTime(long long ipListLastUpdateTime) {
    commonMtx.lock();
    this->ipListLastUpdateTime = ipListLastUpdateTime;
    commonMtx.unlock();
}

long long InternetChecker::getIpListLastUpdateTime() const {
    long long lastUpdateTime;

    commonMtx.lock();
    lastUpdateTime = ipListLastUpdateTime;
    commonMtx.unlock();

    return lastUpdateTime;
}

bool InternetChecker::setNonBlockingMode(int sockfd){

#if defined(_WIN32) || defined(_WIN32_WCE)
    u_long flag = 1;
    if (ioctlsocket(sockfd, FIONBIO, &flag) == -1)
    {
        return false;
    }
    else return true;
#else
    int flags = fcntl(sockfd, F_GETFL, 0);
#if defined(hpux) || defined(__hpux)
    flags |= O_NONBLOCK;
#else
    flags |= O_NONBLOCK|O_NDELAY;
#endif
if (fcntl(sockfd, F_SETFL, flags) == -1)
    {
        return false;
    }
    else return true;
#endif
}

bool InternetChecker::isInternetConnectionAvailable(std::vector<std::string> &ipList){
    int res;
    fd_set writeFds;
    struct timeval timeout;
    int valopt;
    socklen_t sockLen;
    bool isConnectSuccess{false};
    SOCKET soc = -1;
    std::vector<int> indexList;
    int ipListSize = ipList.size();
    int numberOfIPs = (ipListSize>5) ? 5 : ipListSize;
    
    for (int i = 0;i < numberOfIPs; i++) {
        int index{0};
        if(i==numberOfIPs-2){
            index = ipListSize - 2;
        }
        else if(i==numberOfIPs-1){
            index = ipListSize -1;
        }
        
        if(ipListSize<5 && !index){
            index = i;
        }
        else if(ipListSize>5 && !index){
            index = rand()%(ipListSize-2);

            while(std::find(indexList.begin(), indexList.end(), index) != indexList.end()){
                index = rand()%(ipListSize-2);
            }
            indexList.push_back(index);
        }
        
        Log(module, "Trying to connect with domain ["<<index<<"]: "<< ipList[index]);
        soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (soc < 0) {
            Log(module, "Socket creation failed.");
            break;
        }
        
        setNonBlockingMode(soc);

        struct sockaddr_in remoteaddr;
        memset((char *) &remoteaddr, 0, sizeof (remoteaddr));

        remoteaddr.sin_family = AF_INET;
        remoteaddr.sin_port = htons(80);
        remoteaddr.sin_addr.s_addr = inet_addr(ipList[index].c_str());
        
        res = connect(soc, (struct sockaddr *) &remoteaddr, sizeof (remoteaddr));

        bool operationInProgress{false};
#if defined(_WIN32) || defined(_WIN32_WCE)
        if(WSAGetLastError() == WSAEWOULDBLOCK) operationInProgress = true;
#else
        if(errno == EINPROGRESS) operationInProgress = true;
#endif

        if (res == 0) {
            Log(module, "Checking Internet - connect() success");
            isConnectSuccess = true;

#ifdef _WIN32
			closesocket(soc);
#else
			close(soc);
#endif

            break;
        }
        else if (res < 0 && operationInProgress) {
            timeout.tv_sec = 7;
            timeout.tv_usec = 0;

            FD_ZERO(&writeFds);
            FD_SET(soc, &writeFds);

            res = select(soc + 1, NULL, &writeFds, NULL, &timeout);

            if (res > 0) {
                sockLen = sizeof (int);

                if (getsockopt(soc, SOL_SOCKET, SO_ERROR, (char*) (&valopt), &sockLen) < 0) {
                    Log(module, "Checking Internet - error in getsockopt()"); /*error in getsockopt()*/
                }
                if (valopt == 0) {
                    Log(module, "Checking Internet - Success");
                    isConnectSuccess = true;

#ifdef _WIN32
					closesocket(soc);
#else
					close(soc);
#endif

                    break;
                }
                else {
                    Log(module, "Checking Internet - getsockopt() setted error"); /*getsockopt() setted error*/
                }
            }
            else {
                Log(module, "Checking Internet - unhandled behaviour. select() returned:" << res);
            }

        }
        else{
            Log(module, "Checking Internet - Error during connect(). Errno: "<<errno);
        }
        

#ifdef _WIN32
        closesocket(soc);
#else
        close(soc);
#endif
    }
    return isConnectSuccess;
}

bool InternetChecker::checkInternetConnection() {
    
    Log(module, "Checking Internet connection ...");
    auto timeEpoch = std::chrono::system_clock::now().time_since_epoch();
    auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeEpoch).count();
    
    if(currentTime - lastCheckInternetTime < 1000)
    {
        Log(module, "Checking Internet connection ignored: called in short time");
        return true;
    }

    lastCheckInternetTime = currentTime;
    
    std::vector<std::string> ipListToCheck;
    std::string lastUpdateTime{"0"};
    bool isInternetAvailable{true}; //consider true for invalid cases
 
    ipListFileMutex.lock();
    
    std::ifstream fin(getIpListFilePath());
    
    if(fin.is_open()) {
        for (std::string line; getline(fin, line);) {
            if(lastUpdateTime == "0"){
                lastUpdateTime = line;
            }
            else{
                ipListToCheck.push_back(line);
            }
        }
        fin.close();
    }        
    
    ipListFileMutex.unlock();
    
    if(!isPopulatingIPList()) {
        populateIPListIfNeeded();
    }
    
    if(ipListToCheck.size() == 0){
        ipListToCheck = getIpList();
    }
    
    if (ipListToCheck.size() > 0){
        isInternetAvailable = isInternetConnectionAvailable(ipListToCheck);
    } 
    else{
        Log(module, "Error checking Internet connection - IP list is empty !!!");
    }
    
    return isInternetAvailable;
}

void InternetChecker::populateIPListIfNeeded(){
    std::string lastUpdate="0";
    
    ipListFileMutex.lock();
    
    std::ifstream fin(getIpListFilePath());
    if(fin.is_open()){
        getline(fin,lastUpdate);
        fin.close();
    }
    else {
        Log(module, "File Error - Unable to open file during fetching ip list last update !");
    }
    
    ipListFileMutex.unlock();
    
    long long lastUpdateTime = imsdk::ResourceManager::getInstance().toStringToLong(lastUpdate);
    
    /*Unable to read last update from file. Trying from Internet Checker*/
    if(lastUpdateTime == 0){
        lastUpdateTime = getIpListLastUpdateTime();
    }
    
    if(imsdk::ResourceManager::getInstance().gettime() - lastUpdateTime > dnsCacheTimeout){
        std::thread ipListGenerator(&InternetChecker::populateConnectionTestIPList, this);
        ipListGenerator.detach();

#ifndef WINDOWS_PHONE_8
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
#else
        Sleep(1000);
#endif

    }
}

void InternetChecker::populateConnectionTestIPList(){
    Log(module, "Populating Internet test IP list ...");
    long long ipGenStartTime = imsdk::ResourceManager::getInstance().gettime();
    setPopulatingIPList(true);
    std::vector<std::string> domainList;
    std::vector<std::string> connectionTestIPList;
    
    domainList.push_back("google.com");
    domainList.push_back("amazon.com");
    domainList.push_back("facebook.com");
    domainList.push_back("apple.com");
    domainList.push_back("ringid.com");
    
    struct addrinfo hints;
    struct addrinfo *resultAddress, *tempResultAddress=NULL;
    
    for (unsigned int i = 0; i < domainList.size(); i++)
    {
            memset(&hints, 0, sizeof hints);
            hints.ai_family = AF_INET;
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_flags = AI_PASSIVE;

            int error = getaddrinfo(domainList[i].c_str(), NULL, &hints, &resultAddress);

            if (error)
            {
                continue;
            }
            for(tempResultAddress = resultAddress; tempResultAddress!=NULL; tempResultAddress=tempResultAddress->ai_next){
                char clienthost[NI_MAXHOST];  //The client host will hold the IP address.
                char clientservice[NI_MAXSERV];
                int theErrorCode = getnameinfo(tempResultAddress->ai_addr, sizeof(*tempResultAddress->ai_addr), clienthost, sizeof(clienthost), clientservice, sizeof(clientservice), NI_NUMERICHOST | NI_NUMERICSERV);
                connectionTestIPList.push_back(clienthost);
                //if first fetch
                if (getIpList().size()==0)
                {
                    setIpList(connectionTestIPList);
                }
            }
    }
    
    if(connectionTestIPList.size()>0){
        long long currentTimeMillis = imsdk::ResourceManager::getInstance().gettime();
        setIpListLastUpdateTime(currentTimeMillis);
        setIpList(connectionTestIPList);
        
        ipListFileMutex.lock();
        
        std::ofstream fout;
        fout.open(getIpListFilePath(), std::ofstream::out);
        if(fout.is_open()){
            fout << currentTimeMillis << std::endl;

            for(int i=0; i<connectionTestIPList.size(); i++){
            fout << connectionTestIPList[i] << std::endl;
            }

            fout.close();
        }
        else {
            Log(module, "File Error - Unable to write updated ip list !");
        }
        
        ipListFileMutex.unlock();
        Log(module, "IP List generation - Success");
    } else{
        Log(module, "IP List generation - Failed");
    }
    setPopulatingIPList(false);
    long long ipGenEndTime = imsdk::ResourceManager::getInstance().gettime();
    Log(module, "IP generation time: "<<(ipGenEndTime - ipGenStartTime)<<" ms");
}


}
