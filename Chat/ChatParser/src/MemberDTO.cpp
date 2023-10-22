/* 
 * File:   MemberDTO.cpp
 * Author: dipal
 * 
 * Created on September 11, 2015, 5:53 PM
 */

#include "MemberDTO.h"

namespace imsdk {
MemberDTO::MemberDTO() {
}

MemberDTO::MemberDTO(UserIdentity memberId, UserIdentity ringId, std::string fullName, int status, UserIdentity addedBy) {
    this->memberIdentity = memberId;
    this->ringId = ringId;
    this->fullName = fullName;
    this->status = status;
    this->addedBy = addedBy;
}

MemberDTO::~MemberDTO() {
}

void MemberDTO::setAddedBy(UserIdentity addedBy) {
    this->addedBy = addedBy;
}

UserIdentity MemberDTO::getAddedBy() const {
    return addedBy;
}

void MemberDTO::setStatus(int status) {
    this->status = status;
}

int MemberDTO::getStatus() const {
    return status;
}

void MemberDTO::setFullName(std::string fullName) {
    this->fullName = fullName;
}

std::string MemberDTO::getFullName() const {
    return fullName;
}

void MemberDTO::setMemberIdentity(UserIdentity memberIdentity) {
    this->memberIdentity = memberIdentity;
}

UserIdentity MemberDTO::getMemberIdentity() const {
    return memberIdentity;
}

void MemberDTO::setSeenTime(long long seenTime) {
    this->seenTime = seenTime;
}

long long MemberDTO::getSeenTime() const {
    return seenTime;
}

void MemberDTO::setRingId(UserIdentity ringId) {
    this->ringId = ringId;
}

UserIdentity MemberDTO::getRingId() const {
    return ringId;
}

}
