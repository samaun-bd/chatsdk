/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ringid.imsdk;

import java.util.ArrayList;

/**
 * Event handler interface.
 * @author dipal
 */
public interface IChatEventHandler {

    /**
     * Handle friend chat register success. This event can be invoked if {@link Chat#registerFriendChat(long, java.lang.String, java.lang.String, java.lang.String, int, int, java.lang.String, int, int, int, int, long) } is called.
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param serverDate Current server time for friend registration
     * @param packetId Packet ID
     * @param fromAnonymousUser True if from anonymous user false otherwise
     */
    void onFriendChatRegisterSuccess(long userId, long friendId, long serverDate, String packetId, boolean fromAnonymousUser);

    /**
     * Handle friend chat register failure. This event can be invoked if {@link Chat#registerGroupChat(long, java.lang.String, int, long)  } is called.
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param packetId Packet ID
     * @param fromAnonymousUser True if from anonymous user false otherwise
     */
    void onFriendChatRegisterFailure(long userId, long friendId, String packetId, boolean fromAnonymousUser);

    /**
     * Handle registration expired event. This event will be invoked if there is no communication some time and the registration is expired.
     * @param userId
     * @param friendId FriendId to chat with
     * @param fromAnonymousUser True if from anonymous user false otherwise
     */
    void onFriendRegistrationExpired(long userId, long friendId, boolean fromAnonymousUser);
    
    /**
     * Handle friend unregistered event. This event will be invoked if friend unregistered with the session intentionally.
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param onlineStatus Status of friend
     * @param onlineMood Mood of friend
     * @param fromAnonymousUser True if from anonymous user false otherwise
     * @param profileType Profile Type
     */
    void onFriendUnregistered(long userId, long friendId, int onlineStatus, int onlineMood, boolean fromAnonymousUser, int profileType);
    
    /**
     * Handle new message. This event will be invoked if new message received.
     * @param senderId Sender of the message
     * @param receiverId Receiver of the message
     * @param packetId Corresponding packetId
     * @param messageType Message Type
     * @param secretTimeout Timeout for secret chat. For normal chat it should be 0
     * @param message Message to send to the friend
     * @param messageDate Message date
     * @param isSecretVisible whether the secret message is visible or not
     * @param fromOnline whether the message is received from online or offline. if true then received from online.
     * @param fromAnonymousUser True if from anonymous user false otherwise
     */
    void onFriendChatReceived(long senderId, long receiverId, String packetId, int messageType, int secretTimeout, String message, long messageDate, boolean isSecretVisible, boolean fromOnline, boolean fromAnonymousUser);

    /**
     * Handle message delivered. This event will be invoked if a sent message is delivered to friend.
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param packetId Corresponding packetId
     * @param fromAnonymousUser True if from anonymous user false otherwise
     * @param isEdited Is this message edited or not
     * @param fromOnline true if the delivered signal came from online, false otherwise
     */
    void onFriendChatDelivered(long userId, long friendId, String packetId, boolean fromAnonymousUser, boolean isEdited, boolean fromOnline);

    /**
     * Handle friend chat sent.
     * @param userId User ID
     * @param friendId Friend Identity
     * @param packetId Corresponding packetId
     * @param fromAnonymousUser True if from anonymous user false otherwise
     */
    void onFriendChatSent(long userId, long friendId, String packetId, boolean fromAnonymousUser);
    
    /**
     * Handle friend chat failed to send.
     * @param userId User ID
     * @param friendId Friend Identity
     * @param packetId Corresponding packetId
     * @param fromAnonymousUser True if from anonymous user false otherwise
     */
    void onFriendChatFailedToSend(long userId, long friendId, String packetId, boolean fromAnonymousUser);

    /**
     * Friend message seen. This event will be invoked if a message is seen by the friend.
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param seenPacketList List of seen packet
     * @param fromAnonymousUser True if from anonymous user false otherwise
     */
    void onFriendChatSeen(long userId, long friendId, ArrayList<SeenPacketDTO> seenPacketList, boolean fromAnonymousUser);
    
    /**
     * Confirmation that friend chat seen message was received
     * @param userId User ID
     * @param friendid friend who sent the seen packet
     * @param seenPacketList packetDTOs of seen packets
     * @param fromAnonymousUser True if from anonymous user false otherwise
     */
    void onFriendChatSeenConfirmed(long userId, long friendid, ArrayList<SeenPacketDTO> seenPacketList, boolean fromAnonymousUser);
    
    /**
     * Friend is typing. This event will be invoked if friend started to typing.
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param fromAnonymousUser True if from anonymous user false otherwise
     */
    void onFriendChatTyping(long userId, long friendId, boolean fromAnonymousUser);
    
    /**
     * Friend is idle
     * @param friendId Friend Id
     * @param fromAnonymousUser True if from anonymous user false otherwise
     */
    void onFriendChatIdle(long friendId, boolean fromAnonymousUser);

