//
//  IMHandlerAdapter.m
//  ringID
//
//  Created by Sumon on 11/2/15.
//  Copyright © 2015 IPVision Canada Inc. All rights reserved.
//

#import "IMGroupMemberModel.h"
#import "IMGroupModel.h"
#import "IMGroupActivityModel.h"
#import "IMMessageStatusModel.h"
#import "IMMessageModel.h"
#import "IMManager.h"
#include "IChatEventHandler.h"
#import "IMHandlerAdapter.h"
#import "IMHandlerDelegate.h"
#import "IMRoomModel.h"
#import "IMPublicChatMemberModel.h"

ChatEventHandler::ChatEventHandler()
{
    
}

ChatEventHandler::~ChatEventHandler()
{
    
}

void ChatEventHandler::onEventHandlerAttached()
{
    //NSLog(@"[RawHandler] Event handler attached");
}

void ChatEventHandler::onEventHandlerDetached()
{
    //NSLog(@"[RawHandler] Evemt handler detached");
}

void ChatEventHandler::onFriendChatRegisterSuccess(UserIdentity userId, UserIdentity friendId, long long serverDate, const std::string &packetId, bool fromAnonymousUser)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] Register success with friend %lld", (long long) friendId);
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedFriendChatBindPortWithId:userIdSting withFriendID:friendIdSting withDate:serverDate withPacketId:packetIdString withIsAnonymous:fromAnonymousUser];
    }
}

void ChatEventHandler::onFriendChatRegisterFailure(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool fromAnonymousUser)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] Register failure with friend %lld", (long long) friendId);
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedFriendChatRegisterFailureWithId:userIdSting withFriendId:friendIdSting withPacketId:packetIdString withIsAnonymous:fromAnonymousUser];
    }
}

void ChatEventHandler::onGeneralEncryptedPacketReceived(UserIdentity userID, UserIdentity friendID, const std::string &packetID, int type, int infoType, const std::string &info)
{
	
    @autoreleasepool {
        //NSLog(@"[RawHandler] Register failure with friend %lld", (long long) friendId);
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userID];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendID];
        NSString *packetIdString = [NSString stringWithUTF8String:packetID.c_str()];
		 NSString *infoString = [NSString stringWithUTF8String:information.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedGeneralEncryptedPacketWithUserId:userIdSting withFriendId:friendIdSting withPacketId:packetIdString withType:type withInfoType:infoType withInfo:infoString];
    }
}
	
void ChatEventHandler::onGeneralEncryptedPacketConfirmationReceived(UserIdentity userID, UserIdentity friendID, const std::string &packetID, int type, int infoType)
{
	 @autoreleasepool {
        //NSLog(@"[RawHandler] Register failure with friend %lld", (long long) friendId);
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userID];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendID];
        NSString *packetIdString = [NSString stringWithUTF8String:packetID.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedGeneralEncryptedConfirmationWithUserId:userIdSting withFriendId:friendIdSting withPacketId:packetIdString withType:type withInfoType:infoType];
    }
}


void ChatEventHandler::onFriendRegistrationExpired(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] Friend registration expired of %lld", (long long) friendId);
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendId];
        [[IMHandlerDelegate sharedInstance] receivedFriendChatRegistrationExpiredWithId:userIdSting withFriendId:friendIdSting withIsAnonymous:fromAnonymousUser];
    }
}

void ChatEventHandler::onFriendUnregistered(UserIdentity userId, UserIdentity friendId, int onlineStatus, int onlineMood, bool fromAnonymousUser, int profileType)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] Friend %lld has been unregistered. status = %d mood = %d", (long long) friendId, onlineStatus, onlineMood);
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendId];
        [[IMHandlerDelegate sharedInstance] receivedFriendChatUnregisterWithId:userIdSting withFriendId:friendIdSting withOnlineStatus:static_cast<IMSDK_Presence>(onlineStatus) withMood:static_cast<IMSDK_MoodType>(onlineMood) withIsAnonymous:fromAnonymousUser withProfileType:profileType];
    }
}

void ChatEventHandler::onGroupChatRegisterSuccess(GroupIdentity groupId, long long serverDate, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] Register success at group %lld", (long long) groupId);
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        [[IMHandlerDelegate sharedInstance] receivedGroupChatBindPortWithId:groupIdSting withDate:serverDate withPacketId:packetIdString];
    }
}

void ChatEventHandler::onGroupChatRegisterFailure(GroupIdentity groupId, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] Failed to register at group %lld", (long long) groupId);
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        [[IMHandlerDelegate sharedInstance] receivedGroupChatRegisterFailureWithId:groupIdSting withPacketId:packetIdString];
    }
}

void ChatEventHandler::onGroupRegistrationExpired(GroupIdentity groupId, long long lastActivityTime)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] Group registration expired of %lld", (long long) groupId);
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        [[IMHandlerDelegate sharedInstance] receivedGroupChatRegistrationExpiredWithId:groupIdSting withLastActivityTime:lastActivityTime];
    }
}

void ChatEventHandler::onFriendChatReceived(UserIdentity senderId, UserIdentity receiverId, const std::string &packetId, int messageType, int timeout, const std::string &message, long long messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser)
{
    @autoreleasepool {
        NSString *senderIdString = [NSString stringWithFormat:@"%lld",(long long)senderId];
        NSString *receiverIdString = [NSString stringWithFormat:@"%lld",(long long)receiverId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *messageString = [NSString stringWithUTF8String:message.c_str()];
        //NSLog(@"[RawHandler] New friend chat received from %lld message:%@", (long long) senderId, messageString);
    
        [[IMHandlerDelegate sharedInstance] receivedFriendChatMessageWithSenderId:senderIdString withReceiverId:receiverIdString withPacketId:packetIdString withMessageType:static_cast<IMSDK_MessageType>(messageType) withSecretTime:timeout withMessage:messageString withDate:messageDate withIsSecretVisible:isSecretVisible  withIsFromOnline:fromOnline withIsAnonymous:fromAnonymousUser];
    }
}

void ChatEventHandler::onFriendChatDelivered(UserIdentity userId, UserIdentity friendid, const std::string &packetId, bool fromAnonymousUser, bool isEdited, bool fromOnline)
{
    @autoreleasepool {
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendid];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        //NSLog(@"[RawHandler] Friend chat delivered to %lld, packetId:%@", (long long) friendid, packetIdString);
    
        [[IMHandlerDelegate sharedInstance] receivedFriendChatDeliveredWithId:userIdSting withFriendId:friendIdSting withPacketId:packetIdString withIsAnonymous:fromAnonymousUser withIsEdited:isEdited withIsFromOnline:fromOnline];

    }
}
void ChatEventHandler::onFriendChatSent(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool fromAnonymousUser)
{
    @autoreleasepool {
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        //NSLog(@"[RawHandler] Friend chat sent. packetId:%@", packetIdString);
    }
}

void ChatEventHandler::onFriendChatFailedToSend(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool fromAnonymousUser)
{
    @autoreleasepool {
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendId];
        //NSLog(@"[RawHandler] Friend chat failed to send. packetId: %@", packetIdString);
    
        [[IMHandlerDelegate sharedInstance] receivedFailedToSendFriendChatWithId:userIdSting withFriendId:friendIdSting withPacketId:packetIdString withIsAnonymous:fromAnonymousUser];
    }
}

void ChatEventHandler::onFriendChatSeen(UserIdentity userId, UserIdentity friendid, const std::vector<imsdk::SeenPacketDTO> &seenPacketList, bool fromAnonymousUser)
{
    @autoreleasepool {
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendid];
        //NSLog(@"[RawHandler] Friend chat seen of %lld",(long long) friendid);
        NSMutableArray *dtoArray = [NSMutableArray array];
        
        for (int i = 0; i < seenPacketList.size(); i++)
        {
            imsdk::SeenPacketDTO dto = seenPacketList[i];

            IMMessageStatusModel *seenPacketModel = [[IMMessageStatusModel alloc] init];
            seenPacketModel.packetId = [NSString stringWithUTF8String:dto.getPacketID().c_str()];
            seenPacketModel.messageDate = dto.getMessageDate();
            seenPacketModel.messageStatus = static_cast<IMSDK_MessageStatus>(dto.getMessageStatus());
            [dtoArray addObject:seenPacketModel];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedFriendChatSeenWithId:userIdSting withFriendId:friendIdSting withMessageStatusList:dtoArray withIsAnonymous:fromAnonymousUser];
    }
}

void ChatEventHandler::onFriendChatSeenConfirmed(UserIdentity userId, UserIdentity friendid, std::vector<imsdk::SeenPacketDTO> &seenPacketList, bool fromAnonymousUser)
{
    @autoreleasepool {
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendid];
        //NSLog(@"[RawHandler] Friend chat deleted by %lld",(long long) friendid);
    
        NSMutableArray *dtoArray = [NSMutableArray array];
    
        for (int i = 0; i < seenPacketList.size(); i++)
        {
            imsdk::SeenPacketDTO dto = seenPacketList[i];
            
            IMMessageStatusModel *seenPacketModel = [[IMMessageStatusModel alloc] init];
            seenPacketModel.packetId = [NSString stringWithUTF8String:dto.getPacketID().c_str()];
            seenPacketModel.messageDate = dto.getMessageDate();
            seenPacketModel.messageStatus = static_cast<IMSDK_MessageStatus>(dto.getMessageStatus());
            [dtoArray addObject:seenPacketModel];
        }
    
        [[IMHandlerDelegate sharedInstance] receivedFriendChatSeenConfirmationWithId:userIdSting withFriendId:friendIdSting withMessageStatusList:dtoArray withIsAnonymous:fromAnonymousUser];
    }
}

void ChatEventHandler::onFriendChatTyping(UserIdentity userId, UserIdentity friendid, bool fromAnonymousUser)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] Friend typing %lld",(long long) friendid);
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendid];
        [[IMHandlerDelegate sharedInstance] receivedFriendChatTypingWithId:userIdSting withFriendId:friendIdSting withIsAnonymous:fromAnonymousUser];
    }
}

void ChatEventHandler::onFriendChatIdle(UserIdentity friendid, bool fromAnonymousUser)
{
    @autoreleasepool {
    }
}

void ChatEventHandler::onFriendChatEdited(UserIdentity senderId, UserIdentity receiverId, const std::string &packetId, int messageType, int timeout, const std::string &message, long long messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser)
{
    @autoreleasepool {
        NSString *senderIdString = [NSString stringWithFormat:@"%lld",(long long)senderId];
        NSString *receiverIdstring = [NSString stringWithFormat:@"%lld",(long long)receiverId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *messageString = [NSString stringWithUTF8String:message.c_str()];
        //NSLog(@"[RawHandler] Friend chat edited by %lld packetId:%@ message:%@",(long long) senderId, packetIdString, messageString);
    
        [[IMHandlerDelegate sharedInstance] receivedFriendChatEdittedMessageWithSenderId:senderIdString withReceiverId:receiverIdstring withPacketId:packetIdString withMessageType:static_cast<IMSDK_MessageType>(messageType) withSecretTime:(NSInteger)timeout withMessage:messageString withDate:messageDate withIsSecretVisible:isSecretVisible withIsAnonymous:fromAnonymousUser];
    }
}

void ChatEventHandler::onFriendChatDeleted(UserIdentity senderId, UserIdentity friendId, const std::vector<std::string> &packetIdList, bool fromAnonymousUser)
{
    @autoreleasepool {
        NSString *senderIdSting = [NSString stringWithFormat:@"%lld",(long long)senderId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendId];
        //NSLog(@"[RawHandler] Friend chat deleted by %lld",(long long) friendId);
    
        NSMutableArray *packetIdArray = [NSMutableArray array];
    
        for (int i = 0; i < packetIdList.size(); i++)
        {
            NSString *packetIdString = [NSString stringWithUTF8String:packetIdList[i].c_str()];
        
            [packetIdArray addObject:packetIdString];
        }
    
        [[IMHandlerDelegate sharedInstance] receivedFriendChatDeleteWithSenderId:senderIdSting withFriendId:friendIdSting withPacketIdList:packetIdArray withIsAnonymous:fromAnonymousUser];
    }
}

void ChatEventHandler::onFriendChatDeleteRequestStatus(UserIdentity userId, UserIdentity friendid, const std::string &packetId, const std::vector<std::string> &packetIds, bool fromAnonymousUser, bool status, int deleteType)
{
    @autoreleasepool {
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendid];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];

        NSMutableArray *packetIdsArray = [NSMutableArray array];

        for (int i = 0; i < packetIds.size(); i++)
        {
            NSString *packetIdString = [NSString stringWithUTF8String:packetIds[i].c_str()];

            [packetIdsArray addObject:packetIdString];
        }
        //NSLog(@"[RawHandler] Friend chat deleted by you to friend %lld, packetId:%@",(long long)friendid, packetIdString);

        [[IMHandlerDelegate sharedInstance] receivedFriendChatDeleteRequestStatusWithId:userIdSting withFriendId:friendIdSting withPacketId:packetIdString withPacketIds:packetIdsArray withIsAnonymous:fromAnonymousUser withStatus:status withDeleteType:deleteType];
    }
}

