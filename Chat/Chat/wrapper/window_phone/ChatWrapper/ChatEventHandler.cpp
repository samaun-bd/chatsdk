#include "ChatEventHandler.h"
//#include "DataConvertionUtility.h"

using namespace Platform;

namespace ChatWrapper
{
	ChatEventHandler::ChatEventHandler(IMListener ^listener)
	{
		this->listener = listener;
	}
	void ChatEventHandler::onEventHandlerAttached()
	{
		listener->onEventHandlerAttached();
	}
	void ChatEventHandler::onEventHandlerDetached()
	{
		listener->onEventHandlerDetached();
	}

    void ChatEventHandler::onActivaeOrDeactivateUserAccountStatus(UserIdentity userId, const string &packetId, bool isAccountActivate, bool status)
	{
        listener->onActivaeOrDeactivateUserAccountStatus(userId, DataConvertionUtility::ToManagedString(packetId), isAccountActivate, status);
	}

    void ChatEventHandler::onGetUserInfoReceived(UserIdentity userId, UserIdentity friendId, const std::string &packetId, std::string friendName, UserIdentity friendRingId, std::string friendProfileImageUrl, int friendProfileType)
    {
        listener->onGetUserInfoReceived(userId, friendId, DataConvertionUtility::ToManagedString(packetId), DataConvertionUtility::ToManagedString(friendName), friendRingId, DataConvertionUtility::ToManagedString(friendProfileImageUrl), friendProfileType);
    }
    void ChatEventHandler::onGetUserInfoFailure(UserIdentity userId, UserIdentity friendId, const std::string &packetId)
    {
        listener->onGetUserInfoFailure(userId, friendId, DataConvertionUtility::ToManagedString(packetId));
    }

	void ChatEventHandler::onFriendUnregistered(UserIdentity userId, UserIdentity friendId, int onlineStatus, int onlineMood, bool fromAnonymousUser, int profileType)
	{
		listener->onFriendUnregistered(userId, friendId, onlineStatus, onlineMood, fromAnonymousUser, profileType);
	}
	void ChatEventHandler::onFriendChatRegisterSuccess(UserIdentity userId, UserIdentity friendId, long long serverDate, const string &packetId, bool fromAnonymousUser)
	{
		listener->onFriendChatRegisterSuccess(userId, friendId, serverDate, DataConvertionUtility::ToManagedString(packetId), fromAnonymousUser);
	}
	void ChatEventHandler::onFriendChatRegisterFailure(UserIdentity userId, UserIdentity friendId, const string &packetId, bool fromAnonymousUser)
	{
		listener->onFriendChatRegisterFailure(userId, friendId, DataConvertionUtility::ToManagedString(packetId), fromAnonymousUser);
	}
	void ChatEventHandler::onFriendRegistrationExpired(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser)
	{
		listener->onFriendRegistrationExpired(userId, friendId, fromAnonymousUser);
	}
	void ChatEventHandler::onFriendChatTyping(UserIdentity userId, UserIdentity friendid, bool fromAnonymousUser)
	{
		listener->onFriendChatTyping(userId, friendid, fromAnonymousUser);
	}
	void ChatEventHandler::onFriendChatReceived(UserIdentity senderId, UserIdentity receiverId, const string &packetId, int messageType, int timeout, const string &message, long long messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser)
	{
		listener->onFriendChatReceived(senderId, receiverId, DataConvertionUtility::ToManagedString(packetId), messageType, timeout, DataConvertionUtility::ToManagedString(message), messageDate, isSecretVisible, fromOnline, fromAnonymousUser);
	}
	void ChatEventHandler::onFriendChatDelivered(UserIdentity userId, UserIdentity friendid, const string &packetId, bool fromAnonymousUser, bool isEdited, bool fromOnline)
	{
		listener->onFriendChatDelivered(userId, friendid, DataConvertionUtility::ToManagedString(packetId), fromAnonymousUser, isEdited, fromOnline);
	}
	void ChatEventHandler::onFriendChatSent(UserIdentity userId, UserIdentity friendId, const string &packetId, bool fromAnonymousUser)
	{
		listener->onFriendChatSent(userId, friendId, DataConvertionUtility::ToManagedString(packetId), fromAnonymousUser);
	}
	void ChatEventHandler::onFriendChatSeen(UserIdentity userId, UserIdentity friendid, const vector<SeenPacketDTO> &seenPacketList, bool fromAnonymousUser)
	{
		listener->onFriendChatSeen(userId, friendid, DataConvertionUtility::ToManagedCollection(seenPacketList), fromAnonymousUser);
	}
	void ChatEventHandler::onFriendChatSeenConfirmed(UserIdentity userId, UserIdentity friendid, vector<SeenPacketDTO> &packetIds, bool fromAnonymousUser)
	{
		listener->onFriendChatSeenConfirmed(userId, friendid, DataConvertionUtility::ToManagedCollection(packetIds), fromAnonymousUser);
	}
	void ChatEventHandler::onFriendChatEdited(UserIdentity senderId, UserIdentity receiverId, const string &packetId, int messageType, int timeout, const string &message, long long messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser)
	{
		listener->onFriendChatEdited(senderId, receiverId, DataConvertionUtility::ToManagedString(packetId), messageType, timeout, DataConvertionUtility::ToManagedString(message), messageDate, isSecretVisible, fromOnline, fromAnonymousUser);
	}
	void ChatEventHandler::onFriendChatFailedToSend(UserIdentity userId, UserIdentity friendId, const string &packetId, bool fromAnonymousUser)
	{
		listener->onFriendChatFailedToSend(userId, friendId, DataConvertionUtility::ToManagedString(packetId), fromAnonymousUser);
	}
	void ChatEventHandler::onFriendChatDeleted(UserIdentity senderId, UserIdentity friendid, const vector<string> &packetId, bool fromAnonymousUser)
	{
		listener->onFriendChatDeleted(senderId, friendid, DataConvertionUtility::ToManagedCollection(packetId), fromAnonymousUser);
	}
	void ChatEventHandler::onFriendChatDeleteRequestStatus(UserIdentity userId, UserIdentity friendid, const string &packetId, const std::vector<std::string> &packetIds, bool fromAnonymousUser, bool status)
	{
		listener->onFriendChatDeleteRequestStatus(userId, friendid, DataConvertionUtility::ToManagedString(packetId), DataConvertionUtility::ToManagedCollection(packetIds), fromAnonymousUser, status);
	}
	void ChatEventHandler::onFriendChatIdle(UserIdentity friendid, bool fromAnonymousUser)
	{
		listener->onFriendChatIdle(friendid, fromAnonymousUser);
	}
	void ChatEventHandler::onFriendHistoryMessageReceived(UserIdentity userId, UserIdentity friendId, const vector<SDKMessageDTO> &friendHistoryMessageList, int direction) /******/
	{
		listener->onFriendHistoryMessageReceived(userId, friendId, DataConvertionUtility::ToManagedCollection(friendHistoryMessageList), direction);
	}
	void ChatEventHandler::onFriendMessagesStatusReceived(UserIdentity userId, UserIdentity friendId, const vector<FriendMessageStatusDTO> &messageList)
	{
		listener->onFriendMessagesStatusReceived(userId, friendId, DataConvertionUtility::ToManagedCollection(messageList));
	}
	void ChatEventHandler::onFriendHistoryCompleted(UserIdentity userId, UserIdentity friendId, int direction)
	{
		listener->onFriendHistoryCompleted(userId, friendId, direction);
	}
	void ChatEventHandler::onFriendHistoryMessageRequestStatus(UserIdentity userId, UserIdentity friendId, const string &packetId, bool status)
	{
		listener->onFriendHistoryMessageRequestStatus(userId, friendId, DataConvertionUtility::ToManagedString(packetId), status);
	}


