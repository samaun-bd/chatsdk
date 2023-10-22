/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConversationDTO.cpp
 * Author: noman
 * 
 * Created on October 19, 2016, 12:13 PM
 */

#include "ConversationDTO.h"

namespace imsdk {
ConversationDTO::ConversationDTO() {
}

ConversationDTO::ConversationDTO(int conversationType, UserIdentity friendId, GroupIdentity groupId) 
: conversationType(conversationType), friendId(friendId), groupId(groupId){
    
}

ConversationDTO::~ConversationDTO() {
}

void ConversationDTO::SetGroupId(GroupIdentity groupId) {
    this->groupId = groupId;
}

GroupIdentity ConversationDTO::GetGroupId() const {
    return groupId;
}

void ConversationDTO::SetFriendId(UserIdentity friendId) {
    this->friendId = friendId;
}

UserIdentity ConversationDTO::GetFriendId() const {
    return friendId;
}

void ConversationDTO::SetConversationType(int conversationType) {
    this->conversationType = conversationType;
}

int ConversationDTO::GetConversationType() const {
    return conversationType;
}
}

