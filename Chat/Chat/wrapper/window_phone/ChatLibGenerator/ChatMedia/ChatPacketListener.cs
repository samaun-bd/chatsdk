using ChatWrapper;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace ChatLibGenerator.ChatMedia
{
    class ChatPacketListener : IMListener
    {

        public void onEventHandlerAttached() /****** discard *******/
        {
        }

        public void onEventHandlerDetached()  /****** discard *******/
        {

        }




        public void onDeactivateUserAccountStatus(string packetId)
        {
        }

        public void onFriendUnregistered(Int64 userId, Int64 friendId, int onlineStatus, int onlineMood, bool fromAnonymousUser, int profileType)
        {
        }

        public void onFriendChatRegisterSuccess(Int64 userId, Int64 friendId, Int64 serverDate, string packetId, bool fromAnonymousUser)
        {
        }

        public void onFriendChatRegisterFailure(Int64 userId, Int64 friendId, string packetId, bool fromAnonymousUser)  /****** discard *******/
        {
        }

        public void onFriendRegistrationExpired(Int64 userId, Int64 friendId, bool fromAnonymousUser)  /****** discard *******/
        {
        }

        public void onFriendChatTyping(Int64 userId, Int64 friendid, bool fromAnonymousUser)
        {
        }

        public void onFriendChatReceived(Int64 senderId, Int64 receiverId, string packetId, int messageType, int timeout, string message, Int64 messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser)
        {
        }

        public void onFriendChatEdited(Int64 senderId, Int64 receiverId, string packetId, int messageType, int timeout, string message, Int64 messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser)
        {
        }

        public void onFriendChatDelivered(Int64 userId, Int64 friendid, string packetId, bool fromAnonymousUser, bool isEdited, bool fromOnline)
        {
        }

        public void onFriendChatSent(Int64 userId, Int64 friendid, string packetId, bool fromAnonymousUser)
        {
        }

        public void onFriendChatSeen(Int64 userId, Int64 friendid, ManagedSeenPacketDTO[] seenPacketList, bool fromAnonymousUser)
        {
        }

        public void onFriendChatSeenConfirmed(Int64 userId, Int64 friendid, ManagedSeenPacketDTO[] seenPacketList, bool fromAnonymousUser)
        {
        }

        public void onFriendChatFailedToSend(Int64 userId, Int64 friendId, string packetId, bool fromAnonymousUser) // update message to failed
        {
        }

        public void onFriendChatDeleted(Int64 senderId, Int64 friendid, string[] packetId, bool fromAnonymousUser)
        {
        }

        public void onFriendChatDeleteRequestStatus(Int64 userId, Int64 friendid, string packetId, string[] packetIds, bool fromAnonymousUser, bool status)
        {
        }

        public void onFriendChatIdle(Int64 friendid, bool fromAnonymousUser) /****** discard *******/
        { }

        public void onBlocked(Int64 blockerId, Int64 blockedId, Int64 blockUnblockDate, bool addToBlock) /************ need to change **********/
        {
        }

        public void onUnblocked(Int64 blockerId, Int64 blockedId, Int64 blockUnblockDate)/************ need to change **********/
        {
        }

        public void onBlockUnblockRequestStatus(Int64 userId, Int64 friendid, string packetId, Int64 blockUnblockDate, bool status, bool fromBlockRequest) /************ need to change **********/
        {
        }

        public void onFriendHistoryMessageReceived(Int64 userId, Int64 friendId, ManagedMessageDTO[] friendHistoryMessageList, int direction)
        {
        }

        public void onFriendMessagesStatusReceived(Int64 userId, Int64 friendId, ManagedFriendMessageStatusDTO[] messageList)
        {
        }

        public void onFriendHistoryCompleted(Int64 userId, Int64 friendId, int direction) //**** history fetched completed *******/
        {
        }

        public void onFriendHistoryMessageRequestStatus(Int64 userId, Int64 friendId, string packetId, bool status) /********* history confirmation **** discard ******/
        { }

        public void shouldCheckFriendPresence(Int64 userId, Int64 friendId, bool fromAnonymousUser, int profileType) // request for presence
        {
        }

        public void shouldCheckServerAddressForFriend(Int64 userId, Int64 friendId, bool fromAnonymousUser) // request for ip & port
        {
        }

        public void onFriendChatConversationListReceived(Int64 userId, ManagedMessageDTO[] conversationList)
        {
        }





        public void onChatConversationListRequestStatus(Int64 userId, Int64 friendOrGroupId, string packetId, bool status)
        {
        }

        public void onChatConversationListCompleted(Int64 userId)
        {
        }

        public void onConversationListDeleteRequestStatus(Int64 userId, string packetId, bool status)
        {
        }

        public void onConversationListMarkAsSeenRequestStatus(Int64 userId, string packetId, bool status)
        {
        }



        public void onGroupChatConversationListReceived(ManagedMessageDTO[] conversationList)
        {
        }

        public void onGroupChatRegisterSuccess(Int64 groupId, Int64 serverDate, string packetId)
        {
        }

        public void onGroupChatRegisterFailure(Int64 groupId, string packetId)  /****** discard *******/
        {
        }

        public void onGroupRegistrationExpired(Int64 groupId, Int64 lastActivityTime)  /****** discard *******/
        { }

        public void onGroupNameChanged(string packetId, Int64 friendid, Int64 groupid, string groupName) // need packet ID // locally generate
        {
        }

        public void onGroupUrlChanged(string packetId, Int64 friendid, Int64 groupid, string groupUrl)  // need packet ID // locally generate
        {
        }

        public void onGroupNameChangeRequestStatus(Int64 groupId, string packetId, bool status, string groupName)
        {
        }

        public void onGroupUrlChangeRequestStatus(Int64 groupId, string packetId, bool status, string groupUrl)
        {
        }

        public void onGroupMemberAdded(Int64 friendid, Int64 groupid, ManagedMemberDTO[] memberList, string packetId)  // need packet ID // locally generate
        {
        }

        public void onGroupMemberAddRequestStatus(Int64 groupId, string packetId, bool status, ManagedMemberDTO[] memberList) /******sentInfo.GroupId, sentInfo.MemberListToAddOrUpdate, true, 0, packetId ***/
        {
        }

        public void onGroupMemberRemovedOrLeft(Int64 friendid, Int64 groupid, Int64[] memberList, string packetId)  // need packet ID // locally generate
        {
        }

        public void onGroupMemberRemoveLeaveRequestStatus(Int64 groupId, string packetId, bool status, ManagedMemberDTO[] memberList) /******sentInfo.GroupId, sentInfo.MemberListToRemove, sentInfo.UserIdentity, 0, packetId ***/
        {
        }

        public void onGroupMemberStatusChanged(Int64 senderid, Int64 groupid, ManagedMemberDTO[] memberList, string packetId)  // need packet ID // locally generate
        {
        }

        public void onGroupMemberStatusChangeRequestStatus(Int64 groupId, string packetId, bool status, ManagedMemberDTO[] memberList) /******sentInfo.GroupId, sentInfo.MemberListToAddOrUpdate, sentInfo.UserIdentity, 0, packetId ***/
        {
        }

        public void onGroupChatTyping(Int64 friendid, Int64 groupid)
        {
        }

        public void onGroupChatReceived(Int64 senderId, Int64 groupid, string packetId, int messageType, string message, Int64 messageDate, bool fromOnline)
        {
        }

        public void onGroupChatEdited(Int64 senderId, Int64 groupId, string packetId, int messageType, string message, Int64 messageDate, bool fromOnline)
        {
        }

        public void onGroupChatDelivered(Int64 friendid, Int64 groupid, string packetId)
        {
        }

        public void onGroupChatSent(Int64 groupId, string packetId, bool isEdited)
        {
        }

        public void onGroupChatSeen(Int64 groupid, string[] packetIds)
        {
        }

        public void onGroupChatMessageSeenListReceived(Int64 groupid, string packetId, ManagedMemberDTO[] memberList)
        {
        }

        public void onGroupChatMessageSeenListRequestStatus(Int64 groupId, string requestPacketId, string messagePacketId, bool status)
        { }

        public void onGroupChatDeleted(Int64 friendid, Int64 groupid, string[] packetIdList)
        {
        }

        public void onGroupChatDeleteRequestStatus(Int64 groupid, string packetId, string[] packetIds, bool status) /******confirmation ***/
        {
        }

        public void onGroupChatIdle(Int64 friendid, Int64 groupid) /*********discard ***/
        { }

        public void onGroupChatFailedToSend(Int64 groupId, string packetId) // need for activity failed
        {
        }

        public void shouldCheckServerAddressForGroup(Int64 groupId)  // 134
        {
        }

        public void onGroupInformationActivityReceived(ManagedGroupActivityDTO[] groupActivityList)// when this packet is received? is really needed? nothing done from client side?
        {
        }

        public void onGroupInformationActivityFromHistoryMessageReceived(Int64 groupId, ManagedGroupActivityDTO[] groupActivityList, int direction)
        {
        }

        public void onMyGroupListReceived(ManagedGroupDTO[] myGroupList)
        {
        }

        public void onGroupCreated(Int64 groupId, string packetId, bool status)
        {
        }

        public void onGroupHistoryMessageReceived(Int64 groupId, ManagedMessageDTO[] groupHistoryMessageList, int direction)
        {
        }

        public void onGroupHistoryMessageRequestStatus(Int64 groupId, string packetId, bool status) // nothing to do
        {
        }

        public void onGroupHistoryCompleted(Int64 groupId, int direction) // end of history
        {
        }

        public void onGroupInformationWithMembersReceived(Int64 groupId, string groupName, string groupUrl, ManagedMemberDTO[] memberList)
        {
        }

        public void onGroupInformationWithMembersRequestStatus(Int64 groupId, string packetId, bool status) // noting to do
        {
        }

        public void onGroupChatSeenRequestStatus(Int64 groupid, string[] packetIds, bool status)
        {
        }







        //Public Room Chat
        public void onPublicRoomChatRegisterSuccess(string roomId, string packetId, int numberOfMembers, Int64 anonymousId)
        {
        }

        public void onPublicRoomChatRegisterFailure(string roomId, string packetId)
        {
        }

        public void onPublicRoomChatRegistrationExpired(string roomId)
        {
        }

        public void onPublicRoomChatDelivered(string roomId, string packetId, bool isEdited)
        {
        }

        public void onPublicRoomChatFailedToSend(string roomId, string packetId)
        {
        }

        public void onPublicRoomChatReceived(string roomId, Int64 friendId, string packetId, int messageType, string message, Int64 messageDate, string memberFullName, string memberProfileUrl)
        {
        }

        public void onPublicRoomListReceived(ManagedRoomDTO[] roomList, bool roomListFromHistory)
        {
        }

        public void onPublicRoomInformationReceived(string roomId, string roomName, string roomUrl, string packetId)
        {
        }

        public void onPublicRoomChatEdited(string roomId, Int64 friendId, string packetId, int messageType, string message, Int64 messageDate, string memberFullName, string memberProfileUrl)
        {
        }

        public void onPublicRoomChatTyping(string roomId, Int64 friendId, string memberName)
        {
        }

        public void onPublicChatMemberListReceived(string roomId, string pagingState, ManagedPublicChatMemberDTO[] publicChatMemberList)
        {
        }

        public void onPublicChatMemberCountChanged(string roomId, int numberOfMembers)
        {
        }

        public void shouldCheckServerAddressForRoom(string roomId)
        {
        }

        public void onPublicRoomChatHistoryReceived(string roomId, ManagedMessageDTO[] publicChatMessageList)
        {
        }

        public void onPublicRoomChatHistoryCompleted(string roomId)
        {
        }

        public void onPublicRoomListRequestStatus(string packetId, bool requestStatus)
        {
        }

        public void onPublicRoomInformationRequestFailed(string roomId, string packetId)
        {
        }

        public void onPublicRoomChatHistoryRequestStatus(string roomId, string packetId, bool requestStatus)
        {
        }

        public void onPublicRoomMemberListRequestStatus(string roomId, string packetId, bool requestStatus)
        {
        }

        public void onPublicChatMessageDeleted(string roomId, string[] deletedPacketIds)
        {
        }

        public void onPublicChatMessageLiked(string roomId, string packetId, Int64 recipientId)
        {
        }

        public void onPublicChatMessageUnliked(string roomId, string packetId, Int64 messageSenderId)
        {
        }

        public void onPublicChatMessageReported(string roomId, string packetId, Int64 recipientId) // discard
        {
        }

        public void onPublicChatCategoryListReceived(string[] publicChatCategoryList)
        {
        }

        public void onPublicChatLikeMemberListReceived(string roomId, string packetId, ManagedPublicChatMemberDTO[] publicChatMemberList)
        {
        }

        public void onPublicChatDeleteRequestStatus(string roomId, string packetId, bool status)
        {
        }

        public void onPublicChatLikeUnlikeRequestStatus(string roomId, string requestPacketId, string messagePacketId, bool status, bool fromLikeRequest)
        {
        }

        public void onPublicChatReportRequestStatus(string roomId, string requestPacketId, string messagePacketId, bool status)
        {
        }

        public void onPublicChatLikeMemberListRequestStatus(string roomId, string packetId, bool status)
        { }

        public void onPublicChatCategoryListRequestStatus(string packetId, bool status)
        {

        }







        public void shouldCheckOfflineServerAddress()
        {
        }

        public void onServerTimeSynced(Int64 timeDifference)  /********discard ****/
        {
        }

        public void shouldUpdateUserPassword()
        {
        }

        public void onSDKError(int errorCode, string packetId) /********discard ****/
        {
        }

        public void onNetworkDataCounted(ManagedDataCounter dataCounter)
        {
        }




        //Live stream chat
        public void onLiveStreamChatRegisterSuccess(Int64 publisherId, string packetId)
        {
        }
        public void onLiveStreamChatRegisterFailure(Int64 publisherId, string packetId)
        {
        }
        public void onLiveStreamChatRegistrationExpired(Int64 publisherId)
        {
        }
        public void onLiveStreamChatDelivered(Int64 publisherId, string packetId)
        {
        }
        public void onLiveStreamChatFailedToSend(Int64 publisherId, string packetId)
        {
        }
        public void onLiveStreamChatReceived(Int64 publisherId, Int64 senderId, string packetId, int messageType, string message, Int64 messageDate, string senderFullName)
        {
        }
        public void onLiveStreamChatTyping(Int64 publisherId, Int64 senderId)
        {
        }
        public void shouldCheckServerAddressForLiveStreamChat(Int64 publisherId)
        {
        }

        public void onLiveStreamChatBlockUserRequestStatus(Int64 blockedUserId, String packetId)
        {
        }
        public void onLiveStreamChatUserBlocked(Int64 publisherId, Int64 blockedUserId)
        {
        }





        // media file transfer
        public void onFriendFileManifestUploaded(Int64 userId, Int64 friendId, string packetId, string cloudManifestUrl, int messageType, int timeout, string caption, int widthOrFileSize, int heightOrDuration)
        {
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                System.Diagnostics.Debug.WriteLine("file uploading completed ::: " + packetId);
            });
        }
        public void onFriendIncomingChatMedia(Int64 userId, Int64 friendId, string fileName, string packetId, int messageType, int timeout, Int64 messageDate, bool isSecretVisible, string caption, int widthOrSize, int heightOrDuration)
        { }
        public void onFriendChatMediaTransferProgress(Int64 userId, Int64 friendId, string fileName, double transferPercentage, bool isUpload, string packetId)
        {
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                System.Diagnostics.Debug.WriteLine("file " + (isUpload ? "uploading ::: " : "downloading ::: ") + packetId + " ----- name ::: " + fileName + " <===> percentage ::: " + transferPercentage);
            });
        }
        public void onFriendChatMediaTransferFailed(Int64 userId, Int64 friendId, string fileName, string packetId, bool isUpload, bool isChunkedTransfer)
        {
            System.Diagnostics.Debug.WriteLine("file " + (isUpload ? "uploading failed ::: " : "downloading failed ::: ") + packetId);
        }
        public void onFriendChatMediaTransferCanceled(Int64 userId, Int64 friendId, Int64 canceledBy, string fileName, string packetId, bool isUpload, bool isChunkedTransfer)
        {
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                System.Diagnostics.Debug.WriteLine("file " + (isUpload ? "uploading ::: " : "downloading ::: ") + packetId + " ----- name ::: " + fileName + " canceled");
            });
        }
        public void onFriendChatMediaDownloadCompleted(Int64 userId, Int64 friendId, string fileNameWithPath, string packetId, int mediaType, int timeout)
        {
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                System.Diagnostics.Debug.WriteLine("file downloading completed ::: " + packetId);
            });
        }

        public void onGroupFileManifestUploaded(Int64 groupId, string packetId, string cloudManifestUrl, int messageType, string caption, int widthOrFileSize, int heightOrDuration)
        { }
        public void onGroupIncomingChatMedia(Int64 friendId, Int64 groupId, string fileName, string packetId, int messageType, Int64 messageDate, string caption, int widthOrSize, int heightOrDuration)
        { }
        public void onGroupChatMediaTransferProgress(Int64 friendId, Int64 groupId, string fileName, double transferPercentage, bool isUpload, string packetId)
        { }
        public void onGroupChatMediaTransferFailed(Int64 friendId, Int64 groupId, string fileName, string packetId, bool isUpload, bool isChunkedTransfer)
        { }
        public void onGroupChatMediaTransferCanceled(Int64 friendId, Int64 groupId, Int64 canceledBy, string fileName, string packetId, bool isUpload, bool isChunkedTransfer)
        { }
        public void onGroupChatMediaDownloadCompleted(Int64 friendId, Int64 groupId, string fileNameWithPath, string packetId, int mediaType)
        { }


        public void onChatMediaTransferDirectoryError()
        { }
		public void shouldUpdateAppSessionID()
        { }

        public void onActivaeOrDeactivateUserAccountStatus(long userId, string packetId, bool isAccountActivate, bool status)
        {
        }

        public void onGetUserInfoFailure(long userId, long friendId, string packetId)
        {
        }

        public void onGetUserInfoReceived(long userId, long friendId, string packetId, string friendName, long friendRingId, string friendProfileImageUrl, int friendProfileType)
        {
        }
    }
}
