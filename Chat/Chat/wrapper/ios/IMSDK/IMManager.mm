//
//  IMManager.m
//  ringID
//
//  Created by Sumon on 11/2/15.
//  Copyright © 2015 IPVision Canada Inc. All rights reserved.
//

#import "IMAdapter.h"
#import "IMManager.h"
#import "IMHandlerDelegate.h"

@implementation IMManager

+ (instancetype)sharedInstance
{
    static dispatch_once_t once;
    static id sharedInstance;
    dispatch_once(&once, ^{
        sharedInstance = [[IMManager alloc] init];
    });
    return sharedInstance;
}

- (instancetype)init
{
    self = [super init];
    if (self)
    {
//        self.chatHandler = [[[IMHandlerDelegate alloc] init] autorelease];
    }
    return self;
}

- (void)initiateChatWithDelegate:(id <IMReceivedMessageDelegate>)delegate
                      withUserId:(NSString *)userId
                    withUserName:(NSString *)userName
             withOfflineServerIP:(NSString *)offlineIpAddress
           withOfflineServerPort:(NSInteger)offlinePort
                withAuthServerIP:(NSString*)authIpAddress
              withAuthServerPort:(NSInteger)authPort
                  withDeviceType:(IMSDK_DeviceType)deviceType
                withAppSessionId:(NSString*)appSessionId
                  withAppVersion:(NSInteger)appVersion
              withTimeDifference:(long long)timeDifference
              withDirectoryPaths:(NSArray *)directoryPaths
               withBaseUploadUrl:(NSString*)baseUploadUrl
             withBaseDownloadUrl:(NSString*)baseDownloadUrl
                withAutoDownload:(BOOL)autoDownload
               withEncryptionKey:(NSString*)encryptionKey
                     withAppType:(NSInteger)appType
                  withPageIdList:(NSArray *)pageIdList
{
//    [self.chatHandler setDelegate:delegate];
    [[IMHandlerDelegate sharedInstance] setDelegate:delegate];
    
    [IMAdapter initiateChatWithUserId:userId withUserName:userName withOfflineServerIP:offlineIpAddress withOfflineServerPort:offlinePort withAuthServerIP:authIpAddress withAuthServerPort:authPort withDeviceType:deviceType withAppSessionId:appSessionId withAppVersion:appVersion withTimeDifference:timeDifference withDirectoryPaths:directoryPaths withBaseUploadUrl:baseUploadUrl withBaseDownloadUrl:baseDownloadUrl withAutoDownload:autoDownload withEncryptionKey:encryptionKey withAppType:appType withPageIdList:pageIdList];
}


-(IMApiStatus *)activateOrDeactivateUserAccountWithActivationSatus:(BOOL)isAccountActivate
{
    return [IMAdapter activateOrDeactivateUserAccountWithActivationSatus:isAccountActivate];
}

- (void)setNewOfflineServerWithIP:(NSString *)ipAddress withPort:(NSInteger)port
{
    [IMAdapter setNewOfflineServerWithIP:ipAddress withPort:port];
}

- (IMApiStatus *)sendRequestForOfflineMessageAndGroupInformationWithGroupUpdateTime:(long long)groupUpdateDate withBlockUnblockUpdateDate:(long long)blockUpdateDate;
{
    return [IMAdapter sendRequestForOfflineMessageAndGroupInformationWithGroupUpdateTime:groupUpdateDate withBlockUnblockUpdateDate:blockUpdateDate];
}

- (IMApiStatus *)sendRegisterRequstForFriendChatWithId:(NSString *)userId withUserName:(NSString *)userName withFriendId:(NSString *)friendId withFriendName:(NSString *)friendName withFriendUrl:(NSString *)friendUrl withChatServerIP:(NSString *)ipAddress withPort:(NSInteger)port withDeviceType:(IMSDK_DeviceType)deviceType withDeviceToken:(NSString *)deviceToken withAppType:(NSInteger)appType withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood withVoipPush:(NSInteger)voipPush withAuthRegisterTime:(long long)authRegisterTime withProfileType:(NSInteger)profileType;
{
    return [IMAdapter sendRegisterRequstForFriendChatWithId:userId withUserName:userName withFriendId:friendId withFriendName:friendName withFriendUrl:friendUrl withChatServerIP:ipAddress withPort:port withDeviceType:deviceType withDeviceToken:deviceToken withAppType:appType withOnlineStatus:status withMood:mood withVoipPush:voipPush withAuthRegisterTime:authRegisterTime withProfileType:profileType];
}

- (IMApiStatus *)updateFriendRegisterServerWithId:(NSString *)userId withFriendId:(NSString *)friendId withServerAddress:(NSString *)serverAddress withServerPort:(NSInteger)serverPort
{
    return [IMAdapter updateFriendRegisterServerWithId:userId withFriendId:friendId withServerAddress:serverAddress withServerPort:serverPort];
}

