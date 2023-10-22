//
//  IOSLogger.m
//  IMSDK
//
//  Created by Dipranjan Das on 7/19/16.
//  Copyright © 2016 Sumon. All rights reserved.
//

#ifdef __APPLE__

#import "IOSLogger.h"
#include "Logger.h"

@implementation IOSLogger

+ (void) writeConsoleLogWithString:(NSString *)s
{
    NSLog(@"%@",s);
}

@end


void iosConsoleLog(std::string s)
{
    [IOSLogger writeConsoleLogWithString:[NSString stringWithUTF8String:s.c_str()]];
}

#endif