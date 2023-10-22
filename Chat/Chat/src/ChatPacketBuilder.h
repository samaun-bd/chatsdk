/* 
 * File:   ChatPacketBuilder.h
 * Author: dipal
 *
 * Created on September 2, 2015, 4:44 PM
 */

#ifndef CHATPACKETBUILDER_H
#define CHATPACKETBUILDER_H

#include <memory>
#include "ByteArray.h"
#include "Types.h"
#include "PacketTemplate.h"
#include "ChatParser.h"
#include "PacketDTO.h"
#include "SeenPacketDTO.h"


namespace imsdk {

    class BuiltPacket {
    public:
        std::shared_ptr< ByteArray> byteArray;
        std::shared_ptr< PacketDTO> packet;
    };

    class ChatPacketBuilder {
    public:
        ChatPacketBuilder();
        virtual ~ChatPacketBuilder();

        BuiltPacket makeActivateOrDeactivateUserPacket(UserIdentity userId, std::string &packetID, bool isActivate, int platform);
        BuiltPacket makeGetUserInfoPacket(UserIdentity userId, UserIdentity friendId, std::string &packetID, int platform);
		BuiltPacket makeFriendRegister(UserIdentity userId, UserIdentity friendId, std::string &packetID, int platform, int appversion, int appType, UserIdentity pageOwnerId);
        BuiltPacket makeFriendUnregister(UserIdentity userId, UserIdentity friendId, std::string &packetID, int onlineStatus, int onlineMood);
		BuiltPacket makefriendregisterconfirmation(UserIdentity userId, UserIdentity friendId, std::string &packetID, int chatBindingPort, long long serverDate);
        BuiltPacket makeFriendChatIdel(UserIdentity userId, UserIdentity friendId, int platform);
        BuiltPacket makeFriendChatMessageTyping(UserIdentity userId, UserIdentity friendId, int platform, std::string &packetID);
        BuiltPacket makeFriendChatMessage(UserIdentity userId, UserIdentity friendId, std::string &packetID, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform, int appversion, int appType, UserIdentity pageOwnerId);
        BuiltPacket makeFriendCallBusyMessage(UserIdentity userId, UserIdentity friendId, std::string &packetID, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform);
		BuiltPacket makeFriendChatMessageEdit(UserIdentity userId, UserIdentity friendId, std::string &packetID, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform, int appversion, int appType, UserIdentity pageOwnerId);
		BuiltPacket makeGenerateEncryptedPacketInformation(UserIdentity userID, UserIdentity friendID, std::string &packetID, int type, int informationType, std::string &information);
		BuiltPacket makeGeneralEncryptedPacketConfirmation(UserIdentity userID, UserIdentity friendID, std::string &packetID, int type, int informationType);
		BuiltPacket makeFriendChatMessageBroken(UserIdentity userId, UserIdentity friendId, std::string &packetID, int totalNumberOfPackets, int sequenceNumber, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform, int appversion, int appType, UserIdentity pageOwnerId);
		BuiltPacket makeFriendChatMessageBrokenEdit(UserIdentity userId, UserIdentity friendId, std::string &packetID, int totalNumberOfPackets, int sequenceNumber, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform, int appversion, int appType, UserIdentity pageOwnerId);
        BuiltPacket makeFriendChatMessageAnonymous(UserIdentity userId, UserIdentity friendId, std::string &packetID, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform, long long originalUserId);
        BuiltPacket makeFriendChatMessageEditAnonymous(UserIdentity userId, UserIdentity friendId, std::string &packetID, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform, long long originalUserId);
        BuiltPacket makeFriendChatMessageBrokenAnonymous(UserIdentity userId, UserIdentity friendId, std::string &packetID, int totalNumberOfPackets, int sequenceNumber, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform, long long originalUserId);
        BuiltPacket makeFriendChatMessageBrokenEditAnonymous(UserIdentity userId, UserIdentity friendId, std::string &packetID, int totalNumberOfPackets, int sequenceNumber, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform, long long originalUserId);
        BuiltPacket makeFriendChatMultipleMessage(UserIdentity userId, UserIdentity friendId, std::string &packetID, std::vector<std::shared_ptr< PacketDTO>> &messageList);
        BuiltPacket makeUserPasswordUpdateRequest(UserIdentity userId, std::string &packetID);
        BuiltPacket makeFriendChatMessageDelivered(UserIdentity userId, UserIdentity friendId, std::string &packetID);
        BuiltPacket makeFriendChatMessageSent(UserIdentity userId, UserIdentity friendId, std::string &packetID);
        BuiltPacket makeFriendChatMessageSeen(UserIdentity userId, UserIdentity friendId, std::string &packetID, std::vector<SeenPacketDTO> &seenPacketDTOList);
        BuiltPacket makeFriendChatMessageSeenConfirmation(UserIdentity userId, UserIdentity friendId, std::string &packetID);
        BuiltPacket makeFriendChatMultipleMessageDelete(UserIdentity userId, UserIdentity friendId, std::string &packetID, std::vector<std::string> &packetIds, int platform, int deleteType);
        BuiltPacket makeFriendChatMessageDeleteConfirmation(UserIdentity userId, UserIdentity friendId, std::string &packetID);
        BuiltPacket makeFriendBrokenPacket(UserIdentity userId, UserIdentity friendId, std::string &packetID, int totalNumberOfPackets, int sequenceNumber, std::shared_ptr< ByteArray> &dataBytes);
        BuiltPacket makeFriendBrokenPacketConfirmation(UserIdentity userId, UserIdentity friendId, std::string &packetID, int sequenceNumber);
        BuiltPacket makeFriendBlock(UserIdentity userId, UserIdentity friendId, std::string &packetID, long long blockUnblockDate, bool isAddToBlock);
        BuiltPacket makeFriendUnblock(UserIdentity userId, UserIdentity friendId, std::string &packetID, long long blockUnblockDate);
        BuiltPacket makeFriendBlockUnblockConfirmation(UserIdentity userId, UserIdentity friendId, std::string &packetID);
        BuiltPacket makeFriendFileStreamRequest(UserIdentity userId, UserIdentity friendId, std::string &packetId, FileIdentity fileId);
        BuiltPacket makeFriendFileStreamRequestConfirmation(UserIdentity userId, UserIdentity friendId, std::string &packetId, FileIdentity fileId);
        BuiltPacket makeFriendFileStreamSend(UserIdentity userId, UserIdentity friendId, std::string &packetId, FileIdentity fileId);
        BuiltPacket makeFriendFileStreamSendConfirmation(UserIdentity userId, UserIdentity friendId, std::string &packetId, FileIdentity fileId, int fileTrasferPort);
        BuiltPacket makeGroupRegister(UserIdentity userId, long long groupId, std::string &packetID, int platform, int appversion);
        BuiltPacket makeGroupUnregister(UserIdentity userId, long long groupId, std::string &packetID, int onlineStatus, int onlineMood);
        BuiltPacket makeGroupRegisterConfirmation(long long groupId, std::string &packetID, int chatBindingPort, long long serverDate);
        BuiltPacket makeGroupInformation(UserIdentity userId, long long groupId, std::string &packetID, int activityType, std::string &groupNameOrUrl);
        BuiltPacket makeGroupInformationConfirmation(UserIdentity userId, long long groupId, std::string &packetID);
        BuiltPacket makeGroupMemberAdd(UserIdentity userId, long long groupId, std::string &packetID, std::vector<MemberDTO> &memberList);
        BuiltPacket makeGroupMemberAddConfirmation(UserIdentity userId, long long groupId, std::string &packetID);
        BuiltPacket makeGroupMemberRemoveLeave(UserIdentity userId, long long groupId, std::string &packetID, std::vector<MemberDTO> &memberList, int leaveType = 0);
        BuiltPacket makeGroupMemberRemoveLeaveConfirmation(UserIdentity userId, long long groupId, std::string &packetID);
        BuiltPacket makeGroupMemberTypeChange(UserIdentity userId, long long groupId, std::string &packetID, std::vector<MemberDTO> &memberList);
        BuiltPacket makeGroupMemberTypeChangeConfirmation(UserIdentity userId, long long groupId, std::string &packetID);
        BuiltPacket makeGroupChatIdel(UserIdentity userId, long long groupId, int platform);
        BuiltPacket makeGroupChatMessageTyping(UserIdentity userId, long long groupId, int platform, std::string &packetID);
        BuiltPacket makeGroupChatMessage(UserIdentity userId, long long groupId, std::string &packetID, int messageType, std::string &message, long long messageDate);
        BuiltPacket makeGroupChatMessageEdit(UserIdentity userId, long long groupId, std::string &packetID, int messageType, std::string &message, long long messageDate);
        BuiltPacket makeGroupChatMessageBroken(UserIdentity userId, long long groupId, std::string &packetID, int totalNumberOfPackets, int sequenceNumber, int messageType, std::string &message, long long messageDate);
        BuiltPacket makeGroupChatMessageBrokenEdit(UserIdentity userId, long long groupId, std::string &packetID, int totalNumberOfPackets, int sequenceNumber, int messageType, std::string &message, long long messageDate);
        BuiltPacket makeGroupChatMultipleMessage();
        BuiltPacket makeGroupChatMessageDelivered(UserIdentity userId, UserIdentity friendId, long long groupId, std::string &packetID);
        BuiltPacket makeGroupChatMessageSent(long long groupId, std::string &packetID);
        BuiltPacket makeGroupChatMessageSeen(UserIdentity userId, long long groupId, std::string &packetID, std::vector<std::string> &packetIds);
        BuiltPacket makeGroupChatMessageSeenConfirmation(UserIdentity userId, long long groupId, std::string &packetID);
        BuiltPacket makeGroupChatGetMessageSeenListRequest(UserIdentity userId, long long groupId, std::string &newPacketID, std::string actualPacketId, int platform);
        BuiltPacket makeGroupChatMessageSeenListConfirmation(UserIdentity userId, long long groupId, std::string &packetID);
        BuiltPacket makeGroupChatMultipleMessageDelete(UserIdentity userId, long long groupId,  std::string &packetID, std::vector<std::string> &packetIds);
        BuiltPacket makeGroupChatMessageDeleteConfirmation(UserIdentity userId, long long groupId, std::string &packetID);
        BuiltPacket makeGroupBrokenPacketConfirmation(UserIdentity userId, long long groupId, std::string &packetID, int sequenceNumber);
        BuiltPacket makeGroupFileStreamRequestConfirmation();
        BuiltPacket makeGroupFileStreamSend();
        BuiltPacket makeGroupFileStreamSendConfirmation();
        BuiltPacket makeOfflineFriendInformation(UserIdentity userId, UserIdentity friendId, std::string &packetID, std::string &fullName, int friendPlatform, int onlineStatus, int friendApptType, std::string &friendDeviceToken, int onlineMood, int iosVoipPush, int selfPlatform, int profileType, int friendProfileType);
        BuiltPacket makeOfflineFriendInformationConfirmation(UserIdentity friendId, std::string &packetID);
		BuiltPacket makeOfflineGetRequest(UserIdentity userId, std::string &packetID, long long groupUpdateDate, long long blockUpdateDate, int appVersion, int platform, int appType, std::set<UserIdentity> &pageIdList);
        BuiltPacket makeOfflineGetRequestConfirmation(std::string &packetID, long long serverDate);
		BuiltPacket makeOfflineFriendUnreadMessage(std::string &packetID, UserIdentity userID, std::vector<std::shared_ptr< PacketDTO> > &messageList);
        BuiltPacket makeOfflineFriendUnreadMessageConfirmation(UserIdentity userId, std::string &packetID, std::vector<std::string> &packeIds);
        BuiltPacket makeOfflineFriendHistoryMessageRequest(UserIdentity userId, UserIdentity friendId, std::string &packetID, int upDownStatus, int limit, int platform, int appType, int appVersion, UserIdentity pageOwnerId);
        BuiltPacket makeOfflineFriendHistoryMessage(UserIdentity friendId, std::string &packetID, std::vector<std::shared_ptr< PacketDTO> > &messageList);
        BuiltPacket makeOfflineFriendHistoryMessageConfirmation(UserIdentity friendId, std::string &packetID);
        BuiltPacket makeOfflineGetFriendMessgaeStatus(UserIdentity userId, UserIdentity friendId, std::string &packetID, std::vector<std::string> &packetIds);
        BuiltPacket makeOfflineGetFriendMessgaeStatusConfirmation(UserIdentity friendId, std::string &packetID, std::vector<FriendMessageStatusDTO> &friendMessageStatusList);
        BuiltPacket makeOfflineMyGroupList(std::string &packetID, std::vector<GroupDTO> &groupDTOList);
        BuiltPacket makeOfflineGroupUnreadMessageConfirmation(UserIdentity userId, std::string &packetID, std::vector<std::string> &packetIds);
        BuiltPacket makeOfflineCreateGroup(UserIdentity userId, long long groupId, std::string &packetID, std::string &groupName, std::string &groupUrl, std::vector<MemberDTO> &memberList);
        BuiltPacket makeOfflineCreateGroupConfirmation(long long groupId, std::string &packetID);
        BuiltPacket makeOfflineGroupHistoryMessageRequest(UserIdentity userId, long long groupId, std::string &packetID, int upDownStatus, int limit, int appVersion);
        BuiltPacket makeOfflineGroupHistoryMessage(long long groupId, std::string &packetID, std::vector<std::shared_ptr< PacketDTO>> &messageList);
        BuiltPacket makeOfflineGetInformationWithMembers(UserIdentity userId, long long groupId, std::string &packetID);
        BuiltPacket makeOfflineInformationWithMembers(long long groupId, std::string &packetID, std::string &groupName, std::string &groupUrl, std::vector<MemberDTO> &memberList);
        BuiltPacket makeOfflineGroupConfirmation(long long groupId, std::string &packetID);
        BuiltPacket makeOfflineBrokenHistoryPacket(std::string &packetID, int numberOfPackets, int sequenceNumber, std::shared_ptr< ByteArray> dataBytes);
        BuiltPacket makeOfflineBrokenPacket(std::string &packetID, int numberOfPackets, int sequenceNumber, std::shared_ptr< ByteArray> dataBytes);
        BuiltPacket makeOfflineBrokenPacketConfirmation(UserIdentity userId, std::string &packetID, int sequenceNumber);
        BuiltPacket makeRoomBrokenPacketConfirmation(UserIdentity userId, RoomIdentity &roomId, std::string &packetID, int sequenceNumebr);
        BuiltPacket makeOfflineGetConversationList(UserIdentity userId, std::string &packetID, int startIndex, int limit, int conversationType, long long friendOrGroupId, int platform, int appVersion);
        BuiltPacket makeOfflineDeleteConversationRequest(UserIdentity userId, std::string &packetId, std::vector<ConversationDTO> &conversationList, int platform);
        BuiltPacket makeOfflineMarkConversationSeenRequest(UserIdentity userId, std::string &packetId, std::vector<ConversationDTO> &conversationList, int platform);
        BuiltPacket makeOfflineGroupIPPortRequest(UserIdentity userId, GroupIdentity groupId, std::string &packetId, int platform, std::string &serverIp, int serverPort);

