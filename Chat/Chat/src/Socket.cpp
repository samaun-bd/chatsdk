/* 
 * File:   Socket.cpp
 * Author: dipal
 * 
 * Created on August 23, 2015, 3:26 PM
 */

#include "Socket.h"
#ifdef __linux__
#include <bits/error_constants.h>
#endif
#include "Logger.h"
#include "generic/utils.h"
#define module "Socket"

namespace imsdk {
MsgBuffer::MsgBuffer() {
    m_pBuffer = NULL;
    m_iBufLen = 0;
}

MsgBuffer::MsgBuffer(const MsgBuffer &buf) {
    if (this != &buf)
        * this = buf;

}

MsgBuffer& MsgBuffer::operator=(const MsgBuffer &buf) {
    if (this != &buf) {
        m_DestIP = buf.m_DestIP;
        m_DestPort = buf.m_DestPort;
        m_pBuffer = buf.m_pBuffer;
        m_iBufLen = buf.m_iBufLen;
    }

    return *this;

}

int ISocket::m_iGlobalSendBufferUsage;
const int ISocket::m_iGlobalSendBufferMaxSize = 10 * 1024 * 1024;

inline int ISocket::_appendBuffer(const unsigned char *pBuffer, int iSize, const std::string& sIP, int iPort) {
    int result;

    int iSpaceRemainingInMsgBuffer = m_iSendBufferSize - m_iMsgBufferSize;

    

    if (iSize <= iSpaceRemainingInMsgBuffer) {
        MsgBuffer msg;

        msg.m_DestIP = sIP;
        msg.m_DestPort = iPort;

        msg.m_pBuffer = new unsigned char[iSize];
        memcpy(msg.m_pBuffer, pBuffer, iSize);
        msg.m_iBufLen = iSize;
        m_iMsgBufferSize += iSize;

        if (iSize > 0) {
            m_MsgBufferList.push_back(msg);
        }

        result = SOCK_WOULDBLOCK;
    } else if (((int) m_iGlobalSendBufferUsage + iSize) < m_iGlobalSendBufferMaxSize) {
        MsgBuffer msg;

        msg.m_DestIP = sIP;
        msg.m_DestPort = iPort;

        msg.m_pBuffer = new unsigned char[iSize];
        memcpy(msg.m_pBuffer, pBuffer, iSize);
        msg.m_iBufLen = iSize;
        m_iMsgBufferSize += iSize;
        if (iSpaceRemainingInMsgBuffer > 0) {
            m_iGlobalSendBufferUsage += (iSize - iSpaceRemainingInMsgBuffer);
        } else {
            m_iGlobalSendBufferUsage += iSize;
        }

        if (iSize > 0) {
            m_MsgBufferList.push_back(msg);
        }

        result = SOCK_WOULDBLOCK;
    } else {
        
        result = SOCK_ERR;
    }
    
    return result;

}

inline void ISocket::_ReduceMsgBufferSize(int iSize) {
    int iMsgBufferOverflow = m_iMsgBufferSize - m_iSendBufferSize;

    m_iMsgBufferSize -= iSize;
    if (iMsgBufferOverflow > 0) {
        if (iMsgBufferOverflow > iSize) {
            m_iGlobalSendBufferUsage -= iSize;
        } else {
            m_iGlobalSendBufferUsage -= iMsgBufferOverflow;
        }
    }
}


int ISocket::m_iSendBufferSize = 10 * 1024;



void ISocket::SetSendBufferSize(int iSize) {
    if (iSize > 0) {
        m_iSendBufferSize = iSize;
    } else {
        
        
    }
} 

UDPSocket::UDPSocket() {
#ifdef _WIN32
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    m_socketfd = -1;

    m_iMsgBufferSize = 0;
    m_MsgBufferList.clear();
    
    createSocket();
}

UDPSocket::~UDPSocket() {
    close();
    Log(module, "Socket closed. fd "<<m_socketfd);
}

#ifdef __APPLE__
int UDPSocket::createSocket() {

	int on, flags;
	int cnt = 2;
	int status = 0;
	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;
	if ((status = getaddrinfo(nullptr, "0", &hints, &res)) != 0)
	{
		// Log("socket", "DS getaddrinfo failed. error: " << gai_strerror(status));
		return -1;
	}
	// Log("socket", "DS addr list (for localhost):\n" << ip_addr_to_str(res));
	while (cnt-- && ((m_socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) >= 0))
	{
        ipvcore::generic::utills::sleep(50);
	}
	if (m_socketfd < 0)
	{
		freeaddrinfo(res);
		return -1;
	}
#ifdef __APPLE__
	int nosigpipe = 1;
	setsockopt(m_socketfd, SOL_SOCKET, SO_NOSIGPIPE, &nosigpipe, sizeof(nosigpipe));
#endif

	struct linger l;
	l.l_onoff = 1;
	l.l_linger = 0;
#if defined(WIN32) || defined(_WIN32_WCE)
	int no = 0;
	if (setsockopt(m_socketfd, IPPROTO_IPV6, IPV6_V6ONLY, (char *)&no, sizeof(no)) != 0)
	{
		freeaddrinfo(res);
		return -3;
	}
	if (setsockopt(m_socketfd, SOL_SOCKET, SO_LINGER, (char*)&l, sizeof(struct linger)) != 0)
	{
		freeaddrinfo(res);
		return -3;
	}
	u_long flag = 1;
	if (ioctlsocket(m_socketfd, FIONBIO, &flag) == -1)
	{
		freeaddrinfo(res);
		return false;
	}
	else
	{
		freeaddrinfo(res);
		return true;
	}
#else
	int no = 0;
	if (setsockopt(m_socketfd, IPPROTO_IPV6, IPV6_V6ONLY, &no, sizeof(no)) != 0)
	{
		freeaddrinfo(res);
		return -3;
	}
	if (setsockopt(m_socketfd, SOL_SOCKET, SO_LINGER, &l, sizeof(struct linger)) != 0)
	{
		freeaddrinfo(res);
		return -3;
	}
	// TODO: forcefully disable IPV6_ONLY by setsockopt(). To make sure dual stack is enabled.
	flags = fcntl(m_socketfd, F_GETFL, 0);
	flags |= O_NONBLOCK | O_NDELAY;
	if (fcntl(m_socketfd, F_SETFL, flags) == -1)
	{
		freeaddrinfo(res);
		return -4;
	}
#endif
	// TODO: loop through all the addresses returned by getaddrinfo() until success.
	if (::bind(m_socketfd, res->ai_addr, res->ai_addrlen)) {
		// Log("socket","DS could not BIND");
		freeaddrinfo(res);
		return -5;
	}
	freeaddrinfo(res);
	return SOCK_OK;
} //  __APPLE__

#else
int UDPSocket::createSocket() {
    int flags;

    m_socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    Log(module, "Socket created. fd "<<m_socketfd);
    if (m_socketfd < 0)
        return -1;

#ifdef __APPLE__
    int nosigpipe = 1;
    setsockopt(m_socketfd, SOL_SOCKET, SO_NOSIGPIPE, &nosigpipe, sizeof(nosigpipe));
#endif

    
    struct linger l;

    l.l_onoff = 1;
    l.l_linger = 0;
#if defined(_WIN32) || defined(_WIN32_WCE)
    if (setsockopt(m_socketfd, SOL_SOCKET, SO_LINGER, (char*)&l, sizeof (struct linger)) != 0)
        return -3;
	
    u_long flag = 1;
    if (ioctlsocket(m_socketfd, FIONBIO, &flag) == -1)
    {
        return false;
    }
    else return true;
#else
    if (setsockopt(m_socketfd, SOL_SOCKET, SO_LINGER, &l, sizeof (struct linger)) != 0)
        return -3;
    flags = fcntl(m_socketfd, F_GETFL, 0);
    flags |= O_NONBLOCK | O_NDELAY;

    if (fcntl(m_socketfd, F_SETFL, flags) == -1)
        return -4;
#endif

    struct sockaddr_in sin;

    memset((char*)&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(0);
    sin.sin_addr.s_addr = INADDR_ANY;

    if(::bind(m_socketfd, (struct sockaddr *)&sin, sizeof(sin))) {
        Log(module, "Socket bind error. fd:"<<m_socketfd);
        return -5;
    }

    return SOCK_OK;

}
#endif

#ifdef __APPLE__

int UDPSocket::sendTo(const unsigned char *buffer, int len, const std::string& ip_address, int port) {
	int sent;
	if (m_socketfd == -1) {
		return -5;
	}
	int status = 0;
	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_DGRAM;
	//  hints.ai_flags = AI_NUMERICHOST;

#ifdef __ANDROID__
	std::string remote_addr = "::FFFF:" + addr;

#else
	hints.ai_flags = AI_V4MAPPED;
	std::string remote_addr = ip_address;
#endif
	if ((status = getaddrinfo(remote_addr.c_str(), std::to_string(port).c_str(), &hints, &res)) != 0)
	{
		// Log("socket", "DS getaddrinfo failed. error: " << gai_strerror(status) << " addr: " << ip_address << " port: " << utils::intToString(port));
		return -1;
	}

	if (m_MsgBufferList.empty() == false)
		sendBufferedIPV6();

	// Log("socket", "DS addr list (for " << addr << "):\n" << ip_addr_to_str(res));
	// TODO: loop through all the addresses returned by getaddrinfo() until data is successfully sent.
#if defined(WIN32) || defined(_WIN32_WCE)
	sent = ::sendto(m_socketfd, (char*)buffer, len, MSG_DONTWAIT, res->ai_addr, res->ai_addrlen);
#else
	sent = ::sendto(m_socketfd, buffer, len, MSG_DONTWAIT, res->ai_addr, res->ai_addrlen);
#endif
	if (sent <= 0) {
		if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
			sent = _appendBuffer(buffer, len, ip_address, port);
			if (sent == SOCK_ERR) {
				//Log(module, "Socket ERROR:");
			}
		}
		else {
			sent = SOCK_ERR;
		}
	}
	else {
		socketDataSent += sent;
		sent = SOCK_OK;
	}
	freeaddrinfo(res);
	return sent;

}

#else
int UDPSocket::sendTo(ByteArray &data, const std::string& addr, int port) {
    return sendTo(data.getDataPtr(), (const int) data.size(), addr, port);
}

int UDPSocket::sendTo(const unsigned char *pBuffer, int iBufferSize, const std::string& addr, int port) {
    struct sockaddr_in toaddr;
    struct sockaddr *pToaddr;
    socklen_t tolen;
    int sent;

    if (m_socketfd == -1) {
        return SOCK_ERR;
    }

    sendMutex.lock();
    
    memset(&toaddr, 0, sizeof (toaddr));
    toaddr.sin_family = AF_INET;
    toaddr.sin_addr.s_addr = inet_addr(addr.c_str());
    toaddr.sin_port = htons(port);
    tolen = sizeof (toaddr);

    pToaddr = (struct sockaddr*) &toaddr;

    if (m_MsgBufferList.empty() == false)
        sendBuffered();

#if defined(_WIN32) || defined(_WIN32_WCE)
    sent = ::sendto(m_socketfd, (char*)pBuffer, iBufferSize, MSG_DONTWAIT, pToaddr, tolen);
#else
    sent = ::sendto(m_socketfd, pBuffer, iBufferSize, MSG_DONTWAIT, pToaddr, tolen);
#endif
    if (sent <= 0) {
        if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
            sent = _appendBuffer(pBuffer, iBufferSize, addr, port);
            if (sent == SOCK_ERR) {
                
            }
        } else {
            
            sent = SOCK_ERR;
        }
    } else {
        socketDataSent += sent;
        sent = SOCK_OK;
    }