- (IMApiStatus *)updateFriendPresenceId:(NSString *)userId withFriendId:(NSString *)friendId withPresence:(IMSDK_Presence)presence withMood:(IMSDK_MoodType)mood
{
    return [IMAdapter updateFriendPresenceId:userId withFriendId:friendId withPresence:presence withMood:mood];
}

- (IMApiStatus *)dontSendPendingMessagesWithId:(NSString *)userId withFriendId:(NSString *)friendId
{
    return [IMAdapter dontSendPendingMessagesWithId:userId withFriendId:friendId];
}

- (IMApiStatus *)sendFriendCallBusyMessageWithPacketId:(NSString *)packetId
                                            withUserId:(NSString *)userId
                                              withFriendId:(NSString *)friendId
                                           withMessage:(NSString *)message
                                       withMessageDate:(long long)date
{
    return [IMAdapter sendFriendCallBusyMessageWithPacketId:packetId withUserId:userId withFriendId:friendId withMessage:message withMessageDate:date];
}

- (IMApiStatus *)sendFriendCallLogMessageWithPacketId:(NSString *)packetId
                                           withUserId:(NSString *)userId
                                         withFriendId:(NSString *)friendId
                                          withMessage:(NSString *)message
                                      withMessageDate:(long long)date
{
    return [IMAdapter sendFriendCallLogMessageWithPacketId:packetId withUserId:userId withFriendId:friendId withMessage:message withMessageDate:date];
}

- (NSArray *)getPendingFriendMessageListWithId:(NSString *)userId
{
    return [IMAdapter getPendingFriendMessageListWithId:userId];
}

- (NSArray *)getPendingGroupMessageList
{
    return [IMAdapter getPendingGroupMessageList];
}

- (void)cleanUpWithMood:(IMSDK_MoodType)mood
{
    [IMAdapter cleanUpWithMood:mood];
}

- (BOOL) isExistsFriendConnectionWithUserId:(NSString *)userId withFriendId:(NSString *)friendId
{
    return [IMAdapter isExistsFriendConnectionWithUserId:userId withFriendId:friendId];
}

- (IMApiStatus *)sendRegisterRequestForGroupChatWithId:(NSString *)groupId withChatServerIP:(NSString *)ipAddress withPort:(NSInteger)port withAuthRegisterTime:(long long)authRegisterTime
{
    return [IMAdapter sendRegisterRequestForGroupChatWithId:groupId withChatServerIP:ipAddress withPort:port withAuthRegisterTime:authRegisterTime];
}

- (BOOL) isExistsGroupConnectionWithGroupId:(NSString *)groupId
{
    return [IMAdapter isExistsGroupConnectionWithGroupId:groupId];
}

- (IMApiStatus *)sendUnregisterRequestForFriendChatWithId:(NSString *)userId withFriendId:(NSString *)friendId withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood
{
    return [IMAdapter sendUnregisterRequestForFriendChatWithId:userId withFriendId:friendId withOnlineStatus:status withMood:mood];
}

- (IMApiStatus *)sendUnregisterRequestForGroupChatWithId:(NSString *)groupId withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood
{
    return [IMAdapter sendUnregisterRequestForGroupChatWithId:groupId withOnlineStatus:status withMood:mood];
}

- (IMApiStatus *)sendTypingForFriendChatWithId:(NSString *)userId withFriendId:(NSString *)friendId;
{
    return [IMAdapter sendTypingForFriendChatWithId:userId withFriendId:friendId];
}

- (IMApiStatus *)sendTypingForGroupChatwithId:(NSString *)groupId
{
    return [IMAdapter sendTypingForGroupChatwithId:groupId];
}

- (IMApiStatus *)sendFriendChatMessageWithPacketId:(NSString *)packetId withUserId:(NSString *)userId withFriendId:(NSString *)friendId withMessage:(NSString *)message withMessageType:(IMSDK_MessageType)messageType withMessageDate:(long long)date withSecretTime:(NSInteger)secretTime withIsSecretVisible:(BOOL)isSecretVisible
{
    return [IMAdapter sendFriendChatMessageWithPacketId:packetId withUserId:userId withFriendId:friendId withMessage:message withMessageType:messageType withMessageDate:date withSecretTime:secretTime withIsSecretVisible:isSecretVisible];
}

- (IMApiStatus *)sendFriendChatEdittedMessageWithPacketId:(NSString *)packetId withUserId:(NSString *)userId withFriendId:(NSString *)friendId withMessage:(NSString *)message withMessageType:(IMSDK_MessageType)messageType withMessageDate:(long long)date withSecretTime:(NSInteger)secretTime withIsSecretVisible:(BOOL)isSecretVisible
{
    return [IMAdapter sendFriendChatEdittedMessageWithPacketId:packetId withUserId:userId withFriendId:friendId withMessage:message withMessageType:messageType withMessageDate:date withSecretTime:secretTime withIsSecretVisible:isSecretVisible];
}

