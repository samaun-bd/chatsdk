//
//  IMGroupActivityModel.hpp
//  IMSDK
//
//  Created by Dipranjan Das on 2/2/16.
//  Copyright © 2016 Sumon. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "IMSDKTypes.h"

/**
 *  Class for GroupActivityDTO
 */
@interface IMGroupActivityModel : NSObject

/**
 *  Group Id
 */
@property (nonatomic, strong) NSString *groupId;

/**
 *  Activity type
 */
@property (nonatomic, readwrite) IMSDK_GroupChangeActivity activityType;

/**
 *  MemberId
 */
@property (nonatomic, strong) NSString *memberId;

@property (nonatomic, strong) NSString *ringId;

/**
 *  Changed name or url depending on activityType
 */
@property (nonatomic, strong) NSString *nameOrUrlString;

/**
 *  Member type
 */
@property (nonatomic, readwrite) int memberType;

/**
 *  UserId who changed
 */
@property (nonatomic, strong) NSString *changedByUserId;

/**
 *  Update time
 */
@property (nonatomic, readwrite) long long updateTime;

/**
 *  Packet Id
 */
@property (nonatomic, strong) NSString *packetId;

@end
