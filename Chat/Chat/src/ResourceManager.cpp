/*
* File:   ResourceManager.cpp
* Author: dipal
*
* Created on September 6, 2015, 12:21 PM
*/

#include <mutex>
#include <iostream>
#include "ResourceManager.h"
#include "Logger.h"
#include "PacketReceiver.h"
#include "PacketDTO.h"
#include "ChatEvent.h"
#include "EventProcessor.h"

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#define module "ResourceManager"
#define moduleFileSDK "FileSDKHandler"

namespace imsdk {
	ResourceManager::ResourceManager()
	{
		//: m_pFileTransferSDK(NULL){
		//    m_pFileTransferSDK = new CIPVConnectivityDLL();

	}

	ResourceManager::~ResourceManager() {
		//    PacketReceiver::getInstance().removeSocket(socket);
	}

	ResourceManager& ResourceManager::getInstance()
	{
		static ResourceManager resourceManager;
		return resourceManager;
	}

	void ResourceManager::addFriendInfo(std::shared_ptr< FriendInfo> friendInfo)
	{
		friendConnectionMutex.lock();

		auto outerIt = friendInfoMap.find(friendInfo->getUserId());
		if (outerIt != friendInfoMap.end())
		{
			(*outerIt).second[friendInfo->getFriendId()] = friendInfo;
		}
		else
		{
			friendInfoMap[friendInfo->getUserId()][friendInfo->getFriendId()] = friendInfo;
		}

		friendConnectionMutex.unlock();
	}

	std::shared_ptr< FriendInfo> ResourceManager::getFriendInfo(UserIdentity userId, UserIdentity friendid)
	{
		std::shared_ptr< FriendInfo> friendInfo = nullptr;
		friendConnectionMutex.lock();

		auto outerIt = friendInfoMap.find(userId);
		if (outerIt != friendInfoMap.end())
		{
			std::unordered_map<UserIdentity, std::shared_ptr< FriendInfo>> &innerMap = (*outerIt).second;
			auto it = innerMap.find(friendid);
			if (it != innerMap.end())
			{
				friendInfo = (*it).second;
			}
		}

		friendConnectionMutex.unlock();

		return friendInfo;
	}

	void ResourceManager::removeFriendInfo(UserIdentity userId, UserIdentity friendid)
	{
		friendConnectionMutex.lock();

		auto outerIt = friendInfoMap.find(userId);
		if (outerIt != friendInfoMap.end())
		{
			std::unordered_map<UserIdentity, std::shared_ptr< FriendInfo>> &innerMap = (*outerIt).second;
			auto it = innerMap.find(friendid);
			if (it != innerMap.end())
			{
				innerMap.erase(it);
			}

			if (innerMap.size() == 0)
				friendInfoMap.erase(outerIt);
		}

		friendConnectionMutex.unlock();
	}

	void ResourceManager::addRoomInfo(std::shared_ptr< RoomInfo> roomInfo)
	{
		roomConnectionMutex.lock();

		roomConnectionMap[roomInfo->getRoomId()] = roomInfo;

		roomConnectionMutex.unlock();
	}

	std::shared_ptr< RoomInfo> ResourceManager::getRoomInfo(RoomIdentity roomId)
	{
		std::shared_ptr< RoomInfo> roomInfo = nullptr;
		roomConnectionMutex.lock();

		auto it = roomConnectionMap.find(roomId);
		if (it != roomConnectionMap.end())
		{
			roomInfo = (*it).second;
		}

		roomConnectionMutex.unlock();

		return roomInfo;
	}

	void ResourceManager::removeRoomInfo(RoomIdentity roomId){
		roomConnectionMutex.lock();

		auto it = roomConnectionMap.find(roomId);
		if (it != roomConnectionMap.end())
		{
			roomConnectionMap.erase(it);
		}

		roomConnectionMutex.unlock();
	}