void ChatEventHandler::onBlocked(UserIdentity blockerId, UserIdentity blockedId, long long blockUnblockDate, bool addToBlock)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] Block: blockerId %lld, blockedId %lld, addToBlock:%d", (long long) blockerId, (long long)blockedId, addToBlock);
        NSString *blockerIdSting = [NSString stringWithFormat:@"%lld",(long long)blockerId];
        NSString *blockedIdSting = [NSString stringWithFormat:@"%lld",(long long)blockedId];
        [[IMHandlerDelegate sharedInstance] receivedBlockFriendWithBlockerId:blockerIdSting withBlockedId:blockedIdSting withBlockValue:addToBlock];
    }
}

void ChatEventHandler::onUnblocked(UserIdentity blockerId, UserIdentity blockedId, long long blockUnblockDate)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] Unblocked: unblockerId %lld, unblockedId %lld" , (long long) blockerId, (long long)blockedId);
        NSString *blockerIdSting = [NSString stringWithFormat:@"%lld",(long long)blockerId];
        NSString *blockedIdSting = [NSString stringWithFormat:@"%lld",(long long)blockedId];
        [[IMHandlerDelegate sharedInstance] receivedUnblockFriendWithUnblockerId:blockerIdSting withUnblockedId:blockedIdSting];
    }
}

void ChatEventHandler::onBlockUnblockRequestStatus(UserIdentity userId, UserIdentity friendid, const std::string &packetId, long long blockUnblockDate, bool status, bool isBlockRequest)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] You blocked %lld", (long long) friendid);
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendid];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        [[IMHandlerDelegate sharedInstance] receivedBlockUnblockRequestStatusWithId:userIdSting withFriendId:friendIdSting withPacketId:packetIdString withStatus:status withIsBlockRequest:isBlockRequest];
    }
}

void ChatEventHandler::onGroupChatSent(GroupIdentity groupId, const std::string &packetId, bool isEdited)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupChatSent");
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedGroupChatSentWithId:groupIdSting withPacketId:packetIdString  withIsEdited:isEdited];
    }
}

void ChatEventHandler::onGroupChatReceived(UserIdentity friendid, GroupIdentity groupid, const std::string &packetId, int messageType, const std::string &message, long long messageDate, bool fromOnline)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupChatReceived");
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendid];
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupid];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *messageString = [NSString stringWithUTF8String:message.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedGroupChatMessageWithId:groupIdSting withFriendId:friendIdSting withPacketId:packetIdString withMessageType:static_cast<IMSDK_MessageType>(messageType) withMessage:messageString withDate:messageDate withIsFromOnline:fromOnline];
    }
}

void ChatEventHandler::onGroupChatDelivered(UserIdentity friendid, GroupIdentity groupid, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupChatDelivered");
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendid];
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupid];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedGroupChatDeliveredWithId:groupIdSting withFriendId:friendIdSting withPacketId:packetIdString];
    }
}

void ChatEventHandler::onGroupChatDeleted(UserIdentity friendid, GroupIdentity groupid, const std::vector<std::string> &packetIdList)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupChatDeleted");
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendid];
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupid];
        
        
        NSMutableArray *packetIdArray = [NSMutableArray array];
        
        for (int i = 0; i < packetIdList.size(); i++)
        {
            NSString *packetIdString = [NSString stringWithUTF8String:packetIdList[i].c_str()];
            
            [packetIdArray addObject:packetIdString];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedGroupChatMessageDeletedWithId:groupIdSting withFriendId:friendIdSting withPacketIdList:(NSArray *)packetIdArray];
    }
}

void ChatEventHandler::onGroupChatDeleteRequestStatus(GroupIdentity groupid, const std::string &packetId, const std::vector<std::string> &packetIds, bool status)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupChatDeleteConfirmed");
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupid];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];

        NSMutableArray *packetIdsArray = [NSMutableArray array];

        for (int i = 0; i < packetIds.size(); i++)
        {
            NSString *packetIdString = [NSString stringWithUTF8String:packetIds[i].c_str()];

            [packetIdsArray addObject:packetIdString];
        }

        [[IMHandlerDelegate sharedInstance] receivedGroupChatMessageDeleteRequestStatusWithId:groupIdSting withPacketId:packetIdString withPacketIds:packetIdsArray withStatus:status];
    }
}

void ChatEventHandler::onGroupChatSeen(GroupIdentity groupid, const std::vector<std::string> &packetIds)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupChatSeen");
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupid];
        
        NSMutableArray *packetIdArray = [NSMutableArray array];
        
        for (int i = 0; i < packetIds.size(); i++)
        {
            NSString *packetIdString = [NSString stringWithUTF8String:packetIds[i].c_str()];
            
            [packetIdArray addObject:packetIdString];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedGroupChatSeenWithId:groupIdSting withPacketIdList:packetIdArray];
    }
}

void ChatEventHandler::onGroupChatSeenRequestStatus(GroupIdentity groupid, const std::vector<std::string> &packetIds, bool status)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupChatSeenRequestStatus");
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupid];
        
        NSMutableArray *packetIdArray = [NSMutableArray array];
        
        for (int i = 0; i < packetIds.size(); i++)
        {
            NSString *packetIdString = [NSString stringWithUTF8String:packetIds[i].c_str()];
            
            [packetIdArray addObject:packetIdString];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedGroupChatSeenRequestStatusWithId:groupIdSting withPacketIdList:packetIdArray withStatus:status];
    }
}

void ChatEventHandler::onGroupChatMessageSeenListReceived(GroupIdentity groupId, const std::string &packetId, const std::vector<imsdk::MemberDTO> &memberList)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupChatMessageSeenListReceived");
        
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        NSMutableArray *dtoArray = [NSMutableArray array];
        
        for (int i = 0; i < memberList.size(); i++)
        {
            IMGroupMemberModel *memberModel = [[IMGroupMemberModel alloc] init];
            memberModel.friendId = [NSString stringWithFormat:@"%lld",memberList[i].getMemberIdentity()];
            memberModel.ringId = [NSString stringWithFormat:@"%lld",memberList[i].getRingId()];
            memberModel.seenTime = memberList[i].getSeenTime();
            [dtoArray addObject:memberModel];
            
            //[memberModel release];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedRequestedGroupSeenListWithId:groupIdSting withPacketId:packetIdString withMemberList:dtoArray];
    }
}

void ChatEventHandler::onGroupChatMessageSeenListRequestStatus(GroupIdentity groupId, const std::string &requestPacketId, const std::string &messagePacketId, bool status)
{

}

void ChatEventHandler::onGroupChatTyping(UserIdentity friendid, GroupIdentity groupid)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupChatTyping");
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendid];
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupid];
        
        [[IMHandlerDelegate sharedInstance] receivedGroupChatTypingWithId:groupIdSting withFriendId:friendIdSting];
    }
}

void ChatEventHandler::onGroupChatIdle(UserIdentity friendid, GroupIdentity groupid)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler]");
    }

}

void ChatEventHandler::onGroupChatEdited(UserIdentity senderId, GroupIdentity groupId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, bool fromOnline)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupChatEdited");
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)senderId];
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *messageString = [NSString stringWithUTF8String:message.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedGroupChatEdittedMessageWithId:groupIdSting withFriendId:friendIdSting withPacketId:packetIdString withMessageType:static_cast<IMSDK_MessageType>(messageType) withMessage:messageString withDate:messageDate];
    }
}

//void ChatEventHandler::onGroupMemberListReceived(GroupIdentity groupid, const std::vector<imsdk::MemberDTO> &memberList)
//{
//    //NSLog(@"[RawHandler] onGroupMemberListReceived");
//    NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupid];
//
//    NSMutableArray *dtoArray = [NSMutableArray array];
//    
//    for (int i = 0; i < memberList.size(); i++)
//    {
//        imsdk::MemberDTO dto = memberList[i];
//        
//        IMGroupMemberModel *memberModel = [[IMGroupMemberModel alloc] init];
//        memberModel.friendId = [NSString stringWithFormat:@"%lld",dto.getMemberIdentity()];
//        memberModel.friendName = [NSString stringWithUTF8String:dto.getFullName().c_str()];
//        memberModel.memberStatus = (NSInteger)dto.getStatus();
//        memberModel.memberAddedBy = [NSString stringWithFormat:@"%lld",dto.getAddedBy()];
//        
//        [dtoArray addObject:memberModel];
//        [memberModel release];
//    }
//    
//    [[IMHandlerDelegate sharedInstance] receivedGroupMemberListWithId:groupIdSting withMemberList:dtoArray];
//}

void ChatEventHandler::onGroupMemberRemovedOrLeft(UserIdentity friendid, GroupIdentity groupid, const std::vector<UserIdentity> &memberList, const std::string &packetId, bool isHide)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupMemberRemovedOrLeft");
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendid];
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupid];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSMutableArray *dtoArray = [NSMutableArray array];
        
        for (int i = 0; i < memberList.size(); i++)
        {
            IMGroupMemberModel *memberModel = [[IMGroupMemberModel alloc] init];
            memberModel.friendId = [NSString stringWithFormat:@"%lld",memberList[i]];
            [dtoArray addObject:memberModel];

            //[memberModel release];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedGroupMemberLeaveRemoveWithId:groupIdSting withFriendId:friendIdSting withMemberList:dtoArray withPacketId:packetIdString withIsHide:isHide];
    }
}

void ChatEventHandler::onGroupMemberAdded(UserIdentity friendid, GroupIdentity groupid, const std::vector<imsdk::MemberDTO> &memberList, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupMemberAdded");
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendid];
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupid];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSMutableArray *dtoArray = [NSMutableArray array];
        
        for (int i = 0; i < memberList.size(); i++)
        {
            imsdk::MemberDTO dto = memberList[i];
            IMGroupMemberModel *memberModel = [[IMGroupMemberModel alloc] init];
            memberModel.friendId = [NSString stringWithFormat:@"%lld",dto.getMemberIdentity()];
            memberModel.ringId = [NSString stringWithFormat:@"%lld",dto.getRingId()];
            memberModel.friendName = [NSString stringWithUTF8String:dto.getFullName().c_str()];
            memberModel.memberStatus = static_cast<IMSDK_MemberStatus>(dto.getStatus());
            memberModel.memberAddedBy = [NSString stringWithFormat:@"%lld",dto.getAddedBy()];
            [dtoArray addObject:memberModel];
    //            [memberModel release];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedGroupMemberAddWithId:groupIdSting withFriendId:friendIdSting withMemberList:dtoArray withPacketId:packetIdString];
    }
}

