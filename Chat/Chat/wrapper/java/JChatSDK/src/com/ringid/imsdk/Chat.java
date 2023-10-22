 /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ringid.imsdk;

import java.util.ArrayList;

/**
 * The class that contains all APIs to communicate with IM Server. Create one global instance of this class and use for
 * all kinds of communication to IM Server. Each API call will return an {@link ApiStatus}
 * 
 * @author dipal
 */
public class Chat {

    private static long userId;
    private static String userName;
    private static String offlineServerAddress;
    private static int offlineServerPort;
    private static String authenticationServerAddress;
    private static int authenticationServerPort;
    private static int deviceType;
    private static String appSessionId;
    private static int appVersion;
    private static long timeDifference;
    private static ArrayList<String> directoryPaths;
    private static String baseUploadUrl;
    private static String baseDownloadUrl;
    private static boolean autoDownloadEnabled;
    private static String key;
    private static int appType;
    private static ArrayList<Long> pageIdList;
    
    public static Chat chat;
    
    public static void initChat(long userId, String userName, String offlineServerAddress, int offlineServerPort, String authenticationServerAddress, int authenticationServerPort, int deviceType, String appSessionId, int appVersion, long timeDifference, ArrayList<String> directoryPaths, String baseUploadUrl, String baseDownloadUrl, boolean autoDownloadEnabled, String key, int appType, ArrayList<Long> pageIdList)
    {
        Chat.userId = userId;
        Chat.userName = userName;
        Chat.offlineServerAddress = offlineServerAddress;
        Chat.offlineServerPort = offlineServerPort;
        Chat.authenticationServerAddress = authenticationServerAddress;
        Chat.authenticationServerPort = authenticationServerPort;
        Chat.deviceType = deviceType;
        Chat.appSessionId = appSessionId;
        Chat.appVersion = appVersion;
        Chat.timeDifference = timeDifference;
        Chat.directoryPaths = directoryPaths;
        Chat.baseUploadUrl = baseUploadUrl;
        Chat.baseDownloadUrl = baseDownloadUrl;
        Chat.autoDownloadEnabled = autoDownloadEnabled;
        Chat.key = key;
        Chat.appType = appType;
        Chat.pageIdList = pageIdList;
              
        if (chat != null) {
            chat.reinitialize(userId, userName, offlineServerAddress, offlineServerPort, authenticationServerAddress, authenticationServerPort, deviceType, appSessionId, appVersion, timeDifference, directoryPaths, autoDownloadEnabled, key, pageIdList);
        }
    }
    
    public static Chat getInstance()
    {
        if(chat == null)
        {
            chat = new Chat(userId, userName, offlineServerAddress, offlineServerPort, authenticationServerAddress, authenticationServerPort, deviceType, appSessionId, appVersion, timeDifference, directoryPaths, baseUploadUrl, baseDownloadUrl, autoDownloadEnabled, key, appType, pageIdList);
        }
        return chat;
    }
    
    /**
     * Construct Chat object using own userId.
     * @param userId Self user id
     * @param userName Self user name 
     * @param offlineServerAddress Offline server IP
     * @param offlineServerPort Offline server port
     * @param authenticationServerAddress authentication server IP
     * @param authenticationServerPort authentication server port
     * @param deviceType Self device type
     * @param appSessionId App Session ID
     * @param appVersion App Version
     * @param timeDifference Difference in time between server and client
     * @param ipListFilePath Directory Path where IP list file located.
     * @param baseUploadUrl Base Upload Url
     * @param baseUploadUrl Base Download Url
     * @param baseUploadUrl Base Download Url
     * @param autoDownloadEnabled True if Auto download enabled
     */
    private Chat(long userId, String userName, String offlineServerAddress, int offlineServerPort, String authenticationServerAddress, int authenticationServerPort, int deviceType, String appSessionId, int appVersion, long timeDifference, ArrayList<String> directoryPaths, String baseUploadUrl, String baseDownloadUrl, boolean autoDownloadEnabled, String key, int appType, ArrayList<Long> pageIdList) {
        ctor(userId, userName, offlineServerAddress, offlineServerPort, authenticationServerAddress, authenticationServerPort, deviceType, appSessionId, appVersion, timeDifference, directoryPaths, baseUploadUrl, baseDownloadUrl, autoDownloadEnabled, key, appType, pageIdList);
    }

