#include "IMManager.h"
#include "Chat.h"
//#include "IMListener.h"
#include "ChatEventHandler.h"
//#include "DataConvertionUtility.h"

using namespace imsdk;
static Chat *chatService;

namespace ChatWrapper
{
	IMManager::IMManager(UserIdentity userid, String ^userName, String ^offlineServerAddress, int offlineServerPort, String ^authenticationServerAddress, int authenticationServerPort, int deviceType, String ^appSessionId, int appVersion, long long timeDifference, const Array<String^> ^settingsDirectoryPaths, String ^baseUploadUrl, String ^baseDownloadUrl, bool autoDownloadEnabled, String ^key, int appType, const Array<long long> ^pageIdList)
	{
		auto local = Windows::Storage::ApplicationData::Current->LocalFolder;
		string localFileNamePlatformString = DataConvertionUtility::ToNativeString(local->Path) + "\\imsdk.txt";

		chatService = new Chat(
								userid,
								DataConvertionUtility::ToNativeString(userName),
								DataConvertionUtility::ToNativeString(offlineServerAddress),
								offlineServerPort,
								DataConvertionUtility::ToNativeString(authenticationServerAddress),
								authenticationServerPort,
								deviceType,
								DataConvertionUtility::ToNativeString(appSessionId),
								appVersion,
								timeDifference,
								DataConvertionUtility::ToNativeCollection(settingsDirectoryPaths),
								DataConvertionUtility::ToNativeString(baseUploadUrl),
								DataConvertionUtility::ToNativeString(baseDownloadUrl),
								autoDownloadEnabled,
								DataConvertionUtility::ToNativeString(key),
								appType,
								DataConvertionUtility::ToNativeCollectionSet(pageIdList)
							);

		chatService->setLogfile(localFileNamePlatformString);

	}

	void IMManager::registerEventHandler(IMListener ^listener)
	{
		chatService->registerEventHandler(make_shared<ChatEventHandler>(listener));
	}

	void IMManager::unregisterEventHandler()
	{
		chatService->unregisterEventHandler();
	}

	ManagedApiStatus ^IMManager::activateOrDeactivateUserAccount(bool isActivate)
	{
        return	DataConvertionUtility::ToManagedApiStatus(chatService->activateOrDeactivateUserAccount(isActivate));
	}

    ManagedApiStatus ^IMManager::getUserInfo(UserIdentity friendId)
    {
        return	DataConvertionUtility::ToManagedApiStatus(chatService->getUserInfo(friendId));
    }

	void IMManager::setOfflineServer(String ^offlineServerAddress, int offlineServerPort)
	{
		chatService->setOfflineServer(DataConvertionUtility::ToNativeString(offlineServerAddress), offlineServerPort);
	}

	void IMManager::setAuthenticationServer(String ^authenticationServerAddress, int authenticationServerPort)
	{
		chatService->setAuthenticationServer(DataConvertionUtility::ToNativeString(authenticationServerAddress), authenticationServerPort);
	}

