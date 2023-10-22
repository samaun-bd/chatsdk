/* 
 * File:   MessageDTO.h
 * Author: towhid
 *
 * Created on May 7, 2016, 2:35 PM
 */

#ifndef MESSAGEDTO_H
#define	MESSAGEDTO_H

#include <string>
#include "global.h"


namespace imsdk{
class SDKMessageDTO {
public:
    SDKMessageDTO();
    SDKMessageDTO(UserIdentity senderId, UserIdentity receiverId, GroupIdentity groupId, std::string packetId, int messageType, int timeOut, std::string message, long long messageDate, std::string memberFullName, std::string memberProfileUrl, bool isSecretVisible, int messageStatus, int direction, bool isEdited, int publicChatLikeCount, bool publicChatILike, bool publicChatIReport, int unreadCount);
    
    std::string getMemberFullName() const;
    void setMemberFullName(std::string memberFullName);
    std::string getMemberProfileUrl() const;
    void setMemberProfileUrl(std::string memberProfileUrl);
    std::string getMessage() const;
    void setMessage(std::string message);
    long long getMessageDate() const;
    void setMessageDate(long long messageDate);
    int getMessageType() const;
    void setMessageType(int messageType);
    std::string getPacketId() const;
    void setPacketId(std::string packetId);
    UserIdentity getSenderId() const;
    void setSenderId(UserIdentity senderId);
    void setReceiverId(UserIdentity receiverId);
    UserIdentity getReceiverId() const;
    void setDirection(int direction);
    int getDirection() const;
    void setMessageStatus(int messageStatus);
    int getMessageStatus() const;
    void setSecretVisible(bool SecretVisible);
    bool getIsSecretVisible() const;
    void setTimeOut(int timeOut);
    int getTimeOut() const;
    void setIsEdited(bool isEdited);
    bool getIsEdited() const;
    void setPublicChatLikeCount(int publicChatLikeCount);
    int getPublicChatLikeCount() const;
    void setPublicChatILike(bool publicChatILike);
    bool isPublicChatILike() const;
    void setPublicChatIReport(bool publicChatIReport);
    bool isPublicChatIReport() const;
    void setUnreadCount(int unreadCount);
    int getUnreadCount() const;
    void setGroupId(GroupIdentity groupId);
    GroupIdentity getGroupId() const;

private:
    UserIdentity senderId{0};
    UserIdentity receiverId{0};
    GroupIdentity groupId{0};
    
    std::string packetId;
    int messageType{0};
    int timeOut{0};
    std::string message;
    long long messageDate{0};
    std::string memberFullName;
    std::string memberProfileUrl;
    bool isSecretVisible{false};
    int messageStatus{0};
    int direction{0};
    bool isEdited{false};
    int publicChatLikeCount{0};
    bool publicChatILike{false};
    bool publicChatIReport{false};
    int unreadCount{0};
};
}



#endif	/* MESSAGEDTO_H */