    /**
     * A previously sent message is edited. This event will be invoked if an old message has been edited.
     * @param senderId Sender of the message
     * @param receiverId Receiver of the message
     * @param packetId Corresponding packetId
     * @param messageType Message Type
     * @param secretTimeout Timeout for secret chat. For normal chat it should be 0
     * @param message Message to send to the friend
     * @param messageDate Message date
     * @param isSecretVisible whether the secret message is visible or not
     * @param fromOnline whether the message that was edited from online or offline. If online it's true, false for offline
     * @param fromAnonymousUser True if from anonymous user false otherwise
     */
    void onFriendChatEdited(long senderId, long receiverId, String packetId, int messageType, int secretTimeout, String message, long messageDate, boolean isSecretVisible, boolean fromOnline, boolean fromAnonymousUser);

    /**
     * A message is deleted. This event will be invoked if a previous has been deleted.
     * @param senderId User who requested message delete
     * @param friendId FriendId to chat with
     * @param packetIds Corresponding packetIds
     * @param fromAnonymousUser True if from anonymous user false otherwise
     */
    void onFriendChatDeleted(long senderId, long friendId, ArrayList<String> packetIds, boolean fromAnonymousUser);
 
    /**
     * You deleted a message and the friend is aware of that. This event will be invoked if you deleted a message and the friend is aware of that.
     * @param userId User iD
     * @param friendId FriendId to chat with
     * @param packetId packetId of the request
     * @param packetIds Corresponding packetIds
     * @param fromAnonymousUser True if from anonymous user false otherwise
     * @param status request status
     * @param deleteType message delete type    
     */
    void onFriendChatDeleteRequestStatus(long userId, long friendId, String packetId, ArrayList<String> packetIds, boolean fromAnonymousUser, boolean status, int deleteType);

    /**
     * The user is blocked by a friend. This event will be invoked if another user blocked this user.
     * @param blockerId Blocker ID
     * @param blockedId Blocked ID
     * @param blockUnblockDate Block Date
     * @param addToBlock Need to add in db
     */
    void onBlocked(long blockerId, long blockedId, long blockUnblockDate, boolean addToBlock);
    
    /**
     * The user is unblocked by a friend. This event will be invoked if another use unblocked this user.
     * @param unBlockerId Un blocker ID
     * @param unBlockedId Un blocked ID
     * @param blockUnblockDate Un block date
     */
    void onUnblocked(long unBlockerId, long unBlockedId, long blockUnblockDate);
    
    /**
     * Handle group chat register success. This event can be invoked if {@link Chat#registerGroupChat(long, java.lang.String, int, long)   } is called.
     * @param groupId Group id to chat
     * @param serverDate Current server time for group registration
     * @param packetId Packet ID
     */
    void onGroupChatRegisterSuccess(long groupId, long serverDate, String packetId);
    
    /**
     * Handle group chat register failure. This event can be invoked if {@link Chat#registerGroupChat(long, java.lang.String, int, long)   } is called.
     * @param groupId Group id to chat
     * @param packetId Packet ID
     */
    void onGroupChatRegisterFailure(long groupId, String packetId);
    
    /**
     * Handle registration expired event. This event will be invoked if there is no communication some time and the registration is expired.
     * @param groupId Group id to chat
     * @param lastActivityTime Last activity time
     */
    void onGroupRegistrationExpired(long groupId, long lastActivityTime);
    
    /**
     * A block/unblock request is successful.
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param packetId Packet ID
     * @param blockUnblockDate Block/Unblock date
     * @param status Failure or success status
     * @param isBlockRequest true if the request is for block, false otherwise
     */
    void onBlockUnblockRequestStatus(long userId, long friendId, String packetId, long blockUnblockDate, boolean status, boolean isBlockRequest);
    
    /**
     * A group message is sent.
     * @param groupId Group id to chat
     * @param packetId Corresponding packetId
     * @param isEdited True if the message is edited otherwise false
     */
    void onGroupChatSent(long groupId, String packetId, boolean isEdited);
    
    /**
     * A new group chat message is received.
     * @param senderId Sender of the group message
     * @param groupId Group id to chat
     * @param packetId Corresponding packetId
     * @param messageType Message Type
     * @param message Message to send to the friend
     * @param messageDate Message date
     * @param fromOnline Whether the message received from online or offline. true if from online, false otherwise
     */
    void onGroupChatReceived(long senderId, long groupId, String packetId, int messageType, String message, long messageDate, boolean fromOnline);
    
    /**
     * A previously sent group chat message was edited
     * @param groupId Group id to chat
     * @param senderId Sender of the group message edited
     * @param packetId Corresponding packetId
     * @param messageType Message Type
     * @param message Edited chat message
     * @param messageDate Message date
     * @param fromOnline Whether the message received from online or offline. true if from online, false otherwise
     */
    void onGroupChatEdited(long senderId, long groupId, String packetId, int messageType, String message, long messageDate, boolean fromOnline);
    
    /**
     * A group chat message was deleted
     * @param friendid user who deleted the message
     * @param groupid Group whose message was deleted
     * @param packetIds PacketIDs of the deleted messages
     */
    void onGroupChatDeleted(long friendid, long groupid, ArrayList<String> packetIds);
    
