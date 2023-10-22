//
//  IMSDKTypes.h
//  IMSDK
//
//  Created by Dipranjan Das on 2/3/16.
//  Copyright © 2016 Sumon. All rights reserved.
//

#ifndef IMSDKTypes_h
#define IMSDKTypes_h



typedef NS_ENUM (NSUInteger, IMSDK_DeviceType) {
    IMSDK_DeviceType_Desktop = 1,
    IMSDK_DeviceType_Android = 2,
    IMSDK_DeviceType_iOS = 3,
    IMSDK_DeviceType_WindowsPhone = 4,
    IMSDK_DeviceType_Web = 5
};

typedef NS_ENUM (NSUInteger, IMSDK_MoodType) {
    IMSDK_MoodType_Alive = 1,
    IMSDK_MoodType_DontDisturb = 2,
    IMSDK_MoodType_Busy = 3,
    IMSDK_MoodType_Invisible = 4
};

typedef NS_ENUM (NSUInteger, IMSDK_Presence) {
    IMSDK_OnlineStatusType_Offline = 1,
    IMSDK_OnlineStatusType_Online = 2,
    IMSDK_OnlineStatusType_Away = 3
};

typedef NS_ENUM (NSUInteger, IMSDK_MessageType) {
    IMSDK_MessageType_DELETE_MESSAGE = 0,
    IMSDK_MessageType_BLANK_MESSAGE = 1,
    IMSDK_MessageType_PLAIN_MESSAGE = 2,
    IMSDK_MessageType_EMOTICON_MESSAGE = 3,
    IMSDK_MessageType_LOCATION_MESSAGE = 4,
    IMSDK_MessageType_LINK_MESSAGE = 5,
    IMSDK_MessageType_DOWNLOAD_STICKER_MESSAGE = 6,
    IMSDK_MessageType_IMAGE_FILE_FROM_GALLERY = 7,
    IMSDK_MessageType_AUDIO_FILE = 8,
    IMSDK_MessageType_VIDEO_FILE = 9,
    IMSDK_MessageType_IMAGE_FILE_FROM_CAMERA = 10,
    IMSDK_MessageType_FILE_STREAM = 11,
    IMSDK_MessageType_CONTACT = 12,
    IMSDK_MessageType_FILE_STREAM_MANIFEST = 13,
    IMSDK_MessageType_PAGING_MESSAGE = 14,
    IMSDK_MessageType_RING_MEDIA_MESSAGE = 15,
    IMSDK_MessageType_CALL_LOG_MESSAGE = 16,
    IMSDK_MessageType_SCREENSHOT_TAKEN = 17,
    IMSDK_MessageType_FRIENDSHIP_MESSAGE = 18,
	IMSDK_MessageType_GIFT_MESSAGE = 19,
    IMSDK_MessageType_GROUP_ACTIVITY = 20,
    IMSDK_MessageType_GIF_FILE = 23,
    IMSDK_MessageType_RINGID_OFFICIAL = 24,
    IMSDK_MessageType_UNREAD_MESSAGE = 40,
    IMSDK_MessageType_LOAD_MORE = 41
};

typedef NS_ENUM (NSUInteger, IMSDK_GroupChangeActivity) {
    IMSDK_GroupChangeActivity_DELETED = 0,
    IMSDK_GroupChangeActivity_ADDED = 1,
    IMSDK_GroupChangeActivity_LEAVE = 2,
    IMSDK_GroupChangeActivity_GROUP_RENAME = 3,
    IMSDK_GroupChangeActivity_MEMBER_TYPE_CHANGE = 4,
    IMSDK_GroupChangeActivity_GROUP_URL_RENAME = 5,
    IMSDK_GroupChangeActivity_GROUP_CREATED = 6,
    IMSDK_GroupChangeActivity_LEAVE_HIDE = 7
};

typedef NS_ENUM (NSUInteger, IMSDK_MemberStatus) {
    IMSDK_MemberStatus_MEMBER = 1,
    IMSDK_MemberStatus_ADMIN = 2,
    IMSDK_MemberStatus_OWNER = 3,
    IMSDK_MemberStatus_REMOVED = 4,
    IMSDK_MemberStatus_LEAVE = 5
};

typedef NS_ENUM (NSUInteger, IMSDK_MessageStatus) {
    IMSDK_MessageStatus_DELETED = 0,
    IMSDK_MessageStatus_SENT = 1,
    IMSDK_MessageStatus_DELIVERED = 2,
    IMSDK_MessageStatus_SEEN = 3,
    IMSDK_MessageStatus_VIEWED_PLAYED = 4
};

typedef NS_ENUM (NSUInteger, IMSDK_Scroll) {
    IMSDK_Scroll_UP = 1,
    IMSDK_Scroll_DOWN = 2,
};

typedef NS_ENUM (NSUInteger, IMSDK_ConversationType) {
    IMSDK_ConversationType_All = 1,
    IMSDK_ConversationType_Unseen = 2,
    IMSDK_ConversationType_Friend = 3,
    IMSDK_ConversationType_Group = 4,
};

typedef NS_ENUM(NSUInteger, IMSDK_MessageDeleteType) {
    IMSDK_MessageDeleteType_SELF_DEVICE = 1,
    IMSDK_MessageDeleteType_BOTH_DEVICE = 2
};

#endif /* IMTypes_h */