- (IMApiStatus *)sendSeenForFriendChatWithId:(NSString *)userId withFriendId:(NSString *)friendId withMessageStatusList:(NSArray *)messageStatusList
{
    return [IMAdapter sendSeenForFriendChatWithId:userId withFriendId:friendId withMessageStatusList:messageStatusList];
}

- (IMApiStatus *)sendBlockFriendRequestWithPacketId:(NSString*)packetId withUserId:(NSString *)userId withFriendId:(NSString *)friendId withBlockDate:(long long)date withExtrayByte:(BOOL)blockValue
{
    return [IMAdapter sendBlockFriendRequestWithPacketId:packetId withUserId:(NSString *)userId withFriendId:friendId withBlockDate:date withExtrayByte:blockValue];
}

- (IMApiStatus *)sendUnblockFreindRequestWithPacketId:(NSString*)packetId withUserId:(NSString *)userId withFriendId:(NSString *)friendId withUnblockDate:(long long)date
{
    return [IMAdapter sendUnblockFreindRequestWithPacketId:packetId withUserId:(NSString *)userId withFriendId:friendId withUnblockDate:date];
}

- (IMApiStatus *)sendGroupChatMessageWithPacketId:(NSString*)packetId withGroupId:(NSString *)groupId withMessage:(NSString *)message withMessageType:(IMSDK_MessageType)messageType withMessageDate:(long long)date
{
    return [IMAdapter sendGroupChatMessageWithPacketId:packetId withGroupId:groupId withMessage:message withMessageType:messageType withMessageDate:date];
}

- (IMApiStatus *)sendGroupChatEditedMessageWithPacketId:(NSString *)packetId withGroupId:(NSString *)groupId withMessage:(NSString *)message withMessageType:(IMSDK_MessageType)messageType withMessageDate:(long long)date
{
    return [IMAdapter sendGroupChatEditedMessageWithPacketId:packetId withGroupId:groupId withMessage:message withMessageType:messageType withMessageDate:date];
}

- (IMApiStatus *)sendSeenForGroupChatWithId:(NSString *)groupId withPacketIdList:(NSArray *)packetIdList
{
    return [IMAdapter sendSeenForGroupChatWithId:groupId withPacketIdList:packetIdList];
}

- (IMApiStatus *)sendRequestForGroupSeenListWithId:(NSString *)groupId withPacketId:(NSString *)packetId
{
    return [IMAdapter sendRequestForGroupSeenListWithId:groupId withPacketId:packetId];
}

- (IMApiStatus *)sendDeleteFriendMessageRequestWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketIdList:(NSArray *)packetIdArray withDeleteType:(NSInteger) deleteType
{
    return [IMAdapter sendDeleteFriendMessageRequestWithId:userId withFriendId:friendId withPacketIdList:packetIdArray  withDeleteType:deleteType];
}

- (IMApiStatus *)sendDeleteGroupMessageRequestWithId:(NSString *)groupId withPacketIdArray:(NSArray *)packetIdArray
{
    return [IMAdapter sendDeleteGroupMessageRequestWithId:groupId withPacketIdList:packetIdArray];
}

- (IMApiStatus *)sendGroupMemberAddRequestWithId:(NSString *)groupId withMemberList:(NSArray *)memberList
{
    return [IMAdapter sendGroupMemberAddRequestWithId:groupId withMemberList:memberList];
}

- (IMApiStatus *)sendGroupMemberRemoveRequestWithId:(NSString *)groupId withMemberList:(NSArray *)memberList
{
    return [IMAdapter sendGroupMemberRemoveRequestWithId:groupId withMemberList:memberList];
}

- (IMApiStatus *)sendGroupMemberStatusChangeRequestWithId:(NSString *)groupId withMemberList:(NSArray *)memberList
{
    return [IMAdapter sendGroupMemberStatusChangeRequestWithId:groupId withMemberList:memberList];
}

- (IMApiStatus *)sendLeaveGroupRequestWithId:(NSString *)groupId withIsHide:(BOOL)isHide
{
    return [IMAdapter sendLeaveGroupRequestWithId:groupId withIsHide:isHide];
}

- (IMApiStatus *)sendRequestForFriendChatHistoryWithId:(NSString *)userId withFriendId:(NSString*)friendId withPacketId:(NSString*)packetId withDirection:(IMSDK_Scroll)direction withLimit:(int)limit
{
    return [IMAdapter sendRequestForFriendChatHistoryWithId:userId withFriendId:friendId withPacketId:packetId withDirection:direction withLimit:limit];
}

- (IMApiStatus *)sendRequestForFriendMessageStatusWithId:(NSString *)userId withFriendId:(NSString*)friendId withPacketIdArray:(NSArray *)packetIdArray
{
    return [IMAdapter sendRequestForFriendMessageStatusWithId:userId withFriendId:friendId withPacketIdArray:packetIdArray];
}

