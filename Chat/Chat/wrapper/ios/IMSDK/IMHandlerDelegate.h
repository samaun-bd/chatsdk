//
//  IMHandlerDelegate.h
//  ringID
//
//  Created by Sumon on 11/2/15.
//  Copyright © 2015 IPVision Canada Inc. All rights reserved.
//

#import "IMReceivedMessageDelegate.h"
#import <Foundation/Foundation.h>

@interface IMHandlerDelegate : NSObject

@property (nonatomic, weak) id <IMReceivedMessageDelegate> delegate;

+ (instancetype)sharedInstance;

- (void)receivedFriendChatBindPortWithId:(NSString *)userId withFriendID:(NSString *)friendId withDate:(long long)date withPacketId:(NSString *)packetId withIsAnonymous:(BOOL)isAnonymous;

- (void)receivedFriendChatRegisterFailureWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withIsAnonymous:(BOOL)isAnonymous;

-(void)receivedGeneralEncryptedPacketWithUserId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withType:(NSInteger)type withInfoType:(NSInteger)infoType withInfo:(NSString *)info;

-(void)receivedGeneralEncryptedConfirmationWithUserId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withType:(NSInteger)type withInfoType:(NSInteger)infoType;

- (void)receivedFriendChatRegistrationExpiredWithId:(NSString *)userId withFriendId:(NSString *)friendId withIsAnonymous:(BOOL)isAnonymous;

- (void)receivedFriendChatUnregisterWithId:(NSString *)userId withFriendId:(NSString *)friendId withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood withIsAnonymous:(BOOL)isAnonymous withProfileType:(NSInteger)profileType;

- (void)receivedGroupChatBindPortWithId:(NSString *)groupId withDate:(long long)date withPacketId:(NSString *)packetId;

- (void)receivedGroupChatRegisterFailureWithId:(NSString *)groupId withPacketId:(NSString *)packetId;

- (void)receivedGroupChatRegistrationExpiredWithId:(NSString *)groupId withLastActivityTime:(long long)lastActivityTime;

- (void)receivedFriendChatMessageWithSenderId:(NSString *)senderId withReceiverId:(NSString *)receiverId withPacketId:(NSString *)packetId withMessageType:(IMSDK_MessageType)messageType withSecretTime:(NSInteger)secretTime withMessage:(NSString *)message withDate:(long long)date withIsSecretVisible:(BOOL)isSecretVisible withIsFromOnline:(BOOL)isFromOnline withIsAnonymous:(BOOL)isAnonymous;

- (void)receivedFriendChatEdittedMessageWithSenderId:(NSString *)senderId withReceiverId:(NSString *)receiverId withPacketId:(NSString *)packetId withMessageType:(IMSDK_MessageType)messageType withSecretTime:(NSInteger)secretTime withMessage:(NSString *)message withDate:(long long)date withIsSecretVisible:(BOOL)isSecretVisible withIsAnonymous:(BOOL)isAnonymous;

- (void)receivedFriendChatDeliveredWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withIsAnonymous:(BOOL)isAnonymous withIsEdited:(BOOL)isEdited withIsFromOnline:(BOOL)isFromOnline;

- (void)receivedFriendChatSeenWithId:(NSString *)userId withFriendId:(NSString *)friendId withMessageStatusList:(NSArray *)messageStatusList withIsAnonymous:(BOOL)isAnonymous;

- (void)receivedFriendChatSeenConfirmationWithId:(NSString *)userId withFriendId:(NSString *)friendId withMessageStatusList:(NSArray *)messageStatusList withIsAnonymous:(BOOL)isAnonymous;

- (void)receivedFailedToSendFriendChatWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withIsAnonymous:(BOOL)isAnonymous;

- (void)receivedFriendChatTypingWithId:(NSString *)userId withFriendId:(NSString *)friendId withIsAnonymous:(BOOL)isAnonymous;

- (void)receivedFriendChatDeleteWithSenderId:(NSString *)senderId withFriendId:(NSString *)friendId withPacketIdList:(NSArray *)packetIdList withIsAnonymous:(BOOL)isAnonymous;

