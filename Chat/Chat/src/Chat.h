/*
* File:   Chat.h
* Author: dipal
*
* Created on August 17, 2015, 11:55 AM
*/

#ifndef CHAT_H
#define	CHAT_H


#include "IEventHandler.h"
#include "Types.h"
#include "ChatParser.h"
#include "PacketTemplate.h"
#include "IChatEventHandler.h"
#include "ChatPacketBuilder.h"
#include <memory>
#include <random>
#include "ApiStatus.h"
#include "PacketTimeId.h"
#include "FriendInformation.h"
#include "GroupInformation.h"
#include "DataCounter.h"
#include "DuplicateChecker.h"

//const unsigned long long kNum_100nsec_1582_1970 = 0x01b21dd213814000;
//const unsigned long long kMax_node = 0xffffffffffff; // 48-bits, all 1s.
//const uint16_t kMax_clock_seq = 0x3fff; // 14-bits, all 1s.

namespace imsdk {
	class Chat {
    private:
        DuplicateChecker requestDuplicateChecker;

	public:
		Chat(UserIdentity userid, std::string userName, std::string offlineServerAddress, int offlineServerPort,
			std::string authenticationServerAddress, int authenticationServerPort, int deviceType,
			std::string appSessionId, int appVersion, long long timeDifference,
			std::vector<std::string> &directoryPaths, std::string baseUploadUrl, std::string baseDownloadUrl,
			bool autoDownloadEnabled, std::string key, int appType, std::set<UserIdentity> pageIdList);

		void reinitialize(UserIdentity userid, std::string userName, std::string offlineServerAddress,
			int offlineServerPort, std::string authenticationServerAddress, int authenticationServerPort,
			int deviceType, std::string appSessionId, int appVersion, long long timeDifference,
			std::vector<std::string> &directoryPaths, bool autoDownloadEnabled, std::string key, std::set<UserIdentity> pageIdList);

		virtual ~Chat();

        ApiStatus activateOrDeactivateUserAccount(bool isAccountActivate);
        ApiStatus getUserInfo(UserIdentity friendId);


		void registerEventHandler(std::shared_ptr< IChatEventHandler> eventHandler);
		void unregisterEventHandler();
		void setLogfile(std::string fileName);
		void setOfflineServer(std::string offlineServerAddress, int offlineServerPort);
		void setAuthenticationServer(std::string authenticationServerAddress, int authenticationServerPort);
		ApiStatus requestForOffline(long long messageDate, long long blockUpdateDate);

        ApiStatus registerFriendChat(UserIdentity userId, std::string userName, UserIdentity friendId, std::string friendName, std::string friendUrl, std::string registerServerAddress, int registerServerPort, int deviceType, std::string deviceToken, int appType, int status, int mood, int iosVoipPush, long long authRegistrationTime, int profileType);
		bool isExistsFriendConnection(UserIdentity userId, UserIdentity friendId);
		ApiStatus registerGroupChat(GroupIdentity groupId, std::string registerServerAddress, int registerServerPort, long long authRegistrationTime);
		bool isExistsGroupConnection(GroupIdentity groupId);
		ApiStatus unregisterFriendChat(UserIdentity userId, UserIdentity friendId, int status, int mood);
		ApiStatus unregisterGroupChat(GroupIdentity groupId, int status, int mood);
		ApiStatus updateFriendRegisterServer(UserIdentity userId, UserIdentity friendId, std::string registerServerAddress, int registerServerPort);
		ApiStatus updateFriendStatusAndMood(UserIdentity userId, UserIdentity friendId, int status, int mood);
		ApiStatus sendFriendChat(std::string &packetId, UserIdentity userId, UserIdentity friendId, int messageType, int secretTimeout, std::string &message, long long messageDate, bool isSecretVisible);
		ApiStatus dontSendPendingMessages(UserIdentity userId, UserIdentity friendId);
		ApiStatus sendFriendCallBusyMessage(UserIdentity userId, UserIdentity friendId, std::string &message, long long messageDate, std::string &packetId);
		ApiStatus sendFriendCallLogMessage(UserIdentity userId, UserIdentity friendId, std::string &message, long long messageDate, std::string &packetId);
		ApiStatus editFriendChat(std::string &packetId, UserIdentity userId, UserIdentity friendId, int messageType, int secretTimeout, std::string &message, long long messageDate, bool isSecretVisible);
		ApiStatus seenFriendChat(UserIdentity userId, UserIdentity friendId, std::vector<SeenPacketDTO> &seenPacketList);
		ApiStatus typingFriendChat(UserIdentity userId, UserIdentity friendId);
		ApiStatus deleteFriendChatMessage(UserIdentity userId, UserIdentity friendId, std::vector<std::string> &packetIds, int deleteType);
		ApiStatus requestFriendChatHistory(UserIdentity userId, UserIdentity friendId, std::string &packetId, int direction, int limit);//Done
		ApiStatus getFriendMessageStatus(UserIdentity userId, UserIdentity friendId, std::vector<std::string> &packetIds);//Done
		ApiStatus blockFriend(UserIdentity userId, std::string &packetId, UserIdentity friendId, long long blockUnblockDate, bool addToBlock);
		ApiStatus unblockFriend(UserIdentity userId, std::string &packetId, UserIdentity friendId, long long blockUnblockDate);
		ApiStatus sendGroupChat(std::string &packetId, GroupIdentity groupId, int messageType, std::string &message, long long messageDate);
		ApiStatus editGroupChat(std::string &packetId, GroupIdentity groupId, int messageType, std::string &message, long long messageDate);
		ApiStatus seenGroupChat(GroupIdentity groupId, std::vector<std::string> &packetIds);
		ApiStatus typingGroupChat(GroupIdentity groupId);
		ApiStatus deleteGroupChatMessage(GroupIdentity groupId, std::vector<std::string> &packetIds);

