package com.ringid.imsdk;

/**
 * Contains all the packet types.
 * @author Anwar
 */
public class Constants {

    //Client Registration Constants
    public static final int CHAT_REGISTER = 1;
    public static final int CHAT_FRIEND_UNREGISTERED = 2;
    public static final int CHAT_REGISTER_CONFIRMATION = 3;
    public static final int CHAT_GROUP_UNREGISTER = 4;
    //Friend to Friend Chat Constants
    public static final int CHAT_FRIEND = 5;
    public static final int CHAT_DELIVERED = 6;
    public static final int CHAT_SEEN = 7;
    public static final int CHAT_SENT = 8;
    public static final int CHAT_TYPING = 9;
    public static final int CHAT_IDEL = 10;
    //Group Chat Constants
    public static final int CHAT_GROUP_REGISTER = 12;
    public static final int CHAT_GROUP_REG_CONFIRMATION = 13;
    public static final int CHAT_GROUP = 14;
    public static final int CHAT_GROUP_DELIVERED = 15;
    public static final int CHAT_GROUP_SEEN = 16;
    public static final int CHAT_GROUP_SENT = 17;
    public static final int CHAT_GROUP_TYPING = 18;
    public static final int CHAT_GROUP_IDEL = 19;
    //Offline Message
    public static final int CHAT_FRIEND_OFFLINE = 20;
    public static final int CHAT_GROUP_OFFLINE = 21;
    public static final int CHAT_GET_OFFLINE = 22;
    public static final int CHAT_OFFLINE_CONFIRMATION = 23;
    //Chat Delete Constants
    public static final int FRIEND_CHAT_DELETE = 24;
    public static final int FRIEND_CHAT_DELETE_CONFIRMATION = 25;
    public static final int GROUP_CHAT_DELETE = 26;
    public static final int GROUP_CHAT_DELETE_CONFIRMATION = 27;
    public static final int FRIEND_INFORMATION = 28;
    public static final int FRIEND_INFORMATION_CONFIRMATION = 29;
    //File Stream
    public static final int FILE_TOTAL_SEQUENCE = 30;
    public static final int FILE_TOTAL_SEQUENCE_CONFIRMATION = 31;
    public static final int FILE_STREAM_SEND = 32;
    public static final int FILE_STREAM_SEND_CONFIRMATION = 33;
    //End File Stream
    //Group Chat
    public static final int GROUP_MEMBERS = 34;
    public static final int GROUP_MEMBERS_CONFIRMATION = 35;
    public static final int GET_GROUP_MEMBERS = 36;
    public static final int GROUP_MEMBER_REMOVE_LEAVE = 37;
    public static final int GROUP_MEMBER_REMOVE_LEAVE_CONFIRMATION = 38;
    public static final int GROUP_DELETE = 39;
    public static final int GROUP_DELETE_CONFIRMATION = 40;
    public static final int MULTIPLE_FRIEND_CHAT_DELETE = 41;
    public static final int MULTIPLE_GROUP_CHAT_DELETE = 42;
    public static final int FRIEND_CHAT_EDIT = 43;
    public static final int GROUP_CHAT_EDIT = 44;
    public static final int MULTIPLE_CHAT_FOR_FRIEND = 45;
    public static final int BROCKEN_CHAT_FOR_FRIEND = 46;
    public static final int BROCKEN_CHAT_FOR_GROUP = 47;
    public static final int EDIT_BROCKEN_CHAT_FOR_FRIEND = 48;
    public static final int EDIT_BROCKEN_CHAT_FOR_GROUP = 49;
    //File Transfering using UDP
    public static final int CHAT_FRIEND_FILE_STREAM_REQUEST = 50;
    public static final int CHAT_FRIEND_FILE_STREAM_REQUEST_CONFIRMATION = 51;
    public static final int CHAT_FRIEND_FILE_STREAM_SEND = 52;
    public static final int CHAT_FRIEND_FILE_STREAM_SEND_CONFIRMATION = 53;
    public static final int CHAT_GROUP_FILE_STREAM_REQUEST = 54;
    public static final int CHAT_GROUP_FILE_STREAM_REQUEST_CONFIRMATION = 55;
    public static final int CHAT_GROUP_FILE_STREAM_SEND = 56;
    public static final int CHAT_GROUP_FILE_STREAM_SEND_CONFIRMATION = 57;
    
    public static final int CHAT_FRIEND_OFFLINE_CONFIRMATION = 58;
    public static final int CHAT_GROUP_OFFLINE_CONFIRMATION = 59;
    
    public static final int CHAT_FRIEND_BLOCK = 60;
    public static final int CHAT_FRIEND_UNBLOCK = 61;
    public static final int CHAT_BLOCK_UNBLOCK_CONFIRMATION = 62;
    
    public static final int GROUP_MEMBER_ADD = 63;
    public static final int GROUP_MEMBER_ADD_CONFIRMATION = 64;
    public static final int GROUP_INFORMATION = 65;
    public static final int GET_GROUP_INFORMATION = 66;
    public static final int GROUP_INFORMATION_CONFIRMATION = 67;
    public static final int GROUP_MEMBER_STATUS_CHANGE = 68;
    public static final int GROUP_MEMBER_STATUS_CHANGE_CONFIRMATION = 69;
    public static final int UPDATE_GROUP_INFORMATION = 70;
    
	
    //END File Transfering using UDP
    //User Online Status Constants
    public static final int OFFLINE = 1;
    public static final int ONLINE = 2;
    public static final int AWAY = 3;
    public static final int ALIVE = 1;
    
    public static final int DONT_DISTRUBE = 2;
    public static final int BUSY = 3;
    public static final int INVISIVLE = 4;
    
    //Device Platform Constants
    public static final int PLATFORM_DESKTOP = 1;
    public static final int PLATFORM_ANDEOID = 2;
    public static final int PLATFORM_IPHONE = 3;
    public static final int PLATFORM_WINDOWS = 4;
    public static final int PLATFORM_WEB = 5;
}