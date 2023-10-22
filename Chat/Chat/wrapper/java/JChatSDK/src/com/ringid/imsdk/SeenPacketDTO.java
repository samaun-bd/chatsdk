/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ringid.imsdk;

/**
 *
 * @author root
 */
public class SeenPacketDTO {
    
    private String packetId;
    private long messageDate;
    private int messageStatus;
   
    public SeenPacketDTO(){
        
    }
    
    public SeenPacketDTO(String packetId, long messageDate, int messageStatus) {
        this.packetId = packetId;
        this.messageDate = messageDate;
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
     * @return the messageDate
     */
    public long getMessageDate() {
        return messageDate;
    }

    /**
     * @param messageDate the messageDate to set
     */
    public void setMessageDate(long messageDate) {
        this.messageDate = messageDate;
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
