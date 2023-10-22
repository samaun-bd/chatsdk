//
//  IMHandlerDelegate.m
//  ringID
//
//  Created by Sumon on 11/2/15.
//  Copyright © 2015 IPVision Canada Inc. All rights reserved.
//

#import "IMHandlerDelegate.h"

@implementation IMHandlerDelegate

+ (instancetype)sharedInstance
{
    static dispatch_once_t once;
    static id sharedInstance;
    dispatch_once(&once, ^{
        sharedInstance = [[IMHandlerDelegate alloc] init];
    });
    return sharedInstance;
}

- (instancetype)init
{
    self = [super init];
    return self;
}

- (void)receivedFriendChatBindPortWithId:userId withFriendID:(NSString *)friendId withDate:(long long)date withPacketId:(NSString *)packetId withIsAnonymous:(BOOL)isAnonymous
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatBindPortWithId:withFriendID:withDate:withPacketId:withIsAnonymous:)])
        {
            [weakSelf.delegate receivedFriendChatBindPortWithId:userId withFriendId:friendId withDate:date withPacketId:packetId withIsAnonymous:isAnonymous];
        }
    });
}

- (void)receivedFriendChatRegisterFailureWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withIsAnonymous:(BOOL)isAnonymous
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatRegisterFailureWithId:withFriendId:withPacketId:withIsAnonymous:)])
        {
            [weakSelf.delegate receivedFriendChatRegisterFailureWithId:userId withFriendId:friendId withPacketId:packetId withIsAnonymous:isAnonymous];
        }
    });
}

-(void)receivedGeneralEncryptedPacketWithUserId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withType:(NSInteger)type withInfoType:(NSInteger)infoType withInfo:(NSString *)info
{
	 __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGeneralEncryptedPacketWithUserId:withFriendId:withPacketId:withType:withInfoType:withInfo:)])
        {
            [weakSelf.delegate receivedGeneralEncryptedPacketWithUserId:userId withFriendId:friendId withPacketId:packetId withType:type withInfoType:infoType withInfo:info];
        }
    });
}

-(void)receivedGeneralEncryptedConfirmationWithUserId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withType:(NSInteger)type withInfoType:(NSInteger)infoType
{
	 __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGeneralEncryptedConfirmationWithUserId:withFriendId:withPacketId:withType:withInfoType:)])
        {
            [weakSelf.delegate receivedGeneralEncryptedConfirmationWithUserId:userId withFriendId:friendId withPacketId:packetId withType:type withInfoType:infoType];
        }
    });
}


- (void)receivedFriendChatRegistrationExpiredWithId:(NSString *)userId withFriendId:(NSString *)friendId withIsAnonymous:(BOOL)isAnonymous
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatRegistrationExpiredWithId:withFriendId:withIsAnonymous:)])
        {
            [weakSelf.delegate receivedFriendChatRegistrationExpiredWithId:userId withFriendId:friendId withIsAnonymous:isAnonymous];
        }
    });
}

- (void)receivedFriendChatUnregisterWithId:(NSString *)userId withFriendId:(NSString *)friendId withOnlineStatus:(IMSDK_Presence)status withMood:(IMSDK_MoodType)mood withIsAnonymous:(BOOL)isAnonymous withProfileType:(NSInteger)profileType
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatUnregisterWithId:withFriendId:withOnlineStatus:withMood:withIsAnonymous:withProfileType:)])
        {
            [weakSelf.delegate receivedFriendChatUnregisterWithId:userId withFriendId:friendId withOnlineStatus:status withMood:mood withIsAnonymous:isAnonymous withProfileType:profileType];
        }
    });
}

- (void)receivedGroupChatBindPortWithId:(NSString *)groupId withDate:(long long)date withPacketId:(NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupChatBindPortWithId:withDate:withPacketId:)])
        {
            [weakSelf.delegate receivedGroupChatBindPortWithId:groupId withDate:date withPacketId:packetId];
        }
    });
}

- (void)receivedGroupChatRegisterFailureWithId:(NSString *)groupId withPacketId:(NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupChatRegisterFailureWithId:withPacketId:)])
        {
            [weakSelf.delegate receivedGroupChatRegisterFailureWithId:groupId withPacketId:packetId];
        }
    });
}

- (void)receivedGroupChatRegistrationExpiredWithId:(NSString *)groupId withLastActivityTime:(long long)lastActivityTime
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupChatRegistrationExpiredWithId:withLastActivityTime:)])
        {
            [weakSelf.delegate receivedGroupChatRegistrationExpiredWithId:groupId withLastActivityTime:lastActivityTime];
        }
    });
}

- (void)receivedFriendChatMessageWithSenderId:(NSString *)senderId withReceiverId:(NSString *)receiverId withPacketId:(NSString *)packetId withMessageType:(IMSDK_MessageType)messageType withSecretTime:(NSInteger)secretTime withMessage:(NSString *)message withDate:(long long)date withIsSecretVisible:(BOOL)isSecretVisible withIsFromOnline:(BOOL)isFromOnline withIsAnonymous:(BOOL)isAnonymous
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatMessageWithSenderId:withReceiverId:withPacketId:withMessageType:withSecretTime:withMessage:withDate:withIsSecretVisible:withIsFromOnline:withIsAnonymous:)])
        {
            [weakSelf.delegate receivedFriendChatMessageWithSenderId:senderId withReceiverId:receiverId withPacketId:packetId withMessageType:messageType withSecretTime:secretTime withMessage:message withDate:date withIsSecretVisible:isSecretVisible withIsFromOnline:isFromOnline withIsAnonymous:isAnonymous];
        }
    });
}

- (void)receivedFriendChatEdittedMessageWithSenderId:(NSString *)senderId withReceiverId:(NSString *)receiverId withPacketId:(NSString *)packetId withMessageType:(IMSDK_MessageType)messageType withSecretTime:(NSInteger)secretTime withMessage:(NSString *)message withDate:(long long)date withIsSecretVisible:(BOOL)isSecretVisible withIsAnonymous:(BOOL)isAnonymous
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatEdittedMessageWithSenderId:withReceiverId:withPacketId:withMessageType:withSecretTime:withMessage:withDate:withIsSecretVisible:withIsAnonymous:)])
        {
            [weakSelf.delegate receivedFriendChatEdittedMessageWithSenderId:senderId withReceiverId:receiverId withPacketId:packetId withMessageType:messageType withSecretTime:secretTime withMessage:message withDate:date withIsSecretVisible:isSecretVisible withIsAnonymous:isAnonymous];
        }
    });
}

- (void)receivedFriendChatDeliveredWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withIsAnonymous:(BOOL)isAnonymous withIsEdited:(BOOL)isEdited withIsFromOnline:(BOOL)isFromOnline
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatDeliveredWithId:withFriendId:withPacketId:withIsAnonymous:withIsEdited:withIsFromOnline:)])
        {
            [weakSelf.delegate receivedFriendChatDeliveredWithId:userId withFriendId:friendId withPacketId:packetId withIsAnonymous:isAnonymous withIsEdited:isEdited withIsFromOnline:isFromOnline];
        }
    });
}

- (void)receivedFriendChatSeenWithId:(NSString *)userId withFriendId:(NSString *)friendId withMessageStatusList:(NSArray *)messageStatusList withIsAnonymous:(BOOL)isAnonymous
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatSeenWithId:withFriendId:withMessageStatusList:withIsAnonymous:)])
        {
            [weakSelf.delegate receivedFriendChatSeenWithId:userId withFriendId:friendId withMessageStatusList:messageStatusList withIsAnonymous:isAnonymous];
        }
    });
}