        BuiltPacket makePublicRoomRegisterPacket(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, std::string &roomName, std::string &roomUrl, int platform, UserIdentity ringId);
        BuiltPacket makePublicRoomUnregisterPacket(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, UserIdentity recepientId, UserIdentity ringId);
        BuiltPacket makePublicRoomChatIdelPacket(UserIdentity userId, RoomIdentity &roomId, int platform);
        BuiltPacket makePublicRoomChatTypingPacket(UserIdentity userId, RoomIdentity &roomId, std::string &memberName, int platform);
        BuiltPacket makePublicRoomChatMessagePacket(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, int messageType, std::string &message, long long messageDate, std::string &memberFullName, std::string &memberProfileUrl);
        BuiltPacket makePublicRoomChatMessageEditPacket(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, int messageType, std::string &message, long long messageDate, std::string &memberFullName, std::string &memberProfileUrl);
        BuiltPacket makePublicRoomChatMessageBrokenPacket(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, int totalNumberOfPackets, int sequenceNumber, int messageType, std::string &message, long long messageDate, std::string &memberFullName, std::string &memberProfileUrl);
        BuiltPacket makePublicRoomChatMessageBrokenEditPacket(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, int totalNumberOfPackets, int sequenceNumber, int messageType, std::string &message, long long messageDate, std::string &memberFullName, std::string &memberProfileUrl);
        BuiltPacket makePublicRoomChatMessageDeliveredPacket(UserIdentity userId, UserIdentity friendId, RoomIdentity &roomId, std::string &packetId);
        BuiltPacket makePublicRoomChatMessageSentPacket(RoomIdentity &roomId, std::string &packetId);
        BuiltPacket makePublicChatGetMemberList(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, std::string pagingState, int limit, int appVersion);
        BuiltPacket makePublicChatGetMemberListConfirmation(UserIdentity userId, RoomIdentity &roomId, std::string &packetId);
        BuiltPacket makePublicRoomChatMemberCountChange(RoomIdentity &roomId, std::string &packetId, int numberOfMembers);
        BuiltPacket makePublicRoomChatMemberCountChangeConfirmation(UserIdentity userId, RoomIdentity &roomId, std::string &packetId);
        
