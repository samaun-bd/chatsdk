/* 
 * File:   FriendStatus.h
 * Author: towhid
 *
 * Created on March 19, 2016, 1:12 AM
 */

#ifndef FRIENDSTATUS_H
#define	FRIENDSTATUS_H

#include <string>


namespace imsdk{
    class FriendInformation{
    public:
        FriendInformation(std::string registerServerAddress, int registerServerPort, int chatServerPort, int deviceType, int status, int mood, bool blockStatus, std::string friendName, std::string friendUrl, int profileType);
        virtual ~FriendInformation();
        
        std::string getFriendRegisterServerAddress();
        int getFriendRegisterServerPort();
        int getFriendChatServerPort();
        bool getBlockStatus();
        int getFriendStatus();
        int getFriendMood();
        int getFriendDeviceType();
        std::string getFriendUrl() const;
        std::string getFriendName() const;
        int getProfileType() const;
        
    private:
        
        std::string friendRegisterServerAddress;
        int friendRegisterServerPort;
        int friendChatServerPort;
        bool blockStatus;
        int friendStatus;
        int friendMood;
        int friendDeviceType;
        std::string friendName;
        std::string friendUrl;
        int profileType{0};
    };
}

#endif	/* FRIENDSTATUS_H */

