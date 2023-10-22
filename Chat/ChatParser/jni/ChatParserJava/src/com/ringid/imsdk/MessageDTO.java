package com.ringid.imsdk;

import java.util.ArrayList;
import java.util.HashSet;

/**
 * Message Data Transfer Object.
 * @author Anwar
 */
public class MessageDTO {

    private int packetType;
    private String packetID;
    private long userIdentity;
    private String fullName;
    private long friendIdentity;
    private int onlineStatus;
    private String message;
    private int messageType;
    private long messageDate;
    private int device;
    private String deviceToken;
    private int timeout;
    private float latitude;
    private float longitude;
    private long groupId;
    private int totalGroupMembers;
    private String groupName;
    private String groupUrl;
    private int numberOfMembers;
    private int numberOfMessage;
    private ArrayList<MemberDTO> memberList;
    private ArrayList<String> packetIDs;
    private ArrayList<MessageDTO> messageList;
    private int sequenceNumber;
    private int chatBindingPort;
    private long serverDate;
    private int appType;
    private int onlineMood;
    private int fileTotalChunk;
    private int fileChunkCurrentIndex;
    private String fileContent;
    private ArrayList<FileChunk> fileChunkList;
    private boolean isAddToBlock;
    private boolean isUpdateGroupInformation;


    /**
     * MessageDTO Constructor
     */
    public MessageDTO() {
    }

    /**
     * Get Packet Type
     * @return Packet Type
     */
    public int getPacketType() {
        return packetType;
    }

    /**
     * Set Packet Type
     * @param packetType Packet type of this packet
     */
    public void setPacketType(int packetType) {
        this.packetType = packetType;
    }

    /**
     * Get Packet ID
     * @return Packet ID
     */
    public String getPacketID() {
        return packetID;
    }

    /**
     * Set Packet ID
     * @param packetID Packet id of this packet
     */
    public void setPacketID(String packetID) {
        this.packetID = packetID;
    }

    /**
     * Get User Identity
     * @return User Identity
     */
    public long getUserIdentity() {
        return userIdentity;
    }

    /**
     * Set User Identity
     * @param userIdentity User identity
     */
    public void setUserIdentity(long userIdentity) {
        this.userIdentity = userIdentity;
    }

    /**
     * Get Full Name
     * @return Full Name
     */
    public String getFullName() {
        return fullName;
    }

    /**
     * Set Full Name
     * @param fullName Full name of user. maximum length of name is 127 bytes
     */
    public void setFullName(String fullName) {
        this.fullName = fullName;
    }

    /**
     * Get Friend Identity
     * @return Friend Identity
     */
    public long getFriendIdentity() {
        return friendIdentity;
    }

    /**
     * Set Friend Identity
     * @param friendIdentity Friend identity
     */
    public void setFriendIdentity(long friendIdentity) {
        this.friendIdentity = friendIdentity;
    }

    /**
     * Get Message
     * @return Message
     */
    public String getMessage() {
        return message;
    }

    /**
     * Set Message
     * @param message Text message
     */
    public void setMessage(String message) {
        this.message = message;
    }

    /**
     * Get Message Type
     * @return Message Type
     */
    public int getMessageType() {
        return messageType;
    }

    /**
     * Set Message Type
     * @param messageType Message type
     */
    public void setMessageType(int messageType) {
        this.messageType = messageType;
    }

    /**
     * Get Message date
     * @return Message Date
     */
    public long getMessageDate() {
        return messageDate;
    }

    /**
     * Set Message Data
     * @param messageDate Message date
     */
    public void setMessageDate(long messageDate) {
        this.messageDate = messageDate;
    }

    /**
     * Get Device Type Or Platform
     * @return Device
     */
    public int getDevice() {
        return device;
    }

    /**
     * Set Device Type Or Platform
     * @param device Device type or platform of user
     */
    public void setDevice(int device) {
        this.device = device;
    }

    /**
     * Get Device Token
     * @return Device Token
     */
    public String getDeviceToken() {
        return deviceToken;
    }

    /**
     * Set Device Token
     * @param deviceToken Device token of user device
     */
    public void setDeviceToken(String deviceToken) {
        this.deviceToken = deviceToken;
    }

    /**
     * Get Timeout. Timeout will be used for secret chat. Default timeout is zero(0).
     * @return Timeout
     */
    public int getTimeout() {
        return timeout;
    }

    /**
     * Set Timeout. Timeout will be used for secret chat. Default timeout is zero(0).
     * @param timeout Time out for message
     */
    public void setTimeout(int timeout) {
        this.timeout = timeout;
    }

