//
//  IMAdapter.h
//  ringID
//
//  Created by Sumon on 11/2/15.
//  Copyright © 2015 IPVision Canada Inc. All rights reserved.
//


#import <Foundation/Foundation.h>


#import "IMApiStatus.h"
#import "IMMessageStatusModel.h"
#import "IMPacketTimeId.h"
#import "IMSDKTypes.h"
#import "IMFriendInformationModel.h"
#import "IMGroupInformationModel.h"
#import "IMNetworkDataModel.h"
#import "ByteArray.h"

@interface IMAdapter : NSObject

+ (void)initiateChatWithUserId:(NSString *)userId withUserName:(NSString *)userName
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
                withPageIdList:(NSArray *)pageIdList;

+ (IMApiStatus *) activateOrDeactivateUserAccountWithActivationSatus:(BOOL)isAccountActivate;

+ (IMApiStatus *) sendGeneralEncryptedInformationWithUserID:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withType:(NSInteger)type withInfoType:(NSInteger)infoType withInfo:(NSString *)info;

+ (void)setNewOfflineServerWithIP:(NSString *)ipAddress withPort:(NSInteger)port;

+ (IMApiStatus *)sendRequestForOfflineMessageAndGroupInformationWithGroupUpdateTime:(long long)groupUpdateDate withBlockUnblockUpdateDate:(long long)blockUpdateDate;

+ (IMApiStatus *)sendRegisterRequstForFriendChatWithId:(NSString *)userId withUserName:(NSString *)userName withFriendId:(NSString*)friendId withFriendName:(NSString *)friendName withFriendUrl:(NSString *)friendUrl withChatServerIP:(NSString *)ipAddress withPort:(NSInteger)port withDeviceType:(IMSDK_DeviceType)deviceType withDeviceToken:(NSString *)deviceToken withAppType:(NSInteger)appType withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood withVoipPush:(NSInteger)voipPush withAuthRegisterTime:(long long)authRegisterTime withProfileType:(NSInteger)profileType;

+ (IMApiStatus *)updateFriendRegisterServerWithId:(NSString *)userId withFriendId:(NSString *)friendId withServerAddress:(NSString *)serverAddress withServerPort:(NSInteger)serverPort;
+ (IMApiStatus *)updateFriendPresenceId:(NSString *)userId withFriendId:(NSString *)friendId withPresence:(IMSDK_Presence)presence withMood:(IMSDK_MoodType)mood;
+ (IMApiStatus *)dontSendPendingMessagesWithId:(NSString *)userId withFriendId:(NSString *)friendId;
+ (IMApiStatus *)sendFriendCallBusyMessageWithPacketId:(NSString *)packetId
                                            withUserId:(NSString *)userId
                                              withFriendId:(NSString *)friendId
                                           withMessage:(NSString *)message
                                       withMessageDate:(long long)date;

+ (IMApiStatus *)sendFriendCallLogMessageWithPacketId:(NSString *)packetId
                                           withUserId:(NSString *)userId
                                          withFriendId:(NSString *)friendId
                                           withMessage:(NSString *)message
                                       withMessageDate:(long long)date;

+ (NSArray *)getPendingFriendMessageListWithId:(NSString *)userId;
+ (NSArray *)getPendingGroupMessageList;
+ (void)cleanUpWithMood:(IMSDK_MoodType)mood;

+ (BOOL) isExistsFriendConnectionWithUserId:(NSString *)userId withFriendId:(NSString *)friendId;

+ (IMApiStatus *)sendRegisterRequestForGroupChatWithId:(NSString *)groupId withChatServerIP:(NSString *)ipAddress withPort:(NSInteger)port withAuthRegisterTime:(long long)authRegisterTime;

+ (BOOL) isExistsGroupConnectionWithGroupId:(NSString *)groupId;

+ (IMApiStatus *)sendUnregisterRequestForFriendChatWithId:(NSString *)userId withFriendId:(NSString *)friendId withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood;

+ (IMApiStatus *)sendUnregisterRequestForGroupChatWithId:(NSString *)groupId withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood;

+ (IMApiStatus *)sendTypingForFriendChatWithId:(NSString *)userId withFriendId:(NSString *)friendId;

