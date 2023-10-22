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
public class GroupDTO {
    
    private long groupId;
    private String groupName;
    private String groupUrl;
    private long creatorId;
    private int numberOfMembers;
    
    public GroupDTO(){
    }
    
    public GroupDTO(long groupId, String groupName, String groupUrl, long creatorId, int numberOfMembers){
        this.groupId = groupId;
        this.groupName = groupName;
        this.groupUrl = groupUrl;
        this.creatorId = creatorId;
        this.numberOfMembers = numberOfMembers;
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
     * @return the groupName
     */
    public String getGroupName() {
        return groupName;
    }

    /**
     * @param groupName the groupName to set
     */
    public void setGroupName(String groupName) {
        this.groupName = groupName;
    }

    /**
     * @return the groupUrl
     */
    public String getGroupUrl() {
        return groupUrl;
    }

    /**
     * @param groupUrl the groupUrl to set
     */
    public void setGroupUrl(String groupUrl) {
        this.groupUrl = groupUrl;
    }

    /**
     * @return the creatorId
     */
    public long getCreatorId() {
        return creatorId;
    }

    /**
     * @param creatorId the creatorId to set
     */
    public void setCreatorId(long creatorId) {
        this.creatorId = creatorId;
    }

    /**
     * @return the numberOfMembers
     */
    public int getNumberOfMembers() {
        return numberOfMembers;
    }

    /**
     * @param numberOfMembers the numberOfMembers to set
     */
    public void setNumberOfMembers(int numberOfMembers) {
        this.numberOfMembers = numberOfMembers;
    }
}