        BuiltPacket makePublicRoomChatDeleteMessagePacket(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, std::vector<std::string> packetIds);
        BuiltPacket makePublicRoomChatDeleteMessagePacketConfirmation(UserIdentity userId, RoomIdentity &roomId, std::string &packetId);
        BuiltPacket makePublicRoomChatLikeMessagePacket(UserIdentity userId, RoomIdentity &roomId, std::string &newPacketId, UserIdentity recipientId, std::string &actualPacletId);
        BuiltPacket makePublicRoomChatUnlikeMessagePacket(UserIdentity userId, RoomIdentity &roomId, std::string &newPacketId, UserIdentity recipientId, std::string &actualPacletId);
        BuiltPacket makePublicRoomChatLikeUnlikeConfirmation(UserIdentity userId, RoomIdentity &roomId, std::string &packetId);
        BuiltPacket makePublicRoomChatReportMessagePacket(UserIdentity userId, RoomIdentity &roomId, std::string &newPacketId, std::string &message, UserIdentity recipientId, std::string &actualPacletId);
        BuiltPacket makePublicRoomChatReportMessagePacketConfirmation(UserIdentity userId, RoomIdentity &roomId, std::string &packetId);
        
        BuiltPacket makeOfflinePublicRoomListRequest(UserIdentity userId, std::string &packetId, int startIndex, int limit, int platform);
        BuiltPacket makeOfflinePublicRoomListWithHistoryRequest(UserIdentity userId, std::string &packetId, int startIndex, int limit, int platform);
        BuiltPacket makeOfflinePublicRoomListSearchRequest(UserIdentity userId, std::string &packetId, int startIndex, int limit, std::string &searchName, std::string &country, std::string &category, int platform);
        BuiltPacket makeOfflinePublicRoomListRequestConfirmation(std::string &packetId);
        BuiltPacket makeOfflinePublicGetRoomIPPort(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, int platform);
        BuiltPacket makeOfflinePublicGetRoomIPPortConfirmation(RoomIdentity &roomId, std::string &packetId, std::string &serverIp, int serverPort);
        BuiltPacket makeOfflineRoomInformationRequest(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, int platform);
        BuiltPacket makeOfflineRoomGetHistoryPacket(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, int month, int year, int direction, int limit, int platform, int appVersion);
        BuiltPacket makeOfflineRoomGetHistoryConfirmationPacket(RoomIdentity &roomId, std::string &packetId);
              