	void ResourceManager::updateFriendInfoStatus(UserIdentity userId, UserIdentity friendId, int status)
	{
		friendConnectionMutex.lock();

		auto fndInfo = friendInfoMap.find(userId);

		if (fndInfo != friendInfoMap.end())
		{
			std::unordered_map<UserIdentity, std::shared_ptr< FriendInfo>> &innerMap = (*fndInfo).second;

			for (auto it = innerMap.begin(); it != innerMap.end(); it++)
			{
				if ((*it).second->getFriendId() != friendId) continue;
				(*it).second->setStatus(status);
			}
		}

		friendConnectionMutex.unlock();
	}

	void ResourceManager::addGroupConnection(GroupIdentity groupid, std::shared_ptr< ChatConnection> &connection)
	{
		groupConnectionMutex.lock();

		groupConnectionMap[groupid] = connection;

		groupConnectionMutex.unlock();
	}

	std::shared_ptr< ChatConnection> ResourceManager::getGroupConnection(GroupIdentity groupid)
	{
		std::shared_ptr< ChatConnection> groupConnection = nullptr;

		groupConnectionMutex.lock();

		auto it = groupConnectionMap.find(groupid);
		if (it != groupConnectionMap.end())
		{
			groupConnection = (*it).second;
		}

		groupConnectionMutex.unlock();

		return groupConnection;
	}

	void ResourceManager::removeGroupConnection(GroupIdentity groupid)
	{
		groupConnectionMutex.lock();

		auto it = groupConnectionMap.find(groupid);
		if (it != groupConnectionMap.end())
		{
			groupConnectionMap.erase(it);
		}

		groupConnectionMutex.unlock();
	}

    void ResourceManager::addGroupRegistration(GroupIdentity groupid, long long registrationTime)
    {
        groupRegistrationMutex.lock();

        groupRegistrationMap[groupid] = registrationTime;

        groupRegistrationMutex.unlock();
    }

    long long ResourceManager::GetGroupRegistrationTime(GroupIdentity groupid)
    {
        long long groupRegistrationTime = 0;

        groupRegistrationMutex.lock();

        auto it = groupRegistrationMap.find(groupid);
        if (it != groupRegistrationMap.end())
        {
            groupRegistrationTime = (*it).second;
        }

        groupRegistrationMutex.unlock();

        return groupRegistrationTime;
    }

    void ResourceManager::removeGroupRegistration(GroupIdentity groupid)
    {
        groupRegistrationMutex.lock();

        auto it = groupRegistrationMap.find(groupid);
        if (it != groupRegistrationMap.end())
        {
            groupRegistrationMap.erase(it);
        }

        groupRegistrationMutex.unlock();
    }

	void ResourceManager::addLiveStreamChatInfo(std::shared_ptr< LiveStreamChatInfo> liveStreamChatInfo)
	{
		liveStreamChatConnectionMutex.lock();

		liveStreamChatInfoMap[liveStreamChatInfo->getPublisherId()] = liveStreamChatInfo;

		liveStreamChatConnectionMutex.unlock();
	}

	std::shared_ptr< LiveStreamChatInfo> ResourceManager::getLiveStreamChatInfo(UserIdentity publisherId)
	{
		std::shared_ptr< LiveStreamChatInfo> liveStreamInfo = nullptr;
		liveStreamChatConnectionMutex.lock();

		auto it = liveStreamChatInfoMap.find(publisherId);
		if (it != liveStreamChatInfoMap.end())
		{
			liveStreamInfo = (*it).second;
		}

		liveStreamChatConnectionMutex.unlock();

		return liveStreamInfo;
	}

	void ResourceManager::removeLiveStreamChatInfo(UserIdentity publisherId)
	{
		liveStreamChatConnectionMutex.lock();

		auto it = liveStreamChatInfoMap.find(publisherId);
		if (it != liveStreamChatInfoMap.end())
		{
			liveStreamChatInfoMap.erase(it);
		}

		liveStreamChatConnectionMutex.unlock();
	}

	void ResourceManager::createSocketIfNeeded()
	{
		if (!socket)
		{
			Log(module, "creating new socket ");
			socket = std::make_shared<UDPSocket>();
			PacketReceiver::getInstance().addSocket(socket);
		}
	}