//void ChatEventHandler::onGroupInformationReceived(UserIdentity friendid, GroupIdentity groupid, const std::string &groupName, const std::string &groupUrl, int numberOfMembers, bool isUpdate)
//{
//    //NSLog(@"[RawHandler] onGroupInformationReceived");
//    NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendid];
//    NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupid];
//    NSString *groupNameString = [NSString stringWithUTF8String:groupName.c_str()];
//    NSString *imageUrlString = [NSString stringWithUTF8String:groupUrl.c_str()];
//
//    [[IMHandlerDelegate sharedInstance] receivedGroupInformationWithId:groupIdSting withGroupName:groupNameString withFriendId:friendIdSting withImageUrl:imageUrlString withUpdateValue:isUpdate];
//}

void ChatEventHandler::onGroupMemberStatusChanged(UserIdentity senderid, GroupIdentity groupid, const std::vector<imsdk::MemberDTO> &memberList, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupMemberStatusChanged");
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)senderid];
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupid];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSMutableArray *dtoArray = [NSMutableArray array];
        
        for (int i = 0; i < memberList.size(); i++)
        {
                imsdk::MemberDTO dto = memberList[i];
                
                IMGroupMemberModel *memberModel = [[IMGroupMemberModel alloc] init];
                memberModel.friendId = [NSString stringWithFormat:@"%lld",dto.getMemberIdentity()];
                memberModel.ringId = [NSString stringWithFormat:@"%lld",dto.getRingId()];
                memberModel.friendName = [NSString stringWithUTF8String:dto.getFullName().c_str()];
                memberModel.memberStatus = static_cast<IMSDK_MemberStatus>(dto.getStatus());
                memberModel.memberAddedBy = [NSString stringWithFormat:@"%lld",dto.getAddedBy()];
                
                [dtoArray addObject:memberModel];
    //            [memberModel release];
            
        }
        
        [[IMHandlerDelegate sharedInstance] receivedGroupMemberStatusChangeWithId:groupIdSting withFriendId:friendIdSting withMemberList:dtoArray withPacketId:packetIdString];
    }
}

//void ChatEventHandler::onGroupMemberListSent(GroupIdentity groupId, const std::string &packetId)
//{
//    //NSLog(@"[RawHandler] onGroupMemberListSent to %lld", (long long) groupId);
//    NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
//    NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
//    
//    [[IMHandlerDelegate sharedInstance] receivedGroupMemberListConfirmationWithId:groupIdSting withPacketId:packetIdString];
//}

void ChatEventHandler::onGroupMemberRemoveLeaveRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::vector<imsdk::MemberDTO> &memberList, bool isHide)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupMemberRemoveLeaveSent to %lld", (long long) groupId);
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedGroupMemberRemoveLeaveRequestStatusWithId:groupIdSting withPacketId:packetIdString withStatus:status withIsHide:isHide];
    }
}

void ChatEventHandler::onGroupMemberAddRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::vector<imsdk::MemberDTO> &memberList)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupMemberAddSent to %lld", (long long) groupId);
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedGroupMemberAddRequestStatusWithId:groupIdSting withPacketId:packetIdString withStatus:status];
    }
}

//void ChatEventHandler::onGroupInformationSent(GroupIdentity groupId, const std::string &packetId, bool isUpdate)
//{
//    //NSLog(@"[RawHandler] onGroupInformationSent to %lld", (long long) groupId);
//    NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
//    NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
//    
//    [[IMHandlerDelegate sharedInstance] receivedGroupInformationConfirmationWithId:groupIdSting withPacketId:packetIdString withIsUpdate:isUpdate];
//}

void ChatEventHandler::onGroupMemberStatusChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::vector<imsdk::MemberDTO> &memberList)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupMemberStatusChangeSent to %lld", (long long) groupId);
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedGroupMemberStatusChangeRequestStatusWithId:groupIdSting withPacketId:packetIdString withStatus:status];
    }
}

void ChatEventHandler::onGroupChatFailedToSend(GroupIdentity groupId, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupChatFailedToSend to %lld", (long long) groupId);
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedFailedToSendGroupChatWithId:groupIdSting withPacketId:packetIdString];
    }
}


void ChatEventHandler::shouldCheckFriendPresence(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser, int profileType)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] shouldCheckFriendPresence of %lld", (long long) friendId);
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendId];
        
        [[IMHandlerDelegate sharedInstance] shouldCheckFriendPresenceWithId:userIdSting withFriendId:friendIdSting withIsAnonymous:fromAnonymousUser withProfileType:profileType];
    }
}

void ChatEventHandler::shouldCheckServerAddressForFriend(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] shouldCheckServerAddressForFriend of %lld", (long long) friendId);
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendId];
        
        [[IMHandlerDelegate sharedInstance] shouldCheckServerAddressForFriendWithId:userIdSting withFriendId:friendIdSting withIsAnonymous:fromAnonymousUser];
    }
}

void ChatEventHandler::shouldCheckServerAddressForGroup(GroupIdentity groupId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] shouldCheckServerAddressForGroup of %lld", (long long) groupId);
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        
        [[IMHandlerDelegate sharedInstance] shouldCheckServerAddressForGroupWithId:groupIdSting];
    }
}

void ChatEventHandler::shouldCheckOfflineServerAddress()
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] shouldCheckOfflineServerAddress");
        
        [[IMHandlerDelegate sharedInstance] shouldCheckOfflineServerAddress];
    }
}

void ChatEventHandler::shouldUpdateUserPassword()
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] shouldUpdateUserPassword");

        [[IMHandlerDelegate sharedInstance] shouldUpdateUserPassword];
    }
}

void ChatEventHandler::onFriendFileTransferRequestReceived(UserIdentity friendId, std::string fileName, FileIdentity fileId, long long fileSize)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onFriendFileTransferRequestReceived");
    }
    
//    [[IMHandlerDelegate sharedInstance] receivedfile]
}

void ChatEventHandler::onServerTimeSynced(long long timeDifference)
{
    @autoreleasepool {
        [[IMHandlerDelegate sharedInstance] receivedServerTimeSyncedWithTimeDifference:timeDifference];
    }
}

void ChatEventHandler::onSDKError(int errorCode, const std::string &packetId)
{
    @autoreleasepool {
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        //NSLog(@"[RawHandler] error code: %d packetId: %@", errorCode, packetIdString);
    }
}

void ChatEventHandler::onFriendHistoryMessageReceived(UserIdentity userId, UserIdentity friendId, const std::vector<imsdk::SDKMessageDTO> &friendHistoryMessageList, int direction)
{
    @autoreleasepool {
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendId];
        //NSLog(@"[RawHandler] New friend chat received from %lld", (long long) friendId);
        
        NSMutableArray *messageDTOArray = [NSMutableArray array];
        
        for (int i=0; i<friendHistoryMessageList.size(); i++)
        {
            imsdk::SDKMessageDTO messageDTO = friendHistoryMessageList[i];
            
            IMMessageModel *messageModel = [[IMMessageModel alloc] init];
            messageModel.senderId = [NSString stringWithFormat:@"%lld",messageDTO.getSenderId()];
            messageModel.receiverId = [NSString stringWithFormat:@"%lld",messageDTO.getReceiverId()];
            messageModel.packetId = [NSString stringWithUTF8String:messageDTO.getPacketId().c_str()];
            messageModel.messageType = static_cast<IMSDK_MessageType>(messageDTO.getMessageType());
            messageModel.timeout = messageDTO.getTimeOut();
            messageModel.message = [NSString stringWithUTF8String:messageDTO.getMessage().c_str()];
            messageModel.messageDate = messageDTO.getMessageDate();
            messageModel.memberFullName = [NSString stringWithUTF8String:messageDTO.getMemberFullName().c_str()];
            messageModel.memberProfilePicUrl = [NSString stringWithUTF8String:messageDTO.getMemberProfileUrl().c_str()];
            messageModel.isSecretVisible = messageDTO.getIsSecretVisible();
            messageModel.messageStatus = static_cast<IMSDK_MessageStatus>(messageDTO.getMessageStatus());
            messageModel.direction = messageDTO.getDirection();
            messageModel.isEdited = messageDTO.getIsEdited();
            messageModel.likeCount = messageDTO.getPublicChatLikeCount();
            messageModel.isLikedByMe = messageDTO.isPublicChatILike();
            messageModel.isReportedByMe = messageDTO.isPublicChatIReport();
            messageModel.unreadCount = messageDTO.getUnreadCount();
            
            [messageDTOArray addObject:messageModel];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedFriendHistoryMessageWithId:userIdSting withFriendId:friendIdSting withMessageList:messageDTOArray];
    }
}

void ChatEventHandler::onFriendMessagesStatusReceived(UserIdentity userId, UserIdentity friendId, const std::vector<imsdk::FriendMessageStatusDTO> &messageList)
{
    @autoreleasepool {
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendId];
        //NSLog(@"[RawHandler] onFriendMessagesStatusReceived");
        NSMutableArray *dtoArray = [NSMutableArray array];
        
        for (int i = 0; i < messageList.size(); i++)
        {
            imsdk::FriendMessageStatusDTO dto = messageList[i];
            
            IMMessageStatusModel *messageStatusModel = [[IMMessageStatusModel alloc] init];
            messageStatusModel.packetId = [NSString stringWithUTF8String:dto.getPacketId().c_str()];
            messageStatusModel.messageDate = dto.getUpdateDate();
            messageStatusModel.messageStatus = static_cast<IMSDK_MessageStatus>(dto.getMessageStatus());
            
            [dtoArray addObject:messageStatusModel];
//            [messageStatusModel release];
        }

        [[IMHandlerDelegate sharedInstance] receivedFriendMessageStatusWithId:userIdSting withFriendId:friendIdSting withMessageStatusList:dtoArray];
    }
}

void ChatEventHandler::onGroupHistoryMessageReceived(GroupIdentity groupId, const std::vector<imsdk::SDKMessageDTO> &groupHistoryMessageList, int direction)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onFriendMessagesStatusReceived");
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];

        NSMutableArray *messageDTOArray = [NSMutableArray array];
        
        for (int i=0; i<groupHistoryMessageList.size(); i++)
        {
            imsdk::SDKMessageDTO messageDTO = groupHistoryMessageList[i];
            
            IMMessageModel *messageModel = [[IMMessageModel alloc] init];
            messageModel.senderId = [NSString stringWithFormat:@"%lld",messageDTO.getSenderId()];
            messageModel.receiverId = [NSString stringWithFormat:@"%lld",messageDTO.getReceiverId()];
            messageModel.packetId = [NSString stringWithUTF8String:messageDTO.getPacketId().c_str()];
            messageModel.messageType = static_cast<IMSDK_MessageType>(messageDTO.getMessageType());
            messageModel.timeout = messageDTO.getTimeOut();
            messageModel.message = [NSString stringWithUTF8String:messageDTO.getMessage().c_str()];
            messageModel.messageDate = messageDTO.getMessageDate();
            messageModel.memberFullName = [NSString stringWithUTF8String:messageDTO.getMemberFullName().c_str()];
            messageModel.memberProfilePicUrl = [NSString stringWithUTF8String:messageDTO.getMemberProfileUrl().c_str()];
            messageModel.isSecretVisible = messageDTO.getIsSecretVisible();
            messageModel.messageStatus = static_cast<IMSDK_MessageStatus>(messageDTO.getMessageStatus());
            messageModel.direction = messageDTO.getDirection();
            messageModel.isEdited = messageDTO.getIsEdited();
            messageModel.likeCount = messageDTO.getPublicChatLikeCount();
            messageModel.isLikedByMe = messageDTO.isPublicChatILike();
            messageModel.isReportedByMe = messageDTO.isPublicChatIReport();
            messageModel.unreadCount = messageDTO.getUnreadCount();
            
            [messageDTOArray addObject:messageModel];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedGroupHistoryMessageWithId:groupIdSting withMessageList:messageDTOArray];
    }
}

