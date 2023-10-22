/* 
 * File:   RoomDTO.cpp
 * Author: towhid
 * 
 * Created on March 30, 2016, 4:50 PM
 */

#include "RoomDTO.h"

namespace imsdk {
RoomDTO::RoomDTO() {
}

RoomDTO::RoomDTO(std::string roomId, std::string roomFullName, std::string roomPictureUrl)
: roomId(roomId), roomFullName(roomFullName), roomPictureUrl(roomPictureUrl)
{
    
}

RoomDTO::~RoomDTO() {
}

void RoomDTO::setRoomPictureUrl(std::string roomPictureUrl) {
    this->roomPictureUrl = roomPictureUrl;
}

std::string RoomDTO::getRoomPictureUrl() const {
    return roomPictureUrl;
}

void RoomDTO::setRoomFullName(std::string roomFullName) {
    this->roomFullName = roomFullName;
}

std::string RoomDTO::getRoomFullName() const {
    return roomFullName;
}

void RoomDTO::setRoomId(std::string roomId) {
    this->roomId = roomId;
}

std::string RoomDTO::getRoomId() const {
    return roomId;
}

void RoomDTO::setRoomMessageList(std::vector<SDKMessageDTO> roomMessageList) {
    this->roomMessageList = roomMessageList;
}

std::vector<SDKMessageDTO> RoomDTO::getRoomMessageList() const {
    return roomMessageList;
}

void RoomDTO::setNumberOfMember(int numberOfMember) {
    this->numberOfMember = numberOfMember;
}

int RoomDTO::getNumberOfMember() const {
    return numberOfMember;
}

}