    /**
     * Get Latitude
     * @return Latitude
     */
    public float getLatitude() {
        return latitude;
    }

    /**
     * Set Latitude
     * @param latitude Latitude of user
     */
    public void setLatitude(float latitude) {
        this.latitude = latitude;
    }

    /**
     * Get Longitude
     * @return Longitude
     */
    public float getLongitude() {
        return longitude;
    }

    /**
     * Set Longitude
     * @param longitude Longitude of user
     */
    public void setLongitude(float longitude) {
        this.longitude = longitude;
    }

    /**
     * Get Group Or Tag Id
     * @return Group Id
     */
    public long getGroupId() {
        return groupId;
    }

    /**
     * Set Group Or Tag Id
     * @param groupId Group identity
     */
    public void setGroupId(long groupId) {
        this.groupId = groupId;
    }

    /**
     * Get Number of Group Members. To get the group members use {@link MessageDTO#getMemberList() }
     * @return Number Of Members
     */
    public int getNumberOfMembers() {
        return numberOfMembers;
    }

    /**
     * Set Number Of Group Members. Use this function while using {@link MessageDTO#setMemberList(java.util.ArrayList) }
     * @param numberOfMembers Number of members of group
     */
    public void setNumberOfMembers(int numberOfMembers) {
        this.numberOfMembers = numberOfMembers;
    }

    /**
     * Get Member List.
     * @return Member List
     */
    public ArrayList<MemberDTO> getMemberList() {
        return memberList;
    }
    
    /**
     * Set Member List. Also set the number of members at {@link MessageDTO#setNumberOfMembers(int) }
     * @param memberList Member list of group
     */
    public void setMemberList(ArrayList<MemberDTO> memberList) {
        this.memberList = memberList;
    }
    
    /**
     * Get Online Status
     * @return Online Status
     */
    public int getOnlineStatus() {
        return onlineStatus;
    }

    /**
     * Set Online Status
     * @param onlineStatus Online status of user
     */
    public void setOnlineStatus(int onlineStatus) {
        this.onlineStatus = onlineStatus;
    }

    /**
     * Get Number Of Message. If there are several messages, you will know about total number of messages from this function. Get the sequence number of this message from {@link MessageDTO#getSequenceNumber() }
     * @return Number Of Message
     */
    public int getNumberOfMessage() {
        return numberOfMessage;
    }

    /**
     * Set Number Of Message. If there are several messages, set total number of messages using this function and set the sequence number of this messages using {@link MessageDTO#setSequenceNumber(int) }
     * @param numberOfMessage Number of messages included
     */
    public void setNumberOfMessage(int numberOfMessage) {
        this.numberOfMessage = numberOfMessage;
    }

    /**
     * Get Packet Ids
     * @return Packet IDs
     */
    public ArrayList<String> getPacketIDs() {
        return packetIDs;
    }

    /**
     * Set Packet Ids
     * @param packetIDs Packet ids to include
     */
    public void setPacketIDs(ArrayList<String> packetIDs) {
        this.packetIDs = packetIDs;
    }

    /**
     * Get Message List.
     * @return Message List
     */
    public ArrayList<MessageDTO> getMessageList() {
        return messageList;
    }

    /**
     * Set Message List
     * @param messageList List of messages to include
     */
    public void setMessageList(ArrayList<MessageDTO> messageList) {
        this.messageList = messageList;
    }

    /**
     * Get Sequence Number. When there multiple messages, get the sequence number from this function. Get the total number of messages from {@link MessageDTO#getNumberOfMessage() }
     * @return Sequence Number
     */
    public int getSequenceNumber() {
        return sequenceNumber;
    }

    /**
     * Set Sequence Number. When there multiple messages, set the sequence number from this function. Set the total number of messages from {@link MessageDTO#setNumberOfMessage(int) }
     * @param sequenceNumber Sequence number of message
     */
    public void setSequenceNumber(int sequenceNumber) {
        this.sequenceNumber = sequenceNumber;
    }

    /**
     * Get Chat Binding Port. Use this port for farther communication with chat server (without offline message)
     * @return Chat Binding Port
     */
    public int getChatBindingPort() {
        return chatBindingPort;
    }

    /**
     * Set Chat Binding Port. Assigned chat binding port from chat server
     * @param chatBindingPort Assigned chat binding port from chat server
     */
    public void setChatBindingPort(int chatBindingPort) {
        this.chatBindingPort = chatBindingPort;
    }

    /**
     * Get Server Date. Current chat server date
     * @return Server Date
     */
    public long getServerDate() {
        return serverDate;
    }
    
