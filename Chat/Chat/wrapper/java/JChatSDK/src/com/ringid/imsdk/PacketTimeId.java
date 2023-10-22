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
public class PacketTimeId {
    private String packetId;
    private long time1970;
    private long time1582;

    public PacketTimeId(String packetId, long time1970, long time1582) {
        this.packetId = packetId;
        this.time1970 = time1970;
        this.time1582 = time1582;
    }
    
    public String getPacketId() {
        return packetId;
    }

    public void setPacketId(String packetId) {
        this.packetId = packetId;
    }

    public long getTime1970() {
        return time1970;
    }

    public void setTime1970(long time1970) {
        this.time1970 = time1970;
    }

    public long getTime1582() {
        return time1582;
    }

    public void setTime1582(long time1582) {
        this.time1582 = time1582;
    }
}