	void ChatEventHandler::shouldCheckFriendPresence(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser, int profileType)
	{
		listener->shouldCheckFriendPresence(userId, friendId, fromAnonymousUser, profileType);
	}
	void ChatEventHandler::shouldCheckServerAddressForFriend(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser)
	{
		listener->shouldCheckServerAddressForFriend(userId, friendId, fromAnonymousUser);
	}


	void ChatEventHandler::onBlocked(UserIdentity blockerId, UserIdentity blockedId, long long blockUnblockDate, bool addToBlock) /******/
	{
		listener->onBlocked(blockerId, blockedId, blockUnblockDate, addToBlock);
	}
	void ChatEventHandler::onUnblocked(UserIdentity blockerId, UserIdentity blockedId, long long blockUnblockDate) /******/
	{
		listener->onUnblocked(blockerId, blockedId, blockUnblockDate);
	}
	void ChatEventHandler::onBlockUnblockRequestStatus(UserIdentity userid, UserIdentity friendid, const string &packetId, long long blockUnblockDate, bool status, bool fromBlockRequest) /******/
	{
		listener->onBlockUnblockRequestStatus(userid, friendid, DataConvertionUtility::ToManagedString(packetId), blockUnblockDate, status, fromBlockRequest);
	}


	void ChatEventHandler::onFriendChatConversationListReceived(UserIdentity userId, const vector<SDKMessageDTO> &conversationList)
	{
		listener->onFriendChatConversationListReceived(userId, DataConvertionUtility::ToManagedCollection(conversationList));
	}

	void ChatEventHandler::onGroupChatConversationListReceived(const vector<SDKMessageDTO> &conversationList)
	{
		listener->onGroupChatConversationListReceived(DataConvertionUtility::ToManagedCollection(conversationList));
	}

	void ChatEventHandler::onChatConversationListRequestStatus(UserIdentity userId, long long friendOrGroupId, const string &packetId, bool status)
	{
		listener->onChatConversationListRequestStatus(userId, friendOrGroupId, DataConvertionUtility::ToManagedString(packetId), status);
	}

	void ChatEventHandler::onChatConversationListCompleted(UserIdentity userId)
	{
		listener->onChatConversationListCompleted(userId);
	}

	void ChatEventHandler::onConversationListDeleteRequestStatus(UserIdentity userId, const string &packetId, bool status)
	{
		listener->onConversationListDeleteRequestStatus(userId, DataConvertionUtility::ToManagedString(packetId), status);
	}

	void ChatEventHandler::onConversationListMarkAsSeenRequestStatus(UserIdentity userId, const string &packetId, bool status)
	{
		listener->onConversationListMarkAsSeenRequestStatus(userId, DataConvertionUtility::ToManagedString(packetId), status);
	}


