/* 
 * File:   PacketProcessor.h
 * Author: dipal
 *
 * Created on August 17, 2015, 2:32 PM
 */

#ifndef PACKETPROCESSOR_H
#define	PACKETPROCESSOR_H

#include "Processor.h"
#include "PacketDTO.h"
#include "Scheduler.h"
#include "ByteArray.h"
#include "ChatParser.h"
#include "ChatPacketBuilder.h"
#include "DuplicateChecker.h"
#include "CloudNotificationHandler.h"
#include <unordered_map>

namespace imsdk {
class PacketProcessor : public Processor<ByteArray> {
public:
    virtual ~PacketProcessor();
    
    static PacketProcessor& getInstance();
    
    void clear();
    
    void run();
    
    void processPacketProcessTasks();

private:
    PacketProcessor();
    ChatParser parser;
    
    bool isNeedToRemoveResend();
    void handleBrokenChat(std::shared_ptr< PacketDTO> packet);
    void handleBrokenGroupChat(std::shared_ptr< PacketDTO> packet);
    void handleBrokenPublicRoomChat(std::shared_ptr< PacketDTO> packet);
    ByteArray handleBrokenDataPacket(std::shared_ptr< PacketDTO> packet);
    ByteArray handleOfflineBrokenPacket(std::shared_ptr< PacketDTO> packet);
    ByteArray handleRoomBrokenPacket(std::shared_ptr< PacketDTO> packet);
	void createSDKMessageDTOListFromPacket(std::shared_ptr< PacketDTO> packet, bool isFromHistoryBroken);
    std::vector<SDKMessageDTO> generateSDKMessageDTOListForGroupFromPacket(std::vector<std::shared_ptr< PacketDTO>> messageList);
    std::shared_ptr< ChatPacketBuilder> packetBuilder{nullptr};
    
    class BrokenMessage{
    public:
        std::string packetID;
        std::string completeMessage;
        int arrivedPacket;
        int totalPacket;
        
        bool isComplete()
        {
            if(arrivedPacket == totalPacket)
            {
                return true;
            }
            return false;
        }

        std::string getMessage()
        {
            for (std::vector<std::string>::size_type i = 0; i < message.size(); i++){
                completeMessage += message[i];
            }

            return completeMessage;
        }

        std::vector<std::string> message;
    };
    
    class BrokenPacket{
    public:
        std::string packetID;
        ByteArray complePacket;
        int arrivedPacket;
        int totalPacket;
        
        bool isComplete()
        {
            if(arrivedPacket == totalPacket)
            {
                return true;
            }
            return false;
        }

        ByteArray getTotalPacket()
        {
            for (std::vector<std::shared_ptr< ByteArray>>::size_type i = 0; i < packetData.size(); i++) {
                complePacket.appendByteArray(packetData[i]);
            }

            return complePacket;
        }

        std::vector<std::shared_ptr< ByteArray>> packetData;
    };
        
    std::unordered_map<std::string,BrokenMessage> brokenPacketMap;
    std::unordered_map<std::string,BrokenMessage> brokenGroupPacketMap;
    std::unordered_map<std::string,BrokenMessage> brokenPublicChatPacketMap;
    
    std::unordered_map<std::string,BrokenPacket> brokenData;
    std::unordered_map<std::string, std::shared_ptr<PacketDTO>> offlinePacketIdMap;
    
    DuplicateChecker duplicateChecker;
public:

    //std::unordered_map<FileIdentity,string> receiverFileTransferMap;
};
}

#endif	/* PACKETPROCESSOR_H */

