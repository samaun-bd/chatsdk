//
//  IMMessageStatusModel.h
//  IMSDK
//
//  Created by Dipranjan Das on 2/2/16.
//  Copyright © 2016 Sumon. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "IMSDKTypes.h"
/**
 *  Class for IMMessageStatusModel
 */
@interface IMMessageStatusModel : NSObject

/**
 *  Packet id of message
 */
@property (nonatomic, strong) NSString *packetId;

/**
 *  Message Date
 */
@property (nonatomic, readwrite) long long messageDate;

/**
 *  If the message is opened (image, video)
 */
@property (nonatomic, readwrite) IMSDK_MessageStatus messageStatus;

@end