- (void)receivedFriendChatDeleteRequestStatusWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withPacketIds:(NSArray *)packetIds withIsAnonymous:(BOOL)isAnonymous withStatus:(BOOL)status withDeleteType:(NSInteger)deleteType;

- (void)receivedBlockFriendWithBlockerId:(NSString *)blockerId withBlockedId:(NSString *)blockedId withBlockValue:(BOOL)blockValue;

- (void)receivedUnblockFriendWithUnblockerId:(NSString *)unblockerId withUnblockedId:(NSString *)unblockedId;

- (void)receivedBlockUnblockRequestStatusWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withStatus:(BOOL)status withIsBlockRequest:(BOOL)isBlockRequest;

- (void)receivedGroupChatMessageWithId:(NSString *)groupId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withMessageType:(IMSDK_MessageType)messageType withMessage:(NSString *)message withDate:(long long)date withIsFromOnline:(BOOL)isFromOnline;

- (void)receivedGroupChatMessageDeletedWithId:(NSString *)groupId withFriendId:(NSString *)friendId withPacketIdList:(NSArray *)packetIdList;

- (void)receivedGroupChatMessageDeleteRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withPacketIds:(NSArray *)packetIds withStatus:(BOOL)status;

- (void)receivedGroupChatEdittedMessageWithId:(NSString *)groupId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withMessageType:(IMSDK_MessageType)messageType withMessage:(NSString *)message withDate:(long long)date;

- (void)receivedGroupChatDeliveredWithId:(NSString *)groupId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId;

- (void)receivedGroupChatSentWithId:(NSString *)groupId withPacketId:(NSString *)packetId withIsEdited:(BOOL)isEdited; // No Need

- (void)receivedGroupChatSeenWithId:(NSString *)groupId withPacketIdList:(NSArray *)packetIdList;

- (void)receivedRequestedGroupSeenListWithId:(NSString *)groupId withPacketId:(NSString *)packetId withMemberList:(NSArray *)memberList;

- (void)receivedFailedToSendGroupChatWithId:(NSString *)groupId withPacketId:(NSString *)packetId;

- (void)receivedGroupChatTypingWithId:(NSString *)groupId withFriendId:(NSString *)friendId;

- (void)receivedGroupMemberLeaveRemoveWithId:(NSString *)groupId withFriendId:(NSString *)friendId withMemberList:(NSArray *)memberList withPacketId:(NSString *)packetId withIsHide:(BOOL)isHide;

- (void)receivedGroupMemberAddWithId:(NSString *)groupId withFriendId:(NSString *)friendId withMemberList:(NSArray *)memberList withPacketId:(NSString *)packetId;

- (void)receivedGroupMemberStatusChangeWithId:(NSString *)groupId withFriendId:(NSString *)friendId withMemberList:(NSArray *)memberList withPacketId:(NSString *)packetId;

- (void)receivedGroupMemberRemoveLeaveRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status withIsHide:(BOOL)isHide;

- (void)receivedGroupMemberAddRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status;

- (void)receivedGroupMemberStatusChangeRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status;

- (void)shouldCheckFriendPresenceWithId:(NSString *)userId withFriendId:(NSString *)friendId withIsAnonymous:(BOOL)isAnonymous withProfileType:(NSInteger)profileType;

- (void)shouldCheckServerAddressForFriendWithId:(NSString *)userId withFriendId:(NSString *)friendId withIsAnonymous:(BOOL)isAnonymous;

- (void)shouldCheckServerAddressForGroupWithId:(NSString *)groupId;

- (void)shouldCheckOfflineServerAddress;

- (void)shouldUpdateUserPassword;

- (void)receivedServerTimeSyncedWithTimeDifference:(long long)timeDifference;

- (void) receivedFriendHistoryMessageWithId:(NSString *)userId withFriendId:(NSString *)friendId withMessageList:(NSArray *)messageList;

- (void) receivedFriendMessageStatusWithId:(NSString *)userId withFriendId:(NSString *)friendId withMessageStatusList:(NSArray *)messageStatusList;

- (void) receivedGroupHistoryMessageWithId:(NSString *)groupId withMessageList:(NSArray *)messageList;

