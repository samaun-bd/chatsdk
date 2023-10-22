/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ringid.imsdk;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;

/**
 * ChatParser provides apis to handle all kind of chat messages. It can convert
 * any raw buffer to packet object or packet object to raw buffer. It is
 * possible to do all kinds of parsing using
 * {@link ChatParser#parse(com.ringid.imsdk.MessageDTO)} and
 * {@link ChatParser#parse(byte[])} functions. In addition this parser provides
 * a bunch of extra methods to generate specific type of raw packet. The parser
 * will expect to have a native library <tt>libchatparser.so</tt>. Please
 * confirm the the native library stays at default library path
 * (java.library.path)
 *
 * @author dipal
 */
public class ChatParser {

    private static ChatParser parser = null;

    private ChatParser() {
    }

    private synchronized static void createInstance() {
        if (parser == null) {
            parser = new ChatParser();
        }
    }

    /**
     * Get Parser Instance
     *
     * @return {@link ChatParser}
     */
    public static ChatParser getInstance() {
        //System.out.println(Thread.currentThread().getStackTrace()[2]);
        if (parser == null) {
            createInstance();
        }

        return parser;
    }

    /**
     * Parse raw buffer to object. Provide the raw packet as buffer, this
     * function will set the values into corresponding fields and will return
     * {@link MessageDTO}.
     * <pre>
     * {@code
     * byte[] receivedBuffer = receive();
     * MessageDTO messageDTO = chatParser.parse(receivedBuffer);
     *
     * int packetType = messageDTO.getPacketType();
     * String packetID = messageDTO.getPacketID();
     * long userId = messageDTO.getUserIdentity();
     * long friendId = messageDTO.getFriendIdentity();
     * String message = messageDTO.getMessage();
     * float latitude = messageDTO.getLatitude();
     * float longitude = messageDTO.getLongitude();
     * }
     * </pre>
     *
     * @param receivedBuffer Raw packet buffer
     * @return {@link MessageDTO}
     */
    public native MessageDTO parse(byte[] receivedBuffer);

    /**
     * Parse only basic header. Use this function if you need only header of the
     * packet which have <tt>PACKET_TYPE, USER_IDENTITY, FRIEND_IDENTITY</tt> at
     * header. Please don't call this function if it has other values at header.
     *
     * @param receivedBuffer Raw packet buffer
     * @return {@link MessageDTO}
     */
    public native MessageDTO parseHeader(byte[] receivedBuffer);

    /**
     * Parse {@link MessageDTO} to raw buffer. Pass an instance of
     * {@link MessageDTO} by setting necessary values. It is possible to use
     * only this function instead of using other make* functions.
     * <pre>
     * {@code
     * MessageDTO messageDTO = new MessageDTO();
     * messageDTO.setPacketType(Constants.CHAT_FRIEND);
     * messageDTO.setUserIdentity(userIdentity);
     * messageDTO.setFriendIdentity(friendIdentity);
     * messageDTO.setPacketID(packetID);
     * messageDTO.setMessageType(messageType);
     * messageDTO.setTimeout(timeout);
     * messageDTO.setLatitude(latitude);
     * messageDTO.setLongitude(longitude);
     * messageDTO.setMessage(message);
     * messageDTO.setMessageDate(messageDate);
     *
     * byte[] buffer = chatParser.parse(messageDTO);
     * send(buffer);
     * }
     * </pre>
     *
     * @param messageDTO {@link MessageDTO}
     * @return Raw packet buffer
     */
    public native byte[] parse(MessageDTO messageDTO);

