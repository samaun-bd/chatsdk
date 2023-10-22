/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ringid.imsdk;

/**
 *
 * @author noman
 */
public class ChatSDKTypes {
    
    public class DeviceType {
        public final static int DESKTOP = 1;
        public final static int ANDROID = 2;
        public final static int IPHONE = 3;
        public final static int WINDOWS = 4;
        public final static int WEB = 5;
    }
    
    public class OnlineStatus {
        public final static int OFFLINE = 1;
        public final static int ONLINE =2;
        public final static int AWAY = 3;
    }

    public class OnlineMood {
        public final static int ALIVE = 1;
        public final static int DONT_DISTRUBE = 2;
        public final static int BUSY = 3;
        public final static int INVISIVLE = 4;
    }

    public class MessageType {
        public final static int DELETE_MESSAGE = 0;
        public final static int BLANK_MESSAGE = 1;
        public final static int PLAIN_MESSAGE = 2;
        public final static int EMOTICON_MESSAGE = 3;
        public final static int LOCATION_MESSAGE = 4;
        public final static int LINK_MESSAGE = 5;
        public final static int DOWNLOAD_STICKER_MESSAGE = 6;
        public final static int IMAGE_FILE_FROM_GALLERY = 7;
        public final static int AUDIO_FILE = 8;
        public final static int VIDEO_FILE = 9;
        public final static int IMAGE_FILE_FROM_CAMERA = 10;
        public final static int FILE_STREAM = 11;
        public final static int CONTACT = 12;
        public final static int HISTORY_SECRET_PAGING = 14;
        public final static int RING_MEDIA_MESSAGE=15;
        public final static int CALL_LOG_MESSAGE=16;
        public final static int SCREENSHOT_TAKEN=17;
        public final static int FRIENDSHIP_MESSAGE=18;
		public final static int GIFT_MESSAGE=19;
        public final static int GROUP_ACTIVITY = 20;
        public final static int GIF_FILE = 23;
        public final static int RINGID_OFFICIAL = 24;
        public final static int TENOR_MESSAGE = 25;
        public final static int YOUTUBE_MESSAGE = 26;
		public final static int GENERIC_FILE_TRANSFER = 27;
		public final static int GROUP_CALL_BY_MEETING = 28;
		public static final int QUOTE_REPLY_MESSAGE = 30;
		public static final int NEW_KEY_GENERATED = 50;
		public static final int FORWARDED_MESSAGE = 31;
		
    }
    
    public class MessageStatus {
        public final static int DELETED = 0;
        public final static int SENT = 1;
        public final static int DELIVERED = 2;
        public final static int SEEN = 3;
        public final static int VIEWED_PLAYED = 4;
        public final static int FAILED = 100;
        public final static int EDITED = 101;
        public final static int CHAT_STATUS_NOTHING = 102;
        public final static int CHAT_STATUS_FAILED =103;
        public final static int CHAT_STATUS_NOT_ATTEMPTED = 104;
        public final static int CHAT_STATUS_SECRET_NOT_ATTEMPTED = 105;
        public final static int CHAT_STATUS_NOT_FOUND_IN_DB = 106;
    }
    
    public class Direction {
        public final static int UP = 1;
        public final static int DOWN = 2;
    }

    public class GroupChangeActivity {
        public final static int DELETED = 0;
        public final static int ADDED = 1;
        public final static int LEAVE = 2;
        public final static int GROUP_RENAME = 3;
        public final static int MEMBER_TYPE_CHANGE = 4;
        public final static int GROUP_URL_RENAME = 5;
        public final static int GROUP_CREATED = 6;
		public static final int LEAVE_HIDE = 7;
    }
    
    public class MemberStatus {
        public static final int STATUS_MEMBER = 1;
        public static final int STATUS_ADMIN = 2;
        public static final int STATUS_OWNER = 3;
        public static final int STATUS_REMOVED = 4;
        public static final int STATUS_LEAVE = 5;
    }
    
    public class ConversationType {
        public static final int ALL = 1;
        public static final int UNSEEN = 2;
        public static final int FRIEND_ID = 3;
        public static final int GROUP_ID = 4;
    };
    
    public class MessageDeleteType {
        public final static int SELF_DEVICE = 1;
        public final static int BOTH_DEVICE = 2;
    }
}