- (void)receivedFriendChatSeenConfirmationWithId:(NSString *)userId withFriendId:(NSString *)friendId withMessageStatusList:(NSArray *)messageStatusList withIsAnonymous:(BOOL)isAnonymous
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatSeenConfirmationWithId:withFriendId:withMessageStatusList:withIsAnonymous:)])
        {
            [weakSelf.delegate receivedFriendChatSeenConfirmationWithId:userId withFriendId:friendId withMessageStatusList:messageStatusList withIsAnonymous:isAnonymous];
        }
    });
}

- (void)receivedFailedToSendFriendChatWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withIsAnonymous:(BOOL)isAnonymous
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFailedToSendFriendChatWithId:withFriendId:withPacketId:withIsAnonymous:)])
        {
            [weakSelf.delegate receivedFailedToSendFriendChatWithId:userId withFriendId:friendId withPacketId:packetId withIsAnonymous:isAnonymous];
        }
    });
}

- (void)receivedFriendChatTypingWithId:(NSString *)userId withFriendId:(NSString *)friendId withIsAnonymous:(BOOL)isAnonymous
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatTypingWithId:withFriendId:withIsAnonymous:)])
        {
            [weakSelf.delegate receivedFriendChatTypingWithId:userId withFriendId:friendId withIsAnonymous:isAnonymous];
        }
    });
}

- (void)receivedFriendChatDeleteWithSenderId:(NSString *)senderId withFriendId:(NSString *)friendId withPacketIdList:(NSArray *)packetIdList withIsAnonymous:(BOOL)isAnonymous
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatDeleteWithSenderId:withFriendId:withPacketIdList:withIsAnonymous:)])
        {
            [weakSelf.delegate receivedFriendChatDeleteWithSenderId:senderId withFriendId:friendId withPacketIdList:packetIdList withIsAnonymous:isAnonymous];
        }
    });
}

- (void)receivedFriendChatDeleteRequestStatusWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId  withPacketIds:(NSArray *)packetIds withIsAnonymous:(BOOL)isAnonymous withStatus:(BOOL)status withDeleteType:(NSInteger)deleteType
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatDeleteRequestStatusWithId:withFriendId:withPacketId:withPacketIds:withIsAnonymous:withStatus:withDeleteType:)])
        {
            [weakSelf.delegate receivedFriendChatDeleteRequestStatusWithId:userId withFriendId:friendId withPacketId:packetId withPacketIds:packetIds withIsAnonymous:isAnonymous withStatus:status withDeleteType:deleteType];
        }
    });
}

- (void)receivedBlockFriendWithBlockerId:(NSString *)blockerId withBlockedId:(NSString *)blockedId withBlockValue:(BOOL)blockValue
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedBlockFriendWithBlockerId:withBlockedId:withBlockValue:)])
        {
            [weakSelf.delegate receivedBlockFriendWithBlockerId:blockerId withBlockedId:blockedId withBlockValue:blockValue];
        }
    });
}

- (void)receivedUnblockFriendWithUnblockerId:(NSString *)unblockerId withUnblockedId:(NSString *)unblockedId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedUnblockFriendWithUnblockerId:withUnblockedId:)])
        {
            [weakSelf.delegate receivedUnblockFriendWithUnblockerId:unblockerId withUnblockedId:unblockedId];
        }
    });
}

- (void)receivedBlockUnblockRequestStatusWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withStatus:(BOOL)status withIsBlockRequest:(BOOL)isBlockRequest
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedBlockUnblockRequestStatusWithId:withFriendId:withPacketId:withStatus:withIsBlockRequest:)])
        {
            [weakSelf.delegate receivedBlockUnblockRequestStatusWithId:userId withFriendId:friendId withPacketId:packetId withStatus:status withIsBlockRequest:isBlockRequest];
        }
    });
}

- (void)receivedGroupChatMessageWithId:(NSString *)groupId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withMessageType:(IMSDK_MessageType)messageType withMessage:(NSString *)message withDate:(long long)date withIsFromOnline:(BOOL)isFromOnline
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupChatMessageWithId:withFriendId:withPacketId:withMessageType:withMessage:withDate:withIsFromOnline:)])
        {
            [weakSelf.delegate receivedGroupChatMessageWithId:groupId withFriendId:friendId withPacketId:packetId withMessageType:messageType withMessage:message withDate:date withIsFromOnline:isFromOnline];
        }
    });
}

- (void)receivedGroupChatMessageDeletedWithId:(NSString *)groupId withFriendId:(NSString *)friendId withPacketIdList:(NSArray *)packetIdList
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupChatMessageDeletedWithId:withFriendId:withPacketIdList:)])
        {
            [weakSelf.delegate receivedGroupChatMessageDeletedWithId:groupId withFriendId:friendId withPacketIdList:packetIdList];
        }
    });
}

- (void)receivedGroupChatMessageDeleteRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withPacketIds:(NSArray *)packetIds withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupChatMessageDeleteRequestStatusWithId:withPacketId:withPacketIds:withStatus:)])
        {
            [weakSelf.delegate receivedGroupChatMessageDeleteRequestStatusWithId:groupId withPacketId:packetId withPacketIds:(NSArray *)packetIds withStatus:status];
        }
    });
}

- (void)receivedGroupChatEdittedMessageWithId:(NSString *)groupId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withMessageType:(IMSDK_MessageType)messageType withMessage:(NSString *)message withDate:(long long)date // Required
{
//    __block __typeof__(self) weakSelf = self;
//    dispatch_async(dispatch_get_main_queue(), ^{
//        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatBindPortWithId:)])
//        {
//            [weakSelf.delegate receivedFriendChatBindPortWithId:friendId];
//        }
//    });
    
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupChatEdittedMessageWithId:withFriendId:withPacketId:withMessageType:withMessage:withDate:)])
        {
            [weakSelf.delegate receivedGroupChatEdittedMessageWithId:groupId withFriendId:friendId withPacketId:packetId withMessageType:messageType withMessage:message withDate:date];
        }
    });
}

- (void)receivedGroupChatDeliveredWithId:(NSString *)groupId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupChatDeliveredWithId:withFriendId:withPacketId:)])
        {
            [weakSelf.delegate receivedGroupChatDeliveredWithId:groupId withFriendId:friendId withPacketId:packetId];
        }
    });
}

- (void)receivedGroupChatSeenWithId:(NSString *)groupId withPacketIdList:(NSArray *)packetIdList
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupChatSeenWithId:withPacketIdList:)])
        {
            [weakSelf.delegate receivedGroupChatSeenWithId:groupId withPacketIdList:packetIdList];
        }
    });
}

- (void)receivedRequestedGroupSeenListWithId:(NSString *)groupId withPacketId:(NSString *)packetId withMemberList:(NSArray *)memberList
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedRequestedGroupSeenListWithId:withPacketId:withMemberList:)])
        {
            [weakSelf.delegate receivedRequestedGroupSeenListWithId:groupId withPacketId:packetId withMemberList:memberList];
        }
    });
}

- (void)receivedGroupChatSentWithId:(NSString *)groupId withPacketId:(NSString *)packetId withIsEdited:(BOOL)isEdited
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupChatSentWithId:withPacketId:withIsEdited:)])
        {
            [weakSelf.delegate receivedGroupChatSentWithId:groupId withPacketId:packetId withIsEdited:isEdited];
        }
    });
}

- (void)receivedFailedToSendGroupChatWithId:(NSString *)groupId withPacketId:(NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFailedToSendGroupChatWithId:withPacketId:)])
        {
            [weakSelf.delegate receivedFailedToSendGroupChatWithId:groupId withPacketId:packetId];
        }
    });
}

- (void)receivedGroupChatTypingWithId:(NSString *)groupId withFriendId:(NSString *)friendId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupChatTypingWithId:withFriendId:)])
        {
            [weakSelf.delegate receivedGroupChatTypingWithId:groupId withFriendId:friendId];
        }
    });
}

