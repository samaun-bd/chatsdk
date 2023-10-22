/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ringid.imsdk;

import java.util.ArrayList;

/**
 * RoomDTO will be returned when getRoomList or searchRoomList API is called.
 * It will contain roomId, roomName and roomPictureUrl
 * @author towhid
 */
public class RoomDTO {
    
    private String roomId;
    private String roomName;
    private String roomPictureUrl;
    private int numberOfMember;
    private ArrayList<SDKMessageDTO> roomMesageList;
            
    public RoomDTO() {
    }

    /**
     * @param roomId RoomId
     * @param roomName Name of the room
     * @param roomPictureUrl Picture URL of the room
     * @param numberOfMember Number of member in the room
     * @param publicChatMessageDTOs List of publicChatMessageDTOs
     */
    public RoomDTO(String roomId, String roomName, String roomPictureUrl, int numberOfMember, ArrayList<SDKMessageDTO> publicChatMessageDTOs) {
        this.roomId = roomId;
        this.roomName = roomName;
        this.roomPictureUrl = roomPictureUrl;
        this.numberOfMember = numberOfMember;
        this.roomMesageList = publicChatMessageDTOs;
    }
    
    /**
     * Get Room ID
     * @return room identity
     */
    public String getRoomId() {
        return roomId;
    }

    /**
     * Set Room ID
     * @param roomId room identity
     */
    public void setRoomId(String roomId) {
        this.roomId = roomId;
    }

    /**
     * Get Room Name
     * @return room name
     */
    public String getRoomName() {
        return roomName;
    }

    /**
     * Set Room Name
     * @param roomName room name 
     */
    public void setRoomName(String roomName) {
        this.roomName = roomName;
    }

    /**
     * Get Room Url
     * @return room picture url
     */
    public String getRoomPictureUrl() {
        return roomPictureUrl;
    }

    /**
     * Set Room Url
     * @param roomPictureUrl picture url 
     */
    public void setRoomPictureUrl(String roomPictureUrl) {
        this.roomPictureUrl = roomPictureUrl;
    }

    /**
     * get Room Message List
     * @return roomMessageList
     */
    public ArrayList<SDKMessageDTO> getRoomMesageList() {
        return roomMesageList;
    }

    /**
     * set Room Message List
     * @param roomMesageList room message List 
     */
    public void setRoomMesageList(ArrayList<SDKMessageDTO> roomMesageList) {
        this.roomMesageList = roomMesageList;
    }

    /**
     * @return the numberOfMember
     */
    public int getNumberOfMember() {
        return numberOfMember;
    }

    /**
     * @param numberOfMember the numberOfMember to set
     */
    public void setNumberOfMember(int numberOfMember) {
        this.numberOfMember = numberOfMember;
    }

}