- (void) receivedGroupInformationWithmembersWithId:(NSString *)groupId withGroupName:(NSString *)name withGroupUrl:(NSString*)url withMemberList:(NSArray *)memberList;

- (void) receivedGroupActivityWithActivityList:(NSArray *)activityList;

- (void) receivedMyGroupListWithList:(NSArray *)groupList;

- (void) receivedMyGroupListPagingWithList:(NSArray *)groupList withPivotid:(NSString *)pivotId withDirection:(NSInteger)direction;

- (void) receivedMyGroupListCompleted;

- (void) receivedGroupCreateRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status;

- (void) receivedGroupInformationChangeRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status;

- (void) receivedGroupNameUpdateWithId:(NSString *)groupId WithFriendId:(NSString *)friendId withGroupName:(NSString *)name withPacketId:(NSString *)packetId;

- (void) receivedGroupProfilePicUpdateWithId:(NSString *)groupId WithFriendId:(NSString *)friendId withUrl:(NSString *)url withPacketId:(NSString *)packetId;

- (void) receivedPublicRoomChatRegisterSuccessWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId withNumberOfMember:(NSInteger)numberOfMember withAnonymousId:(NSString *)anonymousId;
- (void) receivedPublicRoomChatRegisterFailureWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId;
- (void) receivedPublicRoomChatRegistrationExpiredWithRoomId:(NSString *)roomId;
- (void) receivedPublicRoomChatDeliveredWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId withIsEdited:(BOOL)isEdited;
- (void) receivedPublicRoomChatFailedToSendWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId;
- (void) receivedPublicRoomChatMessageWithRoomId:(NSString *)roomId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withMessageType:(IMSDK_MessageType)messageType withMessage:(NSString *)message withMessageDate:(long long)messageDate withMemberFullName:(NSString *)memberFullName withMemberUrl:(NSString *)memberProfileUrl;
- (void) receivedPublicRoomListWithRoomList:(NSArray *)roomList withIsWithHistory:(BOOL)isWithHistory;
- (void) receivedPublicRoomInformationWithRoomId:(NSString *)roomId withRoomName:(NSString *)roomName withRoomUrl:(NSString *)roomUrl withPacketId:(NSString *)packetId;
- (void) receivedPublicRoomChatEditedMessageWithRoomId:(NSString *)roomId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withMessageType:(IMSDK_MessageType)messageType withMessage:(NSString *)message withMessageDate:(long long)messageDate withMemberFullName:(NSString *)memberFullName withMemberUrl:(NSString *)memberProfileUrl;
- (void) receivedPublicRoomChatTypingWithRoomId:(NSString *)roomId withFriendId:(NSString *)friendId withMemberName:(NSString *)memberName;
- (void) receivedPublicChatMemberListWithRoomId:(NSString *)roomId withPagingState:(NSString *)pagingState withMemberList:(NSArray *)publicChatMemberList;
- (void) receivedPublicChatMemberCountChangeWithRoomId:(NSString *)roomId withNumberOfMember:(NSInteger)numberOfMember;
- (void) shouldCheckServerAddressForRoomWithRoomId:(NSString *)roomId;
- (void) receivedPublicRoomChatHistoryWithRoomId:(NSString *)roomId withMessageList:(NSArray *)publicChatMessageList;
- (void) receivedPublicRoomChatHistoryCompletedWithRoomId:(NSString *)roomId;
- (void) receivedGroupHistoryCompletedWithGroupId:(NSString *)groupId withDirection:(IMSDK_Scroll) direction;
- (void) receivedGroupInformationActivityFromHistoryMessageWithGroupId:(NSString *)groupId WithActivityList:(NSArray *)activityList withDirection:(IMSDK_Scroll) direction;
- (void) receivedGroupInformationWithMembersRequestStatusWithGroupId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status;
- (void) receivedFriendHistoryCompletedWithId:(NSString *)userId withFriendId:(NSString *)friendId withDirection:(IMSDK_Scroll)direction;
- (void) receivedFriendHistoryMessageRequestStatusWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withStatus:(BOOL)status;
- (void) receivedGroupHistoryMessageRequestStatusWithGroupId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status;
- (void) receivedGroupChatSeenRequestStatusWithId:(NSString *)groupId withPacketIdList:(NSArray *)packetIdList withStatus:(BOOL)status;
- (void) receivedPublicRoomListRequestStatusWithPacketId:(NSString *)packetId withStatus:(BOOL)status;
- (void) receivedPublicRoomInformationRequestFailedWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId;
- (void) receivedPublicRoomChatHistoryRequestStatusWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId withStatus:(BOOL)status;
- (void) receivedPublicRoomMemberListRequestStatusWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId withStatus:(BOOL)status;
- (void) receivedPublicRoomChatMessageDeletedWithId:(NSString *)roomId withPacketIdList:(NSArray *)packetIdList;
- (void) receivedPublicRoomChatMessageLikedWithId:(NSString *)roomId withPacketId:(NSString *)packetId withLikerId:(NSString *)likerId;
- (void) receivedPublicRoomChatMessageUnlikedWithId:(NSString *)roomId withPacketId:(NSString *)packetId withUnlikerId:(NSString *)unlikerId;
- (void) receivedPublicRoomChatCategoryListWithList:(NSArray *)categoryList;
- (void) receivedPublicRoomChatMessageLikeListWithId:(NSString *)roomId withPacketId:(NSString *)packetId withMemberList:(NSArray *)memberList;

