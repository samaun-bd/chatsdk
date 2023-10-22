/* 
 * File:   RoomDTO.h
 * Author: towhid
 *
 * Created on March 30, 2016, 4:50 PM
 */

#ifndef ROOMDTO_H
#define	ROOMDTO_H

#include <string>

#include "SDKMessageDTO.h"


namespace imsdk {
class RoomDTO {
public:
    RoomDTO();
    RoomDTO(std::string roomId, std::string roomFullName, std::string roomPictureUrl);
    virtual ~RoomDTO();
    void setRoomPictureUrl(std::string roomPictureUrl);
    std::string getRoomPictureUrl() const;
    void setRoomFullName(std::string roomFullName);
    std::string getRoomFullName() const;
    void setRoomId(std::string roomId);
    std::string getRoomId() const;
    void setRoomMessageList(std::vector<SDKMessageDTO> roomMessageList);
    std::vector<SDKMessageDTO> getRoomMessageList() const;
    void setNumberOfMember(int numberOfMember);
    int getNumberOfMember() const;
private:
    std::string roomId;
    std::string roomFullName;
    std::string roomPictureUrl;
    int numberOfMember{0};
    std::vector <SDKMessageDTO> roomMessageList;
};

}
#endif	/* ROOMDTO_H */

