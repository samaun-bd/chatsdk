/*
 * File:   newsimpletest.cpp
 * Author: dipal
 *
 * Created on Aug 24, 2015, 4:22:27 PM
 */

#include <stdlib.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <time.h>
#include <ctime>
#include "../src/DuplicateChecker.h"
#include "../src/ChatEvent.h"
#include "../src/HashAlgorithm.h"
#include "../src/Chat.h"
#include "../src/IChatEventHandler.h"
#include "../src/Logger.h"
#include "../src/InternetChecker.h"
#include "../src/DataEncryption.h"

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif
/*
 * Simple C++ Test Suite
 */

const unsigned long long kNum_100nsec_1582_1970 = 0x01b21dd213814000;
const unsigned long long kMax_node = 0xffffffffffff; // 48-bits, all 1s.
const uint16_t kMax_clock_seq = 0x3fff; // 14-bits, all 1s.

long long fileId;

long long chat_media_friend_id, chat_media_group_id;
std::string chat_media_manifest_url;
std::string chat_media_file_name;
int chat_media_msg_type;
std::string chunk_transfer_packet_id;


//class ChatEventHandler;
//class ChatWrapper{
//public:
//    
//    static std::string pagingState;
//    static ChatEventHandler eventHandler;
//    ChatWrapper(){
////        chat = new Chat(2110010822, "noman", "38.127.68.55", 1200, "38.127.68.52", 1500, 2, "aa", 134, 0);
////        eventHandler = new ChatEventHandler();
////        chat.registerEventHandler(eventHandler);
//        pagingState = nullptr;
//    }
//    static Chat& getInstance()
//    {
//        static Chat chat(1, "Towhid", "38.127.68.55", 1200, "38.127.68.52", 1500, 2, "aaa", 134, 0);
//        return chat;
//    }
//};

class ChatEventHandler : public imsdk::IChatEventHandler {
public:

    ChatEventHandler() {

    }

    ~ChatEventHandler() {

    }

    virtual void onEventHandlerAttached() {

    }

    virtual void onEventHandlerDetached() {

    }

    void onFriendChatReceived(long long senderId, long long receiverId, const std::string &packetId, int messageType, int secretTimeout, const std::string &message, long long messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser) {
        std::cout << "Chat from " << senderId << " :" << message << " fromAnonymous:" << fromAnonymousUser << " packetId: " << packetId << std::endl;
        time_t myTime = (time_t)(messageDate / 1000);
        std::cout << ctime(&myTime) << std::endl;
        //time_t myTime = (time_t)messageDate;
        //        char buffer[80];
        //        struct tm * timeinfo;
        //        time_t rawTime = std::chrono::system_clock::to_time_t(messageDate);;
        //        timeinfo = localtime (&rawTime);
        //        strftime (buffer,80,"time: %I:%M%p.",timeinfo);
        //        
        //        puts(buffer);
        //double year = messageDate/(1000*60*60*24*365)+1970;
        if (messageType == imsdk::MessageType::IMAGE_FILE_FROM_GALLERY){
            std::cout << "IMAGE_FILE_FROM_GALLERY received" << std::endl;
            chat_media_manifest_url = message;
            chat_media_msg_type = imsdk::MessageType::IMAGE_FILE_FROM_GALLERY;
            chat_media_friend_id = senderId;
            chunk_transfer_packet_id = packetId;
            //call 64 downloadChatMedia next
        }
        else if (messageType == imsdk::MessageType::AUDIO_FILE){
            std::cout << "AUDIO_FILE received" << std::endl;
            chat_media_manifest_url = message;
            chat_media_msg_type = imsdk::MessageType::AUDIO_FILE;
            chat_media_friend_id = senderId;
            chunk_transfer_packet_id = packetId;
            //call 64 downloadChatMedia next
        }
        else if (messageType == imsdk::MessageType::VIDEO_FILE){
            std::cout << "VIDEO_FILE received" << std::endl;
            chat_media_manifest_url = message;
            chat_media_msg_type = imsdk::MessageType::VIDEO_FILE;
            chat_media_friend_id = senderId;
            chunk_transfer_packet_id = packetId;
            //call 64 downloadChatMedia next
        }
        else if (messageType == imsdk::MessageType::IMAGE_FILE_FROM_CAMERA){
            std::cout << "IMAGE_FILE_FROM_CAMERA received" << std::endl;
            chat_media_manifest_url = message;
            chat_media_msg_type = imsdk::MessageType::IMAGE_FILE_FROM_GALLERY;
            chat_media_friend_id = senderId;
            chunk_transfer_packet_id = packetId;
            //call 64 downloadChatMedia next
        }
        else if (messageType == imsdk::MessageType::CALL_LOG_MESSAGE)
        {
            std::cout << " CALL_LOG_MESSAGE received from: " << senderId << std::endl;
        }
    }

    void onFriendChatDelivered(UserIdentity userId, UserIdentity friendid, const std::string &packetId, bool fromAnonymousUser, bool isEdited, bool fromOnline) {
        std::cout << "Chat delivered to :" << friendid << " ->:" << packetId << std::endl;
    }

    void onFriendChatSent(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool fromAnonymousUser) {
        std::cout << "Sent to offline server :" << packetId << std::endl;
    }

    void onFriendChatFailedToSend(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool fromAnonymousUser) {
        std::cout << "Failed to send " << packetId << std::endl;
    }

    void onFriendChatSeen(UserIdentity userId, long long friendId, const std::vector<imsdk::SeenPacketDTO> &seenPacketList, bool fromAnonymousUser) {
        std::cout << "Chat seen by: " << friendId << std::endl;
    }

    void onFriendChatSeenConfirmed(UserIdentity userId, long long friendid, std::vector<imsdk::SeenPacketDTO> &packetId, bool fromAnonymousUser) {
        for (int i = 0; i < packetId.size(); i++)
        {
            std::cout << "Chat seen confirmation sent from: " << friendid << " " << packetId[i].getPacketID() << std::endl;
        }
    }

    void onFriendChatTyping(UserIdentity userId, long long friendId, bool fromAnonymousUser) {
        std::cout << "Typing friend :" << friendId << std::endl;
    }

    void onFriendChatIdle(long long friendId, bool fromAnonymousUser) {
        std::cout << "Idle friend :" << friendId << std::endl;
    }

    void onFriendChatEdited(long long senderId, long long receiverId, const std::string &packetId, int messageType, int secretTimeout, const std::string &message, long long messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser) {
        std::cout << "Chat Edited from " << senderId << " pid:" << packetId << " :" << message << " packetId: " << packetId << std::endl;
    }

    void onFriendChatDeleted(UserIdentity senderId, UserIdentity friendid, const std::vector<std::string> &packetIds, bool fromAnonymousUser) {
        std::cout << "On Friend Chat Deleted from friendId " << friendid << "NOP:" << packetIds.size() << std::endl;
        for (int i = 0; i < packetIds.size(); i++)
        {
            //std::cout << "   Friend chat deleted sender "<<senderId <<" ;friendId:" << friendid << " packetid:" << packetIds[i] << " fromAnonymous: "<<fromAnonymousUser << std::endl;
        }
    }

    void onFriendChatDeleteRequestStatus(UserIdentity userId, UserIdentity  friendId, const std::string &packetId, const std::vector<std::string> &packetIds, bool fromAnonymousUser, bool requestStatus, int deleteType) {
        std::cout << "Friend chat deleted request status received  for " << friendId << std::endl;
        std::cout << "packetId:" << packetId << std::endl;
        for (int i = 0; i < packetIds.size(); i++) {
            std::cout << packetIds[i] << std::endl;
        }
        if (requestStatus) {
            std::cout << "request status: SUCCESS" << std::endl;
        }
        else {
            std::cout << "request status: FAILED" << std::endl;
        }
    }

    void onBlocked(UserIdentity blockerId, UserIdentity blockedId, long long blockUnblockDate, bool addToBlock) {
        std::cout << "Blocked by " << blockerId << " Blocked ID: " << blockedId << " block unblock date: " << blockUnblockDate << " addToBlock:" << addToBlock << std::endl;
    }

    void onUnblocked(UserIdentity blockerId, UserIdentity blockedId, long long blockUnblockDate) {
        std::cout << "Unblocked by" << blockerId << std::endl;
    }

    void onBlockUnblockRequestStatus(UserIdentity userId, UserIdentity friendid, const std::string &packetId, long long blockUnblockDate, bool status, bool isBlockRequest) {
        std::cout << "Block/unblock confirmed of " << friendid << std::endl;
    }

    void onGroupChatSent(GroupIdentity groupId, const std::string &packetId, bool isEdited) {
        std::cout << "Group chat sent to group " << groupId << " ;packetId: " << packetId << std::endl;
    }

    void onGroupChatReceived(long long friendId, long long groupId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, bool fromOnline) {
        std::cout << "Group chat received from " << friendId << " of group " << groupId << " :" << message << std::endl;
        std::cout << "packetId: " << packetId << std::endl << std::endl;
        if (messageType == imsdk::MessageType::IMAGE_FILE_FROM_GALLERY){
            std::cout << "IMAGE_FILE_FROM_GALLERY received" << std::endl;
            chat_media_manifest_url = message;
            chat_media_msg_type = imsdk::MessageType::IMAGE_FILE_FROM_GALLERY;
            chat_media_friend_id = friendId;
            chat_media_group_id = groupId;
            chunk_transfer_packet_id = packetId;
            //call 68 downloadGroupChatMedia next
        }
        else if (messageType == imsdk::MessageType::AUDIO_FILE){
            std::cout << "AUDIO_FILE received" << std::endl;
            chat_media_manifest_url = message;
            chat_media_msg_type = imsdk::MessageType::AUDIO_FILE;
            chat_media_friend_id = friendId;
            chat_media_group_id = groupId;
            chunk_transfer_packet_id = packetId;
            //call 68 downloadGroupChatMedia next
        }
        else if (messageType == imsdk::MessageType::VIDEO_FILE){
            std::cout << "VIDEO_FILE received" << std::endl;
            chat_media_manifest_url = message;
            chat_media_msg_type = imsdk::MessageType::VIDEO_FILE;
            chat_media_group_id = groupId;
            chat_media_friend_id = friendId;
            chunk_transfer_packet_id = packetId;
            //call 68 downloadGroupChatMedia next
        }
        else if (messageType == imsdk::MessageType::IMAGE_FILE_FROM_CAMERA){
            std::cout << "IMAGE_FILE_FROM_CAMERA received" << std::endl;
            chat_media_manifest_url = message;
            chat_media_msg_type = imsdk::MessageType::IMAGE_FILE_FROM_GALLERY;
            chat_media_group_id = groupId;
            chat_media_friend_id = friendId;
            chunk_transfer_packet_id = packetId;
            //call 68 downloadGroupChatMedia next
        }
    }

    void onGroupChatEdited(long long friendId, long long groupId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, bool fromOnline) {
        std::cout << "Group Chat Edited from " << friendId << " pid:" << packetId << " :" << message << std::endl;
    }

    void onGroupChatDeleted(long long friendid, long long groupid, const std::vector<std::string> &packetId) {
        std::cout << "Group chat deleted by friend: " << friendid << " groupId: " << groupid << " pid:" << packetId[0] << std::endl;
        std::cout << "Number of deleted packets: " << packetId.size() << std::endl;
    }

    void onGroupChatDeleteRequestStatus(long long groupid, const std::string &packetId, const std::vector<std::string> &packetIds, bool requestStatus) {
        std::cout << "Group chat deleted request status received  for group" << groupid << std::endl;
        std::cout << "packetId:" << packetId << std::endl;
        for (int i = 0; i < packetIds.size(); i++) {
            std::cout << packetIds[i] << std::endl;
        }
        if (requestStatus) {
            std::cout << "request status: SUCCESS" << std::endl;
        }
        else {
            std::cout << "request status: FAILED" << std::endl;
        }
    }

    void onGroupChatDelivered(long long friendId, long long groupId, const std::string &packetId) {
        std::cout << "Group chat delivered to " << friendId << " of " << groupId << " ;PacketId: " << packetId << std::endl;
    }

