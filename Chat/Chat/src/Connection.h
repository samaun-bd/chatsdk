/* 
 * File:   Connection.h
 * Author: dipal
 *
 * Created on August 23, 2015, 4:45 PM
 */

#ifndef CONNECTION_H
#define	CONNECTION_H

#include "Socket.h"
#include "Types.h"
#include "ByteArray.h"
#include <memory>
#include <mutex>

/**
 * Chat Connection will contain the sockets. It is concerened about PacketReceiver and it will register sockets 
 * to the packet receiver
 * @param chatRegisterAddress
 * @param chatRegisterPort
 * @param offlineServerAddress
 * @param offlineServerPort
 */

namespace imsdk {
class ChatConnection {
public:
    enum ChatServerStatus {
        NOT_EXISTS,
        PROCESSING,
        READY
    };
    
    ChatConnection(std::shared_ptr< UDPSocket> socket);
    void setRegisterServer(std::string registerServerAddress, int registerServerPort);
    std::string getRegisterServerAddress();
    void setChatServerPort(int chatServerPort);
    void setOfflineServer(std::string offlineServerAddress, int offlineServerPort);
    
    int sendToRegisterServer(std::shared_ptr< ByteArray> &registerPacket);
    int sendToChatServer(std::shared_ptr< ByteArray> &chatPacket);
    int sendToOfflineServer(std::shared_ptr< ByteArray> &offlinePacket);
    
    void setChatServerStatus(ChatServerStatus chatServerStatus);
    ChatServerStatus getChatServerStatus();
    
    int getRegisterServerPort();
    int getChatServerPort();
    
    virtual ~ChatConnection();
    
private:
    
    std::shared_ptr< UDPSocket> udpSocket{nullptr};
    
    std::string registerServerAddress;
    int registerServerPort{-1};
    std::string chatServerAddress;
    int chatServerPort{-1};
    std::string offlineServerAddress;
    int offlineServerPort{-1};
    
    ChatServerStatus chatServerStatus;
};
}

#endif	/* CONNECTION_H */