	void ChatEventHandler::onGroupChatRegisterSuccess(GroupIdentity groupId, long long serverDate, const string &packetId)
	{
		listener->onGroupChatRegisterSuccess(groupId, serverDate, DataConvertionUtility::ToManagedString(packetId));
	}
	void ChatEventHandler::onGroupChatRegisterFailure(GroupIdentity groupId, const string &packetId)
	{
		listener->onGroupChatRegisterFailure(groupId, DataConvertionUtility::ToManagedString(packetId));
	}
	void ChatEventHandler::onGroupRegistrationExpired(GroupIdentity groupId, long long lastActivityTime)
	{
		listener->onGroupRegistrationExpired(groupId, lastActivityTime);
	}
	void ChatEventHandler::onGroupChatSent(GroupIdentity groupId, const string &packetId, bool isEdited)
	{
		listener->onGroupChatSent(groupId, DataConvertionUtility::ToManagedString(packetId), isEdited);
	}
	void ChatEventHandler::onGroupChatReceived(UserIdentity senderId, GroupIdentity groupid, const string &packetId, int messageType, const string &message, long long messageDate, bool fromOnline)
	{
		listener->onGroupChatReceived(senderId, groupid, DataConvertionUtility::ToManagedString(packetId), messageType, DataConvertionUtility::ToManagedString(message), messageDate, fromOnline);
	}
	void ChatEventHandler::onGroupChatDelivered(UserIdentity friendid, GroupIdentity groupid, const string &packetId)
	{
		listener->onGroupChatDelivered(friendid, groupid, DataConvertionUtility::ToManagedString(packetId));
	}
	void ChatEventHandler::onGroupChatDeleted(UserIdentity friendid, GroupIdentity groupid, const vector<string> &packetIdList)
	{
		listener->onGroupChatDeleted(friendid, groupid, DataConvertionUtility::ToManagedCollection(packetIdList));
	}
	void ChatEventHandler::onGroupChatDeleteRequestStatus(GroupIdentity groupid, const string &packetId, const std::vector<std::string> &packetIds, bool status)
	{
		listener->onGroupChatDeleteRequestStatus(groupid, DataConvertionUtility::ToManagedString(packetId), DataConvertionUtility::ToManagedCollection(packetIds), status);
	}
	void ChatEventHandler::onGroupChatSeen(GroupIdentity groupid, const vector<string> &packetIds)
	{
		listener->onGroupChatSeen(groupid, DataConvertionUtility::ToManagedCollection(packetIds));
	}
	void ChatEventHandler::onGroupChatSeenRequestStatus(GroupIdentity groupid, const vector<string> &packetIds, bool status)
	{
		listener->onGroupChatSeenRequestStatus(groupid, DataConvertionUtility::ToManagedCollection(packetIds), status);
	}
	void ChatEventHandler::onGroupChatMessageSeenListReceived(GroupIdentity groupId, const string &packetId, const vector<MemberDTO> &memberList)
	{
		listener->onGroupChatMessageSeenListReceived(groupId, DataConvertionUtility::ToManagedString(packetId), DataConvertionUtility::ToManagedCollection(memberList));
	}
	void ChatEventHandler::onGroupChatMessageSeenListRequestStatus(GroupIdentity groupId, const string &requestPacketId, const string &messagePacketId, bool status)
	{
		listener->onGroupChatMessageSeenListRequestStatus(groupId, DataConvertionUtility::ToManagedString(requestPacketId), DataConvertionUtility::ToManagedString(messagePacketId), status);
	}
	void ChatEventHandler::onGroupChatTyping(UserIdentity friendid, GroupIdentity groupid)
	{
		listener->onGroupChatTyping(friendid, groupid);
	}
	void ChatEventHandler::onGroupChatIdle(UserIdentity friendid, GroupIdentity groupid)
	{
		listener->onGroupChatIdle(friendid, groupid);
	}
	void ChatEventHandler::onGroupChatEdited(UserIdentity senderId, GroupIdentity groupId, const string &packetId, int messageType, const string &message, long long messageDate, bool fromOnline)
	{
		listener->onGroupChatEdited(senderId, groupId, DataConvertionUtility::ToManagedString(packetId), messageType, DataConvertionUtility::ToManagedString(message), messageDate, fromOnline);
	}
	void ChatEventHandler::onGroupMemberRemoveLeaveRequestStatus(GroupIdentity groupId, const string &packetId, bool status, const vector<MemberDTO> &memberList) /******/
	{
		listener->onGroupMemberRemoveLeaveRequestStatus(groupId, DataConvertionUtility::ToManagedString(packetId), status, DataConvertionUtility::ToManagedCollection(memberList));
	}
	void ChatEventHandler::onGroupMemberRemovedOrLeft(UserIdentity friendid, GroupIdentity groupid, const vector<UserIdentity> &memberList, const string &packetId)
	{
		listener->onGroupMemberRemovedOrLeft(friendid, groupid, DataConvertionUtility::ToManagedCollection(memberList), DataConvertionUtility::ToManagedString(packetId));
	}
	void ChatEventHandler::onGroupMemberAddRequestStatus(GroupIdentity groupId, const string &packetId, bool status, const vector<MemberDTO> &memberList) /******/
	{
		listener->onGroupMemberAddRequestStatus(groupId, DataConvertionUtility::ToManagedString(packetId), status, DataConvertionUtility::ToManagedCollection(memberList));
	}
	void ChatEventHandler::onGroupMemberAdded(UserIdentity friendid, GroupIdentity groupid, const vector<MemberDTO> &memberList, const string &packetId)
	{
		listener->onGroupMemberAdded(friendid, groupid, DataConvertionUtility::ToManagedCollection(memberList), DataConvertionUtility::ToManagedString(packetId));
	}
	void ChatEventHandler::onGroupMemberStatusChangeRequestStatus(GroupIdentity groupId, const string &packetId, bool status, const vector<MemberDTO> &memberList) /******/
	{
		listener->onGroupMemberStatusChangeRequestStatus(groupId, DataConvertionUtility::ToManagedString(packetId), status, DataConvertionUtility::ToManagedCollection(memberList));
	}
	void ChatEventHandler::onGroupMemberStatusChanged(UserIdentity senderid, GroupIdentity groupid, const vector<MemberDTO> &memberList, const string &packetId)
	{
		listener->onGroupMemberStatusChanged(senderid, groupid, DataConvertionUtility::ToManagedCollection(memberList), DataConvertionUtility::ToManagedString(packetId));
	}
	void ChatEventHandler::onGroupChatFailedToSend(GroupIdentity groupId, const string &packetId)
	{
		listener->onGroupChatFailedToSend(groupId, DataConvertionUtility::ToManagedString(packetId));
	}
	void ChatEventHandler::shouldCheckServerAddressForGroup(GroupIdentity groupId)
	{
		listener->shouldCheckServerAddressForGroup(groupId);
	}