void ChatEventHandler::onGroupInformationWithMembersReceived(GroupIdentity groupId, const std::string &groupName, const std::string &groupUrl, const std::vector<imsdk::MemberDTO> &memberList)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onFriendMessagesStatusReceived");
        
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *groupNameString = [NSString stringWithUTF8String:groupName.c_str()];
        NSString *groupUrlString = [NSString stringWithUTF8String:groupUrl.c_str()];
        
        NSMutableArray *dtoArray = [NSMutableArray array];

        for (int i = 0; i < memberList.size(); i++)
        {
            imsdk::MemberDTO dto = memberList[i];
            IMGroupMemberModel *memberModel = [[IMGroupMemberModel alloc] init];
            memberModel.friendId = [NSString stringWithFormat:@"%lld",dto.getMemberIdentity()];
            memberModel.ringId = [NSString stringWithFormat:@"%lld",dto.getRingId()];
            memberModel.friendName = [NSString stringWithUTF8String:dto.getFullName().c_str()];
            memberModel.memberStatus = static_cast<IMSDK_MemberStatus>(dto.getStatus());
            memberModel.memberAddedBy = [NSString stringWithFormat:@"%lld",dto.getAddedBy()];
        
            [dtoArray addObject:memberModel];
//            [memberModel release];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedGroupInformationWithmembersWithId:groupIdSting withGroupName:groupNameString withGroupUrl:groupUrlString withMemberList:dtoArray];
    }
}

void ChatEventHandler::onGroupInformationActivityReceived(const std::vector<imsdk::GroupActivityDTO> &groupActivityList)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupInformationActivityReceived");
        
        NSMutableArray *dtoArray = [NSMutableArray array];
        
        for (int i = 0; i < groupActivityList.size(); i++)
        {
            imsdk::GroupActivityDTO dto = groupActivityList[i];
            IMGroupActivityModel *groupActivityModel = [[IMGroupActivityModel alloc] init];
            groupActivityModel.groupId = [NSString stringWithFormat:@"%lld",dto.getGroupId()];
            groupActivityModel.activityType = static_cast<IMSDK_GroupChangeActivity>(dto.getActivityType());
            groupActivityModel.memberId = [NSString stringWithFormat:@"%lld",dto.getMemberIdentity()];
            groupActivityModel.ringId = [NSString stringWithFormat:@"%lld",dto.getRingId()];
            groupActivityModel.nameOrUrlString = [NSString stringWithUTF8String:dto.getGroupNameOrUrlString().c_str()];
            groupActivityModel.memberType = dto.getMemberType();
            groupActivityModel.changedByUserId = [NSString stringWithFormat:@"%lld",dto.getChangedByUserId()];
            groupActivityModel.updateTime = dto.getUpdateTime();
            groupActivityModel.packetId = [NSString stringWithUTF8String:dto.getPacketId().c_str()];
            
            [dtoArray addObject:groupActivityModel];
//            [groupActivityModel release];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedGroupActivityWithActivityList:dtoArray];
    }
}

void ChatEventHandler::onMyGroupListReceived(const std::vector<imsdk::GroupDTO> &myGroupList)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onFriendMessagesStatusReceived");
        NSMutableArray *dtoArray = [NSMutableArray array];
        
        for (int i = 0; i < myGroupList.size(); i++)
        {
            imsdk::GroupDTO dto = myGroupList[i];
            IMGroupModel *groupModel = [[IMGroupModel alloc] init];
            groupModel.groupId = [NSString stringWithFormat:@"%lld",dto.getGroupId()];
            groupModel.name = [NSString stringWithUTF8String:dto.getGroupName().c_str()];
            groupModel.profilePicUrl = [NSString stringWithUTF8String:dto.getGroupUrl().c_str()];
            groupModel.creatorid = [NSString stringWithFormat:@"%lld",dto.getCreatorId()];
            groupModel.numberOfMembers = dto.getNumberOfMembers();
            
            [dtoArray addObject:groupModel];
//            [groupModel release];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedMyGroupListWithList:dtoArray];
    }
}


void ChatEventHandler::onMyGroupListPagingReceived(const std::vector<imsdk::GroupDTO> &myGroupList, const std::string &pivotId, int direction)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onFriendMessagesStatusReceived");
        NSString *pivotIdString = [NSString stringWithUTF8String:pivotId.c_str()];
        NSMutableArray *dtoArray = [NSMutableArray array];
        
        for (int i = 0; i < myGroupList.size(); i++)
        {
            imsdk::GroupDTO dto = myGroupList[i];
            IMGroupModel *groupModel = [[IMGroupModel alloc] init];
            groupModel.groupId = [NSString stringWithFormat:@"%lld",dto.getGroupId()];
            groupModel.name = [NSString stringWithUTF8String:dto.getGroupName().c_str()];
            groupModel.profilePicUrl = [NSString stringWithUTF8String:dto.getGroupUrl().c_str()];
            groupModel.creatorid = [NSString stringWithFormat:@"%lld",dto.getCreatorId()];
            groupModel.numberOfMembers = dto.getNumberOfMembers();
            
            [dtoArray addObject:groupModel];
            //            [groupModel release];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedMyGroupListPagingWithList:dtoArray withPivotid:pivotIdString withDirection:direction];
    }
}





void ChatEventHandler::onMyGroupListReceiveCompleted()
{
    @autoreleasepool {
        [[IMHandlerDelegate sharedInstance] receivedMyGroupListCompleted];
    }
}

void ChatEventHandler::onGroupCreated(GroupIdentity groupId, const std::string &packetId, bool status)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onFriendMessagesStatusReceived");
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedGroupCreateRequestStatusWithId:groupIdSting withPacketId:packetIdString withStatus:status];
    }
}

void ChatEventHandler::onGroupNameChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::string &groupName)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupNameChangeRequestStatus");

        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedGroupInformationChangeRequestStatusWithId:groupIdSting withPacketId:packetIdString withStatus:status];
    }
}

void ChatEventHandler::onGroupUrlChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::string &groupUrl)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupUrlChangeRequestStatus");

        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedGroupInformationChangeRequestStatusWithId:groupIdSting withPacketId:packetIdString withStatus:status];
    }
}

void ChatEventHandler::onGroupNameChanged(const std::string &packetId, UserIdentity friendid, GroupIdentity groupId, const std::string &groupName)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onFriendMessagesStatusReceived");
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendid];
        NSString *groupNameIdString = [NSString stringWithUTF8String:groupName.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedGroupNameUpdateWithId:groupIdSting WithFriendId:friendIdSting withGroupName:groupNameIdString withPacketId:packetIdString];
    }
}

void ChatEventHandler::onGroupUrlChanged(const std::string &packetId, UserIdentity friendid, GroupIdentity groupId, const std::string &groupUrl)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onFriendMessagesStatusReceived");
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendid];
        NSString *groupUrlIdString = [NSString stringWithUTF8String:groupUrl.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedGroupProfilePicUpdateWithId:groupIdSting WithFriendId:friendIdSting withUrl:groupUrlIdString withPacketId:packetIdString];
    }
}

void ChatEventHandler::onGroupInformationActivityFromHistoryMessageReceived(GroupIdentity groupId, const std::vector<imsdk::GroupActivityDTO> &groupActivityList, int direction)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupInformationActivityFromHistoryMessageReceived");
        NSString *groupIdString = [NSString stringWithFormat:@"%lld",groupId];

        NSMutableArray *dtoArray = [NSMutableArray array];
        
        for (int i = 0; i < groupActivityList.size(); i++)
        {
            imsdk::GroupActivityDTO dto = groupActivityList[i];
            IMGroupActivityModel *groupActivityModel = [[IMGroupActivityModel alloc] init];
            groupActivityModel.groupId = [NSString stringWithFormat:@"%lld",dto.getGroupId()];
            groupActivityModel.activityType = static_cast<IMSDK_GroupChangeActivity>(dto.getActivityType());
            groupActivityModel.memberId = [NSString stringWithFormat:@"%lld",dto.getMemberIdentity()];
            groupActivityModel.ringId = [NSString stringWithFormat:@"%lld",dto.getRingId()];
            groupActivityModel.nameOrUrlString = [NSString stringWithUTF8String:dto.getGroupNameOrUrlString().c_str()];
            groupActivityModel.memberType = dto.getMemberType();
            groupActivityModel.changedByUserId = [NSString stringWithFormat:@"%lld",dto.getChangedByUserId()];
            groupActivityModel.updateTime = dto.getUpdateTime();
            groupActivityModel.packetId = [NSString stringWithUTF8String:dto.getPacketId().c_str()];
            
            [dtoArray addObject:groupActivityModel];
//            [groupActivityModel release];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedGroupInformationActivityFromHistoryMessageWithGroupId:groupIdString WithActivityList:dtoArray withDirection:static_cast<IMSDK_Scroll>(direction)];
    }
}

void ChatEventHandler::onFriendChatConversationListReceived(UserIdentity userId, const std::vector<imsdk::SDKMessageDTO> &conversationList, bool isFromSynced)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onFriendChatConversationListReceived");
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSMutableArray *messageDTOArray = [NSMutableArray array];
        
        for (int i=0; i<conversationList.size(); i++)
        {
            imsdk::SDKMessageDTO messageDTO = conversationList[i];
            
            IMMessageModel *messageModel = [[IMMessageModel alloc] init];
            messageModel.senderId = (messageDTO.getSenderId()==0) ? nil : [NSString stringWithFormat:@"%lld",messageDTO.getSenderId()];
            messageModel.receiverId = (messageDTO.getReceiverId()==0) ? nil : [NSString stringWithFormat:@"%lld",messageDTO.getReceiverId()];
            messageModel.groupId = (messageDTO.getGroupId()==0) ? nil : [NSString stringWithFormat:@"%lld",messageDTO.getGroupId()];
            messageModel.packetId = [NSString stringWithUTF8String:messageDTO.getPacketId().c_str()];
            messageModel.messageType = static_cast<IMSDK_MessageType>(messageDTO.getMessageType());
            messageModel.timeout = messageDTO.getTimeOut();
            messageModel.message = [NSString stringWithUTF8String:messageDTO.getMessage().c_str()];
            messageModel.messageDate = messageDTO.getMessageDate();
            messageModel.memberFullName = [NSString stringWithUTF8String:messageDTO.getMemberFullName().c_str()];
            messageModel.memberProfilePicUrl = [NSString stringWithUTF8String:messageDTO.getMemberProfileUrl().c_str()];
            messageModel.isSecretVisible = messageDTO.getIsSecretVisible();
            messageModel.messageStatus = static_cast<IMSDK_MessageStatus>(messageDTO.getMessageStatus());
            messageModel.direction = messageDTO.getDirection();
            messageModel.isEdited = messageDTO.getIsEdited();
            messageModel.likeCount = messageDTO.getPublicChatLikeCount();
            messageModel.isLikedByMe = messageDTO.isPublicChatILike();
            messageModel.isReportedByMe = messageDTO.isPublicChatIReport();
            messageModel.unreadCount = messageDTO.getUnreadCount();
            
            [messageDTOArray addObject:messageModel];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedFriendConversationListWithId:userIdSting withList:messageDTOArray withIsFromSynced:isFromSynced];

    }
}

void ChatEventHandler::onGroupChatConversationListReceived(const std::vector<imsdk::SDKMessageDTO> &conversationList, bool isFromSynced)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupChatConversationListReceived");
        
        NSMutableArray *messageDTOArray = [NSMutableArray array];
        
        for (int i=0; i<conversationList.size(); i++)
        {
            imsdk::SDKMessageDTO messageDTO = conversationList[i];
            
            IMMessageModel *messageModel = [[IMMessageModel alloc] init];
            messageModel.senderId = (messageDTO.getSenderId()==0) ? nil : [NSString stringWithFormat:@"%lld",messageDTO.getSenderId()];
            messageModel.receiverId = (messageDTO.getReceiverId()==0) ? nil : [NSString stringWithFormat:@"%lld",messageDTO.getReceiverId()];
            messageModel.groupId = (messageDTO.getGroupId()==0) ? nil : [NSString stringWithFormat:@"%lld",messageDTO.getGroupId()];
            messageModel.packetId = [NSString stringWithUTF8String:messageDTO.getPacketId().c_str()];
            messageModel.messageType = static_cast<IMSDK_MessageType>(messageDTO.getMessageType());
            messageModel.timeout = messageDTO.getTimeOut();
            messageModel.message = [NSString stringWithUTF8String:messageDTO.getMessage().c_str()];
            messageModel.messageDate = messageDTO.getMessageDate();
            messageModel.memberFullName = [NSString stringWithUTF8String:messageDTO.getMemberFullName().c_str()];
            messageModel.memberProfilePicUrl = [NSString stringWithUTF8String:messageDTO.getMemberProfileUrl().c_str()];
            messageModel.isSecretVisible = messageDTO.getIsSecretVisible();
            messageModel.messageStatus = static_cast<IMSDK_MessageStatus>(messageDTO.getMessageStatus());
            messageModel.direction = messageDTO.getDirection();
            messageModel.isEdited = messageDTO.getIsEdited();
            messageModel.likeCount = messageDTO.getPublicChatLikeCount();
            messageModel.isLikedByMe = messageDTO.isPublicChatILike();
            messageModel.isReportedByMe = messageDTO.isPublicChatIReport();
            messageModel.unreadCount = messageDTO.getUnreadCount();
            
            [messageDTOArray addObject:messageModel];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedGroupConversationListWithList:messageDTOArray withIsFromSynced:isFromSynced];
    }
}