//- (void)receivedGroupMemberListWithId:(NSString *)groupId withMemberList:(NSArray *)memberList
//{
//    __block __typeof__(self) weakSelf = self;
//    dispatch_async(dispatch_get_main_queue(), ^{
//        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupMemberListWithId:withMemberList:)])
//        {
//            [weakSelf.delegate receivedGroupMemberListWithId:groupId withMemberList:memberList];
//        }
//    });
//}

- (void)receivedGroupMemberLeaveRemoveWithId:(NSString *)groupId withFriendId:(NSString *)friendId withMemberList:(NSArray *)memberList withPacketId:(NSString *)packetId withIsHide:(BOOL)isHide
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupMemberLeaveRemoveWithId:withFriendId:withMemberList:withPacketId:withIsHide:)])
        {
            [weakSelf.delegate receivedGroupMemberLeaveRemoveWithId:groupId withFriendId:friendId withMemberList:memberList withPacketId:packetId withIsHide:isHide];
        }
    });
}

- (void)receivedGroupMemberAddWithId:(NSString *)groupId withFriendId:(NSString *)friendId withMemberList:(NSArray *)memberList withPacketId:(NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupMemberAddWithId:withFriendId:withMemberList:withPacketId:)])
        {
            [weakSelf.delegate receivedGroupMemberAddWithId:groupId withFriendId:friendId withMemberList:memberList withPacketId:packetId];
        }
    });
}

- (void)receivedGroupMemberStatusChangeWithId:(NSString *)groupId withFriendId:(NSString *)friendId withMemberList:(NSArray *)memberList withPacketId:(NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupMemberStatusChangeWithId:withFriendId:withMemberList:withPacketId:)])
        {
            [weakSelf.delegate receivedGroupMemberStatusChangeWithId:groupId withFriendId:friendId withMemberList:memberList withPacketId:packetId];
        }
    });
}

//- (void)receivedGroupInformationWithId:(NSString *)groupId withGroupName:(NSString *)groupName withFriendId:(NSString *)friendId withImageUrl:(NSString *)imageUrl withUpdateValue:(BOOL)isUpdate
//{
//    __block __typeof__(self) weakSelf = self;
//    dispatch_async(dispatch_get_main_queue(), ^{
//        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupInformationWithId:withGroupName:withImageUrl:withUpdateValue:)])
//        {
//            [weakSelf.delegate receivedGroupInformationWithId:groupId withGroupName:groupName withImageUrl:imageUrl withUpdateValue:isUpdate];
//        }
//    });
//}

//- (void)receivedGroupMemberListConfirmationWithId:(NSString *)groupId withPacketId:(NSString *)packetId
//{
//    __block __typeof__(self) weakSelf = self;
//    dispatch_async(dispatch_get_main_queue(), ^{
//        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupMemberListConfirmationWithId:withPacketId:)])
//        {
//            [weakSelf.delegate receivedGroupMemberListConfirmationWithId:groupId withPacketId:packetId];
//        }
//    });
//}

- (void)receivedGroupMemberRemoveLeaveRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status withIsHide:(BOOL)isHide
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupMemberRemoveLeaveRequestStatusWithId:withPacketId:withStatus:withIsHide:)])
        {
            [weakSelf.delegate receivedGroupMemberRemoveLeaveRequestStatusWithId:groupId withPacketId:packetId withStatus:status withIsHide:isHide];
        }
    });
}

- (void)receivedGroupMemberAddRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupMemberAddRequestStatusWithId:withPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedGroupMemberAddRequestStatusWithId:groupId withPacketId:packetId withStatus:status];
        }
    });
}

//- (void)receivedGroupInformationConfirmationWithId:(NSString *)groupId withPacketId:(NSString *)packetId withIsUpdate:(BOOL)isUpdate
//{
//    __block __typeof__(self) weakSelf = self;
//    dispatch_async(dispatch_get_main_queue(), ^{
//        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupInformationConfirmationWithId:withPacketId:withIsUpdate:)])
//        {
//            [weakSelf.delegate receivedGroupInformationConfirmationWithId:groupId withPacketId:packetId withIsUpdate:isUpdate];
//        }
//    });
//}

- (void)receivedGroupMemberStatusChangeRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupMemberStatusChangeRequestStatusWithId:withPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedGroupMemberStatusChangeRequestStatusWithId:groupId withPacketId:packetId withStatus:status];
        }
    });
}

- (void)shouldCheckFriendPresenceWithId:(NSString *)userId withFriendId:(NSString *)friendId withIsAnonymous:(BOOL)isAnonymous withProfileType:(NSInteger)profileType
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(shouldCheckFriendPresenceWithId:withFriendId:withIsAnonymous:withProfileType:)])
        {
            [weakSelf.delegate shouldCheckFriendPresenceWithId:userId withFriendId:friendId withIsAnonymous:isAnonymous withProfileType:profileType];
        }
    });
}

- (void)shouldCheckServerAddressForFriendWithId:(NSString *)userId withFriendId:(NSString *)friendId withIsAnonymous:(BOOL)isAnonymous
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(shouldCheckServerAddressForFriendWithId:withFriendId:withIsAnonymous:)])
        {
            [weakSelf.delegate shouldCheckServerAddressForFriendWithId:userId withFriendId:friendId withIsAnonymous:isAnonymous];
        }
    });
}

- (void)shouldCheckServerAddressForGroupWithId:(NSString *)groupId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(shouldCheckServerAddressForGroupWithId:)])
        {
            [weakSelf.delegate shouldCheckServerAddressForGroupWithId:groupId];
        }
    });
}

- (void)shouldCheckOfflineServerAddress
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(shouldCheckOfflineServerAddress)])
        {
            [weakSelf.delegate shouldCheckOfflineServerAddress];
        }
    });
}

- (void)shouldUpdateUserPassword
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(shouldUpdateUserPassword)])
        {
            [weakSelf.delegate shouldUpdateUserPassword];
        }
    });
}

- (void)receivedServerTimeSyncedWithTimeDifference:(long long)timeDifference
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedServerTimeSyncedWithTimeDifference:)])
        {
            [weakSelf.delegate receivedServerTimeSyncedWithTimeDifference:timeDifference];
        }
    });
}

- (void) receivedFriendHistoryMessageWithId:(NSString *)userId withFriendId:(NSString *)friendId withMessageList:(NSArray *)messageList
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendHistoryMessageWithId:withFriendId:withMessageList:)])
        {
            [weakSelf.delegate receivedFriendHistoryMessageWithId:userId withFriendId:friendId withMessageList:messageList];
        }
    });
}

- (void) receivedFriendMessageStatusWithId:(NSString *)userId withFriendId:(NSString *)friendId withMessageStatusList:(NSArray *)messageStatusList
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendMessageStatusWithId:withFriendId:withMessageStatusList:)])
        {
            [weakSelf.delegate receivedFriendMessageStatusWithId:userId withFriendId:friendId withMessageStatusList:messageStatusList];
        }
    });
}

- (void) receivedGroupHistoryMessageWithId:(NSString *)groupId withMessageList:(NSArray *)messageList
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupHistoryMessageWithId:withMessageList:)])
        {
            [weakSelf.delegate receivedGroupHistoryMessageWithId:groupId withMessageList:messageList];
        }
    });
}

- (void) receivedGroupInformationWithmembersWithId:(NSString *)groupId withGroupName:(NSString *)name withGroupUrl:(NSString*)url withMemberList:(NSArray *)memberList
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupInformationWithmembersWithId:withGroupName:withGroupUrl:withMemberList:)])
        {
            [weakSelf.delegate receivedGroupInformationWithmembersWithId:groupId withGroupName:name withGroupUrl:url withMemberList:memberList];
        }
    });
}

- (void) receivedGroupActivityWithActivityList:(NSArray *)activityList
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupActivityWithActivityList:)])
        {
            [weakSelf.delegate receivedGroupActivityWithActivityList:activityList];
        }
    });
}

