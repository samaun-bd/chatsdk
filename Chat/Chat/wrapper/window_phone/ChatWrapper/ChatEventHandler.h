#pragma once
#include "IChatEventHandler.h"
#include "ManagedSeenPacketDTO.h"
#include "ManagedMessageDTO.h"
#include "ManagedMemberDTO.h"
#include "ManagedFriendMessageStatusDTO.h"
#include "ManagedGroupActivityDTO.h"
#include "ManagedGroupDTO.h"
#include "DataConvertionUtility.h"

using namespace imsdk;
using namespace Platform;

namespace ChatWrapper
{
	/*class IMListener
	{
	public:
	virtual void onEventHandlerAttached() {};
	};
	*/

	public interface class IMListener
	{
		virtual void onEventHandlerAttached() = 0;
		virtual void onEventHandlerDetached() = 0;

        virtual void onActivaeOrDeactivateUserAccountStatus(UserIdentity userId, String ^packetId, bool isAccountActivate, bool status) = 0;
        virtual void onGetUserInfoReceived(UserIdentity userId, UserIdentity friendId, String ^packetId, String ^friendName, UserIdentity friendRingId, String ^friendProfileImageUrl, int friendProfileType) = 0;
        virtual void onGetUserInfoFailure(UserIdentity userId, UserIdentity friendId, String ^packetId) = 0;
		virtual void onFriendUnregistered(UserIdentity userId, UserIdentity friendId, int onlineStatus, int onlineMood, bool fromAnonymousUser, int profileType) = 0;
		virtual void onFriendChatRegisterSuccess(UserIdentity userId, UserIdentity friendId, long long serverDate, String ^packetId, bool fromAnonymousUser) = 0;
		virtual void onFriendChatRegisterFailure(UserIdentity userId, UserIdentity friendId, String ^packetId, bool fromAnonymousUser) = 0;
		virtual void onFriendRegistrationExpired(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser) = 0;
		virtual void onFriendChatTyping(UserIdentity userId, UserIdentity friendid, bool fromAnonymousUser) = 0;
		virtual void onFriendChatReceived(UserIdentity friendid, UserIdentity receiverId, String ^packetId, int vector, int timeout, String ^message, long long messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser) = 0;
		virtual void onFriendChatEdited(UserIdentity friendid, UserIdentity receiverId, String ^packetId, int vector, int timeout, String ^message, long long messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser) = 0;
		virtual void onFriendChatDelivered(UserIdentity userId, UserIdentity friendid, String ^packetId, bool fromAnonymousUser, bool isEdited, bool fromOnline) = 0;
		virtual void onFriendChatSent(UserIdentity userId, UserIdentity friendid, String ^packetId, bool fromAnonymousUser) = 0;
		virtual void onFriendChatSeen(UserIdentity userId, UserIdentity friendid, const Array<ManagedSeenPacketDTO^> ^seenPacketList, bool fromAnonymousUser) = 0;
		virtual void onFriendChatSeenConfirmed(UserIdentity userId, UserIdentity friendid, const Array<ManagedSeenPacketDTO^> ^packetIds, bool fromAnonymousUser) = 0;
		virtual void onFriendChatFailedToSend(UserIdentity userId, UserIdentity friendId, String ^packetId, bool fromAnonymousUser) = 0;
		virtual void onFriendChatDeleted(UserIdentity senderId, UserIdentity friendid, const Array<String^> ^packetIds, bool fromAnonymousUser) = 0;
		virtual void onFriendChatDeleteRequestStatus(UserIdentity userId, UserIdentity friendid, String ^packetId, const Array<String^> ^packetIds, bool fromAnonymousUser, bool status) = 0;
		virtual void onFriendChatIdle(UserIdentity friendid, bool fromAnonymousUser) = 0;

		virtual void onFriendHistoryMessageReceived(UserIdentity userId, UserIdentity friendId, const Array<ManagedMessageDTO^> ^friendHistoryMessageList, int direction) = 0; /******/
		virtual void onFriendMessagesStatusReceived(UserIdentity userId, UserIdentity friendId, const Array<ManagedFriendMessageStatusDTO^> ^messageList) = 0;
		virtual void onFriendHistoryCompleted(UserIdentity userId, UserIdentity friendId, int direction) = 0;
		virtual void onFriendHistoryMessageRequestStatus(UserIdentity userId, UserIdentity friendId, String ^packetId, bool status) = 0;

		virtual void shouldCheckFriendPresence(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser, int profileType) = 0;
		virtual void shouldCheckServerAddressForFriend(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser) = 0;

		virtual void onBlocked(UserIdentity blockerId, UserIdentity blockedId, int64 blockUnblockDate, bool addToBlock) = 0; /******/
		virtual void onUnblocked(UserIdentity blockerId, UserIdentity blockedId, int64 blockUnblockDate) = 0; /******/
		virtual void onBlockUnblockRequestStatus(UserIdentity userid, UserIdentity friendid, String ^packetId, int64 blockUnblockDate, bool status, bool fromBlockRequest) = 0;

