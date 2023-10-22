/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConversationDTO.h
 * Author: noman
 *
 * Created on October 19, 2016, 12:13 PM
 */

#ifndef CONVERSATIONDTO_H
#define CONVERSATIONDTO_H

#include "global.h"

namespace imsdk {
class ConversationDTO {
public:
    ConversationDTO();
    ConversationDTO(int conversationType, UserIdentity friendId, GroupIdentity groupId);
    virtual ~ConversationDTO();
    void SetGroupId(GroupIdentity groupId);
    GroupIdentity GetGroupId() const;
    void SetFriendId(UserIdentity friendId);
    UserIdentity GetFriendId() const;
    void SetConversationType(int conversationType);
    int GetConversationType() const;
private:
    int conversationType{0};
    UserIdentity friendId{0};
    GroupIdentity groupId{0};
};
}
#endif /* CONVERSATIONDTO_H */

