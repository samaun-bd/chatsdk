/* 
 * File:   packet_dto.h
 * Author: dipal
 *
 * Created on July 12, 2015, 2:20 PM
 */

#ifndef PACKET_DTO_H
#define	PACKET_DTO_H

#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <set>

#include "MemberDTO.h"
#include "SeenPacketDTO.h"
#include "GroupActivityDTO.h"
#include "GroupDTO.h"
#include "FriendMessageStatusDTO.h"
#include "ByteArray.h"
#include "RoomDTO.h"
#include "PublicChatMemberDTO.h"
#include "SDKMessageDTO.h"
#include "ConversationDTO.h"
#include "DataCounter.h"


namespace imsdk {
class PacketDTO {
public:

    PacketDTO();

    virtual ~PacketDTO();

private:

    int packetType{0};
    std::string packetID;
    std::string pivotID; 
    std::string authSessionID;
	long long userIdentity{ 0 };
	long long pageOwnerId{ 0 };
    std::string fullName;
    long long friendIdentity{0};
    long long ringId{0};
    long long publisherId{0};
    int onlineStatus{0};
    std::string message;
	std::string information;
	int type{ 0 };
	int informationType{ 0 };
    int messageType{0};
    long long messageDate{ 0 };
    long long lastSyncTime{ 0 };
    int device{0};
    int friendDevice{0};
    std::string friendDeviceToken;
    int timeout{0};
    long long groupId{0};
    std::string groupName;
    std::string groupUrl;
    int numberOfMembers{0};
    int groupLeaveType{0};
    int numberOfMessage{0};
    std::vector<MemberDTO> memberList;
    std::vector<std::string> packetIDs;
    std::vector<std::shared_ptr<PacketDTO>> messageList;
    std::vector<SeenPacketDTO> seenMessageList;
    int sequenceNumber{0};
    int chatBindingPort{0};
    long long serverDate{0};
    int appType{0};
    int onlineMood{0};
    int fileTotalChunk{0};
    int fileChunkCurrentIndex{0};
    std::string fileContent;
    std::vector<std::pair<int, int> > fileChunkList;
    bool isAddToBlock{false};
    int fileTransferPort{0};
    long long fileId{0};
    bool fileAcceptReject{false};
    long long fileOffSet{0};
    long long receivedBytes{0};
    long long messageUpdateDate{0};
    bool isSecretVisible{false};
    int messageStatus{0};
    long long blockUnblockDate{0};
    std::shared_ptr<ByteArray> dataBytes;
    long long groupUpdateDate{0};
    int upDownStatus{0};
    int limit{0};
    std::vector<GroupActivityDTO> groupActivities;
    std::vector<GroupDTO> groupDTOList;
    int groupActivityType{0};
    std::vector<FriendMessageStatusDTO> friendMessageStatusDTOList;
    int numberOfGroups{0};
    int appVersion{0};
    bool fromOnline{false};
    
    std::string roomId;
    std::string roomFullName;
    std::string roomUrl;
    std::string roomSearchName;
    int selfPlatform{0};
    int friendPlatform{0};
    int startIndex{0};
    std::vector<RoomDTO> roomList;
    std::string serverIp;
    int serverPort{0};
    std::vector<PublicChatMemberDTO> publicChatMemberList;
    int month{0};
    int year{0};
    std::vector<SDKMessageDTO> chatMessageList;
    std::string pagingState;
    long long recipientId{0};
    bool requestStatus{false};
    bool fromAnonymous{false};
    long long originalUserId{0};
    std::vector<UserIdentity> shadowIdList;
    int iosVoipPush {0};
    bool memberInGroup{true};
    int originalPacketType{0};
    DataCounter dataCounter;
    std::string originalPacketID;
    long long lastLikerId{0};
    int numberOfPublicChatLikersId{0};
    std::vector<UserIdentity> publicChatUserIDList;
    int numberOfPublicRoomCategory{0};
    std::vector<std::string> publicRoomCategoryList;
    std::string countryOfPublicChatRoom;
    std::string categoryOfPublicChatRoom;
    int publicChatLikeCount{0};
    bool publicChatILike{false};
    bool publicChatIReport{false};
    int conversationType{0};
    long long friendOrGroupId{0};
    int numberOfConversation{0};
    int unreadCount{0};
    bool messageEdited{false};
    bool networkConnectionAvailable{false};
    std::vector<ConversationDTO> conversationList;
    