	void ResourceManager::createOfflineConnectionIfNeeded()
	{
		if (!offlineConnection)
		{
			offlineConnection = std::make_shared<ChatConnection>(socket);
			offlineConnection->setOfflineServer(offlineServerAddress, offlinePort);
		}
	}

	void ResourceManager::setOfflineServer(std::string offlineServerAddress, int offlineServerPort)
	{
		this->offlineServerAddress = offlineServerAddress;
		this->offlinePort = offlineServerPort;
	}

    void ResourceManager::setAuthSessionID(std::string authSessionId)
    {
        this->authSessionID = authSessionId;
    }

    std::string ResourceManager::getAuthSessionID()
    {
        return this->authSessionID;
    }

	std::shared_ptr< ChatConnection> ResourceManager::getOfflineConnection()
	{
		return offlineConnection;
	}

	std::shared_ptr< UDPSocket> ResourceManager::getSocket()
	{
		return socket;
	}

	void ResourceManager::setAuthenticationServer(std::string authenticationServerAddress, int offlineServerPort)
	{
		this->authenticationServerAddress = authenticationServerAddress;
		this->authenticationServerPort = offlineServerPort;
	}

	std::string ResourceManager::getAuthenticationAddress()
	{
		return authenticationServerAddress;
	}

	int ResourceManager::getAuthenticationPort()
	{
		return authenticationServerPort;
	}

	void ResourceManager::setIsRunningServices(bool isRunning)
	{
		isRunningServices = isRunning;
	}
	bool ResourceManager::getIsRunningServices()
	{
		return isRunningServices;
	}

	void ResourceManager::addAnonymousUser(UserIdentity friendId, AnonymousUserIdentity anonymousUserId)
	{
		anonymousUserMutex.lock();

		anonymousUserMap[friendId] = anonymousUserId;

		anonymousUserMutex.unlock();
	}

	AnonymousUserIdentity ResourceManager::getAnonymousUser(UserIdentity friendId)
	{
		AnonymousUserIdentity anonymousUserId;
		anonymousUserMutex.lock();

		auto it = anonymousUserMap.find(friendId);
		if (it != anonymousUserMap.end())
		{
			anonymousUserId = (*it).second;
		}

		anonymousUserMutex.unlock();

		return anonymousUserId;
	}

	bool ResourceManager::isExistsAnonymousUser(UserIdentity friendId)
	{
		bool isExists = false;
		anonymousUserMutex.lock();

		auto it = anonymousUserMap.find(friendId);
		isExists = (it != anonymousUserMap.end());

		anonymousUserMutex.unlock();

		return isExists;
	}
	void ResourceManager::removeAnonymousUser(UserIdentity friendId)
	{
		anonymousUserMutex.lock();

		auto it = anonymousUserMap.find(friendId);
		if (it != anonymousUserMap.end())
		{
			anonymousUserMap.erase(it);
		}

		anonymousUserMutex.unlock();
	}

	void ResourceManager::clearSocket()
	{
		socket.reset();
	}

	void ResourceManager::clearOfflineConnection()
	{
		offlineConnection.reset();
	}

	void ResourceManager::clear()
	{
		friendConnectionMutex.lock();
		friendInfoMap.clear();
		friendConnectionMutex.unlock();

		groupConnectionMutex.lock();
        groupConnectionMap.clear();
        groupRegistrationMap.clear();
		groupConnectionMutex.unlock();

		roomConnectionMutex.lock();
		roomConnectionMap.clear();
		roomConnectionMutex.unlock();

		anonymousUserMutex.lock();
		anonymousUserMap.clear();
		anonymousUserMutex.unlock();
	}