	void ChatEventHandler::shouldCheckOfflineServerAddress()
	{
		listener->shouldCheckOfflineServerAddress();
	}
	void ChatEventHandler::onServerTimeSynced(long long timeDifference)
	{
		listener->onServerTimeSynced(timeDifference);
	}
	void ChatEventHandler::shouldUpdateUserPassword()
	{
		listener->shouldUpdateUserPassword();
	}
	void ChatEventHandler::onSDKError(int errorCode, const string &packetId)
	{
		listener->onSDKError(errorCode, DataConvertionUtility::ToManagedString(packetId));
	}


	void ChatEventHandler::onGroupHistoryMessageReceived(GroupIdentity groupId, const vector<SDKMessageDTO> &groupHistoryMessageList, int direction) /******/
	{
		listener->onGroupHistoryMessageReceived(groupId, DataConvertionUtility::ToManagedCollection(groupHistoryMessageList), direction);
	}
	void ChatEventHandler::onGroupHistoryCompleted(GroupIdentity groupId, int direction)
	{
		listener->onGroupHistoryCompleted(groupId, direction);
	}
	void ChatEventHandler::onGroupInformationWithMembersReceived(GroupIdentity groupId, const string &groupName, const string &groupUrl, const vector<MemberDTO> &memberList)
	{
		listener->onGroupInformationWithMembersReceived(groupId, DataConvertionUtility::ToManagedString(groupName), DataConvertionUtility::ToManagedString(groupUrl), DataConvertionUtility::ToManagedCollection(memberList));
	}
	void ChatEventHandler::onGroupInformationWithMembersRequestStatus(GroupIdentity groupId, const string &packetId, bool status)
	{
		listener->onGroupInformationWithMembersRequestStatus(groupId, DataConvertionUtility::ToManagedString(packetId), status);
	}
	void ChatEventHandler::onGroupInformationActivityReceived(const vector<GroupActivityDTO> &groupActivityList)
	{
		listener->onGroupInformationActivityReceived(DataConvertionUtility::ToManagedCollection(groupActivityList));
	}
	void ChatEventHandler::onGroupInformationActivityFromHistoryMessageReceived(GroupIdentity groupId, const vector<GroupActivityDTO> &groupActivityList, int direction)
	{
		listener->onGroupInformationActivityFromHistoryMessageReceived(groupId, DataConvertionUtility::ToManagedCollection(groupActivityList), direction);
	}
	void ChatEventHandler::onMyGroupListReceived(const vector<GroupDTO> &myGroupList)
	{
		listener->onMyGroupListReceived(DataConvertionUtility::ToManagedCollection(myGroupList));
	}
	void ChatEventHandler::onGroupCreated(GroupIdentity groupId, const string &packetId, bool status)
	{
		listener->onGroupCreated(groupId, DataConvertionUtility::ToManagedString(packetId), status);
	}

	/*void ChatEventHandler::onGroupInformationChangeRequestStatus(GroupIdentity groupId, const string &packetId, bool status)
	{
	listener->onGroupInformationChangeRequestStatus(groupId, DataConvertionUtility::ToManagedString(packetId), status);
	}*/
	void ChatEventHandler::onGroupNameChangeRequestStatus(GroupIdentity groupId, const string &packetId, bool status, const string &groupName)  /******/
	{
		listener->onGroupNameChangeRequestStatus(groupId, DataConvertionUtility::ToManagedString(packetId), status, DataConvertionUtility::ToManagedString(groupName));
	}
	void ChatEventHandler::onGroupUrlChangeRequestStatus(GroupIdentity groupId, const string &packetId, bool status, const string &groupUrl) /******/
	{
		listener->onGroupUrlChangeRequestStatus(groupId, DataConvertionUtility::ToManagedString(packetId), status, DataConvertionUtility::ToManagedString(groupUrl));
	}
	void ChatEventHandler::onGroupNameChanged(const string &packetId, UserIdentity friendid, GroupIdentity groupid, const string &groupName)
	{
		listener->onGroupNameChanged(DataConvertionUtility::ToManagedString(packetId), friendid, groupid, DataConvertionUtility::ToManagedString(groupName));
	}
	void ChatEventHandler::onGroupUrlChanged(const string &packetId, UserIdentity friendid, GroupIdentity groupid, const string &groupUrl)
	{
		listener->onGroupUrlChanged(DataConvertionUtility::ToManagedString(packetId), friendid, groupid, DataConvertionUtility::ToManagedString(groupUrl));
	}
	void ChatEventHandler::onGroupHistoryMessageRequestStatus(GroupIdentity groupId, const string &packetId, bool status)
	{
		listener->onGroupHistoryMessageRequestStatus(groupId, DataConvertionUtility::ToManagedString(packetId), status);
	}


