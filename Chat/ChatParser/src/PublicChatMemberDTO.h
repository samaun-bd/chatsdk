/* 
 * File:   PublicChatMemberDTO.h
 * Author: towhid
 *
 * Created on April 6, 2016, 12:45 PM
 */

#ifndef PUBLICCHATMEMBERDTO_H
#define	PUBLICCHATMEMBERDTO_H

#include "global.h"

#include <string>


namespace imsdk {
class PublicChatMemberDTO {
public:
    PublicChatMemberDTO();
    PublicChatMemberDTO(std::string fullName, std::string profileUrl, long long addedTime);
    ~PublicChatMemberDTO();

    void setAddedTime(long long addedTime);
    long long getAddedTime() const;
    void setProfileUrl(std::string profileUrl);
    std::string getProfileUrl() const;
    void setFullName(std::string fullName);
    std::string getFullName() const;
    void setMemberId(UserIdentity memberId);
    UserIdentity getMemberId() const;
    void setFakeId(UserIdentity originalUserId);
    UserIdentity getFakeId() const;
    void setRoomId(std::string roomId);
    std::string getRoomId() const;
    void setRingId(UserIdentity ringId);
    UserIdentity getRingId() const;

private:
    std::string roomId;
    UserIdentity memberId{0};
    UserIdentity fakeId{0};
    std::string fullName;
    std::string profileUrl;
    long long addedTime{0};       
    UserIdentity ringId{0};
};
}
#endif	/* PUBLICCHATMEMBERDTO_H */

