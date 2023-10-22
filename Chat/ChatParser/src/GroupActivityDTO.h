/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GroupActivityDTO.h
 * Author: noman
 *
 * Created on January 25, 2016, 12:50 PM
 */

#ifndef GROUPACTIVITYDTO_H
#define GROUPACTIVITYDTO_H

#include "global.h"

namespace imsdk {
class GroupActivityDTO {
public:
    GroupActivityDTO();
    virtual ~GroupActivityDTO();
    
    void setUpdateTime(long long updateTime);
    long long getUpdateTime()const;
    void setChangedByUserId(UserIdentity changedByUserId);
    UserIdentity getChangedByUserId()const;
    void setMemberType(int memberType);
    int getMemberType()const;
    void setGroupNameOrUrlString(std::string groupNameOrUrlString);
    std::string getGroupNameOrUrlString()const;
    void setMemberIdentity(UserIdentity memberIdentity);
    UserIdentity getMemberIdentity()const;
    void setActivityType(int activityType);
    int getActivityType()const;
    void setGroupId(long long groupId);
    long long getGroupId() const;
    void setPacketId(std::string packetId);
    std::string getPacketId() const;
    void setRingId(UserIdentity ringId);
    UserIdentity getRingId() const;

private:

    int activityType{0};
    long long groupId{0};
    UserIdentity memberIdentity{0};
    UserIdentity ringId{0};
    std::string groupNameOrUrlString;
    int memberType{0};
    UserIdentity changedByUserId{0};
    long long updateTime{0};
    std::string packetId;

};
}
#endif /* GROUPACTIVITYDTO_H */