		virtual void onFriendChatConversationListReceived(UserIdentity userId, const Array<ManagedMessageDTO^> ^conversationList) = 0;
		virtual void onGroupChatConversationListReceived(const Array<ManagedMessageDTO^> ^conversationList) = 0;
		virtual void onChatConversationListRequestStatus(UserIdentity userId, long long friendOrGroupId, String ^packetId, bool status) = 0;
		virtual void onChatConversationListCompleted(UserIdentity userId) = 0;
		virtual void onConversationListDeleteRequestStatus(UserIdentity userId, String ^packetId, bool status) = 0;
		virtual void onConversationListMarkAsSeenRequestStatus(UserIdentity userId, String ^packetId, bool status) = 0;

		virtual void onGroupChatRegisterSuccess(GroupIdentity groupId, long long serverDate, String ^packetId) = 0;
		virtual void onGroupChatRegisterFailure(GroupIdentity groupId, String ^packetId) = 0;
		virtual void onGroupRegistrationExpired(GroupIdentity groupId, long long lastActivityTime) = 0;
		virtual void onGroupChatSent(GroupIdentity groupId, String ^packetId, bool isEdited) = 0;
		virtual void onGroupChatReceived(UserIdentity senderId, GroupIdentity groupid, String ^packetId, int messageType, String ^message, long long messageDate, bool fromOnline) = 0;
		virtual void onGroupChatDelivered(UserIdentity friendid, GroupIdentity groupid, String ^packetId) = 0;
		virtual void onGroupChatDeleted(UserIdentity friendid, GroupIdentity groupid, const Array<String^> ^packetIdList) = 0;
		virtual void onGroupChatDeleteRequestStatus(GroupIdentity groupid, String ^packetId, const Array<String^> ^packetIds, bool status) = 0;
		virtual void onGroupChatSeen(GroupIdentity groupid, const Array<String^> ^packetIds) = 0;
		virtual void onGroupChatSeenRequestStatus(GroupIdentity groupid, const Array<String^> ^packetIds, bool status) = 0;
		virtual void onGroupChatMessageSeenListReceived(GroupIdentity groupId, String^ packetId, const Array<ManagedMemberDTO^> ^memberList) = 0;
		virtual void onGroupChatMessageSeenListRequestStatus(GroupIdentity groupId, String^ requestPacketId, String^ messagePacketId, bool status) = 0;
		virtual void onGroupChatTyping(UserIdentity friendid, GroupIdentity groupid) = 0;
		virtual void onGroupChatIdle(UserIdentity friendid, GroupIdentity groupid) = 0;
		virtual void onGroupChatEdited(UserIdentity senderId, GroupIdentity groupId, String ^packetId, int messageType, String ^message, long long messageDate, bool fromOnline) = 0;
		virtual void onGroupMemberRemoveLeaveRequestStatus(GroupIdentity groupId, String ^packetId, bool status, const Array<ManagedMemberDTO^> ^memberList) = 0; /******/
		virtual void onGroupMemberRemovedOrLeft(UserIdentity friendid, GroupIdentity groupid, const Array<UserIdentity> ^memberList, String ^packetId) = 0;
		virtual void onGroupMemberAddRequestStatus(GroupIdentity groupId, String ^packetId, bool status, const Array<ManagedMemberDTO^> ^memberList) = 0; /******/
		virtual void onGroupMemberAdded(UserIdentity friendid, GroupIdentity groupid, const Array<ManagedMemberDTO^> ^memberList, String ^packetId) = 0;
		virtual void onGroupMemberStatusChangeRequestStatus(GroupIdentity groupId, String ^packetId, bool status, const Array<ManagedMemberDTO^> ^memberList) = 0; /******/
		virtual void onGroupMemberStatusChanged(UserIdentity senderid, GroupIdentity groupid, const Array<ManagedMemberDTO^> ^memberList, String ^packetId) = 0;
		virtual void onGroupChatFailedToSend(GroupIdentity groupId, String ^packetId) = 0;
		virtual void shouldCheckServerAddressForGroup(GroupIdentity groupId) = 0;

		virtual void shouldCheckOfflineServerAddress() = 0;
		virtual void onServerTimeSynced(long long timeDifference) = 0;
		virtual void shouldUpdateUserPassword() = 0;
		virtual void onSDKError(int errorCode, String ^packetId) = 0;

