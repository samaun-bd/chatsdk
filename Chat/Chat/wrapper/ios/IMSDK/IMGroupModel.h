//
//  IMGroupModel.h
//  IMSDK
//
//  Created by Dipranjan Das on 2/2/16.
//  Copyright © 2016 Sumon. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Class for GroupDTO
 */
@interface IMGroupModel : NSObject

/**
 *  GroupId
 */
@property (nonatomic, strong) NSString *groupId;

/**
 *  Group Name
 */
@property (nonatomic, strong) NSString *name;

/**
 *  Group Profile Picture URL
 */
@property (nonatomic, strong) NSString *profilePicUrl;

/**
 *  User identity who created this group
 */
@property (nonatomic, strong) NSString *creatorid;

/**
 *  Number of members of the group
 */
@property (nonatomic, readwrite) int numberOfMembers;

@end
