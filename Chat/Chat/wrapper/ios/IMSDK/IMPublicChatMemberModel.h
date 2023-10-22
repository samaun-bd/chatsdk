//
//  IMPublicChatMemberModel.h
//  IMSDK
//
//  Created by Dipranjan Das on 6/11/16.
//  Copyright © 2016 Sumon. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface IMPublicChatMemberModel : NSObject

@property (nonatomic, strong) NSString *memberId;
@property (nonatomic, strong) NSString *fakeId;
@property (nonatomic, strong) NSString *ringId;
@property (nonatomic, strong) NSString *fullName;
@property (nonatomic, strong) NSString *profileUrl;
@property (nonatomic, readwrite) long long addedTime;

@end