        //Group file transfer
        BuiltPacket makeGroupFileIdelPacket(UserIdentity userId, GroupIdentity groupId, int platform);
        BuiltPacket makeGroupFileStreamRequest(UserIdentity userId, UserIdentity friendId, GroupIdentity groupId, std::string &packetId, FileIdentity fileId, bool accept, long long fileOffset);
        BuiltPacket makeGroupFileStreamRequestConfirmation(UserIdentity userId, UserIdentity friendId, GroupIdentity groupId, std::string &packetId, FileIdentity fileId, bool accept);
        BuiltPacket makeGroupFileSessionRequest(UserIdentity userId, GroupIdentity groupId, std::string &packetId, FileIdentity fileId);
        BuiltPacket makeGroupFileSessionRequestConfirmation(UserIdentity userId, GroupIdentity groupId, std::string &packetId, FileIdentity fileId, int fileTransferPort);
        BuiltPacket makeGroupFileIdel(UserIdentity userId, GroupIdentity groupId, int platform);        

        //Anonymous friend chat
        BuiltPacket makeAnonymousFriendChatRegisterPacket(UserIdentity userId, UserIdentity friendId, std::string &packetId, int platform);
		BuiltPacket makeAnonymousFriendChatRegisterConfirmationPacket(UserIdentity userId, UserIdentity friendId, std::string &packetId, int bindingPort, long long serverDate);
        BuiltPacket makeAnonymousFriendChatUnregisterPacket(UserIdentity userId, UserIdentity friendId, std::string &packetId, int onlineStatus, int onlineMood);
        BuiltPacket makeShadowIdInfoRequestPacket(UserIdentity userId, std::string &packetID, std::vector<UserIdentity> &shadowIdList, int platform);
        