	//Public Room Chat
	void ChatEventHandler::onPublicRoomChatRegisterSuccess(RoomIdentity &roomId, const string &packetId, int numberOfMembers, long long anonymousId)
	{
		listener->onPublicRoomChatRegisterSuccess(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(packetId), numberOfMembers, anonymousId);
	}
	void ChatEventHandler::onPublicRoomChatRegisterFailure(RoomIdentity &roomId, const string &packetId)
	{
		listener->onPublicRoomChatRegisterFailure(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(packetId));
	}
	void ChatEventHandler::onPublicRoomChatRegistrationExpired(RoomIdentity &roomId)
	{
		listener->onPublicRoomChatRegistrationExpired(DataConvertionUtility::ToManagedString(roomId));
	}
	void ChatEventHandler::onPublicRoomChatDelivered(RoomIdentity &roomId, const string &packetId, bool isEdited)
	{
		listener->onPublicRoomChatDelivered(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(packetId), isEdited);
	}
	void ChatEventHandler::onPublicRoomChatFailedToSend(RoomIdentity &roomId, const string &packetId)
	{
		listener->onPublicRoomChatFailedToSend(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(packetId));
	}
	void ChatEventHandler::onPublicRoomChatReceived(RoomIdentity &roomId, UserIdentity friendId, const string &packetId, int messageType, const string &message, long long messageDate, const string &memberFullName, const string &memberProfileUrl)
	{
		listener->onPublicRoomChatReceived(DataConvertionUtility::ToManagedString(roomId), friendId, DataConvertionUtility::ToManagedString(packetId), messageType, DataConvertionUtility::ToManagedString(message), messageDate, DataConvertionUtility::ToManagedString(memberFullName), DataConvertionUtility::ToManagedString(memberProfileUrl));
	}

	void ChatEventHandler::onPublicRoomListReceived(const vector<RoomDTO> &roomList, bool roomListFromHistory)
	{
		listener->onPublicRoomListReceived(DataConvertionUtility::ToManagedCollection(roomList), roomListFromHistory);
	}

	void ChatEventHandler::onPublicRoomInformationReceived(RoomIdentity &roomId, string &roomName, string &roomUrl, const string &packetId)
	{
		listener->onPublicRoomInformationReceived(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(roomName), DataConvertionUtility::ToManagedString(roomUrl), DataConvertionUtility::ToManagedString(packetId));
	}
	void ChatEventHandler::onPublicRoomChatEdited(RoomIdentity &roomId, UserIdentity friendId, const string &packetId, int messageType, const string &message, long long messageDate, const string &memberFullName, const string &memberProfileUrl)
	{
		listener->onPublicRoomChatEdited(DataConvertionUtility::ToManagedString(roomId), friendId, DataConvertionUtility::ToManagedString(packetId), messageType, DataConvertionUtility::ToManagedString(message), messageDate, DataConvertionUtility::ToManagedString(memberFullName), DataConvertionUtility::ToManagedString(memberProfileUrl));
	}
	void ChatEventHandler::onPublicRoomChatTyping(RoomIdentity &roomId, UserIdentity friendId, const string &memberName)
	{
		listener->onPublicRoomChatTyping(DataConvertionUtility::ToManagedString(roomId), friendId, DataConvertionUtility::ToManagedString(memberName));
	}
	void ChatEventHandler::onPublicChatMemberListReceived(RoomIdentity &roomId, const string &pagingState, const vector<PublicChatMemberDTO> &publicChatMemberList)
	{
		listener->onPublicChatMemberListReceived(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(pagingState), DataConvertionUtility::ToManagedCollection(publicChatMemberList));
	}
	void ChatEventHandler::onPublicChatMemberCountChanged(RoomIdentity &roomId, int numberOfMembers)
	{
		listener->onPublicChatMemberCountChanged(DataConvertionUtility::ToManagedString(roomId), numberOfMembers);
	}
	void ChatEventHandler::shouldCheckServerAddressForRoom(RoomIdentity &roomId)
	{
		listener->shouldCheckServerAddressForRoom(DataConvertionUtility::ToManagedString(roomId));
	}
	void ChatEventHandler::onPublicRoomChatHistoryReceived(RoomIdentity &roomId, const vector<SDKMessageDTO> &publicChatMessageList)
	{
		listener->onPublicRoomChatHistoryReceived(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedCollection(publicChatMessageList));
	}
	void ChatEventHandler::onPublicRoomChatHistoryCompleted(RoomIdentity &roomId)
	{
		listener->onPublicRoomChatHistoryCompleted(DataConvertionUtility::ToManagedString(roomId));
	}
	void ChatEventHandler::onPublicRoomListRequestStatus(const string &packetId, bool requestStatus)
	{
		listener->onPublicRoomListRequestStatus(DataConvertionUtility::ToManagedString(packetId), requestStatus);
	}
	void ChatEventHandler::onPublicRoomInformationRequestFailed(RoomIdentity &roomId, const string &packetId)
	{
		listener->onPublicRoomInformationRequestFailed(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(packetId));
	}
	void ChatEventHandler::onPublicRoomChatHistoryRequestStatus(RoomIdentity &roomId, const string &packetId, bool requestStatus)
	{
		listener->onPublicRoomChatHistoryRequestStatus(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(packetId), requestStatus);
	}
	void ChatEventHandler::onPublicRoomMemberListRequestStatus(RoomIdentity &roomId, const string &packetId, bool requestStatus)
	{
		listener->onPublicRoomMemberListRequestStatus(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(packetId), requestStatus);
	}


