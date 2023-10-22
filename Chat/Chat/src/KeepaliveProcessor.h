/* 
 * File:   KeepaliveProcessor.h
 * Author: dipal
 *
 * Created on August 23, 2015, 4:57 PM
 */

#ifndef KEEPALIVEPROCESSOR_H
#define	KEEPALIVEPROCESSOR_H

#include "KeepalivePacket.h"
#include "Thread.h"
#include "ChatPacketBuilder.h"
#include <unordered_map>
#include <mutex>


namespace imsdk {
class KeepaliveProcessor : public Thread {
public:
    
    struct FriendKeepalivePacket {
		UserIdentity userId;
		UserIdentity friendId;
        OnlineStatus onlineStatus;
        std::shared_ptr< KeepalivePacket> keepalivePacket;
    };
    
    struct GroupKeepalivePacket {
        GroupIdentity groupId;
        long long lastActivityTime;
        std::shared_ptr< KeepalivePacket> keepalivePacket;
    };
    
    struct PublicRoomKeepalivePacket {
        RoomIdentity roomId;
        std::shared_ptr< KeepalivePacket> keepalivePacket;
        bool isOnPublicChatScreen;
    };
    
    struct LiveStreamChatKeepalivePacket {
        UserIdentity publisherId;
        std::shared_ptr< KeepalivePacket> keepalivePacket;
    };
    
    virtual ~KeepaliveProcessor();
    static KeepaliveProcessor& getInstance();
    
	void addFriendKeepalivePacket(UserIdentity userId, UserIdentity friendId, OnlineStatus onlineStatus, std::shared_ptr< KeepalivePacket> friendKeepalivePacket);
    void addGroupKeepalivePacket(GroupIdentity groupId, std::shared_ptr< KeepalivePacket> groupKeepalivePacket);
    void addPublicRoomKeepalivePacket(RoomIdentity roomId, std::shared_ptr< KeepalivePacket> publicRoomKeepalivePacket);
    void addLiveStreamChatKeepalivePacket(UserIdentity publisherId, std::shared_ptr< KeepalivePacket> liveStreamChatKeepalivePacket);
    
    GroupKeepalivePacket getGroupKeepalivePacket(GroupIdentity groupId);
    std::vector<GroupKeepalivePacket> getAllGroupKeepalivePacket();
    
	void removeFriendKeepalive(UserIdentity userId, UserIdentity friendId);
    void removeGroupKeepalive(GroupIdentity groupId);
    void removePublicRoomKeepalive(RoomIdentity roomId);
    void removeLiveStreamChatKeepalive(UserIdentity publisherId);
    
	void resetFriendKeepalive(UserIdentity userId, UserIdentity friendId, int timerCount = 0);
    void resetGroupKeepalive(GroupIdentity groupId);
    void resetPublicRoomKeepalive(RoomIdentity roomId);
    void resetLiveStreamChatKeepalive(UserIdentity publisherId);
    
    void updateIsOnPublicChatScreen(RoomIdentity roomId, bool presence);
    
    void clear();
    
    void runner();
    
    void processKeepaliveTasks();
    
    const static int maxIdleShot{9};//9
    const static int keepaliveDuration{1};//20
    const static int serviceIdleTimeout{3};//40 seconds
    int sleepTime{0};
    int noSesssionTime{0};
    
private:
    KeepaliveProcessor();
	std::unordered_map<UserIdentity, std::unordered_map<UserIdentity, FriendKeepalivePacket>> friendKeepaliveMap;
    std::unordered_map<GroupIdentity, GroupKeepalivePacket> groupKeepaliveMap;
    std::unordered_map<RoomIdentity, PublicRoomKeepalivePacket> publicRoomKeepaliveMap;
    std::unordered_map<UserIdentity, LiveStreamChatKeepalivePacket> liveStreamChatKeepaliveMap;
    
    std::mutex friendKeepaliveMutex;
    std::mutex groupKeepaliveMutex;
    std::mutex publicRoomKeepaliveMutex;
    std::mutex liveStreamChatKeepaliveMutex;
    
    std::shared_ptr< ChatPacketBuilder> packetBuilder;
};
}

#endif	/* KEEPALIVEPROCESSOR_H */