        //Friend File Transfer
        BuiltPacket makeFriendFileIdelPacket(UserIdentity userId, UserIdentity friendId, int platform);
        BuiltPacket makeFriendFileStreamRequestPacket(UserIdentity userId, UserIdentity friendId, std::string &packetId, FileIdentity fileId, bool fileAcceptReject, long long fileOffset);
        BuiltPacket makeFriendFileStreamRequestConfirmationPacket(UserIdentity userId, UserIdentity friendId, std::string &packetId, FileIdentity fileId, bool fileAcceptReject);
        BuiltPacket makeFriendFileSessionRequestPacket(UserIdentity userId, UserIdentity friendId, std::string &packetId, FileIdentity fileId);
        
        BuiltPacket makeFriendGetChatMessagePacket(UserIdentity userId, UserIdentity friendId, std::string &packetId, int platform);
        BuiltPacket makeGroupGetChatMessagePacket(UserIdentity userId, GroupIdentity groupId, std::string &packetId, int platform);
        
        BuiltPacket makePublicChatLikeMemberListRequest(UserIdentity userId, RoomIdentity roomId, std::string &generatedPacketId, std::string &originalPacketId, UserIdentity lastLikerId, int limit, int appversion);
        BuiltPacket makeOfflinePublicChatCategoryListRequest(UserIdentity userId, std::string &packetId, std::string pagingState, int limit, int platform);
        
