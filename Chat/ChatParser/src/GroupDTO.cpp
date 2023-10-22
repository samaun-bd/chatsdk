/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GroupDTO.cpp
 * Author: noman
 * 
 * Created on January 25, 2016, 12:52 PM
 */

#include "GroupDTO.h"

namespace imsdk {
GroupDTO::GroupDTO() {
}

GroupDTO::~GroupDTO() {
}

void GroupDTO::setCreatorId(UserIdentity creatorId) {
    this->creatorId = creatorId;
}

UserIdentity GroupDTO::getCreatorId() const{
    return creatorId;
}

void GroupDTO::setGroupUrl(std::string groupUrl) {
    this->groupUrl = groupUrl;
}

std::string GroupDTO::getGroupUrl() const{
    return groupUrl;
}

void GroupDTO::setGroupName(std::string groupName) {
    this->groupName = groupName;
}

std::string GroupDTO::getGroupName() const{
    return groupName;
}

void GroupDTO::setGroupId(long long groupId) {
    this->groupId = groupId;
}

long long GroupDTO::getGroupId() const{
    return groupId;
}

void GroupDTO::setNumberOfMembers(int numberOfMembers) {
    this->numberOfMembers = numberOfMembers;
}

int GroupDTO::getNumberOfMembers() const{
    return numberOfMembers;
}
}
