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
public class InternetChecker {
    
    public static String ipListFilePath;
    
    public static InternetChecker internetChecker;
    
    public static InternetChecker getInstance()
    {
        if(internetChecker == null){
            internetChecker = new InternetChecker(ipListFilePath);
        }
        
        return internetChecker;
    }
    
    public native boolean checkInternetConnection();
    
    private InternetChecker(String ipListFilePath){
        ctor(ipListFilePath);
    }
    
    private native void ctor(String ipListFilePath);
    
    public static void init(String ipListFilePath)
    {
        InternetChecker.ipListFilePath = ipListFilePath;
    }

    static {
        System.loadLibrary("imsdk");
    }
}
