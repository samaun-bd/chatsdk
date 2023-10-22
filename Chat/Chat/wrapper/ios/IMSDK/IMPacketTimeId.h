//
//  IMPacketTimeId.h
//  IMSDK
//
//  Created by Dipranjan Das on 4/24/16.
//  Copyright © 2016 Sumon. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  IMPacketTimeId will be returned from generatePacketId. It will contain packetId and corresponding time
 */
@interface IMPacketTimeId : NSObject

/**
 *  Generated packet id
 */
@property (nonatomic, strong) NSString *packetId;

/**
 *  Timestamp from 1970
 */
@property (nonatomic, readwrite) long long packetTime1970;

/**
 *  Timestamp from 1582
 */
@property (nonatomic, readwrite) long long packetTime1582;

/**
 *  IMPacketTimeId Constructor.
 *
 *  @param packetId Corresponding packetId
 *  @param time1970 Timestamp from 1970
 *  @param time1582 Timestamp from 1582
 *
 *  @return IMPacketTimeId instance
 */
+ (instancetype)initWithPacketId:(NSString*)packetId withTime1970:(long long)time1970 withTime1582:(long long)time1582;

@end