	ManagedApiStatus^ IMManager::requestForOffline(long long messageDate, long long blockUpdateDate)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->requestForOffline(messageDate, blockUpdateDate));
	}



	ManagedApiStatus^ IMManager::registerFriendChat(UserIdentity userId, String ^userName, UserIdentity friendId, String ^friendName, String ^friendUrl, String ^registerServerAddress, int registerServerPort, int deviceType, String ^deviceToken, int appType, int status, int mood, int iosVoipPush, long long authRegistrationTime, int profileType)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->registerFriendChat(userId, DataConvertionUtility::ToNativeString(userName), friendId, DataConvertionUtility::ToNativeString(friendName), DataConvertionUtility::ToNativeString(friendUrl), DataConvertionUtility::ToNativeString(registerServerAddress), registerServerPort, deviceType, DataConvertionUtility::ToNativeString(deviceToken), appType, status, mood, iosVoipPush, authRegistrationTime, profileType));
	}

	bool IMManager::isExistsFriendConnection(UserIdentity userId, UserIdentity friendId)
	{
		return chatService->isExistsFriendConnection(userId, friendId);
	}

	ManagedApiStatus^ IMManager::unregisterFriendChat(UserIdentity userId, UserIdentity friendId, int status, int mood)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->unregisterFriendChat(userId, friendId, status, mood));
	}

	ManagedApiStatus^ IMManager::updateFriendRegisterServer(UserIdentity userId, UserIdentity friendId, String ^registerServerAddress, int registerServerPort)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->updateFriendRegisterServer(userId, friendId, DataConvertionUtility::ToNativeString(registerServerAddress), registerServerPort));
	}

	ManagedApiStatus^ IMManager::updateFriendStatusAndMood(UserIdentity userId, UserIdentity friendId, int status, int mood)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->updateFriendStatusAndMood(userId, friendId, status, mood));
	}

	ManagedApiStatus^ IMManager::sendFriendChat(String ^packetId, UserIdentity userId, UserIdentity friendId, int messageType, int secretTimeout, String ^message, long long messageDate, bool isSecretVisible)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->sendFriendChat(DataConvertionUtility::ToNativeString(packetId), userId, friendId, messageType, secretTimeout, DataConvertionUtility::ToNativeString(message), messageDate, isSecretVisible));
	}

	ManagedApiStatus^ IMManager::dontSendPendingMessages(UserIdentity userId, UserIdentity friendId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->dontSendPendingMessages(userId, friendId));
	}

	ManagedApiStatus^ IMManager::sendFriendCallBusyMessage(UserIdentity userId, UserIdentity friendId, String ^message, long long messageDate, String ^packetId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->sendFriendCallBusyMessage(userId, friendId, DataConvertionUtility::ToNativeString(message), messageDate, DataConvertionUtility::ToNativeString(packetId)));
	}

	ManagedApiStatus^ IMManager::sendFriendCallLogMessage(UserIdentity userId, UserIdentity friendId, String ^message, long long messageDate, String ^packetId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->sendFriendCallLogMessage(userId, friendId, DataConvertionUtility::ToNativeString(message), messageDate, DataConvertionUtility::ToNativeString(packetId)));
	}

	ManagedApiStatus^ IMManager::editFriendChat(String ^packetId, UserIdentity userId, UserIdentity friendId, int messageType, int secretTimeout, String ^message, long long messageDate, bool isSecretVisible)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->editFriendChat(DataConvertionUtility::ToNativeString(packetId), userId, friendId, messageType, secretTimeout, DataConvertionUtility::ToNativeString(message), messageDate, isSecretVisible));
	}

	ManagedApiStatus^ IMManager::seenFriendChat(UserIdentity userId, UserIdentity friendId, const Platform::Array<ManagedSeenPacketDTO^> ^seenPacketList)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->seenFriendChat(userId, friendId, DataConvertionUtility::ToNativeCollection(seenPacketList)));
	}

	ManagedApiStatus^ IMManager::typingFriendChat(UserIdentity userId, UserIdentity friendId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->typingFriendChat(userId, friendId));
	}

	ManagedApiStatus^ IMManager::deleteFriendChatMessage(UserIdentity userId, UserIdentity friendId, const Platform::Array<String^> ^packetIds)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->deleteFriendChatMessage(userId, friendId, DataConvertionUtility::ToNativeCollection(packetIds)));
	}

	ManagedApiStatus^ IMManager::requestFriendChatHistory(UserIdentity userId, UserIdentity friendId, String ^packetId, int direction, int limit)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->requestFriendChatHistory(userId, friendId, DataConvertionUtility::ToNativeString(packetId), direction, limit));
	}

	ManagedApiStatus^ IMManager::getFriendMessageStatus(UserIdentity userId, UserIdentity friendId, const Platform::Array<String^> ^packetIds)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->getFriendMessageStatus(userId, friendId, DataConvertionUtility::ToNativeCollection(packetIds)));
	}

	ManagedApiStatus^ IMManager::blockFriend(UserIdentity userId, String ^packetId, UserIdentity friendId, long long blockUnblockDate, bool addToBlock)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->blockFriend(userId, DataConvertionUtility::ToNativeString(packetId), friendId, blockUnblockDate, addToBlock));
	}

	ManagedApiStatus^ IMManager::unblockFriend(UserIdentity userId, String ^packetId, UserIdentity friendId, long long blockUnblockDate)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->unblockFriend(userId, DataConvertionUtility::ToNativeString(packetId), friendId, blockUnblockDate));
	}

	Platform::Array<String^>^ IMManager::getPendingFriendMessages(UserIdentity userId)
	{
		return DataConvertionUtility::ToManagedCollection(chatService->getPendingFriendMessages(userId));
	}

	void IMManager::cleanUp(int mood)
	{
		chatService->cleanUp(mood);
	}

	void IMManager::clearRegisteredSessions(int mood)
	{
		chatService->clearRegisteredSessions(mood);
	}

	ManagedFriendInformation^ IMManager::getFriendInformation(UserIdentity userId, UserIdentity friendId)
	{
		return DataConvertionUtility::ToManagedFriendInformation(*chatService->getFriendInformation(userId, friendId));
	}


	Array<UserIdentity> ^IMManager::getRegisteredFriendsList(UserIdentity userId)
	{
		return DataConvertionUtility::ToManagedCollection(chatService->getRegisteredFriendsList(userId));
	}

	Platform::Array<ManagedGroupInformation^>^ IMManager::getRegisteredGroupList()
	{
		return DataConvertionUtility::ToManagedCollection(chatService->getRegisteredGroupList());
	}

	ManagedDataCounter^ IMManager::getDataSentReceived()
	{
		return DataConvertionUtility::ToManagedDataCounter(chatService->getDataSentReceived());
	}


	ManagedApiStatus^ IMManager::registerGroupChat(GroupIdentity groupId, String ^registerServerAddress, int registerServerPort, long long authRegistrationTime)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->registerGroupChat(groupId, DataConvertionUtility::ToNativeString(registerServerAddress), registerServerPort, authRegistrationTime));
	}

	bool IMManager::isExistsGroupConnection(GroupIdentity groupId)
	{
		return chatService->isExistsGroupConnection(groupId);
	}

	ManagedApiStatus^ IMManager::unregisterGroupChat(GroupIdentity groupId, int status, int mood)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->unregisterGroupChat(groupId, status, mood));
	}

	ManagedApiStatus^ IMManager::sendGroupChat(String ^packetId, GroupIdentity groupId, int messageType, String ^message, long long messageDate)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->sendGroupChat(DataConvertionUtility::ToNativeString(packetId), groupId, messageType, DataConvertionUtility::ToNativeString(message), messageDate));
	}

	ManagedApiStatus^ IMManager::editGroupChat(String ^packetId, GroupIdentity groupId, int messageType, String ^message, long long messageDate)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->editGroupChat(DataConvertionUtility::ToNativeString(packetId), groupId, messageType, DataConvertionUtility::ToNativeString(message), messageDate));
	}

	ManagedApiStatus^ IMManager::seenGroupChat(GroupIdentity groupId, const Array<String^> ^packetIds)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->seenGroupChat(groupId, DataConvertionUtility::ToNativeCollection(packetIds)));
	}

	ManagedApiStatus^ IMManager::getGroupMessageSeenList(GroupIdentity groupId, String^ packetId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->getGroupMessageSeenList(groupId, DataConvertionUtility::ToNativeString(packetId)));
	}

	ManagedApiStatus^ IMManager::typingGroupChat(GroupIdentity groupId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->typingGroupChat(groupId));
	}

	ManagedApiStatus^ IMManager::deleteGroupChatMessage(GroupIdentity groupId, const Platform::Array<String^> ^packetIds)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->deleteGroupChatMessage(groupId, DataConvertionUtility::ToNativeCollection(packetIds)));
	}

	ManagedApiStatus^ IMManager::getConversationList(UserIdentity userId, int conversationType, int startIndex, int limit, long long friendOrGroupId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->getConversationList(userId, DataConvertionUtility::ToNativeConversationType(conversationType), startIndex, limit, friendOrGroupId));
	}

	ManagedApiStatus^ IMManager::deleteConversation(UserIdentity userId, const Array<ManagedConversationDTO^> ^conversationList)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->deleteConversation(userId, DataConvertionUtility::ToNativeCollection(conversationList)));
	}
	ManagedApiStatus^ IMManager::markConversationSeen(UserIdentity userId, const Array<ManagedConversationDTO^> ^conversationList)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->markConversationSeen(userId, DataConvertionUtility::ToNativeCollection(conversationList)));
	}


	void IMManager::updateUserPassword(String ^password)
	{
		chatService->updateUserPassword(DataConvertionUtility::ToNativeString(password));
	}

	ManagedApiStatus^ IMManager::changeGroupName(GroupIdentity groupId, String ^groupName)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->changeGroupName(groupId, DataConvertionUtility::ToNativeString(groupName)));
	}

	ManagedApiStatus^ IMManager::changeGroupUrl(GroupIdentity groupId, String ^groupUrl)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->changeGroupUrl(groupId, DataConvertionUtility::ToNativeString(groupUrl)));
	}

	ManagedApiStatus^ IMManager::addGroupMembers(GroupIdentity groupId, const Platform::Array<ManagedMemberDTO^> ^memberList)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->addGroupMembers(groupId, DataConvertionUtility::ToNativeCollection(memberList)));
	}

	ManagedApiStatus^ IMManager::removeGroupMembers(GroupIdentity groupId, const Platform::Array<long long> ^memberIds)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->removeGroupMembers(groupId, DataConvertionUtility::ToNativeCollection(memberIds)));
	}

	ManagedApiStatus^ IMManager::leaveGroup(GroupIdentity groupId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->leaveGroup(groupId));
	}

	ManagedApiStatus^ IMManager::changeGroupMemberStatus(GroupIdentity groupId, const Platform::Array<ManagedMemberDTO^> ^memberList)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->changeGroupMemberStatus(groupId, DataConvertionUtility::ToNativeCollection(memberList)));
	}

	ManagedApiStatus^ IMManager::createGroup(GroupIdentity groupId, String ^groupName, String ^groupUrl, const Platform::Array<ManagedMemberDTO^> ^memberList)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->createGroup(groupId, DataConvertionUtility::ToNativeString(groupName), DataConvertionUtility::ToNativeString(groupUrl), DataConvertionUtility::ToNativeCollection(memberList)));
	}

	ManagedApiStatus^ IMManager::requestGroupChatHistory(GroupIdentity groupId, String ^packetId, int direction, int limit)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->requestGroupChatHistory(groupId, DataConvertionUtility::ToNativeString(packetId), direction, limit));
	}

	ManagedApiStatus^ IMManager::getGroupInformationWithMembers(GroupIdentity groupId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->getGroupInformationWithMembers(groupId));
	}

	Platform::Array<String^>^ IMManager::getPendingGroupMessages()
	{
		return DataConvertionUtility::ToManagedCollection(chatService->getPendingGroupMessages());
	}

	ManagedGroupInformation^ IMManager::getGroupInformation(GroupIdentity groupId)
	{
		return DataConvertionUtility::ToManagedGroupInformation(*chatService->getGroupInformation(groupId));
	}





	ManagedApiStatus^ IMManager::registerPublicRoomChat(ManagedRoomIdentity roomId, String ^memberName, String ^memberUrl, UserIdentity ringId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->registerPublicRoomChat(DataConvertionUtility::ToNativeString(roomId), DataConvertionUtility::ToNativeString(memberName), DataConvertionUtility::ToNativeString(memberUrl), ringId));
	}

	ManagedApiStatus^ IMManager::sendPublicRoomChat(String ^packetId, ManagedRoomIdentity roomId, int messageType, String ^message, long long messageDate, String ^memberFullName, String ^memberProfileUrl)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->sendPublicRoomChat(DataConvertionUtility::ToNativeString(packetId), DataConvertionUtility::ToNativeString(roomId), messageType, DataConvertionUtility::ToNativeString(message), messageDate, DataConvertionUtility::ToNativeString(memberFullName), DataConvertionUtility::ToNativeString(memberProfileUrl)));
	}

	ManagedApiStatus^ IMManager::editPublicRoomChat(String ^packetId, ManagedRoomIdentity roomId, int messageType, String ^message, long long messageDate, String ^memberFullName, String ^memberProfileUrl)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->editPublicRoomChat(DataConvertionUtility::ToNativeString(packetId), DataConvertionUtility::ToNativeString(roomId), messageType, DataConvertionUtility::ToNativeString(message), messageDate, DataConvertionUtility::ToNativeString(memberFullName), DataConvertionUtility::ToNativeString(memberProfileUrl)));
	}

	ManagedApiStatus^ IMManager::getRoomList(int startIndex, int limit)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->getRoomList(startIndex, limit));
	}

	ManagedApiStatus^ IMManager::searchRoomList(String ^searchName, String ^country, String ^category, int startIndex, int limit)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->searchRoomList(DataConvertionUtility::ToNativeString(searchName), DataConvertionUtility::ToNativeString(country), DataConvertionUtility::ToNativeString(category), startIndex, limit));
	}

	ManagedApiStatus^ IMManager::deletePublicChatMessage(ManagedRoomIdentity roomId, const Array<String^> ^packetIds)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->deletePublicChatMessage(DataConvertionUtility::ToNativeString(roomId), DataConvertionUtility::ToNativeCollection(packetIds)));
	}

	ManagedApiStatus^ IMManager::likePublicChatMessage(String ^packetId, ManagedRoomIdentity roomId, UserIdentity recipientId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->likePublicChatMessage(DataConvertionUtility::ToNativeString(packetId), DataConvertionUtility::ToNativeString(roomId), recipientId));
	}

	ManagedApiStatus^ IMManager::unlikePublicChatMessage(String ^packetId, ManagedRoomIdentity roomId, UserIdentity recipientId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->unlikePublicChatMessage(DataConvertionUtility::ToNativeString(packetId), DataConvertionUtility::ToNativeString(roomId), recipientId));
	}

	ManagedApiStatus^ IMManager::reportPublicChatMessage(String ^packetId, ManagedRoomIdentity roomId, UserIdentity recipientId, String ^reportMessage)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->reportPublicChatMessage(DataConvertionUtility::ToNativeString(packetId), DataConvertionUtility::ToNativeString(roomId), recipientId, DataConvertionUtility::ToNativeString(reportMessage)));
	}

	ManagedApiStatus^ IMManager::getPublicChatLikeMemberList(ManagedRoomIdentity roomId, String ^packetId, UserIdentity lastLikerId, int limit)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->getPublicChatLikeMemberList(DataConvertionUtility::ToNativeString(roomId), DataConvertionUtility::ToNativeString(packetId), lastLikerId, limit));
	}

	ManagedApiStatus^ IMManager::getPublicChatRoomCategoryList(String ^pagingState, int limit)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->getPublicChatRoomCategoryList(DataConvertionUtility::ToNativeString(pagingState), limit));
	}


	ManagedApiStatus^ IMManager::unregisterPublicRoomChat(ManagedRoomIdentity roomId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->unregisterPublicRoomChat(DataConvertionUtility::ToNativeString(roomId)));
	}

	ManagedApiStatus^ IMManager::typingPublicRoomChat(ManagedRoomIdentity roomId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->typingPublicRoomChat(DataConvertionUtility::ToNativeString(roomId)));
	}

	bool IMManager::isExistsRoomConnection(ManagedRoomIdentity roomId)
	{
		return chatService->isExistsRoomConnection(DataConvertionUtility::ToNativeString(roomId));
	}

	ManagedApiStatus^ IMManager::getRoomInformation(ManagedRoomIdentity roomId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->getRoomInformation(DataConvertionUtility::ToNativeString(roomId)));
	}

	ManagedApiStatus^ IMManager::requestRoomChatHistory(ManagedRoomIdentity roomId, String ^packetId, int year, int month, int direction, int limit)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->requestRoomChatHistory(DataConvertionUtility::ToNativeString(roomId), DataConvertionUtility::ToNativeString(packetId), year, month, direction, limit));
	}

	ManagedApiStatus^ IMManager::getRoomListWithHistory(int startIndex, int limit)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->getRoomListWithHistory(startIndex, limit));
	}

	ManagedApiStatus^ IMManager::getRoomMemberList(ManagedRoomIdentity roomId, String ^pagingState, int limit)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->getRoomMemberList(DataConvertionUtility::ToNativeString(roomId), DataConvertionUtility::ToNativeString(pagingState), limit));
	}

	void IMManager::enterPublicChatScreen(String ^roomId)
	{
		return chatService->enterPublicChatScreen(DataConvertionUtility::ToNativeString(roomId));
	}

	void IMManager::exitPublicChatScreen(String ^roomId)
	{
		return chatService->exitPublicChatScreen(DataConvertionUtility::ToNativeString(roomId));
	}

	void IMManager::addUserPage(UserIdentity pageId)
	{
		chatService->addUserPage(pageId);
	}

	void IMManager::removeUserPage(UserIdentity pageId)
	{
		chatService->removeUserPage(pageId);
	}

	ManagedPacketTimeID^ IMManager::generatePacketId(UserIdentity userOrPageId)
	{
		return DataConvertionUtility::ToManagedPacketTimeID(chatService->generatePacketId(userOrPageId));
	}

	ManagedPacketTimeID^ IMManager::generatePacketId(long long timeMili, UserIdentity userId)
	{
		return DataConvertionUtility::ToManagedPacketTimeID(chatService->generatePacketId(timeMili, userId));
	}

	String^ IMManager::generatePacketId_v2()
	{
		return DataConvertionUtility::ToManagedString(imsdk::Chat::generatePacketId_v2());
	}

	GroupIdentity IMManager::generateGroupId()
	{
		return chatService->generateGroupId();
	}

	long long IMManager::getCurrentServerSyncedTime()
	{
		return chatService->getCurrentServerSyncedTime();
	}

	long long IMManager::UUIDToTime(String ^UUID)
	{
		return chatService->UUIDToTime(DataConvertionUtility::ToNativeString(UUID));
	}


	bool IMManager::checkInternetConnection()
	{
		return chatService->checkInternetConnection();
	}


	bool IMManager::sendFriendChatMedia(UserIdentity userId, UserIdentity friendId, String ^packetId, int mediaType, String ^filePath, String ^caption, int widthOrFileSize, int heightOrDuration, int secretTimeout, long long messageDate, bool isSecretVisible)
	{
		return chatService->sendFriendChatMedia(userId, friendId, DataConvertionUtility::ToNativeString(packetId), mediaType, DataConvertionUtility::ToNativeString(filePath), DataConvertionUtility::ToNativeString(caption), widthOrFileSize, heightOrDuration, secretTimeout, messageDate, isSecretVisible);
	}


	bool IMManager::downloadFriendChatMedia(UserIdentity userId, UserIdentity friendId, String ^packetId, String ^manifestUrl, int mediaType, int secretTimeout)
	{
		return chatService->downloadFriendChatMedia(userId, friendId, DataConvertionUtility::ToNativeString(packetId), DataConvertionUtility::ToNativeString(manifestUrl), mediaType, secretTimeout);
	}

	bool IMManager::acceptChatMedia(String ^packetId)
	{
		return chatService->acceptChatMedia(DataConvertionUtility::ToNativeString(packetId));
	}

	bool IMManager::sendGroupChatMedia(GroupIdentity groupId, String ^packetId, int mediaType, String ^filePath, String ^caption, int widthOrFileSize, int heightOrDuration, long long messageDate)
	{
		return chatService->sendGroupChatMedia(groupId, DataConvertionUtility::ToNativeString(packetId), mediaType, DataConvertionUtility::ToNativeString(filePath), DataConvertionUtility::ToNativeString(caption), widthOrFileSize, heightOrDuration, messageDate);
	}
	bool IMManager::downloadGroupChatMedia(GroupIdentity groupId, UserIdentity friendId, String ^packetId, String ^manifestUrl, int mediaType)
	{
		return chatService->downloadGroupChatMedia(groupId, friendId, DataConvertionUtility::ToNativeString(packetId), DataConvertionUtility::ToNativeString(manifestUrl), mediaType);
	}

	void IMManager::cancelChatMediaTransfer(String ^packetId)
	{
		chatService->cancelChatMediaTransfer(DataConvertionUtility::ToNativeString(packetId));
	}
	Array<String^> ^IMManager::getPendingChatMediaList(int conversationType, bool isUpload, bool isChunked)
	{
		return DataConvertionUtility::ToManagedCollection(chatService->getPendingChatMediaList(DataConvertionUtility::ToNativeConversationType(conversationType), isUpload, isChunked));
	}


	bool IMManager::isChatMediaTransferInProgress(String ^packetId)
	{
		return chatService->isChatMediaTransferInProgress(DataConvertionUtility::ToNativeString(packetId));
	}
	void IMManager::updateAppSessionID(String ^appSessionId)
	{
		chatService->updateAppSessionID(DataConvertionUtility::ToNativeString(appSessionId));
	}

	//Live-stream-chat
	ManagedApiStatus^ IMManager::registerLiveStreamChat(UserIdentity publisherId, String ^registerServerAddress, int registerServerPort, String ^fullName)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->registerLiveStreamChat(publisherId, DataConvertionUtility::ToNativeString(registerServerAddress), registerServerPort, DataConvertionUtility::ToNativeString(fullName)));
	}
	ManagedApiStatus^ IMManager::unregisterLiveStreamChat(UserIdentity publisherId, int onlineStatus, int onlineMood)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->unregisterLiveStreamChat(publisherId, onlineStatus, onlineMood));
	}
	ManagedApiStatus^ IMManager::typingLiveStreamChat(UserIdentity publisherId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->typingLiveStreamChat(publisherId));
	}
	ManagedApiStatus^ IMManager::sendLiveStreamChat(String ^packetId, UserIdentity publisherId, int messageType, String ^message, long long messageDate)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->sendLiveStreamChat(DataConvertionUtility::ToNativeString(packetId), publisherId, messageType, DataConvertionUtility::ToNativeString(message), messageDate));
	}

	ManagedApiStatus^ IMManager::blockUserFromLiveStreamChat(UserIdentity blockedUserId, String ^packetId)
	{
		return DataConvertionUtility::ToManagedApiStatus(chatService->blockUserFromLiveStreamChat(blockedUserId, DataConvertionUtility::ToNativeString(packetId)));
	}

}