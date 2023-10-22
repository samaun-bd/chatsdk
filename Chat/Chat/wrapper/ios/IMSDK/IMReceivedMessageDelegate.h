//
//  IMReceivedMessageDelegate.h
//  SocketFrameworkApp
//
//  Created by Mac 15 on 2/11/15.
//  Copyright (c) 2015 Mac 15. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "IMSDKTypes.h"
#import "IMNetworkDataModel.h"
/**
 *  Event handler delegate.
 */
@protocol IMReceivedMessageDelegate <NSObject>

@optional


/**
 *  Handle friend chat register success.
 *
 *  @param friendId FriendId to chat with
 *  @param date     Server date
 */
- (void)receivedFriendChatBindPortWithId:(NSString *)userId withFriendId:(NSString *)friendId withDate:(long long)date withPacketId:(NSString *)packetId withIsAnonymous:(BOOL)isAnonymous;

/**
 *  Handle friend chat register failure.
 *
 *  @param friendId FriendId to chat with
 */
- (void)receivedFriendChatRegisterFailureWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withIsAnonymous:(BOOL)isAnonymous;

/**
 *  Handle friend chat session expired.
 *
 *  @param friendId FriendId to chat with
 */
- (void)receivedFriendChatRegistrationExpiredWithId:(NSString *)userId withFriendId:(NSString *)friendId withIsAnonymous:(BOOL)isAnonymous;

/**
 *  Handle friend unregistered. Can be delegated when a friend sends unregister.
 *
 *  @param friendId FriendId to chat with
 *  @param status   Presence status
 *  @param mood     Mood
 */
- (void)receivedFriendChatUnregisterWithId:(NSString *)userId withFriendId:(NSString *)friendId withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood withIsAnonymous:(BOOL)isAnonymous withProfileType:(NSInteger)profileType;

/**
 *  Handle new friend chat received.
 *
 *  @param friendId         FriendId to chat with
 *  @param packetId         Corresponding packetId
 *  @param messageType      Message type
 *  @param secretTime       Timeout for secret chat. For normal chat it should be 0
 *  @param message          Message to send
 *  @param date             Server date
 *  @param isSecretVisible  Whether secret timer is visible
 */
- (void)receivedFriendChatMessageWithSenderId:(NSString *)senderId
                               withReceiverId:(NSString*)receiverId
                                 withPacketId:(NSString *)packetId
                              withMessageType:(IMSDK_MessageType)messageType
                               withSecretTime:(NSInteger)secretTime
                                  withMessage:(NSString *)message
                                     withDate:(long long)date
                          withIsSecretVisible:(BOOL)isSecretVisible
                             withIsFromOnline:(BOOL)isFromOnline
                              withIsAnonymous:(BOOL)isAnonymous;

/**
 *  Handle friend chat edited.
 *
 *  @param friendId         FriendId to chat with
 *  @param packetId         Corresponding packetId
 *  @param messageType      Message type
 *  @param secretTime       Timeout for secret chat. For normal chat it should be 0
 *  @param message          Message to send
 *  @param date             Server date
 *  @param isSecretVisible  Whether secret timer is visible
 */
- (void)receivedFriendChatEdittedMessageWithSenderId:(NSString *)senderId
                                      withReceiverId:(NSString *)receiverId
                                        withPacketId:(NSString *)packetId
                                     withMessageType:(IMSDK_MessageType)messageType
                                      withSecretTime:(NSInteger)secretTime
                                         withMessage:(NSString *)message
                                            withDate:(long long)date
                                 withIsSecretVisible:(BOOL)isSecretVisible
                                     withIsAnonymous:(BOOL)isAnonymous;


/**
 *  Received friend message history. This will contain both sent and received message.
 *
 *  @param senderId        Userid who sent
 *  @param packetId        Corresponding packetId
 *  @param messageType     Message type
 *  @param secretTime      Timeout for secret chat. For normal chat it should be 0
 *  @param message         Message
 *  @param date            Message date
 *  @param isSecretVisible Whether secret timer is visible
 *  @param messageStatus   Message status
 */
- (void) receivedFriendHistoryMessageWithId:(NSString *)userId withFriendId:(NSString *)friendId withMessageList:(NSArray *)messageList;

/**
 *  Handle delivered friend chat.
 *
 *  @param friendId FriendId to chat with
 *  @param packetId Corresponding packetId
 */
- (void)receivedFriendChatDeliveredWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withIsAnonymous:(BOOL)isAnonymous withIsEdited:(BOOL)isEdited withIsFromOnline:(BOOL)isFromOnline;

