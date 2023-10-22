//
//  IMApiStatus.m
//  ringID
//
//  Created by Sumon on 11/2/15.
//  Copyright © 2015 IPVision Canada Inc. All rights reserved.
//

#import "IMApiStatus.h"

#include "ApiStatus.h"

@implementation IMApiStatus

+ (instancetype)initWithPacketId:(NSString*)packetId withErrorType:(NSInteger)errorType;
{
    return [[[self class] alloc] initWithPacketId:packetId withErrorType:errorType];
}

- (instancetype)initWithPacketId:(NSString*)packetId withErrorType:(NSInteger)errorType;
{
    
    self.packetId = packetId;
    self.errorType = errorType;
    
    return self;
}

//- (void)dealloc
//{
//    self.packetId = nil;
//    [super dealloc];
//}
@end
