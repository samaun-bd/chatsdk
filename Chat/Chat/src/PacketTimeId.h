/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PacketTimeId.h
 * Author: noman
 *
 * Created on March 20, 2016, 5:18 PM
 */

#ifndef PACKETTIMEID_H
#define PACKETTIMEID_H

#include <string>


namespace imsdk
{
class PacketTimeId {
public:
    PacketTimeId();
    virtual ~PacketTimeId();
    
    std::string packetId;
    long long packetTime1970;
    long long packetTime1582;
    
private:

};

}

#endif /* PACKETTIMEID_H */

