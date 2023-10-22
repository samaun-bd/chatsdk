/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ringid.imsdk;

/**
 *
 * @author towhid
 */
public class GroupInformation {
    private long groupId;
    private String registerServerIp;
    private int registerServerPort;
    private int bindingPort;
    private long lastActivityTime;

    public GroupInformation(long groupId, String registerServerIp, int registerServerPort, int bindingPort, long lastActivityTime) {
        this.groupId = groupId;
        this.registerServerIp = registerServerIp;
        this.registerServerPort = registerServerPort;
        this.bindingPort = bindingPort;
        this.lastActivityTime = lastActivityTime;
    }

    /**
     * @return the registerServerIp
     */
    public String getRegisterServerIp() {
        return registerServerIp;
    }

    /**
     * @param registerServerIp the registerServerIp to set
     */
    public void setRegisterServerIp(String registerServerIp) {
        this.registerServerIp = registerServerIp;
    }

    /**
     * @return the registerServerPort
     */
    public int getRegisterServerPort() {
        return registerServerPort;
    }

    /**
     * @param registerServerPort the registerServerPort to set
     */
    public void setRegisterServerPort(int registerServerPort) {
        this.registerServerPort = registerServerPort;
    }

    /**
     * @return the bindingPort
     */
    public int getBindingPort() {
        return bindingPort;
    }

    /**
     * @param bindingPort the bindingPort to set
     */
    public void setBindingPort(int bindingPort) {
        this.bindingPort = bindingPort;
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
     * @return the lastActivityTime
     */
    public long getLastActivityTime() {
        return lastActivityTime;
    }

    /**
     * @param lastActivityTime the lastActivityTime to set
     */
    public void setLastActivityTime(long lastActivityTime) {
        this.lastActivityTime = lastActivityTime;
    }
    
    
}
