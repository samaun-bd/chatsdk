/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ringid.imsdk;

/**
 *
 * @author dipal
 */
public class MemberDTO {

    private long memberIdentity;
    private long ringId;
    private String fullName;
    private int status;
    private long addedBy;
    private long seenTime;

    public MemberDTO() {
    }

    public MemberDTO(long memberId, long ringId, String fullName, int status, long addedBy) {
        this.memberIdentity = memberId;
        this.ringId = ringId;
        this.fullName = fullName;
        this.status = status;
        this.addedBy = addedBy;
    }

    public void setAddedBy(long addedBy) {
        this.addedBy = addedBy;
    }

    public long getAddedBy() {
        return this.addedBy;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public int getStatus() {
        return this.status;
    }

    public void setFullName(String fullName) {
        this.fullName = fullName;
    }

    public String getFullName() {
        return this.fullName;
    }

    public void setMemberIdentity(long memberIdentity) {
        this.memberIdentity = memberIdentity;
    }

    public long getMemberIdentity() {
        return this.memberIdentity;
    }

    /**
     * @return the seenTime
     */
    public long getSeenTime() {
        return seenTime;
    }

    /**
     * @param seenTime the seenTime to set
     */
    public void setSeenTime(long seenTime) {
        this.seenTime = seenTime;
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