    /**
     * Confirmation received of the delete request of a chat message
     * @param groupid Group whose message was requested to be deleted
     * @param packetId PacketID of the deleted messages confirmation
     * @param packetIds Corresponding packetIds
     * @param requestStatus Success or failure status
     */
    void onGroupChatDeleteRequestStatus(long groupid, String packetId, ArrayList<String> packetIds, boolean requestStatus);
    
    /**
     * A previously sent message is delivered to a group user.
     * @param friendId FriendId to chat with
     * @param groupId Group id to chat
     * @param packetId Corresponding packetId
     */
    void onGroupChatDelivered(long friendId, long groupId, String packetId);
    
    /**
     * A previously sent message is seen by a friend.
     * @param groupId Group id to chat
     * @param seenPacketIds Seen PacketIDs
     */
    void onGroupChatSeen(long groupId, long userId, ArrayList<String> seenPacketIds);
    
    /**
     * Seen request send status
     * @param groupid Group id
     * @param packetIds Seen PacketIDs
     * @param status seen sending success or failure status
     */
    void onGroupChatSeenRequestStatus(long groupid, ArrayList<String> packetIds, boolean status);
    
    /**
     * Group Chat Message Seen List Received
     * @param groupId Group ID
     * @param packetId  packet ID
     * @param memberList Seen Member List
     */
    void onGroupChatMessageSeenListReceived(long groupId, String packetId, ArrayList<MemberDTO> memberList);
    
    /**
     * Conversation list of friend chat received
     * @param userId User ID
     * @param conversationList conversation list
     * @param isFromSynced is from synced request or not
     */
    void onFriendChatConversationListReceived(long userId, ArrayList<SDKMessageDTO> conversationList, boolean isFromSynced);
    
    /**
     * Conversation list of group chat received
     * @param conversationList conversation list 
     */
    void onGroupChatConversationListReceived(ArrayList<SDKMessageDTO> conversationList, boolean isFromSynced);

    /**
     * Chat Conversation List Request Status received
     * @param userId User ID
     * @param friendOrGroupId Friend or Group ID
     * @param packetId Packet ID
     * @param status status
     */
    void onChatConversationListRequestStatus(long userId, long friendOrGroupId, String packetId, boolean status);

    /**
     * Conversation list receiving completed
     * @param userId User ID
     */
    void onChatConversationListCompleted(long userId, boolean isFromSynced);
    
    /**
     * Conversation list delete request status success or fail
     * @param userId User ID
     * @param packetId packetId of the request
     * @param status true if the request was successful false otherwise
     */
    void onConversationListDeleteRequestStatus(long userId, String packetId, boolean status);
    
    /**
     * Conversation list mark as read request status success or fail
     * @param userId User ID
     * @param packetId PacketId of the request
     * @param status true if the request was successful false otherwise
     */
    void onConversationListMarkAsSeenRequestStatus(long userId, String packetId, boolean status);
    
    /**
     * A group member started typing.
     * @param friendId FriendId to chat with
     * @param groupId Group id to chat
     */
    void onGroupChatTyping(long friendId, long groupId);
    
    /**
     * Group is idle
     * @param friendId friend id
     * @param groupId group id
     */
    void onGroupChatIdle(long friendId, long groupId);
    
    /**
     * A group member remove leave request was sent
     * @param groupId Group id to chat
     * @param packetId Corresponding packetId
     * @param status Request success or failure status
     * @param isHide is leave or leave with hide
     */
    void onGroupMemberRemoveLeaveRequestStatus(long groupId, String packetId, boolean status, boolean isHide);
    
    /**
     * A new member was added to the group
     * @param groupId Group id to chat
     * @param packetId Corresponding packetId
     * @param status Request success or failure status
     * @param memberList List of members for whom request was successful/failure
     */
    void onGroupMemberAddRequestStatus(long groupId, String packetId, boolean status, ArrayList<MemberDTO> memberList);
    
    /**
     * Status of a group member was changed
     * @param groupId Group id to chat
     * @param packetId Corresponding packetId
     * @param status Request success or failure status
     */
    void onGroupMemberStatusChangeRequestStatus(long groupId, String packetId, boolean status);
    
    /**
     * A couple of group member is removed or left.
     * @param friendId FriendId to chat with
     * @param groupId Group id to chat
     * @param memberList Member list
     * @param packetId Corresponding packetId
     * @param isHide is leave or leave with hide
     */
    void onGroupMemberRemovedOrLeft(long friendId, long groupId, ArrayList<Long> memberList, String packetId, boolean isHide);
    
    /**
     * Some user is added to this group.
     * @param friendId FriendId to chat with
     * @param groupId Group id to chat
     * @param memberList Member list
     * @param packetId Corresponding packetId
     */
    void onGroupMemberAdded(long friendId, long groupId, ArrayList<MemberDTO> memberList, String packetId);
    
    /**
     * Status of some group member has been changed.
     * @param senderId User that changed the status
     * @param groupId Group id to chat
     * @param memberList Member list
     * @param packetId Corresponding packetId
     */
    void onGroupMemberStatusChanged(long senderId, long groupId, ArrayList<MemberDTO> memberList, String packetId);
    