    sendMutex.unlock();

    return sent;

}
#endif
int UDPSocket::sendBuffered() {
    if (m_socketfd == -1) {
        return SOCK_ERR;
    }

    int sent = SOCK_OK;
    int i;
    MsgBufferList::iterator iter;

    iter = m_MsgBufferList.begin();
    for (i = 0; i < (int) m_MsgBufferList.size(); i++) {
        struct sockaddr_in toaddr;
        struct sockaddr *pToaddr;
        socklen_t tolen;

        memset(&toaddr, 0, sizeof (toaddr));
        toaddr.sin_family = AF_INET;
        toaddr.sin_addr.s_addr = inet_addr(iter->m_DestIP.c_str());
        toaddr.sin_port = htons(iter->m_DestPort);
        tolen = sizeof (toaddr);

        pToaddr = (struct sockaddr*) &toaddr;
#if defined(_WIN32) || defined(_WIN32_WCE)
        sent = ::sendto(m_socketfd, (char*)iter->m_pBuffer, iter->m_iBufLen, MSG_DONTWAIT, pToaddr, tolen);
#else
        sent = ::sendto(m_socketfd, iter->m_pBuffer, iter->m_iBufLen, MSG_DONTWAIT, pToaddr, tolen);
#endif
        if (sent <= 0) {
            if ((errno != EAGAIN)&&(errno != EWOULDBLOCK)) {
                

                delete[] iter->m_pBuffer;
                _ReduceMsgBufferSize(iter->m_iBufLen);

                iter = m_MsgBufferList.erase(iter);
            }

            iter++;

            sent = SOCK_ERR;
        } else {
            delete[] iter->m_pBuffer;
            _ReduceMsgBufferSize(iter->m_iBufLen);

            iter = m_MsgBufferList.erase(iter);
            sent = SOCK_OK;
        }

    }

    
    return sent;

}