void ChatEventHandler::onChatConversationListRequestStatus(UserIdentity userId, long long friendOrGroupId, const std::string &packetId, bool status)
{
    
}

void ChatEventHandler::onChatConversationListCompleted(UserIdentity userId, bool isFromSynced)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onChatConversationListCompleted");
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        
        [[IMHandlerDelegate sharedInstance] receivedConversationListCompletedWithId:userIdSting withIsFromSynced:isFromSynced];
    }
}

void ChatEventHandler::onConversationListDeleteRequestStatus(UserIdentity userId, const std::string &packetId, bool status)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onConversationListDeleteRequestStatus");
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedConversationListDeleteRequestStatusWithId:userIdSting withPacketId:packetIdString withStatus:status];
    }
}

void ChatEventHandler::onConversationListMarkAsSeenRequestStatus(UserIdentity userId, const std::string &packetId, bool status)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onConversationListMarkAsSeenRequestStatus");
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedConversationListMarkRequestStatusWithId:userIdSting withPacketId:packetIdString withStatus:status];
    }
}

void ChatEventHandler::onPublicRoomChatRegisterSuccess(RoomIdentity &roomId, const std::string &packetId, int numberOfMembers, long long anonymousId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicRoomChatRegisterSuccess");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *anonymousIdString = [NSString stringWithFormat:@"%lld",(long long)anonymousId];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatRegisterSuccessWithRoomId:roomIdString withPacketId:packetIdString withNumberOfMember:numberOfMembers withAnonymousId:anonymousIdString];
    }
}

void ChatEventHandler::onPublicRoomChatRegisterFailure(RoomIdentity &roomId, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicRoomChatRegisterFailure");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatRegisterFailureWithRoomId:roomIdString withPacketId:packetIdString];
    }
}

void ChatEventHandler::onPublicRoomChatRegistrationExpired(RoomIdentity &roomId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicRoomChatRegistrationExpired");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatRegistrationExpiredWithRoomId:roomIdString];
    }
}

void ChatEventHandler::onPublicRoomChatDelivered(RoomIdentity &roomId, const std::string &packetId, bool isEdited)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicRoomChatDelivered");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatDeliveredWithRoomId:roomIdString withPacketId:packetIdString withIsEdited:isEdited];
    }
}

void ChatEventHandler::onPublicRoomChatFailedToSend(RoomIdentity &roomId, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicRoomChatFailedToSend");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatFailedToSendWithRoomId:roomIdString withPacketId:packetIdString];
    }
}

void ChatEventHandler::onPublicRoomChatReceived(RoomIdentity &roomId, UserIdentity friendId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, const std::string &memberFullName, const std::string &memberProfileUrl)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicRoomChatReceived");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *messageString = [NSString stringWithUTF8String:message.c_str()];
        NSString *memberFullNameString = [NSString stringWithUTF8String:memberFullName.c_str()];
        NSString *memberProfileUrlString = [NSString stringWithUTF8String:memberProfileUrl.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatMessageWithRoomId:roomIdString withFriendId:friendIdSting withPacketId:packetIdString withMessageType:static_cast<IMSDK_MessageType>(messageType) withMessage:messageString withMessageDate:messageDate withMemberFullName:memberFullNameString withMemberUrl:memberProfileUrlString];
    }
}

void ChatEventHandler::onPublicRoomListReceived(const std::vector<imsdk::RoomDTO> &roomList, bool roomListFromHistory)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicRoomListReceived");
        
        NSMutableArray *roomListArray = [NSMutableArray array];
        
        for (int i = 0; i < roomList.size(); i++)
        {
            imsdk::RoomDTO room = roomList[i];
            IMRoomModel *roomModel = [[IMRoomModel alloc] init];
            roomModel.roomId = [NSString stringWithUTF8String:room.getRoomId().c_str()];
            roomModel.roomName = [NSString stringWithUTF8String:room.getRoomFullName().c_str()];
            roomModel.roomPictureUrl = [NSString stringWithUTF8String:room.getRoomPictureUrl().c_str()];
            roomModel.numberOfMember = room.getNumberOfMember();
            
            NSMutableArray *messageDTOArray = [NSMutableArray array];
            auto messageList = roomList[i].getRoomMessageList();
            
            for (int i=0; i<messageList.size(); i++)
            {
                imsdk::SDKMessageDTO messageDTO = messageList[i];
                
                IMMessageModel *messageModel = [[IMMessageModel alloc] init];
                messageModel.senderId = [NSString stringWithFormat:@"%lld",messageDTO.getSenderId()];
                messageModel.receiverId = [NSString stringWithFormat:@"%lld",messageDTO.getReceiverId()];
                messageModel.packetId = [NSString stringWithUTF8String:messageDTO.getPacketId().c_str()];
                messageModel.messageType = static_cast<IMSDK_MessageType>(messageDTO.getMessageType());
                messageModel.timeout = messageDTO.getTimeOut();
                messageModel.message = [NSString stringWithUTF8String:messageDTO.getMessage().c_str()];
                messageModel.messageDate = messageDTO.getMessageDate();
                messageModel.memberFullName = [NSString stringWithUTF8String:messageDTO.getMemberFullName().c_str()];
                messageModel.memberProfilePicUrl = [NSString stringWithUTF8String:messageDTO.getMemberProfileUrl().c_str()];
                messageModel.isSecretVisible = messageDTO.getIsSecretVisible();
                messageModel.messageStatus = static_cast<IMSDK_MessageStatus>(messageDTO.getMessageStatus());
                messageModel.direction = messageDTO.getDirection();
                messageModel.isEdited = messageDTO.getIsEdited();
                messageModel.likeCount = messageDTO.getPublicChatLikeCount();
                messageModel.isLikedByMe = messageDTO.isPublicChatILike();
                messageModel.isReportedByMe = messageDTO.isPublicChatIReport();
                
                [messageDTOArray addObject:messageModel];
            }

            roomModel.popularMessageList = messageDTOArray;
            
            [roomListArray addObject:roomModel];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomListWithRoomList:roomListArray withIsWithHistory:roomListFromHistory];
    }
}

void ChatEventHandler::onPublicRoomInformationReceived(RoomIdentity &roomId, std::string &roomName, std::string &roomUrl, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicRoomInformationReceived");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *roomNameString = [NSString stringWithUTF8String:roomName.c_str()];
        NSString *roomUrlString = [NSString stringWithUTF8String:roomUrl.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomInformationWithRoomId:roomIdString withRoomName:roomNameString withRoomUrl:roomUrlString withPacketId:packetIdString];
    }
}

void ChatEventHandler::onPublicRoomChatEdited(RoomIdentity &roomId, UserIdentity friendId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, const std::string &memberFullName, const std::string &memberProfileUrl)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicRoomChatEdited");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *friendIdString = [NSString stringWithFormat:@"%lld",friendId];
        NSString *messageString = [NSString stringWithUTF8String:message.c_str()];
        NSString *memberFullNameString = [NSString stringWithUTF8String:memberFullName.c_str()];
        NSString *MemberProfileUrlString = [NSString stringWithUTF8String:memberProfileUrl.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatEditedMessageWithRoomId:roomIdString withFriendId:friendIdString withPacketId:packetIdString withMessageType:static_cast<IMSDK_MessageType>(messageType) withMessage:messageString withMessageDate:messageDate withMemberFullName:memberFullNameString withMemberUrl:MemberProfileUrlString];
    }
}

void ChatEventHandler::onPublicRoomChatTyping(RoomIdentity &roomId, UserIdentity friendId, const std::string &memberName)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicRoomChatTyping");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *friendIdString = [NSString stringWithFormat:@"%lld",friendId];
        NSString *memberNameString = [NSString stringWithUTF8String:memberName.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatTypingWithRoomId:roomIdString withFriendId:friendIdString withMemberName:memberNameString];
    }
}

void ChatEventHandler::onPublicChatMemberListReceived(RoomIdentity &roomId, const std::string &pagingState, const std::vector<imsdk::PublicChatMemberDTO> &publicChatMemberList)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicChatMemberListReceived");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *pagingStateString = [NSString stringWithUTF8String:pagingState.c_str()];
        
        NSMutableArray *memberDTOArray = [NSMutableArray array];
        
        for (int i = 0; i < publicChatMemberList.size(); i++)
        {
            imsdk::PublicChatMemberDTO member = publicChatMemberList[i];
            IMPublicChatMemberModel *memberModel = [[IMPublicChatMemberModel alloc] init];
            memberModel.memberId = [NSString stringWithFormat:@"%lld",member.getMemberId()];
            memberModel.fakeId = [NSString stringWithFormat:@"%lld",member.getFakeId()];
            memberModel.ringId = [NSString stringWithFormat:@"%lld",member.getRingId()];
            memberModel.fullName = [NSString stringWithUTF8String:member.getFullName().c_str()];
            memberModel.profileUrl = [NSString stringWithUTF8String:member.getProfileUrl().c_str()];
            memberModel.addedTime = member.getAddedTime();
            
            [memberDTOArray addObject:memberModel];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedPublicChatMemberListWithRoomId:roomIdString withPagingState:pagingStateString withMemberList:memberDTOArray];
    }
}

void ChatEventHandler::onPublicChatMemberCountChanged(RoomIdentity &roomId, int numberOfMembers)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicChatMemberCountChanged");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicChatMemberCountChangeWithRoomId:roomIdString withNumberOfMember:numberOfMembers];
    }
}

void ChatEventHandler::shouldCheckServerAddressForRoom(RoomIdentity &roomId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] shouldCheckServerAddressForRoom");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] shouldCheckServerAddressForRoomWithRoomId:roomIdString];
    }
}

void ChatEventHandler::onPublicRoomChatHistoryReceived(RoomIdentity &roomId, const std::vector<imsdk::SDKMessageDTO> &publicChatMessageList)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicRoomChatHistoryReceived");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];

        NSMutableArray *messageDTOArray = [NSMutableArray array];

        for (int i=0; i<publicChatMessageList.size(); i++)
        {
            imsdk::SDKMessageDTO messageDTO = publicChatMessageList[i];
            
            IMMessageModel *messageModel = [[IMMessageModel alloc] init];
            messageModel.senderId = [NSString stringWithFormat:@"%lld",messageDTO.getSenderId()];
            messageModel.receiverId = [NSString stringWithFormat:@"%lld",messageDTO.getReceiverId()];
            messageModel.packetId = [NSString stringWithUTF8String:messageDTO.getPacketId().c_str()];
            messageModel.messageType = static_cast<IMSDK_MessageType>(messageDTO.getMessageType());
            messageModel.timeout = messageDTO.getTimeOut();
            messageModel.message = [NSString stringWithUTF8String:messageDTO.getMessage().c_str()];
            messageModel.messageDate = messageDTO.getMessageDate();
            messageModel.memberFullName = [NSString stringWithUTF8String:messageDTO.getMemberFullName().c_str()];
            messageModel.memberProfilePicUrl = [NSString stringWithUTF8String:messageDTO.getMemberProfileUrl().c_str()];
            messageModel.isSecretVisible = messageDTO.getIsSecretVisible();
            messageModel.messageStatus = static_cast<IMSDK_MessageStatus>(messageDTO.getMessageStatus());
            messageModel.direction = messageDTO.getDirection();
            messageModel.isEdited = messageDTO.getIsEdited();
            messageModel.likeCount = messageDTO.getPublicChatLikeCount();
            messageModel.isLikedByMe = messageDTO.isPublicChatILike();
            messageModel.isReportedByMe = messageDTO.isPublicChatIReport();
            
            [messageDTOArray addObject:messageModel];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatHistoryWithRoomId:roomIdString withMessageList:messageDTOArray];
    }
}

