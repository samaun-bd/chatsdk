/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GroupDTO.h
 * Author: noman
 *
 * Created on January 25, 2016, 12:52 PM
 */

#ifndef GROUPDTO_H
#define GROUPDTO_H

#include "global.h"

namespace imsdk {
class GroupDTO {
public:
    GroupDTO();
    virtual ~GroupDTO();
    
    void setCreatorId(UserIdentity creatorId);
    UserIdentity getCreatorId()const;
    void setGroupUrl(std::string groupUrl);
    std::string getGroupUrl()const;
    void setGroupName(std::string groupName);
    std::string getGroupName()const;
    void setGroupId(long long groupId);
    long long getGroupId()const;
    void setNumberOfMembers(int numberOfMembers);
    int getNumberOfMembers()const;
private:

    long long groupId{0};
    std::string groupName;
    std::string groupUrl;
    UserIdentity creatorId{0};
    int numberOfMembers{0};
};
}
#endif /* GROUPDTO_H */

