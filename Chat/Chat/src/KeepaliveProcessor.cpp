/* 
 * File:   KeepaliveProcessor.cpp
 * Author: dipal
 * 
 * Created on August 23, 2015, 4:58 PM
 */

#include <mutex>

#include "KeepaliveProcessor.h"
#include "ResourceManager.h"
#include "Logger.h"
#include "EventProcessor.h"
#include "ResendProcessor.h"
#include "PacketReceiver.h"

#define module "KeepAliveProc"

namespace imsdk {
KeepaliveProcessor::KeepaliveProcessor() {
    this->setThreadName("IM_KA_PROC");
    packetBuilder = std::make_shared<ChatPacketBuilder>();
    
}

KeepaliveProcessor::~KeepaliveProcessor() {
}

KeepaliveProcessor& KeepaliveProcessor::getInstance()
{
    static KeepaliveProcessor keepaliveProcessor;
    return keepaliveProcessor;
}

void KeepaliveProcessor::addFriendKeepalivePacket(UserIdentity userId, UserIdentity friendId, OnlineStatus onlineStatus, std::shared_ptr< KeepalivePacket> friendKeepalivePacket)
{
    friendKeepaliveMutex.lock();

	auto outerIt = friendKeepaliveMap.find(userId);
	if (outerIt != friendKeepaliveMap.end())
	{
		(*outerIt).second[friendId] = { userId, friendId, onlineStatus, friendKeepalivePacket };
	}
	else
	{
		friendKeepaliveMap[userId][friendId] = { userId, friendId, onlineStatus, friendKeepalivePacket };
	}
    
    friendKeepaliveMutex.unlock();
}

void KeepaliveProcessor::addPublicRoomKeepalivePacket(RoomIdentity roomId, std::shared_ptr< KeepalivePacket> publicRoomKeepalivePacket)
{
    publicRoomKeepaliveMutex.lock();
    
    publicRoomKeepaliveMap[roomId] = { roomId, publicRoomKeepalivePacket, true };
    
    publicRoomKeepaliveMutex.unlock();
}

void KeepaliveProcessor::addGroupKeepalivePacket(GroupIdentity groupId, std::shared_ptr< KeepalivePacket> groupKeepalivePacket)
{
    long long serverSyncedTime = ResourceManager::getInstance().getServerSyncedTime();
    groupKeepaliveMutex.lock();
    
    groupKeepaliveMap[groupId] = {groupId, serverSyncedTime, groupKeepalivePacket};
    
    groupKeepaliveMutex.unlock();
}

void KeepaliveProcessor::addLiveStreamChatKeepalivePacket(UserIdentity publisherId, std::shared_ptr< KeepalivePacket> liveStreamChatKeepalivePacket)
{
    liveStreamChatKeepaliveMutex.lock();
    
    liveStreamChatKeepaliveMap[publisherId] = {publisherId, liveStreamChatKeepalivePacket};
    
    liveStreamChatKeepaliveMutex.unlock();
}

KeepaliveProcessor::GroupKeepalivePacket KeepaliveProcessor::getGroupKeepalivePacket(GroupIdentity groupId)
{
    KeepaliveProcessor::GroupKeepalivePacket groupKeepalivePacket;
    groupKeepaliveMutex.lock();
    
    auto it = groupKeepaliveMap.find(groupId);
    if (it != groupKeepaliveMap.end())
    {
        groupKeepalivePacket = (*it).second;
    }
    
    groupKeepaliveMutex.unlock();
    
    return groupKeepalivePacket;
}

std::vector<KeepaliveProcessor::GroupKeepalivePacket> KeepaliveProcessor::getAllGroupKeepalivePacket()
{
    std::vector<KeepaliveProcessor::GroupKeepalivePacket> groupKeepaliveList;
    
    groupKeepaliveMutex.lock();
    
    for (auto it = groupKeepaliveMap.begin(); it!=groupKeepaliveMap.end(); it++)
    {
        groupKeepaliveList.push_back((*it).second);
    }
    
    groupKeepaliveMutex.unlock();
    
    return groupKeepaliveList;
}

void KeepaliveProcessor::removeFriendKeepalive(UserIdentity userId, UserIdentity friendId)
{
    friendKeepaliveMutex.lock();
    
	auto outerIt = friendKeepaliveMap.find(userId);
	if (outerIt != friendKeepaliveMap.end())
	{
		std::unordered_map<UserIdentity, FriendKeepalivePacket> &innerMap = (*outerIt).second;
		auto it = innerMap.find(friendId);
		if (it != innerMap.end())
		{
			innerMap.erase(it);
		}

		if (innerMap.size() == 0)
			friendKeepaliveMap.erase(outerIt);
	}

    friendKeepaliveMutex.unlock();
}

void KeepaliveProcessor::removeGroupKeepalive(GroupIdentity groupId)
{
    groupKeepaliveMutex.lock();
    
    auto it = groupKeepaliveMap.find(groupId);
    if (it!=groupKeepaliveMap.end())
    {
        groupKeepaliveMap.erase(it);
    }
    
    groupKeepaliveMutex.unlock();
}

void KeepaliveProcessor::removePublicRoomKeepalive(RoomIdentity roomId){
    
    publicRoomKeepaliveMutex.lock();
    
    auto it = publicRoomKeepaliveMap.find(roomId);
    if (it!=publicRoomKeepaliveMap.end())
    {
        publicRoomKeepaliveMap.erase(it);
    }
    
    publicRoomKeepaliveMutex.unlock();
}

void KeepaliveProcessor::removeLiveStreamChatKeepalive(UserIdentity publisherId)
{
    liveStreamChatKeepaliveMutex.lock();
    
    auto it = liveStreamChatKeepaliveMap.find(publisherId);
    if (it!=liveStreamChatKeepaliveMap.end())
    {
        liveStreamChatKeepaliveMap.erase(it);
    }
    
    liveStreamChatKeepaliveMutex.unlock();
}

void KeepaliveProcessor::resetFriendKeepalive(UserIdentity userId, UserIdentity friendId, int timerCount)
{
    friendKeepaliveMutex.lock();
    
	auto outerIt = friendKeepaliveMap.find(userId);
	if (outerIt != friendKeepaliveMap.end())
	{
		std::unordered_map<UserIdentity, FriendKeepalivePacket> &innerMap = (*outerIt).second;
		auto it = innerMap.find(friendId);
		if (it != innerMap.end())
		{
			(*it).second.keepalivePacket->resetTimer(timerCount);
		}
	}
    
    friendKeepaliveMutex.unlock();
}

void KeepaliveProcessor::resetGroupKeepalive(GroupIdentity groupId)
{
    long long lastActivityTime = ResourceManager::getInstance().gettime();
    groupKeepaliveMutex.lock();
    
    auto it = groupKeepaliveMap.find(groupId);
    if (it != groupKeepaliveMap.end())
    {
        (*it).second.keepalivePacket->resetTimer();
        (*it).second.lastActivityTime = lastActivityTime;
    }
    
    groupKeepaliveMutex.unlock();
}

void KeepaliveProcessor::resetPublicRoomKeepalive(RoomIdentity roomId)
{
    publicRoomKeepaliveMutex.lock();
    
    auto it = publicRoomKeepaliveMap.find(roomId);
    if (it != publicRoomKeepaliveMap.end())
    {
        (*it).second.keepalivePacket->resetTimer();
    }
    
    publicRoomKeepaliveMutex.unlock();
}

void KeepaliveProcessor::resetLiveStreamChatKeepalive(UserIdentity publisherId)
{
    liveStreamChatKeepaliveMutex.lock();
    
    auto it = liveStreamChatKeepaliveMap.find(publisherId);
    if (it != liveStreamChatKeepaliveMap.end())
    {
        (*it).second.keepalivePacket->resetTimer();
    }
    
    liveStreamChatKeepaliveMutex.unlock();
}

void KeepaliveProcessor::updateIsOnPublicChatScreen(RoomIdentity roomId, bool presence){
    
    publicRoomKeepaliveMutex.lock();
    
    auto it = publicRoomKeepaliveMap.find(roomId);
    
    if (it != publicRoomKeepaliveMap.end())
    {
        (*it).second.isOnPublicChatScreen = presence;
    }
    
    publicRoomKeepaliveMutex.unlock();
}

void KeepaliveProcessor::clear()
{
    friendKeepaliveMutex.lock();
    friendKeepaliveMap.clear();
    friendKeepaliveMutex.unlock();
    
    groupKeepaliveMutex.lock();
    groupKeepaliveMap.clear();
    groupKeepaliveMutex.unlock();
    
    publicRoomKeepaliveMutex.lock();
    publicRoomKeepaliveMap.clear();
    publicRoomKeepaliveMutex.unlock();
    
    liveStreamChatKeepaliveMutex.lock();
    liveStreamChatKeepaliveMap.clear();
    liveStreamChatKeepaliveMutex.unlock();
}

void KeepaliveProcessor::processKeepaliveTasks()
{
    std::vector<FriendKeepalivePacket> friendKeepaliveList;
    std::vector<FriendKeepalivePacket> friendConnectionToRemove;

    std::vector<GroupKeepalivePacket> groupKeepaliveList;
    std::vector<GroupKeepalivePacket> groupConnectionToRemove;
    
    std::vector<PublicRoomKeepalivePacket> publicRoomKeepaliveList;
    std::vector<PublicRoomKeepalivePacket> publicRoomConnectionToRemove;
    
    std::vector<LiveStreamChatKeepalivePacket> liveStreamChatKeepAliveList;
    
    if (friendKeepaliveMap.empty() && groupKeepaliveMap.empty() && publicRoomKeepaliveMap.empty() && liveStreamChatKeepaliveMap.empty())
    {
        noSesssionTime++;
        if (noSesssionTime==serviceIdleTimeout) 
        {
            EventProcessor::getInstance().push(ChatEvent(ChatEvent::SERVICE_IDLE_TIMEOUT, nullptr));
        }
    }
    else 
    {
        noSesssionTime=0;
    }
    
    friendKeepaliveMutex.lock();

	for (auto outerIt = friendKeepaliveMap.begin(); outerIt != friendKeepaliveMap.end(); )
	{
		std::unordered_map<UserIdentity, FriendKeepalivePacket> &innerMap = (*outerIt).second;

		for (auto it = innerMap.begin(); it != innerMap.end();)
		{
			if ((*it).second.keepalivePacket->getIdleTimes() > maxIdleShot)
			{
				friendConnectionToRemove.push_back((*it).second);
				it = innerMap.erase(it);
			}
			else
			{
				friendKeepaliveList.push_back((*it).second);
				it++;
			}
		}

		if (innerMap.size() == 0)
		{
			outerIt = friendKeepaliveMap.erase(outerIt);
		}
		else
		{
			outerIt++;
		}
	}

    /*for (auto it = friendKeepaliveMap.begin(); it!=friendKeepaliveMap.end(); )
    {
        if ((*it).second.keepalivePacket->getIdleTimes() > maxIdleShot)
        {
            friendConnectionToRemove.push_back((*it).second);
            it = friendKeepaliveMap.erase(it);
        }
        else 
        {
            friendKeepaliveList.push_back((*it).second);
            it++;
        }
    }*/

    friendKeepaliveMutex.unlock();

    for (std::vector<FriendKeepalivePacket>::size_type i = 0; i < friendKeepaliveList.size(); i++)
    {
        if(friendKeepaliveList[i].onlineStatus == OnlineStatus::ONLINE)
        {
            Log(module, "Sending keepalive for user: " << friendKeepaliveList[i].userId << " friend: "<<friendKeepaliveList[i].friendId);
            friendKeepaliveList[i].keepalivePacket->sendKeepalive();
        }
        else
        {
            Log(module, "Increasing keepalive for user: " << friendKeepaliveList[i].userId << " friend: "<<friendKeepaliveList[i].friendId);
            friendKeepaliveList[i].keepalivePacket->increaseKeepAliveCounter();
        }
    }

    for (std::vector<FriendKeepalivePacket>::size_type i = 0; i < friendConnectionToRemove.size(); i++)
    {
        Log(module, "Removing keepalive for user: " << friendConnectionToRemove[i].userId << " friend: "<<friendConnectionToRemove[i].friendId);
        
		auto friendInfo = ResourceManager::getInstance().getFriendInfo(friendConnectionToRemove[i].userId, friendConnectionToRemove[i].friendId);
        
        if (!friendInfo)
        {
            Log(module, "FriendInfo not found");
            continue;
        }
        
        if (!friendInfo->getIsFriendBlocked())
        {
            auto packetTimeId = ResourceManager::getInstance().generatePacketIdInSDK();
            
            auto connection = friendConnectionToRemove[i].keepalivePacket->getConnection();
            if (!connection)
            {
                Log(module, "Connection not found");
                continue;
            }
            
			auto builtPacket = packetBuilder->makeFriendUnregister(friendConnectionToRemove[i].userId, friendConnectionToRemove[i].friendId, packetTimeId.packetId, OnlineStatus::AWAY, OnlineMood::ALIVE);
            if (!builtPacket.byteArray)
            {
                Log(module, "Packet builder error");
                continue;
            }
            
            connection->sendToRegisterServer(builtPacket.byteArray);
            
            auto resendPacket = ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Register, 3);
            ResendProcessor::getInstance().addResendPacket(resendPacket);
        }
        
        auto packet = std::make_shared<PacketDTO>();
		packet->setUserIdentity(friendConnectionToRemove[i].userId);
		packet->setFriendIdentity(friendConnectionToRemove[i].friendId);
       
        EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_REGISTRATION_EXPIRED, packet));
        EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_REMOVE_DUPLICATE_INFO_FOR_FRIEND, packet));
		ResourceManager::getInstance().removeFriendInfo(friendConnectionToRemove[i].userId, friendConnectionToRemove[i].friendId);
    }

    friendKeepaliveList.clear();
    friendConnectionToRemove.clear();




    groupKeepaliveMutex.lock();
    for (auto it = groupKeepaliveMap.begin(); it!=groupKeepaliveMap.end(); )
    {
        if ((*it).second.keepalivePacket->getIdleTimes() > maxIdleShot)
        {
            groupConnectionToRemove.push_back((*it).second);
            it = groupKeepaliveMap.erase(it);
        }
        else 
        {
            groupKeepaliveList.push_back((*it).second);
            it++;
        }
    }
    groupKeepaliveMutex.unlock();

    for (std::vector<GroupKeepalivePacket>::size_type i = 0; i < groupKeepaliveList.size(); i++)
    {
        Log(module, "Sending keepalive for group "<<groupKeepaliveList[i].groupId);
        groupKeepaliveList[i].keepalivePacket->sendKeepalive();
    }

    for (std::vector<GroupKeepalivePacket>::size_type i = 0; i < groupConnectionToRemove.size(); i++)
    {
        Log(module, "Removing keepalive for group "<<groupConnectionToRemove[i].groupId);
        
        auto packetTimeId = ResourceManager::getInstance().generatePacketIdInSDK();
        
        auto connection = groupConnectionToRemove[i].keepalivePacket->getConnection();
        if (!connection)
        {
            Log(module, "Connection not found");
            continue;
        }
        
        auto builtPacket = packetBuilder->makeGroupUnregister(ResourceManager::getInstance().getUserId(), groupConnectionToRemove[i].groupId, packetTimeId.packetId, OnlineStatus::AWAY, OnlineMood::ALIVE);
        if (!builtPacket.byteArray)
        {
            Log(module, "Packet builder error");
            continue;
        }

        connection->sendToRegisterServer(builtPacket.byteArray);
        
        auto resendPacket = ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Register, 4);
        ResendProcessor::getInstance().addResendPacket(resendPacket);
        
        auto packet = std::make_shared<PacketDTO>();
        packet->setGroupId(groupConnectionToRemove[i].groupId);
        packet->setMessageDate(groupConnectionToRemove[i].lastActivityTime);
        ResourceManager::getInstance().removeGroupRegistration(groupConnectionToRemove[i].groupId);
        ResourceManager::getInstance().removeGroupConnection(groupConnectionToRemove[i].groupId);
        EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_REGISTRATION_EXPIRED, packet));
    }

    groupKeepaliveList.clear();
    groupConnectionToRemove.clear();
    
    publicRoomKeepaliveMutex.lock();
    for (auto it = publicRoomKeepaliveMap.begin(); it!=publicRoomKeepaliveMap.end(); )
    {
        RoomIdentity roomId = (*it).second.roomId;
        bool onPublicChatScreen = (*it).second.isOnPublicChatScreen;
        if ((*it).second.keepalivePacket->getIdleTimes() > maxIdleShot && !onPublicChatScreen)
        {
            publicRoomConnectionToRemove.push_back((*it).second);
            it = publicRoomKeepaliveMap.erase(it);
        }
        else 
        {
            publicRoomKeepaliveList.push_back((*it).second);
            it++;
        }
    }
    publicRoomKeepaliveMutex.unlock();

    for (std::vector<PublicRoomKeepalivePacket>::size_type i = 0; i < publicRoomKeepaliveList.size(); i++)
    {
        Log(module, "Sending keepalive for room "<<publicRoomKeepaliveList[i].roomId);
        publicRoomKeepaliveList[i].keepalivePacket->sendKeepalive();
    }

    for (std::vector<PublicRoomKeepalivePacket>::size_type i=0; i < publicRoomConnectionToRemove.size(); i++)
    {
        Log(module, "Removing keepalive for room "<<publicRoomConnectionToRemove[i].roomId);
        
        auto packet = std::make_shared<PacketDTO>();
        std::string roomId = publicRoomConnectionToRemove[i].roomId;
        packet->setRoomId(roomId);
        EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_CHAT_REGISTRATION_EXPIRED, packet));
        
        auto packetTimeId = ResourceManager::getInstance().generatePacketIdInSDK();
        auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
        if (!roomInfo)
        {
            Log(module, "Room Info Not Found for roomId: " + roomId);
            continue;
        }

        auto connection = roomInfo->getConnection();
        if (!connection)
        {
            Log(module, "Connection not found");
            continue;
        }

        auto builtPacket = packetBuilder->makePublicRoomUnregisterPacket(ResourceManager::getInstance().getUserId(), roomId, packetTimeId.packetId, roomInfo->getAnonymousId(), roomInfo->getRingId());
        if (!builtPacket.byteArray)
        {
            Log(module, "Packet builder error");
            continue;
        }

        connection->sendToRegisterServer(builtPacket.byteArray);
        connection->sendToRegisterServer(builtPacket.byteArray);
        connection->sendToRegisterServer(builtPacket.byteArray);
        
        ResourceManager::getInstance().removeRoomInfo(roomId);
    }

    publicRoomKeepaliveList.clear();
    publicRoomConnectionToRemove.clear();
    
    liveStreamChatKeepaliveMutex.lock();
    for (auto it = liveStreamChatKeepaliveMap.begin(); it!=liveStreamChatKeepaliveMap.end(); )
    {
        liveStreamChatKeepAliveList.push_back((*it).second);
        it++;
    }
    liveStreamChatKeepaliveMutex.unlock();

    for (std::vector<LiveStreamChatKeepalivePacket>::size_type i = 0; i < liveStreamChatKeepAliveList.size(); i++)
    {
        Log(module, "Sending keepalive for live stream chat, publisherID: "<<liveStreamChatKeepAliveList[i].publisherId);;
        liveStreamChatKeepAliveList[i].keepalivePacket->sendKeepalive();
    }

    liveStreamChatKeepAliveList.clear();
}

void KeepaliveProcessor::runner()
{
#ifdef IMSDK_LOG
#ifdef __APPLE__
    pthread_setname_np(getThreadName().c_str());
#endif
#endif

    while (isRunning())
    {
        sleepTime++;
#ifndef WINDOWS_PHONE_8
        std::this_thread::sleep_for(std::chrono::milliseconds(keepaliveDuration*1000));
#else
        Sleep(keepaliveDuration*1000);
#endif
        if ((sleepTime % 15) != 0) continue;
        processKeepaliveTasks();
    }
}
}