- (void) receivedPublicRoomChatDeleteRequestStatusWithId:(NSString *)roomId withPacketId:(NSString *)packetId withStatus:(BOOL)status;
- (void) receivedPublicRoomChatLikeUnlikeRequestStatusWithId:(NSString *)roomId withPacketId:(NSString *)packetId withStatus:(BOOL)status;
- (void) receivedPublicRoomChatReportRequestStatusWithId:(NSString *)roomId withPacketId:(NSString *)packetId withStatus:(BOOL)status;
- (void) receivedPublicRoomChatLikeListRequestStatusWithId:(NSString *)roomId withPacketId:(NSString *)packetId withStatus:(BOOL)status;
- (void) receivedPublicRoomChatCategoryListRequestStatusWithPacketId:(NSString *)packetId withStatus:(BOOL)status;

- (void) receivedFriendConversationListWithId:(NSString *)userId withList:(NSArray *)friendConversationList withIsFromSynced:(BOOL)isFromSynced;
- (void) receivedGroupConversationListWithList:(NSArray *)groupConversationList withIsFromSynced:(BOOL)isFromSynced;
- (void) receivedConversationListCompletedWithId:(NSString *)userId withIsFromSynced:(BOOL)isFromSynced;
- (void) receivedConversationListDeleteRequestStatusWithId:(NSString *)userId withPacketId:(NSString *)packetId withStatus:(BOOL)status;
- (void) receivedConversationListMarkRequestStatusWithId:(NSString *)userId withPacketId:(NSString *)packetId withStatus:(BOOL)status;

- (void) receivedNetworkDataCountWithData:(IMNetworkDataModel *)data;

- (void) receivedFriendFileManifestUploadedWithId:(NSString *)userId
                                     withFriendId:(NSString *)friendId
                                     withPacketId:(NSString *)packetId
                                  withManifestUrl:(NSString *)url
                                  withMessageType:(IMSDK_MessageType)messageType
                                      withTimeout:(NSInteger)timeout
                                      withCaption:(NSString *)caption
                                  withWidthOrSize:(NSInteger)widthOrSize
                             withHeightOrDuration:(NSInteger)heightOrDuration;

- (void) receivedFriendIncomingChatMediaWithId:(NSString *)userId
                                  withFriendId:(NSString *)friendId
                                  withPacketId:(NSString *)packetId
                                  withFileName:(NSString *)fileName
                                withMessgeType:(IMSDK_MessageType)messageType
                                   withTimeout:(NSInteger)timeout
                               withMessageDate:(long long)date
                           withIsSecretVisible:(BOOL)isSecretVisible
                                   withCaption:(NSString *)caption
                               withWidthOrSize:(NSInteger)widthOrSize
                          withHeightOrDuration:(NSInteger)heightOrDuration;

