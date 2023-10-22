/*
* File:   ResourceManager.h
* Author: dipal
*
* Created on September 6, 2015, 12:21 PM
*/

#ifndef RESOURCEMANAGER_H
#define	RESOURCEMANAGER_H

#ifndef SDK_VERSION
#define SDK_VERSION 3
#endif

#include <unordered_map>
#include <memory>
#include <sstream>
#include <set>
#include <algorithm>

#include "Types.h"
#include "Connection.h"
#include "PacketTimeId.h"

//#include "IPVConnectivityDLL.h"
//#include "IPVConnectivityDLLLinker.h"
//#include "IPVConnectivityInterface.h"
const unsigned long long kNum_100nsec_1582_1970 = 0x01b21dd213814000;
const unsigned long long kMax_node = 0xffffffffffff; // 48-bits, all 1s.
const uint16_t kMax_clock_seq = 0x3fff; // 14-bits, all 1s.


namespace imsdk {
	class FriendInfo {
	private:
		UserIdentity userId;
        std::string userName;
		UserIdentity friendId;
		std::string friendName;
		std::string friendUrl;
		int deviceType;
		std::string deviceToken;
		int appType;
		int status;
		int mood;
		int iosVoipPush;
		bool isFriendBlocked;
		long long currentRegisterTime;
		long long authRegisterTime;
		std::shared_ptr< ChatConnection> connection;
                int profileType{ 0 };

	public:
		FriendInfo(
			UserIdentity userId,
			std::string userName,
			UserIdentity friendId,
			std::string friendName,
			std::string friendUrl,
			std::shared_ptr< ChatConnection> connection,
			int deviceType,
			std::string deviceToken,
			int appType,
			int status,
			int mood,
			int iosVoipPush,
			bool isBlocked,
			long long currentRegisterTime,
			long long authRegisterTime,
                        int profileType)
			:
                        userId(userId),
			friendId(friendId),
			friendName(friendName),
			friendUrl(friendUrl),
			deviceType(deviceType),
			deviceToken(deviceToken),
			appType(appType),
			status(status),
			mood(mood),
			iosVoipPush(iosVoipPush),
			isFriendBlocked(isBlocked),
			currentRegisterTime(currentRegisterTime),
			authRegisterTime(authRegisterTime),
			connection(connection),
                        profileType(profileType)
		{
		}

		void setStatus(int status){
			this->status = status;
		}

		void setMood(int mood){
			this->mood = mood;
		}

		UserIdentity getUserId() {
			return userId;
		}
        
        std::string getUserName() {
            return userName;
        }

		UserIdentity getFriendId() {
			return friendId;
		}

		std::shared_ptr< ChatConnection> getConnection() {
			return connection;
		}

		int getDeviceType() {
			return deviceType;
		}

		std::string getDeviceToken() {
			return deviceToken;
		}

		int getAppType() {
			return appType;
		}

		int getStatus() {
			return status;
		}

		int getMood() {
			return mood;
		}

		int getIosVoipPush() {
			return iosVoipPush;
		}

		void setIsFriendBlocked(bool isFriendBlocked){
			this->isFriendBlocked = isFriendBlocked;
		}

		bool getIsFriendBlocked(){
			return isFriendBlocked;
		}

		void setFriendUrl(std::string friendUrl) {
			this->friendUrl = friendUrl;
		}

		std::string getFriendUrl() const {
			return friendUrl;
		}

		void setFriendName(std::string friendName) {
			this->friendName = friendName;
		}

		std::string getFriendName() const {
			return friendName;
		}

		void setCurrentRegisterTime(long long currentRegisterTime) {
			this->currentRegisterTime = currentRegisterTime;
		}

		long long getCurrentRegisterTime() const {
			return currentRegisterTime;
		}

		void setAuthRegisterTime(long long authRegisterTime) {
			this->authRegisterTime = authRegisterTime;
		}

		long long getAuthRegisterTime() const {
			return authRegisterTime;
		}

		void setProfileType(int profileType) {
			this->profileType = profileType;
		}

		int getProfileType() const {
			return profileType;
		}
        
	};

	class RoomInfo {
	private:
		std::shared_ptr< ChatConnection> connection;
		RoomIdentity roomId;
		std::string memberName;
		std::string memberUrl;
		UserIdentity anonymousId;
		int numberOfMember;
		UserIdentity ringId;

	public:

		RoomInfo(
			RoomIdentity &roomId,
			std::shared_ptr< ChatConnection> connection,
			std::string &memberName,
			std::string &memberUrl,
			UserIdentity anonymousId,
			UserIdentity ringId)
			:
			connection(connection),
			roomId(roomId),
			memberName(memberName),
			memberUrl(memberUrl),
			anonymousId(anonymousId),
			ringId(ringId)
		{
		}

		void setRoomId(RoomIdentity roomId) {
			this->roomId = roomId;
		}

		RoomIdentity getRoomId() {
			return roomId;
		}

		void setConnection(std::shared_ptr< ChatConnection> connection) {
			this->connection = connection;
		}

		std::shared_ptr< ChatConnection> getConnection() {
			return connection;
		}

