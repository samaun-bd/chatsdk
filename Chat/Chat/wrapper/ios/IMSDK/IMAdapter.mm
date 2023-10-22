//
//  IMAdapter.m
//  ringID
//
//  Created by Sumon on 11/2/15.
//  Copyright © 2015 IPVision Canada Inc. All rights reserved.
//

#include <vector>
#include "Chat.h"
#include "MemberDTO.h"
#include "ConversationDTO.h"
#import "IMAdapter.h"
#import "IMGroupMemberModel.h"
#import "IMConversationModel.h"
#import "IMHandlerAdapter.h"
#import "InternetChecker.h"
#import "DataEncryption.h"

static imsdk::Chat *chatManager;
static internetchecker::InternetChecker *internetChecker;
static ipvsdk::security::DataEncryption *dataEncryption;
//static ChatEventHandler *eventHandler;

@implementation IMAdapter


+ (void)initiateChatWithUserId:(NSString *)userId
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
    std::string userNameString((userName!=nil)?[userName UTF8String]:"");
    std::string offlineIpAddressSting((offlineIpAddress!=nil)?[offlineIpAddress UTF8String]:"");
    std::string authIpAddressString((authIpAddress!=nil)?[authIpAddress UTF8String]:"");
    std::string appSessionIdString((appSessionId!=nil)?[appSessionId UTF8String]:"");
    std::string encryptionKeyString((encryptionKey!=nil)?[encryptionKey UTF8String]:"");
    
    UserIdentity userIdValue((userId!=nil)?[userId longLongValue]:0);
    std::vector<std::string> vdirectoryPaths;
    for (NSString *directoryPath in directoryPaths)
    {
        std::string sDirectoryPath([directoryPath UTF8String]);
        vdirectoryPaths.push_back(sDirectoryPath);
    }
    std::string baseUploadUrlString((baseUploadUrl!=nil)?[baseUploadUrl UTF8String]:"");
    std::string baseDownloadUrlString((baseDownloadUrl!=nil)?[baseDownloadUrl UTF8String]:"");
    
    int pageIdCount = (int)pageIdList.count;
    std::set<UserIdentity> pageIds;
    
    for (int i=0; i<pageIdCount; i++)
    {
        NSString* pageId = [pageIdList objectAtIndex:i];
        UserIdentity pageIdValue((pageId!=nil)?[pageId longLongValue]:0);
        pageIds.insert(pageIdValue);
    }
    
    if (chatManager == nil)
    {
//        eventHandler = make_shared<ChatEventHandler>();
        chatManager = new imsdk::Chat(userIdValue, userNameString, offlineIpAddressSting, (int)offlinePort, authIpAddressString, (int)authPort, (int)deviceType, appSessionIdString, (int)appVersion, timeDifference, vdirectoryPaths, baseUploadUrlString,baseDownloadUrlString,autoDownload, encryptionKeyString, appType, pageIds);
        chatManager->registerEventHandler(std::make_shared<ChatEventHandler>());
    }
    else
    {
        chatManager->reinitialize(userIdValue, userNameString, offlineIpAddressSting, (int)offlinePort, authIpAddressString, (int)authPort, (int)deviceType, appSessionIdString, (int)appVersion, timeDifference, vdirectoryPaths, autoDownload, encryptionKeyString, pageIds);
    }
}


+ (IMApiStatus *)activateOrDeactivateUserAccountWithActivationSatus:(BOOL)isAccountActivate
{
    imsdk::ApiStatus apiStatus = chatManager->activateOrDeactivateUserAccount(isAccountActivate);

    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}


+ (void)setNewOfflineServerWithIP:(NSString *)ipAddress
                         withPort:(NSInteger)port
{
    std::string ipAddressSting([ipAddress UTF8String]);
    chatManager->setOfflineServer(ipAddressSting, (int)port);
}


+ (IMApiStatus *)sendRequestForOfflineMessageAndGroupInformationWithGroupUpdateTime:(long long)groupUpdateDate withBlockUnblockUpdateDate:(long long)blockUpdateDate
{
    if(chatManager != nil)
    {
        
        imsdk::ApiStatus apiStatus = chatManager->requestForOffline(groupUpdateDate, blockUpdateDate);
        return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];

    }
    else
    {
        //NSLog(@"Error in sendRequestForOfflineMessageAndGroupInformation :: Chat SDK not initialized!");
        return nil;
    }
}


+ (IMApiStatus *)sendRegisterRequstForFriendChatWithId:(NSString *)userId
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
                                       withProfileType:(NSInteger)profileType
{
    if(chatManager != nil)
    {
        std::string ipAddressSting((ipAddress!=nil)?[ipAddress UTF8String]:"");
        std::string deviceTokenSting((deviceToken!=nil)?[deviceToken UTF8String]:"");
        UserIdentity userIdValue((userId!=nil)?[userId longLongValue]:0);
        std::string userNameString((userName!=nil)?[userName UTF8String]:"");
        UserIdentity friendIdValue((friendId!=nil)?[friendId longLongValue]:0);
        std::string friendNameString((friendName!=nil)?[friendName UTF8String]:"");
        std::string friendUrlString((friendUrl!=nil)?[friendUrl UTF8String]:"");
    
        imsdk::ApiStatus apiStatus = chatManager->registerFriendChat(userIdValue, userNameString, friendIdValue, friendNameString, friendUrlString, ipAddressSting, (int)port, (int)deviceType, deviceTokenSting, (int)appType, (int)status, (int)mood, (int)voipPush, authRegisterTime, (int)profileType);
        return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
    }
    else
    {
        //NSLog(@"Error in sendRegisterRequstForFriendChat :: Chat SDK not initialized!");
        return nil;
    }
}

+ (IMApiStatus *) sendGeneralEncryptedInformationWithUserID:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withType:(NSInteger)type withInfoType:(NSInteger)infoType withInfo:(NSString *)info
{
	 std::string packetIdString([packetId UTF8String]);
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);
    std::string infoString([info UTF8String]);
	imsdk::ApiStatus apiStatus = chatManager->sendGeneralEncryptedInformation(userIdValue, friendIdValue, packetIdSting, (int)type, (int)infoType, infoString);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}
	
