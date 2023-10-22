/* 
 * File:   PacketReceiver.cpp
 * Author: dipal
 * 
 * Created on August 17, 2015, 6:51 PM
 */

#include "PacketReceiver.h"
#include "Types.h"
#include "ByteArray.h"
#include "Thread.h"
#include "PacketProcessor.h"

namespace imsdk {
PacketReceiver::PacketReceiver() {
    
    FD_ZERO(&activeFds);
    
    receiveBufferLen = 2048;
    receiveBuffer = new uint8_t[receiveBufferLen];
    this->setThreadName("IM_PR_PROC");
}

PacketReceiver& PacketReceiver::getInstance()
{
    static PacketReceiver packetReceiver;
    return packetReceiver;
}

PacketReceiver::~PacketReceiver() {
    stop();
    delete receiveBuffer;
}

void PacketReceiver::addSocket(std::shared_ptr< UDPSocket> socket)
{
    FD_SET(socket->getFd(), &activeFds);
    
    socketListMutex.lock();
    
    socketList.insert(socket);
    
    socketListMutex.unlock();
}

void PacketReceiver::removeSocket(std::shared_ptr< UDPSocket> socket)
{
    auto it = socketList.find(socket);
    if (it != socketList.end())
    {
        FD_CLR(socket->getFd(), &activeFds);
        (*it)->setToBeClosed(true);
    }
}

void PacketReceiver::clearSocketList()
{
    FD_ZERO(&activeFds);
    for(auto it=socketList.begin(); it!=socketList.end(); it++){
        (*it)->setToBeClosed(true);
    }
}

long long PacketReceiver::getDataReceived(){
    long long packetDataReceived = dataReceived;
    dataReceived = 0;
    return packetDataReceived;
}

void PacketReceiver::runner()
{
    receiver();
}

void PacketReceiver::receiver()
{
#ifdef IMSDK_LOG
#ifdef __APPLE__
    pthread_setname_np(getThreadName().c_str());
#endif
#endif
    while (isRunning())
    {
        if (socketList.empty())
        {
#ifndef WINDOWS_PHONE_8
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
#else
            Sleep(1000);
#endif

            continue;
            //wait;
        }
        fd_set readFds = activeFds;
        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        
        int maxFd = (*socketList.begin())->getFd();
        int rv = select(maxFd+1, &readFds, NULL, NULL, &tv);
        
        if (rv<=0) 
        {
            continue;
        }
        
        int readlen = 0;
        
        for (auto it = socketList.begin(); it!=socketList.end(); it++)
        {
            if (FD_ISSET((*it)->getFd(), &readFds))
            {
                std::string addr;
                int port;
                readlen = (*it)->recvFrom(receiveBuffer, receiveBufferLen, addr, port);
                break;
            }
        }
        if (readlen>0 && readlen<=4096)
        {
            //printf("PACKET RECEIVED-------First byte: %d second byte: %d\n", receiveBuffer[0], receiveBuffer[1]);
            dataReceived += readlen;
            PacketProcessor::getInstance().push(ByteArray(receiveBuffer, readlen));
        }
        else 
        {
            //error
        }
        socketListMutex.lock();
        for (auto it = socketList.begin(); it!=socketList.end();)
        {
            if((*it)->isToBeClosed()){
                FD_CLR((*it)->getFd(), &activeFds);
                it = socketList.erase(it);
            }
            else {
                it++;
            }
        }
        socketListMutex.unlock();
    }
}
}