- (IMApiStatus *)sendGroupRenameWithId:(NSString*)groupId withGroupName:(NSString*)name
{
    return [IMAdapter sendGroupRenameWithId:groupId withGroupName:name];
}

- (IMApiStatus *)sendGroupProfilePicChangeWithId:(NSString*)groupId withImageUrl:(NSString*)url
{
    return [IMAdapter sendGroupProfilePicChangeWithId:groupId withImageUrl:url];
}

- (IMApiStatus *)sendCreateGroupWithId:(NSString*)groupId withGroupName:(NSString*)name withImageUrl:(NSString*)url withMemberList:(NSArray *)memberList
{
    return [IMAdapter sendCreateGroupWithId:groupId withGroupName:name withImageUrl:url withMemberList:memberList];
}

- (IMApiStatus *)sendRequestForGroupChatHistoryWithId:(NSString*)groupId withPacketId:(NSString*)packetId withDirection:(IMSDK_Scroll)direction withLimit:(int)limit
{
    return [IMAdapter sendRequestForGroupChatHistoryWithId:groupId withPacketId:packetId withDirection:direction withLimit:limit];
}

- (IMApiStatus *)sendRequestForGroupInformationWithMembersWithId:(NSString*)groupId
{
    return [IMAdapter sendRequestForGroupInformationWithMembersWithId:groupId];
}

- (void) reinitializeSdkWithUserId:(NSString *)userId
                      withUserName:(NSString *)userName
               withOfflineServerIP:(NSString *)offlineIpAddress
             withOfflineServerPort:(NSInteger)offlinePort
                  withAuthServerIP:(NSString*)authIpAddress
                withAuthServerPort:(NSInteger)authPort
                    withDeviceType:(IMSDK_DeviceType)deviceType
                  withAppSessionId:(NSString*)appSessionId
                    withAppVersion:(NSInteger)appType
                withTimeDifference:(long long)timeDifference
                withDirectoryPaths:(NSArray *)directoryPaths
                  withAutoDownload:(BOOL)autoDownload
                 withEncryptionKey:(NSString*)encryptionKey
                    withPageIdList:(NSArray *)pageIdList
{
    [IMAdapter reinitializeSdkWithUserId:userId withUserName:userName withOfflineServerIP:offlineIpAddress withOfflineServerPort:offlinePort withAuthServerIP:authIpAddress withAuthServerPort:authPort withDeviceType:deviceType withAppSessionId:appSessionId withAppVersion:appType withTimeDifference:timeDifference withDirectoryPaths:directoryPaths withAutoDownload:autoDownload withEncryptionKey:encryptionKey withPageIdList:pageIdList];
}

- (IMFriendInformationModel *)getFriendInformationWithId:(NSString *)userId withFriendId:(NSString *)friendId
{
    return [IMAdapter getFriendInformationWithId:userId withFriendId:friendId];
}

- (IMGroupInformationModel *)getGroupInformationWithId:(NSString *)groupId
{
    return [IMAdapter getGroupInformationWithId:groupId];
}

- (NSArray *)getRegisteredFriendListWithId:(NSString *)userId
{
    return [IMAdapter getRegisteredFriendListWithId:userId];
}

- (NSArray *)getRegisteredGroupList
{
    return [IMAdapter getRegisteredGroupList];
}

- (IMApiStatus *)sendRegisterRequstForPublicRoomChatWithRoomId:(NSString *)roomId
                                              withMemberName:(NSString *)memberName
                                               withMemberUrl:(NSString *)memberUrl
                                                    withRingId:(NSString *)ringId
{
    return [IMAdapter sendRegisterRequestForPublicRoomChatWithRoomId:roomId withMemberName:memberName withMemberUrl:memberName withRingId:ringId];
}

- (void)enterPublicRoomChatScreenWithRoomId:(NSString *)roomId
{
    [IMAdapter enterPublicRoomChatScreenWithRoomId:roomId];
}

- (void)exitPublicRoomChatScreenWithRoomId:(NSString *)roomId
{
    [IMAdapter exitPublicRoomChatScreenWithRoomId:roomId];
}

- (IMApiStatus *)sendPublicRoomChatMessageWithPacketId:(NSString *)packetId
                                            withRoomId:(NSString *)roomId
                                       withMessageType:(IMSDK_MessageType)messageType
                                           withMessage:(NSString *)message
                                       withMessageDate:(long long)messageDate
                                        withMemberName:(NSString *)memberName
                                  withMemberProfileUrl:(NSString *)memberProfileUrl
{
    return [IMAdapter sendPublicRoomChatMessageWithPacketId:packetId withRoomId:roomId withMessageType:messageType withMessage:message withMessageDate:messageDate withMemberName:memberName withMemberProfileUrl:memberProfileUrl];
}

