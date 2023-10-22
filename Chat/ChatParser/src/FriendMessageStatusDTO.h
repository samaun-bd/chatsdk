/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FriendMessageStatusDTO.h
 * Author: noman
 *
 * Created on January 25, 2016, 1:14 PM
 */

#ifndef FRIENDMESSAGESTATUSDTO_H
#define FRIENDMESSAGESTATUSDTO_H

#include "global.h"

namespace imsdk {
class FriendMessageStatusDTO {
public:
    FriendMessageStatusDTO();
    virtual ~FriendMessageStatusDTO();
    void setMessageStatus(int messageStatus);
    int getMessageStatus() const;
    void setUpdateDate(long long updateDate);
    long long getUpdateDate() const;
    void setPacketId(std::string packetId);
    std::string getPacketId() const;
private:
    
    std::string packetId;
    long long updateDate{0};
    int messageStatus{0};
    
};
}

#endif /* FRIENDMESSAGESTATUSDTO_H */