    std::string fileDownloadId;
    int fileChunkCount{0};
    int fileChunkSize{0};
    long long fileSize{0};
    bool fileManifest{false};
    std::string fileChunkDownloadKey;
    int fileDomainType{0};
    std::string localFilePath;
    double chunkedMediaTransferPercentage{0};
    bool mediaTransferTypeUpload{false};
    bool roomListFromHistory{false};
    std::string caption;
    int widthOrFileSize{0};
    int heightOrDuration{0};
    bool chunkedTransfer{true};
    int profileType{ 0 };
    int friendProfileType{ 0 };
    int deleteType{ 0 };
    std::string friendProfileImageUrl;

    std::set<UserIdentity> pageIdList;
    bool isActivateUserAccount{ false };
    bool isFromSynced{ false };
    long long oldestMessageTime{ 0 };
    
    long long disburseTime { 0 };
    long long expireTime { 0 };
    std::string notice;
    std::vector<std::string> isoList;

public:

    // Private attribute accessor methods
    // 
    
    
    /**
     * Set the value of packetType
     * @param new_var the new value of packetType
     */
    void setPacketType(int new_var) {
        packetType = new_var;
    }

    /**
     * Get the value of packetType
     * @return the value of packetType
     */
    int getPacketType() {
        return packetType;
    }

    /**
     * Set the value of packetID
     * @param new_var the new value of packetID
     */
    void setPacketID(std::string new_var) {
        packetID = new_var;
    }

    /**
     * Get the value of packetID
     * @return the value of packetID
     */
    std::string getPacketID() {
        return packetID;
    }

    /**
    * Set the value of pivotID
    * @param new_var the new value of pivotID
    */
    void setPivotID(std::string new_var) {
        pivotID = new_var;
    }

    /**
    * Get the value of pivotID
    * @return the value of pivotID
    */
    std::string getPivotID() {
        return pivotID;
    }

    /**
    * Set the value of authSessionID
    * @param new_var the new value of authSessionID
    */
    void setAuthSessionID(std::string new_var) {
        authSessionID = new_var;
    }

    /**
    * Get the value of authSessionID
    * @return the value of authSessionID
    */
    std::string getAuthSessionID() {
        return authSessionID;
    }


    /**
     * Set the value of userIdentity
     * @param new_var the new value of userIdentity
     */
    void setUserIdentity(long long new_var) {
        userIdentity = new_var;
    }

    /**
     * Get the value of userIdentity
     * @return the value of userIdentity
     */
    long long getUserIdentity() {
        return userIdentity;
    }

	/**
	* Set the value of pageOwnerId
	* @param new_var the new value of pageOwnerId
	*/
	void setPageOwnerId(long long new_var) {
		pageOwnerId = new_var;
	}

	/**
	* Get the value of pageOwnerId
	* @return the value of pageOwnerId
	*/
	long long getPageOwnerId() {
		return pageOwnerId;
	}

    /**
     * Set the value of fullName
     * @param new_var the new value of fullName
     */
    void setFullName(std::string new_var) {
        fullName = new_var;
    }

    /**
     * Get the value of fullName
     * @return the value of fullName
     */
    std::string getFullName() {
        return fullName;
    }

    /**
     * Set the value of friendIdentity
     * @param new_var the new value of friendIdentity
     */
    void setFriendIdentity(long long new_var) {
        friendIdentity = new_var;
    }

    /**
     * Get the value of friendIdentity
     * @return the value of friendIdentity
     */
    long long getFriendIdentity() {
        return friendIdentity;
    }

    /**
     * Set the value of onlineStatus
     * @param new_var the new value of onlineStatus
     */
    void setOnlineStatus(int new_var) {
        onlineStatus = new_var;
    }

    /**
     * Get the value of onlineStatus
     * @return the value of onlineStatus
     */
    int getOnlineStatus() {
        return onlineStatus;
    }

    /**
     * Set the value of message
     * @param new_var the new value of message
     */
    void setMessage(std::string new_var) {
        message = new_var;
    }

