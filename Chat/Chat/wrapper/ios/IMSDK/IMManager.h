//
//  IMManager.h
//  ringID
//
//  Created by Sumon on 11/2/15.
//  Copyright © 2015 IPVision Canada Inc. All rights reserved.
//

#import "IMApiStatus.h"
#import "IMReceivedMessageDelegate.h"
#import "IMPacketTimeId.h"
#import "IMFriendInformationModel.h"
#import "IMGroupInformationModel.h"
#import <Foundation/Foundation.h>

/**
 *  The class that contains all APIs to communicate with IM Server. Create one global instance of this class and use for all kinds of communication to IM Server. Each API call will return an IMApiStatus
 */
@interface IMManager : NSObject

//@property (nonatomic, strong) IMHandlerDelegate *chatHandler;

/**
 *  Instance to access ChatManager APIs
 *
 *  @return Shared instance of ChatManager
 */
+ (instancetype)sharedInstance;

/**
 *  Initialize ChatManager using self information.
 *
 *  @param delegate             Deletage to handle events
 *  @param userId               Self user id
 *  @param userName             Self username
 *  @param offlineIpAddress     Offline server address
 *  @param offlinePort          Offline server port
 *  @param authIpAddress        Auth server address
 *  @param authPort             Auth server port
 *  @param deviceType           Self device type. For iPhone it is IMSDK_DeviceType_iOS
 *  @param appSessionId         Session id of this session provided from auth
 *  @param appType              Corresponding app version of this application
 *  @param timeDifference       Timedifference saved in database. Application should save the time difference from timeDifferenceSynced delegate
 */
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
                  withPageIdList:(NSArray *)pageIdList;

/**
 *  Set offline server.
 *
 *  @param ipAddress Offline server address
 *  @param port      Offline server port
 */
- (void)setNewOfflineServerWithIP:(NSString *)ipAddress withPort:(NSInteger)port;

/**
 *
 *
 *  @param isAccountActivate    true for Activation, false for Deactivation
 *
 *  @return IMApiStatus
 */

- (IMApiStatus *) activateOrDeactivateUserAccountWithActivationSatus:(BOOL)isAccountActivate;


/**
 *  Request for offline messages. Should request for offline after login and network state change.
 *
 *  @param groupUpdateDate Group update date. Last update time of any group.
 *  @param blockUpdateDate Block or unblock update date. Last block or unblock time.
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendRequestForOfflineMessageAndGroupInformationWithGroupUpdateTime:(long long)groupUpdateDate withBlockUnblockUpdateDate:(long long)blockUpdateDate;

/**
 *  Initiate a chat session.
 *
 *  @param friendId    FriendId to chat with
 *  @param ipAddress   Register server address
 *  @param port        Register server port
 *  @param deviceType  Friend device type
 *  @param deviceToken Friend device token
 *  @param appType     Friend app type
 *  @param status      Presence status
 *  @param mood        Friend mood
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendRegisterRequstForFriendChatWithId:(NSString *)userId
                                          withUserName:(NSString *)userName
                                          withFriendId:(NSString *)friendId
                                        withFriendName:(NSString *)friendName
                                         withFriendUrl:(NSString *)friendUrl
                                          withChatServerIP:(NSString *)ipAddress
                                                  withPort:(NSInteger)port
                                            withDeviceType:(IMSDK_DeviceType)deviceType
                                           withDeviceToken:(NSString *)deviceToken
                                               withAppType:(NSInteger)appType
                                          withOnlineStatus:(IMSDK_Presence)status
                                                  withMood:(IMSDK_MoodType)mood
                                          withVoipPush:(NSInteger)voipPush
                                  withAuthRegisterTime:(long long)authRegisterTime
                                       withProfileType:(NSInteger)profileType;

/**
 *  Check whether a friend connection exists or not.
 *
 *  @param friendId FriendId to chat with
 *
 *  @return YES if exists, NO otherwise
 */