- (IMApiStatus *)sendPublicRoomChatEditedMessageWithPacketId:(NSString *)packetId
                                                  withRoomId:(NSString *)roomId
                                             withMessageType:(IMSDK_MessageType)messageType
                                                 withMessage:(NSString *)message
                                             withMessageDate:(long long)messageDate
                                              withMemberName:(NSString *)memberName
                                        withMemberProfileUrl:(NSString *)memberProfileUrl
{
    return [IMAdapter sendPublicRoomChatEditedMessageWithPacketId:packetId withRoomId:roomId withMessageType:messageType withMessage:message withMessageDate:messageDate withMemberName:memberName withMemberProfileUrl:memberProfileUrl];
}

- (IMApiStatus *)sendRoomListRequestWithIndex:(int)startIndex withLimit:(int)limit
{
    return [IMAdapter sendRoomListRequestWithIndex:startIndex withLimit:limit];
}

- (IMApiStatus *)sendRoomListSearchRequestWithName:(NSString *)searchName withCountry:(NSString *)country withCategory:(NSString *)category withIndex:(int)startIndex withLimit:(int)limit
{
    return [IMAdapter sendRoomListSearchRequestWithName:searchName withCountry:(NSString *)country withCategory:(NSString *)category withIndex:startIndex withLimit:limit];
}

- (IMApiStatus *)sendUnregisterRequestForPublicRoomChatWithRoomId:(NSString *)roomId
{
    return [IMAdapter sendUnregisterRequestForPublicRoomChatWithRoomId:roomId];
}

- (IMApiStatus *)sendTypingForPublicRoomChatWithRoomId:(NSString *)roomId
{
    return [IMAdapter sendTypingForPublicRoomChatWithRoomId:roomId];
}

- (BOOL)isExistsPublicRoomChatConnectionWithRoomId:(NSString *)roomId
{
    return [IMAdapter isExistsPublicRoomChatConnectionWithRoomId:roomId];
}

- (IMApiStatus *)sendRequestForPublicChatRoomInformationWithRoomId:(NSString *)roomId
{
    return [IMAdapter sendRequestForPublicChatRoomInformationWithRoomId:roomId];
}

- (IMApiStatus *)sendRoomChatHistoryRequestWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId withYear:(int)year withMonth:(int)month withDirection:(IMSDK_Scroll)direction withLimit:(int)limit
{
    return [IMAdapter sendRoomChatHistoryRequestWithRoomId:roomId withPacketId:packetId withYear:year withMonth:month withDirection:direction withLimit:limit];
}

- (IMApiStatus *)sendRoomListWithHistoryRequestWithIndex:(int)startIndex withLimit:(int)limit
{
    return [IMAdapter sendRoomListWithHistoryRequestWithIndex:startIndex withLimit:limit];
}

- (IMApiStatus *)sendRoomMemberListRequestWithRoomId:(NSString *)roomId withPagingState:(NSString *)pagingState withLimit:(int)limit
{
    return [IMAdapter sendRoomMemberListRequestWithRoomId:roomId withPagingState:pagingState withLimit:limit];
}


- (IMApiStatus *)sendDeletePublicRoomChatDeleteRequestWithId:(NSString *)roomId withPacketIdList:(NSArray *)packetIdList
{
    return [IMAdapter sendDeletePublicRoomChatDeleteRequestWithId:roomId withPacketIdList:packetIdList];
}

- (IMApiStatus *)sendLikePublicRoomChatMessageRequestWithId:(NSString *)roomId withPacketId:(NSString *)packetId withMessageSenderId:(NSString *)messageSender
{
    return [IMAdapter sendLikePublicRoomChatMessageRequestWithId:roomId withPacketId:packetId withMessageSenderId:messageSender];
}

- (IMApiStatus *)sendUnlikePublicRoomChatMessageRequestWithId:(NSString *)roomId withPacketId:(NSString *)packetId withMessageSenderId:(NSString *)messageSender
{
    return [IMAdapter sendUnlikePublicRoomChatMessageRequestWithId:roomId withPacketId:packetId withMessageSenderId:messageSender];
}

- (IMApiStatus *)sendReportPublicRoomChatMessageRequestWithId:(NSString *)roomId withPacketId:(NSString *)packetId withMessageSenderId:(NSString *)messageSender withReportMessage:(NSString *)reportMessage
{
    return [IMAdapter sendReportPublicRoomChatMessageRequestWithId:roomId withPacketId:packetId withMessageSenderId:messageSender withReportMessage:reportMessage];
}

- (IMApiStatus *)sendRequestForPublicRoomChatLikeMemberList:(NSString *)roomId withPacketId:(NSString *)packetId withLastLikerId:(NSString *)lastLikerId withLimit:(int) limit
{
    return [IMAdapter sendRequestForPublicRoomChatLikeMemberList:roomId withPacketId:packetId withLastLikerId:lastLikerId withLimit:limit];
}

