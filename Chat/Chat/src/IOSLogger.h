//
//  IOSLogger.h
//  IMSDK
//
//  Created by Dipranjan Das on 7/19/16.
//  Copyright © 2016 Sumon. All rights reserved.
//

#ifdef __APPLE__

#import <Foundation/Foundation.h>

@interface IOSLogger : NSObject

+ (void) writeConsoleLogWithString:(NSString *)s;

@end

#endif