    /**
     * Set Server Date. 
     * @param serverDate Current date and time of chat server
     */
    public void setServerDate(long serverDate) {
        this.serverDate = serverDate;
    }
    
    /**
     * Get App Type
     * @return App Type
     */
    public int getAppType() {
        return appType;
    }

    /**
     * Set App Type
     * @param appType App type of user
     */
    public void setAppType(int appType) {
        this.appType = appType;
    }
    
    /**
     * Get Online Mood. Get current mood of user.
     * @return Online Mood
     */
    public int getOnlineMood() {
        return onlineMood;
    }

    /**
     * Set Online Mood. Set online mood of user.
     * @param onlineMood Online mood
     */
    public void setOnlineMood(int onlineMood) {
        this.onlineMood = onlineMood;
    }

    /**
     * Get the total number of chunk in file.
     * @return File Total Chunk Of File
     */
    public int getFileTotalChunk() {
        return fileTotalChunk;
    }

    /**
     * Set the total number of chunk in file.
     * @param fileTotalChunk the total number of chunk in file to set
     */
    public void setFileTotalChunk(int fileTotalChunk) {
        this.fileTotalChunk = fileTotalChunk;
    }

    /**
     * Get the current chunk index of file.
     * @return ChunkCurrentIndex
     */
    public int getFileChunkCurrentIndex() {
        return fileChunkCurrentIndex;
    }

    /**
     * Set the chunk index of file.
     * @param fileChunkCurrentIndex  Chunk Current Index
     */
    public void setFileChunkCurrentIndex(int fileChunkCurrentIndex) {
        this.fileChunkCurrentIndex = fileChunkCurrentIndex;
    }

    /**
     * Get file content
     * @return File Content
     */
    public String getFileContent() {
        return fileContent;
    }

    /**
     * Set the file content
     * @param fileContent File Content
     */
    public void setFileContent(String fileContent) {
        this.fileContent = fileContent;
    }

    /**
     * Get the file chunk ranges
     * @return File Chunk Range List
     */
    public ArrayList<FileChunk> getFileChunkList() {
        return fileChunkList;
    }

    /**
     * Set the file chunk ranges
     * @param fileChunkList The File Chunk Range List to set
     */
    public void setFileChunkList(ArrayList<FileChunk> fileChunkList) {
        this.fileChunkList = fileChunkList;
    }

    /**
     * Get isAddToBlock. If it is false then add to db otherwise don't
     * @return the isAddToBlock
     */
    public boolean getIsAddToBlock() {
        return isAddToBlock;
    }

    /**
     * Set isAddToBlock.
     * @param isAddToBlock IsAddToBlock to set
     */
    public void setIsAddToBlock(boolean isAddToBlock) {
        this.isAddToBlock = isAddToBlock;
    }

    /**
     * Get group name. The Name of the group
     * @return the groupName
     */
    public String getGroupName() {
        return groupName;
    }

    /**
     * Set group name. Set the name of the group
     * @param groupName the name of the group
     */
    public void setGroupName(String groupName) {
        this.groupName = groupName;
    }

    /**
     * Get group URL. Get the picture URL of the group
     * @return the picture URL of group
     */
    public String getGroupUrl() {
        return groupUrl;
    }

    /**
     * Set group URL. Set the picture URL of the group
     * @param groupUrl the groupUrl to set
     */
    public void setGroupUrl(String groupUrl) {
        this.groupUrl = groupUrl;
    }

    /**
     * Get isUpdateGroupInformation. If the value is set then update group information otherwise set
     * @return the isUpdateGroupInformation
     */
    public boolean getIsUpdateGroupInformation() {
        return isUpdateGroupInformation;
    }

    /**
     * Set isUpdateGroupInformation. If the value is set then update group information otherwise set
     * @param isUpdateGroupInformation the isUpdateGroupInformation
     */
    public void setIsUpdateGroupInformation(boolean isUpdateGroupInformation) {
        this.isUpdateGroupInformation = isUpdateGroupInformation;
    }

    /**
     * Set total number of group members. Set the total number of members. See also {@link MessageDTO#getMemberList() }
     * @return the totalGroupMembers
     */
    public int getTotalGroupMembers() {
        return totalGroupMembers;
    }

    /**
     * Get total number of group members. Get the total number of members. See also {@link MessageDTO#setMemberList(java.util.ArrayList) }
     * @param totalGroupMembers the totalGroupMembers
     */
    public void setTotalGroupMembers(int totalGroupMembers) {
        this.totalGroupMembers = totalGroupMembers;
    }
}