int UDPSocket::sendBufferedIPV6() {
	if (m_socketfd == -1) {
		return SOCK_ERR;
	}
	int status = 0;
	int sent = SOCK_OK;
	int i;
	MsgBufferList::iterator iter;
	
	iter = m_MsgBufferList.begin();
	for (i = 0; i < (int)m_MsgBufferList.size(); i++) {
		struct addrinfo hints, *res;
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET6;
		hints.ai_socktype = SOCK_DGRAM;
		//  hints.ai_flags = AI_NUMERICHOST;

#ifdef __ANDROID__
		std::string remote_addr = "::FFFF:" + ipvcore::generic::utills::to_string(res->ai_addr);

#else
		hints.ai_flags = AI_V4MAPPED;
		std::string remote_addr = iter->m_DestIP.c_str();
#endif
		if ((status = getaddrinfo(remote_addr.c_str(), ipvcore::generic::utills::to_string(iter->m_DestPort).c_str(), &hints, &res)) != 0)
		{
			// Log("socket", "DS getaddrinfo failed. error: " << gai_strerror(status) << " addr: " << iter->m_DestIP << " port: ");
			
			return -1;
	}
		// Log("socket", "DS addr list (for " << addr << "):\n" << ip_addr_to_str(res));
		// TODO: loop through all the addresses returned by getaddrinfo() until data is successfully sent.
#if defined(WIN32) || defined(_WIN32_WCE)
		sent = ::sendto(m_socketfd, (char*)iter->m_pBuffer, iter->m_iBufLen, MSG_DONTWAIT, res->ai_addr, res->ai_addrlen);
#else
		sent = ::sendto(m_socketfd, iter->m_pBuffer, iter->m_iBufLen, MSG_DONTWAIT, res->ai_addr, res->ai_addrlen);
#endif
		if (sent <= 0) {
			if ((errno != EAGAIN) && (errno != EWOULDBLOCK)) {


				delete[] iter->m_pBuffer;
				_ReduceMsgBufferSize(iter->m_iBufLen);

				iter = m_MsgBufferList.erase(iter);
			}

			iter++;

			sent = SOCK_ERR;
		}
		else {
			delete[] iter->m_pBuffer;
			_ReduceMsgBufferSize(iter->m_iBufLen);

			iter = m_MsgBufferList.erase(iter);
			sent = SOCK_OK;
}
		freeaddrinfo(res);
	}


	return sent;

}


