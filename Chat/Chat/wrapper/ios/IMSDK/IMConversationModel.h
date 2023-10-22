
#import <Foundation/Foundation.h>

#import "IMSDKTypes.h"

@interface IMConversationModel : NSObject

@property (nonatomic, readwrite) IMSDK_ConversationType conversationType;
@property (nonatomic, strong) NSString *friendId;
@property (nonatomic, strong) NSString *groupId;

@end