/**
 *  Handle seen friend chat.
 *
 *  @param friendId             FriendId to chat with
 *  @param messageStatusList    List of IMMessageStatusModel
 */
- (void)receivedFriendChatSeenWithId:(NSString *)userId withFriendId:(NSString *)friendId withMessageStatusList:(NSArray *)messageStatusList withIsAnonymous:(BOOL)isAnonymous;

/**
 *  Seen packet is sent successfully
 *
 *  @param friendId     FriendId to chat with
 *  @param packetIdList Corresponding packetId
 */
- (void)receivedFriendChatSeenConfirmationWithId:(NSString *)userId withFriendId:(NSString *)friendId withMessageStatusList:(NSArray *)messageStatusList withIsAnonymous:(BOOL)isAnonymous;

/**
 *  Handle friend chat failed to send.
 *
 *  @param friendId FriendId to chat with
 *  @param packetId Corresponding packetId
 */
- (void)receivedFailedToSendFriendChatWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withIsAnonymous:(BOOL)isAnonymous;

/**
 *  Handle friend typing.
 *
 *  @param friendId FriendId to chat with
 */
- (void)receivedFriendChatTypingWithId:(NSString *)userId withFriendId:(NSString *)friendId withIsAnonymous:(BOOL)isAnonymous;

/**
 *  Handle deleted message by friend.
 *
 *  @param friendId     FriendId to chat with
 *  @param packetIdList Corresponding packetIdList
 */
- (void)receivedFriendChatDeleteWithSenderId:(NSString *)senderId withFriendId:(NSString *)friendId withPacketIdList:(NSArray *)packetIdList withIsAnonymous:(BOOL)isAnonymous;

/**
 *  Handle friend chat delete confirmation.
 *
 *  @param friendId FriendId to chat with
 *  @param packetId Corresponding packetId
 */
- (void)receivedFriendChatDeleteRequestStatusWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withPacketIds:(NSArray *)packetIds withIsAnonymous:(BOOL)isAnonymous withStatus:(BOOL)status withDeleteType:(NSInteger)deleteType;

/**
 *  Received message status of requested message list.
 *
 *  @param messageStatusList Packet id list with status and time
 */
- (void) receivedFriendMessageStatusWithId:(NSString *)userId withFriendId:(NSString *)friendId withMessageStatusList:(NSArray *)messageStatusList;

/**
 *  You are blocked by a friend.
 *
 *  @param friendId   FriendId to chat with
 *  @param blockValue Where need to add to db for block list or not
 */
- (void)receivedBlockFriendWithBlockerId:(NSString *)blockerId withBlockedId:(NSString *)blockedId withBlockValue:(BOOL)blockValue;

/**
 *  You are unblocked by a friend.
 *
 *  @param friendId FriendId to chat with
 */
- (void)receivedUnblockFriendWithUnblockerId:(NSString *)unblockerId withUnblockedId:(NSString *)unblockedId;

/**
 *  Block or unblock request is confirmed.
 *
 *  @param friendId FriendId to chat with
 */
- (void)receivedBlockUnblockRequestStatusWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withStatus:(BOOL)status withIsBlockRequest:(BOOL)isBlockRequest;

/**
 *  Handle group registration success.
 *
 *  @param groupId Group id to chat with
 *  @param date    Server date
 */
- (void)receivedGroupChatBindPortWithId:(NSString *)groupId withDate:(long long)date withPacketId:(NSString *)packetId;

/**
 *  Handle group chat register failure.
 *
 *  @param groupId Group id to chat with
 */
- (void)receivedGroupChatRegisterFailureWithId:(NSString *)groupId withPacketId:(NSString *)packetId;

/**
 *  Hanlde group chat session expired.
 *
 *  @param groupId Group id to chat with
 */
- (void)receivedGroupChatRegistrationExpiredWithId:(NSString *)groupId withLastActivityTime:(long long)lastActivityTime;

/**
 *  Handle new group chat received.
 *
 *  @param groupId     Group id to chat with
 *  @param friendId    FriendId to chat with
 *  @param packetId    Corresponding packetId
 *  @param messageType Message type
 *  @param message     Message to send
 *  @param date        Server date
 */
- (void)receivedGroupChatMessageWithId:(NSString *)groupId
                          withFriendId:(NSString *)friendId
                          withPacketId:(NSString *)packetId
                       withMessageType:(IMSDK_MessageType)messageType
                           withMessage:(NSString *)message
                              withDate:(long long)date
                      withIsFromOnline:(BOOL)isFromOnline;