- (void) receivedMyGroupListWithList:(NSArray *)groupList
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedMyGroupListWithList:)])
        {
            [weakSelf.delegate receivedMyGroupListWithList:groupList];
        }
    });
}

- (void) receivedMyGroupListPagingWithList:(NSArray *)groupList withPivotid:(NSString *)pivotId withDirection:(NSInteger)direction
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedMyGroupListPagingWithList:withPivotid:withDirection:)])
        {
            [weakSelf.delegate receivedMyGroupListPagingWithList:groupList withPivotid:pivotId withDirection:direction];
        }
    });
}

- (void) receivedMyGroupListCompleted
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedMyGroupListCompleted)])
        {
            [weakSelf.delegate receivedMyGroupListCompleted];
        }
    });
}

- (void) receivedGroupCreateRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupCreateRequestStatusWithId:withPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedGroupCreateRequestStatusWithId:groupId withPacketId:packetId withStatus:status];
        }
    });
}

- (void) receivedGroupInformationChangeRequestStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupInformationChangeRequestStatusWithId:withPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedGroupInformationChangeRequestStatusWithId:groupId withPacketId:packetId withStatus:status];
        }
    });
}

- (void) receivedGroupNameUpdateWithId:(NSString *)groupId WithFriendId:(NSString *)friendId withGroupName:(NSString *)name withPacketId:(NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupNameUpdateWithId:WithFriendId:withGroupName:withPacketId:)])
        {
            [weakSelf.delegate receivedGroupNameUpdateWithId:groupId WithFriendId:friendId withGroupName:name withPacketId:packetId];
        }
    });
}

- (void) receivedGroupProfilePicUpdateWithId:(NSString *)groupId WithFriendId:(NSString *)friendId withUrl:(NSString *)url withPacketId:(NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupProfilePicUpdateWithId:WithFriendId:withUrl:withPacketId:)])
        {
            [weakSelf.delegate receivedGroupProfilePicUpdateWithId:groupId WithFriendId:friendId withUrl:url withPacketId:packetId];
        }
    });
}

- (void) receivedPublicRoomChatRegisterSuccessWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId withNumberOfMember:(NSInteger)numberOfMember withAnonymousId:(NSString *)anonymousId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatRegisterSuccessWithRoomId:withPacketId:withNumberOfMember:withAnonymousId:)])
        {
            [weakSelf.delegate receivedPublicRoomChatRegisterSuccessWithRoomId:roomId withPacketId:packetId withNumberOfMember:numberOfMember withAnonymousId:anonymousId];
        }
    });
}

- (void) receivedPublicRoomChatRegisterFailureWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatRegisterFailureWithRoomId:withPacketId:)])
        {
            [weakSelf.delegate receivedPublicRoomChatRegisterFailureWithRoomId:roomId withPacketId:packetId];
        }
    });
}

- (void) receivedPublicRoomChatRegistrationExpiredWithRoomId:(NSString *)roomId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatRegistrationExpiredWithRoomId:)])
        {
            [weakSelf.delegate receivedPublicRoomChatRegistrationExpiredWithRoomId:roomId];
        }
    });
}

- (void) receivedPublicRoomChatDeliveredWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId withIsEdited:(BOOL)isEdited
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatDeliveredWithRoomId:withPacketId:withIsEdited:)])
        {
            [weakSelf.delegate receivedPublicRoomChatDeliveredWithRoomId:roomId withPacketId:packetId withIsEdited:isEdited];
        }
    });
}

- (void) receivedPublicRoomChatFailedToSendWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatFailedToSendWithRoomId:withPacketId:)])
        {
            [weakSelf.delegate receivedPublicRoomChatFailedToSendWithRoomId:roomId withPacketId:packetId];
        }
    });
}

- (void) receivedPublicRoomChatMessageWithRoomId:(NSString *)roomId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withMessageType:(IMSDK_MessageType)messageType withMessage:(NSString *)message withMessageDate:(long long)messageDate withMemberFullName:(NSString *)memberFullName withMemberUrl:(NSString *)memberProfileUrl
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatMessageWithRoomId:withFriendId:withPacketId:withMessageType:withMessage:withMessageDate:withMemberFullName:withMemberUrl:)])
        {
            [weakSelf.delegate receivedPublicRoomChatMessageWithRoomId:roomId withFriendId:friendId withPacketId:packetId withMessageType:messageType withMessage:message withMessageDate:messageDate withMemberFullName:memberFullName withMemberUrl:memberProfileUrl];
        }
    });
}

- (void) receivedPublicRoomListWithRoomList:(NSArray *)roomList withIsWithHistory:(BOOL)isWithHistory
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomListWithRoomList:withIsWithHistory:)])
        {
            [weakSelf.delegate receivedPublicRoomListWithRoomList:roomList withIsWithHistory:isWithHistory];
        }
    });
}

- (void) receivedPublicRoomInformationWithRoomId:(NSString *)roomId withRoomName:(NSString *)roomName withRoomUrl:(NSString *)roomUrl withPacketId:(NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomInformationWithRoomId:withRoomName:withRoomUrl:withPacketId:)])
        {
            [weakSelf.delegate receivedPublicRoomInformationWithRoomId:roomId withRoomName:roomName withRoomUrl:roomUrl withPacketId:packetId];
        }
    });
}

- (void) receivedPublicRoomChatEditedMessageWithRoomId:(NSString *)roomId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withMessageType:(IMSDK_MessageType)messageType withMessage:(NSString *)message withMessageDate:(long long)messageDate withMemberFullName:(NSString *)memberFullName withMemberUrl:(NSString *)memberProfileUrl
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatEditedMessageWithRoomId:withFriendId:withPacketId:withMessageType:withMessage:withMessageDate:withMemberFullName:withMemberUrl:)])
        {
            [weakSelf.delegate receivedPublicRoomChatEditedMessageWithRoomId:roomId withFriendId:friendId withPacketId:packetId withMessageType:messageType withMessage:message withMessageDate:messageDate withMemberFullName:memberFullName withMemberUrl:memberProfileUrl];
        }
    });
}

- (void) receivedPublicRoomChatTypingWithRoomId:(NSString *)roomId withFriendId:(NSString *)friendId withMemberName:(NSString *)memberName
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatTypingWithRoomId:withFriendId:withMemberName:)])
        {
            [weakSelf.delegate receivedPublicRoomChatTypingWithRoomId:roomId withFriendId:friendId withMemberName:memberName];
        }
    });
}

- (void) receivedPublicChatMemberListWithRoomId:(NSString *)roomId withPagingState:(NSString *)pagingState withMemberList:(NSArray *)publicChatMemberList
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicChatMemberListWithRoomId:withPagingState:withMemberList:)])
        {
            [weakSelf.delegate receivedPublicChatMemberListWithRoomId:roomId withPagingState:pagingState withMemberList:publicChatMemberList];
        }
    });
}

- (void) receivedPublicChatMemberCountChangeWithRoomId:(NSString *)roomId withNumberOfMember:(NSInteger)numberOfMember
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicChatMemberCountChangeWithRoomId:withNumberOfMember:)])
        {
            [weakSelf.delegate receivedPublicChatMemberCountChangeWithRoomId:roomId withNumberOfMember:numberOfMember];
        }
    });
}

- (void) shouldCheckServerAddressForRoomWithRoomId:(NSString *)roomId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(shouldCheckServerAddressForRoomWithRoomId:)])
        {
            [weakSelf.delegate shouldCheckServerAddressForRoomWithRoomId:roomId];
        }
    });
}

- (void) receivedPublicRoomChatHistoryWithRoomId:(NSString *)roomId withMessageList:(NSArray *)publicChatMessageList
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatHistoryWithRoomId:withMessageList:)])
        {
            [weakSelf.delegate receivedPublicRoomChatHistoryWithRoomId:roomId withMessageList:publicChatMessageList];
        }
    });
}