	std::vector<UserIdentity> ResourceManager::getAllRegisteredFriendIDs(UserIdentity userId)
	{
		std::vector<UserIdentity> registeredFriendIds;

		friendConnectionMutex.lock();
		auto outerIt = friendInfoMap.find(userId);
		if (outerIt != friendInfoMap.end())
		{
			std::unordered_map<UserIdentity, std::shared_ptr< FriendInfo>> innerMap = (*outerIt).second;

			if (innerMap.size() > 0)
			{
				for (auto it = innerMap.begin(); it != innerMap.end(); it++)
				{
					registeredFriendIds.push_back((*it).second->getFriendId());
				}
			}
		}
		friendConnectionMutex.unlock();

		return registeredFriendIds;
	}


	std::vector<std::shared_ptr< FriendInfo>> ResourceManager::getAllFriendConnection()
	{
		std::vector<std::shared_ptr< FriendInfo>> friendConnections;

		friendConnectionMutex.lock();

		for (auto outerIt = friendInfoMap.begin(); outerIt != friendInfoMap.end(); outerIt++)
		{
			std::unordered_map<UserIdentity, std::shared_ptr< FriendInfo>> &innerMap = (*outerIt).second;

			for (auto it = innerMap.begin(); it != innerMap.end(); it++)
				friendConnections.push_back((*it).second);
		}

		friendConnectionMutex.unlock();

		return friendConnections;
	}

	std::vector<std::shared_ptr< GroupInfo>> ResourceManager::getAllGroupInfo()
	{
		std::vector<std::shared_ptr< GroupInfo>> groupConnections;

		groupConnectionMutex.lock();
		for (auto it = groupConnectionMap.begin(); it != groupConnectionMap.end(); it++)
		{
			std::shared_ptr< GroupInfo> groupInformation = std::make_shared<GroupInfo>();
			groupInformation->groupId = (*it).first;
			groupInformation->groupConnection = (*it).second;
			groupConnections.push_back(groupInformation);
		}
		groupConnectionMutex.unlock();

		return groupConnections;
	}

	std::vector<std::shared_ptr< RoomInfo>> ResourceManager::getAllRoomConnection()
	{
		std::vector<std::shared_ptr< RoomInfo>> roomConnections;

		roomConnectionMutex.lock();
		for (auto it = roomConnectionMap.begin(); it != roomConnectionMap.end(); it++)
		{
			roomConnections.push_back((*it).second);
		}
		roomConnectionMutex.unlock();

		return roomConnections;
	}

	void ResourceManager::setUserName(std::string userName) {
		this->userName = userName;
	}

	std::string ResourceManager::getUserName() {
		return userName;
	}

	void ResourceManager::setDeviceType(int deviceType) {
		this->deviceType = deviceType;
	}

	int ResourceManager::getDeviceType() {
		return deviceType;
	}

	//void ResourceManager::tryClearFileSession(IPVLongType friendId)
	//{
	//    Log(moduleFileSDK, "Trying calling Close Session");
	//    ResourceManager::getInstance().fileTransferSessionMutex.lock();
	//    
	//    int numberOfSession = ResourceManager::getInstance().fileTransferSession[friendId];
	//    numberOfSession--;
	//    if(numberOfSession == 0)
	//    {
	//        ResourceManager::getInstance().m_pFileTransferSDK->CloseSession(friendId, MediaType::IPV_MEDIA_FILE_TRANSFER);
	//    }
	//    
	//    ResourceManager::getInstance().fileTransferSessionMutex.unlock();
	//    Log(moduleFileSDK, "calling Close Session successful");
	//}

	std::string ResourceManager::toString(int x)
	{
		std::string s;
		std::stringstream out;
		out << x;
		s = out.str();

		return s;
	}

	std::string ResourceManager::toLongToString(long long x)
	{
		std::string s;
		std::stringstream out;
		out << x;
		s = out.str();

		return s;
	}

	long long ResourceManager::toStringToLong(std::string s)
	{
		std::stringstream out;
		out << s.c_str();

		long long returnValue;
		out >> returnValue;

		return returnValue;
	}

	int ResourceManager::toStringToInt(std::string s)
	{
		std::stringstream out;
		out << s.c_str();

		int returnValue;
		out >> returnValue;

		return returnValue;
	}

