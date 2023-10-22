//
//  IMFriendInformationModel.h
//  IMSDK
//
//  Created by Dipranjan Das on 6/12/16.
//  Copyright © 2016 Sumon. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "IMSDKTypes.h"

@interface IMFriendInformationModel : NSObject

@property (nonatomic, strong) NSString *registerServerAddress;
@property (nonatomic, readwrite) int registerServerPort;
@property (nonatomic, readwrite) int bindingPort;
@property (nonatomic, readwrite) BOOL blockStatus;
@property (nonatomic, strong) NSString *friendName;
@property (nonatomic, strong) NSString *friendUrl;
@property (nonatomic, readwrite) IMSDK_Presence status;
@property (nonatomic, readwrite) IMSDK_MoodType mood;
@property (nonatomic, readwrite) IMSDK_DeviceType device;
@property (nonatomic, readwrite) int profileType;
@end