		void setMemberUrl(std::string memberUrl) {
			this->memberUrl = memberUrl;
		}

		std::string getMemberUrl() {
			return memberUrl;
		}

		void setMemberName(std::string memberName) {
			this->memberName = memberName;
		}

		std::string getMemberName() {
			return memberName;
		}

		void setAnonymousId(UserIdentity anonymousId) {
			this->anonymousId = anonymousId;
		}

		UserIdentity getAnonymousId() const {
			return anonymousId;
		}

		void setNumberOfMember(int numberOfMember) {
			this->numberOfMember = numberOfMember;
		}

		int getNumberOfMember() const {
			return numberOfMember;
		}

		void setRingId(UserIdentity ringId) {
			this->ringId = ringId;
		}

		UserIdentity getRingId() const {
			return ringId;
		}
	};

	class LiveStreamChatInfo {
	private:
		std::shared_ptr< ChatConnection> connection;
		UserIdentity publisherId;
		std::string userName;

	public:

		LiveStreamChatInfo(
			UserIdentity publisherId,
			std::shared_ptr< ChatConnection> connection,
			std::string &userName)
			:
			connection(connection),
			publisherId(publisherId),
			userName(userName)
		{
		}

		void setUserName(std::string userName) {
			this->userName = userName;
		}

		std::string getUserName() const {
			return userName;
		}

		void setPublisherId(UserIdentity publisherId) {
			this->publisherId = publisherId;
		}

		UserIdentity getPublisherId() const {
			return publisherId;
		}

		void setConnection(std::shared_ptr< ChatConnection> connection) {
			this->connection = connection;
		}

		std::shared_ptr< ChatConnection> getConnection() const {
			return connection;
		}
	};

	struct AnonymousUserIdentity{
		UserIdentity selfAnonymousId{ 0 };
		UserIdentity originalFriendId{ 0 };
	};

	struct GroupInfo{
		GroupIdentity groupId;
		std::shared_ptr< ChatConnection> groupConnection;
	};

	class ResourceManager {
	public:
		virtual ~ResourceManager();

		static ResourceManager& getInstance();

		void addFriendInfo(std::shared_ptr< FriendInfo> friendInfo);
		std::shared_ptr< FriendInfo> getFriendInfo(UserIdentity userId, UserIdentity friendid);
		void removeFriendInfo(UserIdentity userId, UserIdentity friendid);
		void addRoomInfo(std::shared_ptr< RoomInfo> roomInfo);
		std::shared_ptr< RoomInfo> getRoomInfo(RoomIdentity roomId);
		void removeRoomInfo(RoomIdentity roomId);
		void updateFriendInfoStatus(UserIdentity userId, UserIdentity friendId, int status);
		void addGroupConnection(GroupIdentity groupid, std::shared_ptr< ChatConnection> &connection);
		std::shared_ptr< ChatConnection> getGroupConnection(GroupIdentity groupid);
		void removeGroupConnection(GroupIdentity groupid);
        void addGroupRegistration(GroupIdentity groupid, long long registrationTime);
        long long GetGroupRegistrationTime(GroupIdentity groupid);
        void removeGroupRegistration(GroupIdentity groupid);
		void addLiveStreamChatInfo(std::shared_ptr< LiveStreamChatInfo> liveStreamChatInfo);
		std::shared_ptr< LiveStreamChatInfo> getLiveStreamChatInfo(UserIdentity publisherId);
		void removeLiveStreamChatInfo(UserIdentity publisherId);

		void createSocketIfNeeded();
		void createOfflineConnectionIfNeeded();
        void setOfflineServer(std::string offlineServerAddress, int offlineServerPort);

        void setAuthSessionID(std::string authSessionId);
        std::string getAuthSessionID();

		void setAuthenticationServer(std::string authenticationServerAddress, int authenticationServerPort);
		std::string getAuthenticationAddress();
		int getAuthenticationPort();

		void setIsRunningServices(bool isRunning);
		bool getIsRunningServices();

		void addAnonymousUser(UserIdentity friendId, AnonymousUserIdentity anonymousUserId);
		AnonymousUserIdentity getAnonymousUser(UserIdentity friendId);
		bool isExistsAnonymousUser(UserIdentity friendId);
		void removeAnonymousUser(UserIdentity friendId);

		void clearSocket();
		void clearOfflineConnection();
		void clear();

		std::shared_ptr< ChatConnection> getOfflineConnection();
		std::shared_ptr< UDPSocket> getSocket();

		static std::string toString(int x);
		static std::string toLongToString(long long x);
		static long long toStringToLong(std::string s);
		static int toStringToInt(std::string s);
		void setTimeDifference(long long timeDifference);
		long long getTimeDifference();
		long long gettime();
		long long getServerSyncedTime();
		std::pair<long long, long long> gettimeUUID();
		void setUserId(UserIdentity userId);
		UserIdentity getUserId();
		void setUserPageIdList(std::set<UserIdentity> pageIdList);
        std::set<UserIdentity> getUserPageIdList();
        bool isUserPage(UserIdentity pageId);

		void addNewPage(UserIdentity pageId);
		void removePage(UserIdentity pageId);