- (BOOL)isExistsFriendConnectionWithUserId:(NSString *)userId withFriendId:(NSString *)friendId;


/**
 *  Unregister a friend chat session.
 *
 *  @param friendId FriendId to chat with
 *  @param status   Presence status
 *  @param mood     Mood
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendUnregisterRequestForFriendChatWithId:(NSString *)userId withFriendId:(NSString *)friendId withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood;

/**
 *  Typing to a friend.
 *
 *  @param friendId FriendId to chat with
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendTypingForFriendChatWithId:(NSString *)userId withFriendId:(NSString *)friendId;

/**
 *  Initiate a group chat.
 *
 *  @param groupId   GroupId to chat
 *  @param ipAddress Register server address
 *  @param port      Register server port
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendRegisterRequestForGroupChatWithId:(NSString *)groupId withChatServerIP:(NSString *)ipAddress withPort:(NSInteger)port withAuthRegisterTime:(long long)authRegisterTime;

/**
 *  Update server port for a friend. This methond should be called after receiving new ip port from auth server
 *
 *  @param friendId      Corresnponding friendId
 *  @param serverAddress Server address from auth
 *  @param serverPort    Server port from auth
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)updateFriendRegisterServerWithId:(NSString *)userId withFriendId:(NSString *)friendId withServerAddress:(NSString *)serverAddress withServerPort:(NSInteger)serverPort;

/**
 *  Update presence of a friend. This methond should be called if presence or mood of a friend has been changed
 *
 *  @param friendId Corresponding friendId
 *  @param presence Presence of the friend
 *  @param mood     Mood of the friend
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)updateFriendPresenceId:(NSString *)userId withFriendId:(NSString *)friendId withPresence:(IMSDK_Presence)presence withMood:(IMSDK_MoodType)mood;

/**
 *  Send message to a friend.
 *
 *  @param packetId         Corresponding packetId
 *  @param friendId         FriendId to chat with
 *  @param message          Message to send
 *  @param messageType      Message Type
 *  @param date             Message date
 *  @param secretTime       Timeout for secret chat. For normal chat it should be 0
 *  @param isSecretVisible  Whether secret timer visible or not
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendFriendChatMessageWithPacketId:(NSString *)packetId
                                        withUserId:(NSString *)userId
                                          withFriendId:(NSString *)friendId
                                           withMessage:(NSString *)message
                                       withMessageType:(IMSDK_MessageType)messageType
                                       withMessageDate:(long long)date
                                        withSecretTime:(NSInteger)secretTime
                                   withIsSecretVisible:(BOOL)isSecretVisible;

/**
 *  Edit an existing friend message.
 *
 *  @param packetId         Corresponding packetId
 *  @param friendId         FriendId to chat with
 *  @param message          Message to send
 *  @param messageType      Message Type
 *  @param date             Message date
 *  @param secretTime       Timeout for secret chat. For normal chat it should be 0
 *  @param isSecretVisible  Whether secret timer visible or not
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendFriendChatEdittedMessageWithPacketId:(NSString *)packetId
                                               withUserId:(NSString *)userId
                                                 withFriendId:(NSString *)friendId
                                                  withMessage:(NSString *)message
                                              withMessageType:(IMSDK_MessageType)messageType
                                              withMessageDate:(long long)date
                                               withSecretTime:(NSInteger)secretTime
                                          withIsSecretVisible:(BOOL)isSecretVisible;

/**
 *  Should call this method if user reject a call
 *
 *  @param friendId Corresponding friendId
 *  @param message  Busy message
 *  @param date     Current time
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendFriendCallBusyMessageWithPacketId:(NSString *)packetId
                                            withUserId:(NSString *)userId
                                              withFriendId:(NSString *)friendId
                                           withMessage:(NSString *)message
                                       withMessageDate:(long long)date;

/**
 *  Should call this method to send call log to offline
 *  @param packetId PacketID
 *  @param friendId Corresponding friendId
 *  @param message  message
 *  @param date     Current time
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendFriendCallLogMessageWithPacketId:(NSString *)packetId
                                           withUserId:(NSString *)userId
                                          withFriendId:(NSString *)friendId
                                           withMessage:(NSString *)message
                                       withMessageDate:(long long)date;

/**
 *  A list of friend message is seen.
 *
 *  @param friendId             FriendId to chat with
 *  @param messageStatusList    List of IMMessageStatusModel
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendSeenForFriendChatWithId:(NSString *)userId withFriendId:(NSString *)friendId withMessageStatusList:(NSArray *)messageStatusList;

/**
 *  Delete a list of existing friend message.
 *
 *  @param friendId      FriendId to chat with
 *  @param packetIdArray Packet id list to delete
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendDeleteFriendMessageRequestWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketIdList:(NSArray *)packetIdArray withDeleteType:(NSInteger) deleteType;

/**
 *  Block a friend.
 *
 *  @param packetId   New generated packetId. Can be used from generatePacketId
 *  @param friendId   FriendId to chat with
 *  @param date       Block date. Date should be synced with server. (packetTime1970 can also be used from generated IMPacketTimeId)
 *  @param blockValue This will determine if need to add to db
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendBlockFriendRequestWithPacketId:(NSString*)packetId withUserId:(NSString *)userId withFriendId:(NSString *)friendId withBlockDate:(long long)date  withExtrayByte:(BOOL)blockValue;

/**
 *  Unblock a friend.
 *
 *  @param packetId   New generated packetId. Can be used from generatePacketId
 *  @param friendId   FriendId to chat with
 *  @param date       Unblock date. Date should be synced with server. (packetTime1970 can also be used from generated IMPacketTimeId)
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendUnblockFreindRequestWithPacketId:(NSString*)packetId withUserId:(NSString *)userId withFriendId:(NSString *)friendId withUnblockDate:(long long)date;

/**
 *  Request for friend history.
 *
 *  @param friendId  FriendId to chat with
 *  @param packetId  Corresponding packetId
 *  @param direction Up or down direction for history
 *  @param limit     Number of history message
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendRequestForFriendChatHistoryWithId:(NSString *)userId withFriendId:(NSString*)friendId withPacketId:(NSString*)packetId withDirection:(IMSDK_Scroll)direction withLimit:(int)limit;

/**
 *  Request for message status of existing messages.
 *
 *  @param friendId      FriendId to chat with
 *  @param packetIdArray Array of packetId
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendRequestForFriendMessageStatusWithId:(NSString *)userId withFriendId:(NSString*)friendId withPacketIdArray:(NSArray *)packetIdArray;

/**
 *  Check whether a group connection exists or not.
 *
 *  @param groupId GroupId to chat
 *
 *  @return YES if exists, NO otherwise
 */
