/* 
 * File:   KeepalivePacket.h
 * Author: dipal
 *
 * Created on August 23, 2015, 5:52 PM
 */

#ifndef KEEPALIVEPACKET_H
#define	KEEPALIVEPACKET_H

#include "Connection.h"

namespace imsdk {
class KeepalivePacket {
public:
    KeepalivePacket();
    KeepalivePacket(std::shared_ptr< ChatConnection> connection, std::shared_ptr< ByteArray> keepAliveData);
    virtual ~KeepalivePacket();
    
    int getIdleTimes();
    void resetTimer(int value=0);
    int sendKeepalive();
    void increaseKeepAliveCounter();
    std::shared_ptr< ChatConnection> getConnection();
private:
    int consecutiveKeepalive{0};
    std::shared_ptr< ChatConnection> connection{nullptr};
    std::shared_ptr< ByteArray> keepAliveData{nullptr};
};
}

#endif	/* KEEPALIVEPACKET_H */