- (void) receivedPublicRoomChatHistoryCompletedWithRoomId:(NSString *)roomId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatHistoryCompletedWithRoomId:)])
        {
            [weakSelf.delegate receivedPublicRoomChatHistoryCompletedWithRoomId:roomId];
        }
    });
}

- (void) receivedGroupHistoryCompletedWithGroupId:(NSString *)groupId withDirection:(IMSDK_Scroll) direction
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupHistoryCompletedWithGroupId:withDirection:)])
        {
            [weakSelf.delegate receivedGroupHistoryCompletedWithGroupId:groupId withDirection:direction];
        }
    });
}

- (void) receivedGroupInformationActivityFromHistoryMessageWithGroupId:(NSString *)groupId WithActivityList:(NSArray *)activityList withDirection:(IMSDK_Scroll) direction
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupInformationActivityFromHistoryMessageWithGroupId:WithActivityList:withDirection:)])
        {
            [weakSelf.delegate receivedGroupInformationActivityFromHistoryMessageWithGroupId:groupId WithActivityList:activityList withDirection:direction];
        }
    });
}

- (void) receivedGroupInformationWithMembersRequestStatusWithGroupId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupInformationWithMembersRequestStatusWithGroupId:withPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedGroupInformationWithMembersRequestStatusWithGroupId:groupId withPacketId:packetId withStatus:status];
        }
    });
}

- (void) receivedFriendHistoryCompletedWithId:(NSString *)userId withFriendId:(NSString *)friendId withDirection:(IMSDK_Scroll)direction
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendHistoryCompletedWithId:withFriendId:withDirection:)])
        {
            [weakSelf.delegate receivedFriendHistoryCompletedWithId:userId withFriendId:friendId withDirection:direction];
        }
    });
}

- (void) receivedFriendHistoryMessageRequestStatusWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendHistoryMessageRequestStatusWithId:withFriendId:withPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedFriendHistoryMessageRequestStatusWithId:userId withFriendId:friendId withPacketId:packetId withStatus:status];
        }
    });
}

- (void) receivedGroupHistoryMessageRequestStatusWithGroupId:(NSString *)groupId withPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupHistoryMessageRequestStatusWithGroupId:withPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedGroupHistoryMessageRequestStatusWithGroupId:groupId withPacketId:packetId withStatus:status];
        }
    });
}

- (void) receivedGroupChatSeenRequestStatusWithId:(NSString *)groupId withPacketIdList:(NSArray *)packetIdList withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupChatSeenRequestStatusWithId:withPacketIdList:withStatus:)])
        {
            [weakSelf.delegate receivedGroupChatSeenRequestStatusWithId:groupId withPacketIdList:packetIdList withStatus:status];
        }
    });
}

- (void) receivedPublicRoomListRequestStatusWithPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomListRequestStatusWithPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedPublicRoomListRequestStatusWithPacketId:packetId withStatus:status];
        }
    });
}

- (void) receivedPublicRoomInformationRequestFailedWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomInformationRequestFailedWithRoomId:withPacketId:)])
        {
            [weakSelf.delegate receivedPublicRoomInformationRequestFailedWithRoomId:roomId withPacketId:packetId];
        }
    });
}

- (void) receivedPublicRoomChatHistoryRequestStatusWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatHistoryRequestStatusWithRoomId:withPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedPublicRoomChatHistoryRequestStatusWithRoomId:roomId withPacketId:packetId withStatus:status];
        }
    });
}

- (void) receivedPublicRoomMemberListRequestStatusWithRoomId:(NSString *)roomId withPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomMemberListRequestStatusWithRoomId:withPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedPublicRoomMemberListRequestStatusWithRoomId:roomId withPacketId:packetId withStatus:status];
        }
    });
}

- (void) receivedPublicRoomChatMessageDeletedWithId:(NSString *)roomId withPacketIdList:(NSArray *)packetIdList
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatMessageDeletedWithId:withPacketIdList:)])
        {
            [weakSelf.delegate receivedPublicRoomChatMessageDeletedWithId:roomId withPacketIdList:packetIdList];
        }
    });
}

- (void) receivedPublicRoomChatMessageLikedWithId:(NSString *)roomId withPacketId:(NSString *)packetId withLikerId:(NSString *)likerId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatMessageLikedWithId:withPacketId:withLikerId:)])
        {
            [weakSelf.delegate receivedPublicRoomChatMessageLikedWithId:roomId withPacketId:packetId withLikerId:likerId];
        }
    });
}

- (void) receivedPublicRoomChatMessageUnlikedWithId:(NSString *)roomId withPacketId:(NSString *)packetId withUnlikerId:(NSString *)unlikerId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatMessageUnlikedWithId:withPacketId:withUnlikerId:)])
        {
            [weakSelf.delegate receivedPublicRoomChatMessageUnlikedWithId:roomId withPacketId:packetId withUnlikerId:unlikerId];
        }
    });
}

- (void) receivedPublicRoomChatCategoryListWithList:(NSArray *)categoryList
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatCategoryListWithList:)])
        {
            [weakSelf.delegate receivedPublicRoomChatCategoryListWithList:categoryList];
        }
    });
}

- (void) receivedPublicRoomChatMessageLikeListWithId:(NSString *)roomId withPacketId:(NSString *)packetId withMemberList:(NSArray *)memberList
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatMessageLikeListWithId:withPacketId:withMemberList:)])
        {
            [weakSelf.delegate receivedPublicRoomChatMessageLikeListWithId:roomId withPacketId:packetId withMemberList:memberList];
        }
    });
}

- (void) receivedPublicRoomChatDeleteRequestStatusWithId:(NSString *)roomId withPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatDeleteRequestStatusWithId:withPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedPublicRoomChatDeleteRequestStatusWithId:roomId withPacketId:packetId withStatus:status];
        }
    });
}

- (void) receivedPublicRoomChatLikeUnlikeRequestStatusWithId:(NSString *)roomId withPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatLikeUnlikeRequestStatusWithId:withPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedPublicRoomChatLikeUnlikeRequestStatusWithId:roomId withPacketId:packetId withStatus:status];
        }
    });
}

- (void) receivedPublicRoomChatReportRequestStatusWithId:(NSString *)roomId withPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatReportRequestStatusWithId:withPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedPublicRoomChatReportRequestStatusWithId:roomId withPacketId:packetId withStatus:status];
        }
    });
}

- (void) receivedPublicRoomChatLikeListRequestStatusWithId:(NSString *)roomId withPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatLikeListRequestStatusWithId:withPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedPublicRoomChatLikeListRequestStatusWithId:roomId withPacketId:packetId withStatus:status];
        }
    });
}

- (void) receivedPublicRoomChatCategoryListRequestStatusWithPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedPublicRoomChatCategoryListRequestStatusWithPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedPublicRoomChatCategoryListRequestStatusWithPacketId:packetId withStatus:status];
        }
    });
}

- (void) receivedFriendConversationListWithId:(NSString *)userId withList:(NSArray *)friendConversationList withIsFromSynced:(BOOL)isFromSynced
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendConversationListWithId:withList:withIsFromSynced:)])
        {
            [weakSelf.delegate receivedFriendConversationListWithId:userId withList:friendConversationList withIsFromSynced:isFromSynced];
        }
    });
}

- (void) receivedGroupConversationListWithList:(NSArray *)groupConversationList withIsFromSynced:(BOOL)isFromSynced
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupConversationListWithList:withIsFromSynced:)])
        {
            [weakSelf.delegate receivedGroupConversationListWithList:groupConversationList withIsFromSynced:isFromSynced];
        }
    });
}