#ifdef __APPLE__

int UDPSocket::recvFrom(unsigned char *buffer, int len, std::string& ip_address, int& port) {
	struct sockaddr_storage fromaddr;
	socklen_t fromlen = sizeof(fromaddr);
	int read;
	char szInAddr[INET6_ADDRSTRLEN];
	if (m_socketfd == -1) {
		return -5;
	}
#if defined(WIN32) || defined(_WIN32_WCE)
	read = ::recvfrom(m_socketfd, (char*)buffer, len, 0, (struct sockaddr*) &fromaddr, &fromlen);
#else
	read = ::recvfrom(m_socketfd, buffer, len, 0, (struct sockaddr*) &fromaddr, &fromlen);
#endif
	if (read < 0) {
		read = -5;
	}
	else {
#ifndef WINDOWS_PHONE_8
		if (AF_INET == fromaddr.ss_family) {

			if (inet_ntop(fromaddr.ss_family, &((sockaddr_in *)&fromaddr)->sin_addr, szInAddr, INET_ADDRSTRLEN) == NULL) {
				szInAddr[0] = '\0';
			}
			port = ntohs(((sockaddr_in *)&fromaddr)->sin_port);
		}
		else {
			if (inet_ntop(fromaddr.ss_family, &((sockaddr_in6 *)&fromaddr)->sin6_addr, szInAddr, INET6_ADDRSTRLEN) == NULL) {
				szInAddr[0] = '\0';
			}
			port = ntohs(((sockaddr_in6 *)&fromaddr)->sin6_port);
		}
#endif
		ip_address = (std::string) szInAddr;
	}
	return read;

}
#else
int UDPSocket::recvFrom(unsigned char *pBuf, int iBufLen, std::string &addr, int &port) {
    struct sockaddr_in fromaddr;
    socklen_t fromlen = sizeof (fromaddr);
    in_addr a;
    int read;
    char szInAddr[INET_ADDRSTRLEN];

    if (m_socketfd == -1) {
        return SOCK_ERR;
    }
#if defined(_WIN32) || defined(_WIN32_WCE)
    read = ::recvfrom(m_socketfd, (char*)pBuf, iBufLen, 0, (struct sockaddr*) &fromaddr, &fromlen);
#else
    read = ::recvfrom(m_socketfd, pBuf, iBufLen, 0, (struct sockaddr*) &fromaddr, &fromlen);
#endif
    if (read < 0) {
        int iErrno = errno;
        if (iErrno != EAGAIN) {
            
        }
        read = SOCK_ERR;
    } else {
        a = fromaddr.sin_addr;
        port = ntohs(fromaddr.sin_port);

#ifndef WINDOWS_PHONE_8
        if (inet_ntop(AF_INET, &a, szInAddr, sizeof (szInAddr)) == NULL) {
            szInAddr[0] = '\0';
        }
#endif
        addr = (std::string) szInAddr;
    }

    return read;

}

#endif

int UDPSocket::close() {
    if (m_socketfd != -1) {
#if defined(_WIN32) || defined(_WIN32_WCE)
    while (::closesocket(m_socketfd) != 0) {
        if (errno != EINTR) break;
    }
#else
    while (::close(m_socketfd) != 0) {
        if (errno != EINTR) break;
    }
#endif
    }

    MsgBufferList::iterator iter;

    for (iter = m_MsgBufferList.begin(); iter != m_MsgBufferList.end(); iter++) {
        if (iter->m_pBuffer != NULL)
            delete[] iter->m_pBuffer;
    }

    m_MsgBufferList.clear();

    _ReduceMsgBufferSize(m_iMsgBufferSize);
    return 0;
}

int UDPSocket::getFd() {
    return m_socketfd;
}

long long UDPSocket::getSocketDataSent(){
    long long dataSent = socketDataSent;
    socketDataSent = 0;
    return dataSent;
}

void UDPSocket::setToBeClosed(bool toBeClosed) {
    this->toBeClosed = toBeClosed;
}

bool UDPSocket::isToBeClosed() const {
    return toBeClosed;
}

}