    void onGroupChatSeen(long long groupId, const std::vector<std::string> &packetIds) {
        std::cout << "Group chat seen for group " << groupId << std::endl;
        std::cout << "Seen Packet IDs:" << std::endl;
        for (int i = 0; i < packetIds.size(); i++){
            std::cout << packetIds[i] << std::endl;
        }
    }

    void onGroupChatTyping(long long friendId, long long groupId) {
        std::cout << "Group typing friend " << friendId << " at group " << groupId << std::endl;
    }

    void onGroupChatIdle(long long friendId, long long groupId) {
        std::cout << "Group idle from " << friendId << " of group " << groupId << std::endl;
    }
	//(GroupIdentity groupId, const std::string &packetId, bool status, const std::vector<MemberDTO> &memberList, bool isHide)
    void onGroupMemberRemoveLeaveRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::vector<imsdk::MemberDTO> &memberList, bool isHide) {
        for (int i = 0; i < memberList.size(); i++)
        {
            std::cout << "removed members from the group: " << memberList[i].getMemberIdentity() << std::endl;
        }
    }

    void onGroupMemberAddRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::vector<imsdk::MemberDTO> &memberList) {
        //        for(int i=0;i<memberList.size();i++)
        //        {
        //            std::cout<<"added group member: "<<i<<" member id: "<<memberList[i]<<std::endl;
        //        }
        std::cout << "Group member add request sent with packetId: " << packetId << std::endl;
    }

    void onGroupMemberStatusChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::vector<imsdk::MemberDTO> &memberList) {
        std::cout << "Group member type changed sent, groupId: " << groupId << " ;packetId: " << packetId << std::endl;
    }

	//(UserIdentity friendid, GroupIdentity groupid, const std::vector<UserIdentity> &memberList, const std::string &packetId, bool isHide)
    void onGroupMemberRemovedOrLeft(UserIdentity friendId, GroupIdentity groupId, const std::vector<UserIdentity> &memberList, const std::string &packetId, bool isHide) {
        for (int i = 0; i < memberList.size(); i++)
        {
            std::cout << "Member removed or left by " << friendId << " from " << groupId << " memberId: " << memberList[i] << std::endl;
        }
    }

    void onGroupMemberAdded(long long friendId, long long groupId, const std::vector<imsdk::MemberDTO> &memberList, const std::string &packetId) {
        for (int i = 0; i < memberList.size(); i++)
        {
            std::cout << "UTID " << memberList[i].getMemberIdentity() << " ringID: " << memberList[i].getRingId() << "; added by " << friendId << " of group " << groupId << std::endl;
        }
    }

    void onGroupMemberStatusChanged(long long senderId, long long groupId, const std::vector<imsdk::MemberDTO> &memberList, const std::string &packetId) {
        std::cout << "Group member type changed of senderid: " << senderId << " ;groupId: " << groupId << std::endl;
        for (int i = 0; i < memberList.size(); i++){
            std::cout << "Member name: " << memberList[i].getFullName() << " current status: " << memberList[i].getStatus() << std::endl;
        }
    }

    void onGroupChatFailedToSend(long long groupId, const std::string &packetId) {
        std::cout << "Group chat failed to send" << std::endl;
    }

    void shouldCheckFriendPresence(UserIdentity userId, long long friendId, bool fromAnonymousUser, int profileType) {
        std::cout << "Should check friend presence for " << friendId << " profile type: " << profileType << std::endl;
        //        ChatWrapper::getInstance().registerFriendChat(friendId, "38.127.68.55", 1500, 3, "12654654", 3, 2, 2, 0);
    }

    void shouldCheckServerAddressForFriend(UserIdentity userId, long long friendId, bool fromAnonymousUser) {
        std::cout << "Should check server address " << friendId << std::endl;
        //        ChatWrapper::getInstance().registerFriendChat(2, "38.127.68.55", 1500, 3, "12654654", 3, 2, 2, 0);
    }

    void shouldCheckServerAddressForGroup(long long groupId) {
        std::cout << "Should check server address for group: " << groupId << std::endl;
    }

    void shouldCheckOfflineServerAddress() {
        std::cout << "should Check Offline Server Address" << std::endl;
    }

    void onFriendHistoryMessageReceived(UserIdentity userId, UserIdentity friendId, const std::vector<imsdk::SDKMessageDTO> &friendHistoryMessageList, int direction) {
        std::cout << "Friend history message list size: " << friendHistoryMessageList.size() << std::endl;
        for (int i = 0; i < friendHistoryMessageList.size(); i++){
            std::cout << "sender: " << friendHistoryMessageList[i].getSenderId() << " ;receiver: " << friendHistoryMessageList[i].getReceiverId() << " ;packetID: " << friendHistoryMessageList[i].getPacketId() << " ;message: " << friendHistoryMessageList[i].getMessage() << std::endl;
        }
    }

    void onFriendMessagesStatusReceived(UserIdentity userId, UserIdentity friendId, const std::vector<imsdk::FriendMessageStatusDTO> &messageList) {
        std::cout << "Friend message status received of friends: " << std::endl;
        const std::string packetId;
        for (int i = 0; i < messageList.size(); i++){
            //packetId = messageList[i].getPacketId();
            std::cout << "packetId: " << messageList[i].getPacketId() << " ;Message status:" << messageList[i].getMessageStatus() << std::endl;
        }
    }

    void onFriendHistoryCompleted(UserIdentity userId, UserIdentity friendId, int direction){

    }

    void onGroupHistoryMessageReceived(GroupIdentity groupId, const std::vector<imsdk::SDKMessageDTO> &groupHistoryMessageList, int direction) {
        std::cout << "Group history message of group: " << groupId << " list size: " << groupHistoryMessageList.size() << std::endl;
        for (int i = 0; i < groupHistoryMessageList.size(); i++){
            std::cout << "sender: " << groupHistoryMessageList[i].getSenderId() << " ;message: " << groupHistoryMessageList[i].getMessage() << std::endl;
            std::cout << groupHistoryMessageList[i].getPacketId() << std::endl;
        }
    }

    void onGroupHistoryCompleted(GroupIdentity groupId, int direction){

    }

    void onGroupInformationWithMembersReceived(long long groupId, const std::string &groupName, const std::string &groupUrl, const std::vector<imsdk::MemberDTO> &memberList) {
        std::cout << "Group info: groupId-> " << groupId << " ;groupName->" << groupName << " ;groupUrl->" << groupUrl << " ;memberList:" << std::endl;
        for (int i = 0; i < memberList.size(); i++){
            std::cout << "UTID: " << memberList[i].getMemberIdentity() << " ringId: " << memberList[i].getRingId() << " ;full name:" << memberList[i].getFullName() << " ;STATUS:" << memberList[i].getStatus() << std::endl;
        }
    }

    void onGroupInformationActivityReceived(const std::vector<imsdk::GroupActivityDTO> &groupActivityList) {

        for (int i = 0; i < groupActivityList.size(); i++){
            std::cout << "Member id: " << groupActivityList[i].getMemberIdentity() << " ringId: " << groupActivityList[i].getRingId() << " ;activity type: " << groupActivityList[i].getActivityType() << " string: " << groupActivityList[i].getGroupNameOrUrlString() << std::endl;
        }
    }

    void onGroupInformationActivityFromHistoryMessageReceived(GroupIdentity groupId, const std::vector<imsdk::GroupActivityDTO> &groupActivityList, int direction) {
        std::cout << "onGroupInformationActivityFromHistoryMessageReceived, count: " << groupActivityList.size() << std::endl;
    }

    void onMyGroupListReceived(const std::vector<imsdk::GroupDTO> &myGroupList) {
        std::cout << "Group list received: " << std::endl;
        for (int i = 0; i < myGroupList.size(); i++){
            std::cout << myGroupList[i].getGroupId() << std::endl;
        }
    }

    void onGroupCreated(GroupIdentity groupId, const std::string &packetId, bool status) {
        std::cout << "Group created with id: " << groupId << " ;requestStatus: " << status << " ;packetId: " << packetId << std::endl;
    }

    void onGroupInformationChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status) {

    }

    void onGroupNameChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::string &groupName){

    }

    void onGroupUrlChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::string &groupUrl){

    }

    void onGroupInformationWithMembersRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status){

    }

    void onGroupNameChanged(const std::string &packetId, UserIdentity friendid, GroupIdentity groupid, const std::string &groupName) {
        std::cout << "group name changed of group: " << groupid << " ;by member: " << friendid << " ;new name: " << groupName << std::endl;
    }

    void onGroupUrlChanged(const std::string &packetId, UserIdentity friendid, GroupIdentity groupid, const std::string &groupUrl) {
        std::cout << "group url changed of group: " << groupid << " ;by member: " << friendid << " ;new url: " << groupUrl << std::endl;
    }

    void onFriendChatRegisterSuccess(UserIdentity userId, UserIdentity friendId, long long serverDate, const std::string &packetId, bool fromAnonymousUser) {
        std::cout << "Register Success with " << friendId << " at server time: " << serverDate << " fromAnonymous: " << fromAnonymousUser << std::endl;
    }

    void onFriendChatRegisterFailure(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool fromAnonymousUser) {
        std::cout << "Register Failure with " << friendId << std::endl;
    }

    void onFriendRegistrationExpired(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser) {
        std::cout << "Friend registration expired with " << friendId << std::endl;
    }

    void onFriendUnregistered(UserIdentity userId, UserIdentity friendId, int onlineStatus, int onlineMood, bool fromAnonymousUser, int profileType) {
        std::cout << "Friend unregistered friendid " << friendId << " profile type: " << profileType << std::endl;
        //        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        //        ChatWrapper::getInstance().registerFriendChat(1, "38.127.68.55", 1500, 3, "12654654", 3, 2, 2, 0);
    }

    void onGroupChatRegisterSuccess(GroupIdentity groupId, long long serverDate, const std::string &packetId) {
        std::cout << "Register group success with group " << groupId << " at server time: " << serverDate << std::endl;
    }

    virtual void onGroupChatRegisterFailure(GroupIdentity groupId, const std::string &packetId) {
        std::cout << "Register group failure with group " << groupId << std::endl;
    }

    void onGroupRegistrationExpired(GroupIdentity groupId, long long lastActivityTime) {
        std::cout << "Group registration expired with " << groupId << std::endl;
    }

    void onFriendHistoryMessageRequestStatus(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool status){

    }

    void onGroupHistoryMessageRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status){

    }

    void onFriendGetChatMessageReceived(UserIdentity userId, UserIdentity friendId, const imsdk::SDKMessageDTO& friendChatMessageDTO){
        std::cout << "Friend Get Chat Message Received for friendId: " << friendId << std::endl;
        std::cout << "Msg SenderId: " << friendChatMessageDTO.getSenderId() << std::endl
            << "Msg ReceiverId: " << friendChatMessageDTO.getReceiverId() << std::endl
            << "Message: " << friendChatMessageDTO.getMessage() << std::endl
            << "MessageDate: " << friendChatMessageDTO.getMessageDate() << std::endl
            << "PacketId: " << friendChatMessageDTO.getPacketId() << std::endl;
        if (friendChatMessageDTO.getIsEdited()) std::cout << "MESSAGE EDITED: TRUE" << std::endl;
        else std::cout << "MESSAGE EDITED: FALSE" << std::endl;
    }

    void onGroupGetChatMessageReceived(GroupIdentity groupId, const imsdk::SDKMessageDTO& groupChatMessageDTO){
        std::cout << "Group Get Chat Message Received for groupId: " << groupId << std::endl;
        std::cout << groupChatMessageDTO.getSenderId() << std::endl
            << groupChatMessageDTO.getMessage() << std::endl
            << groupChatMessageDTO.getMessageDate() << std::endl
            << groupChatMessageDTO.getPacketId() << std::endl;
        if (groupChatMessageDTO.getIsEdited()) std::cout << "MESSAGE EDITED - TRUE" << std::endl;
        else std::cout << "MESSAGE EDITED - FALSE" << std::endl;
    }

    void onGroupChatSeenRequestStatus(GroupIdentity groupid, const std::vector<std::string> &packetIds, bool status)
    {

    }
	
	//void onFriendChatConversationListReceived(UserIdentity userId, const std::vector<SDKMessageDTO> &conversationList, bool isFromSynced)
    void onFriendChatConversationListReceived(UserIdentity userId, const std::vector<imsdk::SDKMessageDTO> &conversationList, bool isFromSynced)
    {
        for (auto message : conversationList)
        {
            std::cout << "MessageType: " << message.getMessageType() << " ;SenderId: " << message.getSenderId() << " ;receiverId: " << message.getReceiverId() << " ;packetId: " << message.getPacketId() << " ;message: " << message.getMessage() << " messageDate: " << message.getMessageDate() << std::endl;
        }
    }

    void onGroupChatMessageSeenListRequestStatus(GroupIdentity groupId, const std::string &requestPacketId, const std::string &messagePacketId, bool status){

    }
	
	//(const std::vector<SDKMessageDTO> &conversationList, bool isFromSynced)
    void onGroupChatConversationListReceived(const std::vector<imsdk::SDKMessageDTO> &conversationList, bool isFromSync)
    {
        for (auto message : conversationList)
        {
            std::cout << "MessageType: " << message.getMessageType() << " ;SenderId: " << message.getSenderId() << " ;groupId: " << message.getGroupId() << " ;packetId: " << message.getPacketId() << " ;message: " << message.getMessage() << " messageDate: " << message.getMessageDate() << std::endl;
        }
    }

    void onChatConversationListRequestStatus(UserIdentity userId, long long friendOrGroupId, const std::string &packetId, bool status)
    {
        std::cout << "onChatConversationListRequestStatus: " << status << std::endl;
    }

    void onChatConversationListCompleted(UserIdentity userId, bool isFromSync){
        std::cout << "Conversation list completed............" << std::endl;
    }

    void onConversationListDeleteRequestStatus(UserIdentity userId, const std::string &packetId, bool status){
        std::cout << "onConversationListDeleteRequestStatus, packetId: " << packetId << " ;status: " << status;
    }

    void onConversationListMarkAsSeenRequestStatus(UserIdentity userId, const std::string &packetId, bool status){
        std::cout << "onConversationListMarkAsSeenRequestStatus, packetId: " << packetId << " ;status: " << status;
    }

    void onPublicRoomChatRegisterSuccess(RoomIdentity &roomId, const std::string &packetId, int numberOfMembers, long long anonymousId){
        std::cout << "Room Chat Reg Success for Room Id: " << roomId << " numberOfMembers " << numberOfMembers << " ;anonymousId: " << anonymousId << std::endl;
    }

    void onPublicRoomChatRegisterFailure(RoomIdentity &roomId, const std::string &packetId){
        std::cout << "Room Chat Reg failure for Room Id: " << roomId << std::endl;
    }

    void onPublicRoomChatRegistrationExpired(RoomIdentity &roomId){
        std::cout << "Room Chat Registration expired for Room Id: " << roomId << std::endl;
    }

    void onPublicRoomChatDelivered(RoomIdentity &roomId, const std::string &packetId, bool isEdited){
        std::cout << "Public Room Chat Message Delivered for roomId: " << roomId << " ;packetId: " << packetId << std::endl;
    }

    void onPublicRoomChatFailedToSend(RoomIdentity &roomId, const std::string &packetId){

    }

    void onSDKError(int errorCode, const std::string &packetId) {
        std::cout << "SDK ERROR: " << errorCode << std::endl;
    }

    void onServerTimeSynced(long long timeDifference){
        std::cout << "Server time synced, time difference with server: " << timeDifference << std::endl;
    }
    //New eventhandler function added here

    void onPublicRoomChatReceived(RoomIdentity &roomId, UserIdentity friendId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, const std::string &memberFullName, const std::string &memberProfileUrl){
        std::cout << "Message Received: " << message << " from friendId: " << friendId << " in Chat Room: " << roomId << " PacketID: " << packetId << std::endl;
        std::cout << std::endl << "Member Full Name: " << memberFullName << std::endl;
        std::cout << "Member Profile Url: " << memberProfileUrl << std::endl;
    }

    void onPublicRoomChatEdited(RoomIdentity &roomId, UserIdentity friendId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, const std::string &memberFullName, const std::string &memberProfileUrl){
        std::cout << "Edited message received  from friendId: " << friendId << " in Chat Room: " << roomId << ". MESSAGE : " << message; //<<" (packetId "<<packetId<<")"<<std::endl;
        std::cout << std::endl << "Member Full Name: " << memberFullName << std::endl;
        std::cout << "Member Profile Url: " << memberProfileUrl << std::endl;
    }

    void onPublicRoomListReceived(const std::vector<imsdk::RoomDTO> &roomList, bool roomListFromHistory){
        std::cout << "Room List" << std::endl;
        for (int i = 0; i < roomList.size(); i++){
            std::cout << std::setw(3) << "Room " << i + 1 << ": " << roomList[i].getRoomId() << " " << roomList[i].getRoomFullName() << " " << roomList[i].getRoomPictureUrl() << " numberOfMember:" << roomList[i].getNumberOfMember() << std::endl;
            if (roomList[i].getRoomMessageList().size() > 0){
                std::cout << std::setw(6) << "Room Message List : " << std::endl;
                for (int j = 0; j < roomList[i].getRoomMessageList().size(); j++){
                    std::cout << std::setw(9) << "Sender Id: " << roomList[i].getRoomMessageList()[j].getSenderId() << " Message " << roomList[i].getRoomMessageList()[j].getMessage() << std::endl;
                }
            }
        }
    }

    void onPublicRoomInformationReceived(RoomIdentity &roomId, std::string &roomName, std::string &roomUrl, const std::string &packetId){
        std::cout << "Room Information Received" << std::endl;
        std::cout << "Room Id: " << roomId << "Room Name: " << roomName << std::endl << "Room Url: " << roomUrl << std::endl;
    }

    void onPublicRoomChatTyping(RoomIdentity &roomId, UserIdentity friendId, const std::string &memberName){
        std::cout << "Chat Room:" << roomId << " Member Name: " << memberName << " Member UserId: " << friendId << " is typing ...";
    }

    void onPublicChatMemberListReceived(RoomIdentity &roomId, const std::string &pagingState, const std::vector<imsdk::PublicChatMemberDTO> &publicChatMemberList){
        std::cout << "Member List received: " << std::endl << " RoomID: " << roomId << " pagingState: " << pagingState << std::endl;
        for (int i = 0; i < publicChatMemberList.size(); i++){
            std::cout << "  Member Id " << i + 1 << ": " << publicChatMemberList[i].getMemberId() << " original userId: " << publicChatMemberList[i].getFakeId() << " ringId: " << publicChatMemberList[i].getRingId() << std::endl;
        }
    }

    void onPublicChatMemberCountChanged(RoomIdentity &roomId, int numberOfMembers){
        std::cout << "Room member count changed roomId: " << roomId << " count: " << numberOfMembers << std::endl;
    }

    void onPublicRoomChatHistoryReceived(RoomIdentity& roomId, const std::vector<imsdk::SDKMessageDTO> &publicChatMessageList)
    {
        std::cout << "onPublicRoomChatHistoryReceived" << std::endl;
        for (int i = 0; i < publicChatMessageList.size(); i++){
            std::cout << "Member Name :" << publicChatMessageList[i].getMemberFullName()
                << " packetId: " << publicChatMessageList[i].getPacketId()
                << " Message: " << publicChatMessageList[i].getMessage()
                << " senderId : " << publicChatMessageList[i].getSenderId()
                << " Like Count: " << publicChatMessageList[i].getPublicChatLikeCount()
                << " LIked: " << publicChatMessageList[i].isPublicChatILike()
                << " Reported: " << publicChatMessageList[i].isPublicChatIReport() << std::endl;
        }
    }

    void onPublicRoomChatHistoryCompleted(RoomIdentity &roomId){
        std::cout << "Public chat history completed............" << std::endl;
    }

    void shouldCheckServerAddressForRoom(RoomIdentity &roomId){
        std::cout << "Should check server address for room id " << roomId << std::endl;
    }
    void onPublicRoomListRequestStatus(const std::string &packetId, bool requestStatus){

    }
    void onPublicRoomInformationRequestFailed(RoomIdentity &roomId, const std::string &packetId){

    }
    void onPublicRoomChatHistoryRequestStatus(RoomIdentity &roomId, const std::string &packetId, bool requestStatus){

    }
    void onPublicRoomMemberListRequestStatus(RoomIdentity &roomId, const std::string &packetId, bool requestStatus){

    }

    void onPublicChatMessageDeleted(RoomIdentity& roomId, const std::vector<std::string>& deletedPacketIds){
        std::cout << "onPublicChatMessageDeleted()" << " roomId: " << roomId << std::endl;
        std::cout << "Deleted packetIds:" << std::endl;
        for (int i = 0; i < deletedPacketIds.size(); i++){
            std::cout << deletedPacketIds.at(i) << std::endl;
        }
    }

    void onPublicChatMessageLiked(RoomIdentity& roomId, const std::string& packetId, UserIdentity recipientId){
        std::cout << "onPublicChatMessageLiked()" << " roomId: " << roomId << " packetId: " << packetId << " recipientId: " << recipientId << std::endl;
    }

    void onPublicChatMessageUnliked(RoomIdentity& roomId, const std::string& packetId, UserIdentity recipientId){
        std::cout << "onPublicChatMessageUnliked()" << " roomId: " << roomId << " packetId: " << packetId << " recipientId: " << recipientId << std::endl;
    }

    void onPublicChatMessageReported(RoomIdentity& roomId, const std::string& packetId, UserIdentity recipientId){
        std::cout << "onPublicChatMessageReported()" << " roomId: " << roomId << " packetId: " << packetId << " recipientId: " << recipientId << std::endl;
    }

    void onShadowIdsInfoRequestFailed(const std::string &packetId)
    {
        std::cout << "Shadow Id info request failed. PacketId: " << packetId;
    }

    void onShadowIdsInfoResponseReceived(const std::vector<imsdk::PublicChatMemberDTO> &shadowIdsInfo)
    {
        for (int i = 0; i < shadowIdsInfo.size(); i++){
            std::cout << "RoomId: " << shadowIdsInfo[i].getRoomId() << " ;memberId: " << shadowIdsInfo[i].getMemberId() << " ;shadowId: " << shadowIdsInfo[i].getFakeId() << std::endl;
        }
    }
    void onFileStreamRequestReceived(UserIdentity friendId, FileIdentity fileId, int fileTransferPort, long long fileOffset){
        std::cout << "File Accepted by friendId: " << friendId << " File ID: " << fileId << " Port: " << fileTransferPort << "File Offset: " << fileOffset << std::endl;
    }
    void onFileStreamRequestConfirmed(const std::string &packetId, UserIdentity friendId, FileIdentity fileId, int fileTransferPort, bool fileAcceptReject){
        std::cout << "Packet ID: " << packetId << " File Stream Request confirmed by friendId: " << friendId << " File ID: " << fileId << " Port: " << fileTransferPort << std::endl;
    }
    void onFileTransferCanceled(UserIdentity friendId, FileIdentity fileId){
        std::cout << "File Transfer Canceled with friendId: " << friendId << " fileId: " << fileId << std::endl;
    }

    void onFileStreamRequestReceived(UserIdentity userId, UserIdentity friendId, FileIdentity fileId){}
    void onFriendFileSessionRequestSuccess(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId, int fileTransferPort){}
    void onFriendFileTransferSessionRequestFailed(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId){}
    void onFriendFileStreamRequestSuccess(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId){}
    void onFriendFileTransferStreamRequestFailed(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId)
    {
        std::cout << "File Transfer Failed with friendId: " << friendId << " fileId: " << fileId << std::endl;
    }

    void onGroupFileStreamRequestReceived(UserIdentity friendId, GroupIdentity groupId, FileIdentity fileId)
    {
        std::cout << "File stream request for group received" << std::endl;
    }
    void onGroupFileSessionRequestSuccess(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId, int fileTransferPort)
    {
        std::cout << "File session request for group success" << std::endl;
    }
    void onGroupFileTransferSessionRequestFailed(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId)
    {
        std::cout << "File session request for group failed" << std::endl;
    }
    void onGroupFileStreamRequestSuccess(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId)
    {
        std::cout << "File stream request for group success" << std::endl;
    }
    void onGroupFileTransferStreamRequestFailed(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId)
    {
        std::cout << "File stream request for group failed" << std::endl;
    }

    void onFriendGetChatMessageFailedToSend(UserIdentity userId, UserIdentity friendId, const std::string& packetId){
        std::cout << "FriendGetChatMessageFailedToSend Friend ID: " << friendId << " PacketId: " << packetId << std::endl;
    }

    void onGroupGetChatMessageFailedToSend(GroupIdentity groupId, const std::string& packetId){
        std::cout << "GroupGetChatMessageFailedToSend Group ID: " << groupId << " PacketId: " << packetId << std::endl;
    }

    void onGroupChatMessageSeenListReceived(GroupIdentity groupId, const std::string &packetId, const std::vector<imsdk::MemberDTO> &memberList){
        std::cout << "GroupChatMessageSeenListReceived Group ID: " << groupId << " PacketId: " << packetId << std::endl;
        for (int i = 0; i < memberList.size(); i++)
        {
            std::cout << "MemberId: " << memberList[i].getMemberIdentity() << " seen time: " << memberList[i].getSeenTime() << std::endl;
        }
    }

    void onPublicChatCategoryListReceived(std::vector<std::string> &publicChatCategoryList){
        std::cout << "Public Chat Category List Received. Categroy List: " << std::endl;
        for (int i = 0; i < publicChatCategoryList.size(); i++){
            std::cout << publicChatCategoryList.at(i) << std::endl;
        }
    }

    void onPublicChatLikeMemberListReceived(RoomIdentity &roomId, const std::string &packetId, const std::vector<imsdk::PublicChatMemberDTO> &publicChatMemberList){
        std::cout << "Public Chat Like Member List Received. RoomID" << roomId << " packetId: " << packetId << " Member List: " << std::endl;
        for (int i = 0; i < publicChatMemberList.size(); i++){
            std::cout << "Public Chat Member ID: " << publicChatMemberList[i].getMemberId() << " ringId: " << publicChatMemberList[i].getRingId() << std::endl;
        }
    }

    void onPublicChatDeleteRequestStatus(RoomIdentity roomId, const std::string &packetId, bool status){
        std::cout << "onPublicChatDeleteRequestStatus. RoomID: " << roomId << " PacketId: " << packetId;
        if (status) std::cout << " SUCCESS" << std::endl;
        else std::cout << " FAILED" << std::endl;
    }

    void onPublicChatLikeUnlikeRequestStatus(RoomIdentity roomId, const std::string &requestPacketId, const std::string &messagePacketId, bool status, bool fromLikeRequest){
        std::cout << "onPublicChatLikeUnlikeRequestStatus. RoomID: " << roomId << " requesPacketId: " << requestPacketId << " messagePacketId: " << messagePacketId;
        if (status) std::cout << " SUCCESS" << std::endl;
        else std::cout << " FAILED" << std::endl;
    }

    void onPublicChatReportRequestStatus(RoomIdentity roomId, const std::string &requestPacketId, const std::string &messagePacketId, bool status){
        std::cout << "onPublicChatReportRequestStatus. RoomID: " << roomId << " requesPacketId: " << requestPacketId << " messagePacketId: " << messagePacketId;
        if (status) std::cout << " SUCCESS" << std::endl;
        else std::cout << " FAILED" << std::endl;
    }

    void onPublicChatLikeMemberListRequestStatus(RoomIdentity roomId, const std::string &packetId, bool status){
        std::cout << "onPublicChatLikeMemberListRequestStatus. RoomID: " << roomId << " PacketId: " << packetId;
        if (status) std::cout << " SUCCESS" << std::endl;
        else std::cout << " FAILED" << std::endl;
    }

    void onPublicChatCategoryListRequestStatus(const std::string &packetId, bool status){
        std::cout << "onPublicChatCategoryListRequestStatus PacketId: " << packetId;
        if (status) std::cout << " SUCCESS" << std::endl;
        else std::cout << " FAILED" << std::endl;
    }

    //Live stream chat
    void onLiveStreamChatRegisterSuccess(UserIdentity publisherId, const std::string &packetId)
    {
        std::cout << "Live stream chat register success, publisher id: " << publisherId << " ;packetId: " << packetId << std::endl;
    }
    void onLiveStreamChatRegisterFailure(UserIdentity publisherId, const std::string &packetId)
    {
        std::cout << "Live stream chat register FAILED, publisher id: " << publisherId << " ;packetId: " << packetId << std::endl;
    }
    void onLiveStreamChatRegistrationExpired(UserIdentity publisherId)
    {
        std::cout << "Live stream chat registration EXPIRED, publisher id: " << publisherId << std::endl;
    }
    void onLiveStreamChatDelivered(UserIdentity publisherId, const std::string &packetId)
    {
        std::cout << "Live stream chat Delivered, publisher id: " << publisherId << " ;packetId: " << packetId << std::endl;
    }
    void onLiveStreamChatFailedToSend(UserIdentity publisherId, const std::string &packetId)
    {
        std::cout << "Live stream chat FAILED to send, publisher id: " << publisherId << " ;packetId: " << packetId << std::endl;
    }
    void onLiveStreamChatReceived(UserIdentity publisherId, UserIdentity senderId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, const std::string &senderFullName)
    {
        std::cout << "Live stream chat received, publisher id: " << publisherId << " senderId: " << senderId << " ;packetId: " << packetId << " ;message: " << message << " ;senderFullName: " << senderFullName << std::endl;
    }
    void onLiveStreamChatTyping(UserIdentity publisherId, UserIdentity senderId)
    {
        std::cout << "Live stream chat Typing, publisher id: " << publisherId << " ;senderId: " << senderId << std::endl;
    }
    void onLiveStreamChatBlockUserRequestStatus(UserIdentity blockedUserId, const std::string &packetId)
    {
        std::cout << "onLiveStreamChatBlockUserRequestStatus. Blocked user id: " << blockedUserId << std::endl;
    }
    void onLiveStreamChatUserBlocked(UserIdentity publisherId, UserIdentity blockedUserId)
    {
        std::cout << "onLiveStreamChatUserBlocked. PublisherID: " << publisherId << " Blocked user id: " << blockedUserId << std::endl;
    }
    void shouldCheckServerAddressForLiveStreamChat(UserIdentity publisherId)
    {
        std::cout << "Should check server address for live stream chat, publisher id: " << publisherId << std::endl;
    }

    void onNetworkDataCounted(const imsdk::DataCounter& dataCounter){
        //std::cout << "On Data Counted () ::: Data Sent---> " << dataCounter.getDataSent() << " Data Received: " << dataCounter.getDataReceived() << std::endl;
    }

    void onFriendFileManifestUploaded(UserIdentity userId, UserIdentity friendId, const std::string &packetId, std::string fileUrl, int messageType,
        int timeout, std::string caption, int widthOrFileSize, int heightOrDuration){

        std::cout << "onFileManifestUploaded(): friendId " << friendId << " File Url: " << fileUrl << " Caption: " << caption << " WidthOrFileSize: "
            << widthOrFileSize << " HeightOrDuration: " << heightOrDuration << " packetId: " << packetId << std::endl << "SecretTimeout: " << timeout << std::endl;
        chat_media_friend_id = friendId;
        chat_media_manifest_url = fileUrl;
        chat_media_msg_type = messageType;
        chunk_transfer_packet_id = packetId;
    }

    void onFriendIncomingChatMedia(UserIdentity userId, UserIdentity friendId, std::string fileName, const std::string &packetId, int messageType, int timeout, long long messageDate, bool isSecretVisible, std::string caption, int widthOrSize, int heightOrDuration){
        std::cout << "Incoming File from FriendID: " << friendId << " file name: " << fileName << std::endl;
        std::cout << "PacketID: " << packetId << " messageType: " << messageType << " messageDate: " << messageDate << std::endl;
        std::cout << "caption: " << caption << " widthOrSize: " << widthOrSize << "heightOrDuration: " << heightOrDuration << std::endl << std::endl;
        chunk_transfer_packet_id = packetId;
        // call 65 accetpChatMedia(friendId, fileName) next to accept the file
    }

    void onFriendChatMediaTransferProgress(UserIdentity userId, UserIdentity friendId, std::string fileName, double transferPercentage, bool isUpload, const std::string &packetId){
        if (isUpload){
            std::cout << "Uploading... " << fileName << " completed: " << transferPercentage << "%" << std::endl;
            std::cout << "PacketID: " << packetId << std::endl << std::endl;
        }
        else{
            std::cout << "Downloading... " << fileName << " completed: " << transferPercentage << "%" << std::endl;
            std::cout << "PacketID: " << packetId << std::endl << std::endl;
        }
    }

    void onFriendChatMediaDownloadCompleted(UserIdentity userId, UserIdentity friendId, std::string fileName, const std::string &packetId, int mediaType, int timeout){
        std::cout << "DOWNLOAD complete. file: " << fileName << std::endl;
        std::cout << "Media type: " << mediaType << " timeout: " << timeout << std::endl;
    }

    void onFriendChatMediaTransferFailed(UserIdentity userId, UserIdentity friendId, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer){
        if (isUpload){
            std::cout << "UPLOAD FAILED ! FriendId: " << friendId << " file name: " << fileName << "packetId: " << packetId << std::endl;
        }
        else{
            std::cout << "DOWNLOAD FAILED ! FriendId: " << friendId << " file name: " << fileName << "packetId: " << packetId << std::endl;
        }

        if (isChunkedTransfer){
            std::cout << "STRATEGY: CHUNKED" << std::endl;
        }
        else{
            std::cout << "STRATEGY: NON-BLOCKING" << std::endl;
        }
    }

    void onFriendChatMediaTransferCanceled(UserIdentity userId, UserIdentity friendId, UserIdentity canceledBy, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer){
        if (isUpload){
            std::cout << "UPLOAD Canceled ! FriendId: " << friendId << " file name: " << fileName << "packetId: " << packetId << std::endl;
        }
        else{
            std::cout << "DOWNLOAD Canceled ! FriendId: " << friendId << " file name: " << fileName << "packetId: " << packetId << std::endl;
        }

        if (isChunkedTransfer){
            std::cout << "STRATEGY: CHUNKED" << std::endl;
        }
        else{
            std::cout << "STRATEGY: NON-BLOCKING" << std::endl;
        }
    }

    void onGroupFileManifestUploaded(GroupIdentity groupId, const std::string &packetId, std::string cloudManifestUrl, int messageType, std::string caption, int widthOrFileSize, int heightOrDuration)  {

        std::cout << "onGroupFileManifestUploaded(): groupId" << groupId << " File Url: " << cloudManifestUrl << " Caption: " << caption << " WidthOrFileSize: "
            << widthOrFileSize << " HeightOrDuration: " << heightOrDuration << " packetId: " << packetId << std::endl << std::endl;
        chat_media_group_id = groupId;
        chat_media_manifest_url = cloudManifestUrl;
        chat_media_msg_type = messageType;
        chunk_transfer_packet_id = packetId;
    }
    void onGroupIncomingChatMedia(UserIdentity friendId, GroupIdentity groupId, std::string fileName, const std::string &packetId, int messageType, long long messageDate, std::string caption, int widthOrSize, int heightOrDuration){
        std::cout << "Incoming File from GroupId: " << groupId << " friendId: " << friendId << " file name: " << fileName << std::endl;
        std::cout << "PacketID: " << packetId << " messageType: " << messageType << " messageDate: " << messageDate << std::endl << std::endl;
        std::cout << "caption: " << caption << " widthOrSize: " << widthOrSize << "heightOrDuration: " << heightOrDuration << std::endl << std::endl;
        chunk_transfer_packet_id = packetId;
    }
    void onGroupChatMediaTransferProgress(UserIdentity friendId, GroupIdentity groupId, std::string fileName, double transferPercentage, bool isUpload, const std::string &packetId){
        if (isUpload){
            std::cout << "Uploading... " << fileName << " completed: " << transferPercentage << "%" << std::endl;
            std::cout << "GroupId: " << groupId << " friendId: " << friendId << "PacketID: " << packetId << std::endl << std::endl;
        }
        else{
            std::cout << "Downloading... " << fileName << " completed: " << transferPercentage << "%" << std::endl;
            std::cout << "GroupId: " << groupId << " friendId: " << friendId << "PacketID: " << packetId << std::endl << std::endl;
        }
    }
    void onGroupChatMediaTransferFailed(UserIdentity friendId, GroupIdentity groupId, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer){
        if (isUpload){
            std::cout << "GROUP UPLOAD FAILED ! GroupId: " << groupId << " FriendId: " << friendId << " file name: " << fileName << "packetId: " << packetId << std::endl;
        }
        else{
            std::cout << "GROUP DOWNLOAD FAILED ! GroupId: " << groupId << " FriendId: " << friendId << " file name: " << fileName << "packetId: " << packetId << std::endl;
        }

        if (isChunkedTransfer){
            std::cout << "STRATEGY: CHUNKED" << std::endl;
        }
        else{
            std::cout << "STRATEGY: NON-BLOCKING" << std::endl;
        }
    }

    void onGroupChatMediaTransferCanceled(UserIdentity friendId, GroupIdentity groupId, UserIdentity canceledBy, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer){
        if (isUpload){
            std::cout << "Group UPLOAD Canceled ! FriendId: " << friendId << " file name: " << fileName << "packetId: " << packetId << std::endl;
        }
        else{
            std::cout << "Group DOWNLOAD Canceled ! FriendId: " << friendId << " file name: " << fileName << "packetId: " << packetId << std::endl;
        }

        if (isChunkedTransfer){
            std::cout << "STRATEGY: CHUNKED" << std::endl;
        }
        else{
            std::cout << "STRATEGY: NON-BLOCKING" << std::endl;
        }

    }

    void onChatMediaTransferDirectoryError(std::string directoryPath)
    {
        std::cout << "Error. Chat media transfer directory error! should create directories." << std::endl;
    }

	void onSyncConversationRequestStatus(UserIdentity userId, const std::string &packetId, long long syncTime, bool status) {

	}

	void onSyncFriendHistoryMessageRequestStatus(UserIdentity userId, UserIdentity friendId, const std::string &packetId, long long syncTime, int direction, bool status) {

	}

	void onSyncFriendHistoryMessageReceived(UserIdentity userId, UserIdentity friendId, const std::string &packetId, const std::vector<imsdk::SDKMessageDTO> &friendHistoryMessageList, long long oldestMessageDate, int direction)
	{

	}

	void onMyGroupListPagingReceived(const std::vector<imsdk::GroupDTO> &myGroupList, const std::string &pivotId, int direction)
	{

	}

	void onMyGroupListReceiveCompleted()
	{

	}

	void onSyncFriendHistoryMessageReceiveCompleted(UserIdentity userId, UserIdentity friendId, const std::string &packetId, int direction)
	{

	}

	void onSyncGroupHistoryMessageRequestStatus(GroupIdentity groupId, const std::string &packetId, long long syncTime, int direction, bool status)
	{

	}

	void onSyncGroupHistoryMessageReceived(GroupIdentity groupId, const std::string &packetId, const std::vector<imsdk::SDKMessageDTO> &groupHistoryMessageList, const std::vector<imsdk::GroupActivityDTO> &groupHistoryActivityList, long long oldestMessageDate, int direction)
	{

	}

	void onSyncGroupHistoryMessageReceiveCompleted(GroupIdentity groupId, const std::string &packetId, int direction)
	{

	}

    void shouldUpdateAppSessionID()
    {
        std::cout << "Should update APP_SESSION_ID !!!" << std::endl;
    }

    void onGroupChatMediaDownloadCompleted(UserIdentity friendId, GroupIdentity groupId, std::string fileNameWithPath, const std::string &packetId, int mediaType){
        std::cout << "DOWNLOAD complete. GroupId: " << groupId << " friendId: " << friendId << "file: " << fileNameWithPath << std::endl;
        std::cout << "Media type: " << mediaType << std::endl;
    }

    void shouldUpdateUserPassword()
    {
        std::cout << "Should update password cause provided empty password" << std::endl;
    }


    void onActivaeOrDeactivateUserAccountStatus(UserIdentity userId, const std::string &packetId, bool isAccountActivate, bool status){}
    void onGetUserInfoReceived(UserIdentity userId, UserIdentity friendId, const std::string &packetId, std::string friendName, UserIdentity friendRingId, std::string friendProfileImageUrl, int friendProfileType){}
    void onGetUserInfoFailure(UserIdentity userId, UserIdentity friendId, const std::string &packetId){}
    void onAddNoticeRequestStatus(const std::string &, bool){}

};

