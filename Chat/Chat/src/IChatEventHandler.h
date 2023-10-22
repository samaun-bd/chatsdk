/* 
 * File:   IChatEventHandler.h
 * Author: dipal
 *
 * Created on September 2, 2015, 4:02 PM
 */

#ifndef ICHATEVENTHANDLER_H
#define	ICHATEVENTHANDLER_H

#include "Types.h"
#include <string>
#include <vector>
#include "MemberDTO.h"
#include "SeenPacketDTO.h"
#include "FriendMessageStatusDTO.h"
#include "GroupActivityDTO.h"
#include "GroupDTO.h"
#include "RoomDTO.h"
#include "PublicChatMemberDTO.h"
#include "SDKMessageDTO.h"
#include "DataCounter.h"


namespace imsdk {
class IChatEventHandler {
public:
    IChatEventHandler();
    virtual ~IChatEventHandler();
    
    virtual void onEventHandlerAttached()=0;
    virtual void onEventHandlerDetached()=0;
    virtual void onActivaeOrDeactivateUserAccountStatus(UserIdentity userId, const std::string &packetId, bool isAccountActivate, bool status) = 0;
    virtual void onGetUserInfoReceived(UserIdentity userId, UserIdentity friendId, const std::string &packetId, std::string friendName, UserIdentity friendRingId, std::string friendProfileImageUrl, int friendProfileType) = 0;
    virtual void onGetUserInfoFailure(UserIdentity userId, UserIdentity friendId, const std::string &packetId) = 0;
	virtual void onFriendChatRegisterSuccess(UserIdentity userId, UserIdentity friendId, long long serverDate, const std::string &packetId, bool fromAnonymousUser) = 0;
	virtual void onFriendChatRegisterFailure(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool fromAnonymousUser) = 0;
	virtual void onFriendRegistrationExpired(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser) = 0;
	virtual void onFriendUnregistered(UserIdentity userId, UserIdentity friendId, int onlineStatus, int onlineMood, bool fromAnonymousUser, int profileType) = 0;
    virtual void onGroupChatRegisterSuccess(GroupIdentity groupId, long long serverDate, const std::string &packetId) = 0;
    virtual void onGroupChatRegisterFailure(GroupIdentity groupId, const std::string &packetId) = 0;
    virtual void onGroupRegistrationExpired(GroupIdentity groupId, long long lastActivityTime)=0;
    virtual void onFriendChatReceived(UserIdentity senderId, UserIdentity receiverId, const std::string &packetId, int messageType, int timeout, const std::string &message, long long messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser)=0;
	virtual void onFriendChatDelivered(UserIdentity userId, UserIdentity friendid, const std::string &packetId, bool fromAnonymousUser, bool isEdited, bool fromOnline) = 0;
	virtual void onFriendChatSent(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool fromAnonymousUser) = 0;
	virtual void onFriendChatFailedToSend(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool fromAnonymousUser) = 0;
	virtual void onFriendChatSeen(UserIdentity userId, UserIdentity friendid, const std::vector<SeenPacketDTO> &seenPacketList, bool fromAnonymousUser) = 0;
	virtual void onFriendChatSeenConfirmed(UserIdentity userId, UserIdentity friendid, std::vector<SeenPacketDTO> &packetIds, bool fromAnonymousUser) = 0;
	virtual void onFriendChatTyping(UserIdentity userId, UserIdentity friendid, bool fromAnonymousUser) = 0;
    virtual void onFriendChatIdle(UserIdentity friendid, bool fromAnonymousUser)=0;
    virtual void onFriendChatEdited(UserIdentity senderId, UserIdentity receiverId, const std::string &packetId, int messageType, int timeout, const std::string &message, long long messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser)=0;
    virtual void onFriendChatDeleted(UserIdentity senderId, UserIdentity friendid, const std::vector<std::string> &packetId, bool fromAnonymousUser)=0;
    virtual void onFriendChatDeleteRequestStatus(UserIdentity userId, UserIdentity friendid, const std::string &packetId, const std::vector<std::string> &packetIds, bool fromAnonymousUser, bool status, int deleteType) = 0;
    virtual void onBlocked(UserIdentity blockerId, UserIdentity blockedId, long long blockUnblockDate, bool addToBlock)=0;
    virtual void onUnblocked(UserIdentity blockerId, UserIdentity blockedId, long long blockUnblockDate)=0;
	virtual void onBlockUnblockRequestStatus(UserIdentity userid, UserIdentity friendid, const std::string &packetId, long long blockUnblockDate, bool status, bool isBlockRequest) = 0;
    virtual void onGroupChatSent(GroupIdentity groupId, const std::string &packetId, bool isEdited)=0;
    virtual void onGroupChatReceived(UserIdentity senderId, GroupIdentity groupid, const std::string &packetId, int messageType, const std::string &message, long long messageDate, bool fromOnline)=0;
    virtual void onGroupChatDelivered(UserIdentity friendid, GroupIdentity groupid, const std::string &packetId)=0;
    virtual void onGroupChatDeleted(UserIdentity friendid, GroupIdentity groupid, const std::vector<std::string> &packetIdList)=0;
    virtual void onGroupChatDeleteRequestStatus(GroupIdentity groupid, const std::string &packetId, const std::vector<std::string> &packetIds, bool status)=0;
    virtual void onGroupChatSeen(GroupIdentity groupid, UserIdentity userId, const std::vector<std::string> &packetIds)=0;
    virtual void onGroupChatSeenRequestStatus(GroupIdentity groupid, const std::vector<std::string> &packetIds, bool status)=0;
    virtual void onGroupChatTyping(UserIdentity friendid, GroupIdentity groupid)=0;
    virtual void onGroupChatIdle(UserIdentity friendid, GroupIdentity groupid)=0;
    virtual void onGroupChatEdited(UserIdentity senderId, GroupIdentity groupId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, bool fromOnline)=0;
    virtual void onGroupMemberRemoveLeaveRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::vector<MemberDTO> &memberList, bool isHide)=0;
    virtual void onGroupMemberRemovedOrLeft(UserIdentity friendid, GroupIdentity groupid, const std::vector<UserIdentity> &memberList, const std::string &packetId, bool isHide) = 0;
    virtual void onGroupMemberAddRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::vector<MemberDTO> &memberList)=0;
    virtual void onGroupMemberAdded(UserIdentity friendid, GroupIdentity groupid, const std::vector<MemberDTO> &memberList, const std::string &packetId)=0;
    virtual void onGroupMemberStatusChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::vector<MemberDTO> &memberList)=0;
    virtual void onGroupMemberStatusChanged(UserIdentity senderid, GroupIdentity groupid, const std::vector<MemberDTO> &memberList, const std::string &packetId)=0;
    virtual void onGroupChatFailedToSend(GroupIdentity groupId, const std::string &packetId)=0;
	virtual void shouldCheckFriendPresence(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser, int profileType) = 0;
	virtual void shouldCheckServerAddressForFriend(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser) = 0;
    virtual void shouldCheckServerAddressForGroup(GroupIdentity groupId)=0;
    virtual void shouldCheckOfflineServerAddress()=0;
    virtual void onServerTimeSynced(long long timeDifference)=0;
    
    virtual void shouldUpdateUserPassword()=0;