- (void) receivedConversationListCompletedWithId:(NSString *)userId withIsFromSynced:(BOOL)isFromSynced
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedConversationListCompletedWithId:withIsFromSynced:)])
        {
            [weakSelf.delegate receivedConversationListCompletedWithId:userId withIsFromSynced:isFromSynced];
        }
    });
}

- (void) receivedConversationListDeleteRequestStatusWithId:(NSString *)userId withPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedConversationListDeleteRequestStatusWithId:withPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedConversationListDeleteRequestStatusWithId:userId withPacketId:packetId withStatus:status];
        }
    });
}

- (void) receivedConversationListMarkRequestStatusWithId:(NSString *)userId withPacketId:(NSString *)packetId withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedConversationListMarkRequestStatusWithId:withPacketId:withStatus:)])
        {
            [weakSelf.delegate receivedConversationListMarkRequestStatusWithId:userId withPacketId:packetId withStatus:status];
        }
    });
}

- (void) receivedNetworkDataCountWithData:(IMNetworkDataModel *)data
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedNetworkDataCountWithData:)])
        {
            [weakSelf.delegate receivedNetworkDataCountWithData:data];
        }
    });
}


- (void) receivedFriendFileManifestUploadedWithId:(NSString *)userId
                                     withFriendId:(NSString *)friendId
                                     withPacketId:(NSString *)packetId
                                  withManifestUrl:(NSString *)url
                                  withMessageType:(IMSDK_MessageType)messageType
                                      withTimeout:(NSInteger)timeout
                                      withCaption:(NSString *)caption
                                  withWidthOrSize:(NSInteger)widthOrSize
                             withHeightOrDuration:(NSInteger)heightOrDuration
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendFileManifestUploadedWithId:withFriendId:withPacketId:withManifestUrl:withMessageType:withTimeout:withCaption:withWidthOrSize:withHeightOrDuration:)])
        {
            [weakSelf.delegate receivedFriendFileManifestUploadedWithId:userId withFriendId:friendId withPacketId:packetId withManifestUrl:url withMessageType:messageType withTimeout:timeout withCaption:caption withWidthOrSize:widthOrSize withHeightOrDuration:heightOrDuration];
        }
    });

}

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
                          withHeightOrDuration:(NSInteger)heightOrDuration
{

    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendIncomingChatMediaWithId:withFriendId:withPacketId:withFileName:withMessgeType:withTimeout:withMessageDate:withIsSecretVisible:withCaption:withWidthOrSize:withHeightOrDuration:)])
        {
            [weakSelf.delegate receivedFriendIncomingChatMediaWithId:userId withFriendId:friendId withPacketId:packetId withFileName:fileName withMessgeType:messageType withTimeout:timeout withMessageDate:date withIsSecretVisible:isSecretVisible withCaption:caption withWidthOrSize:widthOrSize withHeightOrDuration:heightOrDuration];
        }
    });
}

- (void) receivedFriendChatMediaTransferProgressWithId:(NSString *)userId
                                          withFriendId:(NSString *)friendId
                                          withPacketId:(NSString *)packetId
                                          withFileName:(NSString *)fileName
                                withTransferPercentage:(double)transferPercentage
                                      withTransferType:(BOOL)isUpload
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatMediaTransferProgressWithId:withFriendId:withPacketId:withFileName:withTransferPercentage:withTransferType:)])
        {
            [weakSelf.delegate receivedFriendChatMediaTransferProgressWithId:userId withFriendId:friendId withPacketId:packetId withFileName:fileName withTransferPercentage:transferPercentage withTransferType:isUpload];
        }
    });

}

- (void) receivedFriendChatMediaTransferFailedWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withFileName:(NSString *)fileName withIsUpload:(BOOL)isUpload withIsChunkedTransfer:(BOOL)isChunkedTransfer
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatMediaTransferFailedWithId:withFriendId:withPacketId:withFileName:withIsUpload:withIsChunkedTransfer:)])
        {
            [weakSelf.delegate receivedFriendChatMediaTransferFailedWithId:userId withFriendId:friendId withPacketId:packetId withFileName:fileName withIsUpload:isUpload withIsChunkedTransfer:isChunkedTransfer];
        }
    });
}

- (void) receivedFriendChatMediaTransferCanceledWithId:(NSString *)userId
                                          withFriendId:(NSString *)friendId
                                        withCanceledBy:(NSString *)canceledBy
                                          withPacketId:(NSString *)packetId
                                          withFileName:(NSString *)fileName
                                          withIsUpload:(BOOL)isUpload
                                 withIsChunkedTransfer:(BOOL)isChunkedTransfer
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatMediaTransferCanceledWithId:withFriendId:withCanceledBy:withPacketId:withFileName:withIsUpload:withIsChunkedTransfer:)])
        {
            [weakSelf.delegate receivedFriendChatMediaTransferCanceledWithId:userId withFriendId:friendId withCanceledBy:canceledBy withPacketId:packetId withFileName:fileName withIsUpload:isUpload withIsChunkedTransfer:isChunkedTransfer];
        }
    });
}

- (void) receivedFriendChatMediaDownloadCompletedWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withFilePath:(NSString *)filePath withMessageType:(IMSDK_MessageType)messageType withTimeout:(NSInteger)timeout
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedFriendChatMediaDownloadCompletedWithId:withFriendId:withPacketId:withFilePath:withMessageType:withTimeout:)])
        {
            [weakSelf.delegate receivedFriendChatMediaDownloadCompletedWithId:userId withFriendId:friendId withPacketId:packetId withFilePath:filePath withMessageType:messageType withTimeout:timeout];
        }
    });
}

- (void) receivedGroupFileManifestUploadedWithId:(NSString *)groupId
                                    withPacketId:(NSString *)packetId
                                 withManifestUrl:(NSString *)url
                                 withMessageType:(IMSDK_MessageType)messageType
                                     withCaption:(NSString *)caption
                                 withWidthOrSize:(NSInteger)widthOrSize
                            withHeightOrDuration:(NSInteger)heightOrDuration
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupFileManifestUploadedWithId:withPacketId:withManifestUrl:withMessageType:withCaption:withWidthOrSize:withHeightOrDuration:)])
        {
            [weakSelf.delegate receivedGroupFileManifestUploadedWithId:groupId withPacketId:packetId withManifestUrl:url withMessageType:messageType withCaption:caption withWidthOrSize:widthOrSize withHeightOrDuration:heightOrDuration];
        }
    });
}

-(void) receivedGroupIncomingChatMediaWithFriendId:(NSString *)friendId
                                       withGroupId:(NSString *)groupId
                                      withPacketId:(NSString *)packetId
                                      withFileName:(NSString *)fileName
                                    withMessgeType:(IMSDK_MessageType)messageType
                                   withMessageDate:(long long)date
                                       withCaption:(NSString *)caption
                                   withWidthOrSize:(NSInteger)widthOrSize
                              withHeightOrDuration:(NSInteger)heightOrDuration
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupIncomingChatMediaWithFriendId:withGroupId:withPacketId:withFileName:withMessgeType:withMessageDate:withCaption:withWidthOrSize:withHeightOrDuration:)])
        {
            [weakSelf.delegate receivedGroupIncomingChatMediaWithFriendId:friendId withGroupId:groupId withPacketId:packetId withFileName:fileName withMessgeType:messageType withMessageDate:date withCaption:caption withWidthOrSize:widthOrSize withHeightOrDuration:heightOrDuration];
        }
    });
}

- (void) receivedGroupChatMediaTransferProgressWithFriendId:(NSString *)friendId
                                                withGroupId:(NSString *)groupId
                                               withPacketId:(NSString *)packetId
                                               withFileName:(NSString *)fileName
                                     withTransferPercentage:(double)transferPercentage
                                           withTransferType:(BOOL)isUpload
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupChatMediaTransferProgressWithFriendId:withGroupId:withPacketId:withFileName:withTransferPercentage:withTransferType:)])
        {
            [weakSelf.delegate receivedGroupChatMediaTransferProgressWithFriendId:friendId withGroupId:groupId withPacketId:packetId withFileName:fileName withTransferPercentage:transferPercentage withTransferType:isUpload];
        }
    });
}