+ (IMApiStatus *)sendTypingForGroupChatwithId:(NSString *)groupId;

+ (IMApiStatus *)sendFriendChatMessageWithPacketId:(NSString *)packetId withUserId:(NSString *)userId withFriendId:(NSString *)friendId withMessage:(NSString *)message withMessageType:(IMSDK_MessageType)messageType withMessageDate:(long long)date withSecretTime:(NSInteger)secretTime withIsSecretVisible:(BOOL)isSecretVisible;

+ (IMApiStatus *)sendFriendChatEdittedMessageWithPacketId:(NSString *)packetId withUserId:(NSString *)userId withFriendId:(NSString *)friendId withMessage:(NSString *)message withMessageType:(IMSDK_MessageType)messageType withMessageDate:(long long)date withSecretTime:(NSInteger)secretTime withIsSecretVisible:(BOOL)isSecretVisible;

+ (IMApiStatus *)sendSeenForFriendChatWithId:(NSString *)userId withFriendId:(NSString *)friendId withMessageStatusList:(NSArray *)messageStatusList;

+ (IMApiStatus *)sendBlockFriendRequestWithPacketId:(NSString*)packetId withUserId:(NSString *)userId withFriendId:(NSString *)friendId withBlockDate:(long long)date withExtrayByte:(BOOL)blockValue;

+ (IMApiStatus *)sendUnblockFreindRequestWithPacketId:(NSString*)packetId withUserId:(NSString *)userId withFriendId:(NSString *)friendId withUnblockDate:(long long)date;

+ (IMApiStatus *)sendGroupChatMessageWithPacketId:(NSString*)packetId withGroupId:(NSString *)groupId withMessage:(NSString *)message withMessageType:(IMSDK_MessageType)messageType withMessageDate:(long long)date;

+ (IMApiStatus *)sendGroupChatEditedMessageWithPacketId:(NSString *)packetId withGroupId:(NSString *)groupId withMessage:(NSString *)message withMessageType:(IMSDK_MessageType)messageType withMessageDate:(long long)date;

+ (IMApiStatus *)sendSeenForGroupChatWithId:(NSString *)groupId withPacketIdList:(NSArray *)packetIdList;

+ (IMApiStatus *)sendRequestForGroupSeenListWithId:(NSString *)groupId withPacketId:(NSString *)packetId;

+ (IMApiStatus *)sendDeleteFriendMessageRequestWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketIdList:(NSArray *)packetIdArray withDeleteType:(NSInteger)deleteType;

+ (IMApiStatus *)sendDeleteGroupMessageRequestWithId:(NSString *)groupId withPacketIdList:(NSArray *)packetIdArray;

+ (IMApiStatus *)sendGroupMemberAddRequestWithId:(NSString *)groupId withMemberList:(NSArray *)memberList;

+ (IMApiStatus *)sendGroupMemberRemoveRequestWithId:(NSString *)groupId withMemberList:(NSArray *)memberList;

+ (IMApiStatus *)sendGroupMemberStatusChangeRequestWithId:(NSString *)groupId withMemberList:(NSArray *)memberList;

+ (IMApiStatus *)sendLeaveGroupRequestWithId:(NSString *)groupId withIsHide:(BOOL)isHide;

+ (IMApiStatus *)sendRequestForFriendChatHistoryWithId:(NSString *)userId withFriendId:(NSString*)friendId withPacketId:(NSString*)packetId withDirection:(IMSDK_Scroll)direction withLimit:(int)limit;

+ (IMApiStatus *)sendRequestForFriendMessageStatusWithId:(NSString *)userId withFriendId:(NSString*)friendId withPacketIdArray:(NSArray *)packetIdArray;

+ (IMApiStatus *)sendGroupRenameWithId:(NSString*)groupId withGroupName:(NSString*)name;

+ (IMApiStatus *)sendGroupProfilePicChangeWithId:(NSString*)groupId withImageUrl:(NSString*)url;

+ (IMApiStatus *)sendCreateGroupWithId:(NSString*)groupId withGroupName:(NSString*)name withImageUrl:(NSString*)url withMemberList:(NSArray *)memberList;

+ (IMApiStatus *)sendRequestForGroupChatHistoryWithId:(NSString*)groupId withPacketId:(NSString*)packetId withDirection:(IMSDK_Scroll)direction withLimit:(int)limit;

