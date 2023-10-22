/* 
 * File:   ChatEventHandler.h
 * Author: dipal
 *
 * Created on September 29, 2015, 1:07 PM
 */

#ifndef CHATEVENTHANDLER_H
#define	CHATEVENTHANDLER_H

#include <jni.h>
#include "IChatEventHandler.h"

namespace imsdk {
void onloadChatEventHandler(JNIEnv *env);
void onunloadChatEventHandler(JNIEnv *env);


class ChatEventHandler : public IChatEventHandler {
public:
    ChatEventHandler(JavaVM* vm, JNIEnv *env, jobject jEventHandler);
    ~ChatEventHandler();

    void onEventHandlerAttached();
    void onEventHandlerDetached();
    void onActivaeOrDeactivateUserAccountStatus(UserIdentity userId, const std::string &packetId, bool isAccountActivate, bool status);
    void onGetUserInfoReceived(UserIdentity userId, UserIdentity friendId, const std::string &packetId, std::string friendName, UserIdentity friendRingId, std::string friendProfileImageUrl, int friendProfileType);
    void onGetUserInfoFailure(UserIdentity userId, UserIdentity friendId, const std::string &packetId);
    void onFriendChatRegisterSuccess(UserIdentity userId, UserIdentity friendId, long long serverDate, const std::string &packetId, bool fromAnonymousUser);
    void onFriendChatRegisterFailure(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool fromAnonymousUser);
    void onFriendRegistrationExpired(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser);
    void onFriendUnregistered(UserIdentity userId, UserIdentity friendId, int onlineStatus, int onlineMood, bool fromAnonymousUser, int profileType);
    void onGroupChatRegisterSuccess(GroupIdentity groupId, long long serverDate, const std::string &packetId);
    void onGroupChatRegisterFailure(GroupIdentity groupId, const std::string &packetId);
    void onGroupRegistrationExpired(GroupIdentity groupId, long long lastActivityTime);
    void onFriendChatReceived(UserIdentity senderId, UserIdentity receiverId, const std::string &packetId, int messageType, int timeout, const std::string &message, long long messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser);
    void onFriendChatDelivered(UserIdentity userId, UserIdentity friendid, const std::string &packetId, bool fromAnonymousUser, bool isEdited, bool fromOnline);
    void onFriendChatSent(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool fromAnonymousUser);
    void onFriendChatFailedToSend(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool fromAnonymousUser);
    void onFriendChatSeen(UserIdentity userId, UserIdentity friendid, const std::vector<SeenPacketDTO> &seenPacketList, bool fromAnonymousUser);
    void onFriendChatSeenConfirmed(UserIdentity userId, UserIdentity friendid, std::vector<SeenPacketDTO> &packetIds, bool fromAnonymousUser);
    void onFriendChatTyping(UserIdentity userId, UserIdentity friendid, bool fromAnonymousUser);
    void onFriendChatIdle(UserIdentity friendid, bool fromAnonymousUser);
    void onFriendChatEdited(UserIdentity senderId, UserIdentity receiverId, const std::string &packetId, int messageType, int timeout, const std::string &message, long long messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser);
    void onFriendChatDeleted(UserIdentity senderId, UserIdentity friendid, const std::vector<std::string> &packetId, bool fromAnonymousUser);
    void onFriendChatDeleteRequestStatus(UserIdentity userId, UserIdentity friendid, const std::string &packetId, const std::vector<std::string> &packetIds, bool fromAnonymousUser, bool status, int deleteType);
    void onBlocked(UserIdentity blockerId, UserIdentity blockedId, long long blockUnblockDate, bool addToBlock);
    void onUnblocked(UserIdentity blockerId, UserIdentity blockedId, long long blockUnblockDate);
    void onBlockUnblockRequestStatus(UserIdentity userId, UserIdentity friendid, const std::string &packetId, long long blockUnblockDate, bool status, bool isBlockRequest);
    void onGroupChatSent(GroupIdentity groupId, const std::string &packetId, bool isEdited);
    void onGroupChatReceived(UserIdentity senderId, GroupIdentity groupid, const std::string &packetId, int messageType, const std::string &message, long long messageDate, bool fromOnline);
    void onGroupChatDelivered(UserIdentity friendid, GroupIdentity groupid, const std::string &packetId);
    void onGroupChatDeleted(UserIdentity friendid, GroupIdentity groupid, const std::vector<std::string> &packetId);
    void onGroupChatDeleteRequestStatus(GroupIdentity groupid, const std::string &packetId, const std::vector<std::string> &packetIds, bool status);
    void onGroupChatSeen(GroupIdentity groupid, UserIdentity userId, const std::vector<std::string> &packetIds);
    void onGroupChatSeenRequestStatus(GroupIdentity groupid, const std::vector<std::string> &packetIds, bool status);
    void onGroupChatTyping(UserIdentity friendid, GroupIdentity groupid);
    void onGroupChatIdle(UserIdentity friendid, GroupIdentity groupid);
    void onGroupChatEdited(UserIdentity senderId, GroupIdentity groupId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, bool fromOnline);
    void onGroupMemberRemoveLeaveRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::vector<MemberDTO> &memberList, bool isHide);
    void onGroupMemberRemovedOrLeft(UserIdentity friendid, GroupIdentity groupid, const std::vector<UserIdentity> &memberList, const std::string &packetId, bool isHide);
    void onGroupMemberAddRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::vector<MemberDTO> &memberList);
    void onGroupMemberAdded(UserIdentity friendid, GroupIdentity groupid, const std::vector<MemberDTO> &memberList, const std::string &packetId);
    void onGroupMemberStatusChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::vector<MemberDTO> &memberList);
    void onGroupMemberStatusChanged(UserIdentity senderid, GroupIdentity groupid, const std::vector<MemberDTO> &memberList, const std::string &packetId);
    void onGroupChatFailedToSend(GroupIdentity groupId, const std::string &packetId);
    void shouldCheckFriendPresence(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser, int profileType);
    void shouldCheckServerAddressForFriend(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser);
    void shouldCheckServerAddressForGroup(GroupIdentity groupId);
    void shouldCheckOfflineServerAddress();
    void onServerTimeSynced(long long timeDifference);
    
    void shouldUpdateUserPassword();