- (IMApiStatus *)sendRequestForPublicRoomChatCategoryListWithLastCategory:(NSString *)lastCategory withLimit:(int) limit
{
    return [IMAdapter sendRequestForPublicRoomChatCategoryListWithLastCategory:lastCategory withLimit:limit];
}

//Anonymous chat
- (IMApiStatus *)sendRegisterRequestForAnonymousFriendChatWithSelfAnonymousId:(NSString *)selfAnonymousId
                                                        withFriendAnonymousId:(NSString *)friendAnonymousId
                                                         withFriendOriginalId:(NSString *)friendOriginalId
                                                    withRegisterServerAddress:(NSString *)registerServerAddress
                                                       withRegisterServerPort:(NSInteger)registerServerPort
                                                               withDeviceType:(IMSDK_DeviceType)deviceType
                                                              withDeviceToken:(NSString *)deviceToken
                                                                  withAppType:(int)appType
                                                             withOnlineStatus:(IMSDK_Presence)status
                                                                     withMood:(IMSDK_MoodType)mood
{
    return [IMAdapter sendRegisterRequestForAnonymousFriendChatWithSelfAnonymousId:selfAnonymousId withFriendAnonymousId:friendAnonymousId withFriendOriginalId:friendOriginalId withRegisterServerAddress:registerServerAddress withRegisterServerPort:registerServerPort withDeviceType:deviceType withDeviceToken:deviceToken withAppType:appType withOnlineStatus:status withMood:mood];
}

- (IMApiStatus *)sendUnregisterRequestForAnonymousFriendChatWithId:(NSString *)userId withFriendId:(NSString *)anonymousFriendId withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood
{
    return [IMAdapter sendUnregisterRequestForAnonymousFriendChatWithId:userId withFriendId:anonymousFriendId withOnlineStatus:status withMood:mood];
}

- (IMApiStatus *)sendRequestForConversationListWithId:(NSString *)userId withType:(IMSDK_ConversationType)conversationType withStartIndex:(int)startIndex withLimit:(int)limit withId:(NSString *)friendGroupId
{
    return [IMAdapter sendRequestForConversationListWithId:userId withType:conversationType withStartIndex:startIndex withLimit:limit withId:friendGroupId];
}

- (IMApiStatus *)sendDeleteConversationListRequestWithId:(NSString *)userId withList:(NSArray *)conversationList
{
    return [IMAdapter sendDeleteConversationListRequestWithId:userId withList:conversationList];
}

- (IMApiStatus *)sendMarkConversationListRequestWithId:(NSString *)userId withList:(NSArray *)conversationList
{
    return [IMAdapter sendMarkConversationListRequestWithId:userId withList:conversationList];
}

- (void) updatePasswordWithPassword:(NSString *)password
{
    [IMAdapter updatePasswordWithPassword:password];
}

- (IMNetworkDataModel *)getNetworkDataUsage
{
    return [IMAdapter getNetworkDataUsage];
}

- (long long)getTimeFromPacketIdWithId:(NSString *)packetId
{
    return [IMAdapter getTimeFromPacketIdWithId:packetId];
}

- (long long)getCurrentServerSyncedTime
{
    return [IMAdapter getCurrentServerSyncedTime];
}

- (BOOL) checkInternetConnection
{
    return [IMAdapter checkInternetConnection];
}


- (BOOL)sendFriendChatMediaWithId:(NSString *)userId
                     withFriendId:(NSString *)friendId
               withPacketId:(NSString *)packetId
            withMessageType:(IMSDK_MessageType)messageType
               withFilePath:(NSString *)filePath
                withCaption:(NSString *)caption
            withWidthOrSize:(NSInteger)widthOrSize
        witHeightOrDuration:(NSInteger)heightOrDuration
                withTimeout:(NSInteger)timeout
            withMessageDate:(long long)date
        withIsSecretVisible:(BOOL)isSecretVisible
{

    return [IMAdapter sendFriendChatMediaWithId:userId withFriendId:friendId withPacketId:packetId withMessageType:messageType withFilePath:filePath withCaption:caption withWidthOrSize:widthOrSize witHeightOrDuration:heightOrDuration withTimeout:timeout withMessageDate:date withIsSecretVisible:isSecretVisible];
}

- (BOOL)downloadFriendChatMediaWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withManifestUrl:(NSString *)manifestUrl withMessageType:(IMSDK_MessageType)messageType withTimeout:(NSInteger)timeout
{
    return [IMAdapter downloadFriendChatMediaWithId:userId withFriendId:friendId withPacketId:packetId withManifestUrl:manifestUrl withMessageType:messageType withTimeout:timeout];

}

- (BOOL)acceptChatMediaWithPacketId:(NSString *)packetId
{

    return [IMAdapter acceptChatMediaWithPacketId:packetId];
}