    /**
     * Handle group chat failed to send.
     * @param groupId Group id to chat
     * @param packetId Corresponding packetId
     */
    void onGroupChatFailedToSend(long groupId, String packetId);
    
    /**
     * Should request to auth server about the presence of a user.
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param fromAnonymousUser True if from anonymous user false otherwise
     */
    void shouldCheckFriendPresence(long userId, long friendId, boolean fromAnonymousUser, int profileType);
    
    /**
     * Should request to auth server a new server address for a friend chat session.
     * @param userId User ID
     * @param friendId FriendId to chat with
     * @param fromAnonymousUser True if from anonymous user false otherwise
     */
    void shouldCheckServerAddressForFriend(long userId, long friendId, boolean fromAnonymousUser);
    
    /**
     * Should request to auth server a new server address for a group chat session.
     * @param groupId GroupId of the group
     */
    void shouldCheckServerAddressForGroup(long groupId);
    
    /**
     * Should request to auth server a new offline server address for chat session.
     */
    void shouldCheckOfflineServerAddress();
    
    /**
     * Friend History message received
     * @param userId User ID
     * @param friendId Friend Id
     * @param chatMessageList Friend history message list
     * @param direction 1 for upward direction 2 for downward direction
     */
    void onFriendHistoryMessageReceived(long userId, long friendId, ArrayList<SDKMessageDTO> chatMessageList, int direction);//long senderId, long receiverId, String packetId, int messageType, int timeout, String message, long messageDate, boolean isSecretVisible, int messageStatus, int direction
    
    /**
     * List of Messages with the status of those message
     * @param userId User ID
     * @param friendId Friend Identity
     * @param messageList messageList
     */
    void onFriendMessagesStatusReceived(long userId, long friendId, ArrayList<FriendMessageStatusDTO> messageList);
    
    /**
     * Friend history receiving completed
     * @param userId User ID
     * @param friendId Friend ID
     * @param direction Up or down status
     */
    void onFriendHistoryCompleted(long userId, long friendId, int direction);
    
    /**
     * Group history message received
     * @param groupId groupId
     * @param groupHistoryMessageList History message of group
     * @param direction 1 for upward direction 2 for downward direction
     */
    void onGroupHistoryMessageReceived(long groupId, ArrayList<SDKMessageDTO> groupHistoryMessageList, int direction);//long senderId, String packetId, int messageType, String message, long messageDate, int direction
    
    /**
     * Group history message receiving completed
     * @param groupId Group ID
     * @param direction Up or down status
     */
    void onGroupHistoryCompleted(long groupId, int direction);
    
    /**
     * Group information with member list received
     * @param groupId groupId
     * @param groupName groupName
     * @param groupUrl groupUrl
     * @param memberList List of members in the group
     */
    void onGroupInformationWithMembersReceived(long groupId, String groupName, String groupUrl, ArrayList<MemberDTO> memberList);
    
    /**
     * Group information with member request failed 
     * @param groupId Group ID
     * @param packetId Packet ID
     * @param status Request success or failure status
     */
    void onGroupInformationWithMembersRequestStatus(long groupId, String packetId, boolean status);
    
    /**
     * Group information with different activity received
     * @param groupActivityList group activity list 
     */
    void onGroupInformationActivityReceived(ArrayList<GroupActivityDTO> groupActivityList);
    
    /**
     * Group Information activity from history message received
     * @param groupId groupId
     * @param groupActivityList group activity list
     * @param direction Up or down direction
     */
    void onGroupInformationActivityFromHistoryMessageReceived(long groupId, ArrayList<GroupActivityDTO> groupActivityList, int direction);
    
    /**
     * Group list received
     * @param myGroupList list of group where the user has been added
     */
    void onMyGroupListReceived(ArrayList<GroupDTO> myGroupList);
    
    /**
     * 
     * @param myGroupList list of group where the user has been added
     * @param pivotId paging request tracing Id
     * @param direction scroll type
     */
    void onMyGroupListPagingReceived(ArrayList<GroupDTO> myGroupList, String pivotId, int direction);
    
    /**
     * Group list receive completed
     */
    void onMyGroupListReceiveCompleted();
    
    /**
     * new group created
     * @param groupId group id
     * @param packetId Packet ID
     * @param status Group create request success or failure status
     */
    void onGroupCreated(long groupId, String packetId, boolean status);
    
    /**
     * Group information sent
     * @param groupId group id
     * @param packetId packet id
     * @param status Request success or failure status
     */
    void onGroupInformationChangeRequestStatus(long groupId, String packetId, boolean status);
    
    /**
     * Group name changed
     * @param packetId packet id
     * @param friendid user who changed the name
     * @param groupid group id
     * @param groupName changed name of the group
     */
    void onGroupNameChanged(String packetId, long friendid, long groupid, String groupName);
    
    /**
     * Group URL changed
     * @param packetId packet id
     * @param friendid user who changed the URL
     * @param groupid group id
     * @param groupUrl changed group URL
     */
    void onGroupUrlChanged(String packetId, long friendid, long groupid, String groupUrl);
    