    private native void ctor(long userId, String userName, String offlineServerAddress, int offlineServerPort, String authenticationServerAddress, int authenticationServerPort, int deviceType, String appSessionId, int appVersion, long timeDifference, ArrayList<String> directoryPaths, String baseUploadUrl, String baseDownloadUrl, boolean autoDownloadEnabled, String key, int appType, ArrayList<Long> pageIdList);
    
    /**
     * Re-initialize chat instance
     * @param userId Self user id
     * @param userName Self user name 
     * @param offlineServerAddress Offline server IP
     * @param offlineServerPort Offline server port
     * @param authenticationServerAddress authentication server IP
     * @param authenticationServerPort authentication server port
     * @param deviceType Self device type
     * @param appSessionId App Session ID
     * @param appVersion App Version
     * @param timeDifference Difference in time between server and client
     * @param directoryPaths Required directory paths for chatSDK
     * @param autoDownloadEnabled True if Auto Download Enabled
     * @param key Encryption decryption key
     * @param pageIdList page ID List
     */
    public native void reinitialize(long userId, String userName, String offlineServerAddress, int offlineServerPort, String authenticationServerAddress, int authenticationServerPort, int deviceType, String appSessionId, int appVersion, long timeDifference, ArrayList<String> directoryPaths, boolean autoDownloadEnabled, String key, ArrayList<Long> pageIdList);
    
    /**
     * Set offline server. Set the offline offline server address if it is updated
     * @param offlineServerAddress Offline server IP
     * @param offlineServerPort Offline server port
     */
    public native void setOfflineServer(String offlineServerAddress, int offlineServerPort);
    
    /**
     * Set authentication server.
     * @param authenticationServerAddress authentication server IP
     * @param authenticationServerPort authentication server port
     */
    public native void setAuthenticationServer(String authenticationServerAddress, int authenticationServerPort);
    
    /**
     * Check whether a connection exist with the given friendId
     * @param userId User ID
     * @param friendId corresponding friendId whose connection is being checked
     * @return true or false
     */
    public native boolean isExistsFriendConnection(long userId, long friendId);
    
    /**
     * Check whether a connection exist with the given groupId
     * @param groupId corresponding groupId whose connection is being checked
     * @return true or false
     */
    public native boolean isExistsGroupConnection(long groupId);
    
    /**
     * Request for offline messages. Should request for offline after log in
     * @param messageDate Message date
     * @param blockUpdateDate block update date
     * @return API status
     */
    public native ApiStatus requestForOffline(long messageDate, long blockUpdateDate);
    
    /**
     * Update register server for a friend chat session. Update the server information for a session
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param registerServerAddress IP of chat register server
     * @param registerServerPort Port of chat register server
     * @return API status
     */
    public native ApiStatus updateFriendRegisterServer(long userId, long friendId, String registerServerAddress, int registerServerPort);
    
    /**
     * Update friend status and mood. Update the status and mood of friend if it has been changed.
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param status Status (online, offline, away)
     * @param mood Mood
     * @return API status
     */
    public native ApiStatus updateFriendStatusAndMood(long userId, long friendId, int status, int mood);
    
    /**
     * Delete friend chat message. Delete single or a couple of message
     * @param userId UserID
     * @param friendId FriendId to chat with
     * @param packetIds List of packet id
     * @param deleteType defines delete type as it one-sided or both-sided
     * @return API status
     */
    public native ApiStatus deleteFriendChatMessage(long userId, long friendId, ArrayList<String> packetIds, int deleteType);
    
    /**
     * Request for friend chat history
     * @param userId User ID
     * @param friendId friend id
     * @param packetId packet id
     * @param direction earlier or later messages than the given time included in packetId
     * @param limit how many message wish to see
     * @return API status
     */
    public native ApiStatus requestFriendChatHistory(long userId, long friendId, String packetId, int direction, int limit);
    
    /**
     * get the status of the messages 
     * @param userId User ID
     * @param friendId friend id
     * @param packetIds Id's of messages whose status want to get
     * @return API status
     */
    public native ApiStatus getFriendMessageStatus(long userId, long friendId, ArrayList<String> packetIds);
    
    /**
     * Block a friend
     * @param userId User ID
     * @param packetId Corresponding packet id
     * @param friendId friend id to block
     * @param blockUnblockDate Date of blocking
     * @param addToBlock should or not add to block
     * @return API status
     */
    public native ApiStatus blockFriend(long userId, String packetId, long friendId, long blockUnblockDate, boolean addToBlock);
    
