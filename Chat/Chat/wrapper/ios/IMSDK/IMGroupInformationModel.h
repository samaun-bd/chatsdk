//
//  IMGroupInformationModel.h
//  IMSDK
//
//  Created by Dipranjan Das on 6/12/16.
//  Copyright © 2016 Sumon. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "IMSDKTypes.h"

@interface IMGroupInformationModel : NSObject

@property (nonatomic, strong) NSString *groupId;
@property (nonatomic, strong) NSString *registerServerAddress;
@property (nonatomic, readwrite) int registerServerPort;
@property (nonatomic, readwrite) int bindingPort;
@property (nonatomic, readwrite) long long lastActivityTime;

@end