    /**
     * Get the value of message
     * @return the value of message
     */
    std::string getMessage() {
        return message;
    }

	std::string getInformation(){
		return information;
	}

	void setInformation(std::string var){
		information = var;
	}

	int getType(){
		return type;
	}

	void setType(int var){
		type = var;
	}

	int getInformationType(){
		return informationType;
	}

	void setInformationType(int var){
		informationType = var;
	}

    /**
     * Set the value of messageType
     * @param new_var the new value of messageType
     */
    void setMessageType(int new_var) {
        messageType = new_var;
    }

    /**
     * Get the value of messageType
     * @return the value of messageType
     */
    int getMessageType() {
        return messageType;
    }

    /**
     * Set the value of messageDate
     * @param new_var the new value of messageDate
     */
    void setMessageDate(long long new_var) {
        messageDate = new_var;
    }

    /**
     * Get the value of messageDate
     * @return the value of messageDate
     */
    long long getMessageDate() {
        return messageDate;
    }

    /**
    * Set the value of lastSyncTime
    * @param new_var the new value of lastSyncTime
    */
    void setLastSyncTime(long long new_var) {
        lastSyncTime = new_var;
    }

    /**
    * Get the value of lastSyncTime
    * @return the value of lastSyncTime
    */
    long long getLastSyncTime() {
        return lastSyncTime;
    }

    /**
     * Set the value of device
     * @param new_var the new value of device
     */
    void setDevice(int new_var) {
        device = new_var;
    }

    /**
     * Get the value of device
     * @return the value of device
     */
    int getDevice() {
        return device;
    }


    /**
     * Set the value of firendDevice
     * @param new_var the new value of firendDevice
     */
    void setFriendDevice(int new_var) {
        friendDevice = new_var;
    }

    /**
     * Get the value of firendDevice
     * @return the value of firendDevice
     */
    int getFriendDevice() {
        return friendDevice;
    }

    /**
     * Set the value of deviceToken
     * @param new_var the new value of deviceToken
     */
    void setFriendDeviceToken(std::string new_var) {
        friendDeviceToken = new_var;
    }

    /**
     * Get the value of deviceToken
     * @return the value of deviceToken
     */
    std::string getFriendDeviceToken() {
        return friendDeviceToken;
    }

    /**
     * Set the value of timeout
     * @param new_var the new value of timeout
     */
    void setTimeout(int new_var) {
        timeout = new_var;
    }

    /**
     * Get the value of timeout
     * @return the value of timeout
     */
    int getTimeout() {
        return timeout;
    }

    /**
     * Set the value of groupId
     * @param new_var the new value of groupId
     */
    void setGroupId(long long new_var) {
        groupId = new_var;
    }

    /**
     * Get the value of groupId
     * @return the value of groupId
     */
    long long getGroupId() {
        return groupId;
    }

    void setGroupUrl(std::string groupUrl) {
        this->groupUrl = groupUrl;
    }

    std::string getGroupUrl() {
        return groupUrl;
    }

    void setGroupName(std::string groupName) {
        this->groupName = groupName;
    }

    std::string getGroupName() {
        return groupName;
    }

    /**
     * Set the value of numberOfMembers
     * @param new_var the new value of numberOfMembers
     */
    void setNumberOfMembers(int new_var) {
        numberOfMembers = new_var;
    }

    /**
    * Get the value of numberOfMembers
    * @return the value of numberOfMembers
    */
    int getNumberOfMembers() {
        return numberOfMembers;
    }

    /**
    * Set the value of groupLeaveType
    * @param new_var the new value of groupLeaveType
    */
    void setGroupLeaveType(int new_var) {
        groupLeaveType = new_var;
    }

    /**
     * Get the value of groupLeaveType
     * @return the value of groupLeaveType
     */
    int getGroupLeaveType() {
        return groupLeaveType;
    }

    /**
     * Set the value of numberOfMessage
     * @param new_var the new value of numberOfMessage
     */
    void setNumberOfMessage(int new_var) {
        numberOfMessage = new_var;
    }

    /**
     * Get the value of numberOfMessage
     * @return the value of numberOfMessage
     */
    int getNumberOfMessage() {
        return numberOfMessage;
    }