- (void) receivedGroupChatMediaTransferFailedWithId:(NSString *)friendId
                                        withGroupId:(NSString *)groupId
                                       withPacketId:(NSString *)packetId
                                       withFileName:(NSString *)fileName
                                       withIsUpload:(BOOL)isUpload
                              withIsChunkedTransfer:(BOOL)isChunkedTransfer
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupChatMediaTransferFailedWithId:withGroupId:withPacketId:withFileName:withIsUpload:withIsChunkedTransfer:)])
        {
            [weakSelf.delegate receivedGroupChatMediaTransferFailedWithId:friendId withGroupId:groupId withPacketId:packetId withFileName:fileName withIsUpload:isUpload withIsChunkedTransfer:isChunkedTransfer];
        }
    });
}

- (void) receivedGroupChatMediaTransferCanceledWithId:(NSString *)friendId
                                          withGroupId:(NSString *)groupId
                                       withCanceledBy:(NSString *)canceledBy
                                         withPacketId:(NSString *)packetId
                                         withFileName:(NSString *)fileName
                                         withIsUpload:(BOOL)isUpload
                                withIsChunkedTransfer:(BOOL)isChunkedTransfer
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupChatMediaTransferCanceledWithId:withGroupId:withCanceledBy:withPacketId:withFileName:withIsUpload:withIsChunkedTransfer:)])
        {
            [weakSelf.delegate receivedGroupChatMediaTransferCanceledWithId:friendId withGroupId:groupId withCanceledBy:canceledBy withPacketId:packetId withFileName:fileName withIsUpload:isUpload withIsChunkedTransfer:isChunkedTransfer];
        }
    });
}

- (void) receivedGroupChatMediaDownloadCompletedWithId:(NSString *)friendId
                                           withGroupId:(NSString *)groupId
                                          withPacketId:(NSString *)packetId
                                          withFilePath:(NSString *)filePath
                                       withMessageType:(IMSDK_MessageType)messageType
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGroupChatMediaDownloadCompletedWithId:withGroupId:withPacketId:withFilePath:withMessageType:)])
        {
            [weakSelf.delegate receivedGroupChatMediaDownloadCompletedWithId:friendId withGroupId:groupId withPacketId:packetId withFilePath:filePath withMessageType:messageType];
        }
    });
}

- (void)shouldUpdateAppSessionID
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(shouldUpdateAppSessionID)])
        {
            [weakSelf.delegate shouldUpdateAppSessionID];
        }
    });
}

- (void)receivedChatMediaTransferDirectoryErrorWithPath:(NSString *)directoryPath
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedChatMediaTransferDirectoryErrorWithPath:)])
        {
            [weakSelf.delegate receivedChatMediaTransferDirectoryErrorWithPath:directoryPath];
        }
    });
}

- (void)receivedActivaeOrDeactivateUserAccountStatusWithId:(NSString *)userId withPacketId:(NSString *)packetId withIsAccountActivate:(BOOL)isAccountActivate withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedActivaeOrDeactivateUserAccountStatusWithId:withPacketId:withIsAccountActivate:withStatus:)])
        {
            [weakSelf.delegate receivedActivaeOrDeactivateUserAccountStatusWithId:userId withPacketId:packetId withIsAccountActivate:isAccountActivate withStatus:status];
        }
    });
}


- (void)receivedGetUserInfoReceivedWithId:(NSString *)userId withFriendID:(NSString *)friendId withPacketId:(NSString *)packetId withFriendName:(NSString *)friendName withFriendRingId:(NSString *)friendRingId withFriendProfileImageUrl:(NSString *)friendProfileImageUrl withFriendProfileType:(NSInteger)friendProfileType
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGetUserInfoReceivedWithId:withFriendID:withPacketId:withFriendName:withFriendRingId:withFriendProfileImageUrl:withFriendProfileType:)])
        {
            [weakSelf.delegate receivedGetUserInfoReceivedWithId:userId withFriendID:friendId withPacketId:packetId withFriendName:friendName withFriendRingId:friendRingId withFriendProfileImageUrl:friendProfileImageUrl withFriendProfileType:friendProfileType];
        }
    });
}

- (void)receivedGetUserInfoFailureWithId:(NSString *)userId withFriendID:(NSString *)friendId withPacketId:(NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedGetUserInfoFailureWithId:withFriendID:withPacketId:)])
        {
            [weakSelf.delegate receivedGetUserInfoFailureWithId:userId withFriendID:friendId withPacketId:packetId];
        }
    });
}

- (void)receivedSyncConversationStatusWithId:(NSString *)userId withPacketId:(NSString *)packetId withSyncTime:(long long)syncTime withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedSyncConversationStatusWithId:withPacketId:withSyncTime:withStatus:)])
        {
            [weakSelf.delegate receivedSyncConversationStatusWithId:userId withPacketId:packetId withSyncTime:syncTime withStatus:status];
        }
    });
}

- (void)receivedSyncFriendHistoryStatusWithId:(NSString *)userId withFriendID:(NSString *)friendId withPacketId:(NSString *)packetId withSyncTime:(long long)syncTime withDirection:(NSInteger)direction withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedSyncFriendHistoryStatusWithId:withFriendID:withPacketId:withSyncTime:withDirection:withStatus:)])
        {
            [weakSelf.delegate receivedSyncFriendHistoryStatusWithId:userId withFriendID:friendId withPacketId:packetId withSyncTime:syncTime withDirection:direction withStatus:status];
        }
    });
}

- (void) receivedSyncFriendHistoryMessageWithId:(NSString *)userId withFriendId:(NSString *)friendId withPacketId:(NSString *)packetId withMessageList:(NSArray *)messageList withOldestMessageDate:(long long)oldestMessageDate withDirection:(NSInteger)direction
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedSyncFriendHistoryMessageWithId:withFriendId:withPacketId:withMessageList:withOldestMessageDate:withDirection:)])
        {
            [weakSelf.delegate receivedSyncFriendHistoryMessageWithId:userId withFriendId:friendId withPacketId:packetId withMessageList:messageList withOldestMessageDate:oldestMessageDate withDirection:direction];
        }
    });
}

- (void)receivedSyncFriendHistoryMessageCompletedWithId:(NSString *)userId withFriendID:(NSString *)friendId withPacketId:(NSString *)packetId withDirection:(NSInteger)direction
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedSyncFriendHistoryMessageCompletedWithId:withFriendID:withPacketId:withDirection:)])
        {
            [weakSelf.delegate receivedSyncFriendHistoryMessageCompletedWithId:userId withFriendID:friendId withPacketId:packetId withDirection:direction];
        }
    });
}

- (void)receivedSyncGroupHistoryStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withSyncTime:(long long)syncTime withDirection:(NSInteger)direction withStatus:(BOOL)status
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedSyncGroupHistoryStatusWithId:withPacketId:withSyncTime: withDirection:withStatus:)])
        {
            [weakSelf.delegate receivedSyncGroupHistoryStatusWithId:groupId withPacketId:packetId withSyncTime:syncTime withDirection:direction withStatus:status];
        }
    });
}

- (void) receivedSyncGroupHistoryMessageWithId:(NSString *)groupId withPacketId:(NSString *)packetId withMessageList:(NSArray *)messageList withActivityList:(NSArray *)activityList withOldestMessageDate:(long long)oldestMessageDate withDirection:(NSInteger)direction
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedSyncGroupHistoryMessageWithId:withPacketId:withMessageList:withActivityList:withOldestMessageDate:withDirection:)])
        {
            [weakSelf.delegate receivedSyncGroupHistoryMessageWithId:groupId withPacketId:packetId withMessageList:messageList withActivityList:activityList withOldestMessageDate:oldestMessageDate withDirection:direction];
        }
    });
}