void ChatEventHandler::onPublicRoomChatHistoryCompleted(RoomIdentity &roomId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicRoomChatHistoryReceived");

        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatHistoryCompletedWithRoomId:roomIdString];
    }
}

void ChatEventHandler::onGroupHistoryCompleted(GroupIdentity groupId, int direction)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupHistoryCompleted");
        NSString *groupIdString = [NSString stringWithFormat:@"%lld",groupId];
        
        [[IMHandlerDelegate sharedInstance] receivedGroupHistoryCompletedWithGroupId:groupIdString withDirection:static_cast<IMSDK_Scroll>(direction)];
    }
}

void ChatEventHandler::onGroupInformationWithMembersRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupInformationWithMembersRequestStatus");
        NSString *groupIdString = [NSString stringWithFormat:@"%lld",groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedGroupInformationWithMembersRequestStatusWithGroupId:groupIdString withPacketId:packetIdString withStatus:status];
    }
}

void ChatEventHandler::onFriendHistoryCompleted(UserIdentity userId, UserIdentity friendId, int direction)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onFriendHistoryCompleted");
        NSString *userIdString = [NSString stringWithFormat:@"%lld",userId];
        NSString *friendIdString = [NSString stringWithFormat:@"%lld",friendId];
        
        [[IMHandlerDelegate sharedInstance] receivedFriendHistoryCompletedWithId:userIdString withFriendId:friendIdString withDirection:static_cast<IMSDK_Scroll>(direction)];
    }
}

void ChatEventHandler::onFriendHistoryMessageRequestStatus(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool status)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onFriendHistoryMessageRequestStatus");
        NSString *userIdString = [NSString stringWithFormat:@"%lld",userId];
        NSString *friendIdString = [NSString stringWithFormat:@"%lld",friendId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedFriendHistoryMessageRequestStatusWithId:userIdString withFriendId:friendIdString withPacketId:packetIdString withStatus:status];
    }
}

void ChatEventHandler::onGroupHistoryMessageRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupHistoryMessageRequestStatus");
        NSString *groupIdString = [NSString stringWithFormat:@"%lld",groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedGroupHistoryMessageRequestStatusWithGroupId:groupIdString withPacketId:packetIdString withStatus:status];
    }
}

void ChatEventHandler::onPublicRoomListRequestStatus(const std::string &packetId, bool requestStatus)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicRoomListRequestStatus");
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomListRequestStatusWithPacketId:packetIdString withStatus:requestStatus];
    }
}

void ChatEventHandler::onPublicRoomInformationRequestFailed(RoomIdentity &roomId, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicRoomInformationRequestFailed");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomInformationRequestFailedWithRoomId:roomIdString withPacketId:packetIdString];
    }
}

void ChatEventHandler::onPublicRoomChatHistoryRequestStatus(RoomIdentity &roomId, const std::string &packetId, bool requestStatus)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicRoomChatHistoryRequestStatus");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatHistoryRequestStatusWithRoomId:roomIdString withPacketId:packetIdString withStatus:requestStatus];
    }
}

void ChatEventHandler::onPublicRoomMemberListRequestStatus(RoomIdentity &roomId, const std::string &packetId, bool requestStatus)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicRoomMemberListRequestStatus");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomMemberListRequestStatusWithRoomId:roomIdString withPacketId:packetIdString withStatus:requestStatus];
    }
}

void ChatEventHandler::onPublicChatMessageDeleted(RoomIdentity& roomId, const std::vector<std::string>& deletedPacketIds)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicChatMessageDeleted");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        
        NSMutableArray *packetIdArray = [NSMutableArray array];
        
        for (int i = 0; i < deletedPacketIds.size(); i++)
        {
            NSString *packetIdString = [NSString stringWithUTF8String:deletedPacketIds[i].c_str()];
            
            [packetIdArray addObject:packetIdString];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatMessageDeletedWithId:roomIdString withPacketIdList:packetIdArray];
    }
}

void ChatEventHandler::onPublicChatMessageLiked(RoomIdentity& roomId, const std::string& packetId, UserIdentity likerId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicChatMessageLiked");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *likerIdString = [NSString stringWithFormat:@"%lld",likerId];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatMessageLikedWithId:roomIdString withPacketId:packetIdString withLikerId:likerIdString];
    }
}

void ChatEventHandler::onPublicChatMessageUnliked(RoomIdentity &roomId, const std::string &packetId, UserIdentity unlikerId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicChatMessageUnliked");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *unlikerIdString = [NSString stringWithFormat:@"%lld",unlikerId];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatMessageUnlikedWithId:roomIdString withPacketId:packetIdString withUnlikerId:unlikerIdString];
    }
}

void ChatEventHandler::onPublicChatMessageReported(RoomIdentity& roomId, const std::string& packetId, UserIdentity reporterId)
{

}

void ChatEventHandler::onPublicChatCategoryListReceived(std::vector<std::string> &publicChatCategoryList)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicChatCategoryListReceived");
        NSMutableArray *categoryArray = [NSMutableArray array];
        
        for (int i = 0; i < publicChatCategoryList.size(); i++)
        {
            NSString *packetIdString = [NSString stringWithUTF8String:publicChatCategoryList[i].c_str()];
            
            [categoryArray addObject:packetIdString];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatCategoryListWithList:categoryArray];
    }
}

void ChatEventHandler::onPublicChatLikeMemberListReceived(RoomIdentity &roomId, const std::string &packetId, const std::vector<imsdk::PublicChatMemberDTO> &publicChatMemberList)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicChatLikeMemberListReceived");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        NSMutableArray *memberDTOArray = [NSMutableArray array];
        
        for (int i = 0; i < publicChatMemberList.size(); i++)
        {
            imsdk::PublicChatMemberDTO member = publicChatMemberList[i];
            IMPublicChatMemberModel *memberModel = [[IMPublicChatMemberModel alloc] init];
            memberModel.memberId = [NSString stringWithFormat:@"%lld",member.getMemberId()];
            memberModel.fakeId = [NSString stringWithFormat:@"%lld",member.getFakeId()];
            memberModel.ringId = [NSString stringWithFormat:@"%lld",member.getRingId()];
            memberModel.fullName = [NSString stringWithUTF8String:member.getFullName().c_str()];
            memberModel.profileUrl = [NSString stringWithUTF8String:member.getProfileUrl().c_str()];
            memberModel.addedTime = member.getAddedTime();
            
            [memberDTOArray addObject:memberModel];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatMessageLikeListWithId:roomIdString withPacketId:packetIdString withMemberList:memberDTOArray];
    }
}

void ChatEventHandler::onPublicChatDeleteRequestStatus(RoomIdentity roomId, const std::string &packetId, bool status)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicChatDeleteRequestStatus");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatDeleteRequestStatusWithId:roomIdString withPacketId:packetIdString withStatus:status];
    }
}

void ChatEventHandler::onPublicChatLikeUnlikeRequestStatus(RoomIdentity roomId, const std::string &requestPacketId, const std::string &messagePacketId, bool status, bool fromLikeRequest)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicChatLikeUnlikeRequestStatus");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:requestPacketId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatLikeUnlikeRequestStatusWithId:roomIdString withPacketId:packetIdString withStatus:status];
    }
}

void ChatEventHandler::onPublicChatReportRequestStatus(RoomIdentity roomId, const std::string &requestPacketId, const std::string &messagePacketId, bool status)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicChatReportRequestStatus");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:requestPacketId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatReportRequestStatusWithId:roomIdString withPacketId:packetIdString withStatus:status];
    }
}

void ChatEventHandler::onPublicChatLikeMemberListRequestStatus(RoomIdentity roomId, const std::string &packetId, bool status)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicChatLikeMemberListRequestStatus");
        NSString *roomIdString = [NSString stringWithUTF8String:roomId.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatLikeListRequestStatusWithId:roomIdString withPacketId:packetIdString withStatus:status];
    }
}

void ChatEventHandler::onPublicChatCategoryListRequestStatus(const std::string &packetId, bool status)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onPublicChatCategoryListRequestStatus");
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedPublicRoomChatCategoryListRequestStatusWithPacketId:packetIdString withStatus:status];
    }
}

void ChatEventHandler::onNetworkDataCounted(const imsdk::DataCounter& dataCounter)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onNetworkDataCounted");
        IMNetworkDataModel *networkDataModel = [[IMNetworkDataModel alloc] init];
        networkDataModel.dataSent = dataCounter.getDataSent();
        networkDataModel.dataReceived = dataCounter.getDataReceived();
        
        [[IMHandlerDelegate sharedInstance] receivedNetworkDataCountWithData:networkDataModel];
    }
}

void ChatEventHandler::onFriendFileManifestUploaded(UserIdentity userId, UserIdentity friendId, const std::string &packetId, std::string cloudManifestUrl, int messageType, int timeout, std::string caption, int widthOrFileSize, int heightOrDuration)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onFileManifestUploaded %lld", (long long) friendId);
        NSString *userIdString = [NSString stringWithFormat:@"%lld",userId];
        NSString *friendIdString = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *cloudManifestUrlString = [NSString stringWithUTF8String:cloudManifestUrl.c_str()];
        NSString *captionString = [NSString stringWithUTF8String:caption.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedFriendFileManifestUploadedWithId:userIdString withFriendId:friendIdString withPacketId:packetIdString withManifestUrl:cloudManifestUrlString withMessageType:static_cast<IMSDK_MessageType>(messageType) withTimeout:timeout withCaption:captionString withWidthOrSize:widthOrFileSize withHeightOrDuration:heightOrDuration];
    }

}

void ChatEventHandler::onFriendIncomingChatMedia(UserIdentity userId, UserIdentity friendId, std::string fileName, const std::string &packetId, int messageType, int timeout, long long messageDate, bool isSecretVisible, std::string caption, int widthOrFileSize, int heightOrDuration)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onIncomingChatMedia %lld", (long long) friendId);
        NSString *userIdString = [NSString stringWithFormat:@"%lld",userId];
        NSString *friendIdString = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *fileNameString = [NSString stringWithUTF8String:fileName.c_str()];
        NSString *captionString = [NSString stringWithUTF8String:caption.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedFriendIncomingChatMediaWithId:userIdString withFriendId:friendIdString withPacketId:packetIdString withFileName:fileNameString withMessgeType:static_cast<IMSDK_MessageType>(messageType) withTimeout:timeout withMessageDate:messageDate withIsSecretVisible:isSecretVisible withCaption:captionString withWidthOrSize:widthOrFileSize withHeightOrDuration:heightOrDuration];
    }
    
}

void ChatEventHandler::onFriendChatMediaTransferProgress(UserIdentity userId, UserIdentity friendId, std::string fileName, double transferPercentage, bool isUpload, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onChatMediaTransferProgress %lld", (long long) friendId);
        NSString *userIdString = [NSString stringWithFormat:@"%lld",userId];
        NSString *friendIdString = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *fileNameString = [NSString stringWithUTF8String:fileName.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedFriendChatMediaTransferProgressWithId:userIdString withFriendId:friendIdString withPacketId:packetIdString withFileName:fileNameString withTransferPercentage:transferPercentage withTransferType:isUpload];
    }

}

