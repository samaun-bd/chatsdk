/* 
 * File:   MessageDTO.h
 * Author: towhid
 *
 * Created on May 7, 2016, 2:35 PM
 */

#include "SDKMessageDTO.h"

namespace imsdk {
SDKMessageDTO::SDKMessageDTO() {
}

SDKMessageDTO::SDKMessageDTO(UserIdentity senderId, UserIdentity receiverId, GroupIdentity groupId, std::string packetId, int messageType, int timeOut, std::string message, long long messageDate, std::string memberFullName, std::string memberProfileUrl, bool isSecretVisible, int messageStatus, int direction, bool isEdited, int publicChatLikeCount, bool publicChatILike, bool publicChatIReport, int unreadCount) {
    this->senderId = senderId;
    this->receiverId = receiverId;
    this->groupId = groupId;
    this->packetId = packetId;
    this->messageType = messageType;
    this->timeOut = timeOut;
    this->message = message;
    this->messageDate = messageDate;
    this->memberFullName = memberFullName;
    this->memberProfileUrl = memberProfileUrl;
    this->isSecretVisible = isSecretVisible;
    this->messageStatus = messageStatus;
    this->direction = direction;
    this->isEdited = isEdited;
    this->publicChatLikeCount = publicChatLikeCount;
    this->publicChatILike = publicChatILike;
    this->publicChatIReport = publicChatIReport;
    this->unreadCount = unreadCount;
}

std::string SDKMessageDTO::getMemberFullName() const {
    return memberFullName;
}

void SDKMessageDTO::setMemberFullName(std::string memberFullName) {
    this->memberFullName = memberFullName;
}

std::string SDKMessageDTO::getMemberProfileUrl() const {
    return memberProfileUrl;
}

void SDKMessageDTO::setMemberProfileUrl(std::string memberProfileUrl) {
    this->memberProfileUrl = memberProfileUrl;
}

std::string SDKMessageDTO::getMessage() const {
    return message;
}

void SDKMessageDTO::setMessage(std::string message) {
    this->message = message;
}

long long SDKMessageDTO::getMessageDate() const {
    return messageDate;
}

void SDKMessageDTO::setMessageDate(long long messageDate) {
    this->messageDate = messageDate;
}

int SDKMessageDTO::getMessageType() const {
    return messageType;
}

void SDKMessageDTO::setMessageType(int messageType) {
    this->messageType = messageType;
}

std::string SDKMessageDTO::getPacketId() const {
    return packetId;
}

void SDKMessageDTO::setPacketId(std::string packetId) {
    this->packetId = packetId;
}

UserIdentity SDKMessageDTO::getSenderId() const{
    return senderId;
}
void SDKMessageDTO::setSenderId(UserIdentity senderId){
    this->senderId = senderId;
}

void SDKMessageDTO::setReceiverId(UserIdentity receiverId) {
    this->receiverId = receiverId;
}

UserIdentity SDKMessageDTO::getReceiverId() const {
    return receiverId;
}

void SDKMessageDTO::setDirection(int direction) {
    this->direction = direction;
}

int SDKMessageDTO::getDirection() const {
    return direction;
}

void SDKMessageDTO::setMessageStatus(int messageStatus) {
    this->messageStatus = messageStatus;
}

int SDKMessageDTO::getMessageStatus() const {
    return messageStatus;
}

void SDKMessageDTO::setSecretVisible(bool secretVisible) {
    isSecretVisible = secretVisible;
}

bool SDKMessageDTO::getIsSecretVisible() const {
    return isSecretVisible;
}

void SDKMessageDTO::setTimeOut(int timeOut) {
    this->timeOut = timeOut;
}

int SDKMessageDTO::getTimeOut() const {
    return timeOut;
}
void SDKMessageDTO::setIsEdited(bool isEdited){
    this->isEdited = isEdited;
}

bool SDKMessageDTO::getIsEdited() const{
    return isEdited;
}

void SDKMessageDTO::setPublicChatLikeCount(int publicChatLikeCount) {
    this->publicChatLikeCount = publicChatLikeCount;
}

int SDKMessageDTO::getPublicChatLikeCount() const {
    return publicChatLikeCount;
}

void SDKMessageDTO::setPublicChatILike(bool publicChatILike) {
    this->publicChatILike = publicChatILike;
}

bool SDKMessageDTO::isPublicChatILike() const {
    return publicChatILike;
}

void SDKMessageDTO::setPublicChatIReport(bool publicChatIReport) {
    this->publicChatIReport = publicChatIReport;
}

bool SDKMessageDTO::isPublicChatIReport() const {
    return publicChatIReport;
}

void SDKMessageDTO::setUnreadCount(int unreadCount) {
    this->unreadCount = unreadCount;
}

int SDKMessageDTO::getUnreadCount() const {
    return unreadCount;
}

void SDKMessageDTO::setGroupId(GroupIdentity groupId) {
    this->groupId = groupId;
}

GroupIdentity SDKMessageDTO::getGroupId() const {
    return groupId;
}
}