		virtual void onGroupHistoryMessageReceived(GroupIdentity groupId, const Array<ManagedMessageDTO^> ^groupHistoryMessageList , int direction) = 0; /******/
		virtual void onGroupHistoryCompleted(GroupIdentity groupId, int direction) = 0;
		virtual void onGroupInformationWithMembersReceived(GroupIdentity groupId, String ^groupName, String ^groupUrl, const Array<ManagedMemberDTO^> ^memberList) = 0;
		virtual void onGroupInformationWithMembersRequestStatus(GroupIdentity groupId, String ^packetId, bool status) = 0;
		virtual void onGroupInformationActivityReceived(const Array<ManagedGroupActivityDTO^> ^groupActivityList) = 0;
		virtual void onGroupInformationActivityFromHistoryMessageReceived(GroupIdentity groupId, const Array<ManagedGroupActivityDTO^> ^groupActivityList, int direction) = 0;
		virtual void onMyGroupListReceived(const Array<ManagedGroupDTO^> ^myGroupList) = 0;
		virtual void onGroupCreated(GroupIdentity groupId, String ^packetId, bool status) = 0;
		//virtual void onGroupInformationChangeRequestStatus(GroupIdentity groupId, String ^packetId, bool status) = 0;
		virtual void onGroupNameChangeRequestStatus(GroupIdentity groupId, String ^packetId, bool status, String ^groupName) = 0; /******/
		virtual void onGroupUrlChangeRequestStatus(GroupIdentity groupId, String ^packetId, bool status, String ^groupUrl) = 0; /******/
		virtual void onGroupNameChanged(String ^packetId, UserIdentity friendid, GroupIdentity groupid, String ^groupName) = 0;
		virtual void onGroupUrlChanged(String ^packetId, UserIdentity friendid, GroupIdentity groupid, String ^groupUrl) = 0;
		virtual void onGroupHistoryMessageRequestStatus(GroupIdentity groupId, String ^packetId, bool status) = 0;



		//Public Room Chat
		virtual void onPublicRoomChatRegisterSuccess(ManagedRoomIdentity roomId, String ^packetId, int numberOfMembers, long long anonymousId) = 0;
		virtual void onPublicRoomChatRegisterFailure(ManagedRoomIdentity roomId, String ^packetId) = 0;
		virtual void onPublicRoomChatRegistrationExpired(ManagedRoomIdentity roomId) = 0;
		virtual void onPublicRoomChatDelivered(ManagedRoomIdentity roomId, String ^packetId, bool isEdited) = 0;
		virtual void onPublicRoomChatFailedToSend(ManagedRoomIdentity roomId, String ^packetId) = 0;
		virtual void onPublicRoomChatReceived(ManagedRoomIdentity roomId, UserIdentity friendId, String ^packetId, int messageType, String ^message, long long messageDate, String ^memberFullName, String ^memberProfileUrl) = 0;
		virtual void onPublicRoomListReceived(const Array<ManagedRoomDTO^> ^roomList, bool roomListFromHistory) = 0;
		virtual void onPublicRoomInformationReceived(ManagedRoomIdentity roomId, String ^roomName, String ^roomUrl, String ^packetId) = 0;
		virtual void onPublicRoomChatEdited(ManagedRoomIdentity roomId, UserIdentity friendId, String ^packetId, int messageType, String ^message, long long messageDate, String ^memberFullName, String ^memberProfileUrl) = 0;
		virtual void onPublicRoomChatTyping(ManagedRoomIdentity roomId, UserIdentity friendId, String ^memberName) = 0;
		virtual void onPublicChatMemberListReceived(ManagedRoomIdentity roomId, String ^pagingState, const Array<ManagedPublicChatMemberDTO^> ^publicChatMemberList) = 0;
		virtual void onPublicChatMemberCountChanged(ManagedRoomIdentity roomId, int numberOfMembers) = 0;
		virtual void shouldCheckServerAddressForRoom(ManagedRoomIdentity roomId) = 0;
		virtual void onPublicRoomChatHistoryReceived(ManagedRoomIdentity roomId, const Array<ManagedMessageDTO^> ^publicChatMessageList) = 0;
		virtual void onPublicRoomChatHistoryCompleted(ManagedRoomIdentity roomId) = 0;
		virtual void onPublicRoomListRequestStatus(String ^packetId, bool requestStatus) = 0;
		virtual void onPublicRoomInformationRequestFailed(ManagedRoomIdentity roomId, String ^packetId) = 0;
		virtual void onPublicRoomChatHistoryRequestStatus(ManagedRoomIdentity roomId, String ^packetId, bool requestStatus) = 0;
		virtual void onPublicRoomMemberListRequestStatus(ManagedRoomIdentity roomId, String ^acketId, bool requestStatus) = 0;
		virtual void onPublicChatMessageDeleted(ManagedRoomIdentity roomId, const Array<String^> ^deletedPacketIds) = 0;
		virtual void onPublicChatMessageLiked(ManagedRoomIdentity roomId, String ^packetId, UserIdentity recipientId) = 0;
		virtual void onPublicChatMessageUnliked(ManagedRoomIdentity roomId, String ^packetId, UserIdentity messageSenderId) = 0;
		virtual void onPublicChatMessageReported(ManagedRoomIdentity roomId, String ^packetId, UserIdentity recipientId) = 0;
		virtual void onPublicChatCategoryListReceived(const Array<String^> ^publicChatCategoryList) = 0;
		virtual void onPublicChatLikeMemberListReceived(ManagedRoomIdentity roomId, String ^packetId, const Array<ManagedPublicChatMemberDTO^> ^publicChatMemberList) = 0;
		virtual void onPublicChatDeleteRequestStatus(ManagedRoomIdentity roomId, String^packetId, bool status) = 0;
		virtual void onPublicChatLikeUnlikeRequestStatus(ManagedRoomIdentity roomId, String^requestPacketId, String^messagePacketId, bool status, bool fromLikeRequest) = 0;
		virtual void onPublicChatReportRequestStatus(ManagedRoomIdentity roomId, String^requestPacketId, String^messagePacketId, bool status) = 0;
		virtual void onPublicChatLikeMemberListRequestStatus(ManagedRoomIdentity roomId, String^packetId, bool status) = 0;
		virtual void onPublicChatCategoryListRequestStatus(String ^packetId, bool status) = 0;