    /**
     * Set the value of memberList
     * @param new_var the new value of memberList
     */
    void setMemberList(const std::vector<MemberDTO> &new_var) {
        memberList = new_var;
    }

    /**
     * Get the value of memberList
     * @return the value of memberList
     */
    std::vector<MemberDTO> getMemberList() {
        return memberList;
    }

    /**
     * Appemd the value into memberList
     * @param new_var the new value of memberList
     */
    void appendMember(MemberDTO new_var) {
        memberList.push_back(new_var);
    }

    /**
     * Set the value of packetIDs
     * @param new_var the new value of packetIDs
     */
    void setPacketIDs(std::vector<std::string> new_var) {
        packetIDs = new_var;
    }

    /**
     * Get the value of packetIDs
     * @return the value of packetIDs
     */
    std::vector<std::string> getPacketIDs() {
        return packetIDs;
    }

    /**
     * Append the value of packetID
     * @param new_var the new value of packetID
     */
    void appendPacketID(std::string new_var) {
        packetIDs.push_back(new_var);
    }

    /**
     * Set the value of messageList
     * @param new_var the new value of messageList
     */
    void setMessageList(std::vector<std::shared_ptr<PacketDTO>> &new_var) {
        messageList = new_var;
    }
    
    /**
     * Set the value of seenMessageList
     * @param new_var the new value of seenMessageList
     */
    void setSeenMessageList(std::vector<SeenPacketDTO> &new_var) {
        seenMessageList = new_var;
    }

    /**
     * Get the value of messageList
     * @return the value of messageList
     */
    std::vector<std::shared_ptr<PacketDTO>> getMessageList() {
        return messageList;
    }
    
    /**
     * Get the value of seenMessageList
     * @return the value of seenMessageList
     */
    std::vector<SeenPacketDTO> getSeenMessageList() {
        return seenMessageList;
    }

    /**
     * Append message to messageList
     * @param new_var the new value of messageList
     */
    void appendMessage(std::shared_ptr<PacketDTO> new_var) {
        messageList.push_back(new_var);
    }
    
    /**
     * Append message to seenMessageList
     * @param new_var the new value of seenMessageList
     */
    void appendSeenMessage(SeenPacketDTO new_var) {
        seenMessageList.push_back(new_var);
    }

    /**
     * Set the value of sequenceNumber
     * @param new_var the new value of sequenceNumber
     */
    void setSequenceNumber(int new_var) {
        sequenceNumber = new_var;
    }

    /**
     * Get the value of sequenceNumber
     * @return the value of sequenceNumber
     */
    int getSequenceNumber() {
        return sequenceNumber;
    }

    /**
     * Set the value of chatBindingPort
     * @param new_var the new value of chatBindingPort
     */
    void setChatBindingPort(int new_var) {
        chatBindingPort = new_var;
    }

    /**
     * Get the value of chatBindingPort
     * @return the value of chatBindingPort
     */
    int getChatBindingPort() {
        return chatBindingPort;
    }

    /**
     * Set the value of serverDate
     * @param new_var the new value of serverDate
     */
    void setServerDate(long long new_var) {
        serverDate = new_var;
    }

    /**
     * Get the value of serverDate
     * @return the value of serverDate
     */
    long long getServerDate() {
        return serverDate;
    }

    /**
     * Set the value of appType
     * @param new_var the new value of appType
     */
    void setAppType(int new_var) {
        appType = new_var;
    }

    /**
     * Get the value of appType
     * @return the value of appType
     */
    int getAppType() {
        return appType;
    }

    /**
     * Set the value of onlineMood
     * @param new_var the new value of onlineMood
     */
    void setOnlineMood(int new_var) {
        onlineMood = new_var;
    }

    /**
     * Get the value of onlineMood
     * @return the value of onlineMood
     */
    int getOnlineMood() {
        return onlineMood;
    }

    /**
     * Set total number of chunk in file
     * @param new_var the total number of chunk
     */
    void setFileTotalChunk(int new_var) {
        fileTotalChunk = new_var;
    }

    /**
     * Get the total number of chunk in file
     * @return the total number of chunk
     */
    int getFileTotalChunk() {
        return fileTotalChunk;
    }

    /**
     * Set current chunk index
     * @param new_var current chunk index of file
     */
    void setFileChunkCurrentIndex(int new_var) {
        fileChunkCurrentIndex = new_var;
    }