    /**
     * Friend history message request status
     * @param userId User ID
     * @param friendId Friend ID
     * @param packetId Packet ID
     * @param status Request success or failure status
     */
    void onFriendHistoryMessageRequestStatus(long userId, long friendId, String packetId, boolean status);
    
    /**
     * Group history message request status
     * @param groupId Group ID
     * @param packetId Packet ID
     * @param status Request success or failure status
     */
    void onGroupHistoryMessageRequestStatus(long groupId, String packetId, boolean status);
    
    /**
     * Time difference between server and client received
     * @param timeDifference Time difference with server
     */
    void onServerTimeSynced(long timeDifference);
    
    /**
     * Public Room Chat registration success
     * @param roomId roomId
     * @param packetId Packet ID
     * @param numberOfMember Member count
     * @param anonymousId Anonymous ID of self
     */
    void onPublicRoomChatRegisterSuccess(String roomId, String packetId, int numberOfMember, long anonymousId);
    
    /**
     * Public Room Chat registration failed
     * @param roomId roomId
     * @param packetId Packet ID
     */
    void onPublicRoomChatRegisterFailure(String roomId, String packetId);
    
    /**
     * Public Room Chat registration expired
     * @param roomId Public Chat room ID
     */
    void onPublicRoomChatRegistrationExpired(String roomId);
    
    /**
     * Public Room Chat message delivered
     * @param roomId public chat room ID
     * @param packetId message packetId
     * @param isEdited Is this message edited or not
     */
    void onPublicRoomChatDelivered(String roomId, String packetId, boolean isEdited);
    
    /**
     * Public Room Chat message delivered
     * @param roomId Room ID
     * @param packetId message packetId
     */
    void onPublicRoomChatFailedToSend(String roomId, String packetId);
    
    /**
     * Public Room Chat message received
     * @param roomId public chat room ID
     * @param friendId sender of the message
     * @param packetId message packetId
     * @param messageType type of the message
     * @param message received message
     * @param messageDate message date
     * @param memberFullName Full Name of the Member
     * @param memberProfileUrl Profile Url of the Member
     */
    void onPublicRoomChatReceived(String roomId, long friendId, String packetId, int messageType, String message, long messageDate, String memberFullName, String memberProfileUrl);
    
    /**
     * Public Room Chat room list received
     * @param roomList room list
     * @param roomListFromHistory true if the room list from history, false otherwise
     */
    void onPublicRoomListReceived(ArrayList<RoomDTO> roomList, boolean roomListFromHistory);
    
    /**
     * Public Room Information Received
     * @param roomId Room Id
     * @param roomName Public Chat Room Name
     * @param roomUrl Public Chat Room Url
     * @param packetId Packet ID
     */
    void onPublicRoomInformationReceived(String roomId, String roomName, String roomUrl, String packetId);
            
    /**
     * Public Room Chat edited message received
     * @param roomId Public Chat Room ID
     * @param friendId Sender of the message
     * @param packetId message packetId
     * @param messageType type of the message
     * @param message Received message
     * @param messageDate message date
     * @param memberFullName Full Name of the Member
     * @param memberProfileUrl Profile Url of the Member
     */
    void onPublicRoomChatEdited(String roomId, long friendId, String packetId, int messageType, String message, long messageDate, String memberFullName, String memberProfileUrl);
    
    /**
     * Public Chat Room friend typing
     * @param roomId Public Chat Room in which friend is typing
     * @param friendId Friend who is typing
     * @param memberName Public Chat Member Name
     */
    void onPublicRoomChatTyping(String roomId, long friendId, String memberName);
    
    /**
     * Public Chat member list received
     * @param roomId Public Chat Room ID
     * @param pagingState Paging State
     * @param memberList public chat room member list 
     */
    void onPublicChatMemberListReceived(String roomId, String pagingState, ArrayList<PublicChatMemberDTO> memberList);
    
    /**
     * Room member count changed after some member added or left
     * @param roomId Room ID
     * @param numberOfMembers Current number of members after adding/leaving user from the room 
     */
    void onPublicChatMemberCountChanged(String roomId, int numberOfMembers);
    
    /**
     * Should check Server address for room
     * @param roomId Public Chat Room Id
     */
    void shouldCheckServerAddressForRoom(String roomId);
    
    
    /**
     * Public Room Chat history received
     * @param roomId Public Chat Room ID
     * @param publicChatHistoryMessageList Public Chat History Message List
     */
    void onPublicRoomChatHistoryReceived(String roomId, ArrayList<SDKMessageDTO> publicChatHistoryMessageList);
    
    /**
     * Public chat history fetching completed for that room
     * @param roomId roomId of the room
     */
    void onPublicRoomChatHistoryCompleted(String roomId);
    
    /**
     * Public room list request status received
     * @param packetId Packet ID
     * @param requestStatus Success or failure status
     */
    void onPublicRoomListRequestStatus(String packetId, boolean requestStatus);
    
    /**
     * Public room information request failed
     * @param roomId Room ID
     * @param packetId Packet ID
     */
    void onPublicRoomInformationRequestFailed(String roomId, String packetId);
    