- (void) receivedFriendChatMediaTransferProgressWithId:(NSString *)userId
                                          withFriendId:(NSString *)friendId
                                          withPacketId:(NSString *)packetId
                                          withFileName:(NSString *)fileName
                                withTransferPercentage:(double)transferPercentage
                                      withTransferType:(BOOL)isUpload;

- (void) receivedFriendChatMediaTransferFailedWithId:(NSString *)userId
                                        withFriendId:(NSString *)friendId
                                        withPacketId:(NSString *)packetId
                                        withFileName:(NSString *)fileName
                                        withIsUpload:(BOOL)isUpload
                               withIsChunkedTransfer:(BOOL)isChunkedTransfer;

- (void) receivedFriendChatMediaTransferCanceledWithId:(NSString *)userId
                                          withFriendId:(NSString *)friendId
                                        withCanceledBy:(NSString *)canceledBy
                                        withPacketId:(NSString *)packetId
                                        withFileName:(NSString *)fileName
                                        withIsUpload:(BOOL)isUpload
                               withIsChunkedTransfer:(BOOL)isChunkedTransfer;

- (void) receivedFriendChatMediaDownloadCompletedWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withFilePath:(NSString *)filePath withMessageType:(IMSDK_MessageType)messageType withTimeout:(NSInteger)timeout;

- (void) receivedGroupFileManifestUploadedWithId:(NSString *)groupId
                                    withPacketId:(NSString *)packetId
                                 withManifestUrl:(NSString *)url
                                 withMessageType:(IMSDK_MessageType)messageType
                                     withCaption:(NSString *)caption
                                 withWidthOrSize:(NSInteger)widthOrSize
                            withHeightOrDuration:(NSInteger)heightOrDuration;

-(void) receivedGroupIncomingChatMediaWithFriendId:(NSString *)friendId
                                       withGroupId:(NSString *)groupId
                                      withPacketId:(NSString *)packetId
                                      withFileName:(NSString *)fileName
                                    withMessgeType:(IMSDK_MessageType)messageType
                                   withMessageDate:(long long)date
                                       withCaption:(NSString *)caption
                                   withWidthOrSize:(NSInteger)widthOrSize
                              withHeightOrDuration:(NSInteger)heightOrDuration;

- (void) receivedGroupChatMediaTransferProgressWithFriendId:(NSString *)friendId
                                                withGroupId:(NSString *)groupId
                                               withPacketId:(NSString *)packetId
                                               withFileName:(NSString *)fileName
                                     withTransferPercentage:(double)transferPercentage
                                           withTransferType:(BOOL)isUpload;

- (void) receivedGroupChatMediaTransferFailedWithId:(NSString *)friendId
                                        withGroupId:(NSString *)groupId
                                       withPacketId:(NSString *)packetId
                                       withFileName:(NSString *)fileName
                                       withIsUpload:(BOOL)isUpload
                              withIsChunkedTransfer:(BOOL)isChunkedTransfer;

- (void) receivedGroupChatMediaTransferCanceledWithId:(NSString *)friendId
                                        withGroupId:(NSString *)groupId
                                       withCanceledBy:(NSString *)canceledBy
                                       withPacketId:(NSString *)packetId
                                       withFileName:(NSString *)fileName
                                       withIsUpload:(BOOL)isUpload
                              withIsChunkedTransfer:(BOOL)isChunkedTransfer;

- (void) receivedGroupChatMediaDownloadCompletedWithId:(NSString *)friendId
                                           withGroupId:(NSString *)groupId
                                          withPacketId:(NSString *)packetId
                                          withFilePath:(NSString *)filePath
                                       withMessageType:(IMSDK_MessageType)messageType;

- (void) receivedChatMediaTransferDirectoryErrorWithPath:(NSString *)directoryPath;
- (void) shouldUpdateAppSessionID;

- (void)receivedActivaeOrDeactivateUserAccountStatusWithId:(NSString *)userId withPacketId:(NSString *)packetId withIsAccountActivate:(BOOL)isAccountActivate withStatus:(BOOL)status;