    /**
     * Get current chunk index
     * @return current chunk index of file
     */
    int getFileChunkCurrentIndex() {
        return fileChunkCurrentIndex;
    }

    /**
     * Set the file content
     * @param new_var file content
     */
    void setFileContent(std::string new_var) {
        fileContent = new_var;
    }

    /**
     * Get the file content
     * @return file content
     */
    std::string getFileContent() {
        return fileContent;
    }

    /**
     * Set chunk index list
     * @param new_var chunk index list
     */
    void setFileChunkList(std::vector<std::pair<int, int> > new_var) {
        fileChunkList = new_var;
    }

    /**
     * Get the chunk index list
     * @return chunk index list
     */
    std::vector<std::pair<int, int> > getFileChunkList() {
        return fileChunkList;
    }

    /**
     * Append chunk range into chunk list
     * @param chunk
     */
    void appendFileChunk(std::pair<int, int> chunk) {
        fileChunkList.push_back(chunk);
    }

    /**
     * Set the value if need to add user to block list (db)
     * @param new_var Is add to block
     */
    void setIsAddToBlock(bool new_var) {
        isAddToBlock = new_var;
    }

    /**
     * Get the value of isAddToBlock
     * @return is add to block
     */
    bool getIsAddToBlock() {
        return isAddToBlock;
    }
    
    /**
     * Set the value of fileTransferPort
     * @param new_var the new value of fileTransferPort
     */
    void setFileTransferPort(int new_var) {
        fileTransferPort = new_var;
    }

    /**
     * Get the value of fileTransferPort
     * @return the value of fileTransferPort
     */
    int getFileTransferPort() {
        return fileTransferPort;
    }
    
    /**
     * Set the value of fileIdentity
     * @param new_var the new value of fileIdentity
     */
    void setFileIdentity(long long new_var) {
        fileId = new_var;
    }

    /**
     * Get the value of fileIdentity
     * @return the value of fileIdentity
     */
    long long getFileIdentity() {
        return fileId;
    }
    
    /**
     * Set the value of fileIdentity
     * @param new_var the new value of fileIdentity
     */
    void setFileOffset(long long new_var) {
        fileOffSet = new_var;
    }

    /**
     * Get the value of fileIdentity
     * @return the value of fileIdentity
     */
    long long getFileOffSet() {
        return fileOffSet;
    }
    
    /**
     * Set the value of fileIdentity
     * @param new_var the new value of fileIdentity
     */
    void setReceivedBytes(long long new_var) {
        receivedBytes = new_var;
    }

    /**
     * Get the value of fileIdentity
     * @return the value of fileIdentity
     */
    long long getReceivedBytes() {
        return receivedBytes;
    }
        
    void setDisburseTime(long long new_var) {
        disburseTime = new_var;
    }
    
    long long getDisburseTime() {
        return disburseTime;
    }
    
    void setExpireTime(long long new_var) {
        expireTime = new_var;
    }
    
    long long getExpireTime() {
        return expireTime;
    }
    
    void setNotice(std::string new_var) {
        notice = new_var;
    }
    
    std::string getNotice() {
        return notice;
    }
    
    void setIsoList(std::vector<std::string> new_var) {
        isoList = new_var;
    }
    
    std::vector<std::string> getIsoList() {
        return isoList;
    }

    void setNumberOfGroups(int numberOfGroups);
    int getNumberOfGroups();
    void setGroupDTOList(std::vector<GroupDTO> groupDTOList);
    std::vector<GroupDTO> getGroupDTOList();
    void appendGroupDTO(GroupDTO groupDTO);
    
    void setGroupActivities(std::vector<GroupActivityDTO> groupActivities);
    std::vector<GroupActivityDTO> getGroupActivities();
    void appendGroupAcitivity(GroupActivityDTO groupActivity);
    
    void setLimit(int limit);
    int getLimit();
    void setUpDownStatus(int upDownStatus);
    int getUpDownStatus();
    void setGroupUpdateDate(long long groupUpdateDate);
    long long getGroupUpdateDate();
    void setBlockUnblockDate(long long blockUnblockDate);
    long long getBlockUnblockDate();
    void setMessageStatus(int messageStatus);
    int getMessageStatus();
    void setIsSecretVisible(bool SecretVisible);
    bool getIsSecretVisible();
    