		//    static std::vector<std::string> StringParser(std::string message);
		//    static std::unordered_map<string,string> fileNameParser(std::string str);
		//    static std::string mapToJson(std::unordered_map<string,string> parsedData);

		std::vector<UserIdentity> getAllRegisteredFriendIDs(UserIdentity userId);
		std::vector<std::shared_ptr< FriendInfo>> getAllFriendConnection();
		std::vector<std::shared_ptr< GroupInfo>> getAllGroupInfo();
		std::vector<std::shared_ptr< RoomInfo>> getAllRoomConnection();
		void setUserName(std::string userName);
		std::string getUserName();
		void setDeviceType(int deviceType);
		int getDeviceType();
		PacketTimeId generatePacketIdInSDK(UserIdentity userId = 0);
		PacketTimeId generatePacketIdInSDK(long long timeMili, UserIdentity userId);
		std::string longToHex(unsigned long long val);
		long long hexToLong(std::string str);
		std::string padHex(unsigned long long l, size_t n);
		std::string timeToUUID(unsigned long long ns100_intervals, UserIdentity userId);
		long long UUIDToTime(std::string UUID);
		const std::vector<std::string> stringSplit(const std::string& s, const char& c);

		int appVersion;

		void countNetworkData();

		void setMediaTransferTmpDirPath(std::string mediaTransferTmpDirPath);
		std::string getMediaTransferTmpDirPath() const;
		void setAutoDownloadEnabled(bool autoDownloadEnabled);
		bool isAutoDownloadEnabled() const;
		void setBaseDownloadUrl(std::string baseDownloadUrl);
		std::string getBaseDownloadUrl() const;
		void setBaseUploadUrl(std::string baseUploadUrl);
		std::string getBaseUploadUrl() const;
		void setChatVideoDownloadPath(std::string chatVideoDownloadPath);
		std::string getChatVideoDownloadPath() const;
		void setChatAudioDownloadPath(std::string chatAudioDownloadPath);
		std::string getChatAudioDownloadPath() const;
		void setChatImageDownloadPath(std::string chatImageDownloadPath);
		std::string getChatImageDownloadPath() const;
		void setSecretChatVideoDownloadPath(std::string secretChatVideoDownloadPath);
		std::string getSecretChatVideoDownloadPath() const;
		void setSecretChatAudioDownloadPath(std::string secretChatAudioDownloadPath);
		std::string getSecretChatAudioDownloadPath() const;
		void setSecretChatImageDownloadPath(std::string secretChatImageDownloadPath);
		std::string getSecretChatImageDownloadPath() const;
		void setEncryptionDecryptionKey(std::shared_ptr<ByteArray> encryptionDecryptionKey);
		std::shared_ptr<ByteArray> getEncryptionDecryptionKey() const;
		void setLatestPublisherId(UserIdentity latestPublisherId);
		UserIdentity getLatestPublisherId() const;
		std::vector<std::string> getSplittedString(std::string originalString, char delim);
		void setAppType(int appType);
		int getAppType() const;

        static std::mutex startServicesMutex;

	private:
		ResourceManager();

		std::unordered_map<UserIdentity, std::unordered_map<UserIdentity, std::shared_ptr< FriendInfo>>> friendInfoMap;
        std::unordered_map<GroupIdentity, std::shared_ptr< ChatConnection>> groupConnectionMap;
        std::unordered_map<GroupIdentity, long long> groupRegistrationMap;
		std::unordered_map<RoomIdentity, std::shared_ptr< RoomInfo>> roomConnectionMap;
		std::unordered_map<UserIdentity, AnonymousUserIdentity> anonymousUserMap;
		std::unordered_map<UserIdentity, std::shared_ptr< LiveStreamChatInfo>> liveStreamChatInfoMap;

		std::shared_ptr< ChatConnection> offlineConnection;

		std::string authenticationServerAddress;
		int authenticationServerPort;

		long long timeDifference{ 0 };

		std::mutex friendConnectionMutex;
        std::mutex groupConnectionMutex;
        std::mutex groupRegistrationMutex;
		std::mutex roomConnectionMutex;
		std::mutex anonymousUserMutex;
		std::mutex liveStreamChatConnectionMutex;

		UserIdentity latestPublisherId{ 0 };

		bool isRunningServices{ false };

		UserIdentity userId{ 0 };
		std::set<UserIdentity> pageIdList;
		std::string userName;
		int deviceType;
		int appType;

        std::string offlineServerAddress;
        std::string authSessionID;
		int offlinePort{ 0 };

		std::string mediaTransferTmpDirPath;
		std::string chatImageDownloadPath;
		std::string chatAudioDownloadPath;
		std::string chatVideoDownloadPath;
		std::string secretChatImageDownloadPath;
		std::string secretChatAudioDownloadPath;
		std::string secretChatVideoDownloadPath;
		bool autoDownloadEnabled{ false };
		std::string baseUploadUrl;
		std::string baseDownloadUrl;
		std::shared_ptr<ByteArray> encryptionDecryptionKey;

		std::shared_ptr< UDPSocket> socket;
	};
}

#endif	/* RESOURCEMANAGER_H */