+ (IMApiStatus *)updateFriendRegisterServerWithId:(NSString *)userId withFriendId:(NSString *)friendId withServerAddress:(NSString *)serverAddress withServerPort:(NSInteger)serverPort
{
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);
    std::string serverAddressString([serverAddress UTF8String]);
    
    imsdk::ApiStatus apiStatus = chatManager->updateFriendRegisterServer(userIdValue, friendIdValue, serverAddressString, (int)serverPort);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)updateFriendPresenceId:(NSString *)userId withFriendId:(NSString *)friendId withPresence:(IMSDK_Presence)presence withMood:(IMSDK_MoodType)mood
{
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);
    
    imsdk::ApiStatus apiStatus = chatManager->updateFriendStatusAndMood(userIdValue, friendIdValue, (int)presence, (int)mood);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)dontSendPendingMessagesWithId:(NSString *)userId withFriendId:(NSString *)friendId
{
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);
    
    imsdk::ApiStatus apiStatus = chatManager->dontSendPendingMessages(userIdValue, friendIdValue);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendFriendCallBusyMessageWithPacketId:(NSString *)packetId
                                            withUserId:(NSString *)userId
                                              withFriendId:(NSString *)friendId
                                           withMessage:(NSString *)message
                                       withMessageDate:(long long)date
{
    std::string packetIdString([packetId UTF8String]);
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);
    std::string messageString([message UTF8String]);
    
    imsdk::ApiStatus apiStatus = chatManager->sendFriendCallBusyMessage(userIdValue, friendIdValue, messageString, date, packetIdString);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendFriendCallLogMessageWithPacketId:(NSString *)packetId
                                           withUserId:(NSString *)userId
                                         withFriendId:(NSString *)friendId
                                          withMessage:(NSString *)message
                                      withMessageDate:(long long)date
{
    std::string packetIdString((packetId!=nil)?[packetId UTF8String]:"");
    UserIdentity userIdValue((userId!=nil)?[userId longLongValue]:0);
    UserIdentity friendIdValue((friendId!=nil)?[friendId longLongValue]:0);
    std::string messageString((message!=nil)?[message UTF8String]:"");

    imsdk::ApiStatus apiStatus = chatManager->sendFriendCallLogMessage(userIdValue, friendIdValue, messageString, date, packetIdString);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (NSArray *)getPendingFriendMessageListWithId:(NSString *)userId
{
    UserIdentity userIdValue((userId!=nil)?[userId longLongValue]:0);
    std::vector<std::string> packetIdList = chatManager->getPendingFriendMessages(userIdValue);
    
    NSMutableArray *packetIdArray = [NSMutableArray array];
    
    for (int i = 0; i < packetIdList.size(); i++)
    {
        NSString *packetIdString = [NSString stringWithUTF8String:packetIdList[i].c_str()];
        
        [packetIdArray addObject:packetIdString];
    }

    return packetIdArray;
}

+ (NSArray *)getPendingGroupMessageList
{
    std::vector<std::string> packetIdList = chatManager->getPendingGroupMessages();
    
    NSMutableArray *packetIdArray = [NSMutableArray array];
    
    for (int i = 0; i < packetIdList.size(); i++)
    {
        NSString *packetIdString = [NSString stringWithUTF8String:packetIdList[i].c_str()];
        
        [packetIdArray addObject:packetIdString];
    }
    
    return packetIdArray;
}

+ (void)cleanUpWithMood:(IMSDK_MoodType)mood
{
    chatManager->cleanUp((int)mood);
}

+ (BOOL) isExistsFriendConnectionWithUserId:(NSString *)userId withFriendId:(NSString *)friendId
{
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);
    return chatManager->isExistsFriendConnection(userIdValue, friendIdValue);
}

+ (IMApiStatus *)sendRegisterRequestForGroupChatWithId:(NSString *)groupId
                                          withChatServerIP:(NSString *)ipAddress
                                                  withPort:(NSInteger)port
                                  withAuthRegisterTime:(long long)authRegisterTime
{
    if(chatManager != nil)
    {
        std::string ipAddressSting([ipAddress UTF8String]);
        UserIdentity groupIdValue([groupId longLongValue]);
    
        imsdk::ApiStatus apiStatus = chatManager->registerGroupChat(groupIdValue, ipAddressSting, (int)port, authRegisterTime);
        return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
    }
    else
    {
        //NSLog(@"Error in sendRegisterRequestForGroupChat :: Chat SDK not initialized!");
        return nil;
    }
}

+ (BOOL) isExistsGroupConnectionWithGroupId:(NSString *)groupId
{
    GroupIdentity groupIdValue([groupId longLongValue]);
    return chatManager->isExistsGroupConnection(groupIdValue);
}

+ (IMApiStatus *)sendUnregisterRequestForFriendChatWithId:(NSString *)userId withFriendId:(NSString *)friendId withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood
{
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);

    imsdk::ApiStatus apiStatus = chatManager->unregisterFriendChat(userIdValue, friendIdValue, (int)status, (int)mood);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendUnregisterRequestForGroupChatWithId:(NSString *)groupId withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood
{
    UserIdentity groupIdValue([groupId longLongValue]);
    
    imsdk::ApiStatus apiStatus = chatManager->unregisterGroupChat(groupIdValue, (int)status, (int)mood);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendTypingForFriendChatWithId:(NSString *)userId withFriendId:(NSString *)friendId
{
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);
    
    imsdk::ApiStatus apiStatus = chatManager->typingFriendChat(userIdValue, friendIdValue);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendTypingForGroupChatwithId:(NSString *)groupId
{
    UserIdentity groupIdValue([groupId longLongValue]);

    imsdk::ApiStatus apiStatus = chatManager->typingGroupChat(groupIdValue);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];

}

