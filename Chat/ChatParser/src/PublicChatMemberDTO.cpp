/* 
 * File:   PublicChatMemberDTO.h
 * Author: towhid
 *
 * Created on April 6, 2016, 12:45 PM
 */

#include "PublicChatMemberDTO.h"

namespace imsdk {

PublicChatMemberDTO::PublicChatMemberDTO() {

}

PublicChatMemberDTO::PublicChatMemberDTO(std::string fullName, std::string profileUrl, long long addedTime) {
    this->fullName = fullName;
    this->profileUrl = profileUrl;
    this->addedTime = addedTime;
}

PublicChatMemberDTO::~PublicChatMemberDTO(){

}

void PublicChatMemberDTO::setAddedTime(long long addedTime) {
    this->addedTime = addedTime;
}

long long PublicChatMemberDTO::getAddedTime() const {
    return addedTime;
}

void PublicChatMemberDTO::setProfileUrl(std::string profileUrl) {
    this->profileUrl = profileUrl;
}

std::string PublicChatMemberDTO::getProfileUrl() const {
    return profileUrl;
}

void PublicChatMemberDTO::setFullName(std::string fullName) {
    this->fullName = fullName;
}

std::string PublicChatMemberDTO::getFullName() const {
    return fullName;
}

void PublicChatMemberDTO::setMemberId(UserIdentity memberId) {
    this->memberId = memberId;
}

UserIdentity PublicChatMemberDTO::getMemberId() const {
    return memberId;
}

void PublicChatMemberDTO::setFakeId(UserIdentity fakeId) {
    this->fakeId = fakeId;
}

UserIdentity PublicChatMemberDTO::getFakeId() const {
    return fakeId;
}

void PublicChatMemberDTO::setRoomId(std::string roomId) {
    this->roomId = roomId;
}

std::string PublicChatMemberDTO::getRoomId() const {
    return roomId;
}

void PublicChatMemberDTO::setRingId(UserIdentity ringId) {
    this->ringId = ringId;
}

UserIdentity PublicChatMemberDTO::getRingId() const {
    return ringId;
}

}