    /**
     * Get the version of native library
     *
     * @return version of native library
     */
    public native String version();

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @param platform Device platform (code for Android, iPhone, Desktop ...)
     * @return Raw packet buffer
     */
    public byte[] makeChatRegisterPacket(long userIdentity, long friendIdentity, String packetID, int platform) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_REGISTER);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);
        messageDTO.setDevice(platform);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity UserIdentity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param onlineStatus Online status of user
     * @param onlineMood Online mood of user
     * @return Raw packet buffer
     */
    public byte[] makeChatFriendUnregisterPacket(long userIdentity, long friendIdentity, int onlineStatus, int onlineMood) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_FRIEND_UNREGISTERED);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setOnlineStatus(onlineStatus);
        messageDTO.setOnlineMood(onlineMood);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @param chatBindingPort Chat binding port for corresponding user to
     * corresponding chat server
     * @param serverDate Current date and time of chat server
     * @return Raw packet buffer
     */
    public byte[] makeChatRegisterConfirmationPacket(long friendIdentity, String packetID, int chatBindingPort, long serverDate) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_REGISTER_CONFIRMATION);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);
        messageDTO.setChatBindingPort(chatBindingPort);
        messageDTO.setServerDate(serverDate);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param onlineStatus Online status of user
     * @param onlineMood Online mood of user
     * @return Raw packet buffer
     */
    public byte[] makeChatGroupUnregisterPacket(long userIdentity, long groupID, int onlineStatus, int onlineMood) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_GROUP_UNREGISTER);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setOnlineStatus(onlineStatus);
        messageDTO.setOnlineMood(onlineMood);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @param messageType Type of message
     * @param timeout Time for this message. Timeout will be used for secret
     * chat. For normal chat the value will be 0(zero)
     * @param latitude Latitude of user
     * @param longitude Longitude of user
     * @param message Text message
     * @param messageDate Date and time of message
     * @return Raw packet buffer
     */
    public byte[] makeChatFriendPacket(long userIdentity, long friendIdentity, String packetID, int messageType, int timeout, float latitude, float longitude, String message, long messageDate) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_FRIEND);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);
        messageDTO.setMessageType(messageType);
        messageDTO.setTimeout(timeout);
        messageDTO.setLatitude(latitude);
        messageDTO.setLongitude(longitude);
        messageDTO.setMessage(message);
        messageDTO.setMessageDate(messageDate);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeChatDeliveredPacket(long userIdentity, long friendIdentity, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_DELIVERED);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeChatSeenPacket(long userIdentity, long friendIdentity, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_SEEN);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeChatSentPacket(long userIdentity, long friendIdentity, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_SENT);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @return Raw packet buffer
     */
    public byte[] makeChatTypingPacket(long userIdentity, long friendIdentity) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_TYPING);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @return Raw packet buffer
     */
    public byte[] makeChatIdlePacket(long userIdentity, long friendIdentity) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_IDEL);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @param platform Device platform (code for Android, iPhone, Desktop ...)
     * @return Raw packet buffer
     */
    public byte[] makeChatGroupRegisterPacket(long userIdentity, long groupID, String packetID, int platform) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_GROUP_REGISTER);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setDevice(platform);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @param chatBindingPort Chat binding port for corresponding user to
     * corresponding chat server
     * @param serverDate Current date and time of chat server
     * @return Raw packet buffer
     */
    public byte[] makeChatGroupRegisterConfirmationPacket(long groupID, String packetID, int chatBindingPort, long serverDate) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_GROUP_REG_CONFIRMATION);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);
        messageDTO.setChatBindingPort(chatBindingPort);
        messageDTO.setServerDate(serverDate);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @param fullName Full name of user. Maximum length is 127 byte
     * @param messageType Type of message
     * @param timeout Time for this message. Timeout will be used for secret
     * chat. For normal chat the value will be 0(zero)
     * @param latitude Latitude of user
     * @param longitude Longitude of user
     * @param message Text message
     * @param messageDate Date and time of message
     * @return Raw packet buffer
     */
    public byte[] makeChatGroupPacket(long userIdentity, long groupID, String packetID, String fullName, int messageType, int timeout, float latitude, float longitude, String message, long messageDate) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_GROUP);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);
        messageDTO.setFullName(fullName);
        messageDTO.setMessageType(messageType);
        messageDTO.setTimeout(timeout);
        messageDTO.setLatitude(latitude);
        messageDTO.setLongitude(longitude);
        messageDTO.setMessage(message);
        messageDTO.setMessageDate(messageDate);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeChatGroupDeliveredPacket(long userIdentity, long friendIdentity, long groupID, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_GROUP_DELIVERED);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeChatGroupSeenPacket(long userIdentity, long friendIdentity, long groupID, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_GROUP_SEEN);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeChatGroupSentPacket(long groupID, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_GROUP_SENT);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @return Raw packet buffer
     */
    public byte[] makeChatGroupTypingPacket(long userIdentity, long groupID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_GROUP_TYPING);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @return Raw packet buffer
     */
    public byte[] makeChatGroupIdlePacket(long userIdentity, long groupID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_GROUP_IDEL);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param packetID Packet ID for this packet
     * @param messageList List of messages as list of {@link MessageDTO}
     * @return Raw packet buffer
     */
    public byte[] makeChatFriendOfflinePacket(String packetID, ArrayList<MessageDTO> messageList) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_FRIEND_OFFLINE);
        messageDTO.setPacketID(packetID);
        messageDTO.setMessageList(messageList);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param packetID Packet ID for this packet
     * @param messageList List of messages as list of {@link MessageDTO}
     * @return Raw packet buffer
     */
    public byte[] makeChatGroupOfflinePacket(String packetID, ArrayList<MessageDTO> messageList) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_GROUP_OFFLINE);
        messageDTO.setPacketID(packetID);
        messageDTO.setMessageList(messageList);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeChatGetOfflinePacket(long userIdentity, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_GET_OFFLINE);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param packetID Packet ID for this packet
     * @param messageDate Date and time of message
     * @return Raw packet buffer
     */
    public byte[] makeChatOfflineConfirmationPacket(String packetID, long messageDate) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_OFFLINE_CONFIRMATION);
        messageDTO.setPacketID(packetID);
        messageDTO.setMessageDate(messageDate);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeFriendChatDeletePacket(long userIdentity, long friendIdentity, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.FRIEND_CHAT_DELETE);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeFriendChatDeleteConfirmationPacket(long userIdentity, long friendIdentity, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.FRIEND_CHAT_DELETE_CONFIRMATION);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeGroupChatDeletePacket(long userIdentity, long groupID, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GROUP_CHAT_DELETE);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeGroupChatDeleteConfirmationPacket(long userIdentity, long friendIdentity, long groupID, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GROUP_CHAT_DELETE_CONFIRMATION);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @param fullName Full name of user. Maximum length is 127 byte
     * @param friendDevice Platform or device of friend
     * @param friendOnlineStatus Online status of friend
     * @param friendAppType App type of friend
     * @param friendDeviceToken Device token of friend
     * @return Raw packet buffer
     */
    public byte[] makeFriendInformationPacket(long userIdentity, long friendIdentity, String packetID, String fullName, int friendDevice, int friendOnlineStatus, int friendAppType, String friendDeviceToken) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.FRIEND_INFORMATION);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);
        messageDTO.setFullName(fullName);
        messageDTO.setDevice(friendDevice);
        messageDTO.setOnlineStatus(friendOnlineStatus);
        messageDTO.setAppType(friendAppType);
        messageDTO.setDeviceToken(friendDeviceToken);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeFriendInformationConfirmationPacket(long friendIdentity, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.FRIEND_INFORMATION_CONFIRMATION);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @return Raw packet buffer
     */
    public byte[] makeFileTotalSequencePacket() {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.FILE_TOTAL_SEQUENCE);
        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @return Raw packet buffer
     */
    public byte[] makeFileTotalSequenceConfirmationPacket() {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.FILE_TOTAL_SEQUENCE_CONFIRMATION);
        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @return Raw packet buffer
     */
    public byte[] makeFileStreamSendPacket() {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.FILE_STREAM_SEND);
        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @return Raw packet buffer
     */
    public byte[] makeFileStreamSendConfirmationPacket() {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.FILE_STREAM_SEND_CONFIRMATION);
        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @param memberList List of members of corresponding group. All the variables of {@link MemberDTO } need to be set
     * @return Raw packet buffer
     */
    public byte[] makeGroupMembersPacket(long userIdentity, long groupID, String packetID, ArrayList<MemberDTO> memberList) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GROUP_MEMBERS);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);
        messageDTO.setMemberList(memberList);
        messageDTO.setNumberOfMembers(memberList.size());

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeGroupMembersConfirmationPacket(long groupID, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GROUP_MEMBERS_CONFIRMATION);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeGetGroupMembersPacket(long userIdentity, long groupID, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GET_GROUP_MEMBERS);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @param memberList List of members of corresponding group. Only the {@link MemberDTO#memberIdentity } need to set
     * @return Raw packet buffer
     */
    public byte[] makeGroupMemberRemoveLeavePacket(long userIdentity, long groupID, String packetID, ArrayList<MemberDTO> memberList) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GROUP_MEMBER_REMOVE_LEAVE);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);
        messageDTO.setMemberList(memberList);
        messageDTO.setNumberOfMembers(memberList.size());

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeGroupMemberRemoveLeaveConfirmationPacket(long groupID, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GROUP_MEMBER_REMOVE_LEAVE_CONFIRMATION);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeGroupDeletePacket(long userIdentity, long groupID, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GROUP_DELETE);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeGroupDeleteConfirmationPacket(long groupID, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GROUP_DELETE_CONFIRMATION);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @param packetIDs List of packet ids to include
     * @return Raw packet buffer
     */
    public byte[] makeMultipleFriendChatDeletePacket(long userIdentity, long friendIdentity, String packetID, ArrayList<String> packetIDs) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.MULTIPLE_FRIEND_CHAT_DELETE);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);
        messageDTO.setPacketIDs(packetIDs);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @param packetIDs List of packet ids to include
     * @return Raw packet buffer
     */
    public byte[] makeMultipleGroupChatDeletePacket(long userIdentity, long groupID, String packetID, ArrayList<String> packetIDs) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.MULTIPLE_GROUP_CHAT_DELETE);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);
        messageDTO.setPacketIDs(packetIDs);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @param messageType Type of message
     * @param timeout Time for this message. Timeout will be used for secret
     * chat. For normal chat the value will be 0(zero)
     * @param latitude Latitude of user
     * @param longitude Longitude of user
     * @param message Text message
     * @param messageDate Date and time of message
     * @return Raw packet buffer
     */
    public byte[] makeFriendChatEditPacket(long userIdentity, long friendIdentity, String packetID, int messageType, int timeout, float latitude, float longitude, String message, long messageDate) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.FRIEND_CHAT_EDIT);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);
        messageDTO.setMessageType(messageType);
        messageDTO.setTimeout(timeout);
        messageDTO.setLatitude(latitude);
        messageDTO.setLongitude(longitude);
        messageDTO.setMessage(message);
        messageDTO.setMessageDate(messageDate);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @param fullName Full name of user. Maximum length is 127 byte
     * @param messageType Type of message
     * @param timeout Time for this message. Timeout will be used for secret
     * chat. For normal chat the value will be 0(zero)
     * @param latitude Latitude of user
     * @param longitude Longitude of user
     * @param message Text message
     * @param messageDate Date and time of message
     * @return Raw packet buffer
     */
    public byte[] makeGroupChatEditPacket(long userIdentity, long groupID, String packetID, String fullName, int messageType, int timeout, float latitude, float longitude, String message, long messageDate) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GROUP_CHAT_EDIT);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);
        messageDTO.setFullName(fullName);
        messageDTO.setMessageType(messageType);
        messageDTO.setTimeout(timeout);
        messageDTO.setLatitude(latitude);
        messageDTO.setLongitude(longitude);
        messageDTO.setMessage(message);
        messageDTO.setMessageDate(messageDate);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @param messageList List of messages as list of {@link MessageDTO}
     * @return Raw packet buffer
     */
    public byte[] makeMultipleChatForFriendPacket(long userIdentity, long friendIdentity, String packetID, ArrayList<MessageDTO> messageList) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.MULTIPLE_CHAT_FOR_FRIEND);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);
        messageDTO.setMessageList(messageList);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @param totalNumberOfPackets Total number of packets
     * @param sequenceNumber Sequence number of this message
     * @param messageType Type of message
     * @param timeout Time for this message. Timeout will be used for secret
     * chat. For normal chat the value will be 0(zero)
     * @param latitude Latitude of user
     * @param longitude Longitude of user
     * @param message Text message
     * @param messageDate Date and time of message
     * @return Raw packet buffer
     */
    public byte[] makeBrockenChatForFriendPacket(long userIdentity, long friendIdentity, String packetID, int totalNumberOfPackets, int sequenceNumber, int messageType, int timeout, float latitude, float longitude, String message, long messageDate) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.BROCKEN_CHAT_FOR_FRIEND);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);
        messageDTO.setNumberOfMessage(totalNumberOfPackets);
        messageDTO.setSequenceNumber(sequenceNumber);
        messageDTO.setMessageType(messageType);
        messageDTO.setTimeout(timeout);
        messageDTO.setLatitude(latitude);
        messageDTO.setLongitude(longitude);
        messageDTO.setMessage(message);
        messageDTO.setMessageDate(messageDate);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @param totalNumberOfPackets Total number of packets
     * @param sequenceNumber Sequence number of this message
     * @param fullName Full name of user. Maximum length is 127 byte
     * @param messageType Type of message
     * @param timeout Time for this message. Timeout will be used for secret
     * chat. For normal chat the value will be 0(zero)
     * @param latitude Latitude of user
     * @param longitude Longitude of user
     * @param message Text message
     * @param messageDate Date and time of message
     * @return Raw packet buffer
     */
    public byte[] makeBrockenChatForGroupPacket(long userIdentity, long groupID, String packetID, int totalNumberOfPackets, int sequenceNumber, String fullName, int messageType, int timeout, float latitude, float longitude, String message, long messageDate) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.BROCKEN_CHAT_FOR_GROUP);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);
        messageDTO.setNumberOfMessage(totalNumberOfPackets);
        messageDTO.setSequenceNumber(sequenceNumber);
        messageDTO.setFullName(fullName);
        messageDTO.setMessageType(messageType);
        messageDTO.setTimeout(timeout);
        messageDTO.setLatitude(latitude);
        messageDTO.setLongitude(longitude);
        messageDTO.setMessage(message);
        messageDTO.setMessageDate(messageDate);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @param totalNumberOfPackets Total number of packets
     * @param sequenceNumber Sequence number of this message
     * @param messageType Type of message
     * @param timeout Time for this message. Timeout will be used for secret
     * chat. For normal chat the value will be 0(zero)
     * @param latitude Latitude of user
     * @param longitude Longitude of user
     * @param message Text message
     * @param messageDate Date and time of message
     * @return Raw packet buffer
     */
    public byte[] makeEditBrockenChatForFriendPacket(long userIdentity, long friendIdentity, String packetID, int totalNumberOfPackets, int sequenceNumber, int messageType, int timeout, float latitude, float longitude, String message, long messageDate) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.EDIT_BROCKEN_CHAT_FOR_FRIEND);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);
        messageDTO.setNumberOfMessage(totalNumberOfPackets);
        messageDTO.setSequenceNumber(sequenceNumber);
        messageDTO.setMessageType(messageType);
        messageDTO.setTimeout(timeout);
        messageDTO.setLatitude(latitude);
        messageDTO.setLongitude(longitude);
        messageDTO.setMessage(message);
        messageDTO.setMessageDate(messageDate);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @param totalNumberOfPackets Total number of packets
     * @param sequenceNumber Sequence number of this message
     * @param fullName Full name of user. Maximum length is 127 byte
     * @param messageType Type of message
     * @param timeout Time for this message. Timeout will be used for secret
     * chat. For normal chat the value will be 0(zero)
     * @param latitude Latitude of user
     * @param longitude Longitude of user
     * @param message Text message
     * @param messageDate Date and time of message
     * @return Raw packet buffer
     */
    public byte[] makeEditBrockenChatForGroupPacket(long userIdentity, long groupID, String packetID, int totalNumberOfPackets, int sequenceNumber, String fullName, int messageType, int timeout, float latitude, float longitude, String message, long messageDate) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.EDIT_BROCKEN_CHAT_FOR_GROUP);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);
        messageDTO.setNumberOfMessage(totalNumberOfPackets);
        messageDTO.setSequenceNumber(sequenceNumber);
        messageDTO.setFullName(fullName);
        messageDTO.setMessageType(messageType);
        messageDTO.setTimeout(timeout);
        messageDTO.setLatitude(latitude);
        messageDTO.setLongitude(longitude);
        messageDTO.setMessage(message);
        messageDTO.setMessageDate(messageDate);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @param fileTotalChunk Total number of chunk of file
     * @param totalNumberOfPackets Total number of packets
     * @param sequenceNumber Sequence number of this message
     * @param fileChunkList List of file chunk indices
     * @return Raw packet buffer
     */
    public byte[] makeChatFriendFileStreamRequestPacket(long userIdentity, long friendIdentity, String packetID, int fileTotalChunk, int totalNumberOfPackets, int sequenceNumber, ArrayList<FileChunk> fileChunkList) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_FRIEND_FILE_STREAM_REQUEST);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);
        messageDTO.setFileTotalChunk(fileTotalChunk);
        messageDTO.setNumberOfMembers(totalNumberOfPackets);
        messageDTO.setSequenceNumber(sequenceNumber);
        messageDTO.setFileChunkList(fileChunkList);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeChatFriendFileStreamRequestConfirmationPacket(long userIdentity, long friendIdentity, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_FRIEND_FILE_STREAM_REQUEST_CONFIRMATION);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @param fileChunkCurrentIndex Index of current file chunk
     * @param fileTotalChunk Total number of chunk of file
     * @param totalNumberOfPackets Total number of packets
     * @param sequenceNumber Sequence number of this message
     * @param fileContent File content
     * @return Raw packet buffer
     */
    public byte[] makeChatFriendFileStreamSendPacket(long userIdentity, long friendIdentity, String packetID, int fileChunkCurrentIndex, int fileTotalChunk, int totalNumberOfPackets, int sequenceNumber, String fileContent) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_FRIEND_FILE_STREAM_SEND);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);
        messageDTO.setFileChunkCurrentIndex(fileChunkCurrentIndex);
        messageDTO.setFileTotalChunk(fileTotalChunk);
        messageDTO.setNumberOfMessage(totalNumberOfPackets);
        messageDTO.setSequenceNumber(sequenceNumber);
        messageDTO.setFileContent(fileContent);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeChatFriendFileStreamSendConfirmationPacket(long userIdentity, long friendIdentity, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_FRIEND_FILE_STREAM_SEND_CONFIRMATION);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @param fileTotalChunk Total number of chunk of file
     * @param totalNumberOfPackets Total number of packets
     * @param sequenceNumber Sequence number of this message
     * @param fileChunkList List of file chunk indices
     * @return Raw packet buffer
     */
    public byte[] makeChatGroupFileStreamRequestPacket(long userIdentity, long friendIdentity, long groupID, String packetID, int fileTotalChunk, int totalNumberOfPackets, int sequenceNumber, ArrayList<FileChunk> fileChunkList) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_GROUP_FILE_STREAM_REQUEST);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);
        messageDTO.setFileTotalChunk(fileTotalChunk);
        messageDTO.setNumberOfMessage(totalNumberOfPackets);
        messageDTO.setSequenceNumber(sequenceNumber);
        messageDTO.setFileChunkList(fileChunkList);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeChatGroupFileStreamRequestConfirmationPacket(long userIdentity, long friendIdentity, long groupID, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_GROUP_FILE_STREAM_REQUEST_CONFIRMATION);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @param fileChunkCurrentIndex Index of current file chunk
     * @param fileTotalChunk Total number of chunk of file
     * @param totalNumberOfPackets Total number of packets
     * @param sequenceNumber Sequence number of this message
     * @param fileContent File content
     * @return Raw packet buffer
     */
    public byte[] makeChatGroupFileStreamSendPacket(long userIdentity, long friendIdentity, long groupID, String packetID, int fileChunkCurrentIndex, int fileTotalChunk, int totalNumberOfPackets, int sequenceNumber, String fileContent) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_GROUP_FILE_STREAM_SEND);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);
        messageDTO.setFileChunkCurrentIndex(fileChunkCurrentIndex);
        messageDTO.setFileTotalChunk(fileTotalChunk);
        messageDTO.setNumberOfMessage(totalNumberOfPackets);
        messageDTO.setSequenceNumber(sequenceNumber);
        messageDTO.setFileContent(fileContent);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeChatGroupFileStreamSendConfirmationPacket(long userIdentity, long friendIdentity, long groupID, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_GROUP_FILE_STREAM_SEND_CONFIRMATION);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param packetID Packet ID for this packet
     * @param packetIDs List of packet ids to include
     * @return Raw packet buffer
     */
    public byte[] makeChatFriendOfflineConfirmationPacket(long userIdentity, String packetID, ArrayList<String> packetIDs) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_FRIEND_OFFLINE_CONFIRMATION);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setPacketID(packetID);
        messageDTO.setPacketIDs(packetIDs);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity User identity of corresponding user
     * @param packetID Packet ID for this packet
     * @param messageDate Date and time of message
     * @param packetIDs List of packet ids to include
     * @return Raw packet buffer
     */
    public byte[] makeChatGroupOfflineConfirmationPacket(long userIdentity, String packetID, long messageDate, ArrayList<String> packetIDs) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_GROUP_OFFLINE_CONFIRMATION);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setPacketID(packetID);
        messageDTO.setMessageDate(messageDate);
        messageDTO.setPacketIDs(packetIDs);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     * 
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @param addToBlock Add to block list db
     * @return Raw packet buffer
     */
    public byte[] makeChatFriendBlockPacket(long userIdentity, long friendIdentity, String packetID, boolean addToBlock) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_FRIEND_BLOCK);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);
        messageDTO.setIsAddToBlock(addToBlock);
        
        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     * 
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeChatFriendUnblockPacket(long userIdentity, long friendIdentity, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_FRIEND_UNBLOCK);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);
        
        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     * 
     * @param userIdentity User identity of corresponding user
     * @param friendIdentity Friend Identity of corresponding user
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeChatBlockUnblockConfirmationPacket(long userIdentity, long friendIdentity, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.CHAT_BLOCK_UNBLOCK_CONFIRMATION);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setFriendIdentity(friendIdentity);
        messageDTO.setPacketID(packetID);
        
        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity UserIdentity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @param memberList List of members of corresponding group. {@link MemberDTO#memberIdentity }, {@link MemberDTO#fullName }, {@link MemberDTO#status } need to be set. {@code userIdentity } will be used as {@link MemberDTO#addedBy }
     * @return Raw packet buffer
     */
    public byte[] makeGroupMemberAdd(long userIdentity, long groupID, String packetID, ArrayList<MemberDTO> memberList) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GROUP_MEMBER_ADD);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);
        messageDTO.setMemberList(memberList);
        messageDTO.setNumberOfMembers(memberList.size());

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeGroupMemberAddConfirmation(long groupID, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GROUP_MEMBER_ADD_CONFIRMATION);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity UserIdentity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @param groupName Name of the group
     * @param groupUrl Group picture URL
     * @param totalGroupMembers Total number of member in group
     * @param isUpdate Is update (or set)
     * @return Raw packet buffer
     */
    public byte[] makeGroupInformation(long userIdentity, long groupID, String packetID, String groupName, String groupUrl, int totalGroupMembers, boolean isUpdate) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GROUP_INFORMATION);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);
        messageDTO.setGroupName(groupName);
        messageDTO.setGroupUrl(groupUrl);
        messageDTO.setTotalGroupMembers(totalGroupMembers);
        messageDTO.setIsUpdateGroupInformation(isUpdate);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity UserIdentity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeGetGroupInformation(long userIdentity, long groupID, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GET_GROUP_INFORMATION);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @param isUpdate Is update (or set)
     * @return Raw packet buffer
     */
    public byte[] makeGroupInformationConfirmation(long groupID, String packetID, boolean isUpdate) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GROUP_INFORMATION_CONFIRMATION);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);
        messageDTO.setIsUpdateGroupInformation(isUpdate);

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param userIdentity UserIdentity of corresponding user
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @param memberList List of members of corresponding group. Only {@link MemberDTO#memberIdentity } and {@link MemberDTO#status } will be used here
     * @return Raw packet buffer
     */
    public byte[] makeGroupMemberStatusChange(long userIdentity, long groupID, String packetID, ArrayList<MemberDTO> memberList) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GROUP_MEMBER_STATUS_CHANGE);
        messageDTO.setUserIdentity(userIdentity);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);
        messageDTO.setMemberList(memberList);
        messageDTO.setNumberOfMembers(memberList.size());

        return ChatParser.getInstance().parse(messageDTO);
    }

    /**
     *
     * @param groupID Group id or tag id of chat group
     * @param packetID Packet ID for this packet
     * @return Raw packet buffer
     */
    public byte[] makeGroupMemberStatusChangeConfirmation(long groupID, String packetID) {
        MessageDTO messageDTO = new MessageDTO();
        messageDTO.setPacketType(Constants.GROUP_MEMBER_STATUS_CHANGE_CONFIRMATION);
        messageDTO.setGroupId(groupID);
        messageDTO.setPacketID(packetID);

        return ChatParser.getInstance().parse(messageDTO);
    }

    static {
        System.loadLibrary("chatparser");
    }

    /*
     public static void main(String[] args) {
     System.out.println("JavaChatParser");
     System.out.println(System.getProperty("java.library.path"));
     System.out.println(ChatParser.getInstance().version());
     byte[] data = new byte[]{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 5, 21, 75, 84, 83, 120, 108, 115, 88, 71, 49, 52, 51, 55, 54, 53, 49, 57, 48, 55, 48, 56, 50, 1};

     //System.out.println((new ChatParser()).parse(data).getPacketID());
     MessageDTO messageDTO = new MessageDTO();
     //        messageDTO.setPacketType(3);
     messageDTO.setUserIdentity(5);
     messageDTO.setFriendIdentity(6);
     messageDTO.setPacketID("abcd");
     //        messageDTO.setChatBindingPort(15132);
     //        messageDTO.setServerDate(1437915204708L);
     //        messageDTO.setFullName(null);

     MessageDTO m1 = new MessageDTO();
     m1.setPacketType(5);
     m1.setUserIdentity(7);
     m1.setFriendIdentity(8);
     m1.setMessageType(3);
     m1.setMessageDate(5L);
     m1.setPacketID("inner1");
     m1.setMessage("inner message 1");

     MessageDTO m2 = new MessageDTO();
     m2.setPacketType(5);
     m2.setUserIdentity(8);
     m2.setFriendIdentity(10);
     m2.setMessageType(4);
     m2.setMessageDate(4L);
     m2.setPacketID("inner2");
     m2.setMessage("inner message 2");

     ArrayList<MessageDTO> messageList = new ArrayList<MessageDTO>();
     messageList.add(m1);
     messageList.add(m2);

     messageDTO.setPacketType(45);
     messageDTO.setMessageList(messageList);
     messageDTO.setNumberOfMessage(messageList.size());

     ChatParser parser = ChatParser.getInstance();
     byte[] d = parser.parse(messageDTO);
     System.out.println(Arrays.toString(d));

     MessageDTO parsedMessage = parser.parse(d);
     MessageDTO pm1 = parsedMessage.getMessageList().get(0);
     MessageDTO pm2 = parsedMessage.getMessageList().get(1);
     System.out.println(pm1.getPacketType() + " " + pm1.getUserIdentity() + " " + pm1.getFriendIdentity() + " " + pm1.getPacketID() + " " + pm1.getMessage());
     System.out.println(pm2.getPacketType() + " " + pm2.getUserIdentity() + " " + pm2.getFriendIdentity() + " " + pm2.getPacketID() + " " + pm2.getMessage());

     byte[] header = new byte[]{6, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 10};
     MessageDTO messageHeader = parser.parseHeader(header);
     System.out.println(messageHeader.getPacketType() + " " + messageHeader.getUserIdentity() + " " + messageHeader.getFriendIdentity());
     }
     */
}