+ (IMApiStatus *)sendRequestForGroupInformationWithMembersWithId:(NSString*)groupId;

+ (void) reinitializeSdkWithUserId:(NSString *)userId
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
                    withPageIdList:(NSArray *)pageIdList;

+ (IMFriendInformationModel *)getFriendInformationWithId:(NSString *)userId withFriendId:(NSString *)friendId;

+ (IMGroupInformationModel *)getGroupInformationWithId:(NSString *)groupId;

+ (NSArray *)getRegisteredFriendListWithId:(NSString *)userId;

+ (NSArray *)getRegisteredGroupList;

+ (IMApiStatus *)sendRegisterRequestForPublicRoomChatWithRoomId:(NSString *)roomId
                                             withMemberName:(NSString *)memberName
                                              withMemberUrl:(NSString *)memberUrl
                                                     withRingId:(NSString *)ringId;

+ (void)enterPublicRoomChatScreenWithRoomId:(NSString *)roomId;

+ (void)exitPublicRoomChatScreenWithRoomId:(NSString *)roomId;

+ (IMApiStatus *)sendPublicRoomChatMessageWithPacketId:(NSString *)packetId
                                            withRoomId:(NSString *)roomId
                                       withMessageType:(IMSDK_MessageType)messageType
                                           withMessage:(NSString *)message
                                       withMessageDate:(long long)messageDate
                                        withMemberName:(NSString *)memberName
                                  withMemberProfileUrl:(NSString *)memberProfileUrl;

+ (IMApiStatus *)sendPublicRoomChatEditedMessageWithPacketId:(NSString *)packetId
                                                  withRoomId:(NSString *)roomId
                                             withMessageType:(IMSDK_MessageType)messageType
                                                 withMessage:(NSString *)message
                                             withMessageDate:(long long)messageDate
                                              withMemberName:(NSString *)memberName
                                        withMemberProfileUrl:(NSString *)memberProfileUrl;

+ (IMApiStatus *)sendRoomListRequestWithIndex:(int)startIndex withLimit:(int)limit;

+ (IMApiStatus *)sendRoomListSearchRequestWithName:(NSString *)searchName withCountry:(NSString *)country withCategory:(NSString *)category withIndex:(int)startIndex withLimit:(int)limit;

+ (IMApiStatus *)sendUnregisterRequestForPublicRoomChatWithRoomId:(NSString *)roomId;

+ (IMApiStatus *)sendTypingForPublicRoomChatWithRoomId:(NSString *)roomId;

+ (BOOL)isExistsPublicRoomChatConnectionWithRoomId:(NSString *)roomId;

+ (IMApiStatus *)sendRequestForPublicChatRoomInformationWithRoomId:(NSString *)roomId;

+ (IMApiStatus *)sendRoomChatHistoryRequestWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId withYear:(int)year withMonth:(int)month withDirection:(IMSDK_Scroll)direction withLimit:(int)limit;

+ (IMApiStatus *)sendRoomListWithHistoryRequestWithIndex:(int)startIndex withLimit:(int)limit;

+ (IMApiStatus *)sendRoomMemberListRequestWithRoomId:(NSString *)roomId withPagingState:(NSString *)pagingState withLimit:(int)limit;

+ (IMApiStatus *)sendDeletePublicRoomChatDeleteRequestWithId:(NSString *)roomId withPacketIdList:(NSArray *)packetIdList;

+ (IMApiStatus *)sendLikePublicRoomChatMessageRequestWithId:(NSString *)roomId withPacketId:(NSString *)packetId withMessageSenderId:(NSString *)messageSender;

+ (IMApiStatus *)sendUnlikePublicRoomChatMessageRequestWithId:(NSString *)roomId withPacketId:(NSString *)packetId withMessageSenderId:(NSString *)messageSender;

+ (IMApiStatus *)sendReportPublicRoomChatMessageRequestWithId:(NSString *)roomId withPacketId:(NSString *)packetId withMessageSenderId:(NSString *)messageSender withReportMessage:(NSString *)reportMessage;

+ (IMApiStatus *)sendRequestForPublicRoomChatLikeMemberList:(NSString *)roomId withPacketId:(NSString *)packetId withLastLikerId:(NSString *)lastLikerId withLimit:(int) limit;

