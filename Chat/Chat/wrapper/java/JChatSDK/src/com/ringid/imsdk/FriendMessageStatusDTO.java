/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ringid.imsdk;

/**
 *
 * @author noman
 */
public class FriendMessageStatusDTO {
    
    private String packetId;
    private long updateDate;
    private int messageStatus;
    
    public FriendMessageStatusDTO(){
        
    }
    
    public FriendMessageStatusDTO(String packetId, long updateDate, int messageStatus){
        this.packetId = packetId;
        this.updateDate = updateDate;
        this.messageStatus = messageStatus;
    }

    /**
     * @return the packetId
     */
    public String getPacketId() {
        return packetId;
    }

    /**
     * @param packetId the packetId to set
     */
    public void setPacketId(String packetId) {
        this.packetId = packetId;
    }

    /**
     * @return the updateDate
     */
    public long getUpdateDate() {
        return updateDate;
    }

    /**
     * @param updateDate the updateDate to set
     */
    public void setUpdateDate(long updateDate) {
        this.updateDate = updateDate;
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
    
}
