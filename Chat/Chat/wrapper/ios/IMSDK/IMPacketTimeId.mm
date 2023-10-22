//
//  IMPacketTimeId.m
//  IMSDK
//
//  Created by Dipranjan Das on 4/24/16.
//  Copyright © 2016 Sumon. All rights reserved.
//

#import "IMPacketTimeId.h"

#include "PacketTimeId.h"

@implementation IMPacketTimeId

+ (instancetype)initWithPacketId:(NSString *)packetId withTime1970:(long long)time1970 withTime1582:(long long)time1582
{
    return [[[self class] alloc] initWithPacketId:packetId withTime1970:time1970 withTime1582:time1582];
}

- (instancetype)initWithPacketId:(NSString *)packetId withTime1970:(long long)time1970 withTime1582:(long long)time1582
{
    
    self.packetId = packetId;
    self.packetTime1970 = time1970;
    self.packetTime1582 = time1582;
    
    return self;
}

//- (void)dealloc
//{
//    self.packetId = nil;
//    [super dealloc];
//}
@end