//    void onFriendFileTransferRequestReceived(UserIdentity friendId, std::string fileName, FileIdentity fileId, long long fileSize);
    void onSDKError(int errorCode, const std::string &packetId);
    
    void onFriendHistoryMessageReceived(UserIdentity userId, UserIdentity friendId, const std::vector<SDKMessageDTO> &friendHistoryMessageList, int direction);
    void onFriendMessagesStatusReceived(UserIdentity userId, UserIdentity friendId, const std::vector<FriendMessageStatusDTO> &messageList);
    void onFriendHistoryCompleted(UserIdentity userId, UserIdentity friendId, int direction);
    void onGroupHistoryMessageReceived(GroupIdentity groupId, const std::vector<SDKMessageDTO> &groupHistoryMessageList, int direction);
    void onGroupHistoryCompleted(GroupIdentity groupId, int direction);
    void onGroupInformationWithMembersReceived(GroupIdentity groupId, const std::string &groupName, const std::string &groupUrl, const std::vector<MemberDTO> &memberList);
    void onGroupInformationWithMembersRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status);
    void onGroupInformationActivityFromHistoryMessageReceived(GroupIdentity groupId, const std::vector<GroupActivityDTO> &groupActivityList, int direction);
    void onGroupInformationActivityReceived(const std::vector<GroupActivityDTO> &groupActivityList);
    void onMyGroupListReceived(const std::vector<GroupDTO> &myGroupList);
    void onMyGroupListPagingReceived(const std::vector<GroupDTO> &myGroupList, const std::string &pivotId, int direction);
    void onMyGroupListReceiveCompleted();
    void onGroupCreated(GroupIdentity groupId, const std::string &packetId, bool status);
    //void onGroupInformationChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status);
    void onGroupNameChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::string &groupName);
    void onGroupUrlChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::string &groupUrl);
    void onGroupNameChanged(const std::string &packetId, UserIdentity friendid, GroupIdentity groupid, const std::string &groupName);
    void onGroupUrlChanged(const std::string &packetId, UserIdentity friendid, GroupIdentity groupid, const std::string &groupUrl);
    void onFriendHistoryMessageRequestStatus(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool status);
    void onGroupHistoryMessageRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status);
    
    void onPublicRoomChatRegisterSuccess(RoomIdentity &roomId, const std::string &packetId, int numberOfMember, long long anonymousId);
    void onPublicRoomChatRegisterFailure(RoomIdentity &roomId, const std::string &packetId);
    void onPublicRoomChatRegistrationExpired(RoomIdentity &roomId);
    void onPublicRoomChatDelivered(RoomIdentity &roomId, const std::string &packetId, bool isEdited);
    void onPublicRoomChatFailedToSend(RoomIdentity &roomId, const std::string &packetId);
    void onPublicRoomChatReceived(RoomIdentity &roomId, UserIdentity friendId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, const std::string &memberFullName, const std::string &memberProfileUrl);
    void onPublicRoomListReceived(const std::vector<RoomDTO> &roomList, bool roomListWithHistory);
    void onPublicRoomInformationReceived(RoomIdentity &roomId, std::string &roomName, std::string &roomUrl, const std::string &packetId);
    void onPublicRoomChatEdited(RoomIdentity &roomId, UserIdentity friendId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, const std::string &memberFullName, const std::string &memberProfileUrl);
    void onPublicRoomChatTyping(RoomIdentity &roomId, UserIdentity friendId, const std::string &memberName);
    void onPublicChatMemberListReceived(RoomIdentity &roomId, const std::string &pagingState, const std::vector<PublicChatMemberDTO> &publicChatMemberList);
    void onPublicChatMemberCountChanged(RoomIdentity &roomId, int numberOfMembers);
    void shouldCheckServerAddressForRoom(RoomIdentity &roomId);
    void onPublicRoomChatHistoryReceived(RoomIdentity &roomId, const std::vector<SDKMessageDTO> &publicChatMessageList);
    void onPublicRoomChatHistoryCompleted(RoomIdentity &roomId);
    void onPublicRoomListRequestStatus(const std::string &packetId, bool requestStatus);
    void onPublicRoomInformationRequestFailed(RoomIdentity &roomId, const std::string &packetId);
    void onPublicRoomChatHistoryRequestStatus(RoomIdentity &roomId, const std::string &packetId, bool requestStatus);
    void onPublicRoomMemberListRequestStatus(RoomIdentity &roomId, const std::string &packetId, bool requestStatus);
    
    void onShadowIdsInfoRequestFailed(const std::string &packetId);
    void onShadowIdsInfoResponseReceived(const std::vector<PublicChatMemberDTO> &shadowIdsInfo);
    
    void onFileStreamRequestReceived(UserIdentity userId, UserIdentity friendId, FileIdentity fileId);
    void onFriendFileSessionRequestSuccess(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId, int fileTransferPort);
    void onFriendFileTransferSessionRequestFailed(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId);
    void onFriendFileStreamRequestSuccess(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId);
    void onFriendFileTransferStreamRequestFailed(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId);
    
    //Live stream chat
    void onLiveStreamChatRegisterSuccess(UserIdentity publisherId, const std::string &packetId);
    void onLiveStreamChatRegisterFailure(UserIdentity publisherId, const std::string &packetId);
    void onLiveStreamChatRegistrationExpired(UserIdentity publisherId);
    void onLiveStreamChatDelivered(UserIdentity publisherId, const std::string &packetId);
    void onLiveStreamChatFailedToSend(UserIdentity publisherId, const std::string &packetId);
    void onLiveStreamChatReceived(UserIdentity publisherId, UserIdentity senderId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, const std::string &senderFullName);
    void onLiveStreamChatTyping(UserIdentity publisherId, UserIdentity senderId);
    void shouldCheckServerAddressForLiveStreamChat(UserIdentity publisherId);
    void onLiveStreamChatBlockUserRequestStatus(UserIdentity blockedUserId, const std::string &packetId);
    void onLiveStreamChatUserBlocked(UserIdentity publisherId, UserIdentity blockedUserId);
    