- (BOOL)isExistsGroupConnectionWithGroupId:(NSString *)groupId;

/**
 *  Typing to a group.
 *
 *  @param groupId GroupId to chat
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendTypingForGroupChatwithId:(NSString *)groupId;

/**
 *  Unregister a group session.
 *
 *  @param groupId GroupId to chat
 *  @param status  Presence status
 *  @param mood    Mood
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendUnregisterRequestForGroupChatWithId:(NSString *)groupId withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood;

/**
 *  Send message to a group.
 *
 *  @param packetId    Corresponding packetId. Packet id should be generated from generatePacketId
 *  @param groupId     GroupId to chat
 *  @param message     Message to send
 *  @param messageType Message Type. Types of enum IMSDK_MessageType can be used
 *  @param date        Server synced current time. Can be used from generated IMPacketTimeId.
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendGroupChatMessageWithPacketId:(NSString*)packetId
                                          withGroupId:(NSString *)groupId
                                          withMessage:(NSString *)message
                                      withMessageType:(IMSDK_MessageType)messageType
                                      withMessageDate:(long long)date;

/**
 *  Edit an existing group message.
 *
 *  @param packetId    PacketId of previous message
 *  @param groupId     GroupId to chat
 *  @param message     Message to send
 *  @param messageType Types of enum IMSDK_MessageType can be used
 *  @param date        Time of previous message
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendGroupChatEditedMessageWithPacketId:(NSString *)packetId
                                                withGroupId:(NSString *)groupId
                                                withMessage:(NSString *)message
                                            withMessageType:(IMSDK_MessageType)messageType
                                            withMessageDate:(long long)date;

/**
 *  A group message is seen.
 *
 *  @param groupId  GroupId to chat
 *  @param friendId FriendId to chat with
 *  @param packetId Corresponding packetId
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendSeenForGroupChatWithId:(NSString *)groupId withPacketIdList:(NSArray *)packetIdList;

- (IMApiStatus *)sendRequestForGroupSeenListWithId:(NSString *)groupId withPacketId:(NSString *)packetId;

/**
 *  Delete a list of existing group message.
 *
 *  @param groupId       GroupId to chat
 *  @param packetIdArray Packet id list to delete
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendDeleteGroupMessageRequestWithId:(NSString *)groupId withPacketIdArray:(NSArray *)packetIdArray;

/**
 *  Add group member.
 *
 *  @param groupId    GroupId to chat
 *  @param memberList Member List
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendGroupMemberAddRequestWithId:(NSString *)groupId withMemberList:(NSArray *)memberList;

/**
 *  Remove group member.
 *
 *  @param groupId    GroupId to chat
 *  @param memberList Member List
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendGroupMemberRemoveRequestWithId:(NSString *)groupId withMemberList:(NSArray *)memberList;

/**
 *  Change status of some members.
 *
 *  @param groupId    GroupId to chat
 *  @param memberList Member List
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendGroupMemberStatusChangeRequestWithId:(NSString *)groupId withMemberList:(NSArray *)memberList;

/**
 *  Leave a group.
 *
 *  @param groupId GroupId to chat
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendLeaveGroupRequestWithId:(NSString *)groupId withIsHide:(BOOL)isHide;

/**
 *  Rename a group.
 *
 *  @param groupId GroupId to chat
 *  @param name    Group new name
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendGroupRenameWithId:(NSString*)groupId withGroupName:(NSString*)name;

/**
 *  Change profile picture of a group.
 *
 *  @param groupId GroupId to chat
 *  @param url     Group new pciture url
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendGroupProfilePicChangeWithId:(NSString*)groupId withImageUrl:(NSString*)url;

/**
 *  Create a group.
 *
 *  @param groupId    GroupId to chat
 *  @param name       Group name
 *  @param url        Group picture url
 *  @param memberList Group member list
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendCreateGroupWithId:(NSString*)groupId withGroupName:(NSString*)name withImageUrl:(NSString*)url withMemberList:(NSArray *)memberList;

/**
 *  Request for group chat history.
 *
 *  @param groupId   GroupId to chat
 *  @param packetId  Corresponding packetId
 *  @param direction Up or down direction for history
 *  @param limit     Number of message
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendRequestForGroupChatHistoryWithId:(NSString*)groupId withPacketId:(NSString*)packetId withDirection:(IMSDK_Scroll)direction withLimit:(int)limit;

/**
 *  Request for full group information with members.
 *
 *  @param groupId GroupId to chat
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)sendRequestForGroupInformationWithMembersWithId:(NSString*)groupId;

/**
 *  Stop sending pending message. After calling this method, message sending failed event will be delegated for each pending messages of that friend. Should call when no internet is detected
 *
 *  @param friendId Corresponding friendId
 *
 *  @return IMApiStatus
 */