/**
 *  Handle deleted group message.
 *
 *  @param groupId      Group id to chat with
 *  @param friendId     Friend who deleted the message
 *  @param packetIdList Deleted packet id
 */
- (void)receivedGroupChatMessageDeletedWithId:(NSString *)groupId withFriendId:(NSString *)friendId withPacketIdList:(NSArray *)packetIdList;

/**
 *  Group message deleted successfully
 *
 *  @param groupId  Group id to chat with
 *  @param packetId Deleted packet id
 */
- (void)receivedGroupChatMessageDeleteRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withPacketIds:(NSArray *)packetIds withStatus:(BOOL)status;

/**
 *  Handle group chat edited message.
 *
 *  @param groupId     Group id to chat with
 *  @param friendId    FriendId to chat with
 *  @param packetId    Corresponding packetId
 *  @param messageType Message type
 *  @param message     Message to send
 *  @param date        Server date
 */
- (void)receivedGroupChatEdittedMessageWithId:(NSString *)groupId
                                 withFriendId:(NSString *)friendId
                                 withPacketId:(NSString *)packetId
                              withMessageType:(IMSDK_MessageType)messageType
                                  withMessage:(NSString *)message
                                     withDate:(long long)date;

/**
 *  Handle delivered a group chat to group member.
 *
 *  @param groupId  Group id to chat with
 *  @param friendId FriendId to chat with
 *  @param packetId Corresponding packetId
 */
- (void)receivedGroupChatDeliveredWithId:(NSString *)groupId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId;

/**
 *  Group chat sent to server.
 *
 *  @param groupId  Group id to chat with
 *  @param packetId Corresponding packetId
 */
- (void)receivedGroupChatSentWithId:(NSString *)groupId withPacketId:(NSString *)packetId withIsEdited:(BOOL)isEdited; // No Need

/**
 *  Group chat seen by a group member.
 *
 *  @param groupId  Group id to chat with
 *  @param friendId FriendId to chat with
 *  @param packetId Corresponding packetId
 */
- (void)receivedGroupChatSeenWithId:(NSString *)groupId withPacketIdList:(NSArray *)packetIdList;

- (void)receivedRequestedGroupSeenListWithId:(NSString *)groupId withPacketId:(NSString *)packetId withMemberList:(NSArray *)memberList;
/**
 *  Group chat sending failed.
 *
 *  @param groupId  Group id to chat with
 *  @param packetId Corresponding packetId
 */
- (void)receivedFailedToSendGroupChatWithId:(NSString *)groupId withPacketId:(NSString *)packetId;

/**
 *  A group member is started typing.
 *
 *  @param groupId  Group id to chat with
 *  @param friendId FriendId to chat with
 */
- (void)receivedGroupChatTypingWithId:(NSString *)groupId withFriendId:(NSString *)friendId;

/**
 *  Handle group member removed or left.
 *
 *  @param groupId    Group id to chat with
 *  @param friendId   FriendId to chat with
 *  @param memberList Member list of the group
 */
- (void)receivedGroupMemberLeaveRemoveWithId:(NSString *)groupId withFriendId:(NSString *)friendId withMemberList:(NSArray *)memberList withPacketId:(NSString *)packetId withIsHide:(BOOL)isHide;

/**
 *  Group member remove or leave request confirmed.
 *
 *  @param groupId  Group id to chat with
 *  @param packetId Corresponding packetId
 */
- (void)receivedGroupMemberRemoveLeaveRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status withIsHide:(BOOL)isHide;

/**
 *  A lsit of new members are added to a group.
 *
 *  @param groupId    Group id to chat with
 *  @param friendId   FriendId to chat with
 *  @param memberList Member list of the group
 */
- (void)receivedGroupMemberAddWithId:(NSString *)groupId withFriendId:(NSString *)friendId withMemberList:(NSArray *)memberList withPacketId:(NSString *)packetId;

/**
 *  Group member add request confirmed.
 *
 *  @param groupId  Group id to chat with
 *  @param packetId Corresponding packetId
 */
- (void)receivedGroupMemberAddRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status;

/**
 *  Status changed of some group members.
 *
 *  @param groupId    Group id to chat with
 *  @param friendId   FriendId to chat with
 *  @param memberList Member list of the group
 */
- (void)receivedGroupMemberStatusChangeWithId:(NSString *)groupId withFriendId:(NSString *)friendId withMemberList:(NSArray *)memberList withPacketId:(NSString *)packetId;

/**
 *  Group member status successfully changed.
 *
 *  @param groupId  Group id to chat with
 *  @param packetId Corresponding packetId
 */
- (void)receivedGroupMemberStatusChangeRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status;

/**
 *  Received group message history. This will contain both sent and received message.
 *
 *  @param groupId     Group id to chat with
 *  @param senderId    Userid who sent
 *  @param packetId    Corresponding packetId
 *  @param messageType Message type
 *  @param message     Message to send
 *  @param date        Message date
 */
- (void) receivedGroupHistoryMessageWithId:(NSString *)groupId withMessageList:(NSArray *)messageList;

/**
 *  Received full member information of the requested group.
 *
 *  @param groupId    Group id to chat with
 *  @param name       Group name
 *  @param url        Profile picture url
 *  @param memberList Member list
 */
- (void) receivedGroupInformationWithmembersWithId:(NSString *)groupId withGroupName:(NSString *)name withGroupUrl:(NSString*)url withMemberList:(NSArray *)memberList;

/**
 *  Received group acitivity list.
 *
 *  @param activityList Group activity list
 */
- (void) receivedGroupActivityWithActivityList:(NSArray *)activityList;

/**
 *  Received group list with basic group informations.
 *
 *  @param groupList My group list
 */
- (void) receivedMyGroupListWithList:(NSArray *)groupList;

/**
 *  Received group list paging with basic group informations.
 *
 *  @param groupList My group list
 *  @param withPivotid requested pivotId
 *  @param direction request direction
 */
- (void) receivedMyGroupListPagingWithList:(NSArray *)groupList withPivotid:(NSString *)pivotId withDirection:(NSInteger)direction;

/**
 *  Received group list receiving completed.
 */
- (void) receivedMyGroupListCompleted;

/**
 *  Create group request successful.
 *
 *  @param groupId Group id to chat with
 */
- (void) receivedGroupCreateRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status;

/**
 *  Group name or profile pic url change successful.
 *
 *  @param groupId  Group id to chat with
 *  @param packetId Corresponding packetId
 */
- (void) receivedGroupInformationChangeRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status;

/**
 *  Group name is changed.
 *
 *  @param groupId  Group id to chat with
 *  @param friendId FriendId who changed
 *  @param name     Group name
 */
- (void) receivedGroupNameUpdateWithId:(NSString *)groupId WithFriendId:(NSString *)friendId withGroupName:(NSString *)name withPacketId:(NSString *)packetId;

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
- (void) receivedGroupInformationWithMembersRequestStatusWithGroupId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status;
- (void) receivedFriendHistoryCompletedWithId:(NSString *)userId withFriendId:(NSString *)friendId withDirection:(IMSDK_Scroll)direction;
- (void) receivedFriendHistoryMessageRequestStatusWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withStatus:(BOOL)status;
- (void) receivedGroupHistoryMessageRequestStatusWithGroupId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status;
- (void) receivedGroupInformationActivityFromHistoryMessageWithGroupId:(NSString *)groupId WithActivityList:(NSArray *)activityList withDirection:(IMSDK_Scroll) direction;
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
                               withIsChunkedTransfer:(BOOL) isChunkedTransfer;

- (void) receivedFriendChatMediaTransferCanceledWithId:(NSString *)userId
                                              withFriendId:(NSString *)friendId
                                        withCanceledBy:(NSString *)canceledBy
                                        withPacketId:(NSString *)packetId
                                        withFileName:(NSString *)fileName
                                        withIsUpload:(BOOL)isUpload
                               withIsChunkedTransfer:(BOOL) isChunkedTransfer;

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

/**
 *  Application should update app session id
 */
- (void) shouldUpdateAppSessionID;

/**
 *  Application should check friend status from auth.
 *
 *  @param friendId FriendId to chat with
 */
- (void)shouldCheckFriendPresenceWithId:(NSString *)userId withFriendId:(NSString *)friendId withIsAnonymous:(BOOL)isAnonymous withProfileType:(NSInteger)profileType;

/**
 *  Application should check for new server address for friend from auth.
 *
 *  @param friendId FriendId to chat with
 */
- (void)shouldCheckServerAddressForFriendWithId:(NSString *)userId withFriendId:(NSString *)friendId withIsAnonymous:(BOOL)isAnonymous;

/**
 *  Application should check for new server address for group from auth.
 *
 *  @param groupId Group id to chat with
 */
- (void)shouldCheckServerAddressForGroupWithId:(NSString *)groupId;

/**
 *  Application should check for new offline server address from auth.
 */
- (void)shouldCheckOfflineServerAddress;

- (void)shouldUpdateUserPassword;

