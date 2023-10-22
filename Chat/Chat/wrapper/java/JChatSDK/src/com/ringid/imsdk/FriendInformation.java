/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ringid.imsdk;

/**
 * Friend Information will be returned when getFriendInformation function of the API is called. It will contain following five variables for any given friendId
 * registerServerAddress, registerServerPort, chatServerPort, status, mood
 * @author S M Towhidul Islam
 */
public class FriendInformation {

    private String friendRegisterServerAddress;
    private int friendRegisterServerPort;
    private int friendChatServerPort;
    private int friendStatus;
    private int friendMood;
    private int friendDeviceType;
    private boolean blockStatus;
    private String friendName;
    private String friendUrl;
    private int profileType;

    /**
     * @param registerServerAddress Register server address
     * @param registerServerPort Register Server Port
     * @param chatServerPort Chat server port
     * @param deviceType Device Type
     * @param status Status
     * @param mood Mood
     * @param blockStatus Block status
     * @param friendName FriendName
     * @param friendUrl Friend profile url
     */
    public FriendInformation(String registerServerAddress, int registerServerPort, int chatServerPort, int deviceType, int status, int mood, boolean blockStatus, String friendName, String friendUrl, int profileType) {
        this.friendRegisterServerAddress = registerServerAddress;
        this.friendRegisterServerPort = registerServerPort;
        this.friendChatServerPort = chatServerPort;
        this.friendStatus = status;
        this.friendMood = mood;
        this.friendDeviceType = deviceType;
        this.friendName = friendName;
        this.friendUrl = friendUrl;
        this.profileType = profileType;
    }
    
    /**
     * Get Register server address
     * @return friendRegisterServerAddress
     */
    public String getFriendRegisterServerAddress(){
        return friendRegisterServerAddress;
    }
    
    /**
     * Get Register Server Port
     * @return friendRegisterServerPort
     */
    public int getFriendRegisterServerPort(){
        return friendRegisterServerPort;
    }
    
    /**
     * Get Chat server port
     * @return friendChatServerPort
     */
    public int getFriendChatServerPort(){
        return friendChatServerPort;
    }
    
    /**
     * Get Status
     * @return friendStatus
     */
    public int getFriendStatus(){
        return friendStatus;
    }

    /**
     * Get Mood
     * @return friendMood
     */
    public int getFriendMood(){
        return friendMood;
    }

    /**
     * @return the friendDeviceType
     */
    public int getFriendDeviceType() {
        return friendDeviceType;
    }

    /**
     * @param friendDeviceType the friendDeviceType to set
     */
    public void setFriendDeviceType(int friendDeviceType) {
        this.friendDeviceType = friendDeviceType;
    }

    /**
     * @return the blockStatus
     */
    public boolean getBlockStatus() {
        return blockStatus;
    }

    /**
     * @return the friendName
     */
    public String getFriendName() {
        return friendName;
    }

    /**
     * @return the friendUrl
     */
    public String getFriendUrl() {
        return friendUrl;
    }

    /**
     * @return the profileType
     */
    public int getProfileType() {
        return profileType;
    }

}