	void ChatEventHandler::onPublicChatMessageDeleted(RoomIdentity& roomId, const vector<string> &deletedPacketIds)
	{
		listener->onPublicChatMessageDeleted(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedCollection(deletedPacketIds));
	}
	void ChatEventHandler::onPublicChatMessageLiked(RoomIdentity& roomId, const string& packetId, UserIdentity recipientId)
	{
		listener->onPublicChatMessageLiked(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(packetId), recipientId);
	}
	void ChatEventHandler::onPublicChatMessageUnliked(RoomIdentity& roomId, const string& packetId, UserIdentity messageSenderId)
	{
		listener->onPublicChatMessageUnliked(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(packetId), messageSenderId);
	}
	void ChatEventHandler::onPublicChatMessageReported(RoomIdentity& roomId, const string& packetId, UserIdentity recipientId)
	{
		listener->onPublicChatMessageReported(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(packetId), recipientId);
	}
	void ChatEventHandler::onPublicChatCategoryListReceived(vector<string> &publicChatCategoryList)
	{
		listener->onPublicChatCategoryListReceived(DataConvertionUtility::ToManagedCollection(publicChatCategoryList));
	}
	void ChatEventHandler::onPublicChatLikeMemberListReceived(RoomIdentity &roomId, const string &packetId, const vector<PublicChatMemberDTO> &publicChatMemberList)
	{
		listener->onPublicChatLikeMemberListReceived(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(packetId), DataConvertionUtility::ToManagedCollection(publicChatMemberList));
	}

	void ChatEventHandler::onPublicChatDeleteRequestStatus(RoomIdentity roomId, const string &packetId, bool status)
	{
		listener->onPublicChatDeleteRequestStatus(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(packetId), status);
	}
	void ChatEventHandler::onPublicChatLikeUnlikeRequestStatus(RoomIdentity roomId, const string &requestPacketId, const string &messagePacketId, bool status, bool fromLikeRequest)
	{
		listener->onPublicChatLikeUnlikeRequestStatus(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(requestPacketId), DataConvertionUtility::ToManagedString(messagePacketId), status, fromLikeRequest);
	}
	void ChatEventHandler::onPublicChatReportRequestStatus(RoomIdentity roomId, const string &requestPacketId, const string &messagePacketId, bool status)
	{
		listener->onPublicChatReportRequestStatus(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(requestPacketId), DataConvertionUtility::ToManagedString(messagePacketId), status);
	}
	void ChatEventHandler::onPublicChatLikeMemberListRequestStatus(RoomIdentity roomId, const string &packetId, bool status)
	{
		listener->onPublicChatLikeMemberListRequestStatus(DataConvertionUtility::ToManagedString(roomId), DataConvertionUtility::ToManagedString(packetId), status);
	}
	void ChatEventHandler::onPublicChatCategoryListRequestStatus(const string &packetId, bool status)
	{
		listener->onPublicChatCategoryListRequestStatus(DataConvertionUtility::ToManagedString(packetId), status);
	}




	void ChatEventHandler::onShadowIdsInfoRequestFailed(const string &packetId){}
	void ChatEventHandler::onShadowIdsInfoResponseReceived(const vector<PublicChatMemberDTO> &shadowIdsInfo){}


	void ChatEventHandler::onFileStreamRequestReceived(UserIdentity userId, UserIdentity friendId, FileIdentity fileId){}
	void ChatEventHandler::onFriendFileSessionRequestSuccess(UserIdentity userId, const string &packetId, UserIdentity friendId, FileIdentity fileId, int fileTransferPort){}
	void ChatEventHandler::onFriendFileTransferSessionRequestFailed(UserIdentity userId, const string &packetId, UserIdentity friendId, FileIdentity fileId){}
	void ChatEventHandler::onFriendFileStreamRequestSuccess(UserIdentity userId, const string &packetId, UserIdentity friendId, FileIdentity fileId){}
	void ChatEventHandler::onFriendFileTransferStreamRequestFailed(UserIdentity userId, const string &packetId, UserIdentity friendId, FileIdentity fileId){}


	void ChatEventHandler::onGroupFileStreamRequestReceived(UserIdentity friendId, GroupIdentity groupId, FileIdentity fileId){}
	void ChatEventHandler::onGroupFileSessionRequestSuccess(const string &packetId, GroupIdentity groupId, FileIdentity fileId, int fileTransferPort){}
	void ChatEventHandler::onGroupFileTransferSessionRequestFailed(const string &packetId, GroupIdentity groupId, FileIdentity fileId){}
	void ChatEventHandler::onGroupFileStreamRequestSuccess(const string &packetId, GroupIdentity groupId, FileIdentity fileId){}
	void ChatEventHandler::onGroupFileTransferStreamRequestFailed(const string &packetId, GroupIdentity groupId, FileIdentity fileId){}

