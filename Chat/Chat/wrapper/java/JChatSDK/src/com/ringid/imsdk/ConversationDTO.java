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
public class ConversationDTO {
    
    private int conversationType;
    private long friendId;
    private long groupId;

    public ConversationDTO() {
    }

    public ConversationDTO(int conversationType, long friendId, long groupId) {
        this.conversationType = conversationType;
        this.friendId = friendId;
        this.groupId = groupId;
    }
    
    /**
     * @return the conversationType
     */
    public int getConversationType() {
        return conversationType;
    }

    /**
     * @param conversationType the conversationType to set
     */
    public void setConversationType(int conversationType) {
        this.conversationType = conversationType;
    }

    /**
     * @return the friendId
     */
    public long getFriendId() {
        return friendId;
    }

    /**
     * @param friendId the friendId to set
     */
    public void setFriendId(long friendId) {
        this.friendId = friendId;
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
}