- (IMApiStatus *)dontSendPendingMessagesWithId:(NSString *)userId withFriendId:(NSString *)friendId;

/**
 *  Get pending friend message list. This method should be called on closing of the application. Application should consider all these messages as pending/failed
 *
 *  @return Array of packetIds
 */
- (NSArray *)getPendingFriendMessageListWithId:(NSString *)userId;

/**
 *  Get pending group message list. This method should be called on closing of the application. Application should consider all these messages as pending/failed
 *
 *  @return Array of packetIds
 */
- (NSArray *)getPendingGroupMessageList;

/**
 *  Cleanup SDK. This method should be called on closing of the application
 *
 *  @param mood Mood of user while closing
 */
- (void)cleanUpWithMood:(IMSDK_MoodType)mood;

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
                withDirectoryPaths:(NSString *)directoryPath
                  withAutoDownload:(BOOL)autoDownload
                 withEncryptionKey:(NSString*)encryptionKey
                    withPageIdList:(NSArray *)pageIdList;

- (IMFriendInformationModel *)getFriendInformationWithId:(NSString *)userId withFriendId:(NSString *)friendId;

- (IMGroupInformationModel *)getGroupInformationWithId:(NSString *)groupId;

- (NSArray *)getRegisteredFriendListWithId:(NSString *)userId;