	/*void ChatEventHandler::onFileTransferAccepted(UserIdentity friendId, long long fileId, int fileTransferPort){}
	void ChatEventHandler::onFileStreamRequestConfirmed(UserIdentity friendId, long long fileId, int fileTransferPort){}
	void ChatEventHandler::onFileTransferCanceled(UserIdentity friendId, long long fileId){}*/

	void ChatEventHandler::onFileTransferAccepted(UserIdentity friendId, FileIdentity fileId, int fileTransferPort, long long fileOffset){}
	void ChatEventHandler::onFileStreamRequestConfirmed(const string &packetId, UserIdentity friendId, FileIdentity fileId, int fileTransferPort, bool fileAcceptReject){}
	void ChatEventHandler::onFileTransferCanceled(UserIdentity friendId, FileIdentity fileId){}
	void ChatEventHandler::onFileTransferFailed(const string &packetId, UserIdentity friendId, FileIdentity fileId){}


	void ChatEventHandler::onGroupFileRecipientArrived(UserIdentity friendId, GroupIdentity groupId, FileIdentity fileId, int fileTransferPort, bool fileTransferRequestAccepted){}
	void ChatEventHandler::onGroupFileTransferStart(UserIdentity friendId, GroupIdentity groupId, FileIdentity fileId, int fileTransferPort, const string &packetId){}
	void ChatEventHandler::onGroupFileTransferFailed(const string &packetId, UserIdentity friendId, GroupIdentity groupId, FileIdentity fileId){}


	void ChatEventHandler::onFriendGetChatMessageReceived(UserIdentity userId, UserIdentity friendId, const SDKMessageDTO& friendChatMessageDTO){}
	void ChatEventHandler::onGroupGetChatMessageReceived(GroupIdentity groupId, const SDKMessageDTO& groupChatMessageDTO){}
	void ChatEventHandler::onFriendGetChatMessageFailedToSend(UserIdentity userId, UserIdentity friendId, const string& packetId){}
	void ChatEventHandler::onGroupGetChatMessageFailedToSend(GroupIdentity groupId, const string& packetId){}

	void ChatEventHandler::onNetworkDataCounted(const DataCounter& dataCounter)
	{
		listener->onNetworkDataCounted(DataConvertionUtility::ToManagedDataCounter(dataCounter));
	}



	//Live stream chat
	void ChatEventHandler::onLiveStreamChatRegisterSuccess(UserIdentity publisherId, const string &packetId)
	{
		listener->onLiveStreamChatRegisterSuccess(publisherId, DataConvertionUtility::ToManagedString(packetId));
	}
	void ChatEventHandler::onLiveStreamChatRegisterFailure(UserIdentity publisherId, const string &packetId)
	{
		listener->onLiveStreamChatRegisterFailure(publisherId, DataConvertionUtility::ToManagedString(packetId));
	}
	void ChatEventHandler::onLiveStreamChatRegistrationExpired(UserIdentity publisherId)
	{
		listener->onLiveStreamChatRegistrationExpired(publisherId);
	}
	void ChatEventHandler::onLiveStreamChatDelivered(UserIdentity publisherId, const string &packetId)
	{
		listener->onLiveStreamChatDelivered(publisherId, DataConvertionUtility::ToManagedString(packetId));
	}
	void ChatEventHandler::onLiveStreamChatFailedToSend(UserIdentity publisherId, const string &packetId)
	{
		listener->onLiveStreamChatFailedToSend(publisherId, DataConvertionUtility::ToManagedString(packetId));
	}
	void ChatEventHandler::onLiveStreamChatReceived(UserIdentity publisherId, UserIdentity senderId, const string &packetId, int messageType, const string &message, long long messageDate, const string &senderFullName)
	{
		listener->onLiveStreamChatReceived(publisherId, senderId, DataConvertionUtility::ToManagedString(packetId), messageType, DataConvertionUtility::ToManagedString(message), messageDate, DataConvertionUtility::ToManagedString(senderFullName));
	}
	void ChatEventHandler::onLiveStreamChatTyping(UserIdentity publisherId, UserIdentity senderId)
	{
		listener->onLiveStreamChatTyping(publisherId, senderId);
	}
	void ChatEventHandler::shouldCheckServerAddressForLiveStreamChat(UserIdentity publisherId)
	{
		listener->shouldCheckServerAddressForLiveStreamChat(publisherId);
	}
	void ChatEventHandler::onLiveStreamChatBlockUserRequestStatus(UserIdentity blockedUserId, const string &packetId)
	{
		listener->onLiveStreamChatBlockUserRequestStatus(blockedUserId, DataConvertionUtility::ToManagedString(packetId));
	}
	void ChatEventHandler::onLiveStreamChatUserBlocked(UserIdentity publisherId, UserIdentity blockedUserId)
	{
		listener->onLiveStreamChatUserBlocked(publisherId, blockedUserId);
	}



	// media file transfer
	void ChatEventHandler::onFriendFileManifestUploaded(UserIdentity userId, UserIdentity friendId, const string &packetId, string cloudManifestUrl, int messageType, int timeout, string caption, int widthOrFileSize, int heightOrDuration)
	{
		listener->onFriendFileManifestUploaded(userId, friendId, DataConvertionUtility::ToManagedString(packetId), DataConvertionUtility::ToManagedString(cloudManifestUrl), messageType, timeout, DataConvertionUtility::ToManagedString(caption), widthOrFileSize, heightOrDuration);
	}