void menu() {
    std::cout << "reg:     1 friendId status" << std::endl;
    std::cout << "chat:    2 friendId message" << std::endl;
    std::cout << "seen:    3 friendId packetid" << std::endl;
    std::cout << "typing:  4 friendId" << std::endl;
    std::cout << "mchunk:  5 friendId" << std::endl;
    std::cout << "GroupChat register: 6" << std::endl;
    std::cout << "GroupChat initiator: 7" << std::endl;
    std::cout << "Edit groupChat: 8" << std::endl;
    std::cout << "Send group chat: 9" << std::endl;
    std::cout << "Change group mem status: 10" << std::endl;
    std::cout << "Get offline message: 11" << std::endl;
    std::cout << "Delete group chat message: 12" << std::endl;
    std::cout << "Edit friend Chat message: 13" << std::endl;
    std::cout << "Add group member: 14" << std::endl;
    std::cout << "File transfer: 15" << std::endl;
    std::cout << "Get friend history: 18" << std::endl;
    std::cout << "Get group history: 19" << std::endl;
    std::cout << "Room Chat register: 20" << std::endl;
    std::cout << "Send Public Room Chat Message: 21" << std::endl;
    std::cout << "Get Public Room List: 22" << std::endl;
    std::cout << "Search Public Room List: 23" << std::endl;
    std::cout << "Edit Public Room Chat Message: 24" << std::endl;
    std::cout << "Typing Public Room Chat: 25" << std::endl;
    std::cout << "Unregister Public Room Chat: 26" << std::endl;
    std::cout << "Delete friend chat: 27" << std::endl;
    std::cout << "Seen group chat: 28" << std::endl;
    std::cout << "Remove group member: 29" << std::endl;
    std::cout << "Change group URL: 30" << std::endl;
    std::cout << "Get Room Information: 31" << std::endl;
    std::cout << "Get Room List: 32" << std::endl;
    std::cout << "Get Room history: 33" << std::endl;
    std::cout << "Get Public Chat Room List With History: 34" << std::endl;
    std::cout << "Get Room Member List: 35" << std::endl;
    std::cout << "Get Room Member List Next: 36" << std::endl;
    std::cout << "Get All Registered Friend IDs: 37" << std::endl;
    std::cout << "Register anonymous friend chat: 39" << std::endl;
    std::cout << "Unregister public room chat 40" << std::endl;
    std::cout << "Request File Session: 41" << std::endl;
    std::cout << "Group File Session request: 42" << std::endl;
    std::cout << "send block packet: 43" << std::endl;
    std::cout << "Clean up: 44" << std::endl;
    std::cout << "send unblock packet: 45" << std::endl;
    std::cout << "Group File Stream request: 46" << std::endl;
    std::cout << "Get registered group List: 47" << std::endl;
    std::cout << "onPublicRoomChatENTER: 48" << std::endl;
    std::cout << "onPublicRoomChatEXIT: 49" << std::endl;
    std::cout << "GetFriendChatMessage: 50" << std::endl;
    std::cout << "GetGroupChatMessage: 51" << std::endl;
    std::cout << "GetNetworkDataCount: 52" << std::endl;
    std::cout << "Delete Public Chat Message: 53" << std::endl;
    std::cout << "Like Public Chat Message: 54" << std::endl;
    std::cout << "Report Public Chat Message: 55" << std::endl;
    std::cout << "Public Chat Like Member List Request: 56" << std::endl;
    std::cout << "Public Chat Category List Request: 57" << std::endl;
    std::cout << "GetGroupMessageSeenList: 58" << std::endl;
    std::cout << "Get friend conversation list: 59" << std::endl;
    std::cout << "Check Network Connection: 60" << std::endl;
    std::cout << "Get friend Information: 61" << std::endl;

    std::cout << "Register Live Stream Chat: 101" << std::endl;
    std::cout << "Send Live Stream Chat: 102" << std::endl;
    std::cout << "Typing Live Stream Chat: 103" << std::endl;
    std::cout << "Generate group ID: 104" << std::endl;

    std::cout << "Delete conversation list: 162" << std::endl;
    std::cout << "Mark as read conversation list: 163" << std::endl;

    std::cout << "Start Chat Media Transfer: 62" << std::endl;
    std::cout << "Send Media Url Message: 63" << std::endl;
    std::cout << "Download Media from Url Message: 64" << std::endl;
    std::cout << "Accept Chat / Group Chat Media: 65" << std::endl;

    std::cout << "Send Group Chat Media: 66" << std::endl;
    std::cout << "Send Group Media Url Message: 67" << std::endl;
    std::cout << "Download Group Chat Media: 68" << std::endl;
    std::cout << "Get pending friend chat media list: 69" << std::endl;
    std::cout << "Cancel Chat media transfer: 71" << std::endl;
    std::cout << "Check isChatMediaTransferInProgress: 72" << std::endl;
    std::cout << "Block live chat user: 73" << std::endl;
    std::cout << "Encrypt Decrypt test: 75" << std::endl;
    std::cout << "Data encryption->getSessionlessKey: 76" << std::endl;
    std::cout << "Unregister friend chat: 77" << std::endl;
    std::cout << "quit: -1" << std::endl;
}