    /**
     * Unblock a friend
     * @param userId User ID
     * @param packetId Corresponding packet id
     * @param friendId Friend id to unblock
     * @param blockUnblockDate Date of unblocking
     * @return API status
     */
    public native ApiStatus unblockFriend(long userId, String packetId, long friendId, long blockUnblockDate);   
    
    /**
     * Delete group chat message. Delete single or a couple of message
     * @param groupId GroupId to chat
     * @param packetId Corresponding packetId
     * @return API status
     */
    public native ApiStatus deleteGroupChatMessage(long groupId, ArrayList<String> packetId);
    
    /**
     * Initiate a chat session.
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param friendName Name of the friend
     * @param friendUrl profile url of the friend
     * @param registerServerAddress IP of chat register server
     * @param registerServerPort Port of chat register server
     * @param deviceType Device type (android=2)
     * @param deviceToken Friend device token
     * @param appType Application type
     * @param status Status (online, offline, away)
     * @param mood Mood
     * @param iosVoipPush Is Ios Voip Push
     * @param authRegistrationTime registration time given by auth server
     * @param profileType Profile type
     * @return API status
     */
    public native ApiStatus registerFriendChat(long userId, String userName, long friendId, String friendName, String friendUrl, String registerServerAddress, int registerServerPort, int deviceType, String deviceToken, int appType, int status, int mood, int iosVoipPush, long authRegistrationTime, int profileType);
    
    /**
     * Unregister the chat with a friend. This can be called if the registration need to be stopped.
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param onlineStatus Status of friend
     * @param onlineMood Mood of friend
     * @return API status
     */
    public native ApiStatus unregisterFriendChat(long userId, long friendId, int onlineStatus, int onlineMood);
    
    /**
     * Send message to a friend.
     * @param packetId Corresponding packetId
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param messageType Message Type
     * @param secretTimeout Timeout for secret chat. For normal chat it should be 0
     * @param message Message to send to the friend
     * @param messageDate Message date
     * @param isSecretVisible whether the message will be visible or not
     * @return API status
     */
    public native ApiStatus sendFriendChat(String packetId, long userId, long friendId, int messageType, int secretTimeout, String message, long messageDate, boolean isSecretVisible);
    
	public native ApiStatus sendGeneralEncryptedInformation(long userID, long friendID, String packetID, int type, int informationType, String information);
    /**
     * Stop trying to send pending messages
     * @param userId User ID
     * @param friendId friendID to whom sent messages are pending
     * @return API status
     */
    public native ApiStatus dontSendPendingMessages(long userId, long friendId);
    
    /**
     * Send busy message to a friend
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param message Message to send to the friend
     * @param messageDate Message date
     * @param packetId packetID
     * @return API status
     */
    public native ApiStatus sendFriendCallBusyMessage(long userId, long friendId, String message, long messageDate, String packetId);
    
     /**
     * Send call log message to a friend
     * @param userId User ID
     * @param friendId FriendId
     * @param message Message
     * @param messageDate Message date
     * @param packetId packetID
     * @return API status
     */
    public native ApiStatus sendFriendCallLogMessage(long userId, long friendId, String message, long messageDate, String packetId);

    /**
     * Edit an existing friend chat message.
     * @param packetId Corresponding packetId
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param messageType Message Type
     * @param secretTimeout Timeout for secret chat. For normal chat it should be 0
     * @param message Message to send to the friend
     * @param messageDate Message date
     * @param isSecretVisible whether the message will be visible or not
     * @return API status
     */
    public native ApiStatus editFriendChat(String packetId, long userId, long friendId, int messageType, int secretTimeout, String message, long messageDate, boolean isSecretVisible);
    
    /**
     * Notify friend that this message is seen.
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param seenPacketList List of seen packet
     * @return API status
     */
    public native ApiStatus seenFriendChat(long userId, long friendId, ArrayList<SeenPacketDTO> seenPacketList);
    
    /**
     * Call this API when user starts typing
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @return API status
     */
    public native ApiStatus typingFriendChat(long userId, long friendId);
    
    /**
     * Register the event handler to be notified from SDK. This will also bind the handler thread with JVM
     * @param eventHandler Event Handler
     */
    public native void registerEventHandler(IChatEventHandler eventHandler);
    