		ApiStatus changeGroupName(GroupIdentity groupId, std::string &groupName);//Done
		ApiStatus changeGroupUrl(GroupIdentity groupId, std::string &groupUrl);//Done
		ApiStatus addGroupMembers(GroupIdentity groupId, std::vector<MemberDTO> &memberList);
		ApiStatus removeGroupMembers(GroupIdentity groupId, std::vector<UserIdentity> &memberIds);
        ApiStatus leaveGroup(GroupIdentity groupId, bool isHide);
		ApiStatus changeGroupMemberStatus(GroupIdentity groupId, std::vector<MemberDTO> &memberList);
		ApiStatus createGroup(GroupIdentity groupId, std::string &groupName, std::string &groupUrl, std::vector<MemberDTO> &memberList);//Done
		ApiStatus requestGroupChatHistory(GroupIdentity groupId, std::string &packetId, int direction, int limit);//Done
		ApiStatus getGroupInformationWithMembers(GroupIdentity groupId);//Done

		std::shared_ptr< ByteArray> getGroupFileTransferIdlePacket(GroupIdentity groupId);
		std::shared_ptr< ByteArray> getGroupFileIdlePacket(GroupIdentity groupId);

		std::shared_ptr< ByteArray> getFriendFileIdelPacket(UserIdentity userId, UserIdentity friendId);
		//    
		//    ApiStatus sendFileToFriend(UserIdentity friendId, int messageType, int secretTimeOut, FileIdentity fileId, std::string fileFullPath, long long fileSize, long long messageDate, bool isSecretVisible);
		//    ApiStatus startFileTransfer(UserIdentity friendId, FileIdentity fileId, const std::string &filePath);
		//    ApiStatus cancelFileTransfer(UserIdentity friendId, FileIdentity fileId);    
		std::vector<std::string> getPendingFriendMessages(UserIdentity userId);
		std::vector<std::string> getPendingGroupMessages();
		void cleanUp(int mood);
		void clearRegisteredSessions(int mood);
		std::shared_ptr< FriendInformation> getFriendInformation(UserIdentity userId, UserIdentity friendId);
		std::shared_ptr< GroupInformation> getGroupInformation(GroupIdentity groupId);
		std::vector<UserIdentity> getRegisteredFriendsList(UserIdentity userId);
		std::vector<std::shared_ptr< GroupInformation>> getRegisteredGroupList();
		DataCounter getDataSentReceived();