- (NSMutableArray *) getRegisteredGroupList;

- (IMApiStatus *)sendRegisterRequstForPublicRoomChatWithRoomId:(NSString *)roomId
                                              withMemberName:(NSString *)memberName
                                               withMemberUrl:(NSString *)memberUrl
                                                    withRingId:(NSString *)ringId;

- (void)enterPublicRoomChatScreenWithRoomId:(NSString *)roomId;

- (void)exitPublicRoomChatScreenWithRoomId:(NSString *)roomId;

- (IMApiStatus *)sendPublicRoomChatMessageWithPacketId:(NSString *)packetId
                                            withRoomId:(NSString *)roomId
                                       withMessageType:(IMSDK_MessageType)messageType
                                           withMessage:(NSString *)message
                                       withMessageDate:(long long)messageDate
                                        withMemberName:(NSString *)memberName
                                  withMemberProfileUrl:(NSString *)memberProfileUrl;

- (IMApiStatus *)sendPublicRoomChatEditedMessageWithPacketId:(NSString *)packetId
                                                  withRoomId:(NSString *)roomId
                                             withMessageType:(IMSDK_MessageType)messageType
                                                 withMessage:(NSString *)message
                                             withMessageDate:(long long)messageDate
                                              withMemberName:(NSString *)memberName
                                        withMemberProfileUrl:(NSString *)memberProfileUrl;

- (IMApiStatus *)sendRoomListRequestWithIndex:(int)startIndex withLimit:(int)limit;

- (IMApiStatus *)sendRoomListSearchRequestWithName:(NSString *)searchName withCountry:(NSString *)country withCategory:(NSString *)category withIndex:(int)startIndex withLimit:(int)limit;

- (IMApiStatus *)sendUnregisterRequestForPublicRoomChatWithRoomId:(NSString *)roomId;

- (IMApiStatus *)sendTypingForPublicRoomChatWithRoomId:(NSString *)roomId;

- (BOOL)isExistsPublicRoomChatConnectionWithRoomId:(NSString *)roomId;

- (IMApiStatus *)sendRequestForPublicChatRoomInformationWithRoomId:(NSString *)roomId;

- (IMApiStatus *)sendRoomChatHistoryRequestWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId withYear:(int)year withMonth:(int)month withDirection:(IMSDK_Scroll)direction withLimit:(int)limit;

- (IMApiStatus *)sendRoomListWithHistoryRequestWithIndex:(int)startIndex withLimit:(int)limit;

- (IMApiStatus *)sendRoomMemberListRequestWithRoomId:(NSString *)roomId withPagingState:(NSString *)pagingState withLimit:(int)limit;

- (IMApiStatus *)sendDeletePublicRoomChatDeleteRequestWithId:(NSString *)roomId withPacketIdList:(NSArray *)packetIdList;

- (IMApiStatus *)sendLikePublicRoomChatMessageRequestWithId:(NSString *)roomId withPacketId:(NSString *)packetId withMessageSenderId:(NSString *)messageSender;