+ (IMApiStatus *)sendRequestForPublicRoomChatCategoryListWithLastCategory:(NSString *)lastCategory withLimit:(int) limit;

//Anonymous chat
+ (IMApiStatus *)sendRegisterRequestForAnonymousFriendChatWithSelfAnonymousId:(NSString *)selfAnonymousId
                                                        withFriendAnonymousId:(NSString *)friendAnonymousId
                                                         withFriendOriginalId:(NSString *)friendOriginalId
                                                    withRegisterServerAddress:(NSString *)registerServerAddress
                                                       withRegisterServerPort:(NSInteger)registerServerPort
                                                               withDeviceType:(IMSDK_DeviceType)deviceType
                                                              withDeviceToken:(NSString *)deviceToken
                                                                  withAppType:(int)appType
                                                             withOnlineStatus:(IMSDK_Presence)status
                                                                     withMood:(IMSDK_MoodType)mood;

+ (IMApiStatus *)sendUnregisterRequestForAnonymousFriendChatWithId:(NSString *)userId withFriendId:(NSString *)anonymousFriendId withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood;

+ (IMApiStatus *)sendRequestForConversationListWithId:(NSString *)userId withType:(IMSDK_ConversationType)conversationType withStartIndex:(int)startIndex withLimit:(int)limit withId:(NSString *)friendGroupId;

+ (IMApiStatus *)sendDeleteConversationListRequestWithId:(NSString *)userId withList:(NSArray *)conversationList;

+ (IMApiStatus *)sendMarkConversationListRequestWithId:(NSString *)userId withList:(NSArray *)conversationList;

+ (void) updatePasswordWithPassword:(NSString *)password;

+ (IMNetworkDataModel *)getNetworkDataUsage;

+ (long long)getTimeFromPacketIdWithId:(NSString *)packetId;

+ (long long)getCurrentServerSyncedTime;

+ (BOOL) checkInternetConnection;

//+ (IMApiStatus *)sendFileToFriendWithFriendId:(NSString*)friendId withMessageType:(int)messageType withSecretTimeOut:(int)secretTimeOut withFileIdentity:(long long)fileId withFileFullPath:(NSString*)fileFullPath withFileSize:(long long)fileSize withMessageDate:(long long)messageDate withIsSecretVisible:(bool)isSecretVisible;
//
//+ (IMApiStatus *) startFileTransferWithFriendId:(NSString*)friendId withFileIdentity:(long long)fileId withFilePath:(NSString*)filePath;
//
//+ (IMApiStatus *) cancelFileTransferWithFriendId:(NSString*)friendId withFileIdentity:(long long)fileId;

+ (void)setLogEnabledWithIsEnabled:(BOOL)isEnabled;

+ (NSString *) generateGroupId;

+ (void) addPageIdWithId:(NSString *)pageId;
+ (void) removePageIdWithId:(NSString *)pageId;

+ (IMPacketTimeId *) generatePacketIdWithUserId:(NSString *)userId;

+ (IMPacketTimeId *) generatePacketIdWithTime:(long long)timeMili withUserId:(NSString *)userId;

+ (void)setLogfileWithFileName:(NSString *)fileName;

+ (NSString *) version;

+ (BOOL)sendFriendChatMediaWithId:(NSString *)userId
                     withFriendId:(NSString *)friendId
               withPacketId:(NSString *)packetId
            withMessageType:(IMSDK_MessageType)messageType
               withFilePath:(NSString *)filePath
                withCaption:(NSString *)caption
            withWidthOrSize:(NSInteger)widthOrSize
        witHeightOrDuration:(NSInteger)heightOrDuration
                withTimeout:(NSInteger)timeout
            withMessageDate:(long long)date
        withIsSecretVisible:(BOOL)isSecretVisible;

+ (BOOL)downloadFriendChatMediaWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withManifestUrl:(NSString *)manifestUrl withMessageType:(IMSDK_MessageType)messageType withTimeout:(NSInteger)timeout;

+ (BOOL)acceptChatMediaWithPacketId:(NSString *)packetId;

