//
//  IMNetworkDataModel.h
//  IMSDK
//
//  Created by Dipranjan Das on 8/2/16.
//  Copyright © 2016 Sumon. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface IMNetworkDataModel : NSObject

@property (nonatomic, readwrite) long long dataSent;
@property (nonatomic, readwrite) long long dataReceived;

@end