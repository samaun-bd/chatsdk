#pragma once

#include "ChatEventHandler.h"
#include "ManagedApiStatus.h"
#include "ManagedFriendInformation.h"
#include "ManagedMemberDTO.h"
#include "ManagedGroupInformation.h"
#include "ManagedPacketTimeID.h"
#include "DataConvertionUtility.h"
#include "ManagedConversationDTO.h"
#include<collection.h>

//namespace PC = Platform::Collections;
using namespace Platform;

namespace ChatWrapper
{
	public ref class IMManager sealed
	{
	public:
		//IMManager(UserIdentity userid, String ^userName, String ^offlineServerAddress, int offlineServerPort, String ^authenticationServerAddress, int authenticationServerPort, int deviceType, String ^appSessionId, int appVersion, long long timeDifference, String ^settingsDirectoryPath);
		IMManager(UserIdentity userid, String ^userName, String ^offlineServerAddress, int offlineServerPort, String ^authenticationServerAddress, int authenticationServerPort, int deviceType, String ^appSessionId, int appVersion, long long timeDifference, const Array<String^> ^settingsDirectoryPaths, String ^baseUploadUrl, String ^baseDownloadUrl, bool autoDownloadEnabled, String ^key, int appType, const Array<long long> ^pageIdList);
		void registerEventHandler(IMListener ^listener);
		void unregisterEventHandler();
		//void setLogfile(String ^fileName);

        ManagedApiStatus ^activateOrDeactivateUserAccount(bool isActivate);
        ManagedApiStatus ^getUserInfo(UserIdentity friendId);

		void setOfflineServer(String ^offlineServerAddress, int offlineServerPort);
		void setAuthenticationServer(String ^authenticationServerAddress, int authenticationServerPort); // discard
		ManagedApiStatus ^requestForOffline(long long messageDate, long long blockUpdateDate);

		ManagedApiStatus ^registerFriendChat(UserIdentity userId, String ^userName, UserIdentity friendId, String ^friendName, String ^friendUrl, String ^registerServerAddress, int registerServerPort, int deviceType, String ^deviceToken, int appType, int status, int mood, int iosVoipPush, long long authRegistrationTime, int profileType);
		bool isExistsFriendConnection(UserIdentity userId, UserIdentity friendId);
		ManagedApiStatus ^registerGroupChat(GroupIdentity groupId, String ^registerServerAddress, int registerServerPort, long long authRegistrationTime);
		bool isExistsGroupConnection(GroupIdentity groupId);
		ManagedApiStatus ^unregisterFriendChat(UserIdentity userId, UserIdentity friendId, int status, int mood);
		ManagedApiStatus ^unregisterGroupChat(GroupIdentity groupId, int status, int mood);
		ManagedApiStatus ^updateFriendRegisterServer(UserIdentity userId, UserIdentity friendId, String ^registerServerAddress, int registerServerPort);
		ManagedApiStatus ^updateFriendStatusAndMood(UserIdentity userId, UserIdentity friendId, int status, int mood);
		ManagedApiStatus ^sendFriendChat(String ^packetId, UserIdentity userId, UserIdentity friendId, int messageType, int secretTimeout, String ^message, long long messageDate, bool isSecretVisible);
		ManagedApiStatus ^dontSendPendingMessages(UserIdentity userId, UserIdentity friendId);
		ManagedApiStatus ^sendFriendCallBusyMessage(UserIdentity userId, UserIdentity friendId, String ^message, long long messageDate, String ^packetId);
		ManagedApiStatus ^sendFriendCallLogMessage(UserIdentity userId, UserIdentity friendId, String ^message, long long messageDate, String ^packetId);
		ManagedApiStatus ^editFriendChat(String ^packetId, UserIdentity userId, UserIdentity friendId, int messageType, int secretTimeout, String ^message, long long messageDate, bool isSecretVisible);
		ManagedApiStatus ^seenFriendChat(UserIdentity userId, UserIdentity friendId, const Array<ManagedSeenPacketDTO^> ^seenPacketList);
		ManagedApiStatus ^typingFriendChat(UserIdentity userId, UserIdentity friendId);
		ManagedApiStatus ^deleteFriendChatMessage(UserIdentity userId, UserIdentity friendId, const Array<String^> ^packetIds);
		ManagedApiStatus ^requestFriendChatHistory(UserIdentity userId, UserIdentity friendId, String ^packetId, int direction, int limit);
		ManagedApiStatus ^getFriendMessageStatus(UserIdentity userId, UserIdentity friendId, const Array<String^> ^packetIds);
		ManagedApiStatus ^blockFriend(UserIdentity userId, String ^packetId, UserIdentity friendId, long long blockUnblockDate, bool addToBlock);
		ManagedApiStatus ^unblockFriend(UserIdentity userId, String ^packetId, UserIdentity friendId, long long blockUnblockDate);
		ManagedApiStatus ^sendGroupChat(String ^packetId, GroupIdentity groupId, int messageType, String ^message, long long messageDate);
		ManagedApiStatus ^editGroupChat(String ^packetId, GroupIdentity groupId, int messageType, String ^message, long long messageDate);
		ManagedApiStatus ^seenGroupChat(GroupIdentity groupId, const Array<String^> ^packetIds);
		ManagedApiStatus ^getGroupMessageSeenList(GroupIdentity groupId, String^ packetId);
		ManagedApiStatus ^typingGroupChat(GroupIdentity groupId);
		ManagedApiStatus ^deleteGroupChatMessage(GroupIdentity groupId, const Array<String^> ^packetIds);

		ManagedApiStatus ^getConversationList(UserIdentity userId, int conversationType, int startIndex, int limit, long long friendOrGroupId);
		ManagedApiStatus ^deleteConversation(UserIdentity userId, const Array<ManagedConversationDTO^> ^conversationList);
		ManagedApiStatus ^markConversationSeen(UserIdentity userId, const Array<ManagedConversationDTO^> ^conversationList);

		void updateUserPassword(String ^password);

		ManagedApiStatus ^changeGroupName(GroupIdentity groupId, String ^groupName);
		ManagedApiStatus ^changeGroupUrl(GroupIdentity groupId, String ^groupUrl);
		ManagedApiStatus ^addGroupMembers(GroupIdentity groupId, const Array<ManagedMemberDTO^> ^memberList);
		ManagedApiStatus ^removeGroupMembers(GroupIdentity groupId, const Array<long long> ^memberIds);
		ManagedApiStatus ^leaveGroup(GroupIdentity groupId);
		ManagedApiStatus ^changeGroupMemberStatus(GroupIdentity groupId, const Array<ManagedMemberDTO^> ^memberList);
		ManagedApiStatus ^createGroup(GroupIdentity groupId, String ^groupName, String ^groupUrl, const Array<ManagedMemberDTO^> ^memberList);
		ManagedApiStatus ^requestGroupChatHistory(GroupIdentity groupId, String ^packetId, int direction, int limit);
		ManagedApiStatus ^getGroupInformationWithMembers(GroupIdentity groupId);

		Array<String^> ^getPendingFriendMessages(UserIdentity userId);
		Array<String^> ^getPendingGroupMessages();
		void cleanUp(int mood);
		void clearRegisteredSessions(int mood); // A limited version of cleanUp() for windows phone
		ManagedFriendInformation ^getFriendInformation(UserIdentity userId, UserIdentity friendId);
		ManagedGroupInformation ^getGroupInformation(GroupIdentity groupId);
		
		
		Array<UserIdentity> ^getRegisteredFriendsList(UserIdentity userId);

	    //Array<UserIdentity> ^getRegisteredFriendsList();

		Array<ManagedGroupInformation^> ^getRegisteredGroupList();
		ManagedDataCounter ^getDataSentReceived();
		long long getCurrentServerSyncedTime();
		long long UUIDToTime(String ^UUID);

		// Public Room Chat
		ManagedApiStatus ^registerPublicRoomChat(ManagedRoomIdentity roomId, String ^memberName, String ^memberUrl, UserIdentity ringId);
		ManagedApiStatus ^sendPublicRoomChat(String ^packetId, ManagedRoomIdentity roomId, int messageType, String ^message, long long messageDate, String ^memberFullName, String ^memberProfileUrl);
		ManagedApiStatus ^editPublicRoomChat(String ^packetId, ManagedRoomIdentity roomId, int messageType, String ^message, long long messageDate, String ^memberFullName, String ^memberProfileUrl);
		ManagedApiStatus ^getRoomList(int startIndex, int limit);

		ManagedApiStatus ^searchRoomList(String ^searchName, String ^country, String ^category, int startIndex, int limit);
		ManagedApiStatus ^deletePublicChatMessage(ManagedRoomIdentity roomId, const Array<String^> ^packetIds);
		ManagedApiStatus ^likePublicChatMessage(String ^packetId, ManagedRoomIdentity roomId, UserIdentity recipientId);
		ManagedApiStatus ^unlikePublicChatMessage(String ^packetId, ManagedRoomIdentity roomId, UserIdentity recipientId);
		ManagedApiStatus ^reportPublicChatMessage(String ^packetId, ManagedRoomIdentity roomId, UserIdentity recipientId, String ^reportMessage);
		ManagedApiStatus ^getPublicChatLikeMemberList(ManagedRoomIdentity roomId, String ^packetId, UserIdentity lastLikerId, int limit);
		ManagedApiStatus ^getPublicChatRoomCategoryList(String ^pagingState, int limit);

		ManagedApiStatus ^unregisterPublicRoomChat(ManagedRoomIdentity roomId);
		ManagedApiStatus ^typingPublicRoomChat(ManagedRoomIdentity roomId);
		bool isExistsRoomConnection(ManagedRoomIdentity roomId);
		ManagedApiStatus ^getRoomInformation(ManagedRoomIdentity roomId);
		ManagedApiStatus ^requestRoomChatHistory(ManagedRoomIdentity roomId, String ^packetId, int year, int month, int direction, int limit);
		ManagedApiStatus ^getRoomListWithHistory(int startIndex, int limit);
		ManagedApiStatus ^getRoomMemberList(ManagedRoomIdentity roomId, String ^pagingState, int limit);
		void enterPublicChatScreen(String ^roomId);
		void exitPublicChatScreen(String ^roomId);


		//ManagedApiStatus ^registerAnonymousFriendChat(UserIdentity selfAnonymousUserId, UserIdentity friendAnonymousId, UserIdentity originalFriendId, String ^registerServerAddress, int registerServerPort, int deviceType, String ^deviceToken, int appType, int status, int mood);
		//ManagedApiStatus ^unregisterAnonymousFriendChat(UserIdentity friendId, int status, int mood);

		void addUserPage(UserIdentity pageId);
		void removeUserPage(UserIdentity pageId);

		ManagedPacketTimeID ^generatePacketId(UserIdentity userOrPageId);
		ManagedPacketTimeID ^generatePacketId(long long timeMili, UserIdentity userId);
		static String ^generatePacketId_v2();
		GroupIdentity generateGroupId();

		//String ^version();
		//void setLogEnabled(bool enableDisable);
		//static void startServices();
		//static void stopServices();

		bool checkInternetConnection();



		bool sendFriendChatMedia(UserIdentity userId, UserIdentity friendId, String ^packetId, int mediaType, String ^filePath, String ^caption, int widthOrFileSize, int heightOrDuration, int secretTimeout, long long messageDate, bool isSecretVisible);
		bool downloadFriendChatMedia(UserIdentity userId, UserIdentity friendId, String ^packetId, String ^manifestUrl, int mediaType, int secretTimeout);
		bool acceptChatMedia(String ^packetId);

		bool sendGroupChatMedia(GroupIdentity groupId, String ^packetId, int mediaType, String ^filePath, String ^caption, int widthOrFileSize, int heightOrDuration, long long messageDate);
		bool downloadGroupChatMedia(GroupIdentity groupId, UserIdentity friendId, String ^packetId, String ^manifestUrl, int mediaType);

		void cancelChatMediaTransfer(String ^packetId);
		Array<String^> ^getPendingChatMediaList(int conversationType, bool isUpload, bool isChunked);
		
		bool isChatMediaTransferInProgress(String ^packetId);
		void updateAppSessionID(String ^appSessionId);


		//Live-stream-chat
		ManagedApiStatus ^registerLiveStreamChat(UserIdentity publisherId, String ^registerServerAddress, int registerServerPort, String ^fullName);
		ManagedApiStatus ^unregisterLiveStreamChat(UserIdentity publisherId, int onlineStatus, int onlineMood);
		ManagedApiStatus ^typingLiveStreamChat(UserIdentity publisherId);
		ManagedApiStatus ^sendLiveStreamChat(String ^packetId, UserIdentity publisherId, int messageType, String ^message, long long messageDate);
		ManagedApiStatus ^blockUserFromLiveStreamChat(UserIdentity blockedUserId, String ^packetId);
	};


}