		ApiStatus friendFileTransferSessionRequest(UserIdentity userId, UserIdentity friendId, FileIdentity fileId);
		ApiStatus friendFileTransferStreamRequest(UserIdentity userId, UserIdentity friendId, FileIdentity fileId);

		ApiStatus groupFileTransferSessionRequest(GroupIdentity groupId, FileIdentity fileId);
		ApiStatus groupFileTransferStreamRequest(UserIdentity friendId, GroupIdentity groupId, FileIdentity fileId);

		ApiStatus getFriendChatMessage(UserIdentity userId, UserIdentity friendId, std::string &packetId);
		ApiStatus getGroupChatMessage(GroupIdentity groupId, std::string &packetId);

		ApiStatus getGroupMessageSeenList(GroupIdentity groupId, std::string &packetId);

		ApiStatus getConversationList(UserIdentity userId, ConversationType conversationType, int startIndex, int limit, long long friendOrGroupId);
		ApiStatus deleteConversation(UserIdentity userId, std::vector<ConversationDTO> &conversationList);
		ApiStatus markConversationSeen(UserIdentity userId, std::vector<ConversationDTO> &conversationList);

		void updateUserPassword(std::string password);

		// Public Room Chat
		ApiStatus registerPublicRoomChat(RoomIdentity &roomId, std::string &memberName, std::string &memberUrl, UserIdentity ringId);
		ApiStatus sendPublicRoomChat(std::string &packetId, RoomIdentity roomId, int messageType, std::string &message, long long messageDate, std::string &memberFullName, std::string &memberProfileUrl);
		ApiStatus editPublicRoomChat(std::string &packetId, RoomIdentity roomId, int messageType, std::string &message, long long messageDate, std::string &memberFullName, std::string &memberProfileUrl);
		ApiStatus getRoomList(int startIndex, int limit);
		ApiStatus searchRoomList(std::string &searchName, std::string &country, std::string &category, int startIndex, int limit);
		ApiStatus unregisterPublicRoomChat(RoomIdentity roomId);
		ApiStatus typingPublicRoomChat(RoomIdentity roomId);
		bool isExistsRoomConnection(RoomIdentity roomId);
		ApiStatus getRoomInformation(RoomIdentity roomId);
		ApiStatus requestRoomChatHistory(RoomIdentity roomId, std::string &packetId, int year, int month, int direction, int limit);
		ApiStatus getRoomListWithHistory(int startIndex, int limit);
		ApiStatus getRoomMemberList(RoomIdentity roomId, std::string pagingState, int limit);

		void enterPublicChatScreen(RoomIdentity roomId);
		void exitPublicChatScreen(RoomIdentity roomId);

		ApiStatus deletePublicChatMessage(RoomIdentity &roomId, std::vector<std::string> &packetIds);
		ApiStatus likePublicChatMessage(std::string &packetId, RoomIdentity &roomId, UserIdentity messageSenderId);
		ApiStatus unlikePublicChatMessage(std::string &packetId, RoomIdentity &roomId, UserIdentity messageSenderId);
		ApiStatus reportPublicChatMessage(std::string &packetId, RoomIdentity &roomId, UserIdentity messageSenderId, std::string &reportMessage);

		ApiStatus getPublicChatLikeMemberList(RoomIdentity roomId, std::string &packetId, UserIdentity lastLikerId, int limit);
		ApiStatus getPublicChatRoomCategoryList(std::string &lastCategory, int limit);

		//Live-stream-chat
		ApiStatus registerLiveStreamChat(UserIdentity publisherId, std::string registerServerAddress, int registerServerPort, std::string fullName);
		ApiStatus unregisterLiveStreamChat(UserIdentity publisherId, int onlineStatus, int onlineMood);
		ApiStatus typingLiveStreamChat(UserIdentity publisherId);
		ApiStatus sendLiveStreamChat(std::string &packetId, UserIdentity publisherId, int messageType, std::string &message, long long messageDate);
		ApiStatus blockUserFromLiveStreamChat(UserIdentity blockedUserId, std::string &packetId);