	void ResourceManager::setTimeDifference(long long timeDifference) {
		this->timeDifference = timeDifference;
	}

	long long ResourceManager::getTimeDifference() {
		return timeDifference;
	}

	std::pair<long long, long long> ResourceManager::gettimeUUID()
	{
		static long long last_uuid_time = 0; // On the heap!
		long long uuid_time = 0;
		long long currentTime;
#ifdef __MACH__
		clock_serv_t cclock;
		mach_timespec_t tp;
		host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
		clock_get_time(cclock, &tp);
		mach_port_deallocate(mach_task_self(), cclock);
		currentTime = ((long long)tp.tv_sec) * 1000 + ((long long)tp.tv_nsec) / 1000000;
		// Convert to 100-nanosecond intervals
		uuid_time = ((long long)tp.tv_sec) * 10000000;
		uuid_time = uuid_time + (((long long)tp.tv_nsec) / 100);
#elif _WIN32
		auto timeEpoch = std::chrono::system_clock::now().time_since_epoch();
		currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeEpoch).count();
		uuid_time = std::chrono::duration_cast<std::chrono::nanoseconds>(timeEpoch).count() / 100;
#else
		struct timespec tp;
		clock_gettime(CLOCK_REALTIME, &tp);
		currentTime = ((long long)tp.tv_sec) * 1000 + ((long long)tp.tv_nsec) / 1000000;
		// Convert to 100-nanosecond intervals
		uuid_time = ((long long)tp.tv_sec) * 10000000;
		uuid_time = uuid_time + (((long long)tp.tv_nsec) / 100);
#endif

		uuid_time = uuid_time + kNum_100nsec_1582_1970;

		if (uuid_time > last_uuid_time){
			last_uuid_time = uuid_time;
		}
		else {
			uuid_time = last_uuid_time + 1;
			last_uuid_time = uuid_time;
		}