		/*virtual void onFriendGetChatMessageReceived(UserIdentity friendId, ManagedMessageDTO ^friendChatMessageDTO) = 0;
		virtual void onGroupGetChatMessageReceived(GroupIdentity groupId, ManagedMessageDTO ^groupChatMessageDTO) = 0;
		virtual void onFriendGetChatMessageFailedToSend(UserIdentity friendId, String ^packetId) = 0;
		virtual void onGroupGetChatMessageFailedToSend(GroupIdentity groupId, String ^packetId) = 0;
*/
		virtual void onNetworkDataCounted(ManagedDataCounter ^dataCounter) = 0;


		//Live stream chat
		virtual void onLiveStreamChatRegisterSuccess(UserIdentity publisherId, String ^packetId) = 0;
		virtual void onLiveStreamChatRegisterFailure(UserIdentity publisherId, String ^packetId) = 0;
		virtual void onLiveStreamChatRegistrationExpired(UserIdentity publisherId) = 0;
		virtual void onLiveStreamChatDelivered(UserIdentity publisherId, String ^packetId) = 0;
		virtual void onLiveStreamChatFailedToSend(UserIdentity publisherId, String ^packetId) = 0;
		virtual void onLiveStreamChatReceived(UserIdentity publisherId, UserIdentity senderId, String ^packetId, int messageType, String ^message, long long messageDate, String ^senderFullName) = 0;
		virtual void onLiveStreamChatTyping(UserIdentity publisherId, UserIdentity senderId) = 0;
		virtual void shouldCheckServerAddressForLiveStreamChat(UserIdentity publisherId) = 0;
		virtual void onLiveStreamChatBlockUserRequestStatus(UserIdentity blockedUserId, String ^packetId) = 0;
		virtual void onLiveStreamChatUserBlocked(UserIdentity publisherId, UserIdentity blockedUserId) = 0;



		
		// media file transfer
		virtual void onFriendFileManifestUploaded(UserIdentity userId, UserIdentity friendId, String ^packetId, String ^cloudManifestUrl, int messageType, int timeout, String ^caption, int widthOrFileSize, int heightOrDuration) = 0;
		virtual void onFriendIncomingChatMedia(UserIdentity userId, UserIdentity friendId, String ^fileName, String ^packetId, int messageType, int timeout, long long messageDate, bool isSecretVisible, String ^caption, int widthOrSize, int heightOrDuration) = 0;
		virtual void onFriendChatMediaTransferProgress(UserIdentity userId, UserIdentity friendId, String ^fileName, double transferPercentage, bool isUpload, String ^packetId) = 0;
		virtual void onFriendChatMediaTransferFailed(UserIdentity userId, UserIdentity friendId, String ^fileName, String ^packetId, bool isUpload, bool isChunkedTransfer) = 0;
		virtual void onFriendChatMediaTransferCanceled(UserIdentity userId, UserIdentity friendId, UserIdentity canceledBy, String ^fileName, String ^packetId, bool isUpload, bool isChunkedTransfer) = 0;
		virtual void onFriendChatMediaDownloadCompleted(UserIdentity userId, UserIdentity friendId, String ^fileNameWithPath, String ^packetId, int mediaType, int timeout) = 0;

		virtual void onGroupFileManifestUploaded(GroupIdentity groupId, String ^packetId, String ^cloudManifestUrl, int messageType, String ^caption, int widthOrFileSize, int heightOrDuration) = 0;
		virtual void onGroupIncomingChatMedia(UserIdentity friendId, GroupIdentity groupId, String ^fileName, String ^packetId, int messageType, long long messageDate, String ^caption, int widthOrSize, int heightOrDuration) = 0;
		virtual void onGroupChatMediaTransferProgress(UserIdentity friendId, GroupIdentity groupId, String ^fileName, double transferPercentage, bool isUpload, String ^packetId) = 0;
		virtual void onGroupChatMediaTransferFailed(UserIdentity friendId, GroupIdentity groupId, String ^fileName, String ^packetId, bool isUpload, bool isChunkedTransfer) = 0;
		virtual void onGroupChatMediaTransferCanceled(UserIdentity friendId, GroupIdentity groupId, UserIdentity canceledBy, String ^fileName, String ^packetId, bool isUpload, bool isChunkedTransfer) = 0;
		virtual void onGroupChatMediaDownloadCompleted(UserIdentity friendId, GroupIdentity groupId, String ^fileNameWithPath, String ^packetId, int mediaType) = 0;

