/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ringid.imsdk;

/**
 * PublicChatMemberDTO will be returned on Public Chat Room registration success and when a new member joins a chat room.
 * It will contain memberId, fullName, profileUrl and addedTime
 * @author towhid
 */
public class PublicChatMemberDTO {
    
    private String roomId;
    private long fakeId;
    private long memberId;
    private String fullName;
    private String profileUrl;
    private long addedTime;
    private long ringId;

    public PublicChatMemberDTO() {
    }

    /**
     * PublicChatMemberDTO constructor
     * @param roomId Room Identity
     * @param memberId member's userId
     * @param fakeId Fake user ID
     * @param fullName member's full name
     * @param profileUrl member's profile url
     * @param addedTime time when member added
     * @param ringId ringID
     */
    public PublicChatMemberDTO(String roomId, long memberId, long fakeId, String fullName, String profileUrl, long addedTime, long ringId) {
        this.roomId = roomId;
        this.fakeId = fakeId;
        this.memberId = memberId;
        this.fullName = fullName;
        this.profileUrl = profileUrl;
        this.addedTime = addedTime;
        this.ringId = ringId;
    }

    /**
     * Get member id
     * @return member's userid
     */
    public long getMemberId() {
        return memberId;
    }

    /**
     * Set member id
     * @param memberId member's userid 
     */
    public void setMemberId(long memberId) {
        this.memberId = memberId;
    }

    /**
     * Get  full name
     * @return member's full name
     */
    public String getFullName() {
        return fullName;
    }

    /**
     * Set full name
     * @param fullName member's full name
     */
    public void setFullName(String fullName) {
        this.fullName = fullName;
    }

    /**
     * Get profile url
     * @return member's profile url
     */
    public String getProfileUrl() {
        return profileUrl;
    }

    /**
     * Set profile url
     * @param profileUrl member's profile url 
     */
    public void setProfileUrl(String profileUrl) {
        this.profileUrl = profileUrl;
    }

    /**
     * Get added time
     * @return time when member added
     */
    public long getAddedTime() {
        return addedTime;
    }

    /**
     * Set added time
     * @param addedTime time when member added
     */
    public void setAddedTime(long addedTime) {
        this.addedTime = addedTime;
    }

    /**
     * Get Fake user ID
     * @return the originalUserId
     */
    public long getFakeId() {
        return fakeId;
    }

    /**
     * Set Fake user ID
     * @param fakeId the Fake ID to set
     */
    public void setFakeId(long fakeId) {
        this.fakeId = fakeId;
    }

    /**
     * @return the roomId
     */
    public String getRoomId() {
        return roomId;
    }

    /**
     * @param roomId the roomId to set
     */
    public void setRoomId(String roomId) {
        this.roomId = roomId;
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