long long gettime()
{
    auto timeEpoch = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(timeEpoch).count();
}

//class imsdk::PacketTimeId {
//public:
//    PacketTimeId();
//    virtual ~PacketTimeId();
//    
//    std::string packetId;
//    unsigned long long packetTime1970;
//    unsigned long long packetTime1582;
//    
//private:
//
//};

imsdk::DuplicateChecker duplicateChecker;

void duplicateChecker_task1()
{
    while (true)
    {
        //std::cout << std::endl << "starting duplicateChecker.isSafe call 1111111111111111111111111" << std::endl;
        duplicateChecker.isSafe("sample_check_hash");
        //std::cout << std::endl << "finished duplicateChecker.isSafe call 2222222222222222222222222" << std::endl;
    }
}

void duplicateChecker_task2()
{
    while (true)
    {
        //std::cout << std::endl << "starting duplicateChecker.clear call 33333333333333333333333333" << std::endl;
        duplicateChecker.clear();
        //std::cout << std::endl << "finished duplicateChecker.clear call --------------------------" << std::endl;
    }
}


void checkStartServicesCall_task1()
{
    while (true)
    {
        imsdk::Chat::startServices();
    }
}

void checkStartServicesCall_task2()
{
    while (true)
    {
        imsdk::Chat::startServices();
    }
}