    void setFriendMessageStatusDTOList(std::vector<FriendMessageStatusDTO> friendMessageStatusDTOList);
    std::vector<FriendMessageStatusDTO> getFriendMessageStatusDTOList();
    void appendFriendMessageStatusDTO(FriendMessageStatusDTO friendMessageStatusDTO);
    
    void setDataBytes(std::shared_ptr<ByteArray> dataBytes);
    std::shared_ptr<ByteArray> getDataBytes();
    
    void setGroupActivityType(int groupActivityType);
    int getGroupActivityType();
    std::string toString() {
        std::stringstream sout;

        sout << "PacketID : " << getPacketID() << std::endl;
        sout << "User Identity : " << getUserIdentity() << std::endl;
        sout << "Friend Indentity : " << getFriendIdentity() << std::endl;
        sout << "AppType : " << getAppType() << std::endl;
        sout << "Chat Binding Port : " << getChatBindingPort() << std::endl;
        sout << "Device : " << getDevice() << std::endl;
        sout << "Device Token : " << getFriendDeviceToken() << std::endl;
        sout << "Full Name : " << getFullName() << std::endl;
        sout << "Group Id :" << getGroupId() << std::endl;

        return sout.str();
    }
    void setAppVersion(int appVersion);
    int getAppVersion();
    void setOnline(bool Online);
    bool isOnline();
    void setServerPort(int serverPort);
    int getServerPort() const;
    void setServerIp(std::string serverIp);
    std::string getServerIp() const;
    void setRoomList(std::vector<RoomDTO> &roomList);
    std::vector<RoomDTO> getRoomList() const;
    void appendRoom(RoomDTO &roomDTO);
    void setStartIndex(int startIndex);
    int getStartIndex() const;
    void setSelfPlatform(int selfPlatform);
    int getSelfPlatform() const;
    void setRoomSearchName(std::string roomSearchName);
    std::string getRoomSearchName() const;
    void setRoomUrl(std::string roomUrl);
    std::string getRoomUrl() const;
    void setRoomFullName(std::string roomFullName);
    std::string getRoomFullName() const;
    void setRoomId(std::string roomId);
    std::string getRoomId() const;
    void setPublicChatMemberList(std::vector<PublicChatMemberDTO> publicChatMemberList);
    std::vector<PublicChatMemberDTO> getPublicChatMemberList() const;
    void setYear(int year);
    int getYear() const;
    void setMonth(int month);
    int getMonth() const;
    void setChatMessageList(std::vector<SDKMessageDTO> &chatMessageList);
    std::vector<SDKMessageDTO> getChatMessageList() const;
    void setPagingState(std::string pagingState);
    std::string getPagingState() const;
    void setRecipientId(long long recepientId);
    long long getRecipientId() const;
    void setRequestStatus(bool status);
    bool getRequestStatus() const;
    void setFromAnonymous(bool fromAnonymous);
    bool isFromAnonymous() const;
    void setOriginalUserId(long long originalUserId);
    long long getOriginalUserId() const;
    void setShadowIdList(std::vector<UserIdentity> &shadowIdList);
    std::vector<UserIdentity> getShadowIdList() const;
    void setFileAcceptReject(bool fileAcceptReject);
    bool isFileAcceptReject() const;
    void setMemberInGroup(bool isMemberInGroup);
    bool isMemberInGroup();
    void setIosVoipPush(int IosVoipPush);
    int getIosVoipPush() const;
    void setOriginalPacketType(int originalPacketType);
    int getOriginalPacketType() const;
    void setDataCounter(DataCounter dataCounter);
    DataCounter getDataCounter();
    void setOriginalPacketID(std::string originalPacketID);
    std::string getOriginalPacketID() const;
    void setLastLikerId(long long lastLikerId);
    long long getLastLikerId() const;
    void setNumberOfPublicChatLikersId(int numberOfPublicChatLikersId);
    int getNumberOfPublicChatLikersId() const;
    void setPublicChatUserIDList(std::vector<UserIdentity> publicChatUserIDList);
    std::vector<UserIdentity> getPublicChatUserIDList() const;
    void setNumberOfPublicRoomCategory(int numberOfPublicRoomCategory);
    int getNumberOfPublicRoomCategory() const;
    void setPublicRoomCategoryList(std::vector<std::string> publicRoomCategoryList);
    std::vector<std::string> getPublicRoomCategoryList() const;
    void setCountryOfPublicChatRoom(std::string countryOfPublicChatRoom);
    std::string getCountryOfPublicChatRoom() const;
    void setCategoryOfPublicChatRoom(std::string categoryOfPublicChatRoom);
    std::string getCategoryOfPublicChatRoom() const;
    void setPublicChatLikeCount(int publicChatLikeCount);
    int getPublicChatLikeCount() const;
    void setPublicChatReportCount(int publicChatReportCount);
    int getPublicChatReportCount() const;
    void setPublicChatILike(bool publicChatILike);
    bool isPublicChatILike() const;
    void setPublicChatIReport(bool publicChatIReport);
    bool isPublicChatIReport() const;
    void setFriendOrGroupId(long long friendOrGroupId);
    long long getFriendOrGroupId() const;
    void setConversationType(int conversationType);
    int getConversationType() const;
    void setUnreadCount(int unreadCount);
    int getUnreadCount() const;
    void setNumberOfConversation(int numberOfConversation);
    int getNumberOfConversation() const;
    void setMessageEdited(bool messageEdited);
    bool isMessageEdited() const;
    void setRingId(long long ringId);
    long long getRingId() const;
    void setNetworkConnectionAvailable(bool networkConnectionAvailable);
    bool isNetworkConnectionAvailable() const;