- (void)receivedyncGroupHistoryMessageCompletedWithId:(NSString *)groupId withPacketId:(NSString *)packetId withDirection:(NSInteger)direction
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedyncGroupHistoryMessageCompletedWithId:withPacketId:withDirection:)])
        {
            [weakSelf.delegate receivedyncGroupHistoryMessageCompletedWithId:groupId withPacketId:packetId withDirection:direction];
        }
    });
}



//- (void)receivedSyncConversationStatusWithId:(NSString *)userId withPacketId:(NSString *)packetId withSyncTime:(long long)syncTime withStatus:(BOOL)status;

//- (void)receivedSyncFriendHistoryStatusWithId:(NSString *)userId withFriendID:(NSString *)friendId withPacketId:(NSString *)packetId withSyncTime:(long long)syncTime withStatus:(BOOL)status;

//- (void)receivedSyncGroupHistoryStatusWithId:(NSString *)groupId withPacketId:(NSString *)packetId withSyncTime:(long long)syncTime withStatus:(BOOL)status;





//- (void) receivedFileTransferProgressWithFileId:(long long)fileID withFriendName:(long long)friendName withReceivedLength:(long long)receivedLength
//{
//    __block __typeof__(self) weakSelf = self;
//    dispatch_async(dispatch_get_main_queue(), ^{
//        if([weakSelf.delegate respondsToSelector:@selector(receivedFileTransferProgressWithFileId:withFriendName:withReceivedLength:)])
//        {
//            [weakSelf.delegate receivedFileTransferProgressWithFileId:fileID withFriendName:friendName withReceivedLength:receivedLength];
//        }
//    });
//}
//
//- (void) receivedFileTransferCompletedWithFileId:(long long)fileID withFriendName:(long long)friendName withReceivedLength:(long long)receivedLength
//{
//    __block __typeof__(self) weakSelf = self;
//    dispatch_async(dispatch_get_main_queue(), ^{
//        if([weakSelf.delegate respondsToSelector:@selector(receivedFileTransferCompletedWithFileId:withFriendName:withReceivedLength:)])
//        {
//            [weakSelf.delegate receivedFileTransferCompletedWithFileId:fileID withFriendName:friendName withReceivedLength:receivedLength];
//        }
//    });
//}
//
//- (void) receivedFileTransferCanceledWithFileId:(long long)fileID withFriendName:(long long)friendName withReceivedLength:(long long)receivedLength
//{
//    __block __typeof__(self) weakSelf = self;
//    dispatch_async(dispatch_get_main_queue(), ^{
//        if([weakSelf.delegate respondsToSelector:@selector(receivedFileTransferCanceledWithFileId:withFriendName:withReceivedLength:)])
//        {
//            [weakSelf.delegate receivedFileTransferCanceledWithFileId:fileID withFriendName:friendName withReceivedLength:receivedLength];
//        }
//    });
//}
//
//- (void) receivedFileTransferFailedWithFileId:(long long)fileID withFriendName:(long long)friendName withReceivedLength:(long long)receivedLength
//{
//    __block __typeof__(self) weakSelf = self;
//    dispatch_async(dispatch_get_main_queue(), ^{
//        if([weakSelf.delegate respondsToSelector:@selector(receivedFileTransferFailedWithFileId:withFriendName:withReceivedLength:)])
//        {
//            [weakSelf.delegate receivedFileTransferFailedWithFileId:fileID withFriendName:friendName withReceivedLength:receivedLength];
//        }
//    });
//}





//Live-stream-chat
- (void)receivedLiveStreamChatRegisterSuccessWithPublisherId: (NSString *)publisherId withPacketId: (NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedLiveStreamChatRegisterSuccessWithPublisherId:withPacketId:)])
        {
            [weakSelf.delegate receivedLiveStreamChatRegisterSuccessWithPublisherId:publisherId withPacketId:packetId];
        }
    });
}

- (void)receivedLiveStreamChatRegisterFailureWithPublisherId: (NSString *)publisherId withPacketId: (NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedLiveStreamChatRegisterFailureWithPublisherId:withPacketId:)])
        {
            [weakSelf.delegate receivedLiveStreamChatRegisterFailureWithPublisherId:publisherId withPacketId:packetId];
        }
    });
}

- (void)receivedLiveStreamChatRegistrationExpiredWithPublisherId: (NSString *)publisherId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedLiveStreamChatRegistrationExpiredWithPublisherId:)])
        {
            [weakSelf.delegate receivedLiveStreamChatRegistrationExpiredWithPublisherId:publisherId];
        }
    });
}

- (void)receivedLiveStreamChatDeliveredWithPublisherId: (NSString *)publisherId withPacketId: (NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedLiveStreamChatDeliveredWithPublisherId:withPacketId:)])
        {
            [weakSelf.delegate receivedLiveStreamChatDeliveredWithPublisherId:publisherId withPacketId:packetId];
        }
    });
}

- (void)receivedLiveStreamChatFailedToSendWithPublisherId: (NSString *)publisherId withPacketId: (NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedLiveStreamChatFailedToSendWithPublisherId:withPacketId:)])
        {
            [weakSelf.delegate receivedLiveStreamChatFailedToSendWithPublisherId:publisherId withPacketId:packetId];
        }
    });
}

- (void)receivedLiveStreamChatWithPublisherId: (NSString *)publisherId withSenderId: (NSString *)senderId withPacketId: (NSString *)packetId withMessageType: (IMSDK_MessageType)messageType withMessage: (NSString *)message withMessageDate: (long long)messageDate withSenderFullName: (NSString *)senderFullName
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedLiveStreamChatWithPublisherId:withSenderId:withPacketId:withMessageType:withMessage:withMessageDate:withSenderFullName:)])
        {
            [weakSelf.delegate receivedLiveStreamChatWithPublisherId:publisherId withSenderId:senderId withPacketId:packetId withMessageType:messageType withMessage:message withMessageDate:messageDate withSenderFullName:senderFullName];
        }
    });
}

- (void)receivedLiveStreamChatTypingWithPublisherId: (NSString *)publisherId withSenderId: (NSString *)senderId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedLiveStreamChatTypingWithPublisherId:withSenderId:)])
        {
            [weakSelf.delegate receivedLiveStreamChatTypingWithPublisherId:publisherId withSenderId:senderId];
        }
    });
}

- (void)shouldCheckServerAddressForLiveStreamChatWithPublisherId: (NSString *)publisherId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(shouldCheckServerAddressForLiveStreamChatWithPublisherId:)])
        {
            [weakSelf.delegate shouldCheckServerAddressForLiveStreamChatWithPublisherId:publisherId];
        }
    });
}

- (void)receivedLiveStreamChatBlockUserRequestStatusWithBlockedUserId:(NSString *)blockedUserId withPacketId: (NSString *)packetId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedLiveStreamChatBlockUserRequestStatusWithBlockedUserId:withPacketId:)])
        {
            [weakSelf.delegate receivedLiveStreamChatBlockUserRequestStatusWithBlockedUserId:blockedUserId withPacketId:packetId];
        }
    });
}

- (void)receivedLiveStreamChatUserBlockedWithPublisherId:(NSString *)publisherId withBlockedUserId:(NSString *)blockedUserId
{
    __block __typeof__(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        if([weakSelf.delegate respondsToSelector:@selector(receivedLiveStreamChatUserBlockedWithPublisherId:withBlockedUserId:)])
        {
            [weakSelf.delegate receivedLiveStreamChatUserBlockedWithPublisherId:publisherId withBlockedUserId:blockedUserId];
        }
    });
}

@end