- (void)receivedGetUserInfoReceivedWithId:(NSString *)userId withFriendID:(NSString *)friendId withPacketId:(NSString *)packetId withFriendName:(NSString *)friendName withFriendRingId:(NSString *)friendRingId withFriendProfileImageUrl:(NSString *)friendProfileImageUrl withFriendProfileType:(NSInteger)friendProfileType;

- (void)receivedGetUserInfoFailureWithId:(NSString *)userId withFriendID:(NSString *)friendId withPacketId:(NSString *)packetId;



- (void)receivedSyncConversationStatusWithId:(NSString *)userId withPacketId:(NSString *)packetId withSyncTime:(long long)syncTime withStatus:(BOOL)status;


- (void)receivedSyncFriendHistoryStatusWithId:(NSString *)userId withFriendID:(NSString *)friendId withPacketId:(NSString *)packetId withSyncTime:(long long)syncTime withDirection:(NSInteger)direction withStatus:(BOOL)status;

- (void)receivedSyncFriendHistoryMessageWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withMessageList:(NSArray *)messageList withOldestMessageDate:(long long)oldestMessageDate withDirection:(NSInteger)direction;

- (void)receivedSyncFriendHistoryMessageCompletedWithId:(NSString *)userId withFriendID:(NSString *)friendId withPacketId:(NSString *)packetId withDirection:(NSInteger)direction;


- (void)receivedSyncGroupHistoryStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withSyncTime:(long long)syncTime withDirection:(NSInteger)direction withStatus:(BOOL)status;

- (void) receivedSyncGroupHistoryMessageWithId:(NSString *)groupId withPacketId:(NSString *)packetId withMessageList:(NSArray *)messageList withActivityList:(NSArray *)activityList withOldestMessageDate:(long long)oldestMessageDate withDirection:(NSInteger)direction;

- (void)receivedyncGroupHistoryMessageCompletedWithId:(NSString *)groupId withPacketId:(NSString *)packetId withDirection:(NSInteger)direction;


//- (void) receivedFileTransferProgressWithFileId:(long long)fileID withFriendName:(long long)friendName withReceivedLength:(long long)receivedLength;
//
//- (void) receivedFileTransferCompletedWithFileId:(long long)fileID withFriendName:(long long)friendName withReceivedLength:(long long)receivedLength;
//
//- (void) receivedFileTransferCanceledWithFileId:(long long)fileID withFriendName:(long long)friendName withReceivedLength:(long long)receivedLength;
//
//- (void) receivedFileTransferFailedWithFileId:(long long)fileID withFriendName:(long long)friendName withReceivedLength:(long long)receivedLength;




//Live-stream-chat
- (void)receivedLiveStreamChatRegisterSuccessWithPublisherId: (NSString *)publisherId withPacketId: (NSString *)packetId;

- (void)receivedLiveStreamChatRegisterFailureWithPublisherId: (NSString *)publisherId withPacketId: (NSString *)packetId;

- (void)receivedLiveStreamChatRegistrationExpiredWithPublisherId: (NSString *)publisherId;

- (void)receivedLiveStreamChatDeliveredWithPublisherId: (NSString *)publisherId withPacketId: (NSString *)packetId;

- (void)receivedLiveStreamChatFailedToSendWithPublisherId: (NSString *)publisherId withPacketId: (NSString *)packetId;

- (void)receivedLiveStreamChatWithPublisherId: (NSString *)publisherId withSenderId: (NSString *)senderId withPacketId: (NSString *)packetId withMessageType: (IMSDK_MessageType)messageType withMessage: (NSString *)message withMessageDate: (long long)messageDate withSenderFullName: (NSString *)senderFullName;

- (void)receivedLiveStreamChatTypingWithPublisherId: (NSString *)publisherId withSenderId: (NSString *)senderId;

- (void)shouldCheckServerAddressForLiveStreamChatWithPublisherId: (NSString *)publisherId;

- (void)receivedLiveStreamChatBlockUserRequestStatusWithBlockedUserId:(NSString *)blockedUserId withPacketId: (NSString *)packetId;

- (void)receivedLiveStreamChatUserBlockedWithPublisherId:(NSString *)publisherId withBlockedUserId:(NSString *)blockedUserId;

@end