void ChatEventHandler::onFriendChatMediaTransferFailed(UserIdentity userId, UserIdentity friendId, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onChatMediaTransferFailed %lld", (long long) friendId);
        NSString *userIdString = [NSString stringWithFormat:@"%lld",userId];
        NSString *friendIdString = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *fileNameString = [NSString stringWithUTF8String:fileName.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedFriendChatMediaTransferFailedWithId:userIdString withFriendId:friendIdString withPacketId:packetIdString withFileName:fileNameString withIsUpload:isUpload withIsChunkedTransfer:isChunkedTransfer];
    }
}

void ChatEventHandler::onFriendChatMediaTransferCanceled(UserIdentity userId, UserIdentity friendId, UserIdentity canceledBy, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onFriendChatMediaTransferCanceled %lld", (long long) friendId);
        NSString *userIdString = [NSString stringWithFormat:@"%lld",userId];
        NSString *friendIdString = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *canceledByString = [NSString stringWithFormat:@"%lld",(long long)canceledBy];
        NSString *fileNameString = [NSString stringWithUTF8String:fileName.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedFriendChatMediaTransferCanceledWithId:userIdString withFriendId:friendIdString withCanceledBy:canceledByString withPacketId:packetIdString withFileName:fileNameString withIsUpload:isUpload withIsChunkedTransfer:isChunkedTransfer];
    }
}

void ChatEventHandler::onFriendChatMediaDownloadCompleted(UserIdentity userId, UserIdentity friendId, std::string fileNameWithPath, const std::string &packetId, int messageType, int timeout)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onChatMediaDownloadCompleted %lld", (long long) friendId);
        NSString *userIdString = [NSString stringWithFormat:@"%lld",userId];
        NSString *friendIdString = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *filePathString = [NSString stringWithUTF8String:fileNameWithPath.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedFriendChatMediaDownloadCompletedWithId:userIdString withFriendId:friendIdString withPacketId:packetIdString withFilePath:filePathString withMessageType:static_cast<IMSDK_MessageType>(messageType) withTimeout:timeout];
    }
}

void ChatEventHandler::onGroupFileManifestUploaded(GroupIdentity groupId, const std::string &packetId, std::string cloudManifestUrl, int messageType, std::string caption, int widthOrFileSize, int heightOrDuration)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupFileManifestUploaded %lld", (long long) groupId);
        NSString *groupIdString = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *cloudManifestUrlString = [NSString stringWithUTF8String:cloudManifestUrl.c_str()];
        NSString *captionString = [NSString stringWithUTF8String:caption.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedGroupFileManifestUploadedWithId:groupIdString withPacketId:packetIdString withManifestUrl:cloudManifestUrlString withMessageType:static_cast<IMSDK_MessageType>(messageType) withCaption:captionString withWidthOrSize:widthOrFileSize withHeightOrDuration:heightOrDuration];
    }
}

void ChatEventHandler::onGroupIncomingChatMedia(UserIdentity friendId, GroupIdentity groupId, std::string fileName, const std::string &packetId, int messageType, long long messageDate, std::string caption, int widthOrFileSize, int heightOrDuration)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onIncomingGroupChatMedia %lld", (long long) groupId);
        NSString *friendIdString = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *groupIdString = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *fileNameString = [NSString stringWithUTF8String:fileName.c_str()];
        NSString *captionString = [NSString stringWithUTF8String:caption.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedGroupIncomingChatMediaWithFriendId:friendIdString withGroupId:groupIdString withPacketId:packetIdString withFileName:fileNameString withMessgeType:static_cast<IMSDK_MessageType>(messageType) withMessageDate:messageDate withCaption:captionString withWidthOrSize:widthOrFileSize withHeightOrDuration:heightOrDuration];
    }
}

void ChatEventHandler::onGroupChatMediaTransferProgress(UserIdentity friendId, GroupIdentity groupId, std::string fileName, double transferPercentage, bool isUpload, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onChatMediaTransferProgress %lld", (long long) groupId);
        NSString *friendIdString = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *groupIdString = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *fileNameString = [NSString stringWithUTF8String:fileName.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedGroupChatMediaTransferProgressWithFriendId:friendIdString withGroupId:groupIdString withPacketId:packetIdString withFileName:fileNameString withTransferPercentage:transferPercentage withTransferType:isUpload];
    }
}

void ChatEventHandler::onGroupChatMediaTransferFailed(UserIdentity friendId, GroupIdentity groupId, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupChatMediaTransferFailed %lld", (long long) groupId);
        NSString *friendIdString = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *groupIdString = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *fileNameString = [NSString stringWithUTF8String:fileName.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedGroupChatMediaTransferFailedWithId:friendIdString withGroupId:groupIdString withPacketId:packetIdString withFileName:fileNameString withIsUpload:isUpload withIsChunkedTransfer:isChunkedTransfer];
    }
}

void ChatEventHandler::onGroupChatMediaTransferCanceled(UserIdentity friendId, GroupIdentity groupId, UserIdentity canceledBy, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupChatMediaTransferCanceled %lld", (long long) groupId);
        NSString *friendIdString = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *groupIdString = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *canceledByString = [NSString stringWithFormat:@"%lld",(long long)canceledBy];
        NSString *fileNameString = [NSString stringWithUTF8String:fileName.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedGroupChatMediaTransferCanceledWithId:friendIdString withGroupId:groupIdString withCanceledBy:canceledByString withPacketId:packetIdString withFileName:fileNameString withIsUpload:isUpload withIsChunkedTransfer:isChunkedTransfer];
    }
}

void ChatEventHandler::onGroupChatMediaDownloadCompleted(UserIdentity friendId, GroupIdentity groupId, std::string fileNameWithPath, const std::string &packetId, int messageType)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onGroupChatMediaDownloadCompleted %lld", (long long) groupId);
        NSString *friendIdString = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *groupIdString = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *filePathString = [NSString stringWithUTF8String:fileNameWithPath.c_str()];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedGroupChatMediaDownloadCompletedWithId:friendIdString withGroupId:groupIdString withPacketId:packetIdString withFilePath:filePathString withMessageType:static_cast<IMSDK_MessageType>(messageType)];
    }
}
void ChatEventHandler::onChatMediaTransferDirectoryError(std::string directoryPath)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onChatMediaTransferDirectoryError");
        NSString *directoryPathString = [NSString stringWithUTF8String:directoryPath.c_str()];
        [[IMHandlerDelegate sharedInstance] receivedChatMediaTransferDirectoryErrorWithPath:directoryPathString];
    }
}

void ChatEventHandler::shouldUpdateAppSessionID()
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] shouldUpdateAppSessionID");

        [[IMHandlerDelegate sharedInstance] shouldUpdateAppSessionID];
    }
}

void ChatEventHandler::onShadowIdsInfoRequestFailed(const std::string &packetId){}
void ChatEventHandler::onShadowIdsInfoResponseReceived(const std::vector<imsdk::PublicChatMemberDTO> &shadowIdsInfo){}

void ChatEventHandler::onFileStreamRequestReceived(UserIdentity userId, UserIdentity friendId, FileIdentity fileId){}
void ChatEventHandler::onFriendFileSessionRequestSuccess(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId, int fileTransferPort){}
void ChatEventHandler::onFriendFileTransferSessionRequestFailed(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId){}
void ChatEventHandler::onFriendFileStreamRequestSuccess(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId){}
void ChatEventHandler::onFriendFileTransferStreamRequestFailed(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId){}

//Group file transfer
void ChatEventHandler::onGroupFileStreamRequestReceived(UserIdentity friendId, GroupIdentity groupId, FileIdentity fileId){}
void ChatEventHandler::onGroupFileSessionRequestSuccess(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId, int fileTransferPort){}
void ChatEventHandler::onGroupFileTransferSessionRequestFailed(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId){}
void ChatEventHandler::onGroupFileStreamRequestSuccess(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId){}
void ChatEventHandler::onGroupFileTransferStreamRequestFailed(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId){}

void ChatEventHandler::onFriendGetChatMessageReceived(UserIdentity userId, UserIdentity friendId, const imsdk::SDKMessageDTO& friendChatMessageDTO){}
void ChatEventHandler::onGroupGetChatMessageReceived(GroupIdentity groupId, const imsdk::SDKMessageDTO& groupChatMessageDTO){}
void ChatEventHandler::onFriendGetChatMessageFailedToSend(UserIdentity userId, UserIdentity friendId, const std::string& packetId){}
void ChatEventHandler::onGroupGetChatMessageFailedToSend(GroupIdentity groupId, const std::string& packetId){}

//Live stream chat
void ChatEventHandler::onLiveStreamChatRegisterSuccess(UserIdentity publisherId, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] Live stream chat register success with publisherId %lld", (long long) publisherId);
        NSString *publisherIdString = [NSString stringWithFormat:@"%lld",(long long)publisherId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedLiveStreamChatRegisterSuccessWithPublisherId:publisherIdString withPacketId:packetIdString];
    }
}

void ChatEventHandler::onLiveStreamChatRegisterFailure(UserIdentity publisherId, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] Live stream chat register failure with publisherId %lld", (long long) publisherId);
        NSString *publisherIdString = [NSString stringWithFormat:@"%lld",(long long)publisherId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedLiveStreamChatRegisterFailureWithPublisherId:publisherIdString withPacketId:packetIdString];
    }
}

void ChatEventHandler::onLiveStreamChatRegistrationExpired(UserIdentity publisherId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] Live stream chat reg expired with publisherId %lld", (long long) publisherId);
        NSString *publisherIdString = [NSString stringWithFormat:@"%lld",(long long)publisherId];
        
        [[IMHandlerDelegate sharedInstance] receivedLiveStreamChatRegistrationExpiredWithPublisherId:publisherIdString];
    }
}

void ChatEventHandler::onLiveStreamChatDelivered(UserIdentity publisherId, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] Live stream chat delivered with publisherId %lld", (long long) publisherId);
        NSString *publisherIdString = [NSString stringWithFormat:@"%lld",(long long)publisherId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedLiveStreamChatDeliveredWithPublisherId:publisherIdString withPacketId:packetIdString];
    }
}

void ChatEventHandler::onLiveStreamChatFailedToSend(UserIdentity publisherId, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] Live stream chat register success with publisherId %lld", (long long) publisherId);
        NSString *publisherIdString = [NSString stringWithFormat:@"%lld",(long long)publisherId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedLiveStreamChatFailedToSendWithPublisherId:publisherIdString withPacketId:packetIdString];
    }
}

void ChatEventHandler::onLiveStreamChatReceived(UserIdentity publisherId, UserIdentity senderId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, const std::string &senderFullName)
{
    @autoreleasepool {
        NSString *publisherIdString = [NSString stringWithFormat:@"%lld",(long long)publisherId];
        NSString *senderIdString = [NSString stringWithFormat:@"%lld",(long long)senderId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *messageString = [NSString stringWithUTF8String:message.c_str()];
        NSString *senderFullNameString = [NSString stringWithUTF8String:senderFullName.c_str()];
        //NSLog(@"[RawHandler] Live stream chat received with publisherId %lld, senderid %lld message:%@", (long long) publisherId, (long long) senderId, messageString);
    
        [[IMHandlerDelegate sharedInstance] receivedLiveStreamChatWithPublisherId:publisherIdString withSenderId:senderIdString withPacketId:packetIdString withMessageType:static_cast<IMSDK_MessageType>(messageType) withMessage:messageString withMessageDate:messageDate withSenderFullName:senderFullNameString];
    }
}

void ChatEventHandler::onLiveStreamChatTyping(UserIdentity publisherId, UserIdentity senderId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] Live stream chat typing with publisherId %lld", (long long) publisherId);
        NSString *publisherIdString = [NSString stringWithFormat:@"%lld",(long long)publisherId];
        NSString *senderIdString = [NSString stringWithFormat:@"%lld",(long long)senderId];
        
        [[IMHandlerDelegate sharedInstance] receivedLiveStreamChatTypingWithPublisherId:publisherIdString withSenderId:senderIdString];
    }
}

