/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ringid.imsdk;

/**
 * File chunk range. From and to index for a chunk
 * @author dipal
 */
public class FileChunk {
    private int indexFrom;
    private int indexTo;

    /**
     * Default constructor
     */
    public FileChunk() {
    }

    /**
     * Constructor with from and to index.
     * @param indexFrom starting index of chunk
     * @param indexTo ending index of chunk
     */
    public FileChunk(int indexFrom, int indexTo) {
        this.indexFrom = indexFrom;
        this.indexTo = indexTo;
    }
    
    /**
     * Set starting index.
     * @param indexFrom starting index
     */
    public void setIndexFrom(int indexFrom) {
        this.indexFrom = indexFrom;
    }
    
    /**
     * Get starting index.
     * @return starting index
     */
    public int getIndexFrom() {
        return this.indexFrom;
    }
    
    /**
     * Set ending index.
     * @param indexTo ending index
     */
    public void setIndexTo(int indexTo) {
        this.indexTo = indexTo;
    }
    
    /**
     * Get ending index.
     * @return ending index
     */
    public int getIndexTo() {
        return this.indexTo;
    }    
}
