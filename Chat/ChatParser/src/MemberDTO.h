/* 
 * File:   MemberDTO.h
 * Author: dipal
 *
 * Created on September 11, 2015, 5:53 PM
 */

#ifndef MEMBERDTO_H
#define	MEMBERDTO_H

#include "global.h"

#include <string>


namespace imsdk {

class MemberDTO {
public:
    MemberDTO();
    MemberDTO(UserIdentity memberId, UserIdentity ringId, std::string fullName, int status, UserIdentity addedBy);
    virtual ~MemberDTO();
    void setAddedBy(UserIdentity addedBy);
    UserIdentity getAddedBy() const;
    void setStatus(int status);
    int getStatus() const;
    void setFullName(std::string fullName);
    std::string getFullName() const;
    void setMemberIdentity(UserIdentity memberIdentity);
    UserIdentity getMemberIdentity() const;
    void setSeenTime(long long seenTime);
    long long getSeenTime() const;
    void setRingId(UserIdentity ringId);
    UserIdentity getRingId() const;
    
private:
    UserIdentity memberIdentity{0};
    UserIdentity ringId{0};
    std::string fullName;
    int status{0};
    UserIdentity addedBy{0};
    long long seenTime{0};
};
}

#endif	/* MEMBERDTO_H */