void ChatEventHandler::shouldCheckServerAddressForLiveStreamChat(UserIdentity publisherId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] shouldCheckOfflineServerAddress for live stream chat with publisherId %lld", (long long) publisherId);
        NSString *publisherIdString = [NSString stringWithFormat:@"%lld",(long long)publisherId];
        
        [[IMHandlerDelegate sharedInstance] shouldCheckServerAddressForLiveStreamChatWithPublisherId:publisherIdString];
    }
}

void ChatEventHandler::onLiveStreamChatBlockUserRequestStatus(UserIdentity blockedUserId, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onLiveStreamChatBlockUserRequestStatus with blocked user id %lld", (long long) blockedUserId);
        NSString *blockedUserIdString = [NSString stringWithFormat:@"%lld",(long long)blockedUserId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedLiveStreamChatBlockUserRequestStatusWithBlockedUserId:blockedUserIdString withPacketId:packetIdString];
    }
}

void ChatEventHandler::onLiveStreamChatUserBlocked(UserIdentity publisherId, UserIdentity blockedUserId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onLiveStreamChatUserBlocked with blocked user id %lld", (long long) blockedUserId);
        NSString *publisherIdString = [NSString stringWithFormat:@"%lld",(long long)publisherId];
        NSString *blockedUserIdString = [NSString stringWithFormat:@"%lld",(long long)blockedUserId];

        [[IMHandlerDelegate sharedInstance] receivedLiveStreamChatUserBlockedWithPublisherId:publisherIdString withBlockedUserId:blockedUserIdString];
    }
}


void ChatEventHandler::onActivaeOrDeactivateUserAccountStatus(UserIdentity userId, const std::string &packetId, bool isAccountActivate, bool status)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] on Activae Or Deactivate User AccountStatus with friend %lld", (long long) friendId);

        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedActivaeOrDeactivateUserAccountStatusWithId:userIdSting withPacketId:packetIdString withIsAccountActivate:isAccountActivate withStatus:status];
    }
}


void ChatEventHandler::onGetUserInfoReceived(UserIdentity userId, UserIdentity friendId, const std::string &packetId, std::string friendName, UserIdentity friendRingId, std::string friendProfileImageUrl, int friendProfileType)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] on Get UserInfo Received with friend %lld", (long long) friendId);

        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        NSString *friendNameString = [NSString stringWithUTF8String:friendName.c_str()];
        NSString *friendRingIdString = [NSString stringWithFormat:@"%lld",(long long)friendRingId];
        NSString *friendProfileImageUrlString = [NSString stringWithUTF8String:friendProfileImageUrl.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedGetUserInfoReceivedWithId:userIdSting withFriendID:friendIdSting withPacketId:packetIdString withFriendName:friendNameString withFriendRingId:friendRingIdString withFriendProfileImageUrl:friendProfileImageUrlString withFriendProfileType:friendProfileType];
    }
}

void ChatEventHandler::onGetUserInfoFailure(UserIdentity userId, UserIdentity friendId, const std::string &packetId)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] on Get UserInfo Failure with friend %lld", (long long) friendId);

        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIDSting = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];

        [[IMHandlerDelegate sharedInstance] receivedGetUserInfoFailureWithId:userIdSting withFriendID:friendIDSting withPacketId:packetIdString];
    }
}

void ChatEventHandler::onSyncConversationRequestStatus(UserIdentity userId, const std::string &packetId, long long syncTime, bool status)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] on Sync Conversation Request Status with userId %lld", (long long) syncTime);
        
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedSyncConversationStatusWithId:userIdSting withPacketId:packetIdString withSyncTime:syncTime withStatus:status];
    }
}

void ChatEventHandler::onSyncFriendHistoryMessageRequestStatus(UserIdentity userId, UserIdentity friendId, const std::string &packetId, long long syncTime, int direction, bool status)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] on Sync Friend History Message Request Status with userId %lld", (long long) syncTime);
        
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIDSting = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedSyncFriendHistoryStatusWithId:userIdSting withFriendID:friendIDSting withPacketId:packetIdString withSyncTime:syncTime withDirection:direction withStatus:status];
    }
}

void ChatEventHandler::onSyncFriendHistoryMessageReceived(UserIdentity userId, UserIdentity friendId, const std::string &packetId, const std::vector<imsdk::SDKMessageDTO> &friendHistoryMessageList, long long oldestMessageDate, int direction)
{
    @autoreleasepool {
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIdSting = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        NSMutableArray *messageDTOArray = [NSMutableArray array];
        
        for (int i=0; i<friendHistoryMessageList.size(); i++)
        {
            imsdk::SDKMessageDTO messageDTO = friendHistoryMessageList[i];
            
            IMMessageModel *messageModel = [[IMMessageModel alloc] init];
            messageModel.senderId = [NSString stringWithFormat:@"%lld",messageDTO.getSenderId()];
            messageModel.receiverId = [NSString stringWithFormat:@"%lld",messageDTO.getReceiverId()];
            messageModel.packetId = [NSString stringWithUTF8String:messageDTO.getPacketId().c_str()];
            messageModel.messageType = static_cast<IMSDK_MessageType>(messageDTO.getMessageType());
            messageModel.timeout = messageDTO.getTimeOut();
            messageModel.message = [NSString stringWithUTF8String:messageDTO.getMessage().c_str()];
            messageModel.messageDate = messageDTO.getMessageDate();
            messageModel.memberFullName = [NSString stringWithUTF8String:messageDTO.getMemberFullName().c_str()];
            messageModel.memberProfilePicUrl = [NSString stringWithUTF8String:messageDTO.getMemberProfileUrl().c_str()];
            messageModel.isSecretVisible = messageDTO.getIsSecretVisible();
            messageModel.messageStatus = static_cast<IMSDK_MessageStatus>(messageDTO.getMessageStatus());
            messageModel.direction = messageDTO.getDirection();
            messageModel.isEdited = messageDTO.getIsEdited();
            messageModel.likeCount = messageDTO.getPublicChatLikeCount();
            messageModel.isLikedByMe = messageDTO.isPublicChatILike();
            messageModel.isReportedByMe = messageDTO.isPublicChatIReport();
            messageModel.unreadCount = messageDTO.getUnreadCount();
            
            [messageDTOArray addObject:messageModel];
        }
        
        [[IMHandlerDelegate sharedInstance] receivedSyncFriendHistoryMessageWithId:userIdSting withFriendId:friendIdSting withPacketId:packetIdString withMessageList:messageDTOArray withOldestMessageDate:oldestMessageDate withDirection:direction];
    }
}


void ChatEventHandler::onSyncFriendHistoryMessageReceiveCompleted(UserIdentity userId, UserIdentity friendId, const std::string &packetId, int direction)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] on Sync Friend History Message Request Status with userId %lld", (long long) syncTime);
        
        NSString *userIdSting = [NSString stringWithFormat:@"%lld",(long long)userId];
        NSString *friendIDSting = [NSString stringWithFormat:@"%lld",(long long)friendId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedSyncFriendHistoryMessageCompletedWithId:userIdSting withFriendID:friendIDSting withPacketId:packetIdString withDirection:direction];
    }
}


void ChatEventHandler::onSyncGroupHistoryMessageRequestStatus(GroupIdentity groupId, const std::string &packetId, long long syncTime, int direction, bool status)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] on Sync Group History MessageRequest Status with userId %lld", (long long) syncTime);
        
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedSyncGroupHistoryStatusWithId:groupIdSting withPacketId:packetIdString withSyncTime:syncTime withDirection:direction withStatus:status];
    }
}


void ChatEventHandler::onSyncGroupHistoryMessageReceived(GroupIdentity groupId, const std::string &packetId, const std::vector<imsdk::SDKMessageDTO> &groupHistoryMessageList, const std::vector<imsdk::GroupActivityDTO> &groupActivityList, long long oldestMessageDate, int direction)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] onFriendMessagesStatusReceived");
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        NSMutableArray *messageDTOArray = [NSMutableArray array];
        
        for (int i=0; i<groupHistoryMessageList.size(); i++)
        {
            imsdk::SDKMessageDTO messageDTO = groupHistoryMessageList[i];
            
            IMMessageModel *messageModel = [[IMMessageModel alloc] init];
            messageModel.senderId = [NSString stringWithFormat:@"%lld",messageDTO.getSenderId()];
            messageModel.receiverId = [NSString stringWithFormat:@"%lld",messageDTO.getReceiverId()];
            messageModel.packetId = [NSString stringWithUTF8String:messageDTO.getPacketId().c_str()];
            messageModel.messageType = static_cast<IMSDK_MessageType>(messageDTO.getMessageType());
            messageModel.timeout = messageDTO.getTimeOut();
            messageModel.message = [NSString stringWithUTF8String:messageDTO.getMessage().c_str()];
            messageModel.messageDate = messageDTO.getMessageDate();
            messageModel.memberFullName = [NSString stringWithUTF8String:messageDTO.getMemberFullName().c_str()];
            messageModel.memberProfilePicUrl = [NSString stringWithUTF8String:messageDTO.getMemberProfileUrl().c_str()];
            messageModel.isSecretVisible = messageDTO.getIsSecretVisible();
            messageModel.messageStatus = static_cast<IMSDK_MessageStatus>(messageDTO.getMessageStatus());
            messageModel.direction = messageDTO.getDirection();
            messageModel.isEdited = messageDTO.getIsEdited();
            messageModel.likeCount = messageDTO.getPublicChatLikeCount();
            messageModel.isLikedByMe = messageDTO.isPublicChatILike();
            messageModel.isReportedByMe = messageDTO.isPublicChatIReport();
            messageModel.unreadCount = messageDTO.getUnreadCount();
            
            [messageDTOArray addObject:messageModel];
        }
        
        
        NSMutableArray *activityDTOArray = [NSMutableArray array];
        
        for (int i = 0; i < groupActivityList.size(); i++)
        {
            imsdk::GroupActivityDTO dto = groupActivityList[i];
            IMGroupActivityModel *groupActivityModel = [[IMGroupActivityModel alloc] init];
            groupActivityModel.groupId = [NSString stringWithFormat:@"%lld",dto.getGroupId()];
            groupActivityModel.activityType = static_cast<IMSDK_GroupChangeActivity>(dto.getActivityType());
            groupActivityModel.memberId = [NSString stringWithFormat:@"%lld",dto.getMemberIdentity()];
            groupActivityModel.ringId = [NSString stringWithFormat:@"%lld",dto.getRingId()];
            groupActivityModel.nameOrUrlString = [NSString stringWithUTF8String:dto.getGroupNameOrUrlString().c_str()];
            groupActivityModel.memberType = dto.getMemberType();
            groupActivityModel.changedByUserId = [NSString stringWithFormat:@"%lld",dto.getChangedByUserId()];
            groupActivityModel.updateTime = dto.getUpdateTime();
            groupActivityModel.packetId = [NSString stringWithUTF8String:dto.getPacketId().c_str()];
            
            [activityDTOArray addObject:groupActivityModel];
        }
        
        
        [[IMHandlerDelegate sharedInstance] receivedSyncGroupHistoryMessageWithId:groupIdSting withPacketId:packetIdString withMessageList:messageDTOArray withActivityList:activityDTOArray withOldestMessageDate:oldestMessageDate withDirection:direction];
    }
}

void ChatEventHandler::onSyncGroupHistoryMessageReceiveCompleted(GroupIdentity groupId, const std::string &packetId, int direction)
{
    @autoreleasepool {
        //NSLog(@"[RawHandler] on Sync Group History MessageRequest Status with userId %lld", (long long) syncTime);
        
        NSString *groupIdSting = [NSString stringWithFormat:@"%lld",(long long)groupId];
        NSString *packetIdString = [NSString stringWithUTF8String:packetId.c_str()];
        
        [[IMHandlerDelegate sharedInstance] receivedyncGroupHistoryMessageCompletedWithId:groupIdSting withPacketId:packetIdString withDirection:direction];
    }
}

void ChatEventHandler::onAddNoticeRequestStatus(const std::string &packetId, bool status){}