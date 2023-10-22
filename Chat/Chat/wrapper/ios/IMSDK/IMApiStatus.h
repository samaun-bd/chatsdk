//
//  IMApiStatus.h
//  ringID
//
//  Created by Sumon on 11/2/15.
//  Copyright © 2015 IPVision Canada Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  RIChatApiSatus will be returned when an API is called. It will contain two variables. PacketId and error code.
 */
@interface IMApiStatus : NSObject

/**
 *  Corrensponding packetId
 */
@property (nonatomic, strong) NSString *packetId;

/**
 *  Error code of the call
 */
@property (nonatomic, readwrite) NSInteger errorType;

/**
 *  API Status Constructor.
 *
 *  @param packetId  Corresponding packetId
 *  @param errorType Error code of the call
 *
 *  @return IMApiStatus instance
 */
+ (instancetype)initWithPacketId:(NSString*)packetId withErrorType:(NSInteger)errorType;

@end
