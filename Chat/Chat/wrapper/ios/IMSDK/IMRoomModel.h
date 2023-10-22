//
//  IMRoomModel.h
//  IMSDK
//
//  Created by Dipranjan Das on 6/11/16.
//  Copyright © 2016 Sumon. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Class for GroupDTO
 */
@interface IMRoomModel : NSObject

@property (nonatomic, strong) NSString *roomId;
@property (nonatomic, strong) NSString *roomName;
@property (nonatomic, strong) NSString *roomPictureUrl;
@property (nonatomic, readwrite) int numberOfMember;
@property (nonatomic, strong) NSArray *popularMessageList;

@end