        //Live-stream-chat
        BuiltPacket makeLiveStreamChatRegisterPacket(UserIdentity userId, UserIdentity publisherId, std::string &packetId, int platform);
        BuiltPacket makeLiveStreamChatUnregisterPacket(UserIdentity userId, UserIdentity publisherId, std::string &packetId, int onlineStatus, int onlineMood);
        BuiltPacket makeLiveStreamChatRegisterConfirmationPacket(UserIdentity publisherId, std::string &packetId, int chatBindingPort, long long serverDate);
        BuiltPacket makeLiveStreamChatIdlePacket(UserIdentity userId, UserIdentity publisherId, int platform);
        BuiltPacket makeLiveStreamChatMessageTypingPacket(UserIdentity userId, UserIdentity publisherId, int platform);
        BuiltPacket makeLiveStreamChatMessagePacket(UserIdentity userId, UserIdentity publisherId, std::string &packetId, int messageType, std::string &message, long long serverDate, std::string &fullName);
        BuiltPacket makeLiveStreamChatMessageDeliveredPacket(UserIdentity userId, UserIdentity publisherId, std::string &packetId);
        BuiltPacket makeLiveStreamChatMessageSentPacket(UserIdentity publisherId, std::string &packetId);
        BuiltPacket makeLiveStreamChatBlockUserPacket(UserIdentity publisherId, UserIdentity blockedUserId, std::string &packetId);
        BuiltPacket makeLiveStreamChatBlockUserConfirmationPacket(UserIdentity publisherId, UserIdentity userId, std::string &packetId);

