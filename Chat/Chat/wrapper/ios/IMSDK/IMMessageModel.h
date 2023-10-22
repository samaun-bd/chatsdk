//
//  IMSDKMessageModel.h
//  IMSDK
//
//  Created by Dipranjan Das on 6/8/16.
//  Copyright © 2016 Sumon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IMSDKTypes.h"

@interface IMMessageModel : NSObject

@property (nonatomic, strong) NSString *senderId;
@property (nonatomic, strong) NSString *receiverId;
@property (nonatomic, strong) NSString *groupId;
@property (nonatomic, strong) NSString *packetId;
@property (nonatomic, readwrite) IMSDK_MessageType messageType;
@property (nonatomic, readwrite) int timeout;
@property (nonatomic, strong) NSString *message;
@property (nonatomic, readwrite) long long messageDate;
@property (nonatomic, strong) NSString *memberFullName;
@property (nonatomic, strong) NSString *memberProfilePicUrl;
@property (nonatomic, readwrite) BOOL isSecretVisible;
@property (nonatomic, readwrite) IMSDK_MessageStatus messageStatus;
@property (nonatomic, readwrite) int direction;
@property (nonatomic, readwrite) BOOL isEdited;
@property (nonatomic, readwrite) int likeCount;
@property (nonatomic, readwrite) BOOL isLikedByMe;
@property (nonatomic, readwrite) BOOL isReportedByMe;
@property (nonatomic, readwrite) int unreadCount;

@end