//    virtual void onFriendFileTransferRequestReceived(UserIdentity friendId, std::string fileName, FileIdentity fileId, long long fileSize)=0;
    virtual void onSDKError(int errorCode, const std::string &packetId)=0;
    
	virtual void onFriendHistoryMessageReceived(UserIdentity userId, UserIdentity friendId, const std::vector<SDKMessageDTO> &friendHistoryMessageList, int direction) = 0;//UserIdentity senderId, UserIdentity receiverId, const std::string &packetId, int messageType, int timeout, const std::string &message, long long messageDate, bool isSecretVisible, int messageStatus, int direction
	virtual void onFriendMessagesStatusReceived(UserIdentity userId, UserIdentity friendId, const std::vector<FriendMessageStatusDTO> &messageList) = 0;
	virtual void onFriendHistoryCompleted(UserIdentity userId, UserIdentity friendId, int direction) = 0;
    virtual void onGroupHistoryMessageReceived(GroupIdentity groupId, const std::vector<SDKMessageDTO> &groupHistoryMessageList, int direction)=0;//UserIdentity senderId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, int direction
    virtual void onGroupHistoryCompleted(GroupIdentity groupId, int direction)=0;
    virtual void onGroupInformationWithMembersReceived(GroupIdentity groupId, const std::string &groupName, const std::string &groupUrl, const std::vector<MemberDTO> &memberList)=0;
    virtual void onGroupInformationWithMembersRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status) = 0;
    virtual void onGroupInformationActivityReceived(const std::vector<GroupActivityDTO> &groupActivityList)=0;
    virtual void onGroupInformationActivityFromHistoryMessageReceived(GroupIdentity groupId, const std::vector<GroupActivityDTO> &groupActivityList, int direction)=0;
    virtual void onMyGroupListReceived(const std::vector<GroupDTO> &myGroupList) = 0;
    virtual void onMyGroupListPagingReceived(const std::vector<GroupDTO> &myGroupList, const std::string &pivotId, int direction) = 0;
    virtual void onMyGroupListReceiveCompleted() = 0;
    virtual void onGroupCreated(GroupIdentity groupId, const std::string &packetId, bool status) = 0;
    //virtual void onGroupInformationChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status)=0;
    virtual void onGroupNameChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::string &groupName)=0;
    virtual void onGroupUrlChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::string &groupUrl)=0;
    virtual void onGroupNameChanged(const std::string &packetId, UserIdentity friendid, GroupIdentity groupid, const std::string &groupName)=0;
    virtual void onGroupUrlChanged(const std::string &packetId, UserIdentity friendid, GroupIdentity groupid, const std::string &groupUrl)=0;

	virtual void onFriendHistoryMessageRequestStatus(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool status) = 0;
    virtual void onGroupHistoryMessageRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status) = 0;
                                                
    virtual void onGroupChatMessageSeenListReceived(GroupIdentity groupId, const std::string &packetId, const std::vector<MemberDTO> &memberList)=0;
    virtual void onGroupChatMessageSeenListRequestStatus(GroupIdentity groupId, const std::string &requestPacketId, const std::string &messagePacketId, bool status)=0;
    
	virtual void onFriendChatConversationListReceived(UserIdentity userId, const std::vector<SDKMessageDTO> &conversationList, bool isFromSynced) = 0;
    virtual void onGroupChatConversationListReceived(const std::vector<SDKMessageDTO> &conversationList, bool isFromSynced) = 0;
	virtual void onChatConversationListRequestStatus(UserIdentity userId, long long friendOrGroupId, const std::string &packetId, bool status) = 0;
    virtual void onChatConversationListCompleted(UserIdentity userId, bool isFromSynced) = 0;
	virtual void onConversationListDeleteRequestStatus(UserIdentity userId, const std::string &packetId, bool status) = 0;
	virtual void onConversationListMarkAsSeenRequestStatus(UserIdentity userId, const std::string &packetId, bool status) = 0;
    
    //Public Room Chat
    virtual void onPublicRoomChatRegisterSuccess(RoomIdentity &roomId, const std::string &packetId, int numberOfMembers, long long anonymousId)=0;
    virtual void onPublicRoomChatRegisterFailure(RoomIdentity &roomId, const std::string &packetId)=0;
    virtual void onPublicRoomChatRegistrationExpired(RoomIdentity &roomId)=0;
    virtual void onPublicRoomChatDelivered(RoomIdentity &roomId, const std::string &packetId, bool isEdited)=0;
    virtual void onPublicRoomChatFailedToSend(RoomIdentity &roomId, const std::string &packetId)=0;
    virtual void onPublicRoomChatReceived(RoomIdentity &roomId, UserIdentity friendId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, const std::string &memberFullName, const std::string &memberProfileUrl)=0;
    virtual void onPublicRoomListReceived(const std::vector<RoomDTO> &roomList, bool roomListFromHistory)=0;
    virtual void onPublicRoomInformationReceived(RoomIdentity &roomId, std::string &roomName, std::string &roomUrl, const std::string &packetId)=0;
    virtual void onPublicRoomChatEdited(RoomIdentity &roomId, UserIdentity friendId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, const std::string &memberFullName, const std::string &memberProfileUrl)=0;
    virtual void onPublicRoomChatTyping(RoomIdentity &roomId, UserIdentity friendId, const std::string &memberName)=0;
    virtual void onPublicChatMemberListReceived(RoomIdentity &roomId, const std::string &pagingState, const std::vector<PublicChatMemberDTO> &publicChatMemberList)=0;
    virtual void onPublicChatMemberCountChanged(RoomIdentity &roomId, int numberOfMembers)=0;
    virtual void shouldCheckServerAddressForRoom(RoomIdentity &roomId)=0;
    virtual void onPublicRoomChatHistoryReceived(RoomIdentity &roomId, const std::vector<SDKMessageDTO> &publicChatMessageList)=0;
    virtual void onPublicRoomChatHistoryCompleted(RoomIdentity &roomId)=0;
    virtual void onPublicRoomListRequestStatus(const std::string &packetId, bool requestStatus) = 0;
    virtual void onPublicRoomInformationRequestFailed(RoomIdentity &roomId, const std::string &packetId) = 0;
    virtual void onPublicRoomChatHistoryRequestStatus(RoomIdentity &roomId, const std::string &packetId, bool requestStatus) = 0;
    virtual void onPublicRoomMemberListRequestStatus(RoomIdentity &roomId, const std::string &packetId, bool requestStatus) = 0;
    virtual void onPublicChatMessageDeleted(RoomIdentity& roomId, const std::vector<std::string>& deletedPacketIds)=0;
    virtual void onPublicChatMessageLiked(RoomIdentity& roomId, const std::string& packetId, UserIdentity likerId)=0;
    virtual void onPublicChatMessageUnliked(RoomIdentity& roomId, const std::string& packetId, UserIdentity unlikerId)=0;
    virtual void onPublicChatMessageReported(RoomIdentity& roomId, const std::string& packetId, UserIdentity reporterId)=0;
    virtual void onPublicChatCategoryListReceived(std::vector<std::string> &publicChatCategoryList)=0;
    virtual void onPublicChatLikeMemberListReceived(RoomIdentity &roomId, const std::string &packetId, const std::vector<PublicChatMemberDTO> &publicChatMemberList)=0;
    
    virtual void onPublicChatDeleteRequestStatus(RoomIdentity roomId, const std::string &packetId, bool status)=0;
    virtual void onPublicChatLikeUnlikeRequestStatus(RoomIdentity roomId, const std::string &requestPacketId, const std::string &messagePacketId, bool status, bool fromLikeRequest)=0;
    virtual void onPublicChatReportRequestStatus(RoomIdentity roomId, const std::string &requestPacketId, const std::string &messagePacketId, bool status)=0;
    virtual void onPublicChatLikeMemberListRequestStatus(RoomIdentity roomId, const std::string &packetId, bool status)=0;
    virtual void onPublicChatCategoryListRequestStatus(const std::string &packetId, bool status)=0;
    
    virtual void onShadowIdsInfoRequestFailed(const std::string &packetId) = 0;
    virtual void onShadowIdsInfoResponseReceived(const std::vector<PublicChatMemberDTO> &shadowIdsInfo) = 0;
    
	virtual void onFileStreamRequestReceived(UserIdentity userId, UserIdentity friendId, FileIdentity fileId) = 0;
	virtual void onFriendFileSessionRequestSuccess(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId, int fileTransferPort) = 0;
	virtual void onFriendFileTransferSessionRequestFailed(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId) = 0;
	virtual void onFriendFileStreamRequestSuccess(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId) = 0;
	virtual void onFriendFileTransferStreamRequestFailed(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId) = 0;
    
    //Live stream chat
    virtual void onLiveStreamChatRegisterSuccess(UserIdentity publisherId, const std::string &packetId)=0;
    virtual void onLiveStreamChatRegisterFailure(UserIdentity publisherId, const std::string &packetId)=0;
    virtual void onLiveStreamChatRegistrationExpired(UserIdentity publisherId)=0;
    virtual void onLiveStreamChatDelivered(UserIdentity publisherId, const std::string &packetId)=0;
    virtual void onLiveStreamChatFailedToSend(UserIdentity publisherId, const std::string &packetId)=0;
    virtual void onLiveStreamChatReceived(UserIdentity publisherId, UserIdentity senderId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, const std::string &senderFullName)=0;
    virtual void onLiveStreamChatTyping(UserIdentity publisherId, UserIdentity senderId)=0;
    virtual void shouldCheckServerAddressForLiveStreamChat(UserIdentity publisherId)=0;
    virtual void onLiveStreamChatBlockUserRequestStatus(UserIdentity blockedUserId, const std::string &packetId)=0;
    virtual void onLiveStreamChatUserBlocked(UserIdentity publisherId, UserIdentity blockedUserId)=0;
    
    //Group file transfer
    virtual void onGroupFileStreamRequestReceived(UserIdentity friendId, GroupIdentity groupId, FileIdentity fileId)=0;
    virtual void onGroupFileSessionRequestSuccess(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId, int fileTransferPort)=0;
    virtual void onGroupFileTransferSessionRequestFailed(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId)=0;
    virtual void onGroupFileStreamRequestSuccess(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId)=0;
    virtual void onGroupFileTransferStreamRequestFailed(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId)=0;

	virtual void onFriendGetChatMessageReceived(UserIdentity userId, UserIdentity friendId, const SDKMessageDTO& friendChatMessageDTO) = 0;
    virtual void onGroupGetChatMessageReceived(GroupIdentity groupId, const SDKMessageDTO& groupChatMessageDTO)=0;
	virtual void onFriendGetChatMessageFailedToSend(UserIdentity userId, UserIdentity friendId, const std::string& packetId) = 0;
    virtual void onGroupGetChatMessageFailedToSend(GroupIdentity groupId, const std::string& packetId)=0;
    
    virtual void onNetworkDataCounted(const DataCounter& dataCounter)=0;
    
	virtual void onFriendFileManifestUploaded(UserIdentity userId, UserIdentity friendId, const std::string &packetId, std::string cloudManifestUrl, int messageType, int timeout, std::string caption, int widthOrFileSize, int heightOrDuration) = 0;
	virtual void onFriendIncomingChatMedia(UserIdentity userId, UserIdentity friendId, std::string fileName, const std::string &packetId, int messageType, int timeout, long long messageDate, bool isSecretVisible, std::string caption, int widthOrSize, int heightOrDuration) = 0;
	virtual void onFriendChatMediaTransferProgress(UserIdentity userId, UserIdentity friendId, std::string fileName, double transferPercentage, bool isUpload, const std::string &packetId) = 0;
	virtual void onFriendChatMediaTransferFailed(UserIdentity userId, UserIdentity friendId, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer) = 0;
	virtual void onFriendChatMediaTransferCanceled(UserIdentity userId, UserIdentity friendId, UserIdentity canceledBy, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer) = 0;
	virtual void onFriendChatMediaDownloadCompleted(UserIdentity userId, UserIdentity friendId, std::string fileNameWithPath, const std::string &packetId, int mediaType, int timeout) = 0;
    
    virtual void onGroupFileManifestUploaded(GroupIdentity groupId, const std::string &packetId, std::string cloudManifestUrl, int messageType, std::string caption, int widthOrFileSize, int heightOrDuration)=0;
    virtual void onGroupIncomingChatMedia(UserIdentity friendId, GroupIdentity groupId, std::string fileName, const std::string &packetId, int messageType, long long messageDate, std::string caption, int widthOrSize, int heightOrDuration)=0;
    virtual void onGroupChatMediaTransferProgress(UserIdentity friendId, GroupIdentity groupId, std::string fileName, double transferPercentage, bool isUpload, const std::string &packetId)=0;
    virtual void onGroupChatMediaTransferFailed(UserIdentity friendId, GroupIdentity groupId, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer)=0;
    virtual void onGroupChatMediaTransferCanceled(UserIdentity friendId, GroupIdentity groupId, UserIdentity canceledBy, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer)=0;
    virtual void onGroupChatMediaDownloadCompleted(UserIdentity friendId, GroupIdentity groupId, std::string fileNameWithPath, const std::string &packetId, int mediaType)=0;
	virtual void onGeneralEncryptedPacketReceived(UserIdentity userID, UserIdentity friendID, const std::string &packetID, int type, int informationType, const std::string &information) = 0;
	virtual void onGeneralEncryptedPacketConfirmationReceived(UserIdentity userID, UserIdentity friendID, const std::string &packetID, int type, int informationType) = 0;
    
	virtual void onChatMediaTransferDirectoryError(std::string directoryPath) = 0;
    virtual void shouldUpdateAppSessionID()=0;

    virtual void onSyncConversationRequestStatus(UserIdentity userId, const std::string &packetId, long long syncTime, bool status) = 0;
    
    virtual void onSyncFriendHistoryMessageRequestStatus(UserIdentity userId, UserIdentity friendId, const std::string &packetId, long long syncTime, int direction, bool status) = 0;
    virtual void onSyncFriendHistoryMessageReceived(UserIdentity userId, UserIdentity friendId, const std::string &packetId, const std::vector<SDKMessageDTO> &friendHistoryMessageList, long long oldestMessageDate, int direction) = 0;
    virtual void onSyncFriendHistoryMessageReceiveCompleted(UserIdentity userId, UserIdentity friendId, const std::string &packetId, int direction) = 0;

    virtual void onSyncGroupHistoryMessageRequestStatus(GroupIdentity groupId, const std::string &packetId, long long syncTime, int direction, bool status) = 0;
    virtual void onSyncGroupHistoryMessageReceived(GroupIdentity groupId, const std::string &packetId, const std::vector<SDKMessageDTO> &groupHistoryMessageList, const std::vector<GroupActivityDTO> &groupHistoryActivityList, long long oldestMessageDate, int direction) = 0;
    virtual void onSyncGroupHistoryMessageReceiveCompleted(GroupIdentity groupId, const std::string &packetId, int direction) = 0;
    
    //notice
    virtual void onAddNoticeRequestStatus(const std::string &packetId, bool status) = 0;

private:

};
}

#endif	/* ICHATEVENTHANDLER_H */

