/* 
 * File:   ApiStatus.h
 * Author: dipal
 *
 * Created on September 23, 2015, 4:17 PM
 */

#ifndef APISTATUS_H
#define	APISTATUS_H

#include "Types.h"
#include <string>


namespace imsdk {
class ApiStatus {
public:
    ApiStatus(std::string packetId, ChatError chatError = ChatError::NO_ERROR_IN_SDK);
    virtual ~ApiStatus();
    
    std::string getPacketId();
    ChatError getErrorCode();
    
private:
    std::string packetId;
    ChatError chatError;
};
}

#endif	/* APISTATUS_H */

