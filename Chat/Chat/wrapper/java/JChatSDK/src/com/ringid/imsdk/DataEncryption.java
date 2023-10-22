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
public class DataEncryption {
    
    public static native byte[] encryptData(byte[] data, byte[] key, int startIndex);
    public static native byte[] decryptData(byte[] data, byte[] key, int startIndex);
    public static native String getSessionlessKey(String ipAddress, long ringId);

    static {
        System.loadLibrary("imsdk");
    }
}
