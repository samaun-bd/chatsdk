/* 
 * File:   ApiStatus.cpp
 * Author: dipal
 * 
 * Created on September 23, 2015, 4:17 PM
 */

#include "ApiStatus.h"

namespace imsdk {
ApiStatus::ApiStatus(std::string packetId, ChatError chatError) : packetId(packetId), chatError(chatError) {
    
}

ApiStatus::~ApiStatus() {
}


std::string ApiStatus::getPacketId()
{
    return packetId;
}

ChatError ApiStatus::getErrorCode()
{
    return chatError;
}
}