    void setConversationList(std::vector<ConversationDTO> conversationList);
    std::vector<ConversationDTO> getConversationList() const;

    void setPublisherId(long long publisherId);
    long long getPublisherId() const;

    void setFileChunkDownloadKey(std::string fileChunkDownloadKey);
    std::string getFileChunkDownloadKey() const;
    void setFileSize(long long fileSize);
    long long getFileSize() const;
    void setFileChunkSize(int fileChunkSize);
    int getFileChunkSize() const;
    void setFileChunkCount(int fileChunkCount);
    int getFileChunkCount() const;
    void setFileDownloadId(std::string fileDownloadId);
    std::string getFileDownloadId() const;
    void setFileManifest(bool fileManifest);
    bool isFileManifest() const;
    void setFileDomainType(int fileDomainType);
    int getFileDomainType() const;
    void setLocalFilePath(std::string localFilePath);
    std::string getLocalFilePath() const;
    void setChunkedMediaTransferPercentage(double chunkedMediaTransferPercentage);
    double getChunkedMediaTransferPercentage() const;
    void setMediaTransferTypeUpload(bool mediaTransferTypeUpload);
    bool isMediaTransferTypeUpload() const;
    void setRoomListFromHistory(bool roomListFromHistory);
    bool isRoomListFromHistory() const;
    void setHeightOrDuration(int heightOrDuration);
    int getHeightOrDuration() const;
    void setWidthOrFileSize(int widthOrFileSize);
    int getWidthOrFileSize() const;
    void setCaption(std::string caption);
    std::string getCaption() const;
    void setFriendProfileImageUrl(std::string profileImageUrl);
    std::string getFriendProfileImageUrl() const;
    void setChunkedTransfer(bool chunkedTransfer);
    bool isChunkedTransfer() const;
    void setBlockedUserId(long long blockedUserId);
    long long getBlockedUserId() const;
    void setProfileType(int profileType);
    int getProfileType() const;
    void setFriendProfileType(int friendProfileType);
    int getFriendProfileType() const;

    void setMessageDeleteType(int deleteType);
    int getMessageDeleteType() const;
    
    void setPageIdList(std::set<UserIdentity> &pageIdList);
	std::set<UserIdentity> getPageIdList() const;

    bool getIsActivateUserAccount() const;
    void setIsActivateUserAccount(bool isActivate);

    void setIsFromSynced(bool isSynced);
    bool getIsFromSynced() const;

    void setOldestMessageTime(long long oldestMessageTime);
    long long getOldestMessageTime() const;

private:


    void initAttributes();

};
}

#endif	/* PACKET_DTO_H */