        BuiltPacket makeFriendInitChunkFileDownloadPacket(UserIdentity userId, UserIdentity friendId, std::string packetId, std::string fileDownloadId, int fileChunkCount, int fileChunkSize, long long fileSize, int fileDomainType, int secretTimeout, long long messageDate, bool isSecretVisible, std::string caption, int widthOrSize, int heightOrDuration);
        BuiltPacket makeFriendFileChunkUploadedPacket(UserIdentity userId, UserIdentity friendId, std::string packetId, bool isManifest, std::string &fileDownloadId, std::string &fileChunkDownloadKey);
        BuiltPacket makeFriendFileChunkConfirmationPacket(UserIdentity userId, UserIdentity friendId, std::string &packetId);
        BuiltPacket makeFriendChatMediaTransferCancelPacket(UserIdentity userId, UserIdentity friendId, std::string &packetId);

        BuiltPacket makeGroupInitChunkFileDownloadPacket(UserIdentity userId, GroupIdentity groupId, std::string packetId, std::string fileDownloadId, int fileChunkCount, int fileChunkSize, long long fileSize, int fileDomainType, long long messageDate, std::string caption, int widthOrSize, int heightOrDuration);
        BuiltPacket makeGroupFileChunkUploadedPacket(UserIdentity userId, GroupIdentity groupId, std::string packetId, bool isManifest, std::string &fileDownloadId, std::string &fileChunkDownloadKey);
        BuiltPacket makeGroupFileChunkConfirmationPacket(UserIdentity userId, GroupIdentity groupId, std::string &packetId);
        BuiltPacket makeGroupChatMediaTransferCancelPacket(UserIdentity userId, GroupIdentity groupId, std::string &packetId);

        BuiltPacket makeGetSyncConversationRequest(UserIdentity userId, std::string &packetId, long long lastSyncTime, int platform);
        BuiltPacket makeGetSyncConversationStatus(UserIdentity userId, std::string &packetId);
        BuiltPacket makeSyncFriendHistoryMessageRequest(UserIdentity userId, UserIdentity friendId, std::string &packetId, long long lastSyncTime, int platform, int appType, int appVersion, UserIdentity pageOwnerId, int limit, int direction);
        BuiltPacket makeSyncGroupHistoryMessageRequest(UserIdentity userId, GroupIdentity groupId, std::string &packetId, long long lastSyncTime, int appVersion, int platform, int limit, int direction);

        BuiltPacket makeGetMyGroupListPagingRequest(UserIdentity userId, std::string &packetId, std::string &pivotId, int limit, int direction, int platform);

        BuiltPacket makeAddNotice(UserIdentity userId, std::string &packetId, int messageType, long long disburseTime, long long expireTime, std::string &notice, std::vector<std::string> &isoCountryList);
        BuiltPacket makeAddNoticeConfirmation(UserIdentity userId, std::string &packetId);
    private:
        std::shared_ptr< ChatParser> parser{nullptr};
    };
}

#endif /* CHATPACKETBUILDER_H */

