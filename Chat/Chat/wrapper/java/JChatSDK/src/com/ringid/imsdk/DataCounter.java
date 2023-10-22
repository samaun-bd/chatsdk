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
public class DataCounter {
    private long dataSent;
    private long dataReceived;

    public DataCounter(){
        
    }
    
    public DataCounter(long dataSent, long dataReceived){
        this.dataSent = dataSent;
        this.dataReceived = dataReceived;
    }
    /**
     * @return the dataSent
     */
    public long getDataSent() {
        return dataSent;
    }

    /**
     * @return the dataReceived
     */
    public long getDataReceived() {
        return dataReceived;
    }
}