- (BOOL)sendGroupChatMediaWithId:(NSString *)groupId
                    withPacketId:(NSString *)packetId
                 withMessageType:(IMSDK_MessageType)messageType
                    withFilePath:(NSString *)filePath
                     withCaption:(NSString *)caption
                 withWidthOrSize:(NSInteger)widthOrSize
             witHeightOrDuration:(NSInteger)heightOrDuration
                 withMessageDate:(long long)date
{
    return [IMAdapter sendGroupChatMediaWithId:groupId withPacketId:packetId withMessageType:messageType withFilePath:filePath withCaption:caption withWidthOrSize:widthOrSize witHeightOrDuration:heightOrDuration withMessageDate:date];
}

- (BOOL)downloadGroupChatMediaWithId:(NSString *)groupId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withManifestUrl:(NSString *)manifestUrl withMessageType:(IMSDK_MessageType)messageType
{
    return [IMAdapter downloadGroupChatMediaWithId:groupId withFriendId:friendId withPacketId:packetId withManifestUrl:manifestUrl withMessageType:messageType];
}

- (NSArray *)getPendingChatMediaListWithType:(IMSDK_ConversationType)conversationType withUploadingMediaList:(BOOL)uploadingMediaList withIsChunkedTransfer:(BOOL)isChunkedTransfer
{
    return [IMAdapter getPendingChatMediaListWithType:conversationType withUploadingMediaList:uploadingMediaList withIsChunkedTransfer:isChunkedTransfer];
}

- (BOOL)isChatMediaTransferInProgressWithPacketId:(NSString *)packetId
{
    return [IMAdapter isChatMediaTransferInProgressWithPacketId:packetId];
}

- (void) cancelChatMediaTransferWithId:(NSString *)packetId
{
    [IMAdapter cancelChatMediaTransferWithId:packetId];
}

- (void) updateAppSessionIDWithAppSessionId:(NSString *)appSessionId
{
    [IMAdapter updateAppSessionIDWithAppSessionId:appSessionId];
}

//- (IMApiStatus *)sendFileToFriendWithFriendId:(NSString*)friendId withMessageType:(int)messageType withSecretTimeOut:(int)secretTimeOut withFileIdentity:(long long)fileId withFileFullPath:(NSString*)fileFullPath withFileSize:(long long)fileSize withMessageDate:(long long)messageDate withIsSecretVisible:(bool)isSecretVisible
//{
//    return [IMAdapter sendFileToFriendWithFriendId:friendId withMessageType:messageType withSecretTimeOut:secretTimeOut withFileIdentity:fileId withFileFullPath:fileFullPath withFileSize:fileSize withMessageDate:messageDate withIsSecretVisible:isSecretVisible];
//}
//
//- (IMApiStatus *) startFileTransferWithFriendId:(NSString*)friendId withFileIdentity:(long long)fileId withFilePath:(NSString*)filePath
//{
//    return [IMAdapter startFileTransferWithFriendId:friendId withFileIdentity:fileId withFilePath:filePath];
//}
//
//- (IMApiStatus *) cancelFileTransferWithFriendId:(NSString*)friendId withFileIdentity:(long long)fileId
//{
//    return [IMAdapter cancelFileTransferWithFriendId:friendId withFileIdentity:fileId];
//}

- (void)setLogEnabledWithIsEnabled:(BOOL)isEnabled
{
    [IMAdapter setLogEnabledWithIsEnabled:isEnabled];
}

- (NSString *) generateGroupId
{
    return [IMAdapter generateGroupId];
}

- (void) addPageIdWithId:(NSString *)pageId
{
    [IMAdapter addPageIdWithId:pageId];
}

- (void) removePageIdWithId:(NSString *)pageId
{
    [IMAdapter removePageIdWithId:pageId];
}

- (IMPacketTimeId *) generatePacketIdWithUserId:(NSString *)userId
{
    return [IMAdapter generatePacketIdWithUserId:userId];
}

- (IMPacketTimeId *) generatePacketIdWithTime:(long long)timeMili withUserId:(NSString *)userId
{
    return [IMAdapter generatePacketIdWithTime:timeMili withUserId:userId];
}

- (NSString *) version
{
    return [IMAdapter version];
}

- (void)setLogfileWithFileName:(NSString *)fileName
{
    [IMAdapter setLogfileWithFileName:fileName];
}

//Live-stream-chat
- (IMApiStatus *)sendRegisterRequestForLiveStreamChatWithPublisherId:(NSString *)publisherId
                                        withRegisterServerAddress:(NSString *)registerServerAddress
                                        withRegisterServerPort:(NSInteger)registerServerPort
                                        withFullName:(NSString *)fullName
{
    return [IMAdapter sendRegisterRequestForLiveStreamChatWithPublisherId:publisherId withRegisterServerAddress:registerServerAddress withRegisterServerPort:registerServerPort withFullName:fullName];
}