		virtual void onChatMediaTransferDirectoryError() = 0;
		virtual void shouldUpdateAppSessionID() = 0;
	};

	//static IMListener ^listener = nullptr;

	class ChatEventHandler : public IChatEventHandler
	{
		IMListener ^listener = nullptr;
	public:
		ChatEventHandler(IMListener ^listener);

		void onEventHandlerAttached();
		void onEventHandlerDetached();

        void onActivaeOrDeactivateUserAccountStatus(UserIdentity userId, const std::string &packetId, bool isAccountActivate, bool status);
        void onGetUserInfoReceived(UserIdentity userId, UserIdentity friendId, const std::string &packetId, std::string friendName, UserIdentity friendRingId, std::string friendProfileImageUrl, int friendProfileType);
        void onGetUserInfoFailure(UserIdentity userId, UserIdentity friendId, const std::string &packetId);
		void onFriendUnregistered(UserIdentity userId, UserIdentity friendId, int onlineStatus, int onlineMood, bool fromAnonymousUser, int profileType);
		void onFriendChatRegisterSuccess(UserIdentity userId, UserIdentity friendId, long long serverDate, const string &packetId, bool fromAnonymousUser);
		void onFriendChatRegisterFailure(UserIdentity userId, UserIdentity friendId, const string &packetId, bool fromAnonymousUser);
		void onFriendRegistrationExpired(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser);
		void onFriendChatTyping(UserIdentity userId, UserIdentity friendid, bool fromAnonymousUser);
		void onFriendChatReceived(UserIdentity senderId, UserIdentity receiverId, const string &packetId, int messageType, int timeout, const string &message, long long messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser);
		void onFriendChatEdited(UserIdentity senderId, UserIdentity receiverId, const string &packetId, int messageType, int timeout, const string &message, long long messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser);
		void onFriendChatDelivered(UserIdentity userId, UserIdentity friendid, const string &packetId, bool fromAnonymousUser, bool isEdited, bool fromOnline);
		void onFriendChatSent(UserIdentity userId, UserIdentity friendId, const string &packetId, bool fromAnonymousUser);
		void onFriendChatSeen(UserIdentity userId, UserIdentity friendid, const vector<SeenPacketDTO> &seenPacketList, bool fromAnonymousUser);
		void onFriendChatSeenConfirmed(UserIdentity userId, UserIdentity friendid, vector<SeenPacketDTO> &packetIds, bool fromAnonymousUser);
		void onFriendChatFailedToSend(UserIdentity userId, UserIdentity friendId, const string &packetId, bool fromAnonymousUser);
		void onFriendChatDeleted(UserIdentity senderId, UserIdentity friendid, const vector<string> &packetId, bool fromAnonymousUser);
		void onFriendChatDeleteRequestStatus(UserIdentity userId, UserIdentity friendid, const std::string &packetId, const std::vector<std::string> &packetIds, bool fromAnonymousUser, bool status);
		void onFriendChatIdle(UserIdentity friendid, bool fromAnonymousUser);

		void onFriendHistoryMessageReceived(UserIdentity userId, UserIdentity friendId, const vector<SDKMessageDTO> &friendHistoryMessageList, int direction);//UserIdentity senderId, UserIdentity receiverId, const string &packetId, int messageType, int timeout, const string &message, long long messageDate, bool isSecretVisible, int messageStatus, int direction
		void onFriendMessagesStatusReceived(UserIdentity userId, UserIdentity friendId, const vector<FriendMessageStatusDTO> &messageList);
		void onFriendHistoryCompleted(UserIdentity userId, UserIdentity friendId, int direction);
		void onFriendHistoryMessageRequestStatus(UserIdentity userId, UserIdentity friendId, const string &packetId, bool status);

		void shouldCheckFriendPresence(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser, int profileType);
		void shouldCheckServerAddressForFriend(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser);

		void onBlocked(UserIdentity blockerId, UserIdentity blockedId, long long blockUnblockDate, bool addToBlock);
		void onUnblocked(UserIdentity blockerId, UserIdentity blockedId, long long blockUnblockDate);
		void onBlockUnblockRequestStatus(UserIdentity userid, UserIdentity friendid, const string &packetId, long long blockUnblockDate, bool status, bool fromBlockRequest);


		void onFriendChatConversationListReceived(UserIdentity userId, const vector<SDKMessageDTO> &conversationList);
		void onGroupChatConversationListReceived(const vector<SDKMessageDTO> &conversationList);
		void onChatConversationListRequestStatus(UserIdentity userId, long long friendOrGroupId, const string &packetId, bool status);
		void onChatConversationListCompleted(UserIdentity userId);
		void onConversationListDeleteRequestStatus(UserIdentity userId, const string &packetId, bool status);
		void onConversationListMarkAsSeenRequestStatus(UserIdentity userId, const string &packetId, bool status);