    /**
     * Edit a previously sent group chat message
     * @param packetId packetId of that message
     * @param groupId GroupID of that message
     * @param messageType Message type
     * @param message Edited message
     * @param messageDate new date
     * @return API status
     */
    public native ApiStatus editGroupChat(String packetId, long groupId, int messageType, String message, long messageDate);
    
    /**
     * Initiate a group chat
     * @param groupId GroupId to chat
     * @param registerServerAddress IP of chat register server
     * @param registerServerPort Port of chat register server
     * @param authRegistrationTime registration time given by auth server
     * @return API status
     */
    public native ApiStatus registerGroupChat(long groupId, String registerServerAddress, int registerServerPort, long authRegistrationTime);
    
    /**
     * Unregister a group chat
     * @param groupId GroupId to chat
     * @param status Status (online, offline, away)
     * @param mood Mood
     * @return API status
     */
    public native ApiStatus unregisterGroupChat(long groupId, int status, int mood);
    
    /**
     * Send message to a group
     * @param packetId Corresponding packetId
     * @param groupId GroupId to chat
     * @param messageType Message Type
     * @param message Message to send to the group
     * @param messageDate Message date
     * @return API status
     */
    public native ApiStatus sendGroupChat(String packetId, long groupId, int messageType, String message, long messageDate);
    
    /**
     * Notify group users that this message is seen
     * @param groupId GroupId to chat
     * @param seenPacketIds Seen Packet IDs
     * @return API status
     */
    public native ApiStatus seenGroupChat(long groupId, ArrayList<String> seenPacketIds);
    
    /**
     * Get Group Message Seen List
     * @param groupId Group ID
     * @param packetId Packet ID
     * @return API status
     */
    public native ApiStatus getGroupMessageSeenList(long groupId, String packetId);
    
    /**
     * Get conversation list
     * @param userId User ID
     * @param conversationType conversation type
     * @param startIndex Start index
     * @param limit Limit
     * @param friendOrGroupId Friend or group ID
     * @return API status
     */
    public native ApiStatus getConversationList(long userId, int conversationType, int startIndex, int limit, long friendOrGroupId);
    
    /**
     * Delete conversation log
     * @param userId User ID
     * @param conversationList list of conversation to delete
     * @return API status
     */
    public native ApiStatus deleteConversation(long userId, ArrayList<ConversationDTO> conversationList);
    
    /**
     * Mark conversation list as read
     * @param userId User ID
     * @param conversationList list of conversation to mark as read
     * @return API status
     */
    public native ApiStatus markConversationSeen(long userId, ArrayList<ConversationDTO> conversationList);
    
    /**
     * Provide updated password
     * @param password new/updated password
     */
    public native void updateUserPassword(String password);
    
    /**
     * Call this API when user starts typing
     * @param groupId GroupId to chat
     * @return API status
     */
    public native ApiStatus typingGroupChat(long groupId);
    
    /**
     * Remove single or some members from a group.
     * @param groupId Group id to chat
     * @param memberIds List of member IDs
     * @return API status
     */
    public native ApiStatus removeGroupMembers(long groupId, ArrayList<Long> memberIds);
    
    /**
     * Change group name
     * @param groupId Groupid
     * @param groupName changed name
     * @return API status
     */
    public native ApiStatus changeGroupName(long groupId, String groupName);
    
    /**
     * Change group URL
     * @param groupId Group id
     * @param groupUrl Changed URL of the group
     * @return API status
     */
    public native ApiStatus changeGroupUrl(long groupId, String groupUrl);
    
    /**
     * Add single or some members to the group.
     * @param groupId GroupId to chat
     * @param memberList Member list
     * @return API status
     */
    public native ApiStatus addGroupMembers(long groupId, ArrayList<MemberDTO> memberList);
    
    /**
     * Change status of some members.
     * @param groupId GroupId to chat
     * @param memberList Member list
     * @return API status
     */
    public native ApiStatus changeGroupMemberStatus(long groupId, ArrayList<MemberDTO> memberList);
    
    /**
     * Create new group
     * @param groupId Id of the group
     * @param groupName group name
     * @param groupUrl group URL
     * @param memberList Members of the group
     * @return API status
     */
    public native ApiStatus createGroup(long groupId, String groupName, String groupUrl, ArrayList<MemberDTO> memberList);
    
    /**
     * Request group history messages
     * @param groupId Group Id
     * @param packetId packet id
     * @param direction earlier or later messages than the given time included in packetId
     * @param limit how many message wish to see
     * @return API status
     */
    public native ApiStatus requestGroupChatHistory(long groupId, String packetId, int direction, int limit);
    