- (IMApiStatus *)sendUnregisterRequestForLiveStreamChatWithPublisherId:(NSString *)publisherId
                                          withOnlineStatus:(IMSDK_Presence)onlineStatus
                                          withMood:(IMSDK_MoodType)onlineMood
{
    return [IMAdapter sendUnregisterRequestForLiveStreamChatWithPublisherId:publisherId withOnlineStatus:onlineStatus withMood:onlineMood];
}

- (IMApiStatus *)sendTypingForLiveStreamChatWithPublisherId:(NSString *)publisherId
{
    return [IMAdapter sendTypingForLiveStreamChatWithPublisherId:publisherId];
}

- (IMApiStatus *)sendLiveStreamChatMessageWithPacketId:(NSString *)packetId
                                          withPublisherId:(NSString *)publisherId
                                       withMessageType:(IMSDK_MessageType)messageType
                                           withMessage:(NSString *)message
                                       withMessageDate:(long long)messageDate
{
    return [IMAdapter sendLiveStreamChatMessageWithPacketId:packetId withPublisherId:publisherId withMessageType:messageType withMessage:message withMessageDate:messageDate];
}

- (IMApiStatus *)blockUserFromLiveStreamChatWithViewerId:(NSString *)viewerId
                                            withPacketId:(NSString *)packetId
{
    return [IMAdapter blockUserFromLiveStreamChatWithViewerId:viewerId withPacketId:packetId];
}

- (IMApiStatus *)getSyncedConversationWithId:(NSString *)userId withPacketId:(NSString *)packetId withLastSyncedTime:(long long)lastSyncedTime
{
    return [IMAdapter getSyncedConversationWithId:userId withPacketId:packetId withLastSyncedTime:lastSyncedTime];
}

- (IMApiStatus *)getSyncedFriendHistoryMessageWithId:(NSString *)userId withFrinedId:(NSString *)friendId withPacketId:(NSString *)packetId withLastSyncedTime:(long long)lastSyncedTime withLimit:(NSInteger)limit withDirection:(NSInteger)direction
{
    return [IMAdapter getSyncedFriendHistoryMessageWithId:userId withFrinedId:friendId withPacketId:packetId withLastSyncedTime:lastSyncedTime withLimit:limit withDirection:direction];
}

- (IMApiStatus *)getSyncedGroupHistoryMessageWithId:(NSString *)userId withGroupId:(NSString *)groupId withPacketId:(NSString *)packetId withLastSyncedTime:(long long)lastSyncedTime withLimit:(NSInteger)limit withDirection:(NSInteger)direction
{
    return [IMAdapter getSyncedGroupHistoryMessageWithId:userId withGroupId:groupId withPacketId:packetId withLastSyncedTime:lastSyncedTime withLimit:limit withDirection:direction];
}

- (IMApiStatus *)getMyGroupListPagingWithId:(NSString *)userId withPacketId:(NSString *)packetId withPivotId:(NSString *)pivotId withLimit:(NSInteger)limit withDirection:(NSInteger)direction
{
    return [IMAdapter getMyGroupListPagingWithId:userId withPacketId:packetId withPivotId:pivotId withLimit:limit withDirection:direction];
}


@end


@implementation InternetChecker

+ (instancetype)sharedInstance
{
    static dispatch_once_t once;
    static id sharedInstance;
    dispatch_once(&once, ^{
        sharedInstance = [[InternetChecker alloc] init];
    });
    return sharedInstance;
}

- (void)initWithIpListFilePath:(NSString *)ipListFilePath
{
    [IMInternetCheckerAdapter initInternetCheckerWithIpListFilePath:ipListFilePath];
}

- (BOOL) checkInternetConnection
{
    return [IMInternetCheckerAdapter checkInternetConnection];
}

@end

@implementation DataEncryption

+ (instancetype)sharedInstance
{
    static dispatch_once_t once;
    static id sharedInstance;
    dispatch_once(&once, ^{
        sharedInstance = [[DataEncryption alloc] init];
    });
    return sharedInstance;
}

- (NSData *)encryptDataWithData:(NSData *)data withKey:(NSData *)key withStartIndex:(NSInteger)startIndex
{
    return [IPVDataEncryption encryptDataWithData:data withKey:key withStartIndex:startIndex];
}

- (NSData *)DecryptDataWithData:(NSData *)data withKey:(NSData *)key withStartIndex:(NSInteger)startIndex
{
    return [IPVDataEncryption DecryptDataWithData:data withKey:key withStartIndex:startIndex];
}

- (NSString *)getSessionlessKeyWithServerAddress:(NSString *)serverAddress withRingId:(NSString *)ringId
{
    return [IPVDataEncryption getSessionlessKeyWithServerAddress:serverAddress withRingId:ringId];
}


@end
