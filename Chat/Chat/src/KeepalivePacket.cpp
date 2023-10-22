/* 
 * File:   KeepalivePacket.cpp
 * Author: dipal
 * 
 * Created on August 23, 2015, 5:52 PM
 */

#include "KeepalivePacket.h"

namespace imsdk {
KeepalivePacket::KeepalivePacket() {
}

KeepalivePacket::KeepalivePacket(std::shared_ptr< ChatConnection> connection, std::shared_ptr< ByteArray> keepAliveData)
    : connection(connection), keepAliveData(keepAliveData)
{
    
}

KeepalivePacket::~KeepalivePacket() {
}

int KeepalivePacket::getIdleTimes()
{
    return consecutiveKeepalive;
}

void KeepalivePacket::increaseKeepAliveCounter()
{
    consecutiveKeepalive++;
}

void KeepalivePacket::resetTimer(int value)
{
    consecutiveKeepalive=value;
}

int KeepalivePacket::sendKeepalive()
{
    consecutiveKeepalive++;
    
    if (connection)
    {
        return connection->sendToChatServer(keepAliveData);
    }
    
    return -1;
}

std::shared_ptr< ChatConnection> KeepalivePacket::getConnection()
{
    return connection;
}

}