+ (BOOL)sendGroupChatMediaWithId:(NSString *)groupId
                    withPacketId:(NSString *)packetId
                 withMessageType:(IMSDK_MessageType)messageType
                    withFilePath:(NSString *)filePath
                     withCaption:(NSString *)caption
                 withWidthOrSize:(NSInteger)widthOrSize
             witHeightOrDuration:(NSInteger)heightOrDuration
                 withMessageDate:(long long)date;

+ (BOOL)downloadGroupChatMediaWithId:(NSString *)groupId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withManifestUrl:(NSString *)manifestUrl withMessageType:(IMSDK_MessageType)messageType;

+ (NSArray *)getPendingChatMediaListWithType:(IMSDK_ConversationType)conversationType withUploadingMediaList:(BOOL)uploadingMediaList withIsChunkedTransfer:(BOOL)isChunkedTransfer;

+ (BOOL)isChatMediaTransferInProgressWithPacketId:(NSString *)packetId;

+ (void) updateAppSessionIDWithAppSessionId:(NSString *)appSessionId;

+ (void) cancelChatMediaTransferWithId:(NSString *)packetId;

//Live-stream-chat
+ (IMApiStatus *)sendRegisterRequestForLiveStreamChatWithPublisherId:(NSString *)publisherId
                                        withRegisterServerAddress:(NSString *)registerServerAddress
                                        withRegisterServerPort:(NSInteger)registerServerPort
                                        withFullName:(NSString *)fullName;

+ (IMApiStatus *)sendUnregisterRequestForLiveStreamChatWithPublisherId:(NSString *)publisherId
                                          withOnlineStatus:(IMSDK_Presence)onlineStatus
                                          withMood:(IMSDK_MoodType)onlineMood;

+ (IMApiStatus *)sendTypingForLiveStreamChatWithPublisherId:(NSString *)publisherId;

+ (IMApiStatus *)sendLiveStreamChatMessageWithPacketId:(NSString *)packetId
                                          withPublisherId:(NSString *)publisherId
                                       withMessageType:(IMSDK_MessageType)messageType
                                           withMessage:(NSString *)message
                                       withMessageDate:(long long)messageDate;

+ (IMApiStatus *)blockUserFromLiveStreamChatWithViewerId:(NSString *)viewerId
                                            withPacketId:(NSString *)packetId;



+ (IMApiStatus *)getSyncedConversationWithId:(NSString *)userId
                            withPacketId:(NSString *)packetId
                              withLastSyncedTime:(long long)lastSyncedTime;

+ (IMApiStatus *)getSyncedFriendHistoryMessageWithId:(NSString *)userId
                            withFrinedId:(NSString *)friendId
                            withPacketId:(NSString *)packetId
                            withLastSyncedTime:(long long)lastSyncedTime
                            withLimit:(NSInteger)limit
                            withDirection:(NSInteger)direction;

+ (IMApiStatus *)getSyncedGroupHistoryMessageWithId:(NSString *)userId
                            withGroupId:(NSString *)groupId
                            withPacketId:(NSString *)packetId
                            withLastSyncedTime:(long long)lastSyncedTime
                            withLimit:(NSInteger)limit
                            withDirection:(NSInteger)direction;

+ (IMApiStatus *)getMyGroupListPagingWithId:(NSString *)userId
                               withPacketId:(NSString *)packetId
                               withPivotId:(NSString *)pivotId
                               withLimit:(NSInteger)limit
                               withDirection:(NSInteger)direction;



@end

@interface IMInternetCheckerAdapter : NSObject

+ (void) initInternetCheckerWithIpListFilePath:(NSString *)ipListFilePath;

+ (BOOL) checkInternetConnection;

@end


@interface IPVDataEncryption : NSObject

+ (imsdk::ByteArray)toByteArrayWithData:(NSData *)data;

+ (NSData *)toNSDataWithBytes:(imsdk::ByteArray)bytes;

+ (NSData *)encryptDataWithData:(NSData *)data withKey:(NSData *)key withStartIndex:(NSInteger)startIndex;

+ (NSData *)DecryptDataWithData:(NSData *)data withKey:(NSData *)key withStartIndex:(NSInteger)startIndex;

+ (NSString *)getSessionlessKeyWithServerAddress:(NSString *)serverAddress withRingId:(NSString *)ringId;

@end