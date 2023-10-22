/* 
 * File:   Socket.h
 * Author: dipal
 *
 * Created on August 23, 2015, 3:26 PM
 */

#ifndef SOCKET_H
#define	SOCKET_H

#include <list>
#include <string>
#include <iostream>
#include "ByteArray.h"
#include "DataCounter.h"
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <mutex>
#include <ws2tcpip.h>
#include <winsock2.h> //can also be winsock.h
// Need to link with Ws2_32.lib
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
#include <mutex>

#ifndef __APPLE__
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#endif


typedef int SOCKET;
#endif

#ifndef MSG_DONTWAIT
#define MSG_DONTWAIT 0
#endif // !MSG_DONTWAIT

#define SOCK_OK                  0

#define SOCK_INVALID_PARAMETERS -1
#define SOCK_NOT_IMPLEMENTED    -2
#define SOCK_CLOSED             -3
#define SOCK_NO_BUFFER          -4
#define SOCK_ERR                -5
#define SOCK_WOULDBLOCK         -6

namespace imsdk {
class MsgBuffer {
public:
    std::string m_DestIP;
    short m_DestPort;
    unsigned char *m_pBuffer;
    int m_iBufLen;

public:

    MsgBuffer();

    MsgBuffer(const MsgBuffer &buf);

    MsgBuffer& operator=(const MsgBuffer &buf);

};

typedef std::list<MsgBuffer> MsgBufferList;

class ISocket {
protected:
    MsgBufferList m_MsgBufferList;
    unsigned int m_iMsgBufferSize;

    virtual int _appendBuffer(const unsigned char *pBuffer, int iSize, const std::string& sIP, int iPort);
    void _ReduceMsgBufferSize(int iSize);

public:
    virtual ~ISocket() = default;
    virtual int sendBuffered() = 0;
    virtual int recvFrom(unsigned char *pBuf, int iBufLen, std::string &addr, int &port) = 0;
    //virtual int send(const unsigned char *pBuffer, int iBufferSize);
    virtual int close() = 0;
    virtual int getFd() = 0;

protected:
    static int m_iSendBufferSize;

public:
    //Set Send Buffer Size. Default 10 KB
    static void SetSendBufferSize(int iSize);

private:
    static int m_iGlobalSendBufferUsage;
    const static int m_iGlobalSendBufferMaxSize;
    
    virtual int sendTo(const unsigned char *pBuffer, int iBufferSize, const std::string& addr, int port) = 0;
};

class UDPSocket : public ISocket {
private:
    int m_socketfd;
    std::string m_AddrBuffer;
    int m_PortBuffer;
    
    int createSocket();
    long long socketDataSent{0};
    bool toBeClosed{false};
    
public:
    UDPSocket();
    virtual ~UDPSocket();

    //if you need to remove coupling with ByteArray class, just remove this function
    int sendTo(ByteArray &data, const std::string& addr, int port);
    int sendTo(const unsigned char *pBuffer, int iBufferSize, const std::string& addr, int port);
    int sendBuffered();
	int sendBufferedIPV6();

    //! received data from socket and copy senders address and port to parameters
    int recvFrom(unsigned char *pBuf, int iBufLen, std::string& addr, int &port);

    int close();
    int getFd();
    
    long long getSocketDataSent();
    void setToBeClosed(bool toBeClosed);
    bool isToBeClosed() const;    
    std::mutex sendMutex;
};

}

#endif	/* SOCKET_H */

