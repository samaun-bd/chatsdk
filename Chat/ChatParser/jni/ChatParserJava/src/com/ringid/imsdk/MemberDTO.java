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
    private String fullName;
    private int status;
    private long addedBy;

    public MemberDTO() {
    }

    public MemberDTO(long memberIdentity, String fullName, int status, long addedBy) {
        this.memberIdentity = memberIdentity;
        this.fullName = fullName;
        this.status = status;
        this.addedBy = addedBy;
    }

    
    /**
     * Get member identity. The user identity of this member
     * @return the user identity of corresponding member
     */
    public long getMemberIdentity() {
        return memberIdentity;
    }

    /**
     * Set member identity. The user identity of the member
     * @param memberIdentity the user identity of the member
     */
    public void setMemberIdentity(long memberIdentity) {
        this.memberIdentity = memberIdentity;
    }

    /**
     * Get full name. Get the full name of the member
     * @return the full name of the member
     */
    public String getFullName() {
        return fullName;
    }

    /**
     * Set full name. Set the full name of the member
     * @param fullName the full name of the member
     */
    public void setFullName(String fullName) {
        this.fullName = fullName;
    }

    /**
     * Get the status. Get the administrative status of this member to the group
     * @return the status of member
     */
    public int getStatus() {
        return status;
    }

    /**
     * Set the status. Set the administrative status of this member to the group
     * @param status the status of member
     */
    public void setStatus(int status) {
        this.status = status;
    }

    /**
     * Get added by userid. Get the user identity of user who added this member to the corresponding group
     * @return the user who added this member
     */
    public long getAddedBy() {
        return addedBy;
    }

    /**
     * Set added by userid. Set the user identity of user who added this member to the corresponding group
     * @param addedBy the addedBy to set
     */
    public void setAddedBy(long addedBy) {
        this.addedBy = addedBy;
    }
}