		void onGroupChatRegisterSuccess(GroupIdentity groupId, long long serverDate, const string &packetId);
		void onGroupChatRegisterFailure(GroupIdentity groupId, const string &packetId);
		void onGroupRegistrationExpired(GroupIdentity groupId, long long lastActivityTime);
		void onGroupChatSent(GroupIdentity groupId, const string &packetId, bool isEdited);
		void onGroupChatReceived(UserIdentity senderId, GroupIdentity groupid, const string &packetId, int messageType, const string &message, long long messageDate, bool fromOnline);
		void onGroupChatDelivered(UserIdentity friendid, GroupIdentity groupid, const string &packetId);
		void onGroupChatDeleted(UserIdentity friendid, GroupIdentity groupid, const vector<string> &packetIdList);
		void onGroupChatDeleteRequestStatus(GroupIdentity groupid, const std::string &packetId, const std::vector<std::string> &packetIds, bool status);
		void onGroupChatSeen(GroupIdentity groupid, const vector<string> &packetIds);
		void onGroupChatSeenRequestStatus(GroupIdentity groupid, const vector<string> &packetIds, bool status);
		void onGroupChatMessageSeenListReceived(GroupIdentity groupId, const string &packetId, const vector<MemberDTO> &memberList);
		void onGroupChatMessageSeenListRequestStatus(GroupIdentity groupId, const string &requestPacketId, const string &messagePacketId, bool status);
		void onGroupChatTyping(UserIdentity friendid, GroupIdentity groupid);
		void onGroupChatIdle(UserIdentity friendid, GroupIdentity groupid);
		void onGroupChatEdited(UserIdentity senderId, GroupIdentity groupId, const string &packetId, int messageType, const string &message, long long messageDate, bool fromOnline);
		void onGroupMemberRemoveLeaveRequestStatus(GroupIdentity groupId, const string &packetId, bool status, const vector<MemberDTO> &memberList);
		void onGroupMemberRemovedOrLeft(UserIdentity friendid, GroupIdentity groupid, const vector<UserIdentity> &memberList, const string &packetId);
		void onGroupMemberAddRequestStatus(GroupIdentity groupId, const string &packetId, bool status, const vector<MemberDTO> &memberList);
		void onGroupMemberAdded(UserIdentity friendid, GroupIdentity groupid, const vector<MemberDTO> &memberList, const string &packetId);
		void onGroupMemberStatusChangeRequestStatus(GroupIdentity groupId, const string &packetId, bool status, const vector<MemberDTO> &memberList);
		void onGroupMemberStatusChanged(UserIdentity senderid, GroupIdentity groupid, const vector<MemberDTO> &memberList, const string &packetId);
		void onGroupChatFailedToSend(GroupIdentity groupId, const string &packetId);
		void shouldCheckServerAddressForGroup(GroupIdentity groupId);

		void shouldCheckOfflineServerAddress();
		void onServerTimeSynced(long long timeDifference);
		void shouldUpdateUserPassword();
		//    void onFriendFileTransferRequestReceived(UserIdentity friendId, string fileName, FileIdentity fileId, long long fileSize)=0;
		void onSDKError(int errorCode, const string &packetId);

		void onGroupHistoryMessageReceived(GroupIdentity groupId, const vector<SDKMessageDTO> &groupHistoryMessageList, int direction);
		void onGroupHistoryCompleted(GroupIdentity groupId, int direction);
		void onGroupInformationWithMembersReceived(GroupIdentity groupId, const string &groupName, const string &groupUrl, const vector<MemberDTO> &memberList);
		void onGroupInformationWithMembersRequestStatus(GroupIdentity groupId, const string &packetId, bool status);
		void onGroupInformationActivityReceived(const vector<GroupActivityDTO> &groupActivityList);
		void onGroupInformationActivityFromHistoryMessageReceived(GroupIdentity groupId, const vector<GroupActivityDTO> &groupActivityList, int direction);
		void onMyGroupListReceived(const vector<GroupDTO> &myGroupList);
		void onGroupCreated(GroupIdentity groupId, const string &packetId, bool status);

		//void onGroupInformationChangeRequestStatus(GroupIdentity groupId, const string &packetId, bool status);
		void onGroupNameChangeRequestStatus(GroupIdentity groupId, const string &packetId, bool status, const string &groupName);
		void onGroupUrlChangeRequestStatus(GroupIdentity groupId, const string &packetId, bool status, const string &groupUrl);
		void onGroupNameChanged(const string &packetId, UserIdentity friendid, GroupIdentity groupid, const string &groupName);
		void onGroupUrlChanged(const string &packetId, UserIdentity friendid, GroupIdentity groupid, const string &groupUrl);
		void onGroupHistoryMessageRequestStatus(GroupIdentity groupId, const string &packetId, bool status);