    /**
     * Get group information with member list
     * @param groupId Group id
     * @return API status
     */
    public native ApiStatus getGroupInformationWithMembers(long groupId);
    
    /**
     * Leave the group.
     * @param groupId GroupId to chat
     * @return API status
     */
    public native ApiStatus leaveGroup(long groupId, boolean isHide);
    
    /**
     * Unregister event handler. This will detach handler and the handler thread from JVM
     * 
     */
    public native void unregisterEventHandler();
    
    /**
     * Set log file name. Need to provide full path of the file
     * @param fileName Log file name with full path
     */
    public native void setLogfile(String fileName);
    
    /**
     * getFriendInformation
     * @param userId User ID
     * @param friendId Friend id
     * @return Friend information
     */
    public native FriendInformation getFriendInformation(long userId, long friendId);
    
    /**
     * Get Group Information
     * @param groupId Group Id
     * @return Group Information
     */
    public native GroupInformation getGroupInformation(long groupId);
    
    /**
     * Get Registered Friends List 
     * @param userId User ID
     * @return List of All Registered Freind Ids
     */
    public native ArrayList<Long> getRegisteredFriendsList(long userId);
    
    /**
     * Get Registered group list
     * @return List of all Registered group
     */
    public native ArrayList<GroupInformation> getRegisteredGroupList();
        
    /**
     * Sends unregister for all friend and group, stop all services 
     * @param mood Mood
     */
    public native void cleanUp(int mood);
    
    /**
     * Get pending friend messages
     * @param userId User ID
     * @return packetId list of pending friend messages
     */
    public native ArrayList<String> getPendingFriendMessages(long userId);
    
    /**
     * Get pending group messages
     * @return packetId list of pending group messages
     */
    public native ArrayList<String> getPendingGroupMessages();
    
/**
     * Public Room Chat register
     * @param roomId Public Chat Room ID
     * @param memberName Public Chat Member Name
     * @param memberUrl Public Chat Member Url
     * @param ringId Ring ID
     * @return API status
     */
    public native ApiStatus registerPublicRoomChat(String roomId, String memberName, String memberUrl, long ringId);
    
    /**
     * Public Room Chat send message
     * @param packetId Public Chat Room message packet ID
     * @param roomId Public Chat Room ID
     * @param messageType Type of public chat room message
     * @param message message
     * @param messageDate messageDate
     * @param memberFullName Full Name of the Member
     * @param memberProfileUrl Profile Url of the Member
     * @return API status
     */
    public native ApiStatus sendPublicRoomChat(String packetId, String roomId, int messageType, String message, long messageDate, String memberFullName, String memberProfileUrl);
    
    /**
     * Public Room Chat edit message
     * @param packetId Public Chat Room message packet ID
     * @param roomId Public Chat Room ID
     * @param messageType Type of public chat room message
     * @param message message
     * @param messageDate messageDate
     * @param memberFullName Full Name of the Member
     * @param memberProfileUrl Profile Url of the Member
     * @return API status
     */
    public native ApiStatus editPublicRoomChat(String packetId, String roomId, int messageType, String message, long messageDate, String memberFullName, String memberProfileUrl);
    
    /**
     * Public room chat get room list
     * @param startIndex Public Chat Room start position from which RoomList will be returned
     * @param limit Number of rooms to be returned starting from startIndex
     * @return API status
     */
    public native ApiStatus getRoomList(int startIndex, int limit);
    
    /**
     * Public room chat get room list with history
     * @param startIndex Public Chat Room start position from which RoomList will be returned
     * @param limit Number of rooms to be returned starting from startIndex
     * @return API status
     */
    public native ApiStatus getRoomListWithHistory(int startIndex, int limit);
    
    /**
     * Get Public Chat Room Member List
     * @param roomId Public Chat Room ID
     * @param pagingState Paging State
     * @param limit Limit
     * @return API status
     */
    public native ApiStatus getRoomMemberList(String roomId, String pagingState, int limit);
    
    /**
     * Public room chat search room list
     * @param searchName search keyword
     * @param country Country filter. Pass empty string for default
     * @param startIndex Public Chat Room start position from which RoomList will be returned
     * @param category Category filter. Pass empty string for default
     * @param limit Number of rooms to be returned starting from startIndex
     * @return API status
     */
    public native ApiStatus searchRoomList(String searchName, String country, String category, int startIndex, int limit);
    
