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
public class GroupActivityDTO {
    
    private int activityType;
    private long memberIdentity;
    private long ringId;
    private long groupId;
    private String groupNameOrUrlString;
    private int memberType;
    private long changedByUserId;
    private long updateTime;
    private String packetId;
    
    public GroupActivityDTO(){
        
    }
    
    public GroupActivityDTO(int activityType, long memberIdentity, long ringId, String groupNameOrUrlString, int memberType, long changedByUserId, long updateTime, long groupId, String packetId){
        this.activityType = activityType;
        this.memberIdentity = memberIdentity;
        this.ringId = ringId;
        this.groupNameOrUrlString = groupNameOrUrlString;
        this.memberType = memberType;
        this.changedByUserId = changedByUserId;
        this.updateTime = updateTime;
        this.groupId = groupId;
        this.packetId = packetId;
    }

    /**
     * @return the activityType
     */
    public int getActivityType() {
        return activityType;
    }

    /**
     * @param activityType the activityType to set
     */
    public void setActivityType(int activityType) {
        this.activityType = activityType;
    }

    /**
     * @return the memberIdentity
     */
    public long getMemberIdentity() {
        return memberIdentity;
    }

    /**
     * @param memberIdentity the memberIdentity to set
     */
    public void setMemberIdentity(long memberIdentity) {
        this.memberIdentity = memberIdentity;
    }

    /**
     * @return the groupNameOrUrlString
     */
    public String getGroupNameOrUrlString() {
        return groupNameOrUrlString;
    }

    /**
     * @param groupNameOrUrlString the groupNameOrUrlString to set
     */
    public void setGroupNameOrUrlString(String groupNameOrUrlString) {
        this.groupNameOrUrlString = groupNameOrUrlString;
    }

    /**
     * @return the memberType
     */
    public int getMemberType() {
        return memberType;
    }

    /**
     * @param memberType the memberType to set
     */
    public void setMemberType(int memberType) {
        this.memberType = memberType;
    }

    /**
     * @return the changedByUserId
     */
    public long getChangedByUserId() {
        return changedByUserId;
    }

    /**
     * @param changedByUserId the changedByUserId to set
     */
    public void setChangedByUserId(long changedByUserId) {
        this.changedByUserId = changedByUserId;
    }

    /**
     * @return the updateTime
     */
    public long getUpdateTime() {
        return updateTime;
    }

    /**
     * @param updateTime the updateTime to set
     */
    public void setUpdateTime(long updateTime) {
        this.updateTime = updateTime;
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

    public String getPacketId() {
        return packetId;
    }

    public void setPacketId(String packetId) {
        this.packetId = packetId;
    }

    /**
     * @return the ringId
     */
    public long getRingId() {
        return ringId;
    }

    /**
     * @param ringId the ringId to set
     */
    public void setRingId(long ringId) {
        this.ringId = ringId;
    }
}
