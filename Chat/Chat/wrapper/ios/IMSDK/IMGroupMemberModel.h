//
//  IMGroupMemberModel.h
//  ringID
//
//  Created by Sumon on 9/9/15.
//  Copyright (c) 2015 IPVision Canada Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "IMSDKTypes.h"
/**
 *  Class for MemberDTO
 */
@interface IMGroupMemberModel : NSObject

/**
 *  Member user identity
 */
@property (nonatomic, strong) NSString *friendId;

@property (nonatomic, strong) NSString *ringId;

/**
 *  Member Name
 */
@property (nonatomic, strong) NSString *friendName;

/**
 *  User identity who added this member
 */
@property (nonatomic, strong) NSString *memberAddedBy;

/**
 *  Permission status of this member to the corrensponding group
 */
@property (nonatomic, readwrite) IMSDK_MemberStatus memberStatus;

@property (nonatomic, readwrite) long long seenTime;


@end