- (IMApiStatus *)sendUnlikePublicRoomChatMessageRequestWithId:(NSString *)roomId withPacketId:(NSString *)packetId withMessageSenderId:(NSString *)messageSender;

- (IMApiStatus *)sendReportPublicRoomChatMessageRequestWithId:(NSString *)roomId withPacketId:(NSString *)packetId withMessageSenderId:(NSString *)messageSender withReportMessage:(NSString *)reportMessage;

- (IMApiStatus *)sendRequestForPublicRoomChatLikeMemberList:(NSString *)roomId withPacketId:(NSString *)packetId withLastLikerId:(NSString *)lastLikerId withLimit:(int) limit;

- (IMApiStatus *)sendRequestForPublicRoomChatCategoryListWithLastCategory:(NSString *)lastCategory withLimit:(int) limit;

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
                                                                     withMood:(IMSDK_MoodType)mood;

- (IMApiStatus *)sendUnregisterRequestForAnonymousFriendChatWithId:(NSString *)userId withFriendId:(NSString *)anonymousFriendId withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood;


- (IMApiStatus *)sendRequestForConversationListWithId:(NSString *)userId withType:(IMSDK_ConversationType)conversationType withStartIndex:(int)startIndex withLimit:(int)limit withId:(NSString *)friendGroupId;

- (IMApiStatus *)sendDeleteConversationListRequestWithId:(NSString *)userId withList:(NSArray *)conversationList;

- (IMApiStatus *)sendMarkConversationListRequestWithId:(NSString *)userId withList:(NSArray *)conversationList;

- (void) updatePasswordWithPassword:(NSString *)password;

- (IMNetworkDataModel *)getNetworkDataUsage;

- (long long)getTimeFromPacketIdWithId:(NSString *)packetId;

- (long long)getCurrentServerSyncedTime;

- (BOOL) checkInternetConnection;

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
        withIsSecretVisible:(BOOL)isSecretVisible;

- (BOOL)downloadFriendChatMediaWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withManifestUrl:(NSString *)manifestUrl withMessageType:(IMSDK_MessageType)messageType withTimeout:(NSInteger)timeout;

- (BOOL)acceptChatMediaWithPacketId:(NSString *)packetId;

- (BOOL)sendGroupChatMediaWithId:(NSString *)groupId
                    withPacketId:(NSString *)packetId
                 withMessageType:(IMSDK_MessageType)messageType
                    withFilePath:(NSString *)filePath
                     withCaption:(NSString *)caption
                 withWidthOrSize:(NSInteger)widthOrSize
             witHeightOrDuration:(NSInteger)heightOrDuration
                 withMessageDate:(long long)date;

- (BOOL)downloadGroupChatMediaWithId:(NSString *)groupId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withManifestUrl:(NSString *)manifestUrl withMessageType:(IMSDK_MessageType)messageType;

- (NSArray *)getPendingChatMediaListWithType:(IMSDK_ConversationType)conversationType withUploadingMediaList:(BOOL)uploadingMediaList withIsChunkedTransfer:(BOOL)isChunkedTransfer;

- (BOOL)isChatMediaTransferInProgressWithPacketId:(NSString *)packetId;

- (void) cancelChatMediaTransferWithId:(NSString *)packetId;

- (void) updateAppSessionIDWithAppSessionId:(NSString *)appSessionId;

- (void)setLogEnabledWithIsEnabled:(BOOL)isEnabled;

- (NSString *) generateGroupId;

- (void) addPageIdWithId:(NSString *)pageId;

- (void) removePageIdWithId:(NSString *)pageId;


/**
 *  Generate a unique packet id.
 *
 *  @return IMPacketTimeId
 */
- (IMPacketTimeId *) generatePacketIdWithUserId:(NSString *)userId;

- (IMPacketTimeId *) generatePacketIdWithTime:(long long)timeMili withUserId:(NSString *)userId;

