/* 
 * File:   ResendProcessor.h
 * Author: dipal
 *
 * Created on August 17, 2015, 11:52 AM
 */

#ifndef RESENDPROCESSOR_H
#define	RESENDPROCESSOR_H

#include "Processor.h"
#include "PacketDTO.h"
#include "Scheduler.h"
#include "Socket.h"
#include "Connection.h"
#include "ChatPacketBuilder.h"
#include "KeepaliveProcessor.h"
#include <queue>
#include <mutex>
#include <map>

namespace imsdk {
class ResendProcessor : public Thread {
public:

    enum DestinationType {
        Register=10,
        Chat=11,
        Offline=12
    };

    class ResendPacket {
    public:

        ResendPacket() {
        }

        ResendPacket(
                std::string &packetId,
                std::shared_ptr< ByteArray> &byteArray,
                std::shared_ptr< PacketDTO> packet,
                std::shared_ptr< ChatConnection> connection,
                DestinationType destinationType,
                int resendCount = 1)
        :
                packet(packet),
                byteArray(byteArray),
                packetId(packetId),
                resendCount(resendCount),
                connection(connection),
                destinationType(destinationType)
        {
        }

        virtual ~ResendPacket() {

        }

        std::shared_ptr< PacketDTO> packet{nullptr};
        std::shared_ptr< ByteArray> byteArray{nullptr};
        std::string packetId;
        int resendCount{0};
        std::shared_ptr< ChatConnection> connection{nullptr};
        DestinationType destinationType;
        bool isWaitingForPresence{false};
        int waitingTimeForPresence{0};
        bool isWaitingForServerUpdate{false};
        int waitingTimeForServerUpdate{0};
        bool alreadyCheckedForPresence{false};
        int timeInQ{0};
    };
    
    virtual ~ResendProcessor();

    static ResendProcessor& getInstance();


    void addResendPacket(ResendPacket resendPacket);
    std::shared_ptr< PacketDTO> getPacketDTO(std::string &packetId);
    void removePacket(const std::string &packetID);
	void updatePendingDestination(UserIdentity userId, UserIdentity friendId, int presence);
	void updatedServerAddress(UserIdentity userId, UserIdentity friendId);
	void updateConnection(UserIdentity userId, UserIdentity friendId, std::shared_ptr< ChatConnection> &connection);
    void updateGroupConnection(GroupIdentity groupId, std::shared_ptr< ChatConnection> &connection);
    void updateOfflineServer(std::string offlineServerAddress, int offlineServerPort);
    bool isExistInResendPacketMap(const std::string &packetID);
	void expirePendingMessagesForFriend(UserIdentity userId, UserIdentity friendId);
    void expirePendingMessagesForGroup(GroupIdentity groupId);
    void clear();
	std::vector<std::string> getFriendResendPacket(UserIdentity userId);
    std::vector<std::string> getGroupResendPacket();
    void runner();
    
    void processResendTasks();
    //now resend proc will call in every 2 seconds
    const static int maxResend{5};
    const static int maxTimeInQ{45};//90/2
    const static int maxWaitingTimeForPresence{8};//15/2
    const static int maxWaitingTimeForServerUpdate{8};//15/2

private:
    ResendProcessor();
    std::map<std::string, ResendPacket> resendPacketMap;
    std::mutex resendMapMutex;
    std::shared_ptr< ChatPacketBuilder> packetBuilder{nullptr};
};
}

#endif	/* RESENDPROCESSOR_H */