		//Public Room Chat
		void onPublicRoomChatRegisterSuccess(RoomIdentity &roomId, const string &packetId, int numberOfMembers, long long anonymousId);
		void onPublicRoomChatRegisterFailure(RoomIdentity &roomId, const string &packetId);
		void onPublicRoomChatRegistrationExpired(RoomIdentity &roomId);
		void onPublicRoomChatDelivered(RoomIdentity &roomId, const string &packetId, bool isEdited);
		void onPublicRoomChatFailedToSend(RoomIdentity &roomId, const string &packetId);
		void onPublicRoomChatReceived(RoomIdentity &roomId, UserIdentity friendId, const string &packetId, int messageType, const string &message, long long messageDate, const string &memberFullName, const string &memberProfileUrl);
		void onPublicRoomListReceived(const vector<RoomDTO> &roomList, bool roomListFromHistory);
		void onPublicRoomInformationReceived(RoomIdentity &roomId, string &roomName, string &roomUrl, const string &packetId);
		void onPublicRoomChatEdited(RoomIdentity &roomId, UserIdentity friendId, const string &packetId, int messageType, const string &message, long long messageDate, const string &memberFullName, const string &memberProfileUrl);
		void onPublicRoomChatTyping(RoomIdentity &roomId, UserIdentity friendId, const string &memberName);
		void onPublicChatMemberListReceived(RoomIdentity &roomId, const string &pagingState, const vector<PublicChatMemberDTO> &publicChatMemberList);
		void onPublicChatMemberCountChanged(RoomIdentity &roomId, int numberOfMembers);
		void shouldCheckServerAddressForRoom(RoomIdentity &roomId);
		void onPublicRoomChatHistoryReceived(RoomIdentity &roomId, const vector<SDKMessageDTO> &publicChatMessageList);
		void onPublicRoomChatHistoryCompleted(RoomIdentity &roomId);
		void onPublicRoomListRequestStatus(const string &packetId, bool requestStatus);
		void onPublicRoomInformationRequestFailed(RoomIdentity &roomId, const string &packetId);
		void onPublicRoomChatHistoryRequestStatus(RoomIdentity &roomId, const string &packetId, bool requestStatus);
		void onPublicRoomMemberListRequestStatus(RoomIdentity &roomId, const string &packetId, bool requestStatus);
		void onPublicChatMessageDeleted(RoomIdentity& roomId, const vector<string>& deletedPacketIds);
		void onPublicChatMessageLiked(RoomIdentity& roomId, const string& packetId, UserIdentity recipientId);
		void onPublicChatMessageUnliked(RoomIdentity& roomId, const string& packetId, UserIdentity messageSenderId);
		void onPublicChatMessageReported(RoomIdentity& roomId, const string& packetId, UserIdentity recipientId);
		void onPublicChatCategoryListReceived(vector<string> &publicChatCategoryList);
		void onPublicChatLikeMemberListReceived(RoomIdentity &roomId, const string &packetId, const vector<imsdk::PublicChatMemberDTO> &publicChatMemberList);
		void onPublicChatDeleteRequestStatus(RoomIdentity roomId, const string &packetId, bool status);
		void onPublicChatLikeUnlikeRequestStatus(RoomIdentity roomId, const string &requestPacketId, const string &messagePacketId, bool status, bool fromLikeRequest);
		void onPublicChatReportRequestStatus(RoomIdentity roomId, const string &requestPacketId, const string &messagePacketId, bool status);
		void onPublicChatLikeMemberListRequestStatus(RoomIdentity roomId, const string &packetId, bool status);
		void onPublicChatCategoryListRequestStatus(const string &packetId, bool status);


		
		
		void onShadowIdsInfoRequestFailed(const string &packetId);
		void onShadowIdsInfoResponseReceived(const vector<PublicChatMemberDTO> &shadowIdsInfo);
		void onFileTransferAccepted(UserIdentity friendId, FileIdentity fileId, int fileTransferPort, long long fileOffset);
		void onFileStreamRequestConfirmed(const string &packetId, UserIdentity friendId, FileIdentity fileId, int fileTransferPort, bool fileAcceptReject);
		void onFileTransferCanceled(UserIdentity friendId, FileIdentity fileId);
		void onFileTransferFailed(const string &packetId, UserIdentity friendId, FileIdentity fileId);


		void onFileStreamRequestReceived(UserIdentity userId, UserIdentity friendId, FileIdentity fileId);
		void onFriendFileSessionRequestSuccess(UserIdentity userId, const string &packetId, UserIdentity friendId, FileIdentity fileId, int fileTransferPort);
		void onFriendFileTransferSessionRequestFailed(UserIdentity userId, const string &packetId, UserIdentity friendId, FileIdentity fileId);
		void onFriendFileStreamRequestSuccess(UserIdentity userId, const string &packetId, UserIdentity friendId, FileIdentity fileId);
		void onFriendFileTransferStreamRequestFailed(UserIdentity userId, const string &packetId, UserIdentity friendId, FileIdentity fileId);

