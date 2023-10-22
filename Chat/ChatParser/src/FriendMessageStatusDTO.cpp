/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FriendMessageStatusDTO.cpp
 * Author: noman
 * 
 * Created on January 25, 2016, 1:14 PM
 */

#include "FriendMessageStatusDTO.h"

namespace imsdk {
FriendMessageStatusDTO::FriendMessageStatusDTO() {
}

FriendMessageStatusDTO::~FriendMessageStatusDTO() {
}

void FriendMessageStatusDTO::setMessageStatus(int messageStatus) {
    this->messageStatus = messageStatus;
}

int FriendMessageStatusDTO::getMessageStatus() const{
    return messageStatus;
}

void FriendMessageStatusDTO::setUpdateDate(long long updateDate) {
    this->updateDate = updateDate;
}

long long FriendMessageStatusDTO::getUpdateDate() const{
    return updateDate;
}

void FriendMessageStatusDTO::setPacketId(std::string packetId) {
    this->packetId = packetId;
}

std::string FriendMessageStatusDTO::getPacketId() const{
    return packetId;
}
}
