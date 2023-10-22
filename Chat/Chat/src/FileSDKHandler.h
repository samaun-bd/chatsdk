/* 
 * File:   FileSDKHandler.h
 * Author: root
 *
 * Created on December 29, 2015, 1:12 PM
 */

#ifndef FILESDKHANDLER_H
#define	FILESDKHANDLER_H

#include<iostream>
//#include "IPVConnectivityDLL.h"
#include "EventProcessor.h"



//void notifierForFileTransfer(int eventType, IPVLongType fileID, IPVLongType friendID, IPVLongType iOffSet, IPVLongType receivedLength, double iSpeed) {
//  
//    Log("FSDKCallBack", "call back event type:"<<eventType<<" FileID: "<<fileID);
//    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();
//    
//    switch(eventType)
//    {
//        case FILE_TRANSFER_PROGRESS:
//            packet->setFileIdentity(fileID);
//            packet->setFileOffset(iOffSet);
//            packet->setReceivedBytes(receivedLength);
//            packet->setFriendIdentity(friendID);
//            EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_FILE_TRANSFER_PROGRESS, packet));
//            break;
//            
//        case FILE_TRANSFER_COMPLETED:
//            packet->setFileIdentity(fileID);
//            packet->setFileOffset(iOffSet);
//            packet->setReceivedBytes(receivedLength);
//            packet->setFriendIdentity(friendID);
//            EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_FILE_TRANSFER_COMPLETED, packet));
//            break;
//            
//        case FILE_TRANSFER_CANCELLED:
//            packet->setFileIdentity(fileID);
//            packet->setFileOffset(iOffSet);
//            packet->setReceivedBytes(receivedLength);
//            packet->setFriendIdentity(friendID);
//            EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_FILE_TRANSFER_CANCELLED, packet));
//            break;
//            
//        case FILE_TRANSFER_FAILED:
//            packet->setFileIdentity(fileID);
//            packet->setFileOffset(iOffSet);
//            packet->setReceivedBytes(receivedLength);
//            packet->setFriendIdentity(friendID);
//            EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_FILE_TRANSFER_FAILED, packet));
//            break;
//            
//        default:
//            break;
//    }
//
//}


#endif	/* FILESDKHANDLER_H */