void checkStartServicesCall_task3()
{
    while (true)
    {
        imsdk::Chat::stopServices();
    }
}


int main(int argc, char** argv) {
    std::cout << "Self Id: ";
    UserIdentity userid = 0;
    std::cin >> userid;
    GroupIdentity groupId = 100123;
    int secretTimeout = 0;
    std::string packetId;
    imsdk::ApiStatus status("");

    //    std::string message, encryptMessage, decryptMessage;
    //    std::cin >>message;
    //    encryptMessage = MessageEncryption::encryptMessage(message, "hello");
    //    std::cout<<"encrypted message: "<<encryptMessage<<std::endl;
    //    decryptMessage = MessageEncryption::decryptMessage(encryptMessage, "hello");
    //    std::cout<<"decrypted message: "<<decryptMessage<<std::endl;
    //    return 0;

    std::unordered_map<int, std::string> passwordMap;
    //    passwordMap[1] = "1234560";
    passwordMap[1] = "fb0a8929865016ba27349dbfeeaa31a699fb74d5";
    //passwordMap[2] = "asdfgh";
    passwordMap[2] = "7ab515d12bd2cf431745511ac4ee13fed15ab578";
    passwordMap[3] = "aaaaaa";
    passwordMap[583] = "aaaaaa";
    passwordMap[19] = "asdfgh";
    passwordMap[60913] = "d4d34fc8979f2077ed39bc78677a582b3ae80851";
    passwordMap[60915] = "bab4cf29ef76392e2f7cc0284baf70bce8bb6126";
    passwordMap[55717] = "7c4a8d09ca3762af61e59520943dc26494f8941b";

    if (argc > 1) userid = atoi(argv[1]);

    std::cout << "userid: " << userid << std::endl;

    std::string serverAddress = "38.127.68.55"; //(dev)
    //    std::string serverAddress = "192.168.1.251";
    //    std::string serverAddress = "192.168.1.138";
    //    std::string serverAddress = "104.193.36.180";
    std::string baseUploadUrl = "http://devimages.ringid.com/";
    std::string baseDownloadUrl = "http://devimagesres.ringid.com/";

    std::string appSessionID = "223760186236930132110078272"; // used as storage_token in chat media transfer
    int appType = 1;
    if (userid > 60000) appType = 3;
    std::cout << "APP TYPE: app type: " << appType << std::endl;
    std::vector<std::string> directoryPaths;
    //directoryPaths.push_back("/home/towhid/ringid");  // settings directory path
    directoryPaths.push_back("H:\\DESKTOP_LOGSandOTHERS\\SDKChatLogs");  // settings directory path

    if (userid == 1) directoryPaths.push_back("H:\\DESKTOP_LOGSandOTHERS\\SDKChatLogs"); // temp directory path

    //if (userid == 1) directoryPaths.push_back("/home/towhid/ringid/tmp_dir_111"); // temp directory path
    else if (userid == 2) directoryPaths.push_back("/home/towhid/ringid/tmp_dir_112");
    else if (userid == 3) directoryPaths.push_back("/home/towhid/ringid/tmp_dir_113");

    if (userid == 2) {
        directoryPaths.push_back("/home/towhid/ringid/download_112/ringID_images"); // image download path
        directoryPaths.push_back("/home/towhid/ringid/download_112/ringID_audio"); // audio download path
        directoryPaths.push_back("/home/towhid/ringid/download_112/ringID_video"); // video download path
        directoryPaths.push_back("/home/towhid/ringid/download_112/ringID_images_secret"); // image download path
        directoryPaths.push_back("/home/towhid/ringid/download_112/ringID_audio_secret"); // audio download path
        directoryPaths.push_back("/home/towhid/ringid/download_112/ringID_video_secret"); // video download path
    }
    else {
        directoryPaths.push_back("H:\\DESKTOP_LOGSandOTHERS\\SDKChatLogs");
        directoryPaths.push_back("H:\\DESKTOP_LOGSandOTHERS\\SDKChatLogs");
        directoryPaths.push_back("H:\\DESKTOP_LOGSandOTHERS\\SDKChatLogs");
        directoryPaths.push_back("H:\\DESKTOP_LOGSandOTHERS\\SDKChatLogs");
        directoryPaths.push_back("H:\\DESKTOP_LOGSandOTHERS\\SDKChatLogs");
        directoryPaths.push_back("H:\\DESKTOP_LOGSandOTHERS\\SDKChatLogs");

        //directoryPaths.push_back("/home/towhid/ringid/ringID_images"); // image download path
        //directoryPaths.push_back("/home/towhid/ringid/ringID_audio"); // audio download path
        //directoryPaths.push_back("/home/towhid/ringid/ringID_video"); // video download path
        //directoryPaths.push_back("/home/towhid/ringid/ringID_images_secret"); // image download path
        //directoryPaths.push_back("/home/towhid/ringid/ringID_audio_secret"); // audio download path
        //directoryPaths.push_back("/home/towhid/ringid/ringID_video_secret"); // video download path
    }
    //std::cout << "vdo path: " << directoryPaths[4] << std::endl << "std::endl" << std::endl;

    bool autoDownloadEnabled{ true };
    if (userid == 2){
        autoDownloadEnabled = false;
    }
    //    std::string authServerAddress = "38.127.68.52";
    std::string authServerAddress = "172.16.3.41";

    //    int authServerPort = 1500;
    int authServerPort = 30025;
    internetchecker::InternetChecker::getInstance().setIpListFilePath("/home/towhid/ringid/imsdk_settings");
    std::set<UserIdentity> pageIdList;

    //imsdk::Chat chat(userid, "Towhid", serverAddress, 1200, authServerAddress, authServerPort, 2, appSessionID, 29, 0, directoryPaths, baseUploadUrl, baseDownloadUrl, autoDownloadEnabled, passwordMap[userid], appType, pageIdList);
    imsdk::Chat chat(34526, "Towhid", "104.193.36.181", 10051, authServerAddress, authServerPort, 2, appSessionID, 29, 0, directoryPaths, baseUploadUrl, baseDownloadUrl, autoDownloadEnabled, ipvsdk::security::HashAlgorithm::sha1("!@#$%^"), appType, pageIdList);

    chat.registerEventHandler(std::make_shared<ChatEventHandler>());
    //chat.registerFriendChat(friendid, "192.168.1.138", 1500, 3, "12cdsw34d", 3, 2, 2);
    //    std::cout << sizeof(string) <<std::endl;
    //    return 0;

    int type;
    menu();
    while (std::cin >> type) {
        if (type == 0) {
            menu();
        }
        else if (type == 1) {//status is known from the auth server
            int friendId, status;
            std::cin >> friendId >> status;
            //            chat.registerFriendChat(friendId, "0", 1500, 0, "12654654", 0, 1, 0, 0);
            chat.registerFriendChat(userid, "user1", friendId, "Noman", "url", serverAddress, 1500, 3, "12654654", 3, status, 2, 0, 0, 3);
            //            chat.registerFriendChat(friendId, "192.168.1.251", 1500, 3, "12654654", 3, status, 2);
        }
        else if (type == 2) {
            int friendId;
            //            std::string message = "Zeus was the god of the sky and ruler of the Olympian gods. He overthrew his father, Cronus, and then drew lots with his brothers Poseidon and Hades, in order to decide who would succeed their father on the throne. Zeus won the draw and became the supreme ruler of the gods, as well as lord of the sky and rain. His weapon was a thunderbolt which he hurled at those who displeased or defied him, especially liars and oathbreakers. He was married to Hera but often tested her patience, as he was infamous for his many affairs. \n Zeus, the presiding deity of the universe, ruler of the skies and the earth, was regarded by the Greeks as the god of all natural phenomena on the sky; the personification of the laws of nature; the ruler of the state; and finally, the father of gods and men. \n Using his shield, the Aegis, Zeus could create all natural phenomena related to the air and the sky, such as storms, tempests, and intense darkness. At his command, mighty thunders would flash and lightnings would roll, wreaking havoc; or the skies would open to rejuvenate the earth with life-giving water. \n As the personification of the operations of nature, he represented the grand laws of unchanging and harmonious order, by which both the natural and the spiritual world were governed. He was the god of regulated time as marked by the changing seasons and the regular succession of day and night, in contrast to what his father Cronus represented before him; absolute time, i.e. eternity.";
            std::string message;
            std::cin >> friendId >> message;
            imsdk::PacketTimeId packetTimeId = chat.generatePacketId();
            imsdk::ApiStatus apiStatus = chat.sendFriendChat(packetTimeId.packetId, userid, friendId, 2, 0, message, gettime(), true);
            //            std::cout<<"PacketId "<<packetTimeId.packetId<<std::endl;
        }
        else if (type == 3) {
            int friendId;
            int numberOfPacketId;
            std::string packetId;
            std::cin >> friendId >> numberOfPacketId;
            std::vector<imsdk::SeenPacketDTO> seenPacketDTOList;
            for (int i = 0; i < numberOfPacketId; i++){
                //std::cin >>packetId;
                packetId = chat.generatePacketId().packetId;
                seenPacketDTOList.push_back(imsdk::SeenPacketDTO(packetId, gettime(), 2)); //packetId, 0, true
            }
            chat.seenFriendChat(userid, friendId, seenPacketDTOList);
        }
        else if (type == 4) {
            int friendId;
            std::cin >> friendId;
            chat.typingFriendChat(userid, friendId);
        }
        else if (type == 5) {
            int friendId;
            std::cin >> friendId;
            for (int i = 0; i < 10; i++) {
                std::string message = "msg" + std::to_string(i);
                imsdk::PacketTimeId packetTimeId = chat.generatePacketId();
                chat.sendFriendChat(packetTimeId.packetId, userid, friendId, 2, 0, message, 0, true);
            }
        }
        else if (type == 6) {
            //int groupId;
            std::cin >> groupId;
            chat.registerGroupChat(groupId, serverAddress, 1500, 0);
        }
        else if (type == 7) {
            int numberOfMembers, groupMember, ringId;
            std::string message, groupName, url, fullName;

            time_t curtime = time(NULL);
            long long myTime = (long long)curtime;

            std::cin >> groupId >> groupName >> url >> fullName;

            std::vector<imsdk::MemberDTO> memberList;
            for (int i = 1; i < 10; i++)
            {
                memberList.push_back({ i, i, "নোমান", 3, userid });
            }

            chat.createGroup(groupId, groupName, url, memberList);

            //            std::cin >>message;
            //            packetId = generatePacketId();
            //            status = chat.sendGroupChat(packetId, groupId, fullName, 2, 0, 0, 0, message, myTime);

        }
        else if (type == 8) {
            std::string message, fullName, packetId;

            time_t curtime = time(NULL);
            //std::cout<<"curtime before casting: "<<curtime<<std::endl;
            long long myTime = (long long)curtime;
            //std::cout<<"cur time after casting: "<<myTime<<std::endl;

            //packetId = status.getPacketId();
            //std::cout<<"packet ID from editGroupChat: "<<packetId<<std::endl;
            std::cin >> message >> packetId;
            chat.editGroupChat(packetId, groupId, 2, message, myTime);
        }
        else if (type == 9) {
            //            chat.getGroupInformation(groupId);
            //            chat.getGroupMembers(groupId);
            GroupIdentity groupId;

            std::string message, packetId;
            std::cin >> groupId >> message;
            imsdk::PacketTimeId packetTimeId = chat.generatePacketId();
            chat.sendGroupChat(packetTimeId.packetId, groupId, 2, message, 0);
        }
        else if (type == 10) {
            int groupMember, ringId;
            GroupIdentity groupId;
            std::cin >> groupId;
            //            std::vector<imsdk::MemberDTO> memberList;
            //            for (int i = 0; i < 3; i++) {
            //                std::cin >>groupMember>>ringId;
            //                memberList.push_back({groupMember, ringId, "groupMember", 3, userid});
            //            }
            //            chat.changeGroupMemberStatus(groupId, memberList);
            chat.getGroupInformationWithMembers(groupId);
        }
        else if (type == 11) {
            imsdk::PacketTimeId packetTimeId = chat.generatePacketId();
            chat.requestForOffline(packetTimeId.packetTime1970, packetTimeId.packetTime1970);
            //            chat.requestForOffline(0, 0);
        }
        else if (type == 12) {
            std::vector<std::string> packetIds;
            for (int i = 0; i < 20; i++){
                packetIds.push_back(chat.generatePacketId().packetId);
            }
            GroupIdentity groupId;
            std::cin >> groupId;
            chat.deleteGroupChatMessage(groupId, packetIds);
        }
        else if (type == 13) {
            int friendId;
            std::string message, packetId;
            std::cin >> friendId >> message >> packetId;
            //imsdk::PacketTimeId packetTimeId = chat.generatePacketId();
            chat.editFriendChat(packetId, userid, friendId, 2, 0, message, 0, true);
        }
        else if (type == 14) {
            std::vector<imsdk::MemberDTO> memberList;
            UserIdentity member, ringId, groupId;
            std::cin >> member >> groupId;
            //for(int i=3; i<100; i++)
            //{
            memberList.push_back({ member, member + 100, "NOMAN", 3, userid });
            //}
            chat.addGroupMembers(groupId, memberList);
        }
        else if (type == 17){
            GroupIdentity groupId;
            std::cin >> groupId;
            //chat.leaveGroup(groupId);
        }
        else if (type == 18){
            UserIdentity friendId;
            int scrollType;
            std::string packetId;

            std::cout << "friendID : ";
            std::cin >> friendId;
            std::cout << "scroll Type : ";
            std::cin >> scrollType;
            std::cout << "packetId : ";
            std::cin >> packetId;


            //imsdk::PacketTimeId packetTimeId = chat.generatePacketId();
            //chat.requestFriendChatHistory(userid, friendId, packetTimeId.packetId, 1, 15);

            std::string packetID = "9dc9c900-6940-11e7-0000-0000000086de";//"71599850-6940-11e7-0000-0000000086de";
            chat.requestFriendChatHistory(34526, friendId, packetId, scrollType, 15);
        }
        else if (type == 19){
            imsdk::PacketTimeId packetTimeId = chat.generatePacketId();
            long long groupId;
            std::cin >> groupId;
            chat.requestGroupChatHistory(groupId, packetTimeId.packetId, 1, 5);
        }
        else if (type == 20){
            imsdk::PacketTimeId packetTimeId = chat.generatePacketId();
            std::string roomId;
            std::string roomName;
            std::string roomUrl;
            UserIdentity ringId;
            //            long long anonymousId;
            std::cin >> roomId >> roomName >> roomUrl >> ringId;
            //            chat.registerPublicRoomChat(userid+1000000, roomId, roomName, roomUrl);
            chat.registerPublicRoomChat(roomId, roomName, roomUrl, ringId);
        }
        else if (type == 21){
            imsdk::PacketTimeId packetTimeId = chat.generatePacketId();
            std::string roomId, message, memberFullName = "abcd", memberProfileUrl = "";
            int messageType = 2;
            long long messageDate = 0;

            std::cin >> roomId >> message;

            chat.sendPublicRoomChat(packetTimeId.packetId, roomId, messageType, message, messageDate, memberFullName, memberProfileUrl);
        }
        else if (type == 22){
            int startIndex, limit;

            std::cin >> startIndex >> limit;

            //RoomId is not required
            //            chat.getRoomList(startIndex, limit);
            chat.getRoomListWithHistory(startIndex, limit);
        }
        else if (type == 23){
            int startIndex, limit;
            std::string searchName, country = "Bangladesh", category = "Cricket";

            std::cin >> searchName >> startIndex >> limit;

            chat.searchRoomList(searchName, country, category, startIndex, limit);
        }
        else if (type == 24){
            std::string roomId, message, packetId, memberFullName, memberProfileUrl;
            int messageType;
            long long messageDate;

            std::cin >> packetId >> roomId >> messageType >> message >> messageDate >> memberFullName >> memberProfileUrl;

            chat.editPublicRoomChat(packetId, roomId, messageType, message, messageDate, memberFullName, memberProfileUrl);
        }
        else if (type == 25){
            std::string roomId;

            std::cin >> roomId;

            chat.typingPublicRoomChat(roomId);
        }
        else if (type == 26){
            std::string roomId;
            std::cin >> roomId;

            chat.unregisterPublicRoomChat(roomId);
        }
        else if (type == 27)
        {
            std::vector<std::string> packetIds;
            int numberOfDeletePacket;
            UserIdentity friendId;
            std::cin >> friendId >> numberOfDeletePacket;
            for (int i = 0; i < numberOfDeletePacket; i++){
                packetIds.push_back(chat.generatePacketId().packetId);
            }
            //chat.deleteFriendChatMessage(userid, friendId, packetIds);
        }
        else if (type == 28)
        {
            UserIdentity friendId; GroupIdentity groupId;
            std::string packetId;
            std::cin >> groupId;
            std::vector<std::string> packetIds;
            std::cin >> packetId;
            packetIds.push_back(packetId);
            chat.seenGroupChat(groupId, packetIds);
        }
        else if (type == 29)
        {
            std::vector<UserIdentity> memberList;
            //            memberList.push_back({7, "a", 3, 1});
            //            memberList.push_back({8, "b", 3, 1});
            //            memberList.push_back({9, "c", 3, 1});
            //            chat.removeGroupMembers(100, memberList);
            UserIdentity memberId; GroupIdentity groupId;
            std::cin >> groupId >> memberId;
            memberList.push_back(memberId);
            chat.removeGroupMembers(groupId, memberList);
        }
        else if (type == 30)
        {
            std::string newGroupUrl = "newGroupUrl";
            chat.changeGroupUrl(100, newGroupUrl);
        }
        else if (type == 31)
        {
            RoomIdentity roomId;
            std::cin >> roomId;
            chat.getRoomInformation(roomId);
        }
        else if (type == 32)
        {
            int start;
            int limit;
            std::cin >> start >> limit;
            chat.getRoomList(start, limit);
            //            RoomIdentity roomId = 
        }
        else if (type == 33)
        {
            RoomIdentity roomId;// = "9df7e830-2c7e-11e6-80b9-31fadfa26813";
            //                                 
            //            imsdk::PacketTimeId packetTimeId = chat.generatePacketId(0, userid);
            imsdk::PacketTimeId packetTimeId = chat.generatePacketId();
            int month;
            std::cin >> roomId;
            std::cin >> month;
            int direction;
            std::cin >> direction;
            chat.requestRoomChatHistory(roomId, packetTimeId.packetId, 2016, month, direction, 50);
        }
        else if (type == 34)
        {
            int startIndex, limit;

            std::cin >> startIndex >> limit;

            chat.getRoomListWithHistory(startIndex, limit);
        }
        else if (type == 35)
        {
            RoomIdentity roomId;
            std::string pagingState;
            int limit;

            pagingState = "";
            std::cin >> roomId >> limit;

            chat.getRoomMemberList(roomId, pagingState, limit);
        }
        else if (type == 36)
        {
            RoomIdentity roomId = "1798b331-fe45-11e5-a7e9-750e97cc4e0d";
            std::string pagingState;
            int limit;

            //pagingState = "";
            std::cin >> pagingState >> limit;

            chat.getRoomMemberList(roomId, pagingState, limit);
        }
        else if (type == 37)
        {
            std::vector<UserIdentity> registeredFriendsList = chat.getRegisteredFriendsList(userid);
            std::cout << "List of Registered Friends: " << std::endl;
            for (int i = 0; i < registeredFriendsList.size(); i++){
                std::cout << "Friend ID: " << registeredFriendsList[i] << std::endl;
            }
        }

        else if (type == 38)
        {
            int friendId;
            std::string message;
            std::cin >> friendId >> message;
            //            std::string message = "Zeus was the god of the sky and ruler of the Olympian gods. He overthrew his father, Cronus, and then drew lots with his brothers Poseidon and Hades, in order to decide who would succeed their father on the throne. Zeus won the draw and became the supreme ruler of the gods, as well as lord of the sky and rain. His weapon was a thunderbolt which he hurled at those who displeased or defied him, especially liars and oathbreakers. He was married to Hera but often tested her patience, as he was infamous for his many affairs. \n Zeus, the presiding deity of the universe, ruler of the skies and the earth, was regarded by the Greeks as the god of all natural phenomena on the sky; the personification of the laws of nature; the ruler of the state; and finally, the father of gods and men. \n Using his shield, the Aegis, Zeus could create all natural phenomena related to the air and the sky, such as storms, tempests, and intense darkness. At his command, mighty thunders would flash and lightnings would roll, wreaking havoc; or the skies would open to rejuvenate the earth with life-giving water. \n As the personification of the operations of nature, he represented the grand laws of unchanging and harmonious order, by which both the natural and the spiritual world were governed. He was the god of regulated time as marked by the changing seasons and the regular succession of day and night, in contrast to what his father Cronus represented before him; absolute time, i.e. eternity.";
            //            std::string message = "hello";
            imsdk::PacketTimeId packetTimeId = chat.generatePacketId();
            chat.sendFriendChat(packetTimeId.packetId, userid, friendId, 2, 0, message, gettime(), true);
        }
        else if (type == 39)
        {
            int anonymousId, friendId, status;
            std::cin >> anonymousId >> friendId >> status;
            //            chat.registerFriendChat(friendId, "192.168.1.251", 1500, 3, "12654654", 3, status, 2);
            chat.registerAnonymousFriendChat(anonymousId, friendId, friendId, serverAddress, 1500, 3, "12654654", 3, status, 2);
        }
        else if (type == 40)
        {
            std::string roomId;
            std::cin >> roomId;
            chat.unregisterPublicRoomChat(roomId);
        }
        else if (type == 41)
        {

        }
        else if (type == 42)
        {
            long long groupId, fileId;
            std::cin >> groupId >> fileId;
            chat.groupFileTransferSessionRequest(groupId, fileId);
        }
        else if (type == 43)
        {
            UserIdentity friendId;
            std::cin >> friendId;
            imsdk::PacketTimeId packetTimeId = chat.generatePacketId();
            imsdk::ApiStatus st = chat.blockFriend(userid, packetTimeId.packetId, friendId, packetTimeId.packetTime1970, 0);
            std::cout << "Return type of block api is :" << st.getErrorCode() << std::endl;
        }
        else if (type == 44){
            chat.cleanUp(2);
        }
        else if (type == 45)
        {
            UserIdentity friendId;
            std::cin >> friendId;
            imsdk::PacketTimeId packetTimeId = chat.generatePacketId();
            imsdk::ApiStatus st = chat.unblockFriend(userid, packetTimeId.packetId, friendId, packetTimeId.packetTime1970);
        }
        else if (type == 46){
            long long friendId, groupId, fileId;
            std::cin >> friendId >> groupId >> fileId;
            chat.groupFileTransferStreamRequest(friendId, groupId, fileId);
        }
        else if (type == 47)
        {
            std::vector<std::shared_ptr<imsdk::GroupInformation>> registeredGroupList = chat.getRegisteredGroupList();
            for (int i = 0; i < registeredGroupList.size(); i++){
                time_t lastActivityTime = (time_t)(registeredGroupList[i]->getLastActivityTime() / 1000);
                std::cout << "GroupId: " << registeredGroupList[i]->getGroupId() << " lastActivityTime: " << ctime(&lastActivityTime) << std::endl;
            }
        }
        else if (type == 48){
            RoomIdentity roomId;
            std::cin >> roomId;
            chat.enterPublicChatScreen(roomId);
        }
        else if (type == 49){
            RoomIdentity roomId;
            std::cin >> roomId;
            chat.exitPublicChatScreen(roomId);
        }
        else if (type == 50){
            UserIdentity friendId;
            std::string packetId;
            std::cin >> friendId >> packetId;
            chat.getFriendChatMessage(userid, friendId, packetId);
        }
        else if (type == 51){
            GroupIdentity groupId;
            std::string packetId;
            std::cin >> groupId >> packetId;
            chat.getGroupChatMessage(groupId, packetId);
        }
        else if (type == 52){

            imsdk::DataCounter dataCounter = chat.getDataSentReceived();
            std::cout << "Data Sent: " << dataCounter.getDataSent();
            std::cout << " Data Received: " << dataCounter.getDataReceived() << std::endl;

        }
        else if (type == 53){
            RoomIdentity roomId;
            std::vector<std::string> packetIds;

            std::cin >> roomId;

            for (int i = 0; i < 5; i++){
                packetIds.push_back(chat.generatePacketId().packetId);
            }

            chat.deletePublicChatMessage(roomId, packetIds);
        }
        else if (type == 54){
            bool like = true;
            std::string packetId;
            RoomIdentity roomId;
            UserIdentity recipientId;
            std::cin >> packetId >> roomId >> recipientId;

            if (like) chat.likePublicChatMessage(packetId, roomId, recipientId);

            else chat.unlikePublicChatMessage(packetId, roomId, recipientId);
        }
        else if (type == 55){
            std::string reportMessage = "";
            RoomIdentity roomId;
            UserIdentity recipientId;
            std::cin >> packetId >> roomId >> recipientId;
            chat.reportPublicChatMessage(packetId, roomId, recipientId, reportMessage);
        }
        else if (type == 56){
            std::string packetId;
            RoomIdentity roomId;
            UserIdentity lastLikerId;
            int limit;
            std::cin >> packetId >> roomId >> lastLikerId >> limit;
            chat.getPublicChatLikeMemberList(roomId, packetId, lastLikerId, limit);
        }
        else if (type == 57){
            std::string pagingState = "";
            int limit;
            std::cin >> limit;
            chat.getPublicChatRoomCategoryList(pagingState, limit);
        }
        else if (type == 58){
            GroupIdentity groupId;
            std::string packetId;
            std::cin >> groupId >> packetId;
            chat.getGroupMessageSeenList(groupId, packetId);
        }
        else if (type == 59)
        {
            UserIdentity friendId;
            int startIndex = 0, limit = 10;
            //            std::cin >>friendId;
            std::cin >> startIndex >> limit;
            chat.getConversationList(userid, imsdk::ConversationType::ALL, startIndex, limit, 0);
        }
        else if (type == 60){
            for (int i = 0; i < 5; i++)
            {
                bool isAvailable = internetchecker::InternetChecker::getInstance().checkInternetConnection();

                std::cout << "Check " << i + 1 << ": ";
                if (isAvailable) std::cout << "Connection Available" << std::endl;
                else std::cout << "Connection Unavailable" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        else if (type == 61){
            UserIdentity friendId;
            std::cin >> friendId;
            auto friendInfo = chat.getFriendInformation(userid, friendId);
            std::cout << "friendName: " << friendInfo->getFriendName() << " friendUrl: " << friendInfo->getFriendUrl() << std::endl;
        }
        else if (type == 162){
            std::vector<imsdk::ConversationDTO> conversationList;
            imsdk::ConversationDTO conversation, conversation1, conversation2;
            UserIdentity friendId = 0;
            GroupIdentity groupId = 0;
            std::cin >> friendId >> groupId;
            if (friendId == 0){
                conversation.SetConversationType(4);
                conversation.SetFriendId(friendId);
                conversation.SetGroupId(groupId);
            }
            else{
                conversation.SetConversationType(3);
                conversation.SetFriendId(friendId);
                conversation.SetGroupId(groupId);
            }
            conversation1.SetConversationType(3);
            conversation1.SetFriendId(2);
            conversation1.SetGroupId(0);
            conversation2.SetConversationType(4);
            conversation2.SetFriendId(0);
            conversation2.SetGroupId(100);

            conversationList.push_back(conversation);
            conversationList.push_back(conversation1);
            conversationList.push_back(conversation2);
            chat.deleteConversation(userid, conversationList);
        }
        else if (type == 163){
            std::vector<imsdk::ConversationDTO> conversationList;
            imsdk::ConversationDTO conversation;;
            UserIdentity friendId = 0;
            GroupIdentity groupId = 0;
            std::cin >> friendId >> groupId;
            if (friendId == 0){
                conversation.SetConversationType(4);
                conversation.SetFriendId(friendId);
                conversation.SetGroupId(groupId);
            }
            else{
                conversation.SetConversationType(3);
                conversation.SetFriendId(friendId);
                conversation.SetGroupId(groupId);
            }
            conversationList.push_back(conversation);
            chat.markConversationSeen(userid, conversationList);
        }
        else if (type == 62) {
            UserIdentity friendId;
            int mediaType{ 0 };
            std::string filePath = "/home/towhid/ringid/test_audio.mp3";
            std::string caption;
            int widthOrFileSize;
            int heightOrDuration;

            std::cin >> friendId >> mediaType;

            if (mediaType == 7) { // chat_image_from_gallery
                widthOrFileSize = 640;
                heightOrDuration = 640;
                caption = "GALLERY_IMAGE_CAPTION";
                filePath = "/home/towhid/ringid/test_image_small.jpg";
            }
            else if (mediaType == 8) { // chat_audio
                widthOrFileSize = 1000;
                heightOrDuration = 14;
                caption = "AUDIO_CAPTION";
                filePath = "/home/towhid/ringid/test_audio.mp3";
            }
            else if (mediaType == 9) { // chat_video
                widthOrFileSize = 1000;
                heightOrDuration = 4;
                caption = "VIDEO_CAPTION";
                filePath = "/home/towhid/ringid/test_video.mp4";
            }
            else if (mediaType == 10) { //chat_image_from_camera
                widthOrFileSize = 640;
                heightOrDuration = 640;
                caption = "CAMERA_IMAGE_CAPTION";
                filePath = "/home/towhid/ringid/upload/test_image_small.jpg";
            }
            std::string packetId = chat.generatePacketId().packetId;
            chunk_transfer_packet_id = packetId;
            chat.sendFriendChatMedia(userid, friendId, packetId, mediaType, filePath, caption, widthOrFileSize, heightOrDuration, secretTimeout, 1213, false);
        }
        else if (type == 63){
            imsdk::ApiStatus apiStatus = chat.sendFriendChat(chunk_transfer_packet_id, userid, chat_media_friend_id, chat_media_msg_type, secretTimeout, chat_media_manifest_url, gettime(), true);
        }
        else if (type == 64){
            bool ret = chat.downloadFriendChatMedia(userid, chat_media_friend_id, chunk_transfer_packet_id, chat_media_manifest_url, chat_media_msg_type, secretTimeout);
            if (ret) {
                std::cout << "Friend chat media download request accepted" << std::endl;
            }
            else {
                std::cout << "Friend chat media download request failed" << std::endl;
            }
        }
        else if (type == 65){
            chat.acceptChatMedia(chunk_transfer_packet_id);
        }
        else if (type == 66) {
            GroupIdentity groupId;
            int mediaType{ 0 };
            std::string filePath = "/home/towhid/ringid/test_audio.mp3";
            std::string caption;
            int widthOrFileSize;
            int heightOrDuration;

            std::cin >> groupId >> mediaType;

            if (mediaType == 7) { // chat_image_from_gallery
                widthOrFileSize = 640;
                heightOrDuration = 640;
                caption = "GALLERY_IMAGE_CAPTION";
                filePath = "/home/towhid/ringid/test_image_small.jpg";
            }
            else if (mediaType == 8) { // chat_audio
                widthOrFileSize = 1000;
                heightOrDuration = 14;
                caption = "AUDIO_CAPTION";
                filePath = "/home/towhid/ringid/test_audio.mp3";
            }
            else if (mediaType == 9) { // chat_video
                widthOrFileSize = 1000;
                heightOrDuration = 4;
                caption = "VIDEO_CAPTION";
                filePath = "/home/towhid/ringid/test_video.mp4";
            }
            else if (mediaType == 10) { //chat_image_from_camera
                widthOrFileSize = 640;
                heightOrDuration = 640;
                caption = "CAMERA_IMAGE_CAPTION";
                filePath = "/home/towhid/ringid/upload/test_image_small.jpg";
            }
            std::string packetId = chat.generatePacketId().packetId;
            chunk_transfer_packet_id = packetId;
            chat.sendGroupChatMedia(groupId, packetId, mediaType, filePath, caption, widthOrFileSize, heightOrDuration, 1213);
        }
        else if (type == 67){
            imsdk::ApiStatus apiStatus = chat.sendGroupChat(chunk_transfer_packet_id, chat_media_group_id, chat_media_msg_type, chat_media_manifest_url, 0);
        }
        else if (type == 68){
            bool ret = chat.downloadGroupChatMedia(chat_media_group_id, chat_media_friend_id, chunk_transfer_packet_id, chat_media_manifest_url, chat_media_msg_type);
            if (ret) {
                std::cout << "Group chat media download request accepted" << std::endl;
            }
            else {
                std::cout << "Group chat media download request failed" << std::endl;
            }
        }
        else if (type == 69) {
            bool upload;
            std::string msg;
            if (userid == 1){
                upload = true;
                msg = "Pending upload list: ";
            }
            else if (userid == 2){
                upload = false;
                msg = "Pending download list: ";
            }
            imsdk::ConversationType conversationType;
            int cnvType;

            std::cin >> cnvType;

            if (cnvType == 1){
                conversationType = imsdk::ConversationType::FRIEND_ID;
            }
            else if (cnvType == 2){
                conversationType = imsdk::ConversationType::GROUP_ID;
            }
            std::vector<std::string> pendingFriendChatMediaList = chat.getPendingChatMediaList(conversationType, upload, false);
            std::cout << msg << std::endl;
            for (int i = 0; i < pendingFriendChatMediaList.size(); i++) {
                std::cout << "pkt_id: " << pendingFriendChatMediaList[i] << std::endl;
            }
        }
        else if (type == 71)
        {
            chat.cancelChatMediaTransfer(chunk_transfer_packet_id);
        }
        else if (type == 72)
        {
            bool inProgress = chat.isChatMediaTransferInProgress(chunk_transfer_packet_id);
            if (inProgress) {
                std::cout << "IN PROGESS | packetId: " << chunk_transfer_packet_id << std::endl;
            }
            else {
                std::cout << "NOT IN PROGRESS" << std::endl;
            }
        }
        else if (type == 73)
        {
            std::string packetId = chat.generatePacketId().packetId;
            UserIdentity blockedUserId;
            std::cin >> blockedUserId;
            chat.blockUserFromLiveStreamChat(blockedUserId, packetId);
        }
        else if (type == 74)
        {
            UserIdentity friendId;
            std::string message;

            std::cin >> friendId >> message;

            imsdk::PacketTimeId packetTimeId = chat.generatePacketId();
            chat.sendFriendCallLogMessage(userid, friendId, message, 0, packetTimeId.packetId);
        }
        else if (type == 75)
        {
            std::string key, message, decryptedMessage;

            key = "a2b2";
            message = "$hello$";

            imsdk::ByteArray keyBytes(key);
            imsdk::ByteArray messageBytes(message);
            int startIndex = 2;
            imsdk::ByteArray encryptedMessageBytes = ipvsdk::security::DataEncryption::encryptMessage(messageBytes, keyBytes, startIndex);

            imsdk::ByteArray decryptedMessageBytes = ipvsdk::security::DataEncryption::decryptMessage(encryptedMessageBytes, keyBytes, startIndex);

            decryptedMessage = std::string((const char *)decryptedMessageBytes.getDataPtr(), decryptedMessageBytes.size());//decryptedMessageBytes.toString();

            std::cout << "Original Message: " << message << std::endl;
            std::cout << "Original Message Bytes: " << messageBytes.toString() << std::endl;
            std::cout << "Encrypted Message Bytes: " << encryptedMessageBytes.toString() << std::endl;
            std::cout << "Decrypted Message Bytes: " << decryptedMessageBytes.toString() << std::endl;
            std::cout << "Decrypted Message: " << decryptedMessage << std::endl;
        }
        else if (type == 76)
        {
            std::string serverAddr = "192.168.1.163";
            std::string sessionlessKey = ipvsdk::security::DataEncryption::getSessionlessKey(serverAddr, 10013235);
            std::cout << "SESSION LESS KEY: " << sessionlessKey << std::endl;
        }
        else if (type == 77) {
            UserIdentity friendId;
            std::cin >> friendId;
            chat.unregisterFriendChat(userid, friendId, 2, 1);
        }
        else if (type == 100)
        {
            chat.setLogEnabled(false);
        }
        else if (type == 101)
        {
            UserIdentity publisherId;
            std::string fullName;
            std::cin >> publisherId >> fullName;
            chat.registerLiveStreamChat(publisherId, serverAddress, 1500, fullName);
        }
        else if (type == 102)
        {
            UserIdentity publisherId;
            std::cin >> publisherId;
            std::string packetId = chat.generatePacketId().packetId, message = "hello";
            chat.sendLiveStreamChat(packetId, publisherId, 2, message, 0);
        }
        else if (type == 103)
        {
            chat.typingLiveStreamChat(100);
        }
        else if (type == 104){
            long long serverSyncTime = chat.getCurrentServerSyncedTime();
            std::cout << "Current server sync time: " << serverSyncTime << std::endl;
        }
        else if (type == 105)
        {
            std::cout << "Generated groupId: " << chat.generateGroupId() << std::endl;
        }
        else if (type == 106)
        {
            chat.updateUserPassword("");
        }




        /*--------------------------------------------*/

        else if (type == 9001) // check sha1
        {
            std::cout << "Hashed string: " << ipvsdk::security::HashAlgorithm::sha1("sample string") << std::endl;
        }

        else if (type == 9002) // lock_guard of dupicate checker
        {
            //duplicateChecker_task1();

            std::thread t1(duplicateChecker_task1);
            std::thread t2(duplicateChecker_task2);

            t1.join();
            t2.join();

        }

        else if (type == 9003) // startservice check
        {
            chat.stopServices();

            std::thread t1(checkStartServicesCall_task1);
            std::thread t2(checkStartServicesCall_task2);
            std::thread t3(checkStartServicesCall_task3);

            t1.join();
            t2.join();
            t3.join();
        }


        //        menu();
    }


    std::this_thread::sleep_for(std::chrono::seconds(300));

    return (EXIT_SUCCESS);
}