		void onGroupFileStreamRequestReceived(UserIdentity friendId, GroupIdentity groupId, FileIdentity fileId);
		void onGroupFileSessionRequestSuccess(const string &packetId, GroupIdentity groupId, FileIdentity fileId, int fileTransferPort);
		void onGroupFileTransferSessionRequestFailed(const string &packetId, GroupIdentity groupId, FileIdentity fileId);
		void onGroupFileStreamRequestSuccess(const string &packetId, GroupIdentity groupId, FileIdentity fileId);
		void onGroupFileTransferStreamRequestFailed(const string &packetId, GroupIdentity groupId, FileIdentity fileId);


		void onGroupFileRecipientArrived(UserIdentity friendId, GroupIdentity groupId, FileIdentity fileId, int fileTransferPort, bool fileTransferRequestAccepted);
		void onGroupFileTransferStart(UserIdentity friendId, GroupIdentity groupId, FileIdentity fileId, int fileTransferPort, const string &packetId);
		void onGroupFileTransferFailed(const string &packetId, UserIdentity friendId, GroupIdentity groupId, FileIdentity fileId);


		void onFriendGetChatMessageReceived(UserIdentity userId, UserIdentity friendId, const SDKMessageDTO& friendChatMessageDTO);
		void onGroupGetChatMessageReceived(GroupIdentity groupId, const SDKMessageDTO& groupChatMessageDTO);
		void onFriendGetChatMessageFailedToSend(UserIdentity userId, UserIdentity friendId, const string& packetId);
		void onGroupGetChatMessageFailedToSend(GroupIdentity groupId, const string& packetId);

		void onNetworkDataCounted(const DataCounter& dataCounter);



		//Live stream chat
		void onLiveStreamChatRegisterSuccess(UserIdentity publisherId, const string &packetId);
		void onLiveStreamChatRegisterFailure(UserIdentity publisherId, const string &packetId);
		void onLiveStreamChatRegistrationExpired(UserIdentity publisherId);
		void onLiveStreamChatDelivered(UserIdentity publisherId, const string &packetId);
		void onLiveStreamChatFailedToSend(UserIdentity publisherId, const string &packetId);
		void onLiveStreamChatReceived(UserIdentity publisherId, UserIdentity senderId, const string &packetId, int messageType, const string &message, long long messageDate, const string &senderFullName);
		void onLiveStreamChatTyping(UserIdentity publisherId, UserIdentity senderId);
		void shouldCheckServerAddressForLiveStreamChat(UserIdentity publisherId);
		void onLiveStreamChatBlockUserRequestStatus(UserIdentity blockedUserId, const string &packetId);
		void onLiveStreamChatUserBlocked(UserIdentity publisherId, UserIdentity blockedUserId);



		// media file transfer
		void onFriendFileManifestUploaded(UserIdentity userId, UserIdentity friendId, const string &packetId, string cloudManifestUrl, int messageType, int timeout, string caption, int widthOrFileSize, int heightOrDuration);
		void onFriendIncomingChatMedia(UserIdentity userId, UserIdentity friendId, string fileName, const string &packetId, int messageType, int timeout, long long messageDate, bool isSecretVisible, string caption, int widthOrSize, int heightOrDuration);
		void onFriendChatMediaTransferProgress(UserIdentity userId, UserIdentity friendId, string fileName, double transferPercentage, bool isUpload, const string &packetId);
		void onFriendChatMediaTransferFailed(UserIdentity userId, UserIdentity friendId, string fileName, const string &packetId, bool isUpload, bool isChunkedTransfer);
		void onFriendChatMediaTransferCanceled(UserIdentity userId, UserIdentity friendId, UserIdentity canceledBy, string fileName, const string &packetId, bool isUpload, bool isChunkedTransfer);
		void onFriendChatMediaDownloadCompleted(UserIdentity userId, UserIdentity friendId, string fileNameWithPath, const string &packetId, int mediaType, int timeout);

		void onGroupFileManifestUploaded(GroupIdentity groupId, const string &packetId, string cloudManifestUrl, int messageType, string caption, int widthOrFileSize, int heightOrDuration);
		void onGroupIncomingChatMedia(UserIdentity friendId, GroupIdentity groupId, string fileName, const string &packetId, int messageType, long long messageDate, string caption, int widthOrSize, int heightOrDuration);
		void onGroupChatMediaTransferProgress(UserIdentity friendId, GroupIdentity groupId, string fileName, double transferPercentage, bool isUpload, const string &packetId);
		void onGroupChatMediaTransferFailed(UserIdentity friendId, GroupIdentity groupId, string fileName, const string &packetId, bool isUpload, bool isChunkedTransfer);
		void onGroupChatMediaTransferCanceled(UserIdentity friendId, GroupIdentity groupId, UserIdentity canceledBy, string fileName, const string &packetId, bool isUpload, bool isChunkedTransfer);
		void onGroupChatMediaDownloadCompleted(UserIdentity friendId, GroupIdentity groupId, string fileNameWithPath, const string &packetId, int mediaType);

		void onChatMediaTransferDirectoryError();
		void shouldUpdateAppSessionID();
	};
}