    /**
     * Public room chat unregister
     * @param roomId Public Chat Room ID
     * @return API status
     */
    public native ApiStatus unregisterPublicRoomChat(String roomId);
    
    /**
     * Public room chat register
     * @param roomId Public Chat Room ID
     * @return API status
     */
    public native ApiStatus typingPublicRoomChat(String roomId);
    
    /**
     * Check whether a connection exist with the given roomId
     * @param roomId corresponding roomId whose connection is being checked
     * @return true or false
     */
    public native boolean isExistsRoomConnection(String roomId);
    
    /**
     * Get Room Information (Room Name and Room Url)
     * @param roomId Public Chat Room ID
     * @return API status
     */
    public native ApiStatus getRoomInformation(String roomId);
            
    /**
     * Request Room Chat History
     * @param roomId Public Chat Room ID
     * @param packetId Packet ID
     * @param year Year
     * @param month Month
     * @param direction Direction
     * @param limit Limit
     * @return Api Status
     */
    public native ApiStatus requestRoomChatHistory(String roomId, String packetId, int year, int month, int direction, int limit);
    
    //Group file transfer

    /**
     * Get group file transfer idle packet
     * @param groupId Group ID
     * @return Byte array of group file transfer idle packet
     */
    public native byte[] getGroupFileTransferIdlePacket(long groupId);
    
//    /**
//     * File transfer request is sent
//     * @param friendId friend to whom the user wants to send the file to
//     * @param messageType message type for file transfer
//     * @param timeOut Time out
//     * @param fileId unique file identity
//     * @param fileFullPath source file path and name
//     * @param fileSize source file size
//     * @param messageDate time of file transfer request
//     * @param isSecretVisible Whether the file is secret or not
//     * @return API status
//     */
//    public native ApiStatus sendFileToFriend(long friendId, int messageType, int timeOut, long fileId, String fileFullPath, long fileSize, long messageDate, boolean isSecretVisible);
//    
//    /**
//     * File transfer request is accepted and start file transfer
//     * @param friendId friendId of the sender
//     * @param fileId fileId obtained from the event onFriendFileTransferRequestReceived
//     * @param filePath intended file path for receiving
//     * @return API status
//     */
//    public native ApiStatus startFileTransfer(long friendId, long fileId, String filePath);
//    
//    /**
//     * File transfer request is canceled
//     * @param friendId friendId of the sender/receiver
//     * @param fileId fileId of the file
//     * @return API status
//     */
//    public native ApiStatus cancelFileTransfer(long friendId, long fileId);
    
    /**
     * Get random packet id.
     * @param userId User ID
     * @return PacketTimeId
     */
    public native PacketTimeId generatePacketId(long userId);
    
    /**
     * Get packetId with time
     * @param timeMilli time in millisecond
     * @param userId self userId
     * @return PacketTimeId
     */
    public native PacketTimeId generatePacketId(long timeMilli, long userId);
    
    /**
     * Generate groupID
     * @return generated group ID
     */
    public native long generateGroupId();
    
    /**
     * Get the SDK version.
     * @return SDK Version
     */
    public native String version();
    
    public static native String getRingIdPackageName();
    public static native String getRingIncPackageName();

    /**
     * Get current time
     * @return Server sync time
     */
    public native long getCurrentServerSyncedTime();
    
    /**
     * Get time from given packetId
     * @param packetId Packet ID
     * @return Time
     */
    public native long getTimeFromPacketId(String packetId);
    
    /**
     * Register anonymous friend chat
     * @param selfAnonymousUserId Self anonymous user ID
     * @param friendAnonymousId Anonymous friend ID
     * @param originalFriendId Original friend ID
     * @param registerServerAddress Register server address
     * @param registerServerPort Register server port
     * @param deviceType Device type
     * @param deviceToken Device token
     * @param appType Application type
     * @param status Status (online, offline, away)
     * @param mood mood
     * @return Api status
     */
    public native ApiStatus registerAnonymousFriendChat(long selfAnonymousUserId, long friendAnonymousId, long originalFriendId, String registerServerAddress, int registerServerPort, int deviceType, String deviceToken, int appType, int status, int mood);
    
    /**
     * Unregister anonymous friend chat
     * @param friendId Friend ID
     * @param status Status (online, offline, away)
     * @param mood mood
     * @return Api status
     */
    public native ApiStatus unregisterAnonymousFriendChat(long userId, long friendId, int status, int mood);
    