		//Anonymous chat
		ApiStatus registerAnonymousFriendChat(UserIdentity selfAnonymousUserId, UserIdentity friendAnonymousId, UserIdentity originalFriendId, std::string registerServerAddress, int registerServerPort, int deviceType, std::string deviceToken, int appType, int status, int mood);
		ApiStatus unregisterAnonymousFriendChat(UserIdentity userId, UserIdentity friendId, int status, int mood);
		ApiStatus getShadowIdInfo(std::vector<UserIdentity> &userIds);

		void addUserPage(UserIdentity pageId);
		void removeUserPage(UserIdentity pageId);

		PacketTimeId generatePacketId(UserIdentity userId = 0);
		PacketTimeId generatePacketId(long long timeMili, UserIdentity userId);
		static std::string generatePacketId_v2();
		GroupIdentity generateGroupId();
		std::string version();
        static std::string getRingIdPackageName();
        static std::string getRingIncPackageName();
		long long getCurrentServerSyncedTime();
		long long UUIDToTime(std::string UUID);

		void setLogEnabled(bool enableDisable);
		static void startServices();
		static void stopServices();

		bool checkInternetConnection();

		bool sendFriendChatMedia(UserIdentity userId, UserIdentity friendId, std::string &packetId, int mediaType, const std::string filePath, std::string caption, int widthOrFileSize, int heightOrDuration, int secretTimeout, long long messageDate, bool isSecretVisible);
		bool downloadFriendChatMedia(UserIdentity userId, UserIdentity friendId, std::string &packetId, const std::string manifestUrl, int mediaType, int secretTimeout);
		bool acceptChatMedia(std::string packetId);

		bool sendGroupChatMedia(GroupIdentity groupId, std::string &packetId, int mediaType, const std::string filePath, std::string caption, int widthOrFileSize, int heightOrDuration, long long messageDate);
		bool downloadGroupChatMedia(GroupIdentity groupId, UserIdentity friendId, std::string &packetId, const std::string manifestUrl, int mediaType);

		void cancelChatMediaTransfer(std::string &packetId);

		std::vector<std::string> getPendingChatMediaList(ConversationType conversationType, bool isUpload, bool isChunked);
		bool isChatMediaTransferInProgress(std::string packetId);

		void updateAppSessionID(std::string appSessionId);

        ApiStatus getSyncedConversation(UserIdentity userId, std::string &packetId, long long lastSyncedTime);
        ApiStatus getSyncedFriendHistoryMessage(UserIdentity userId, UserIdentity friendId, std::string &packetId, long long lastSyncedTime, int limit, int direction);
        ApiStatus getSyncedGroupHistoryMessage(UserIdentity userId, GroupIdentity groupId, std::string &packetId, long long lastSyncedTime, int limit, int direction);

        ApiStatus getMyGroupListPaging(UserIdentity userId, std::string &packetId, std::string &pivotId, int limit, int direction);

        //notice add
        ApiStatus addNotice(int messageType, long long disburseTime, long long expireTime, std::string &notice, std::vector<std::string> &isoCountryList);
		ApiStatus sendGeneralEncryptedInformation(UserIdentity userID, UserIdentity friendID, std::string &packetID, int type, int informationType, std::string &information);
        
	private:

		//    UserIdentity userId{0};
		//    std::string userName;
		//    int deviceType;
		std::shared_ptr< ChatPacketBuilder> packetBuilder{ nullptr };

		ApiStatus sendOrEditBrokenFriendChat(int packetType, UserIdentity userId, UserIdentity friendId, std::string &packetId, int totalNumberOfPackets, int chunkNumber, int messageType, int secretTimeout, std::string &message, long long messageDate, bool isSecretVisible);
		ApiStatus sendOrEditBrokenGroupChat(int packetType, GroupIdentity groupId, std::string &packetId, int totalNumberOfPackets, int chunkNumber, int messageType, std::string &message, long long messageDate);
		ApiStatus sendOrEditBrokenPublicRoomChat(int packetType, RoomIdentity roomId, std::string &packetId, int totalNumberOfPackets, int chunkNumber, int messageType, std::string &message, long long messageDate, std::string &memberFullName, std::string &memberProfileUrl);
		//void startServices();
		bool isExistsValidKey(std::string &packetId, UserIdentity friendId, GroupIdentity groupId = 0);
		void sendUnregisterForRegisteredSessions(int mood);
	};
}

#endif	/* CHAT_H */

