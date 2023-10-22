/* 
 * File:   PacketReceiver.h
 * Author: dipal
 *
 * Created on August 17, 2015, 6:51 PM
 */

#ifndef PACKETRECEIVER_H
#define	PACKETRECEIVER_H

#include "Thread.h"
#include "Socket.h"
#include <set>
#include <functional>


namespace imsdk {
class SocketComparator
{
public:
    bool operator () (const std::shared_ptr< UDPSocket> &a, const std::shared_ptr< UDPSocket> &b) const
    {
        return a->getFd() > b->getFd();
    }
};

class PacketReceiver : public Thread {
public:
    virtual ~PacketReceiver();
    
    static PacketReceiver& getInstance();
    
    /**
     * Add the Socket to listen. Will be ignored if the socket is already listed
     * @param socket
     */
    void addSocket(std::shared_ptr< UDPSocket> socket);
    
    /**
     * Remove the Socket to listen. Wont do anything if the socket is not listed
     * @param socket
     */
    void removeSocket(std::shared_ptr< UDPSocket> socket);
    
    void clearSocketList();
    
    /**
     * Runner will start receiving from sockets
     */
    void runner();
    
    long long getDataReceived();
    
private:
    PacketReceiver();
    
    fd_set activeFds;
    uint8_t *receiveBuffer;
    int receiveBufferLen;
    
    /**
     * Packet receiver from listed sockets
     */
    void receiver();
    
    std::set<std::shared_ptr< UDPSocket>,SocketComparator> socketList;
    std::mutex socketListMutex;
    
    long long dataReceived{0};
};
}

#endif	/* PACKETRECEIVER_H */