    /**
     * Public room chat history request status received
     * @param roomId Room ID
     * @param packetId Packet ID
     * @param requestStatus success or failure status
     */
    void onPublicRoomChatHistoryRequestStatus(String roomId, String packetId, boolean requestStatus);
    
    /**
     * Public room member list request status received
     * @param roomId Room ID
     * @param packetId packet ID
     * @param requestStatus success or failure status
     */
    void onPublicRoomMemberListRequestStatus(String roomId, String packetId, boolean requestStatus);
    
    /**
     * ShadowID Info request failed
     * @param packetId Packet Id of the request
     */
    void onShadowIdsInfoRequestFailed(String packetId);
    
    /**
     * ShadowID info response received
     * @param shadowIdsInfo List of PublicChatMemberDTO that contains shadow IDs of requested userIds
     */
    void onShadowIdsInfoResponseReceived(ArrayList<PublicChatMemberDTO> shadowIdsInfo);
    
    /**
     * Network Data Counted
     * @param dataCounter Sent and Received Data Count
     */
    void onNetworkDataCounted(DataCounter dataCounter);
    
    /**
     * Public Chat Message Deleted
     * @param roomId Room ID
     * @param packetIds Deleted Packet IDs
     */
    void onPublicChatMessageDeleted(String roomId, ArrayList<String> packetIds);
    
    /**
     * Public Chat Message Liked
     * @param roomId Room ID
     * @param packetId Packet ID
     * @param likerId userId of the user who liked the message
     */
    void onPublicChatMessageLiked(String roomId, String packetId, long likerId);
    
    /**
     * Public Chat Message Liked
     * @param roomId Room ID
     * @param packetId Packet ID
     * @param unlikerId userId of the user who unliked the message
     */
    void onPublicChatMessageUnliked(String roomId, String packetId, long unlikerId);
    
    /**
     * Public Chat Message Reported
     * @param roomId Room ID
     * @param packetId Packet ID
     * @param reporterId userId of the user who reported message
     */
    void onPublicChatMessageReported(String roomId, String packetId, long reporterId);
    
    /**
     * Public Chat Category List Received
     * @param publicChatCategoryList Public Chat Category List
     */
    void onPublicChatCategoryListReceived(ArrayList<String> publicChatCategoryList);
    
    /**
     * Public Chat Like Member List Received
     * @param roomId Room ID
     * @param packetId Packet ID
     * @param publicChatMemberList Public Chat Like MemberList 
     */
    void onPublicChatLikeMemberListReceived(String roomId, String packetId, ArrayList<PublicChatMemberDTO> publicChatMemberList);
    
    /**
     * Public chat delete request status received
     * @param roomId Room ID
     * @param packetId packet ID
     * @param requestStatus success or failure status
     */
    void onPublicChatDeleteRequestStatus(String roomId, String packetId, boolean requestStatus);
    
    /**
     * Public chat like unlike request status received
     * @param roomId Room ID
     * @param requestPacketId packet id of the request
     * @param messagePacketId packet id of the message
     * @param requestStatus success or failure status
     * @param fromLikeRequest whether this request status is for Like or Unlike request
     */
    void onPublicChatLikeUnlikeRequestStatus(String roomId, String requestPacketId, String messagePacketId, boolean requestStatus, boolean fromLikeRequest);
    
    /**
     * Public chat report request status received
     * @param roomId Room ID
     * @param requestPacketId packet id of the request
     * @param messagePacketId packet id of the message
     * @param requestStatus success or failure status
     */
    void onPublicChatReportRequestStatus(String roomId, String requestPacketId, String messagePacketId, boolean requestStatus);
    
    /**
     * Public chat member list request status received
     * @param roomId Room ID
     * @param packetId packet ID
     * @param requestStatus success or failure status
     */
    void onPublicChatLikeMemberListRequestStatus(String roomId, String packetId, boolean requestStatus);
    
    /**
     * Public chat category list request status received
     * @param packetId packet ID
     * @param requestStatus success or failure status
     */
    void onPublicChatCategoryListRequestStatus(String packetId, boolean requestStatus);
    
    //Live stream chat
    /**
     * Live stream chat register successful
     * @param publisherId User who is live streaming
     * @param packetId packet ID
     */
    void onLiveStreamChatRegisterSuccess(long publisherId, String packetId);
    
    /**
     * Live stream chat register failed
     * @param publisherId User who is live streaming
     * @param packetId packet ID
     */
    void onLiveStreamChatRegisterFailure(long publisherId, String packetId);
    
    /**
     * Live stream chat registration expired
     * @param publisherId User who is live streaming
     */
    void onLiveStreamChatRegistrationExpired(long publisherId);
    
    /**
     * Live stream chat delivered
     * @param publisherId User who is live streaming
     * @param packetId packet ID
     */
    void onLiveStreamChatDelivered(long publisherId, String packetId);
    
    /**
     * Live stream chat failed to send
     * @param publisherId User who is live streaming
     * @param packetId packet ID
     */
    void onLiveStreamChatFailedToSend(long publisherId, String packetId);
    
