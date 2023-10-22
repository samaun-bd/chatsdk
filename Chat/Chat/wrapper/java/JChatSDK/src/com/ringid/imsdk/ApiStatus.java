/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ringid.imsdk;

/**
 * API Status will be returned when an API is called. It will contain two variables. PacketId and error code. The 
 * values of error code are given bellow.
 * <table summary="Api error codes">
 * <tr><td style="width: 25%">0</td><td>NO_ERROR</td></tr>
 * <tr><td>1</td><td>PARSING_FAILED</td></tr>
 * <tr><td>2</td><td>CONNECTION_NOT_FOUND</td></tr>
 * <tr><td>3</td><td>FAILED_TO_SEND</td></tr>
 * <tr><td>4</td><td>SESSION_ALREADY_EXISTS</td></tr>
 * <tr><td>5</td><td>PACKET_BUILDER_ERROR</td></tr>
 * <tr><td>6</td><td>SOCK_ERROR</td></tr>
 * </table>
 * 
 * Note: The Packet id can or cannot exist depending on the API.
 * @author dipal
 */
public class ApiStatus {

    private String packetId;
    private int chatError;

    /**
     * 
     * @param packetId Corresponding packetId
     * @param chatError Error code
     */
    public ApiStatus(String packetId, int chatError) {
        this.packetId = packetId;
        this.chatError = chatError;
    }

    /**
     * Get the packet id generated from SDK.
     * @return Packet id
     */
    public String getPacketId() {
        return packetId;
    }

    /**
     * Get the error code. If there is no error the value will be 0.
     * @return Packet id
     */
    public int getErrorCode() {
        return chatError;
    }

}