    /**
     * Request shadowID info for specified userIds
     * @param userIds User IDs
     * @return Api status
     */
    public native ApiStatus getShadowIdInfo(ArrayList<Long> userIds);
    
    /**
     * Enable or disable log. By default log is enabled
     * @param enableDisable true for enabling false for disabling
     */
    public native void setLogEnabled(boolean enableDisable);
    
    /**
     * Enter Public Chat Screen
     * @param roomId Room Identity
     */
    public native void enterPublicChatScreen(String roomId);
    
    /**
     * Exit Public Chat Screen
     * @param roomId Room Identity
     */
    public native void exitPublicChatScreen(String roomId);
    
    /**
     * Get Network Data Count
     * @return Network data send receive count
     */
    public native DataCounter getDataSentReceived();
    
    /**
     * Delete Public Chat Message
     * @param roomId Room ID
     * @param packetIds Packet IDs
     * @return API Status
     */
    public native ApiStatus deletePublicChatMessage(String roomId, ArrayList<String> packetIds);
    
    /**
     * Like Public Chat Message
     * @param packetId  PacketID
     * @param roomId Room ID
     * @param messageSenderId SenderID of the liked message
     * @return API Status
     */
    public native ApiStatus likePublicChatMessage(String packetId, String roomId, long messageSenderId);
    
    /**
     * Like Public Chat Message
     * @param packetId  PacketID
     * @param roomId Room ID
     * @param messageSenderId SenderID of the liked message
     * @return API Status
     */
    public native ApiStatus unlikePublicChatMessage(String packetId, String roomId, long messageSenderId);
    
    /**
     * Report Public Chat Message
     * @param packetId  PacketID
     * @param roomId Room ID
     * @param messageSenderId SenderID of the reported message
     * @param reportMessage report message
     * @return API Status
     */
    public native ApiStatus reportPublicChatMessage(String packetId, String roomId, long messageSenderId, String reportMessage);
    
    /**
     * Get Public Chat Like Member List
     * @param roomId Room ID
     * @param packetId Packet ID
     * @param lastlikerid Last Liker ID
     * @param limit Limit
     * @return API status
     */
    public native ApiStatus getPublicChatLikeMemberList(String roomId, String packetId, long lastlikerid, int limit);
    
    /**
     * Get Public Chat Room Category List
     * @param lastCategory Last Category
     * @param limit Limit
     * @return API status
     */
    public native ApiStatus getPublicChatRoomCategoryList(String lastCategory, int limit);
    
    //Live-stream-chat
    /**
     * Register Live Stream Chat
     * @param publisherId User who is live streaming
     * @param registerServerAddress register server address
     * @param registerServerPort register server port
     * @param fullName Full Name of chat message sender
     * @return API status
     */
    public native ApiStatus registerLiveStreamChat(long publisherId, String registerServerAddress, int registerServerPort, String fullName);
    
    /**
     * Unregister from live stream chat
     * @param publisherId User who is live streaming
     * @param onlineStatus online status
     * @param onlineMood online mood
     * @return API status
     */
    public native ApiStatus unregisterLiveStreamChat(long publisherId, int onlineStatus, int onlineMood);
    
    /**
     * Typing live stream chat
     * @param publisherId User who is live streaming
     * @return API status
     */
    public native ApiStatus typingLiveStreamChat(long publisherId);
    
    /**
     * Send live stream chat
     * @param packetId packet id of the chat message
     * @param publisherId User who is live streaming
     * @param messageType message type
     * @param message message
     * @param messageDate message time
     * @return API status
     */
    public native ApiStatus sendLiveStreamChat(String packetId, long publisherId, int messageType, String message, long messageDate);

    /**
     * Block user from live stream chat
     * @param publisherId User who is live streaming
     * @param blockedUserId User to be blocked
     * @param packetId Packet ID
     * @return API status
     */
    public native ApiStatus blockUserFromLiveStreamChat(long blockedUserId, String packetId);

    /**
     * Check Internet Connection
     * @return True if checking in progress.
     */
    public native boolean checkInternetConnection();
    