    /**
     * New live stream chat received
     * @param publisherId User who is live streaming
     * @param senderId Live stream chat sender ID
     * @param packetId packet ID
     * @param messageType message type
     * @param message message
     * @param messageDate message time
     * @param senderFullName full name of the sender 
     */
    void onLiveStreamChatReceived(long publisherId, long senderId, String packetId, int messageType, String message, long messageDate, String senderFullName);
    
    /**
     * Live stream chat typing
     * @param publisherId User who is live streaming
     * @param senderId id of the user who is typing
     */
    void onLiveStreamChatTyping(long publisherId, long senderId);
    
    /**
     * No IP port for live streaming of this publisher
     * @param publisherId User who is live streaming
     */
    void shouldCheckServerAddressForLiveStreamChat(long publisherId);

    /**
     * Live Stream Chat Block User Request Status received
     * @param blockedUserId User who blocked
     * @param packetId Request Packet ID
     */
    void onLiveStreamChatBlockUserRequestStatus(long blockedUserId, String packetId);

    /**
     * Live Stream Chat User Blocked
     * @param publisherId Live stream publisher ID
     * @param blockedUserId Blocked user ID
     */
    void onLiveStreamChatUserBlocked(long publisherId, long blockedUserId);

    /**
     * On File Manifest Uploaded
     * @param userId User ID
     * @param friendId FriendID
     * @param packetId Packet ID
     * @param fileUrl File Manifest Cloud Url
     * @param mediaType Chat Media Type
     * @param timeout Secret timeout
     * @param caption Caption
     * @param widthOrFileSize Width for image, file size for audio or video
     * @param heightOrDuration Height for image, duration for audio or video
     */
    void onFriendFileManifestUploaded(long userId, long friendId, String packetId, String fileUrl, int mediaType, int timeout, String caption, int widthOrFileSize, int heightOrDuration);
    
    /**
     * On Incoming Chat Media to download
     * @param userId User ID
     * @param friendId Friend ID
     * @param fileName File Name
     * @param packetId Packet ID
     * @param messageType Message Type
     * @param timeout Secret timeout
     * @param messageDate Message Date
     * @param isSecretVisible Is secret visible
     * @param caption Caption
     * @param widthOrSize Width for image, file size for audio or video
     * @param heightOrDuration Height for image, duration for audio or video
     */
    void onFriendIncomingChatMedia(long userId, long friendId, String fileName, String packetId, int messageType, int timeout, long messageDate, boolean isSecretVisible, String caption, int widthOrSize, int heightOrDuration);
    
    /**
     * On Chat Media Transfer Progress
     * @param userId User ID
     * @param friendId FriendID
     * @param fileName File Name
     * @param transferPercentage Transfer completed (in percent)
     * @param isUpload True if transfer type is upload
     * @param packetId Packet ID
     */
    void onFriendChatMediaTransferProgress(long userId, long friendId, String fileName, double transferPercentage, boolean isUpload, String packetId);

    /**
     * On Chat Media Transfer Failed
     * @param userId User ID
     * @param friendId Friend ID
     * @param fileName File Name
     * @param packetId Packet ID
     * @param isUpload True if transfer type is upload
     * @param isChunkedTransfer True if media transfer strategy is chunked
     */
    void onFriendChatMediaTransferFailed(long userId, long friendId, String fileName, String packetId, boolean isUpload, boolean isChunkedTransfer);
    

    /**
     * On Chat Media Download Completed
     * @param userId User ID
     * @param friendId Friend ID
     * @param fileNameWithPath Downloaded file name with full path
     * @param packetId Packet ID
     * @param mediaType Media Type
     * @param timeout Secret Timeout
     */
    void onFriendChatMediaDownloadCompleted(long userId, long friendId, String fileNameWithPath, String packetId, int mediaType, int timeout);

    /**
     * On friend chat media transfer canceled
     * @param userId User ID
     * @param friendId Friend ID
     * @param canceledBy Canceled by UserID
     * @param fileName File Name
     * @param packetId Packet ID
     * @param isUpload True if transfer type is upload
     * @param isChunkedTransfer True if media transfer strategy is CHUNKED
     */
    void onFriendChatMediaTransferCanceled(long userId, long friendId, long canceledBy, String fileName, String packetId, boolean isUpload, boolean isChunkedTransfer);
    
    /**
     * GroupFileManifestUploaded
     * @param groupId Group ID
     * @param packetId Packet ID
     * @param cloudManifestUrl Cloud manifest URL
     * @param messageType Message type
     * @param caption Caption
     * @param widthOrFileSize Width for image, file size for audio or video
     * @param heightOrDuration Height for image, duration for audio or video
     */
    void onGroupFileManifestUploaded(long groupId, String packetId, String cloudManifestUrl, int messageType, String caption, int widthOrFileSize, int heightOrDuration);
    
    /**
     * IncomingGroupChatMedia
     * @param friendId Friend ID
     * @param groupId Group ID
     * @param fileName File name
     * @param packetId Packet ID
     * @param messageType Message type
     * @param messageDate Message date
     * @param caption Caption
     * @param widthOrSize Width for image, file size for audio or video
     * @param heightOrDuration Height for image, duration for audio or video
     */
    void onGroupIncomingChatMedia(long friendId, long groupId, String fileName, String packetId, int messageType, long messageDate, String caption, int widthOrSize, int heightOrDuration);  
    