	void ChatEventHandler::onFriendIncomingChatMedia(UserIdentity userId, UserIdentity friendId, string fileName, const string &packetId, int messageType, int timeout, long long messageDate, bool isSecretVisible, string caption, int widthOrSize, int heightOrDuration)
	{
		listener->onFriendIncomingChatMedia(userId, friendId, DataConvertionUtility::ToManagedString(fileName), DataConvertionUtility::ToManagedString(packetId), messageType, timeout, messageDate, isSecretVisible, DataConvertionUtility::ToManagedString(caption), widthOrSize, heightOrDuration);
	}

	void ChatEventHandler::onFriendChatMediaTransferProgress(UserIdentity userId, UserIdentity friendId, string fileName, double transferPercentage, bool isUpload, const string &packetId)
	{
		listener->onFriendChatMediaTransferProgress(userId, friendId, DataConvertionUtility::ToManagedString(fileName), transferPercentage, isUpload, DataConvertionUtility::ToManagedString(packetId));
	}

	void ChatEventHandler::onFriendChatMediaTransferFailed(UserIdentity userId, UserIdentity friendId, string fileName, const string &packetId, bool isUpload, bool isChunkedTransfer)
	{
		listener->onFriendChatMediaTransferFailed(userId, friendId, DataConvertionUtility::ToManagedString(fileName), DataConvertionUtility::ToManagedString(packetId), isUpload, isChunkedTransfer);
	}

	void ChatEventHandler::onFriendChatMediaTransferCanceled(UserIdentity userId, UserIdentity friendId, UserIdentity canceledBy, string fileName, const string &packetId, bool isUpload, bool isChunkedTransfer)
	{
		listener->onFriendChatMediaTransferCanceled(userId, friendId, canceledBy, DataConvertionUtility::ToManagedString(fileName), DataConvertionUtility::ToManagedString(packetId), isUpload, isChunkedTransfer);
	}

	void ChatEventHandler::onFriendChatMediaDownloadCompleted(UserIdentity userId, UserIdentity friendId, string fileNameWithPath, const string &packetId, int mediaType, int timeout)
	{
		listener->onFriendChatMediaDownloadCompleted(userId, friendId, DataConvertionUtility::ToManagedString(fileNameWithPath), DataConvertionUtility::ToManagedString(packetId), mediaType, timeout);
	}



	void ChatEventHandler::onGroupFileManifestUploaded(GroupIdentity groupId, const string &packetId, string cloudManifestUrl, int messageType, string caption, int widthOrFileSize, int heightOrDuration)
	{
		listener->onGroupFileManifestUploaded(groupId, DataConvertionUtility::ToManagedString(packetId), DataConvertionUtility::ToManagedString(cloudManifestUrl), messageType, DataConvertionUtility::ToManagedString(caption), widthOrFileSize, heightOrDuration);
	}

	void ChatEventHandler::onGroupIncomingChatMedia(UserIdentity friendId, GroupIdentity groupId, string fileName, const string &packetId, int messageType, long long messageDate, string caption, int widthOrSize, int heightOrDuration)
	{
		listener->onGroupIncomingChatMedia(friendId, groupId, DataConvertionUtility::ToManagedString(fileName), DataConvertionUtility::ToManagedString(packetId), messageType, messageDate, DataConvertionUtility::ToManagedString(caption), widthOrSize, heightOrDuration);
	}

	void ChatEventHandler::onGroupChatMediaTransferProgress(UserIdentity friendId, GroupIdentity groupId, string fileName, double transferPercentage, bool isUpload, const string &packetId)
	{
		listener->onGroupChatMediaTransferProgress(friendId, groupId, DataConvertionUtility::ToManagedString(fileName), transferPercentage, isUpload, DataConvertionUtility::ToManagedString(packetId));
	}

	void ChatEventHandler::onGroupChatMediaTransferFailed(UserIdentity friendId, GroupIdentity groupId, string fileName, const string &packetId, bool isUpload, bool isChunkedTransfer)
	{
		listener->onGroupChatMediaTransferFailed(friendId, groupId, DataConvertionUtility::ToManagedString(fileName), DataConvertionUtility::ToManagedString(packetId), isUpload, isChunkedTransfer);
	}

	void ChatEventHandler::onGroupChatMediaTransferCanceled(UserIdentity friendId, GroupIdentity groupId, UserIdentity canceledBy, string fileName, const string &packetId, bool isUpload, bool isChunkedTransfer)
	{
		listener->onGroupChatMediaTransferCanceled(friendId, groupId, canceledBy, DataConvertionUtility::ToManagedString(fileName), DataConvertionUtility::ToManagedString(packetId), isUpload, isChunkedTransfer);
	}

	void ChatEventHandler::onGroupChatMediaDownloadCompleted(UserIdentity friendId, GroupIdentity groupId, string fileNameWithPath, const string &packetId, int mediaType)
	{
		listener->onGroupChatMediaDownloadCompleted(friendId, groupId, DataConvertionUtility::ToManagedString(fileNameWithPath), DataConvertionUtility::ToManagedString(packetId), mediaType);
	}



	void ChatEventHandler::onChatMediaTransferDirectoryError()
	{
		listener->onChatMediaTransferDirectoryError();
	}
	void ChatEventHandler::shouldUpdateAppSessionID()
	{
		listener->shouldUpdateAppSessionID();
	}

}