    /**
     * Send Chat Media
     * @param userId User ID
     * @param friendId Friend ID
     * @param packetId Packet ID
     * @param mediaType Chat Media Type
     * @param filePath File Path
     * @param caption Caption
     * @param widthOrFileSize Width for image. File size for audio/video
     * @param heightOrDuration Height for image. Duration for audio/video
     * @param secretTimeout Secret timeout
     * @param messageDate Message Date
     * @param isSecretVisible Is secret visible
     * @return true if upload in progress
     */
    public native boolean sendFriendChatMedia(long userId, long friendId, String packetId, int mediaType, String filePath, String caption, int widthOrFileSize, int heightOrDuration, int secretTimeout, long messageDate, boolean isSecretVisible);
    
    /**
     * Download Chat Media
     * @param userId User ID
     * @param friendId friendId
     * @param packetId Packet ID
     * @param fileManifestUrl Cloud Url 
     * @param mediaType Chat Media Type
     * @param secretTimeout Secret timeout
     * @return  file path if exists already. Otherwise, 202 Accepted.
     */
    public native boolean downloadFriendChatMedia(long userId, long friendId, String packetId, String fileManifestUrl, int mediaType, int secretTimeout);
    
    /**
     * Accept Incoming Chat and Group Chat Media
     * @param packetId Packet ID
     * @return False if all file chunk upload already complete
     */
    public native boolean acceptChatMedia(String packetId);
    
     /**
     * Send Chat Media
     * @param groupId Group ID
     * @param packetId Packet ID
     * @param mediaType Chat Media Type
     * @param filePath File Path
     * @param caption Caption
     * @param widthOrFileSize Width for image. File size for audio/video
     * @param heightOrDuration Height for image. Duration for audio/video
     * @param messageDate Message Date
     * @return true if upload in progress
     */
    public native boolean sendGroupChatMedia(long groupId, String packetId, int mediaType, String filePath, String caption, int widthOrFileSize, int heightOrDuration, long messageDate);
    
    /**
     * Download Chat Media
     * @param groupId Group ID
     * @param friendId Friend ID
     * @param packetId Packet ID
     * @param fileManifestUrl Cloud Url 
     * @param mediaType Chat Media Type
     * @return  file path if exists already. Otherwise, 202 Accepted.
     */
    public native boolean downloadGroupChatMedia(long groupId, long friendId, String packetId, String fileManifestUrl, int mediaType);
    
    /**
     * Get pending chat media list
     * @param conversationType Conversation type
     * @param uploadingMediaList If true, API will return uploading list, else downloading list
     * @param isChunkedTransfer YES if Chunk transfer
     * @return pending chat media packet id list
     */
    public native ArrayList<String> getPendingChatMediaList(int conversationType, boolean uploadingMediaList, boolean isChunkedTransfer);

    public native void cancelChatMediaTransfer(String packetId);

    public native void updateAppSessionID(String packetId);

    public native void addUserPage(long pageId);

    /**
     * 
     * @param isAccountActivate
     * @return 
     */
    public native ApiStatus activateOrDeactivateUserAccount(boolean isAccountActivate);
    
    public native void removeUserPage(long pageId);
    
    
    
    /**
     * Get Synced Conversation
     * @param userId User ID
     * @param packetId Packet ID
     * @param lastSyncedTime time when last synced
     * @return API status
     */
    public native ApiStatus getSyncedConversation(long userId, String packetId, long lastSyncedTime);
    
    
    /**
     * Get Synced Friend History Message
     * @param userId User ID
     * @param friendId Friend ID
     * @param packetId Packet ID
     * @param lastSyncedTime time when last synced
     * @param limit number of messages
     * @param isButtonPressSync to detect either for button press or not
     * @return API status
     */
    public native ApiStatus getSyncedFriendHistoryMessage(long userId, long friendId, String packetId, long lastSyncedTime, int limit, int direction);
    
    
    
    /**
     * Get Synced Group History Message
     * @param userId User ID
     * @param groupId Group ID
     * @param packetId Packet ID
     * @param lastSyncedTime time when last synced
     * @param limit number of messages
     * @param isButtonPressSync to detect either for button press or not
     * @return API status
     */
    public native ApiStatus getSyncedGroupHistoryMessage(long userId, long groupId, String packetId, long lastSyncedTime, int limit, int direction);
   
    
    
    /**
     * Get My Group List Paging
     * @param userId User ID
     * @param groupId Group ID
     * @param packetId Packet ID
     * @param limit Limit
     * @return 
     */
    public native ApiStatus getMyGroupListPaging(long userId, String packetId, String pivotId, int limit, int direction);

    static {
        System.loadLibrary("imsdk");
    }
}