		return{ currentTime, uuid_time };
	}

	void ResourceManager::setUserId(UserIdentity userId) {
		this->userId = userId;
	}

	UserIdentity ResourceManager::getUserId() {
		return this->userId;
	}

	void ResourceManager::setUserPageIdList(std::set<UserIdentity> pageIdList) {
		this->pageIdList = pageIdList;
	}

	std::set<UserIdentity> ResourceManager::getUserPageIdList() {
		return this->pageIdList;
	}

    bool ResourceManager::isUserPage(UserIdentity pageId) {
        return (!this->pageIdList.empty() && this->pageIdList.find(pageId) != this->pageIdList.end());
    }

	void ResourceManager::addNewPage(UserIdentity pageId) {
		if (this->pageIdList.find(pageId) == this->pageIdList.end())
			this->pageIdList.insert(pageId);
	}

	void ResourceManager::removePage(UserIdentity pageId) {
		if (this->pageIdList.find(pageId) != this->pageIdList.end())
			this->pageIdList.erase(pageId);
	}

	long long ResourceManager::gettime()
	{
		long long timeMili = 0;
#ifdef __MACH__
		clock_serv_t cclock;
		mach_timespec_t tp;
		host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
		clock_get_time(cclock, &tp);
		mach_port_deallocate(mach_task_self(), cclock);
		timeMili = ((long long)tp.tv_sec) * 1000 + ((long long)tp.tv_nsec) / 1000000;
#elif _WIN32
		auto timeEpoch = std::chrono::system_clock::now().time_since_epoch();
		timeMili = std::chrono::duration_cast<std::chrono::milliseconds>(timeEpoch).count();
#else
		struct timespec tp;
		clock_gettime(CLOCK_REALTIME, &tp);
		timeMili = ((long long)tp.tv_sec) * 1000 + ((long long)tp.tv_nsec) / 1000000;
#endif

		return timeMili;
	}

	long long ResourceManager::getServerSyncedTime()
	{
		return gettime() + getTimeDifference();
	}

	std::string ResourceManager::longToHex(unsigned long long val)
	{
		std::stringstream stream;
		stream << std::hex << val;
		return stream.str();
	}

	long long ResourceManager::hexToLong(std::string str){

		unsigned long long value;
		std::stringstream stream(str);
		stream >> std::hex >> value;
		return value;

	}

	std::string ResourceManager::padHex(unsigned long long l, size_t n) {
		std::string s = longToHex(l);

		while (s.length() < n) {
			s = "0" + s;
		}

		return s;
	}

	std::string ResourceManager::timeToUUID(unsigned long long ns100_intervals, UserIdentity userId)
	{
		uint32_t time_low = ns100_intervals & 0xffffffff;
		uint16_t time_mid = (ns100_intervals >> 32) & 0xffff;
		uint16_t time_hi_version = (ns100_intervals >> 48) & 0xfff;

		unsigned long long upper_ = 0;
		unsigned long long lower_ = 0;

		// Build the high 4 bytes.
		upper_ = (unsigned long long) time_low << 32;
		upper_ |= (unsigned long long) time_mid << 16;
		upper_ |= (unsigned long long) time_hi_version;

		lower_ |= userId;

		upper_ |= 0x0000000000001000;

		return
			padHex(((upper_ & 0xFFFFFFFF00000000L) >> 32) & 0xFFFFFFFFL, 8)
			+ "-" +
			padHex(((upper_ & 0xFFFF0000L) >> 16), 4)
			+ "-" +
			padHex((upper_ & 0x0000000000000000FFFFL), 4)
			+ "-" +
			padHex((((lower_ & 0xFFFF000000000000L) >> 48) & 0xFFFF), 4)
			+ "-" +
			padHex(lower_ & 0xFFFFFFFFFFFFL, 12);
	}

	long long ResourceManager::UUIDToTime(std::string UUID){

		std::vector<std::string> vc{ stringSplit(UUID, '-') };
		unsigned long long value = 0;

		if (vc.size() == 5) {
			value = (hexToLong(vc[0]) & 0x00000000FFFFFFFFL);

			value |= (hexToLong(vc[1]) << 32 & 0x0000FFFF00000000L);

			value |= (hexToLong(vc[2]) << 48 & 0x0FFF000000000000L);

			value -= kNum_100nsec_1582_1970;

			value /= 10000;
		}

		return value;

	}

	const std::vector<std::string> ResourceManager::stringSplit(const std::string& s, const char& c)
	{
		std::string buff{ "" };
		std::vector<std::string> vc;

		for (auto n : s)
		{
			if (n != c){
				buff += n;
			}
			else if (n == c && buff != "") {
				vc.push_back(buff);
				buff = "";
			}
		}

		if (buff != ""){
			vc.push_back(buff);
		}

		return vc;
	}

	PacketTimeId ResourceManager::generatePacketIdInSDK(UserIdentity userId)
	{
		PacketTimeId packetTimeId;

		auto timeUUID = ResourceManager::getInstance().gettimeUUID();
		unsigned long long ns100_intervals = (unsigned long long) timeUUID.second;
		ns100_intervals = ns100_intervals + (unsigned long long)ResourceManager::getInstance().getTimeDifference() * 10000;//gettime();

		packetTimeId.packetTime1582 = (long long)ns100_intervals;
		packetTimeId.packetTime1970 = timeUUID.first + ResourceManager::getInstance().getTimeDifference();

		//cout<<ns100_intervals<<" ";   
		packetTimeId.packetId = timeToUUID(ns100_intervals, (userId == 0 ? ResourceManager::getInstance().getUserId() : userId));
		return packetTimeId;
	}

	PacketTimeId ResourceManager::generatePacketIdInSDK(long long timeMili, UserIdentity userId)
	{
		PacketTimeId packetTimeId;

		unsigned long long ns100_intervals = timeMili * 10000 + kNum_100nsec_1582_1970;
		//ns100_intervals = ns100_intervals + (unsigned long long)ResourceManager::getInstance().getTimeDifference() * 10000;//gettime();

		packetTimeId.packetTime1582 = (long long)ns100_intervals;
        packetTimeId.packetTime1970 = timeMili; // +ResourceManager::getInstance().getTimeDifference();

		//cout<<ns100_intervals<<" ";   
		packetTimeId.packetId = timeToUUID(ns100_intervals, userId);
		return packetTimeId;
	}

	void ResourceManager::countNetworkData(){
		long long dataSent = ResourceManager::getInstance().getSocket()->getSocketDataSent();
		long long dataReceived = PacketReceiver::getInstance().getDataReceived();
		auto packet = std::make_shared<PacketDTO>();
		packet->setDataCounter({ dataSent, dataReceived });
		EventProcessor::getInstance().push(ChatEvent(ChatEvent::DATA_COUNTED, packet));
	}
	//std::vector<std::string> ResourceManager::StringParser(std::string message)
	//{
	//    std::vector<std::string> arr;
	//    int i;
	//    std::string temp;
	//    for(i=0 ;i<message.size();i++)
	//    {
	//        if(message.at(i) == '/')
	//        {
	//            arr.push_back(temp);
	//            temp.clear();
	//            continue;
	//        }
	//        temp.push_back(message.at(i));
	//    }
	//    arr.push_back(temp);
	//    return arr;
	//}
	//std::unordered_map<string,string> ResourceManager::fileNameParser(std::string str)
	//{
	//    std::unordered_map<string,string> parsedMap;
	//    std::string key, value;
	//    
	//    char modStr[str.size()];
	//   
	//    int startIndex = 0;
	//    int endIndex = 0;
	//    int count = 0;
	//    
	//    int j=0;
	//    bool canRemoveSpace = true;
	//   
	//    for(int i=0;i<str.size();i++)
	//    {
	//        if(str.at(i)=='\"')
	//        {
	//            canRemoveSpace = !canRemoveSpace;
	//        }
	//        
	//        if(str.at(i)==' ' && canRemoveSpace)
	//        {
	//            continue;
	//        }
	//        
	//        modStr[j++]=str.at(i);
	//        modStr[j]=0;
	//    }
	//
	//    std::string finalStr(modStr);
	//    
	//    for(int i=0;i<finalStr.length();i++)
	//    {
	//        if(finalStr.at(i)==':')
	//        {
	//            startIndex = endIndex = i-1;
	//            while(finalStr.at(startIndex-1)!='{' && finalStr.at(startIndex-1)!=',')
	//            {
	//                startIndex--;
	//            }
	//            key = finalStr.substr(startIndex+1,endIndex-startIndex-1);
	//            
	//            endIndex = startIndex = i+1;
	//            while(finalStr.at(endIndex+1)!='}' && finalStr.at(endIndex+1)!=',')
	//            {
	//                endIndex++;
	//            }
	//            
	//            if(finalStr.at(startIndex)=='\"')
	//                value = finalStr.substr(startIndex+1,endIndex-startIndex-1);
	//            else value = finalStr.substr(startIndex,endIndex-startIndex+1);
	//            
	//            parsedMap.insert(std::pair<string,string>(key,value));
	//        }
	//    }
	//    
	//    return parsedMap;
	//
	//}

	//std::string ResourceManager::mapToJson(std::unordered_map<string,string> parsedData)
	//{
	//    std::string jsonData;
	//    
	//    jsonData.append("{");
	//    
	//    for(auto i=parsedData.begin();i!=parsedData.end();i++)
	//    {
	//        if(i!=parsedData.begin())
	//        {
	//            jsonData.append(",");
	//        }
	//
	//        jsonData.append(i->first);
	//        jsonData.append(":");
	//        jsonData.append(i->second);
	//    }
	//    
	//    jsonData.append("}");
	//    
	//    return jsonData;
	//
	//}
	/*void ResourceManager::setFriendOfflineConnection(std::shared_ptr< ChatConnection> &connection)
	{
	friendOfflineConnection = connection;
	}

	std::shared_ptr< ChatConnection> ResourceManager::getFriendOfflineConnection()
	{
	return friendOfflineConnection;
	}*/


	void ResourceManager::setMediaTransferTmpDirPath(std::string mediaTransferTmpDirPath) {
		this->mediaTransferTmpDirPath = mediaTransferTmpDirPath;
	}

	std::string ResourceManager::getMediaTransferTmpDirPath() const {
		return mediaTransferTmpDirPath;
	}

	void ResourceManager::setAutoDownloadEnabled(bool autoDownloadEnabled) {
		this->autoDownloadEnabled = autoDownloadEnabled;
	}

	bool ResourceManager::isAutoDownloadEnabled() const {
		return autoDownloadEnabled;
	}

	void ResourceManager::setBaseDownloadUrl(std::string baseDownloadUrl) {
		this->baseDownloadUrl = baseDownloadUrl;
	}

	std::string ResourceManager::getBaseDownloadUrl() const {
		return baseDownloadUrl;
	}

	void ResourceManager::setBaseUploadUrl(std::string baseUploadUrl) {
		this->baseUploadUrl = baseUploadUrl;
	}

	std::string ResourceManager::getBaseUploadUrl() const {
		return baseUploadUrl;
	}

	void ResourceManager::setChatVideoDownloadPath(std::string chatVideoDownloadPath) {
		this->chatVideoDownloadPath = chatVideoDownloadPath;
	}

	std::string ResourceManager::getChatVideoDownloadPath() const {
		return chatVideoDownloadPath;
	}

	void ResourceManager::setChatAudioDownloadPath(std::string chatAudioDownloadPath) {
		this->chatAudioDownloadPath = chatAudioDownloadPath;
	}

	std::string ResourceManager::getChatAudioDownloadPath() const {
		return chatAudioDownloadPath;
	}

	void ResourceManager::setChatImageDownloadPath(std::string chatImageDownloadPath) {
		this->chatImageDownloadPath = chatImageDownloadPath;
	}

	std::string ResourceManager::getChatImageDownloadPath() const {
		return chatImageDownloadPath;
	}

	void ResourceManager::setSecretChatVideoDownloadPath(std::string secretChatVideoDownloadPath) {
		this->secretChatVideoDownloadPath = secretChatVideoDownloadPath;
	}

	std::string ResourceManager::getSecretChatVideoDownloadPath() const {
		return secretChatVideoDownloadPath;
	}

	void ResourceManager::setSecretChatAudioDownloadPath(std::string secretChatAudioDownloadPath) {
		this->secretChatAudioDownloadPath = secretChatAudioDownloadPath;
	}

	std::string ResourceManager::getSecretChatAudioDownloadPath() const {
		return secretChatAudioDownloadPath;
	}

	void ResourceManager::setSecretChatImageDownloadPath(std::string secretChatImageDownloadPath) {
		this->secretChatImageDownloadPath = secretChatImageDownloadPath;
	}

	std::string ResourceManager::getSecretChatImageDownloadPath() const {
		return secretChatImageDownloadPath;
	}

	void ResourceManager::setEncryptionDecryptionKey(std::shared_ptr<ByteArray> encryptionDecryptionKey) {
		this->encryptionDecryptionKey = encryptionDecryptionKey;
	}

	std::shared_ptr<ByteArray> ResourceManager::getEncryptionDecryptionKey() const {
		return encryptionDecryptionKey;
	}

	void ResourceManager::setLatestPublisherId(UserIdentity latestPublisherId) {
		this->latestPublisherId = latestPublisherId;
	}

	UserIdentity ResourceManager::getLatestPublisherId() const {
		return latestPublisherId;
	}

	std::vector<std::string> ResourceManager::getSplittedString(std::string originalString, char delim) {
		std::stringstream ss;
		ss.str(originalString);

		std::string str;
		std::vector<std::string> splittedStrings;

		while (getline(ss, str, delim)) {
			splittedStrings.push_back(str);
		}
		return splittedStrings;
	}

	void ResourceManager::setAppType(int appType) {
		this->appType = appType;
	}

	int ResourceManager::getAppType() const {
		return appType;
	}

}