/**
 *  Application should save this time difference into database and use it while initializing SDK next time.
 *
 *  @param timeDifference time difference with server
 */
- (void)receivedServerTimeSyncedWithTimeDifference:(long long)timeDifference;

/**
 *  Group profile pic changed.
 *
 *  @param groupId  Group id to chat with
 *  @param friendId FriendId who changed
 *  @param url      Group profile picture url
 */
- (void) receivedGroupProfilePicUpdateWithId:(NSString *)groupId WithFriendId:(NSString *)friendId withUrl:(NSString *)url withPacketId:(NSString *)packetId;

///**
// *  File transfer progress
// *
// *  @param fileId         Corresponding fileId
// *  @param friendId       Corresponding friendId
// *  @param receivedLength Length received
// */
//- (void) receivedFileTransferProgressWithFileId:(long long)fileId withFriendId:(long long)friendId withReceivedLength:(long long)receivedLength;
//
///**
// *  File transfer is completed
// *
// *  @param fileId         Corresponding fileId
// *  @param friendId       Corresponding friendId
// *  @param receivedLength Length received
// */
//- (void) receivedFileTransferCompletedWithFileId:(long long)fileId withFriendId:(long long)friendId withReceivedLength:(long long)receivedLength;
//
///**
// *  File transfer canceled
// *
// *  @param fileId         Corresponding fileId
// *  @param friendId       Corresponding friendId
// *  @param receivedLength Length received
// */
//- (void) receivedFileTransferCanceledWithFileId:(long long)fileId withFriendId:(long long)friendId withReceivedLength:(long long)receivedLength;
//
///**
// *  File transfer failed
// *
// *  @param fileId         Corresponding fileId
// *  @param friendId       Corresponding friendId
// *  @param receivedLength Length received
// */
//- (void) receivedFileTransferFailedWithFileId:(long long)fileId withFriendId:(long long)friendId withReceivedLength:(long long)receivedLength;

/**
 *
 *
 *  @param userId
 *  @param packetId
 *  @param isAccountActivate
 *  @param status
 */
- (void)receivedActivaeOrDeactivateUserAccountStatusWithId:(NSString *)userId withPacketId:(NSString *)packetId withIsAccountActivate:(BOOL)isAccountActivate withStatus:(BOOL)status;

/**
 *
 *
 *  @param userId
 *  @param friendId
 *  @param packetId
 *  @param friendName
 *  @param friendProfileImageUrl
 *  @param friendRingId
 *  @param friendProfileType
 */
- (void)receivedGetUserInfoReceivedWithId:(NSString *)userId withFriendID:(NSString *)friendId withPacketId:(NSString *)packetId withFriendName:(NSString *)friendName withFriendRingId:(NSString *)friendRingId withFriendProfileImageUrl:(NSString *)friendProfileImageUrl withFriendProfileType:(NSInteger)friendProfileType;

/**
 *
 *
 *  @param userId
 *  @param friendId
 *  @param packetId
 */
- (void)receivedGetUserInfoFailureWithId:(NSString *)userId withFriendID:(NSString *)friendId withPacketId:(NSString *)packetId;


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


- (void)receivedSyncConversationStatusWithId:(NSString *)userId withPacketId:(NSString *)packetId withSyncTime:(long long)syncTime withStatus:(BOOL)status;


- (void)receivedSyncFriendHistoryStatusWithId:(NSString *)userId withFriendID:(NSString *)friendId withPacketId:(NSString *)packetId withSyncTime:(long long)syncTime withDirection:(NSInteger)direction withStatus:(BOOL)status;

- (void)receivedSyncFriendHistoryMessageWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withMessageList:(NSArray *)messageList withOldestMessageDate:(long long)oldestMessageDate withDirection:(NSInteger)direction;

- (void)receivedSyncFriendHistoryMessageCompletedWithId:(NSString *)userId withFriendID:(NSString *)friendId withPacketId:(NSString *)packetId withDirection:(NSInteger)direction;


- (void)receivedSyncGroupHistoryStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withSyncTime:(long long)syncTime withDirection:(NSInteger)direction withStatus:(BOOL)status;

- (void)receivedSyncGroupHistoryMessageWithId:(NSString *)groupId withPacketId:(NSString *)packetId withMessageList:(NSArray *)messageList withActivityList:(NSArray *)activityList withOldestMessageDate:(long long)oldestMessageDate withDirection:(NSInteger)direction;

- (void)receivedyncGroupHistoryMessageCompletedWithId:(NSString *)groupId withPacketId:(NSString *)packetId withDirection:(NSInteger)direction;

@end
