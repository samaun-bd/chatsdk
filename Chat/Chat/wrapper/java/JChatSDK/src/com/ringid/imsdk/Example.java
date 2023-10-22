/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ringid.imsdk;

import java.util.*;
import java.util.ArrayList;

class ChatEventHandler implements IChatEventHandler{

    @Override
    public void onGroupChatEdited(long friendId, long groupId, String packetId, int messageType, String message, long messageDate, boolean fromOnline) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatDeleted(long friendid, long groupid, ArrayList<String> packetIds) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatTyping(long friendId, long groupId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatIdle(long friendId, long groupId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatFailedToSend(long groupId, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void shouldCheckServerAddressForGroup(long groupId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void shouldCheckOfflineServerAddress() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onMyGroupListReceived(ArrayList<GroupDTO> myGroupList) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    @Override
    public void onServerTimeSynced(long timeDifference) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

//    @Override
//    public void onFriendFileTransferRequestReceived(long friendId, String fileName, long fileId, long fileSize) {
//        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
//    }
//
//    @Override
//    public void onFileTransferProgress(long fileID, long friendName, long receivedLength) {
//        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
//    }
//
//    @Override
//    public void onFileTransferCompleted(long fileID, long friendName, long receivedLength) {
//        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
//    }
//
//    @Override
//    public void onFileTransferCanceled(long fileID, long friendName, long receivedLength) {
//        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
//    }
//
//    @Override
//    public void onFileTransferFailed(long fileID, long friendName, long receivedLength) {
//        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
//    }

    @Override
    public void onSDKError(int errorCode, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicRoomChatRegistrationExpired(String roomId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupInformationActivityReceived(ArrayList<GroupActivityDTO> groupActivityList) {
                System.out.println("Group information activity received of ;and activity: ");
        for(int i=0;i<groupActivityList.size();i++){
            System.out.println("Member id: "+groupActivityList.get(i).getMemberIdentity()+" ;activity type: "+groupActivityList.get(i).getActivityType());
        }

    }

    @Override
    public void onGroupInformationActivityFromHistoryMessageReceived(long groupId, ArrayList<GroupActivityDTO> groupActivityList, int direction) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupInformationWithMembersReceived(long groupId, String groupName, String groupUrl, ArrayList<MemberDTO> memberList) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatReceived(long friendId, long groupId, String packetId, int messageType, String message, long messageDate, boolean fromOnline) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void shouldCheckServerAddressForRoom(String roomId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicRoomChatReceived(String roomId, long friendId, String packetId, int messageType, String message, long messageDate, String memberFullName, String memberProfileUrl) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicRoomChatEdited(String roomId, long friendId, String packetId, int messageType, String message, long messageDate, String memberFullName, String memberProfileUrl) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicRoomChatHistoryReceived(String roomId, ArrayList<SDKMessageDTO> publicChatHistoryMessageList) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicChatMemberListReceived(String roomId, String pagingState, ArrayList<PublicChatMemberDTO> memberList) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicRoomChatTyping(String roomId, long friendId, String memberName) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatRegisterSuccess(long groupId, long serverDate, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatRegisterFailure(long groupId, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupMemberRemoveLeaveRequestStatus(long groupId, String packetId, boolean status) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupMemberStatusChangeRequestStatus(long groupId, String packetId, boolean status) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendMessagesStatusReceived(long userId, long friendId, ArrayList<FriendMessageStatusDTO> messageList) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    @Override
    public void onGroupInformationWithMembersRequestStatus(long groupId, String packetId, boolean status) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupCreated(long groupId, String packetId, boolean status) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupInformationChangeRequestStatus(long groupId, String packetId, boolean status) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendHistoryMessageRequestStatus(long userId, long friendId, String packetId, boolean status) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupHistoryMessageRequestStatus(long groupId, String packetId, boolean status) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendHistoryCompleted(long userId, long friendId, int direction) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupHistoryCompleted(long groupId, int direction) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicRoomListRequestStatus(String packetId, boolean requestStatus) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatRegisterSuccess(long userId, long friendId, long serverDate, String packetId, boolean fromAnonymousUser) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatRegisterFailure(long userId, long friendId, String packetId, boolean fromAnonymousUser) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendRegistrationExpired(long userId, long friendId, boolean fromAnonymousUser) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendUnregistered(long userId, long friendId, int onlineStatus, int onlineMood, boolean fromAnonymousUser, int profileType) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatReceived(long senderId, long receiverId, String packetId, int messageType, int secretTimeout, String message, long messageDate, boolean isSecretVisible, boolean fromOnline, boolean fromAnonymousUser) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatSent(long userId, long friendId, String packetId, boolean fromAnonymousUser) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatFailedToSend(long userId, long friendId, String packetId, boolean fromAnonymousUser) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatSeen(long userId, long friendId, ArrayList<SeenPacketDTO> seenPacketList, boolean fromAnonymousUser) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatSeenConfirmed(long userId, long friendid, ArrayList<SeenPacketDTO> packetId, boolean fromAnonymousUser) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatTyping(long userId, long friendId, boolean fromAnonymousUser) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatIdle(long friendId, boolean fromAnonymousUser) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatEdited(long senderId, long receiverId, String packetId, int messageType, int secretTimeout, String message, long messageDate, boolean isSecretVisible, boolean fromOnline, boolean fromAnonymousUser) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatDeleted(long senderId, long friendId, ArrayList<String> packetIds, boolean fromAnonymousUser) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatDeleteRequestStatus(long userId, long friendId, String packetId, ArrayList<String> packetIds, boolean fromAnonymousUser, boolean status) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void shouldCheckFriendPresence(long userId, long friendId, boolean fromAnonymousUser, int profileType) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void shouldCheckServerAddressForFriend(long userId, long friendId, boolean fromAnonymousUser) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatDeleteRequestStatus(long groupid, String packetId, ArrayList<String> packetIds, boolean requestStatus) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicRoomChatRegisterFailure(String roomId, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicRoomChatFailedToSend(String roomId, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicRoomInformationReceived(String roomId, String roomName, String roomUrl, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicRoomInformationRequestFailed(String roomId, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicRoomChatHistoryRequestStatus(String roomId, String packetId, boolean requestStatus) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicRoomMemberListRequestStatus(String roomId, String packetId, boolean requestStatus) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicRoomChatRegisterSuccess(String roomId, String packetId, int numberOfMember, long recepientId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onShadowIdsInfoRequestFailed(String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onShadowIdsInfoResponseReceived(ArrayList<PublicChatMemberDTO> shadowIdsInfo) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicChatMemberCountChanged(String roomId, int numberOfMembers) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onBlocked(long blockerId, long blockedId, long blockUnblockDate, boolean addToBlock) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    @Override
    public void onUnblocked(long unBlockerId, long unBlockedId, long blockUnblockDate) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupRegistrationExpired(long groupId, long lastActivityTime) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupMemberRemovedOrLeft(long friendId, long groupId, ArrayList<Long> memberList, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupMemberAdded(long friendId, long groupId, ArrayList<MemberDTO> memberList, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupMemberStatusChanged(long senderId, long groupId, ArrayList<MemberDTO> memberList, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onNetworkDataCounted(DataCounter dataCounter) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicChatMessageDeleted(String roomId, ArrayList<String> packetIds) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicChatMessageLiked(String roomId, String packetId, long recipientId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicChatMessageReported(String roomId, String packetId, long recipientId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicChatCategoryListReceived(ArrayList<String> publicChatCategoryList) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicChatLikeMemberListReceived(String roomId, String packetId, ArrayList<PublicChatMemberDTO> publicChatMemberList) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
	@Override
    public void onGroupChatSeen(long groupId, ArrayList<String> seenPacketIds) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatMessageSeenListReceived(long groupId, String packetId, ArrayList<MemberDTO> memberList) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicChatMessageUnliked(String roomId, String packetId, long messageSenderId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicChatDeleteRequestStatus(String roomId, String packetId, boolean requestStatus) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicChatLikeMemberListRequestStatus(String roomId, String packetId, boolean requestStatus) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicChatCategoryListRequestStatus(String packetId, boolean requestStatus) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatSeenRequestStatus(long groupid, ArrayList<String> packetIds, boolean status) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatConversationListReceived(long userId, ArrayList<SDKMessageDTO> conversationList, boolean isFromSynced) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatConversationListReceived(ArrayList<SDKMessageDTO> conversationList, boolean isFromSynced) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onChatConversationListRequestStatus(long userId, long friendOrGroupId, String packetId, boolean status) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicChatLikeUnlikeRequestStatus(String roomId, String requestPacketId, String messagePacketId, boolean requestStatus, boolean fromLikeRequest) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicChatReportRequestStatus(String roomId, String requestPacketId, String messagePacketId, boolean requestStatus) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onChatConversationListCompleted(long userId, boolean isFromSynced) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicRoomChatHistoryCompleted(String roomId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    @Override
    public void onPublicRoomChatDelivered(String roomId, String packetId, boolean isEdited) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatSent(long groupId, String packetId, boolean isEdited) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatDelivered(long friendId, long groupId, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onConversationListDeleteRequestStatus(long userId, String packetId, boolean status) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onConversationListMarkAsSeenRequestStatus(long userId, String packetId, boolean status) {
    	throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onBlockUnblockRequestStatus(long userId, long friendId, String packetId, long blockUnblockDate, boolean status, boolean isBlockRequest) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onLiveStreamChatRegisterSuccess(long publisherId, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onLiveStreamChatRegisterFailure(long publisherId, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onLiveStreamChatRegistrationExpired(long publisherId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onLiveStreamChatDelivered(long publisherId, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onLiveStreamChatFailedToSend(long publisherId, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onLiveStreamChatReceived(long publisherId, long senderId, String packetId, int messageType, String message, long messageDate, String senderFullName) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onLiveStreamChatTyping(long publisherId, long senderId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void shouldCheckServerAddressForLiveStreamChat(long publisherId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupFileManifestUploaded(long groupId, String packetId, String cloudManifestUrl, int messageType, String caption, int widthOrFileSize, int heightOrDuration) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatMediaTransferProgress(long friendId, long groupId, String fileName, double transferPercentage, boolean isUpload, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatMediaTransferFailed(long friendId, long groupId, String fileName, String packetId, boolean isUpload, boolean isChunkedTransfer) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatMediaDownloadCompleted(long friendId, long groupId, String fileNameWithPath, String packetId, int mediaType) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onPublicRoomListReceived(ArrayList<RoomDTO> roomList, boolean roomListFromHistory) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupMemberAddRequestStatus(long groupId, String packetId, boolean status, ArrayList<MemberDTO> memberList) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendFileManifestUploaded(long userId, long friendId, String packetId, String fileUrl, int mediaType, int timeout, String caption, int widthOrFileSize, int heightOrDuration) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    public void onFriendIncomingChatMedia(long userId, long friendId, String fileName, String packetId, int messageType, int timeout, long messageDate, boolean isSecretVisible) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatMediaTransferProgress(long userId, long friendId, String fileName, double transferPercentage, boolean isUpload, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatMediaTransferFailed(long userId, long friendId, String fileName, String packetId, boolean isUpload, boolean isChunkedTransfer) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatMediaDownloadCompleted(long userId, long friendId, String fileNameWithPath, String packetId, int mediaType, int timeout) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    public void onGroupIncomingChatMedia(long friendId, long groupId, String fileName, String packetId, int messageType, long messageDate) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendIncomingChatMedia(long userId, long friendId, String fileName, String packetId, int messageType, int timeout, long messageDate, boolean isSecretVisible, String caption, int widthOrSize, int heightOrDuration) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupIncomingChatMedia(long friendId, long groupId, String fileName, String packetId, int messageType, long messageDate, String caption, int widthOrSize, int heightOrDuration) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatDelivered(long userId, long friendId, String packetId, boolean fromAnonymousUser, boolean isEdited, boolean fromOnline) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendHistoryMessageReceived(long userId, long friendId, ArrayList<SDKMessageDTO> chatMessageList, int direction) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupHistoryMessageReceived(long groupId, ArrayList<SDKMessageDTO> groupHistoryMessageList, int direction) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void shouldUpdateUserPassword() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupNameChanged(String packetId, long friendid, long groupid, String groupName) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupUrlChanged(String packetId, long friendid, long groupid, String groupUrl) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onChatMediaTransferDirectoryError() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onLiveStreamChatBlockUserRequestStatus(long blockedUserId, String packetId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onLiveStreamChatUserBlocked(long publisherId, long blockedUserId) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void shouldUpdateAppSessionID() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onFriendChatMediaTransferCanceled(long userId, long friendId, long canceledBy, String fileName, String packetId, boolean isUpload, boolean isChunkedTransfer) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onGroupChatMediaTransferCanceled(long friendId, long groupId, long canceledBy, String fileName, String packetId, boolean isUpload, boolean isChunkedTransfer) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void onActivaeOrDeactivateUserAccountStatus(long userId, String packetId, boolean isAccountActivate, boolean status) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    @Override
    public void onSyncConversationRequestStatus(long userId, String packetId, long syncTime, boolean status) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    @Override
    public void onSyncFriendHistoryMessageRequestStatus(long userId, long friendId, String packetId, long syncTime, boolean status) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    @Override
    public void onSyncGroupHistoryMessageRequestStatus(long groupId, String packetId, long syncTime, boolean status) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
}

public class Example {

    public static long fileIdentity = 0;

    public static void menu() {
        System.out.println("reg:     1 friendId status");
        System.out.println("chat:    2 friendId message");
        System.out.println("seen:    3 friendId packetid");
        System.out.println("typing:  4 friendId");
        System.out.println("FriendChatEdit:  5 friendId");
        System.out.println("GroupChat register: 6");
        System.out.println("GroupChat initiator: 7");
        System.out.println("Edit groupChat: 8");
        System.out.println("Send group chat: 9");
        System.out.println("Change group mem status: 10");
        System.out.println("Get offline message: 11");
        System.out.println("Delete group chat message: 12");
        System.out.println("Edit friend Chat message: 13");
        System.out.println("Add group member: 14");
        System.out.println("File transfer: 15");
        System.out.println("Get friend history: 18");
        System.out.println("Get group history: 19");
        System.out.println("quit: -1");
    }
    
    public static void main(String[] args) throws InterruptedException {
        // TODO code application logic here

        long userId, friendId, flag2, groupId;
        int status, type;
        Scanner sc = new Scanner(System.in);
        
        
//        userId = sc.nextLong();
        userId = 2110010115;
        
        ArrayList<String> dirPaths = new ArrayList<String>();
        dirPaths.add("");

        ArrayList<Long> pageIdList = new ArrayList<Long>();

        Chat.initChat(userId, "noman", "192.168.1.251", 1200, "38.127.68.52", 1500, 2, "aa", 134, 0, dirPaths, "", "", false, "", /*appType*/1, pageIdList);
        Chat chat = Chat.getInstance();
        chat.registerEventHandler(new ChatEventHandler());
        menu();
        //type = sc.nextInt();
//        friendId = sc.nextLong();
//        status = sc.nextInt();
//        //chat.registerEventHandler(new ChatEventHandler());
//        chat.registerFriendChat(friendId, "192.168.1.251", 1500, 3, "12654654", 3, status, 2);
//        
//        FriendInformation friendInformation = chat.getFriendInformation(friendId);
//        System.out.println(friendInformation.getFriendRegisterServerAddress()+" "+friendInformation.getFriendRegisterServerPort()+" "+friendInformation.getFriendChatServerPort()+" "+friendInformation.getFriendStatus()+" "+friendInformation.getFriendMood());
//      
        //PacketTimeId packetTimeId = chat.generatePacketId();
        
        //String temp = Long.toUnsignedString(packetTimeId.getTime1970());
        
        //System.out.println(""+ packetTimeId.getTime1970() +" "+System.currentTimeMillis());
//        chat.registerGroupChat(100, 2, "192.168.1.251", 1500);
        PacketTimeId packetTimeId = chat.generatePacketId(userId);
        chat.requestForOffline(packetTimeId.getTime1970()-31536000000L, packetTimeId.getTime1970()-31536000000L);
        
//        while(true)
//        {
//            if (type == 1) {//status is known from the auth server
//                friendId = sc.nextLong();
//                status = sc.nextInt();
//                chat.registerFriendChat(friendId, "192.168.1.251", 1500, 3, "12654654", 3, status, 2);
//                //chat.registerFriendChat(friendId, "38.127.68.54", 1500, 3, "12654654", 3, status, 2);
//            } else if (type == 2) {
//                String message;
//                friendId = sc.nextLong();
//                message = sc.next();
//                String packetId = chat.generatePacketId();
//                chat.sendFriendChat(packetId, friendId, 2, 0, message, 12345678901234567l, true);
//            } else if (type == 3) {
//    //            int friendId;
//    //            string packetId;
//    //            cin >> friendId>>packetId;
//                ArrayList<SeenPacketDTO> seenPacketDTOList;
////                seenPacketDTOList.push_back(SeenPacketDTO(packetId, 5, true)); //packetId, 0, true
////                seenPacketDTOList.push_back(SeenPacketDTO(packetId, 6, true));
////
////                chat.seenFriendChat(friendId, seenPacketDTOList);
//            } else if (type == 4) {
//                friendId = sc.nextLong();
//                chat.typingFriendChat(friendId);
//            }else if (type == 6) {
//                groupId = sc.nextLong();
//                chat.registerGroupChat(groupId, 2, "192.168.1.251", 1500);
////            } else if (type == 7) {
////                int numberOfMembers, groupMember;
////                string message, groupName, url, fullName;
////
////                time_t curtime = time(NULL);
////                long long myTime = (long long) curtime;
////
////                cin >>groupId >> numberOfMembers >> groupName >> url>>fullName;
////
////                vector<MemberDTO> memberList;
////                for (int i = 0; i < numberOfMembers; i++) {
////                    cin>>groupMember;
////                    memberList.push_back({groupMember, "groupMember", 2, userid});
////                }
////
////                chat.createGroup(groupId, groupName, url, memberList);
////
////            } else if (type == 8) {
////                string message, fullName, packetId;
////
////                time_t curtime = time(NULL);
////                //cout<<"curtime before casting: "<<curtime<<endl;
////                long long myTime = (long long) curtime;
////                //cout<<"cur time after casting: "<<myTime<<endl;
////
////                packetId = status.getPacketId();
////                //cout<<"packet ID from editGroupChat: "<<packetId<<endl;
////                cin >> fullName>>message;
////                chat.editGroupChat(packetId, groupId, 2, message, myTime);
////            } else if (type == 9) {
////    //            chat.getGroupInformation(groupId);
////    //            chat.getGroupMembers(groupId);
////                string message, packetId;
////                cin>>message;
////                packetId = Chat::generatePacketId();
////                chat.sendGroupChat(packetId, groupId, 2, message, 0);
////            } else if (type == 10) {
////                int groupMember;
////                vector<MemberDTO> memberList;
////                for (int i = 0; i < 3; i++) {
////                    cin>>groupMember;
////                    memberList.push_back({groupMember, "groupMember", 3, userid});
////                }
////                chat.changeGroupMemberStatus(groupId, memberList);
////                chat.getGroupInformationWithMembers(groupId);
////            } else if (type == 11) {
////                chat.requestForOffline(0, 0);
////            } else if (type == 13) {
////                int friendId;
////                string message;
////                cin >> friendId>>message;
////                string packetId = Chat::generatePacketId();
////                chat.editFriendChat(packetId, friendId, 2, 0, message, 0, true);
////            } else if (type == 14) {
////                vector<MemberDTO> memberList;
////                memberList.push_back({5, "groupMember", 3, userid});
////                chat.addGroupMembers(groupId, memberList);
////            } 
////            else if(type ==17){
////                chat.leaveGroup(groupId);
////            }
////            else if(type == 18){
////                UserIdentity friendId;
////                cin >> friendId;
////                string packetId = Chat::generatePacketId();
////                chat.requestFriendChatHistory(friendId, packetId, 1, 10);
////            }
////            else if(type == 19){
////                string packetId = Chat::generatePacketId();
////                long long groupId;
////                cin >> groupId;
////                chat.requestGroupChatHistory(groupId, packetId, 1, 10);
////            }
//
//            menu();
//            type = sc.nextInt();
//        }
//        }
//        userId = sc.nextLong();
//
//        Chat chat = new Chat(userId, "noman", "192.168.1.251", 1200, "38.127.68.60", 1500, 1, "abcd", 1);
//        //Chat chat = new Chat(userId, "dipal", "38.127.68.54", 1200, "38.127.68.52", 1500, 2);
//        ChatEventHandler eventHandler = new ChatEventHandler();
//        chat.registerEventHandler(eventHandler);
//        System.out.println(chat.version());
//
//        friendId = sc.nextLong();
//        chat.registerFriendChat(friendId, "192.168.1.251", 1500, 1, "", 3, 2, 2);
//        
//        //chat.sendFriendChat("abc", friendId, 0, 0, message, flag2, true)
//
        while (true) {
            try {
                Thread.sleep(20000);
            } catch (InterruptedException ex) {
                //Logger.getLogger(Chat.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
    }
}