//    void onFileTransferProgress(IPVLongType fileID, IPVLongType friendName, IPVLongType receivedLength);
//    void onFileTransferCompleted(IPVLongType fileID, IPVLongType friendName, IPVLongType receivedLength);
//    void onFileTransferCanceled(IPVLongType fileID, IPVLongType friendName, IPVLongType receivedLength);
//    void onFileTransferFailed(IPVLongType fileID, IPVLongType friendName, IPVLongType receivedLength);
    void onGroupFileStreamRequestReceived(UserIdentity friendId, GroupIdentity groupId, FileIdentity fileId);
    void onGroupFileSessionRequestSuccess(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId, int fileTransferPort);
    void onGroupFileTransferSessionRequestFailed(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId);
    void onGroupFileStreamRequestSuccess(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId);
    void onGroupFileTransferStreamRequestFailed(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId);
    
    void onFriendGetChatMessageReceived(UserIdentity userId, UserIdentity friendId, const SDKMessageDTO& friendChatMessageDTO);
    void onGroupGetChatMessageReceived(GroupIdentity groupId, const SDKMessageDTO& groupChatMessageDTO);
    void onFriendGetChatMessageFailedToSend(UserIdentity userId, UserIdentity friendId, const std::string &packetId);
    void onGroupGetChatMessageFailedToSend(GroupIdentity groupId, const std::string &packetId);
    
    void onGroupChatMessageSeenListReceived(GroupIdentity groupId, const std::string &packetId, const std::vector<MemberDTO> &memberList);
    void onGroupChatMessageSeenListRequestStatus(GroupIdentity groupId, const std::string &requestPacketId, const std::string &messagePacketId, bool status);
    void onFriendChatConversationListReceived(UserIdentity userId, const std::vector<SDKMessageDTO> &conversationList, bool isFromSynced);
    void onGroupChatConversationListReceived(const std::vector<SDKMessageDTO> &conversationList, bool isFromSynced);
    void onChatConversationListRequestStatus(UserIdentity userId, long long friendOrGroupId, const std::string &packetId, bool status);
    void onChatConversationListCompleted(UserIdentity userId, bool isFromSynced);
    void onConversationListDeleteRequestStatus(UserIdentity userId, const std::string &packetId, bool status);
    void onConversationListMarkAsSeenRequestStatus(UserIdentity userId, const std::string &packetId, bool status);
    
    void onNetworkDataCounted(const DataCounter& dataCounter);
    
    void onPublicChatMessageDeleted(RoomIdentity& roomId, const std::vector<std::string>& deletedPacketIds);
    void onPublicChatMessageLiked(RoomIdentity& roomId, const std::string &packetId, UserIdentity likerId);
    void onPublicChatMessageUnliked(RoomIdentity& roomId, const std::string &packetId, UserIdentity unlikerId);
    void onPublicChatMessageReported(RoomIdentity& roomId, const std::string &packetId, UserIdentity reporterId);
    void onPublicChatCategoryListReceived(std::vector<std::string> &publicChatCategoryList);
    void onPublicChatLikeMemberListReceived(RoomIdentity &roomId, const std::string &packetId, const std::vector<PublicChatMemberDTO> &publicChatMemberList);
    
    void onPublicChatDeleteRequestStatus(RoomIdentity roomId, const std::string &packetId, bool status);
    void onPublicChatLikeUnlikeRequestStatus(RoomIdentity roomId, const std::string &requestPacketId, const std::string &messagePacketId, bool status, bool fromLikeRequest);
    void onPublicChatReportRequestStatus(RoomIdentity roomId, const std::string &requestPacketId, const std::string &messagePacketId, bool status);
    void onPublicChatLikeMemberListRequestStatus(RoomIdentity roomId, const std::string &packetId, bool status);
    void onPublicChatCategoryListRequestStatus(const std::string &packetId, bool status);
    
    void onFriendFileManifestUploaded(UserIdentity userId, UserIdentity friendId, const std::string &packetId, std::string fileUrl, int mediaType, int timeout, std::string caption, int widthOrFileSize, int heightOrDuration);
    void onFriendIncomingChatMedia(UserIdentity userId, UserIdentity friendId, std::string fileName, const std::string &packetId, int messageType, int timeout, long long messageDate, bool isSecretVisible, std::string caption, int widthOrSize, int heightOrDuration);
    void onFriendChatMediaTransferProgress(UserIdentity userId, UserIdentity friendId, std::string fileName, double transferPercentage, bool isUpload, const std::string &packetId);
    void onFriendChatMediaTransferFailed(UserIdentity userId, UserIdentity friendId, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer);
    void onFriendChatMediaTransferCanceled(UserIdentity userId, UserIdentity friendId, UserIdentity canceledBy, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer);
    void onFriendChatMediaDownloadCompleted(UserIdentity userId, UserIdentity friendId, std::string fileNameWithPath, const std::string &packetId, int mediaType, int timeout);
    
    void onGroupFileManifestUploaded(GroupIdentity groupId, const std::string &packetId, std::string cloudManifestUrl, int messageType, std::string caption, int widthOrFileSize, int heightOrDuration);    
    void onGroupIncomingChatMedia(UserIdentity friendId, GroupIdentity groupId, std::string fileName, const std::string &packetId, int messageType, long long messageDate, std::string caption, int widthOrSize, int heightOrDuration);    
    void onGroupChatMediaTransferProgress(UserIdentity friendId, GroupIdentity groupId, std::string fileName, double transferPercentage, bool isUpload, const std::string &packetId);
    void onGroupChatMediaTransferFailed(UserIdentity friendId, GroupIdentity groupId, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer);
    void onGroupChatMediaTransferCanceled(UserIdentity friendId, GroupIdentity groupId, UserIdentity canceledBy, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer);
    void onGroupChatMediaDownloadCompleted(UserIdentity friendId, GroupIdentity groupId, std::string fileNameWithPath, const std::string &packetId, int mediaType);
	void onGeneralEncryptedPacketReceived(UserIdentity userID, UserIdentity friendID, const std::string &packetID, int type, int informationType, const std::string &information);
	void onGeneralEncryptedPacketConfirmationReceived(UserIdentity userID, UserIdentity friendID, const std::string &packetID, int type, int informationType);
    
	void onChatMediaTransferDirectoryError(std::string directoryPath);
    void shouldUpdateAppSessionID();
    
    void onSyncConversationRequestStatus(UserIdentity userId, const std::string &packetId, long long syncTime, bool status);
    
    void onSyncFriendHistoryMessageRequestStatus(UserIdentity userId, UserIdentity friendId, const std::string &packetId, long long syncTime, int direction, bool status);
    void onSyncFriendHistoryMessageReceived(UserIdentity userId, UserIdentity friendId, const std::string &packetId, const std::vector<SDKMessageDTO> &friendHistoryMessageList, long long oldestMessageDate, int direction);
    void onSyncFriendHistoryMessageReceiveCompleted(UserIdentity userId, UserIdentity friendId, const std::string &packetId, int direction);
    
    void onSyncGroupHistoryMessageRequestStatus(GroupIdentity groupId, const std::string &packetId, long long syncTime, int direction, bool status);
    void onSyncGroupHistoryMessageReceived(GroupIdentity groupId, const std::string &packetId, const std::vector<SDKMessageDTO> &groupHistoryMessageList, const std::vector<GroupActivityDTO> &groupHistoryActivityList, long long oldestMessageDate, int direction);
    void onSyncGroupHistoryMessageReceiveCompleted(GroupIdentity groupId, const std::string &packetId, int direction);
    
    void onAddNoticeRequestStatus(const std::string &packetId, bool status);
private:
    JNIEnv *env;
    jobject eventHandler{nullptr};
    JavaVM *javaVM;
};
}
#endif	/* CHATEVENTHANDLER_H */

