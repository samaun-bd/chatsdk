/* 
 * File:   Types.h
 * Author: dipal
 *
 * Created on August 24, 2015, 11:01 AM
 */

#ifndef TYPES_H
#define	TYPES_H

#include <string>
#include "ParserTypes.h"


typedef long long UserIdentity;
typedef long long GroupIdentity;
typedef std::string  RoomIdentity;
typedef long long FileIdentity;
typedef long long IPVLongType;

#if defined(_WIN32) || defined(_WIN32)
#define PATH_SEPARATOR "\\" 
#else 
#define PATH_SEPARATOR '/' 
#endif

namespace imsdk {
enum ChatError {
    NO_ERROR_IN_SDK = 0,                   //No error
    PARSING_FAILED,           //Parser failed to parse. Possibly wrong packet format
    CONNECTION_NOT_FOUND,     //Connection not found
    FAILED_TO_SEND,           //Failed to send both chat and offline server
    SESSION_ALREADY_EXISTS,
    PACKET_BUILDER_ERROR,
    SOCK_ERROR,
    
};

enum OnlineStatus {
    OFFLINE = 1,
    ONLINE,
    AWAY,
};

enum OnlineMood {
    ALIVE = 1,
    DONT_DISTRUBE,
    BUSY,
    INVISIVLE,
};

enum UserProfileType {
	DEFAULT = 1,
	PAGE = 3
};

enum MessageType {
    DELETE_MESSAGE = 0,
    BLANK_MESSAGE,
    PLAIN_MESSAGE,
    EMOTICON_MESSAGE,
    LOCATION_MESSAGE,
    LINK_MESSAGE,
    DOWNLOAD_STICKER_MESSAGE,
    IMAGE_FILE_FROM_GALLERY,
    AUDIO_FILE,
    VIDEO_FILE,
    IMAGE_FILE_FROM_CAMERA,
    FILE_STREAM,
    CONTACT,
    FILE_STREAM_MENIFEST,
    PAGING_MESSAGE,
    RING_MEDIA_MESSAGE,
    CALL_LOG_MESSAGE,
    SCREENSHOT_TAKEN,
    FRIENDSHIP_MESSAGE,
    GIFT_MESSAGE,
    GROUP_ACTIVITY,
    GIF_FILE = 23,
    RING_OFFICIAL = 24,
	GENERIC_FILE_TRANSFER = 27,
	GROUP_CALL_BY_MEETING = 28
};

enum GroupChangeActivity {
    DELETED = 0,
    ADDED,
    LEAVE,
    GROUP_RENAME,
    MEMBER_TYPE_CHANGE,
    GROUP_URL_RENAME,
    GROUP_CREATED,
};

enum Direction {
    UP = 1,
    DOWN = 2,
};

enum MessageStatus {
    DELETED_STATUS = 0,
    SENT_STATUS,
    DELIVERED_STATUS,
    SEEN_STATUS,
    VIEWED_PLAYED_STATUS
};

enum MessageDeleteType {
    SELF_DEVICE = 1,
    BOTH_DEVICE = 2
};

enum GroupLeaveType {
    GROUP_LEAVE = 1,
    GROUP_LEAVE_WITH_HIDE = 2
};

}

#endif	/* TYPES_H */