+ (IMApiStatus *)sendFriendChatMessageWithPacketId:(NSString *)packetId
                                        withUserId:(NSString *)userId
                                          withFriendId:(NSString *)friendId
                                           withMessage:(NSString *)message
                                       withMessageType:(IMSDK_MessageType)messageType
                                       withMessageDate:(long long)date
                                        withSecretTime:(NSInteger)secretTime
                                   withIsSecretVisible:(BOOL)isSecretVisible
{
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);
    std::string packetIdString([packetId UTF8String]);
    std::string messageSting([message UTF8String]);
    
    imsdk::ApiStatus apiStatus = chatManager->sendFriendChat(packetIdString, userIdValue, friendIdValue, (int)messageType, (int)secretTime, messageSting, date, isSecretVisible);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendFriendChatEdittedMessageWithPacketId:(NSString *)packetId
                                               withUserId:(NSString *)userId
                                    withFriendId:(NSString *)friendId
                                     withMessage:(NSString *)message
                                 withMessageType:(IMSDK_MessageType)messageType
                                 withMessageDate:(long long)date
                                  withSecretTime:(NSInteger)secretTime
                             withIsSecretVisible:(BOOL)isSecretVisible
{
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);
    std::string messageSting([message UTF8String]);
    std::string packetIdSting([packetId UTF8String]);

    imsdk::ApiStatus apiStatus = chatManager->editFriendChat(packetIdSting, userIdValue, friendIdValue, (int)messageType, (int)secretTime, messageSting, date, isSecretVisible);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendSeenForFriendChatWithId:(NSString *)userId withFriendId:(NSString *)friendId withMessageStatusList:(NSArray *)messageStatusList
{
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);
    
    int count = (int)messageStatusList.count;
    std::vector<imsdk::SeenPacketDTO> dtoList(count);
    
    for (int i = 0; i < count; i++)
    {
        IMMessageStatusModel *messageStatusModel = [messageStatusList objectAtIndex:i];
        
        std::string packetIdValue([messageStatusModel.packetId UTF8String]);
        
        imsdk::SeenPacketDTO seenPacketDTO(packetIdValue, messageStatusModel.messageDate, messageStatusModel.messageStatus);
        dtoList[i] = seenPacketDTO;
    }
    
    imsdk::ApiStatus apiStatus = chatManager->seenFriendChat(userIdValue, friendIdValue, dtoList);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendBlockFriendRequestWithPacketId:(NSString*)packetId
                                         withUserId:(NSString *)userId
                                           withFriendId:(NSString *)friendId
                                          withBlockDate:(long long)date
                                         withExtrayByte:(BOOL)blockValue
{
    std::string packetIdSting([packetId UTF8String]);
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);
    
    imsdk::ApiStatus apiStatus = chatManager->blockFriend(userIdValue, packetIdSting,friendIdValue, date, blockValue);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendUnblockFreindRequestWithPacketId:(NSString*)packetId withUserId:(NSString *)userId withFriendId:(NSString *)friendId withUnblockDate:(long long)date
{
    std::string packetIdSting([packetId UTF8String]);
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);
    
    imsdk::ApiStatus apiStatus = chatManager->unblockFriend(userIdValue, packetIdSting, friendIdValue, date);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendGroupChatMessageWithPacketId:(NSString *)packetId
                                          withGroupId:(NSString *)groupId
                                          withMessage:(NSString *)message
                                      withMessageType:(IMSDK_MessageType)messageType
                                      withMessageDate:(long long)date
{
    UserIdentity groupIdValue([groupId longLongValue]);
    std::string packetIdString([packetId UTF8String]);
    std::string messageSting([message UTF8String]);
    
    imsdk::ApiStatus apiStatus = chatManager->sendGroupChat(packetIdString, groupIdValue, (int)messageType, messageSting, date);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendGroupChatEditedMessageWithPacketId:(NSString *)packetId
                                                withGroupId:(NSString *)groupId
                                                withMessage:(NSString *)message
                                            withMessageType:(IMSDK_MessageType)messageType
                                            withMessageDate:(long long)date
{
    UserIdentity groupIdValue([groupId longLongValue]);
    std::string packetIdString([packetId UTF8String]);
    std::string messageSting([message UTF8String]);
    
    imsdk::ApiStatus apiStatus = chatManager->editGroupChat(packetIdString, groupIdValue, (int)messageType, messageSting, date);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendSeenForGroupChatWithId:(NSString *)groupId
                                withPacketIdList:(NSArray *)packetIdList
{
    UserIdentity groupIdValue([groupId longLongValue]);
    
    int packetIdArrayCount = (int)packetIdList.count;
    std::vector<std::string> packetIds(packetIdArrayCount);
    
    int i = 0;
    for (NSString *packetId in packetIdList)
    {
        std::string packetIdString([packetId UTF8String]);
        
        packetIds[i] = packetIdString;
        i++;
    }
    
    imsdk::ApiStatus apiStatus = chatManager->seenGroupChat(groupIdValue, packetIds);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendRequestForGroupSeenListWithId:(NSString *)groupId withPacketId:(NSString *)packetId
{
    UserIdentity groupIdValue([groupId longLongValue]);
    std::string packetIdString([packetId UTF8String]);
    
    imsdk::ApiStatus apiStatus = chatManager->getGroupMessageSeenList(groupIdValue, packetIdString);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendDeleteFriendMessageRequestWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketIdList:(NSArray *)packetIdArray withDeleteType:(NSInteger)deleteType
{
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);
    
    int packetIdArrayCount = (int)packetIdArray.count;
    std::vector<std::string> packetIdList(packetIdArrayCount);
    
    int i = 0;
    for (NSString *packetId in packetIdArray)
    {
        std::string packetIdString([packetId UTF8String]);
        
        packetIdList[i] = packetIdString;
        i++;
    }
    
    imsdk::ApiStatus apiStatus = chatManager->deleteFriendChatMessage(userIdValue, friendIdValue, packetIdList, (int)deleteType);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendDeleteGroupMessageRequestWithId:(NSString *)groupId withPacketIdList:(NSArray *)packetIdArray
{
    UserIdentity groupIdValue([groupId longLongValue]);
    
    int packetIdArrayCount = (int)packetIdArray.count;
    std::vector<std::string> packetIdList(packetIdArrayCount);
    
    int i = 0;
    for (NSString *packetId in packetIdArray)
    {
        std::string packetIdString([packetId UTF8String]);
        
        packetIdList[i] = packetIdString;
        i++;
    }
    
    imsdk::ApiStatus apiStatus = chatManager->deleteGroupChatMessage(groupIdValue, packetIdList);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendGroupMemberAddRequestWithId:(NSString *)groupId
                                      withMemberList:(NSArray *)memberList
{
    UserIdentity groupIdValue([groupId longLongValue]);
    
    int memberCount = (int)memberList.count;
    std::vector<imsdk::MemberDTO> dtoList(memberCount);
    
    for (int i = 0; i < memberCount; i ++)
    {
        IMGroupMemberModel *memberModel = [memberList objectAtIndex:i];
        
        UserIdentity memberIdValue([memberModel.friendId longLongValue]);
        UserIdentity ringIdValue([memberModel.ringId longLongValue]);
        UserIdentity addedByIdValue([memberModel.memberAddedBy longLongValue]);
        std::string memberNameSting([memberModel.friendName UTF8String]);
        
        imsdk::MemberDTO memberDTO(memberIdValue, ringIdValue, memberNameSting, (int)memberModel.memberStatus, addedByIdValue);
        dtoList[i] = memberDTO;
    }
    
    imsdk::ApiStatus apiStatus = chatManager->addGroupMembers(groupIdValue, dtoList);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendGroupMemberRemoveRequestWithId:(NSString *)groupId
                                         withMemberList:(NSArray *)memberList
{
    UserIdentity groupIdValue([groupId longLongValue]);
    
    int memberCount = (int)memberList.count;
    std::vector<UserIdentity> dtoList(memberCount);
    
    for (int i = 0; i < memberCount; i ++)
    {
        IMGroupMemberModel *memberModel = [memberList objectAtIndex:i];
        
        UserIdentity memberIdValue([memberModel.friendId longLongValue]);
//        UserIdentity addedByIdValue([memberModel.memberAddedBy longLongValue]);
//        std::string memberNameSting([memberModel.friendName UTF8String]);
        
//        imsdk::MemberDTO memberDTO(memberIdValue, memberNameSting, (int)memberModel.memberStatus, addedByIdValue);
        dtoList[i] = memberIdValue;
    }

    imsdk::ApiStatus apiStatus = chatManager->removeGroupMembers(groupIdValue, dtoList);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendGroupMemberStatusChangeRequestWithId:(NSString *)groupId
                                               withMemberList:(NSArray *)memberList
{
    UserIdentity groupIdValue([groupId longLongValue]);
    
    int memberCount = (int)memberList.count;
    std::vector<imsdk::MemberDTO> dtoList(memberCount);
    
    for (int i = 0; i < memberCount; i ++)
    {
        IMGroupMemberModel *memberModel = [memberList objectAtIndex:i];
        
        UserIdentity memberIdValue([memberModel.friendId longLongValue]);
        UserIdentity ringIdValue([memberModel.ringId longLongValue]);
        UserIdentity addedByIdValue([memberModel.memberAddedBy longLongValue]);
        std::string memberNameSting([memberModel.friendName UTF8String]);
        
        imsdk::MemberDTO memberDTO(memberIdValue, ringIdValue, memberNameSting, (int)memberModel.memberStatus, addedByIdValue);
        dtoList[i] = memberDTO;
    }
    
    imsdk::ApiStatus apiStatus = chatManager->changeGroupMemberStatus(groupIdValue, dtoList);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendLeaveGroupRequestWithId:(NSString *)groupId
                                  withIsHide:(BOOL)isHide
{
    GroupIdentity groupIdValue([groupId longLongValue]);
    
    imsdk::ApiStatus apiStatus = chatManager->leaveGroup(groupIdValue, isHide);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendRequestForFriendChatHistoryWithId:(NSString *)userId withFriendId:(NSString*)friendId withPacketId:(NSString*)packetId withDirection:(IMSDK_Scroll)direction withLimit:(int)limit
{
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);
    std::string packetIdString([packetId UTF8String]);
    
    imsdk::ApiStatus apiStatus = chatManager->requestFriendChatHistory(userIdValue, friendIdValue, packetIdString, direction, limit);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendRequestForFriendMessageStatusWithId:(NSString *)userId withFriendId:(NSString*)friendId withPacketIdArray:(NSArray *)packetIdArray
{
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);
    
    int packetIdArrayCount = (int)packetIdArray.count;
    std::vector<std::string> packetIdList(packetIdArrayCount);
    
    int i = 0;
    for (NSString *packetId in packetIdArray)
    {
        std::string packetIdString([packetId UTF8String]);
        
        packetIdList[i] = packetIdString;
        i++;
    }
    
    imsdk::ApiStatus apiStatus = chatManager->getFriendMessageStatus(userIdValue, friendIdValue, packetIdList);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendGroupRenameWithId:(NSString*)groupId withGroupName:(NSString*)name
{
    GroupIdentity groupIdValue([groupId longLongValue]);
    std::string nameString([name UTF8String]);
    
    imsdk::ApiStatus apiStatus = chatManager->changeGroupName(groupIdValue, nameString);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendGroupProfilePicChangeWithId:(NSString*)groupId withImageUrl:(NSString*)url
{
    GroupIdentity groupIdValue([groupId longLongValue]);
    std::string urlString([url UTF8String]);
    
    imsdk::ApiStatus apiStatus = chatManager->changeGroupUrl(groupIdValue, urlString);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendCreateGroupWithId:(NSString*)groupId withGroupName:(NSString*)name withImageUrl:(NSString*)url withMemberList:(NSArray *)memberList
{
    GroupIdentity groupIdValue([groupId longLongValue]);
    std::string nameString([name UTF8String]);
    std::string urlString([url UTF8String]);
    
    int memberCount = (int)memberList.count;
    std::vector<imsdk::MemberDTO> dtoList(memberCount);
    
    for (int i = 0; i < memberCount; i ++)
    {
        IMGroupMemberModel *memberModel = [memberList objectAtIndex:i];
        
        UserIdentity memberIdValue([memberModel.friendId longLongValue]);
        UserIdentity ringIdValue([memberModel.ringId longLongValue]);
        UserIdentity addedByIdValue([memberModel.memberAddedBy longLongValue]);
        std::string memberNameSting([memberModel.friendName UTF8String]);
        
        imsdk::MemberDTO memberDTO(memberIdValue, ringIdValue, memberNameSting, (int)memberModel.memberStatus, addedByIdValue);
        dtoList[i] = memberDTO;
    }
    
    imsdk::ApiStatus apiStatus = chatManager->createGroup(groupIdValue, nameString, urlString, dtoList);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendRequestForGroupChatHistoryWithId:(NSString*)groupId withPacketId:(NSString*)packetId withDirection:(IMSDK_Scroll)direction withLimit:(int)limit
{
    GroupIdentity groupIdValue([groupId longLongValue]);
    std::string packetIdString([packetId UTF8String]);
    
    imsdk::ApiStatus apiStatus = chatManager->requestGroupChatHistory(groupIdValue, packetIdString, direction, limit);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendRequestForGroupInformationWithMembersWithId:(NSString*)groupId
{
    GroupIdentity groupIdValue([groupId longLongValue]);
    
    imsdk::ApiStatus apiStatus = chatManager->getGroupInformationWithMembers(groupIdValue);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (void) reinitializeSdkWithUserId:(NSString *)userId
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
                  withAutoDownload:(BOOL)autoDownload
                 withEncryptionKey:(NSString*)encryptionKey
                    withPageIdList:(NSArray *)pageIdList
{
    std::string userNameString((userName!=nil)?[userName UTF8String]:"");
    std::string offlineIpAddressSting((offlineIpAddress!=nil)?[offlineIpAddress UTF8String]:"");
    std::string authIpAddressString((authIpAddress!=nil)?[authIpAddress UTF8String]:"");
    std::string appSessionIdString((appSessionId!=nil)?[appSessionId UTF8String]:"");
    std::string encryptionKeyString((encryptionKey!=nil)?[encryptionKey UTF8String]:"");
    UserIdentity userIdValue((userId!=nil)?[userId longLongValue]:0);
    
    std::vector<std::string> vdirectoryPaths;
    for (NSString *directoryPath in directoryPaths)
    {
        std::string sDirectoryPath([directoryPath UTF8String]);
        vdirectoryPaths.push_back(sDirectoryPath);
    }
    
    int pageIdCount = (int)pageIdList.count;
    std::set<UserIdentity> pageIds;
    
    for (int i=0; i<pageIdCount; i++)
    {
        NSString* pageId = [pageIdList objectAtIndex:i];
        UserIdentity pageIdValue((pageId!=nil)?[pageId longLongValue]:0);
        pageIds.insert(pageIdValue);
    }
    
    chatManager->reinitialize(userIdValue, userNameString, offlineIpAddressSting, (int)offlinePort, authIpAddressString, (int)authPort, deviceType, appSessionIdString, (int)appVersion, timeDifference, vdirectoryPaths, autoDownload, encryptionKeyString, pageIds);

}

+ (IMFriendInformationModel *)getFriendInformationWithId:(NSString *)userId withFriendId:(NSString *)friendId
{
    UserIdentity userIdValue((userId!=nil)?[userId longLongValue]:0);
    UserIdentity friendIdValue((friendId!=nil)?[friendId longLongValue]:0);
    
    std::shared_ptr<imsdk::FriendInformation> friendInformation = chatManager->getFriendInformation(userIdValue, friendIdValue);
    
    if (friendInformation)
    {
        IMFriendInformationModel *friendInformationModel = [[IMFriendInformationModel alloc] init];
        
        friendInformationModel.registerServerAddress = [NSString stringWithUTF8String:friendInformation->getFriendRegisterServerAddress().c_str()];
        friendInformationModel.registerServerPort = friendInformation->getFriendRegisterServerPort();
        friendInformationModel.bindingPort = friendInformation->getFriendChatServerPort();
        friendInformationModel.blockStatus = friendInformation->getBlockStatus();
        friendInformationModel.friendName = [NSString stringWithUTF8String:friendInformation->getFriendName().c_str()];
        friendInformationModel.friendUrl = [NSString stringWithUTF8String:friendInformation->getFriendUrl().c_str()];
        friendInformationModel.status = static_cast<IMSDK_Presence>(friendInformation->getFriendStatus());
        friendInformationModel.mood = static_cast<IMSDK_MoodType>(friendInformation->getFriendMood());
        friendInformationModel.device = static_cast<IMSDK_DeviceType>(friendInformation->getFriendDeviceType());
        friendInformationModel.profileType = friendInformation->getProfileType();
    
        return friendInformationModel;
    }
    
    return nil;
}

+ (IMGroupInformationModel *)getGroupInformationWithId:(NSString *)groupId
{
    UserIdentity groupIdValue((groupId!=nil)?[groupId longLongValue]:0);
    
    std::shared_ptr<imsdk::GroupInformation> groupInformation = chatManager->getGroupInformation(groupIdValue);
    
    IMGroupInformationModel *groupInformationModel = [[IMGroupInformationModel alloc] init];
    
    groupInformationModel.groupId = [NSString stringWithFormat:@"%lld",(long long)groupInformation->getGroupId()];
    groupInformationModel.registerServerAddress = [NSString stringWithUTF8String:groupInformation->getRegisterServerIp().c_str()];
    groupInformationModel.registerServerPort = groupInformation->getRegisterServerPort();
    groupInformationModel.bindingPort = groupInformation->getBindingPort();
    groupInformationModel.lastActivityTime = groupInformation->getLastActivityTime();
    
    return groupInformationModel;
}

+ (NSArray *)getRegisteredFriendListWithId:(NSString *)userId
{
    UserIdentity userIdValue((userId!=nil)?[userId longLongValue]:0);
    std::vector<UserIdentity> registeredFriendsList = chatManager->getRegisteredFriendsList(userIdValue);
    NSMutableArray *registeredFriendsListArray = [NSMutableArray array];
    
    for (int i = 0; i < registeredFriendsList.size(); i++)
    {
        NSString *registeredFriend = [NSString stringWithFormat:@"%lld", (long long)registeredFriendsList[i]];
        [registeredFriendsListArray addObject:registeredFriend];
    }
    return registeredFriendsListArray;
}

+ (NSArray *)getRegisteredGroupList
{
    NSMutableArray *registeredGroupListArray = [NSMutableArray array];
    std::vector<std::shared_ptr<imsdk::GroupInformation>> registeredGroupList = chatManager->getRegisteredGroupList();
    
    for(int i=0; i<registeredGroupList.size(); i++){
        std::shared_ptr<imsdk::GroupInformation> groupInformation = registeredGroupList[i];
        IMGroupInformationModel *groupInformationModel = [[IMGroupInformationModel alloc] init];
        groupInformationModel.groupId = [NSString stringWithFormat:@"%lld", (long long)groupInformation->getGroupId()];
        groupInformationModel.registerServerAddress = [NSString stringWithUTF8String:groupInformation->getRegisterServerIp().c_str()];
        groupInformationModel.registerServerPort = groupInformation->getRegisterServerPort();
        groupInformationModel.bindingPort = groupInformation->getBindingPort();
        groupInformationModel.lastActivityTime = groupInformation->getLastActivityTime();
        
        [registeredGroupListArray addObject:groupInformationModel];
    }
    
    return registeredGroupListArray;
}

+ (IMApiStatus *)sendRegisterRequestForPublicRoomChatWithRoomId:(NSString *)roomId
                                             withMemberName:(NSString *)memberName
                                              withMemberUrl:(NSString *)memberUrl
                                                     withRingId:(NSString *)ringId
{
    if(chatManager != nil)
    {
        std::string roomIdString((roomId!=nil)?[roomId UTF8String]:"");
        std::string roomNameString((memberName!=nil)?[memberName UTF8String]:"");
        std::string roomUrlString((memberUrl!=nil)?[memberUrl UTF8String]:"");
        UserIdentity ringIdValue((ringId!=nil)?[ringId longLongValue]:0);
    
        imsdk::ApiStatus apiStatus = chatManager->registerPublicRoomChat(roomIdString, roomNameString, roomUrlString, ringIdValue);
        return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
    }
    else
    {
        //NSLog(@"Error in sendRegisterRequestForPublicRoomChat :: Chat SDK not initialized!");
        return nil;
    }
}

+ (void)enterPublicRoomChatScreenWithRoomId:(NSString *)roomId
{
    std::string roomIdString((roomId!=nil)?[roomId UTF8String]:"");
    chatManager->enterPublicChatScreen(roomIdString);
}

+ (void)exitPublicRoomChatScreenWithRoomId:(NSString *)roomId
{
    std::string roomIdString((roomId!=nil)?[roomId UTF8String]:"");
    chatManager->exitPublicChatScreen(roomIdString);
}

+ (IMApiStatus *)sendPublicRoomChatMessageWithPacketId:(NSString *)packetId
                                            withRoomId:(NSString *)roomId
                                       withMessageType:(IMSDK_MessageType)messageType
                                           withMessage:(NSString *)message
                                       withMessageDate:(long long)messageDate
                                        withMemberName:(NSString *)memberName
                                  withMemberProfileUrl:(NSString *)memberProfileUrl
{
    std::string packetIdString((packetId!=nil)?[packetId UTF8String]:"");
    std::string roomIdString((roomId!=nil)?[roomId UTF8String]:"");
    std::string messageString((message!=nil)?[message UTF8String]:"");
    std::string memberNameString((memberName!=nil)?[memberName UTF8String]:"");
    std::string memberProfileUrlString((memberProfileUrl!=nil)?[memberProfileUrl UTF8String]:"");
    
    imsdk::ApiStatus apiStatus = chatManager->sendPublicRoomChat(packetIdString, roomIdString, messageType, messageString, messageDate, memberNameString, memberProfileUrlString);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendPublicRoomChatEditedMessageWithPacketId:(NSString *)packetId
                                                  withRoomId:(NSString *)roomId
                                             withMessageType:(IMSDK_MessageType)messageType
                                                 withMessage:(NSString *)message
                                             withMessageDate:(long long)messageDate
                                              withMemberName:(NSString *)memberName
                                        withMemberProfileUrl:(NSString *)memberProfileUrl
{
    std::string packetIdString((packetId!=nil)?[packetId UTF8String]:"");
    std::string roomIdString((roomId!=nil)?[roomId UTF8String]:"");
    std::string messageString((message!=nil)?[message UTF8String]:"");
    std::string memberNameString((memberName!=nil)?[memberName UTF8String]:"");
    std::string memberProfileUrlString((memberProfileUrl!=nil)?[memberProfileUrl UTF8String]:"");
    
    imsdk::ApiStatus apiStatus = chatManager->editPublicRoomChat(packetIdString, roomIdString, messageType, messageString, messageDate, memberNameString, memberProfileUrlString);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendRoomListRequestWithIndex:(int)startIndex withLimit:(int)limit
{
    imsdk::ApiStatus apiStatus = chatManager->getRoomList(startIndex, limit);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendRoomListSearchRequestWithName:(NSString *)searchName withCountry:(NSString *)country withCategory:(NSString *)category withIndex:(int)startIndex withLimit:(int)limit
{
    std::string searchNameString((searchName!=nil)?[searchName UTF8String]:"");
    std::string countryString((country!=nil)?[country UTF8String]:"");
    std::string categoryString((category!=nil)?[category UTF8String]:"");
    
    imsdk::ApiStatus apiStatus = chatManager->searchRoomList(searchNameString, countryString, categoryString, startIndex, limit);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendUnregisterRequestForPublicRoomChatWithRoomId:(NSString *)roomId
{
    std::string roomIdString((roomId!=nil)?[roomId UTF8String]:"");
    
    imsdk::ApiStatus apiStatus = chatManager->unregisterPublicRoomChat(roomIdString);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendTypingForPublicRoomChatWithRoomId:(NSString *)roomId
{
    std::string roomIdString((roomId!=nil)?[roomId UTF8String]:"");
    
    imsdk::ApiStatus apiStatus = chatManager->typingPublicRoomChat(roomIdString);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (BOOL)isExistsPublicRoomChatConnectionWithRoomId:(NSString *)roomId
{
    std::string roomIdString((roomId!=nil)?[roomId UTF8String]:"");
    
    return chatManager->isExistsRoomConnection(roomIdString);
}

+ (IMApiStatus *)sendRequestForPublicChatRoomInformationWithRoomId:(NSString *)roomId
{
    std::string roomIdString((roomId!=nil)?[roomId UTF8String]:"");
    
    imsdk::ApiStatus apiStatus = chatManager->getRoomInformation(roomIdString);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendRoomChatHistoryRequestWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId withYear:(int)year withMonth:(int)month withDirection:(IMSDK_Scroll)direction withLimit:(int)limit
{
    std::string roomIdString((roomId!=nil)?[roomId UTF8String]:"");
    std::string packetIdString((packetId!=nil)?[packetId UTF8String]:"");
    
    imsdk::ApiStatus apiStatus = chatManager->requestRoomChatHistory(roomIdString, packetIdString, year, month, direction, limit);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendRoomListWithHistoryRequestWithIndex:(int)startIndex withLimit:(int)limit
{
    imsdk::ApiStatus apiStatus = chatManager->getRoomListWithHistory(startIndex, limit);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendRoomMemberListRequestWithRoomId:(NSString *)roomId withPagingState:(NSString *)pagingState withLimit:(int)limit
{
    std::string roomIdString((roomId!=nil)?[roomId UTF8String]:"");
    std::string pagingStateString((pagingState!=nil)?[pagingState UTF8String]:"");
    
    imsdk::ApiStatus apiStatus = chatManager->getRoomMemberList(roomIdString, pagingStateString, limit);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendDeletePublicRoomChatDeleteRequestWithId:(NSString *)roomId withPacketIdList:(NSArray *)packetIdList
{
    std::string roomIdString((roomId!=nil)?[roomId UTF8String]:"");
    
    int packetIdArrayCount = (int)packetIdList.count;
    std::vector<std::string> packetIds(packetIdArrayCount);
    
    int i = 0;
    for (NSString *packetId in packetIdList)
    {
        std::string packetIdString([packetId UTF8String]);
        
        packetIds[i] = packetIdString;
        i++;
    }
    
    imsdk::ApiStatus apiStatus = chatManager->deletePublicChatMessage(roomIdString, packetIds);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendLikePublicRoomChatMessageRequestWithId:(NSString *)roomId withPacketId:(NSString *)packetId withMessageSenderId:(NSString *)messageSender
{
    std::string roomIdString((roomId!=nil)?[roomId UTF8String]:"");
    std::string packetIdString((packetId!=nil)?[packetId UTF8String]:"");
    UserIdentity messageSendIdValue([messageSender longLongValue]);
    
    imsdk::ApiStatus apiStatus = chatManager->likePublicChatMessage(packetIdString, roomIdString, messageSendIdValue);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendUnlikePublicRoomChatMessageRequestWithId:(NSString *)roomId withPacketId:(NSString *)packetId withMessageSenderId:(NSString *)messageSender
{
    std::string roomIdString((roomId!=nil)?[roomId UTF8String]:"");
    std::string packetIdString((packetId!=nil)?[packetId UTF8String]:"");
    UserIdentity messageSendIdValue([messageSender longLongValue]);
    
    imsdk::ApiStatus apiStatus = chatManager->unlikePublicChatMessage(packetIdString, roomIdString, messageSendIdValue);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendReportPublicRoomChatMessageRequestWithId:(NSString *)roomId withPacketId:(NSString *)packetId withMessageSenderId:(NSString *)messageSender withReportMessage:(NSString *)reportMessage
{
    std::string roomIdString((roomId!=nil)?[roomId UTF8String]:"");
    std::string packetIdString((packetId!=nil)?[packetId UTF8String]:"");
    std::string reportMessageString((reportMessage!=nil)?[reportMessage UTF8String]:"");
    UserIdentity messageSendIdValue([messageSender longLongValue]);
    
    imsdk::ApiStatus apiStatus = chatManager->reportPublicChatMessage(packetIdString, roomIdString, messageSendIdValue, reportMessageString);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendRequestForPublicRoomChatLikeMemberList:(NSString *)roomId withPacketId:(NSString *)packetId withLastLikerId:(NSString *)lastLikerId withLimit:(int) limit
{
    std::string roomIdString((roomId!=nil)?[roomId UTF8String]:"");
    std::string packetIdString((packetId!=nil)?[packetId UTF8String]:"");
    UserIdentity lastLikerIdValue([lastLikerId longLongValue]);
    
    imsdk::ApiStatus apiStatus = chatManager->getPublicChatLikeMemberList(roomIdString, packetIdString, lastLikerIdValue, limit);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendRequestForPublicRoomChatCategoryListWithLastCategory:(NSString *)lastCategory withLimit:(int) limit
{
    std::string lastCategoryString((lastCategory!=nil)?[lastCategory UTF8String]:"");
    
    imsdk::ApiStatus apiStatus = chatManager->getPublicChatRoomCategoryList(lastCategoryString, limit);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

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
                                                                     withMood:(IMSDK_MoodType)mood
{
    UserIdentity selfAnonymousIdValue((selfAnonymousId!=nil)?[selfAnonymousId longLongValue]:0);
    UserIdentity friendAnonymousIdValue((friendAnonymousId!=nil)?[friendAnonymousId longLongValue]:0);
    UserIdentity friendOriginalIdValue((friendOriginalId!=nil)?[friendOriginalId longLongValue]:0);
    std::string registerServerAddressString((registerServerAddress!=nil)?[registerServerAddress UTF8String]:"");
    std::string deviceTokenString((deviceToken!=nil)?[deviceToken UTF8String]:"");
    
    imsdk::ApiStatus apiStatus = chatManager->registerAnonymousFriendChat(selfAnonymousIdValue, friendAnonymousIdValue, friendOriginalIdValue, registerServerAddressString, (int)registerServerPort, deviceType, deviceTokenString, appType, status, mood);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendUnregisterRequestForAnonymousFriendChatWithId:(NSString *)userId withFriendId:(NSString *)anonymousFriendId withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood
{
    UserIdentity userIdValue((userId!=nil)?[userId longLongValue]:0);
    UserIdentity anonymousFriendIdValue((anonymousFriendId!=nil)?[anonymousFriendId longLongValue]:0);
    
    imsdk::ApiStatus apiStatus = chatManager->unregisterAnonymousFriendChat(userIdValue, anonymousFriendIdValue, status, mood);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendRequestForConversationListWithId:(NSString *)userId withType:(IMSDK_ConversationType)conversationType withStartIndex:(int)startIndex withLimit:(int)limit withId:(NSString *)friendGroupId
{
    UserIdentity userIdValue((userId!=nil)?[userId longLongValue]:0);
    UserIdentity friendGroupIdValue((friendGroupId!=nil)?[friendGroupId longLongValue]:0);
    
    imsdk::ApiStatus apiStatus = chatManager->getConversationList(userIdValue, static_cast<imsdk::ConversationType>(conversationType), startIndex, limit, friendGroupIdValue);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendDeleteConversationListRequestWithId:(NSString *)userId withList:(NSArray *)conversationList
{
    UserIdentity userIdValue((userId!=nil)?[userId longLongValue]:0);
    int count = (int)conversationList.count;
    std::vector<imsdk::ConversationDTO> dtoList(count);

    for (int i = 0; i < count; i++)
    {
        IMConversationModel *conversationModel = [conversationList objectAtIndex:i];

        UserIdentity friendIdValue((conversationModel.friendId!=nil)?[conversationModel.friendId longLongValue]:0);
        UserIdentity groupIdValue((conversationModel.groupId!=nil)?[conversationModel.groupId longLongValue]:0);

        imsdk::ConversationDTO conversationDTO(static_cast<int>(conversationModel.conversationType), friendIdValue, groupIdValue);
        dtoList[i] = conversationDTO;
    }

    imsdk::ApiStatus apiStatus = chatManager->deleteConversation(userIdValue, dtoList);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendMarkConversationListRequestWithId:(NSString *)userId withList:(NSArray *)conversationList
{
    UserIdentity userIdValue((userId!=nil)?[userId longLongValue]:0);
    int count = (int)conversationList.count;
    std::vector<imsdk::ConversationDTO> dtoList(count);
        for (int i = 0; i < count; i++)
    {
        IMConversationModel *conversationModel = [conversationList objectAtIndex:i];

        UserIdentity friendIdValue((conversationModel.friendId!=nil)?[conversationModel.friendId longLongValue]:0);
        UserIdentity groupIdValue((conversationModel.groupId!=nil)?[conversationModel.groupId longLongValue]:0);

        imsdk::ConversationDTO conversationDTO(static_cast<int>(conversationModel.conversationType), friendIdValue, groupIdValue);
        dtoList[i] = conversationDTO;
    }

    imsdk::ApiStatus apiStatus = chatManager->markConversationSeen(userIdValue, dtoList);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (void) updatePasswordWithPassword:(NSString *)password
{
    std::string passwordString((password!=nil)?[password UTF8String]:"");

    chatManager->updateUserPassword(passwordString);
}

+ (IMNetworkDataModel *)getNetworkDataUsage
{
    imsdk::DataCounter dataCounter = chatManager->getDataSentReceived();

    IMNetworkDataModel *networkDataModel = [[IMNetworkDataModel alloc] init];
    networkDataModel.dataSent = dataCounter.getDataSent();
    networkDataModel.dataReceived = dataCounter.getDataReceived();

    return networkDataModel;
}

+ (long long)getTimeFromPacketIdWithId:(NSString *)packetId
{
    std::string packetIdString((packetId!=nil)?[packetId UTF8String]:"");
    return chatManager->UUIDToTime(packetIdString);
}

+ (long long)getCurrentServerSyncedTime
{
    return chatManager->getCurrentServerSyncedTime();
}

+ (BOOL) checkInternetConnection
{
    return chatManager->checkInternetConnection();
}

//+ (IMApiStatus *)sendFileToFriendWithFriendId:(NSString*)friendId withMessageType:(int)messageType withSecretTimeOut:(int)secretTimeOut withFileIdentity:(long long)fileId withFileFullPath:(NSString*)fileFullPath withFileSize:(long long)fileSize withMessageDate:(long long)messageDate withIsSecretVisible:(bool)isSecretVisible
//{
//    UserIdentity friendIdValue([friendId longLongValue]);
//    std::string fileFullPathValue([fileFullPath UTF8String]);
//    
//    imsdk::ApiStatus apiStatus = chatManager->sendFileToFriend(friendIdValue, messageType, secretTimeOut, fileId, fileFullPathValue, fileSize, messageDate, isSecretVisible);
//    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
//}
//
//+ (IMApiStatus *) startFileTransferWithFriendId:(NSString*)friendId withFileIdentity:(long long)fileId withFilePath:(NSString*)filePath
//{
//    UserIdentity friendIdValue([friendId longLongValue]);
//    std::string filePathValue([filePath UTF8String]);
//    
//    imsdk::ApiStatus apiStatus = chatManager->startFileTransfer(friendIdValue, fileId, filePathValue);
//    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
//}
//
//+ (IMApiStatus *) cancelFileTransferWithFriendId:(NSString*)friendId withFileIdentity:(long long)fileId
//{
//    UserIdentity friendIdValue([friendId longLongValue]);
//    imsdk::ApiStatus apiStatus = chatManager->cancelFileTransfer(friendIdValue, fileId);
//    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
//}

+ (void)setLogEnabledWithIsEnabled:(BOOL)isEnabled
{
    chatManager->setLogEnabled(isEnabled);
}

+ (NSString *) generateGroupId
{
    NSString *groupIdString = [NSString stringWithFormat:@"%lld",chatManager->generateGroupId()];
    return groupIdString;
}

+ (void) addPageIdWithId:(NSString *)pageId
{
    UserIdentity pageIdValue((pageId!=nil)?[pageId longLongValue]:0);
    chatManager->addUserPage(pageIdValue);
}

+ (void) removePageIdWithId:(NSString *)pageId
{
    UserIdentity pageIdValue((pageId!=nil)?[pageId longLongValue]:0);
    chatManager->removeUserPage(pageIdValue);
}

+ (IMPacketTimeId *) generatePacketIdWithUserId:(NSString *)userId
{
    UserIdentity userIdValue((userId!=nil)?[userId longLongValue]:0);
    imsdk::PacketTimeId packetTimeId = chatManager->generatePacketId(userIdValue);
    return [IMPacketTimeId initWithPacketId:[NSString stringWithUTF8String:packetTimeId.packetId.c_str()] withTime1970:packetTimeId.packetTime1970 withTime1582:packetTimeId.packetTime1582];
}

+ (IMPacketTimeId *) generatePacketIdWithTime:(long long)timeMili withUserId:(NSString *)userId
{
    UserIdentity userIdValue((userId!=nil)?[userId longLongValue]:0);
    imsdk::PacketTimeId packetTimeId = chatManager->generatePacketId(timeMili, userIdValue);
    return [IMPacketTimeId initWithPacketId:[NSString stringWithUTF8String:packetTimeId.packetId.c_str()] withTime1970:packetTimeId.packetTime1970 withTime1582:packetTimeId.packetTime1582];
}

+ (NSString *) version
{
    return [NSString stringWithUTF8String:chatManager->version().c_str()];
}

+ (void)setLogfileWithFileName:(NSString *)fileName
{
    std::string fileNameString((fileName!=nil)?[fileName UTF8String]:"");
    chatManager->setLogfile(fileNameString);
}

//Live-stream-chat
+ (IMApiStatus *)sendRegisterRequestForLiveStreamChatWithPublisherId:(NSString *)publisherId
                                        withRegisterServerAddress:(NSString *)registerServerAddress
                                        withRegisterServerPort:(NSInteger)registerServerPort
                                        withFullName:(NSString *)fullName
{
    UserIdentity publisherIdValue((publisherId!=nil)?[publisherId longLongValue]:0);
    std::string registerServerAddressSting((registerServerAddress!=nil)?[registerServerAddress UTF8String]:"");
    std::string fullNameString((fullName!=nil)?[fullName UTF8String]:"");
    
    imsdk::ApiStatus apiStatus = chatManager->registerLiveStreamChat(publisherIdValue, registerServerAddressSting, (int)registerServerPort, fullNameString);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendUnregisterRequestForLiveStreamChatWithPublisherId:(NSString *)publisherId 
                                          withOnlineStatus:(IMSDK_Presence)onlineStatus
                                          withMood:(IMSDK_MoodType)onlineMood
{
    UserIdentity publisherIdValue((publisherId!=nil)?[publisherId longLongValue]:0);
    
    imsdk::ApiStatus apiStatus = chatManager->unregisterLiveStreamChat(publisherIdValue, (int)onlineStatus, (int)onlineMood);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendTypingForLiveStreamChatWithPublisherId:(NSString *)publisherId 
{
    UserIdentity publisherIdValue((publisherId!=nil)?[publisherId longLongValue]:0);
    
    imsdk::ApiStatus apiStatus = chatManager->typingLiveStreamChat(publisherIdValue);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)sendLiveStreamChatMessageWithPacketId:(NSString *)packetId
                                          withPublisherId:(NSString *)publisherId
                                       withMessageType:(IMSDK_MessageType)messageType
                                           withMessage:(NSString *)message
                                       withMessageDate:(long long)messageDate
{
    UserIdentity publisherIdValue([publisherId longLongValue]);
    std::string packetIdString([packetId UTF8String]);
    std::string messageSting([message UTF8String]);
    
    imsdk::ApiStatus apiStatus = chatManager->sendLiveStreamChat(packetIdString, publisherIdValue, (int)messageType, messageSting, messageDate);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)blockUserFromLiveStreamChatWithViewerId:(NSString *)viewerId
                                            withPacketId:(NSString *)packetId
{
    UserIdentity viewerIdValue([viewerId longLongValue]);
    std::string packetIdString([packetId UTF8String]);

    imsdk::ApiStatus apiStatus = chatManager->blockUserFromLiveStreamChat(viewerIdValue, packetIdString);

    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

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
    withIsSecretVisible:(BOOL)isSecretVisible
{
    UserIdentity userIdValue((userId!=nil)?[userId longLongValue]:0);
    UserIdentity friendIdValue((friendId!=nil)?[friendId longLongValue]:0);
    std::string packetIdString((packetId!=nil)?[packetId UTF8String]:"");
    std::string filePathString((filePath!=nil)?[filePath UTF8String]:"");
    std::string captionString((caption!=nil)?[caption UTF8String]:"");
    
    return chatManager->sendFriendChatMedia(userIdValue, friendIdValue, packetIdString, messageType, filePathString, captionString, (int)widthOrSize, (int)heightOrDuration, (int)timeout, date, isSecretVisible);
}

+ (BOOL)downloadFriendChatMediaWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withManifestUrl:(NSString *)manifestUrl withMessageType:(IMSDK_MessageType)messageType withTimeout:(NSInteger)timeout
{
    UserIdentity userIdValue((userId!=nil)?[userId longLongValue]:0);
    UserIdentity friendIdValue((friendId!=nil)?[friendId longLongValue]:0);
    std::string packetIdString((packetId!=nil)?[packetId UTF8String]:"");
    std::string manifestUrlString((manifestUrl!=nil)?[manifestUrl UTF8String]:"");

    return chatManager->downloadFriendChatMedia(userIdValue, friendIdValue, packetIdString, manifestUrlString, messageType, (int)timeout);
}

+ (BOOL)acceptChatMediaWithPacketId:(NSString *)packetId
{
    std::string packetIdString((packetId!=nil)?[packetId UTF8String]:"");
    return chatManager->acceptChatMedia(packetIdString);
}

+ (BOOL)sendGroupChatMediaWithId:(NSString *)groupId
                    withPacketId:(NSString *)packetId
                 withMessageType:(IMSDK_MessageType)messageType
                    withFilePath:(NSString *)filePath
                     withCaption:(NSString *)caption
                 withWidthOrSize:(NSInteger)widthOrSize
             witHeightOrDuration:(NSInteger)heightOrDuration
                 withMessageDate:(long long)date
{
    UserIdentity groupIdValue((groupId!=nil)?[groupId longLongValue]:0);
    std::string packetIdString((packetId!=nil)?[packetId UTF8String]:"");
    std::string filePathString((filePath!=nil)?[filePath UTF8String]:"");
    std::string captionString((caption!=nil)?[caption UTF8String]:"");

    return chatManager->sendGroupChatMedia(groupIdValue, packetIdString, messageType, filePathString, captionString, (int)widthOrSize, (int)heightOrDuration, date);
}

+ (BOOL)downloadGroupChatMediaWithId:(NSString *)groupId
                        withFriendId:(NSString *)friendId
                        withPacketId:(NSString *)packetId
                     withManifestUrl:(NSString *)manifestUrl
                     withMessageType:(IMSDK_MessageType)messageType
{
    UserIdentity groupIdValue((groupId!=nil)?[groupId longLongValue]:0);
    UserIdentity friendIdValue((friendId!=nil)?[friendId longLongValue]:0);
    std::string packetIdString((packetId!=nil)?[packetId UTF8String]:"");
    std::string manifestUrlString((manifestUrl!=nil)?[manifestUrl UTF8String]:"");

    return chatManager->downloadGroupChatMedia(groupIdValue, friendIdValue, packetIdString, manifestUrlString, messageType);
}

+ (NSArray *)getPendingChatMediaListWithType:(IMSDK_ConversationType)conversationType withUploadingMediaList:(BOOL)uploadingMediaList withIsChunkedTransfer:(BOOL)isChunkedTransfer
{
    std::vector<std::string> packetIdList = chatManager->getPendingChatMediaList(static_cast<imsdk::ConversationType>(conversationType), uploadingMediaList, isChunkedTransfer);

    NSMutableArray *packetIdArray = [NSMutableArray array];

    for (int i = 0; i < packetIdList.size(); i++)
    {
        NSString *packetIdString = [NSString stringWithUTF8String:packetIdList[i].c_str()];

        [packetIdArray addObject:packetIdString];
    }

    return packetIdArray;
}

+ (BOOL)isChatMediaTransferInProgressWithPacketId:(NSString *)packetId
{
    std::string packetIdString((packetId!=nil)?[packetId UTF8String]:"");
    return chatManager->isChatMediaTransferInProgress(packetIdString);
}

+ (void) updateAppSessionIDWithAppSessionId:(NSString *)appSessionId
{
    std::string appSessionIdString((appSessionId!=nil)?[appSessionId UTF8String]:"");
    chatManager->updateAppSessionID(appSessionIdString);
}

+ (void) cancelChatMediaTransferWithId:(NSString *)packetId
{
    std::string packetIdString((packetId!=nil)?[packetId UTF8String]:"");

    chatManager->cancelChatMediaTransfer(packetIdString);
}



+ (IMApiStatus *)getSyncedConversationWithId:(NSString *)userId withPacketId:(NSString *)packetId withLastSyncedTime:(long long)lastSyncedTime;
{
    UserIdentity userIdValue([userId longLongValue]);
    std::string packetIdString([packetId UTF8String]);
    
    imsdk::ApiStatus apiStatus = chatManager->getSyncedConversation(userIdValue, packetIdString, lastSyncedTime);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}


+ (IMApiStatus *)getSyncedFriendHistoryMessageWithId:(NSString *)userId withFrinedId:(NSString *)friendId withPacketId:(NSString *)packetId withLastSyncedTime:(long long)lastSyncedTime withLimit:(NSInteger)limit withDirection:(NSInteger)direction;
{
    UserIdentity userIdValue([userId longLongValue]);
    UserIdentity friendIdValue([friendId longLongValue]);
    std::string packetIdString([packetId UTF8String]);
    
    imsdk::ApiStatus apiStatus = chatManager->getSyncedFriendHistoryMessage(userIdValue, friendIdValue, packetIdString, lastSyncedTime, (int)limit, (int)direction);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}


+ (IMApiStatus *)getSyncedGroupHistoryMessageWithId:(NSString *)userId withGroupId:groupId withPacketId:(NSString *)packetId withLastSyncedTime:(long long)lastSyncedTime withLimit:(NSInteger)limit withDirection:(NSInteger)direction;
{
    UserIdentity userIdValue([userId longLongValue]);
    GroupIdentity groupIdValue([groupId longLongValue]);
    std::string packetIdString([packetId UTF8String]);
    
    imsdk::ApiStatus apiStatus = chatManager->getSyncedGroupHistoryMessage(userIdValue, groupIdValue, packetIdString, lastSyncedTime, (int)limit, (int)direction);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}

+ (IMApiStatus *)getMyGroupListPagingWithId:(NSString *)userId withPacketId:(NSString *)packetId withPivotId:(NSString *)pivotId withLimit:(NSInteger)limit withDirection:(NSInteger)direction
{
    UserIdentity userIdValue([userId longLongValue]);
    std::string packetIdString([packetId UTF8String]);
    std::string pivotIdString([pivotId UTF8String]);
    
    imsdk::ApiStatus apiStatus = chatManager->getMyGroupListPaging(userIdValue, packetIdString, pivotIdString, (int)limit, (int)direction);
    return [IMApiStatus initWithPacketId:[NSString stringWithUTF8String:apiStatus.getPacketId().c_str()] withErrorType:apiStatus.getErrorCode()];
}


@end

@implementation IMInternetCheckerAdapter

+ (void)initInternetCheckerWithIpListFilePath:(NSString *)ipListFilePath
{
    std::string ipListFilePathString((ipListFilePath!=nil)?[ipListFilePath UTF8String]:"");

    if(internetChecker == nil)
    {
        internetChecker = new internetchecker::InternetChecker();
        internetChecker->setIpListFilePath(ipListFilePathString);
        internetChecker->populateIPListIfNeeded();
    }
}

+ (BOOL) checkInternetConnection
{
    return internetChecker->checkInternetConnection();
}

@end


@implementation IPVDataEncryption

+ (imsdk::ByteArray)toByteArrayWithData:(NSData *)data
{
    NSUInteger dataLength = [data length] / sizeof(unsigned char);
    unsigned char *dataArray = (unsigned char *)[data bytes];
    imsdk::ByteArray dataBytes(dataArray, (int)dataLength);

    return dataBytes;
}

+ (NSData *)toNSDataWithBytes:(imsdk::ByteArray)bytes
{
    NSData* data = [NSData dataWithBytes:(const void *)bytes.getDataPtr() length:sizeof(char)*bytes.size()];
    return data;
}

+ (NSData *)encryptDataWithData:(NSData *)data withKey:(NSData *)key withStartIndex:(NSInteger)startIndex
{
    if(data == nil || key == nil) {
        NSData* emptyData = [[NSData alloc] init];
        return emptyData;
    }
    imsdk::ByteArray dataBytes = [self toByteArrayWithData:data];
    imsdk::ByteArray keyBytes = [self toByteArrayWithData:key];

    imsdk::ByteArray encryptedBytes = dataEncryption->encryptMessage(dataBytes, keyBytes, (int)startIndex);

    return [self toNSDataWithBytes:encryptedBytes];
}

+ (NSData *)DecryptDataWithData:(NSData *)data withKey:(NSData *)key withStartIndex:(NSInteger)startIndex
{
    if(data == nil || key == nil) {
        NSData* emptyData = [[NSData alloc] init];
        return emptyData;
    }
    imsdk::ByteArray dataBytes = [self toByteArrayWithData:data];
    imsdk::ByteArray keyBytes = [self toByteArrayWithData:key];

    imsdk::ByteArray decryptedBytes = dataEncryption->decryptMessage(dataBytes, keyBytes, (int)startIndex);

    return [self toNSDataWithBytes:decryptedBytes];
}

+ (NSString *)getSessionlessKeyWithServerAddress:(NSString *)serverAddress withRingId:(NSString *)ringId
{
    std::string serverAddressString((serverAddress!=nil)?[serverAddress UTF8String]:"");
    UserIdentity ringIdValue((ringId!=nil)?[ringId longLongValue]:0);

    return [NSString stringWithUTF8String:dataEncryption->getSessionlessKey(serverAddressString, ringIdValue).c_str()];
}

@end
