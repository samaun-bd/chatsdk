/* 
 * File:   FriendStatus.h
 * Author: towhid
 *
 * Created on March 19, 2016, 1:12 AM
 */

#include "FriendInformation.h"

namespace imsdk{
    
    FriendInformation::FriendInformation(
            std::string registerServerAddress,
            int registerServerPort,
            int chatServerPort,
            int deviceType,
            int status,
            int mood,
            bool blockStatus,
            std::string friendName,
            std::string friendUrl,
            int profileType)
    :
            friendRegisterServerAddress(registerServerAddress),
            friendRegisterServerPort(registerServerPort),
            friendChatServerPort(chatServerPort),
            blockStatus(blockStatus),
            friendStatus(status),
            friendMood(mood),
            friendDeviceType(deviceType),
            friendName(friendName),
            friendUrl(friendUrl),
            profileType(profileType)
    {
    }
    
    FriendInformation::~FriendInformation(){
        
    }
    
    std::string FriendInformation::getFriendRegisterServerAddress(){
        return friendRegisterServerAddress;
    }
    
    int FriendInformation::getFriendRegisterServerPort(){
        return friendRegisterServerPort;
    }
    
    int FriendInformation::getFriendChatServerPort(){
        return friendChatServerPort;
    }
    
    bool FriendInformation::getBlockStatus(){
        return blockStatus;
    }

    int FriendInformation::getFriendStatus(){
        return friendStatus;
    }

    int FriendInformation::getFriendMood(){
        return friendMood;
    }
    
    int FriendInformation::getFriendDeviceType(){
        return friendDeviceType;
    }

    std::string FriendInformation::getFriendUrl() const {
        return friendUrl;
    }

    std::string FriendInformation::getFriendName() const {
        return friendName;
    }

    int FriendInformation::getProfileType() const {
        return profileType;
    }
}
