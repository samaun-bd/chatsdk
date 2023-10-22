/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GroupActivityDTO.cpp
 * Author: noman
 * 
 * Created on January 25, 2016, 12:51 PM
 */

#include "GroupActivityDTO.h"

namespace imsdk {
GroupActivityDTO::GroupActivityDTO() {
}

GroupActivityDTO::~GroupActivityDTO() {
}

void GroupActivityDTO::setUpdateTime(long long updateTime) {
    this->updateTime = updateTime;
}

long long GroupActivityDTO::getUpdateTime() const{
    return updateTime;
}

void GroupActivityDTO::setChangedByUserId(UserIdentity changedByUserId) {
    this->changedByUserId = changedByUserId;
}

UserIdentity GroupActivityDTO::getChangedByUserId() const{
    return changedByUserId;
}

void GroupActivityDTO::setMemberType(int memberType) {
    this->memberType = memberType;
}

int GroupActivityDTO::getMemberType() const{
    return memberType;
}

void GroupActivityDTO::setGroupNameOrUrlString(std::string groupNameOrUrlString) {
    this->groupNameOrUrlString = groupNameOrUrlString;
}

std::string GroupActivityDTO::getGroupNameOrUrlString() const{
    return groupNameOrUrlString;
}

void GroupActivityDTO::setMemberIdentity(UserIdentity memberIdentity) {
    this->memberIdentity = memberIdentity;
}

UserIdentity GroupActivityDTO::getMemberIdentity() const{
    return memberIdentity;
}

void GroupActivityDTO::setActivityType(int activityType) {
    this->activityType = activityType;
}

int GroupActivityDTO::getActivityType() const{
    return activityType;
}

void GroupActivityDTO::setGroupId(long long groupId) {
    this->groupId = groupId;
}

long long GroupActivityDTO::getGroupId() const {
    return groupId;
}

void GroupActivityDTO::setPacketId(std::string packetId) {
    this->packetId = packetId;
}

std::string GroupActivityDTO::getPacketId() const {
    return packetId;
}

void GroupActivityDTO::setRingId(UserIdentity ringId) {
    this->ringId = ringId;
}

UserIdentity GroupActivityDTO::getRingId() const {
    return ringId;
}
}
