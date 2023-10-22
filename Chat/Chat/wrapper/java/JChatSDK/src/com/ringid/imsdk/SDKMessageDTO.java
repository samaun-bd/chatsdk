/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ringid.imsdk;

/**
 *
 * @author towhid
 */
public class SDKMessageDTO {
    private long senderId;
    private long receiverId;
    private long groupId;
    private String packetId;
    private int messageType;
    private int timeOut;
    private String message;
    private long messageDate;
    private String memberFullName;
    private String memberProfileUrl;
    private boolean isSecretVisible;
    private int messageStatus;
    private int direction;
    private boolean isEdited;
    private int publicChatLikeCount;
    private boolean publicChatILike;
    private boolean publicChatIReport;
    private int unreadCount;

    public int getPublicChatLikeCount() {
        return publicChatLikeCount;
    }

    public void setPublicChatLikeCount(int publicChatLikeCount) {
        this.publicChatLikeCount = publicChatLikeCount;
    }

    public boolean isPublicChatILike() {
        return publicChatILike;
    }

    public void setPublicChatILike(boolean publicChatILike) {
        this.publicChatILike = publicChatILike;
    }

    public boolean isPublicChatIReport() {
        return publicChatIReport;
    }

    public void setPublicChatIReport(boolean publicChatIReport) {
        this.publicChatIReport = publicChatIReport;
    }
    
    public SDKMessageDTO(){
        
    }
    
    public SDKMessageDTO(long senderId, long receiverId, long groupId, String packetId, int messageType, int timeOut, String message, long messageDate, String memberFullName, String memberProfileUrl, boolean isSecretVisible, int messageStatus, int direction, boolean isEdited, int publicChatLikeCount, boolean publicChatILike, boolean publicChatIReport, int unreadCount) {
        this.senderId = senderId;
        this.receiverId = receiverId;
        this.groupId = groupId;
        this.packetId = packetId;
        this.messageType = messageType;
        this.timeOut = timeOut;
        this.message = message;
        this.messageDate = messageDate;
        this.memberFullName = memberFullName;
        this.memberProfileUrl = memberProfileUrl;
        this.isSecretVisible = isSecretVisible;
        this.messageStatus = messageStatus;
        this.direction = direction;
        this.isEdited = isEdited;
        this.publicChatLikeCount = publicChatLikeCount;
        this.publicChatILike = publicChatILike;
        this.publicChatIReport = publicChatIReport;
        this.unreadCount = unreadCount;           
    }

    public long getSenderId() {
        return senderId;
    }

    public void setSenderId(long senderId) {
        this.senderId = senderId;
    }

    public String getPacketId() {
        return packetId;
    }

    public void setPacketId(String packetId) {
        this.packetId = packetId;
    }

    public int getMessageType() {
        return messageType;
    }

    public void setMessageType(int messageType) {
        this.messageType = messageType;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public long getMessageDate() {
        return messageDate;
    }

    public void setMessageDate(long messageDate) {
        this.messageDate = messageDate;
    }

    public String getMemberFullName() {
        return memberFullName;
    }

    public void setMemberFullName(String memberFullName) {
        this.memberFullName = memberFullName;
    }

    public String getMemberProfileUrl() {
        return memberProfileUrl;
    }

    public void setMemberProfileUrl(String memberProfileUrl) {
        this.memberProfileUrl = memberProfileUrl;
    }

    /**
     * @return the receiverId
     */
    public long getReceiverId() {
        return receiverId;
    }

    /**
     * @param receiverId the receiverId to set
     */
    public void setReceiverId(long receiverId) {
        this.receiverId = receiverId;
    }

    /**
     * @return the timeOut
     */
    public int getTimeOut() {
        return timeOut;
    }

    /**
     * @param timeOut the timeOut to set
     */
    public void setTimeOut(int timeOut) {
        this.timeOut = timeOut;
    }

    /**
     * @return the isSecretVisible
     */
    public boolean isIsSecretVisible() {
        return isSecretVisible;
    }

    /**
     * @param isSecretVisible the isSecretVisible to set
     */
    public void setIsSecretVisible(boolean isSecretVisible) {
        this.isSecretVisible = isSecretVisible;
    }

    /**
     * @return the messageStatus
     */
    public int getMessageStatus() {
        return messageStatus;
    }

    /**
     * @param messageStatus the messageStatus to set
     */
    public void setMessageStatus(int messageStatus) {
        this.messageStatus = messageStatus;
    }

    /**
     * @return the direction
     */
    public int getDirection() {
        return direction;
    }

    /**
     * @param direction the direction to set
     */
    public void setDirection(int direction) {
        this.direction = direction;
    }
    
    public void setIsEdited(boolean isEdited){
        this.isEdited = isEdited;
    }
    
    public boolean getIsEdited(){
        return isEdited;
    }

    /**
     * @return the groupId
     */
    public long getGroupId() {
        return groupId;
    }

    /**
     * @param groupId the groupId to set
     */
    public void setGroupId(long groupId) {
        this.groupId = groupId;
    }

    /**
     * @return the unreadCount
     */
    public int getUnreadCount() {
        return unreadCount;
    }

    /**
     * @param unreadCount the unreadCount to set
     */
    public void setUnreadCount(int unreadCount) {
        this.unreadCount = unreadCount;
    }
    
}