- (void)setLogfileWithFileName:(NSString *)fileName;

/**
 *  Get the current version of native library.
 *
 *  @return IMApiStatus
 */
- (NSString *) version;

//Live-stream-chat
- (IMApiStatus *)sendRegisterRequestForLiveStreamChatWithPublisherId:(NSString *)publisherId
                                        withRegisterServerAddress:(NSString *)registerServerAddress
                                        withRegisterServerPort:(NSInteger)registerServerPort
                                        withFullName:(NSString *)fullName;

- (IMApiStatus *)sendUnregisterRequestForLiveStreamChatWithPublisherId:(NSString *)publisherId 
                                          withOnlineStatus:(IMSDK_Presence)onlineStatus
                                          withMood:(IMSDK_MoodType)onlineMood;

- (IMApiStatus *)sendTypingForLiveStreamChatWithPublisherId:(NSString *)publisherId;

- (IMApiStatus *)sendLiveStreamChatMessageWithPacketId:(NSString *)packetId
                                          withPublisherId:(NSString *)publisherId
                                       withMessageType:(IMSDK_MessageType)messageType
                                           withMessage:(NSString *)message
                                       withMessageDate:(long long)messageDate;

- (IMApiStatus *)blockUserFromLiveStreamChatWithViewerId:(NSString *)viewerId
                                            withPacketId:(NSString *)packetId;


- (IMApiStatus *)getSyncedConversationWithId:(NSString *)userId withPacketId:(NSString *)packetId withLastSyncedTime:(long long)lastSyncedTime;

- (IMApiStatus *)getSyncedFriendHistoryMessageWithId:(NSString *)userId withFrinedId:(NSString *)friendId withPacketId:(NSString *)packetId withLastSyncedTime:(long long)lastSyncedTime withLimit:(NSInteger)limit withDirection:(NSInteger)direction;

- (IMApiStatus *)getSyncedGroupHistoryMessageWithId:(NSString *)userId withGroupId:(NSString *)groupId withPacketId:(NSString *)packetId withLastSyncedTime:(long long)lastSyncedTime withLimit:(NSInteger)limit withDirection:(NSInteger)direction;

- (IMApiStatus *)getMyGroupListPagingWithId:(NSString *)userId withPacketId:(NSString *)packetId withPivotId:(NSString *)pivotId withLimit:(NSInteger)limit withDirection:(NSInteger)direction;

@end


@interface InternetChecker : NSObject

/**
 *  IP list file path
 */
@property (nonatomic, strong) NSString *ipListFilePath;

/**
 *  Instance to access InternetChecker APIs
 *
 *  @return Shared instance of InternetChecker
 */
+ (instancetype)sharedInstance;

/**
 *  InternetChecker Constructor
 *
 *  @param ipListFilePath  IP list file path
 *
 *  @return InternetChecker instance
 */
- (void)initWithIpListFilePath:(NSString*)ipListFilePath;

/**
 *  Check internet connection
 *  @return True if internet available
 */
- (BOOL) checkInternetConnection;

@end


@interface DataEncryption : NSObject

/**
 *  Instance to access DataEncryption APIs
 *
 *  @return Shared instance of DataEncryption
 */
+ (instancetype)sharedInstance;

/**
 *  Encrypt data
 *
 *  @param data - data bytes
 *
 *  @param key - key bytes
 *
 *  @return encrypted data bytes
 */
- (NSData *)encryptDataWithData:(NSData *)data withKey:(NSData *)key withStartIndex:(NSInteger)startIndex;

/**
 *  Decrypt data
 *
 *  @param data - encrypted data bytes
 *
 *  @param key - key bytes
 *
 *  @return decrypted data bytes
 */
- (NSData *)DecryptDataWithData:(NSData *)data withKey:(NSData *)key withStartIndex:(NSInteger)startIndex;

- (NSString *)getSessionlessKeyWithServerAddress:(NSString *)serverAddress withRingId:(NSString *)ringId;


@end