    /**
     * GroupChatMediaTransferProgress
     * @param friendId Friend ID
     * @param groupId Group ID
     * @param fileName File Name
     * @param transferPercentage Transfer completed (in percent)
     * @param isUpload True if transfer type is upload
     * @param packetId Packet ID
     */
    void onGroupChatMediaTransferProgress(long friendId, long groupId, String fileName, double transferPercentage, boolean isUpload, String packetId);
    
    /**
     * GroupChatMediaTransferFailed
     * @param friendId Friend ID
     * @param groupId Group ID
     * @param fileName File name
     * @param packetId Packet ID
     * @param isUpload True if transfer type is upload
     * @param isChunkedTransfer True if media transfer strategy is chunked
     */
    void onGroupChatMediaTransferFailed(long friendId, long groupId, String fileName, String packetId, boolean isUpload, boolean isChunkedTransfer);
    
    /**
     * GroupChatMediaDownloadCompleted
     * @param friendId Friend ID
     * @param groupId Group ID
     * @param fileNameWithPath Downloaded file name with full path
     * @param packetId Packet ID
     * @param mediaType Media Type
     */
    void onGroupChatMediaDownloadCompleted(long friendId, long groupId, String fileNameWithPath, String packetId, int mediaType);

    /**
     * On group chat media transfer canceled
     * @param friendId Friend ID
     * @param groupId Group ID
     * @param canceledBy Canceled by UserID
     * @param fileName File name
     * @param packetId Packet ID
     * @param isUpload True if transfer type is upload
     * @param isChunkedTransfer True if media transfer strategy is CHUNKED
     */
    void onGroupChatMediaTransferCanceled(long friendId, long groupId, long canceledBy, String fileName, String packetId, boolean isUpload, boolean isChunkedTransfer);

    /**
     * Directory error occurred during chat media transfer.
     */
    void onChatMediaTransferDirectoryError(String directoryPath);

    /**
     * Should update App Session ID
     */
    void shouldUpdateAppSessionID();

    /**
     * Should update user password cause password previously given was empty
     */
    void shouldUpdateUserPassword();
    
    /**
     * Account activate or deactivate request status
     * @param userId
     * @param packetId
     * @param isAccountActivate
     * @param status 
     */
    void onActivaeOrDeactivateUserAccountStatus(long userId, String packetId, boolean isAccountActivate, boolean status);
    
    /**
     * SDK error occurred. This event will be invoked if an internal error has been occurred. Report the error code and packetId.
     * @param errorCode Error code
     * @param packetId Corresponding packetId
     */
    void onSDKError(int errorCode, String packetId);

    /**
     * Sync Conversation Request Status
     * @param userId
     * @param packetId
     * @param syncTime
     * @param status 
     */
    void onSyncConversationRequestStatus(long userId, String packetId, long syncTime, boolean status);
    
    /**
     * Sync Friend History Message Request Status
     * @param userId
     * @param friendId
     * @param packetId
     * @param syncTime
     * @param direction
     * @param status 
     */
    void onSyncFriendHistoryMessageRequestStatus(long userId, long friendId, String packetId, long syncTime, int direction, boolean status);
    
    
    /**
     * Sync Friend History Message Received
     * @param userId
     * @param friendId
     * @param packetId
     * @param chatMessageList
     * @param oldestMessageDate
     * @param direction 
     */
    void onSyncFriendHistoryMessageReceived(long userId, long friendId, String packetId, ArrayList<SDKMessageDTO> chatMessageList, long oldestMessageDate, int direction);
    
    
    /**
     * Sync Friend History Message Receive Completed
     * @param userId
     * @param friendId
     * @param packetId
     * @param direction 
     */
    void onSyncFriendHistoryMessageReceiveCompleted(long userId, long friendId, String packetId, int direction);

    
    /**
     * Sync Group History Message Request Status
     * @param groupId
     * @param packetId
     * @param syncTime
     * @param direction
     * @param status 
     */
    void onSyncGroupHistoryMessageRequestStatus(long groupId, String packetId, long syncTime, int direction, boolean status);
    
    
    /**
     * Sync Group History Message Received
     * @param groupId
     * @param packetId
     * @param groupHistoryMessageList
     * @param groupActivityList
     * @param oldestMessageDate
     * @param direction 
     */
    void onSyncGroupHistoryMessageReceived(long groupId, String packetId, ArrayList<SDKMessageDTO> groupHistoryMessageList, ArrayList<GroupActivityDTO> groupActivityList, long oldestMessageDate, int direction);
    
    /**
     * Sync Group History Message Receive Completed
     * @param groupId
     * @param packetId
     * @param direction 
     */
    void onSyncGroupHistoryMessageReceiveCompleted(long groupId, String packetId, int direction);
	
	void onGeneralEncryptedPacketReceived(long userID, long friendID, String packetID, int type, int informationType, String information);
	
	void onGeneralEncryptedPacketConfirmationReceived(long userID, long friendID, String packetID, int type, int informationType);

}
