/* 
 * File:   ChatPacketBuilder.cpp
 * Author: dipal
 * 
 * Created on September 2, 2015, 4:44 PM
 */

#include "ChatPacketBuilder.h"
#include "ResourceManager.h"
#include<set>

namespace imsdk {
ChatPacketBuilder::ChatPacketBuilder() {
    parser = std::make_shared<ChatParser>();
}

ChatPacketBuilder::~ChatPacketBuilder() {
}

BuiltPacket ChatPacketBuilder::makeActivateOrDeactivateUserPacket(UserIdentity userId, std::string &packetID, bool isActivate, int platform) {
	std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(ACTIVATE_DEACTIVATE_USER_ACCOUNT);
	packetDTO->setUserIdentity(userId);
    packetDTO->setPacketID(packetID);
    packetDTO->setIsActivateUserAccount(isActivate);
    packetDTO->setDevice(platform);

	return{ parser->parse(packetDTO), packetDTO };
}

BuiltPacket ChatPacketBuilder::makeGetUserInfoPacket(UserIdentity userId, UserIdentity friendId, std::string &packetID, int platform) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GET_USER_INFO);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setDevice(platform);

    return{ parser->parse(packetDTO), packetDTO };
}

BuiltPacket ChatPacketBuilder::makeFriendRegister(UserIdentity userId, UserIdentity friendId, std::string &packetID, int platform, int appversion, int appType, UserIdentity pageOwnerId) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_REGISTER);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setDevice(platform);
    packetDTO->setAppVersion(appversion);
	packetDTO->setAppType(appType);
    packetDTO->setPageOwnerId(pageOwnerId);
    packetDTO->setAuthSessionID(ResourceManager::getInstance().getAuthSessionID());
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendUnregister(UserIdentity userId, UserIdentity friendId, std::string &packetID, int onlineStatus, int onlineMood) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_UNREGISTER);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setOnlineStatus(onlineStatus);
    packetDTO->setOnlineMood(onlineMood);
    packetDTO->setAuthSessionID(ResourceManager::getInstance().getAuthSessionID());

    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makefriendregisterconfirmation(UserIdentity userId, UserIdentity friendId, std::string &packetID, int chatBindingPort, long long serverDate) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_REGISTER_CONFIRMATION);
	packetDTO->setFriendIdentity(userId);
	packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setChatBindingPort(chatBindingPort);
    packetDTO->setServerDate(serverDate);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendChatIdel(UserIdentity userId, UserIdentity friendId, int platform) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_IDEL);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setDevice(platform);
    packetDTO->setAuthSessionID(ResourceManager::getInstance().getAuthSessionID());

    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendChatMessageTyping(UserIdentity userId, UserIdentity friendId, int platform, std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_MESSAGE_TYPING);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setDevice(platform);
    packetDTO->setPacketID(packetID);
    packetDTO->setAuthSessionID(ResourceManager::getInstance().getAuthSessionID());

    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendChatMessage(UserIdentity userId, UserIdentity friendId, std::string &packetID, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform, int appversion, int appType, UserIdentity pageOwnerId) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_MESSAGE);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setMessageType(messageType);
    packetDTO->setTimeout(timeout);
    packetDTO->setMessage(message);
    packetDTO->setMessageDate(messageDate);
    packetDTO->setIsSecretVisible(isSecretVisible);
    packetDTO->setDevice(platform);
    packetDTO->setAppVersion(appversion);
	packetDTO->setAppType(appType);
	packetDTO->setPageOwnerId(pageOwnerId);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendCallBusyMessage(UserIdentity userId, UserIdentity friendId, std::string &packetID, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CALL_BUSY_MESSAGE);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setMessageType(messageType);
    packetDTO->setTimeout(timeout);
    packetDTO->setMessage(message);
    packetDTO->setMessageDate(messageDate);
    packetDTO->setIsSecretVisible(isSecretVisible);
    packetDTO->setDevice(platform);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendChatMessageEdit(UserIdentity userId, UserIdentity friendId, std::string &packetID, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform, int appversion, int appType, UserIdentity pageOwnerId) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_MESSAGE_EDIT);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setMessageType(messageType);
    packetDTO->setTimeout(timeout);
    packetDTO->setMessage(message);
    packetDTO->setMessageDate(messageDate);
    packetDTO->setIsSecretVisible(isSecretVisible);
    packetDTO->setDevice(platform);
    packetDTO->setAppVersion(appversion);
	packetDTO->setAppType(appType);
	packetDTO->setPageOwnerId(pageOwnerId);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGenerateEncryptedPacketInformation(UserIdentity userID, UserIdentity friendID, std::string &packetID, int type, int informationType, std::string &information)
{
	std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
	packetDTO->setPacketType(GENERAL_ENCRYPTED_PACKET);
	packetDTO->setUserIdentity(userID);
	packetDTO->setFriendIdentity(friendID);
	packetDTO->setPacketID(packetID);
	packetDTO->setType(type);
	packetDTO->setInformationType(informationType);
	packetDTO->setInformation(information);

	return{ parser->parse(packetDTO), packetDTO };
}

BuiltPacket ChatPacketBuilder::makeGeneralEncryptedPacketConfirmation(UserIdentity userID, UserIdentity friendID, std::string &packetID, int type, int informationType)
{
	std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
	packetDTO->setPacketType(GENERAL_ENCRYPTED_CONFIRMATION);
	packetDTO->setUserIdentity(userID);
	packetDTO->setFriendIdentity(friendID);
	packetDTO->setPacketID(packetID);
	packetDTO->setType(type);
	packetDTO->setInformationType(informationType);

	return{ parser->parse(packetDTO), packetDTO };
}

BuiltPacket ChatPacketBuilder::makeFriendChatMessageBroken(UserIdentity userId, UserIdentity friendId, std::string &packetID, int totalNumberOfPackets, int sequenceNumber, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform, int appversion, int appType, UserIdentity pageOwnerId) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_MESSAGE_BROKEN);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setNumberOfMessage(totalNumberOfPackets);
    packetDTO->setSequenceNumber(sequenceNumber);
    packetDTO->setMessageType(messageType);
    packetDTO->setTimeout(timeout);
    packetDTO->setMessage(message);
    packetDTO->setMessageDate(messageDate);
    packetDTO->setIsSecretVisible(isSecretVisible);
    packetDTO->setDevice(platform);
    packetDTO->setAppVersion(appversion);
	packetDTO->setAppType(appType);
	packetDTO->setPageOwnerId(pageOwnerId);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendChatMessageBrokenEdit(UserIdentity userId, UserIdentity friendId, std::string &packetID, int totalNumberOfPackets, int sequenceNumber, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform, int appversion, int appType, UserIdentity pageOwnerId) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_MESSAGE_BROKEN_EDIT);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setNumberOfMessage(totalNumberOfPackets);
    packetDTO->setSequenceNumber(sequenceNumber);
    packetDTO->setMessageType(messageType);
    packetDTO->setTimeout(timeout);
    packetDTO->setMessage(message);
    packetDTO->setMessageDate(messageDate);
    packetDTO->setIsSecretVisible(isSecretVisible);
    packetDTO->setDevice(platform);
    packetDTO->setAppVersion(appversion);
	packetDTO->setAppType(appType);
	packetDTO->setPageOwnerId(pageOwnerId);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendChatMessageAnonymous(UserIdentity userId, UserIdentity friendId, std::string &packetID, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform, long long originalUserId) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_MESSAGE_ANONYMOUS);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setMessageType(messageType);
    packetDTO->setTimeout(timeout);
    packetDTO->setMessage(message);
    packetDTO->setMessageDate(messageDate);
    packetDTO->setIsSecretVisible(isSecretVisible);
    packetDTO->setDevice(platform);
    packetDTO->setOriginalUserId(originalUserId);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendChatMessageEditAnonymous(UserIdentity userId, UserIdentity friendId, std::string &packetID, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform, long long originalUserId) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_MESSAGE_EDIT_ANONYMOUS);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setMessageType(messageType);
    packetDTO->setTimeout(timeout);
    packetDTO->setMessage(message);
    packetDTO->setMessageDate(messageDate);
    packetDTO->setIsSecretVisible(isSecretVisible);
    packetDTO->setDevice(platform);
    packetDTO->setOriginalUserId(originalUserId);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendChatMessageBrokenAnonymous(UserIdentity userId, UserIdentity friendId, std::string &packetID, int totalNumberOfPackets, int sequenceNumber, int messageType, int timeout, std::string &message, long long messageDate, bool isSecretVisible, int platform, long long originalUserId) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_MESSAGE_BROKEN_ANONYMOUS);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setNumberOfMessage(totalNumberOfPackets);
    packetDTO->setSequenceNumber(sequenceNumber);
    packetDTO->setMessageType(messageType);
    packetDTO->setTimeout(timeout);
    packetDTO->setMessage(message);
    packetDTO->setMessageDate(messageDate);
    packetDTO->setIsSecretVisible(isSecretVisible);
    packetDTO->setDevice(platform);
    packetDTO->setOriginalUserId(originalUserId);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendChatMessageBrokenEditAnonymous(UserIdentity userId, UserIdentity friendId,  std::string &packetID, int totalNumberOfPackets, int sequenceNumber, int messageType, int timeout,  std::string &message, long long messageDate, bool isSecretVisible, int platform, long long originalUserId) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_MESSAGE_BROKEN_EDIT_ANONYMOUS);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setNumberOfMessage(totalNumberOfPackets);
    packetDTO->setSequenceNumber(sequenceNumber);
    packetDTO->setMessageType(messageType);
    packetDTO->setTimeout(timeout);
    packetDTO->setMessage(message);
    packetDTO->setMessageDate(messageDate);
    packetDTO->setIsSecretVisible(isSecretVisible);
    packetDTO->setDevice(platform);
    packetDTO->setOriginalUserId(originalUserId);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendChatMultipleMessage(UserIdentity userId, UserIdentity friendId,  std::string &packetID, std::vector<std::shared_ptr< PacketDTO>> &messageList) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_MULTIPLE_MESSAGE);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setMessageList(messageList);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeUserPasswordUpdateRequest(UserIdentity userId, std::string &packetID)
{
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(USER_PASSWORD_UPDATE);
    packetDTO->setUserIdentity(userId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendChatMessageDelivered(UserIdentity userId, UserIdentity friendId,  std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_MESSAGE_DELIVERED);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendChatMessageSent(UserIdentity userId, UserIdentity friendId,  std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_MESSAGE_SENT);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendChatMessageSeen(UserIdentity userId, UserIdentity friendId,  std::string &packetID, std::vector<SeenPacketDTO> &seenPacketDTOList) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_MESSAGE_SEEN);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setSeenMessageList(seenPacketDTOList);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendChatMessageSeenConfirmation(UserIdentity userId, UserIdentity friendId,  std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_MESSAGE_SEEN_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendChatMultipleMessageDelete(UserIdentity userId, UserIdentity friendId, std::string &packetID, std::vector<std::string> &packetIds, int platform, int deleteType) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_MULTIPLE_MESSAGE_DELETE);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setPacketIDs(packetIds);
    packetDTO->setDevice(platform);
    packetDTO->setMessageDeleteType(deleteType);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendChatMessageDeleteConfirmation(UserIdentity userId, UserIdentity friendId,  std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_CHAT_MESSAGE_DELETE_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendBrokenPacket(UserIdentity userId, UserIdentity friendId,  std::string &packetID, int totalNumberOfPackets, int sequenceNumber, std::shared_ptr< ByteArray> &dataBytes) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_BROKEN_PACKET);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setNumberOfMessage(totalNumberOfPackets);
    packetDTO->setSequenceNumber(sequenceNumber);
    packetDTO->setDataBytes(dataBytes);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendBrokenPacketConfirmation(UserIdentity userId, UserIdentity friendId,  std::string &packetID, int sequenceNumber) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_BROKEN_PACKET_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setSequenceNumber(sequenceNumber);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendBlock(UserIdentity userId, UserIdentity friendId,  std::string &packetID, long long blockUnblockDate, bool isAddToBlock) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_BLOCK);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setBlockUnblockDate(blockUnblockDate);
    packetDTO->setIsAddToBlock(isAddToBlock);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendUnblock(UserIdentity userId, UserIdentity friendId,  std::string &packetID, long long blockUnblockDate) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_UNBLOCK);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setBlockUnblockDate(blockUnblockDate);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeFriendBlockUnblockConfirmation(UserIdentity userId, UserIdentity friendId,  std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(FRIEND_BLOCK_UNBLOCK_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

//BuiltPacket ChatPacketBuilder::makeFriendFileStreamRequest(UserIdentity userId, UserIdentity friendId, std::string &packetId, long long fileId) {
//    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
//    packetDTO->setPacketType(FRIEND_FILE_STREAM_REQUEST);
//    packetDTO->setUserIdentity(userId);
//    packetDTO->setFriendIdentity(friendId);
//    packetDTO->setPacketID(packetId);
//    packetDTO->setFileIdentity(fileId);
//    
//    return {parser->parse(packetDTO), packetDTO};
//}
//
//BuiltPacket ChatPacketBuilder::makeFriendFileStreamRequestConfirmation(UserIdentity userId, UserIdentity friendId, std::string &packetId, long long fileId) {
//    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
//    packetDTO->setPacketType(FRIEND_FILE_STREAM_REQUEST_CONFIRMATION);
//    packetDTO->setUserIdentity(userId);
//    packetDTO->setFriendIdentity(friendId);
//    packetDTO->setPacketID(packetId);
//    packetDTO->setFileIdentity(fileId);
//    
//    return {parser->parse(packetDTO), packetDTO};
//}
//
//BuiltPacket ChatPacketBuilder::makeFriendFileStreamSend(UserIdentity userId, UserIdentity friendId, std::string &packetId, long long fileId) {
//    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
//    packetDTO->setPacketType(FRIEND_FILE_STREAM_SEND);
//    packetDTO->setUserIdentity(userId);
//    packetDTO->setFriendIdentity(friendId);
//    packetDTO->setPacketID(packetId);
//    packetDTO->setFileIdentity(fileId);
//    
//    return {parser->parse(packetDTO), packetDTO};
//}
//
//BuiltPacket ChatPacketBuilder::makeFriendFileStreamSendConfirmation(UserIdentity userId, UserIdentity friendId, std::string &packetId, long long fileId, int fileTrasferPort) {
//    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
//    packetDTO->setPacketType(FRIEND_FILE_STREAM_SEND_CONFIRMATION);
//    packetDTO->setUserIdentity(userId);
//    packetDTO->setFriendIdentity(friendId);
//    packetDTO->setPacketID(packetId);
//    packetDTO->setFileIdentity(fileId);
//    packetDTO->setFileTransferPort(fileTrasferPort);
//    
//    return {parser->parse(packetDTO), packetDTO};
//}

BuiltPacket ChatPacketBuilder::makeGroupRegister(UserIdentity userId, long long groupId,  std::string &packetID, int platform, int appversion) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_REGISTER);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setDevice(platform);
    packetDTO->setAppVersion(appversion);
    packetDTO->setAuthSessionID(ResourceManager::getInstance().getAuthSessionID());

    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupUnregister(UserIdentity userId, long long groupId,  std::string &packetID, int onlineStatus, int onlineMood) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_UNREGISTER);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setOnlineStatus(onlineStatus);
    packetDTO->setOnlineMood(onlineMood);
    packetDTO->setAuthSessionID(ResourceManager::getInstance().getAuthSessionID());

    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupRegisterConfirmation(long long groupId,  std::string &packetID, int chatBindingPort, long long serverDate) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_REGISTER_CONFIRMATION);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setChatBindingPort(chatBindingPort);
    packetDTO->setServerDate(serverDate);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupInformation(UserIdentity userId, long long groupId, std::string &packetID, int activityType, std::string &groupNameOrUrl) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_INFORMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    
    packetDTO->setGroupActivityType(activityType);
    
    if (activityType ==  GROUP_NAME_CHANGE)
    {
        packetDTO->setGroupName(groupNameOrUrl);
    }
    else if (activityType == GROUP_URL_CHANGE)
    {
        packetDTO->setGroupUrl(groupNameOrUrl);
    }
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupInformationConfirmation(UserIdentity userId, long long groupId,  std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_INFORMATION_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupMemberAdd(UserIdentity userId, long long groupId,  std::string &packetID, std::vector<MemberDTO> &memberList) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_MEMBER_ADD);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setMemberList(memberList);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupMemberAddConfirmation(UserIdentity userId, long long groupId,  std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_MEMBER_ADD_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupMemberRemoveLeave(UserIdentity userId, long long groupId, std::string &packetID, std::vector<MemberDTO> &memberList, int leaveType) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_MEMBER_REMOVE_LEAVE);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setMemberList(memberList);
    packetDTO->setGroupLeaveType(leaveType);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupMemberRemoveLeaveConfirmation(UserIdentity userId, long long groupId, std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_MEMBER_REMOVE_LEAVE_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupMemberTypeChange(UserIdentity userId, long long groupId,  std::string &packetID, std::vector<MemberDTO> &memberList) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_MEMBER_TYPE_CHANGE);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setMemberList(memberList);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupMemberTypeChangeConfirmation(UserIdentity userId, long long groupId,  std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_MEMBER_TYPE_CHANGE_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupChatIdel(UserIdentity userId, long long groupId, int platform) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_CHAT_IDEL);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setDevice(platform);
    packetDTO->setAuthSessionID(ResourceManager::getInstance().getAuthSessionID());

    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupChatMessageTyping(UserIdentity userId, long long groupId, int platform, std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_CHAT_MESSAGE_TYPING);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setDevice(platform);
    packetDTO->setPacketID(packetID);
    packetDTO->setAuthSessionID(ResourceManager::getInstance().getAuthSessionID());

    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupChatMessage(UserIdentity userId, long long groupId,  std::string &packetID, int messageType,  std::string &message, long long messageDate) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_CHAT_MESSAGE);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setMessageType(messageType);
    packetDTO->setMessage(message);
    packetDTO->setMessageDate(messageDate);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupChatMessageEdit(UserIdentity userId, long long groupId,  std::string &packetID, int messageType,  std::string &message, long long messageDate) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_CHAT_MESSAGE_EDIT);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setMessageType(messageType);
    packetDTO->setMessage(message);
    packetDTO->setMessageDate(messageDate);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupChatMessageBroken(UserIdentity userId, long long groupId,  std::string &packetID, int totalNumberOfPackets, int sequenceNumber, int messageType,  std::string &message, long long messageDate) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_CHAT_MESSAGE_BROKEN);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setNumberOfMessage(totalNumberOfPackets);
    packetDTO->setSequenceNumber(sequenceNumber);
    packetDTO->setMessageType(messageType);
    packetDTO->setMessage(message);
    packetDTO->setMessageDate(messageDate);    
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupChatMessageBrokenEdit(UserIdentity userId, long long groupId,  std::string &packetID, int totalNumberOfPackets, int sequenceNumber, int messageType,  std::string &message, long long messageDate) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_CHAT_MESSAGE_BROKEN_EDIT);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setNumberOfMessage(totalNumberOfPackets);
    packetDTO->setSequenceNumber(sequenceNumber);
    packetDTO->setMessageType(messageType);
    packetDTO->setMessage(message);
    packetDTO->setMessageDate(messageDate);    
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupChatMultipleMessage() {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_CHAT_MULTIPLE_MESSAGE);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupChatMessageDelivered(UserIdentity userId, UserIdentity friendId, long long groupId,  std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_CHAT_MESSAGE_DELIVERED);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupChatMessageSent(long long groupId,  std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_CHAT_MESSAGE_SENT);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupChatMessageSeen(UserIdentity userId, long long groupId,  std::string &packetID, std::vector<std::string> &packetIds) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_CHAT_MESSAGE_SEEN);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setPacketIDs(packetIds);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupChatMessageSeenConfirmation(UserIdentity userId, long long groupId, std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_CHAT_MESSAGE_SEEN_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupChatGetMessageSeenListRequest(UserIdentity userId, long long groupId, std::string &newPacketID, std::string actualPacketId, int platform){
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_CHAT_GET_MESSAGE_SEEN_LIST_REQUEST);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(newPacketID);
    packetDTO->setOriginalPacketID(actualPacketId);
    packetDTO->setDevice(platform);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupChatMessageSeenListConfirmation(UserIdentity userId, long long groupId, std::string &packetID){
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_CHAT_MESSAGE_SEEN_LIST_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupChatMultipleMessageDelete(UserIdentity userId, long long groupId,  std::string &packetID, std::vector<std::string> &packetIds) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_CHAT_MULTIPLE_MESSAGE_DELETE);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setPacketIDs(packetIds);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupChatMessageDeleteConfirmation(UserIdentity userId, long long groupId, std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_CHAT_MESSAGE_DELETE_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeGroupBrokenPacketConfirmation(UserIdentity userId, long long groupId,  std::string &packetID, int sequenceNumber) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(GROUP_BROKEN_PACKET_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setSequenceNumber(sequenceNumber);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineFriendInformation(UserIdentity userId, UserIdentity friendId, std::string &packetID, std::string &fullName, int friendPlatform, int onlineStatus, int friendApptType, std::string &friendDeviceToken, int onlineMood, int iosVoipPush, int selfPlatform, int profileType, int friendProfileType) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_FRIEND_INFORMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setFullName(fullName);
    packetDTO->setFriendDevice(friendPlatform);
    packetDTO->setOnlineStatus(onlineStatus);
    packetDTO->setAppType(friendApptType);
    packetDTO->setFriendDeviceToken(friendDeviceToken);
    packetDTO->setOnlineMood(onlineMood);
    packetDTO->setIosVoipPush(iosVoipPush);
    packetDTO->setDevice(selfPlatform);
    packetDTO->setProfileType(profileType);
    packetDTO->setFriendProfileType(friendProfileType);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineFriendInformationConfirmation(UserIdentity friendId, std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_FRIEND_INFORMATION_CONFIRMATION);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

    BuiltPacket ChatPacketBuilder::makeOfflineGetRequest(UserIdentity userId, std::string &packetID, long long groupUpdateDate, long long blockUpdateDate, int appVersion, int platform, int appType, std::set<UserIdentity> &pageIdList) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_GET_REQUEST);
    packetDTO->setUserIdentity(userId);
    packetDTO->setPacketID(packetID);
    packetDTO->setGroupUpdateDate(groupUpdateDate);
    packetDTO->setBlockUnblockDate(blockUpdateDate);
    packetDTO->setAppVersion(appVersion);
    packetDTO->setDevice(platform);
    packetDTO->setAppType(appType);
        packetDTO->setPageIdList(pageIdList);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineGetRequestConfirmation(std::string &packetID, long long serverDate) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_GET_REQUEST_CONFIRMATION);
    packetDTO->setPacketID(packetID);
    packetDTO->setServerDate(serverDate);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineFriendUnreadMessage(std::string &packetID, UserIdentity userID, std::vector<std::shared_ptr< PacketDTO> > &messageList) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_FRIEND_UNREAD_MESSAGE);
	packetDTO->setPacketID(packetID);
	packetDTO->setUserIdentity(userID);
    packetDTO->setMessageList(messageList);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineFriendUnreadMessageConfirmation(UserIdentity userId, std::string &packetID, std::vector<std::string> &packeIds) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_FRIEND_UNREAD_MESSAGE_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setPacketID(packetID);
    packetDTO->setPacketIDs(packeIds);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineFriendHistoryMessageRequest(UserIdentity userId, UserIdentity friendId, std::string &packetID, int upDownStatus, int limit, int platform, int appType, int appVersion, UserIdentity pageOwnerId) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_FRIEND_HISTORY_MESSAGE_REQUEST);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setUpDownStatus(upDownStatus);
    packetDTO->setLimit(limit);
    packetDTO->setDevice(platform);
    packetDTO->setAppType(appType);
	packetDTO->setAppVersion(appVersion);
	packetDTO->setPageOwnerId(pageOwnerId);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineFriendHistoryMessage(UserIdentity friendId, std::string &packetID, std::vector<std::shared_ptr< PacketDTO> > &messageList) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_FRIEND_HISTORY_MESSAGE);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setMessageList(messageList);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineFriendHistoryMessageConfirmation(UserIdentity friendId, std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_FRIEND_HISTORY_MESSAGE_CONFIRMATION);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineGetFriendMessgaeStatus(UserIdentity userId, UserIdentity friendId, std::string &packetID, std::vector<std::string> &packetIds) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_GET_FRIEND_MESSGAE_STATUS);
    packetDTO->setUserIdentity(userId);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setPacketIDs(packetIds);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineGetFriendMessgaeStatusConfirmation(UserIdentity friendId, std::string &packetID, std::vector<FriendMessageStatusDTO> &friendMessageStatusList) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_GET_FRIEND_MESSGAE_STATUS_CONFIRMATION);
    packetDTO->setFriendIdentity(friendId);
    packetDTO->setPacketID(packetID);
    packetDTO->setFriendMessageStatusDTOList(friendMessageStatusList);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineMyGroupList(std::string &packetID, std::vector<GroupDTO> &groupDTOList) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_MY_GROUP_LIST);
    packetDTO->setPacketID(packetID);
    packetDTO->setGroupDTOList(groupDTOList);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineGroupUnreadMessageConfirmation(UserIdentity userId, std::string &packetID, std::vector<std::string> &packetIds) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_GROUP_UNREAD_MESSAGE_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setPacketID(packetID);
    packetDTO->setPacketIDs(packetIds);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineCreateGroup(UserIdentity userId, long long groupId, std::string &packetID, std::string &groupName, std::string &groupUrl, std::vector<MemberDTO> &memberList) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_CREATE_GROUP);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setGroupName(groupName);
    packetDTO->setGroupUrl(groupUrl);
    packetDTO->setMemberList(memberList);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineCreateGroupConfirmation(long long groupId, std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_CREATE_GROUP_CONFIRMATION);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineGroupHistoryMessageRequest(UserIdentity userId, long long groupId, std::string &packetID, int upDownStatus, int limit, int appVersion) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_GROUP_HISTORY_MESSAGE_REQUEST);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setUpDownStatus(upDownStatus);
    packetDTO->setLimit(limit);
    packetDTO->setAppVersion(appVersion);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineGroupHistoryMessage(long long groupId, std::string &packetID, std::vector<std::shared_ptr< PacketDTO>> &messageList) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_GROUP_HISTORY_MESSAGE);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setMessageList(messageList);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineGetInformationWithMembers(UserIdentity userId, long long groupId, std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_GET_INFORMATION_WITH_MEMBERS);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineInformationWithMembers(long long groupId, std::string &packetID, std::string &groupName, std::string &groupUrl, std::vector<MemberDTO> &memberList) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_INFORMATION_WITH_MEMBERS);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    packetDTO->setGroupName(groupName);
    packetDTO->setGroupUrl(groupUrl);
    packetDTO->setMemberList(memberList);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineGroupConfirmation(long long groupId, std::string &packetID) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_GROUP_CONFIRMATION);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetID);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineBrokenHistoryPacket(std::string &packetID, int numberOfPackets, int sequenceNumber, std::shared_ptr< ByteArray> dataBytes) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_BROKEN_HISTORY_PACKET);
    packetDTO->setPacketID(packetID);
    packetDTO->setNumberOfMessage(numberOfPackets);
    packetDTO->setSequenceNumber(sequenceNumber);
    packetDTO->setDataBytes(dataBytes);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineBrokenPacket(std::string &packetID, int numberOfPackets, int sequenceNumber, std::shared_ptr< ByteArray> dataBytes) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_BROKEN_PACKET);
    packetDTO->setPacketID(packetID);
    packetDTO->setNumberOfMessage(numberOfPackets);
    packetDTO->setSequenceNumber(sequenceNumber);
    packetDTO->setDataBytes(dataBytes);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineBrokenPacketConfirmation(UserIdentity userId, std::string &packetID, int sequenceNumber) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_BROKEN_PACKET_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setPacketID(packetID);
    packetDTO->setSequenceNumber(sequenceNumber);
    
    return {parser->parse(packetDTO), packetDTO};
    }

    BuiltPacket ChatPacketBuilder::makeRoomBrokenPacketConfirmation(UserIdentity userId, RoomIdentity &roomId, std::string &packetID, int sequenceNumber) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(ROOM_BROKEN_PACKET_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setRoomId(roomId);
    packetDTO->setPacketID(packetID);
    packetDTO->setSequenceNumber(sequenceNumber);
    
    return {parser->parse(packetDTO), packetDTO};
    }
    
BuiltPacket ChatPacketBuilder::makeOfflineGetConversationList(UserIdentity userId, std::string &packetID, int startIndex, int limit, int conversationType, long long friendOrGroupId, int platform, int appVersion) {
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_GET_CONVERSATION_REQUEST);
    packetDTO->setUserIdentity(userId);
    packetDTO->setPacketID(packetID);
    packetDTO->setStartIndex(startIndex);
    packetDTO->setLimit(limit);
    packetDTO->setConversationType(conversationType);
    packetDTO->setFriendOrGroupId(friendOrGroupId);
    packetDTO->setDevice(platform);
    packetDTO->setAppVersion(appVersion);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineDeleteConversationRequest(UserIdentity userId, std::string &packetId, std::vector<ConversationDTO> &conversationList, int platform)
{
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(DELETE_CONVERSATION_REQUEST);
    packetDTO->setUserIdentity(userId);
    packetDTO->setPacketID(packetId);
    packetDTO->setConversationList(conversationList);
    packetDTO->setDevice(platform);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineMarkConversationSeenRequest(UserIdentity userId, std::string &packetId, std::vector<ConversationDTO> &conversationList, int platform)
{
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(MARK_CONVERSATION_SEEN_REQUEST);
    packetDTO->setUserIdentity(userId);
    packetDTO->setPacketID(packetId);
    packetDTO->setConversationList(conversationList);
    packetDTO->setDevice(platform);
    
    return {parser->parse(packetDTO), packetDTO};
}

BuiltPacket ChatPacketBuilder::makeOfflineGroupIPPortRequest(UserIdentity userId, GroupIdentity groupId, std::string &packetId, int platform, std::string &serverIp, int serverPort)
{
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(OFFLINE_GROUP_IP_PORT);
    packetDTO->setUserIdentity(userId);
    packetDTO->setGroupId(groupId);
    packetDTO->setPacketID(packetId);
    packetDTO->setDevice(platform);
    packetDTO->setServerIp(serverIp);
    packetDTO->setServerPort(serverPort);
    
    return {parser->parse(packetDTO), packetDTO};
}

    BuiltPacket ChatPacketBuilder::makePublicRoomRegisterPacket(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, std::string &roomName, std::string &roomUrl, int platform, UserIdentity ringId) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_ROOM_REGISTER);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        packetDTO->setRoomFullName(roomName);
        packetDTO->setRoomUrl(roomUrl);
        packetDTO->setDevice(platform);
        packetDTO->setRingId(ringId);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makePublicRoomUnregisterPacket(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, UserIdentity recepientId, UserIdentity ringId) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_ROOM_UNREGISTER);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        packetDTO->setRecipientId(recepientId);
        packetDTO->setRingId(ringId);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makePublicRoomChatIdelPacket(UserIdentity userId, RoomIdentity &roomId, int platform) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_ROOM_CHAT_IDEL);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setDevice(platform);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makePublicRoomChatTypingPacket(UserIdentity userId, RoomIdentity &roomId, std::string &memberName, int platform) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_ROOM_CHAT_MESSAGE_TYPING);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setRoomFullName(memberName);
        packetDTO->setDevice(platform);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makePublicRoomChatMessagePacket(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, int messageType, std::string &message, long long messageDate, std::string &memberFullName, std::string &memberProfileUrl) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_ROOM_CHAT_MESSAGE);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        packetDTO->setMessageType(messageType);
        packetDTO->setMessage(message);
        packetDTO->setMessageDate(messageDate);
        packetDTO->setRoomFullName(memberFullName);
        packetDTO->setRoomUrl(memberProfileUrl);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makePublicRoomChatMessageEditPacket(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, int messageType, std::string &message, long long messageDate, std::string &memberFullName, std::string &memberProfileUrl) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_ROOM_CHAT_MESSAGE_EDIT);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        packetDTO->setMessageType(messageType);
        packetDTO->setMessage(message);
        packetDTO->setMessageDate(messageDate);
        packetDTO->setRoomFullName(memberFullName);
        packetDTO->setRoomUrl(memberProfileUrl);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makePublicRoomChatMessageBrokenPacket(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, int totalNumberOfPackets, int sequenceNumber, int messageType, std::string &message, long long messageDate, std::string &memberFullName, std::string &memberProfileUrl) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_ROOM_CHAT_MESSAGE_BROKEN);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        packetDTO->setNumberOfMessage(totalNumberOfPackets);
        packetDTO->setSequenceNumber(sequenceNumber);
        packetDTO->setMessageType(messageType);
        packetDTO->setMessage(message);
        packetDTO->setMessageDate(messageDate);
        packetDTO->setRoomFullName(memberFullName);
        packetDTO->setRoomUrl(memberProfileUrl);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makePublicRoomChatMessageBrokenEditPacket(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, int totalNumberOfPackets, int sequenceNumber, int messageType, std::string &message, long long messageDate, std::string &memberFullName, std::string &memberProfileUrl) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_ROOM_CHAT_MESSAGE_BROKEN_EDIT);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        packetDTO->setNumberOfMessage(totalNumberOfPackets);
        packetDTO->setSequenceNumber(sequenceNumber);
        packetDTO->setMessageType(messageType);
        packetDTO->setMessage(message);
        packetDTO->setMessageDate(messageDate);
        packetDTO->setRoomFullName(memberFullName);
        packetDTO->setRoomUrl(memberProfileUrl);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makePublicRoomChatMessageDeliveredPacket(UserIdentity userId, UserIdentity friendId, RoomIdentity &roomId, std::string &packetId) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_ROOM_CHAT_MESSAGE_DELIVERED);
        packetDTO->setUserIdentity(userId);
        packetDTO->setFriendIdentity(friendId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makePublicRoomChatMessageSentPacket(RoomIdentity &roomId, std::string &packetId) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_ROOM_CHAT_MESSAGE_SENT);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makePublicChatGetMemberList(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, std::string pagingState, int limit, int appversion){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_CHAT_GET_MEMBER_LIST);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        packetDTO->setPagingState(pagingState);
        packetDTO->setLimit(limit);
        packetDTO->setAppVersion(appversion);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makePublicChatGetMemberListConfirmation(UserIdentity userId, RoomIdentity &roomId, std::string &packetId) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_CHAT_GET_MEMBER_LIST_CONFIRMATION);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makePublicRoomChatMemberCountChange(RoomIdentity &roomId, std::string &packetId, int numberOfMembers) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_CHAT_MEMBER_COUNT_CHANGE);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        packetDTO->setNumberOfMembers(numberOfMembers);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makePublicRoomChatMemberCountChangeConfirmation(UserIdentity userId, RoomIdentity &roomId, std::string &packetId) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_CHAT_MEMBER_COUNT_CHANGE_CONFIRMATION);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makePublicRoomChatDeleteMessagePacket(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, std::vector<std::string> packetIds){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_CHAT_DELETE_MESSAGE);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        packetDTO->setPacketIDs(packetIds);
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makePublicRoomChatDeleteMessagePacketConfirmation(UserIdentity userId, RoomIdentity &roomId, std::string &packetId){
    std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
    packetDTO->setPacketType(PUBLIC_CHAT_DELETE_MESSAGE_CONFIRMATION);
    packetDTO->setUserIdentity(userId);
    packetDTO->setRoomId(roomId);
    packetDTO->setPacketID(packetId);
    return
    {
        parser->parse(packetDTO), packetDTO
    };
    }
    
    BuiltPacket ChatPacketBuilder::makePublicRoomChatLikeMessagePacket(UserIdentity userId, RoomIdentity &roomId, std::string &newPacketId, UserIdentity recipientId, std::string &actualPacletId){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_CHAT_LIKE_A_MESSAGE);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(newPacketId);
        packetDTO->setRecipientId(recipientId);
        packetDTO->setOriginalPacketID(actualPacletId);
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makePublicRoomChatUnlikeMessagePacket(UserIdentity userId, RoomIdentity &roomId, std::string &newPacketId, UserIdentity recipientId, std::string &actualPacletId){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_CHAT_UNLIKE_A_MESSAGE);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(newPacketId);
        packetDTO->setRecipientId(recipientId);
        packetDTO->setOriginalPacketID(actualPacletId);
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makePublicRoomChatLikeUnlikeConfirmation(UserIdentity userId, RoomIdentity &roomId, std::string &packetId){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_CHAT_LIKE_UNLIKE_CONFIRMATION);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makePublicRoomChatReportMessagePacket(UserIdentity userId, RoomIdentity &roomId, std::string &newPacketId, std::string &message, UserIdentity recipientId, std::string &actualPacletId){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_CHAT_REPORT_A_MESSAGE);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(newPacketId);
        packetDTO->setMessage(message);
        packetDTO->setRecipientId(recipientId);
        packetDTO->setOriginalPacketID(actualPacletId);
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makePublicRoomChatReportMessagePacketConfirmation(UserIdentity userId, RoomIdentity &roomId, std::string &packetId){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_CHAT_REPORT_A_MESSAGE_CONFIRMATION);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    
    BuiltPacket ChatPacketBuilder::makeOfflinePublicRoomListRequest(UserIdentity userId, std::string &packetId, int startIndex, int limit, int platform) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(OFFLINE_PUBLIC_ROOM_LIST_REQUEST);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPacketID(packetId);
        packetDTO->setStartIndex(startIndex);
        packetDTO->setLimit(limit);
        packetDTO->setDevice(platform);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeOfflinePublicRoomListWithHistoryRequest(UserIdentity userId, std::string &packetId, int startIndex, int limit, int platform) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(OFFLINE_PUBLIC_ROOM_LIST_WITH_HISTORY_REQUEST);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPacketID(packetId);
        packetDTO->setStartIndex(startIndex);
        packetDTO->setLimit(limit);
        packetDTO->setDevice(platform);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makeOfflinePublicRoomListSearchRequest(UserIdentity userId, std::string &packetId, int startIndex, int limit, std::string &searchName, std::string &country, std::string &category, int platform) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(OFFLINE_PUBLIC_ROOM_LIST_SEARCH_REQUEST);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPacketID(packetId);
        packetDTO->setStartIndex(startIndex);
        packetDTO->setLimit(limit);
        packetDTO->setRoomSearchName(searchName);
        packetDTO->setCountryOfPublicChatRoom(country);
        packetDTO->setCategoryOfPublicChatRoom(category);
        packetDTO->setDevice(platform);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    BuiltPacket ChatPacketBuilder::makeOfflinePublicRoomListRequestConfirmation(std::string &packetId) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(OFFLINE_PUBLIC_ROOM_LIST_REQUEST_CONFIRMATION);
        packetDTO->setPacketID(packetId);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeOfflinePublicGetRoomIPPort(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, int platform) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(OFFLINE_PUBLIC_GET_ROOM_IPPORT);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        packetDTO->setDevice(platform);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makeOfflinePublicGetRoomIPPortConfirmation(RoomIdentity &roomId, std::string &packetId, std::string &serverIp, int serverPort) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(OFFLINE_PUBLIC_GET_ROOM_IPPORT);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        packetDTO->setServerIp(serverIp);
        packetDTO->setServerPort(serverPort);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeOfflineRoomInformationRequest(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, int platform){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(OFFLINE_ROOM_INFORMATION_REQUEST);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        packetDTO->setDevice(platform);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeOfflineRoomGetHistoryPacket(UserIdentity userId, RoomIdentity &roomId, std::string &packetId, int month, int year, int direction, int limit, int platform, int appVersion){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(OFFLINE_ROOM_GET_HISTORY);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        packetDTO->setMonth(month);
        packetDTO->setYear(year);
        packetDTO->setUpDownStatus(direction);
        packetDTO->setLimit(limit);
        packetDTO->setDevice(platform);
        packetDTO->setAppVersion(appVersion);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    BuiltPacket ChatPacketBuilder::makeOfflineRoomGetHistoryConfirmationPacket(RoomIdentity &roomId, std::string &packetId){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(OFFLINE_ROOM_GET_HISTORY_CONFIRMATION);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(packetId);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    //Group file transfer
    BuiltPacket ChatPacketBuilder::makeGroupFileIdelPacket(UserIdentity userId, GroupIdentity groupId, int platform){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(GROUP_FILE_IDEL);
        packetDTO->setUserIdentity(userId);
        packetDTO->setGroupId(groupId);
        packetDTO->setDevice(platform);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makeGroupFileStreamRequest(UserIdentity userId, UserIdentity friendId, GroupIdentity groupId, std::string &packetId, FileIdentity fileId, bool accept, long long fileOffset){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(GROUP_FILE_STREAM_REQUEST);
        packetDTO->setUserIdentity(userId);
        packetDTO->setFriendIdentity(friendId);
        packetDTO->setGroupId(groupId);
        packetDTO->setPacketID(packetId);
        packetDTO->setFileIdentity(fileId);
        packetDTO->setFileAcceptReject(accept);
        packetDTO->setFileOffset(fileOffset);

        return{ parser->parse(packetDTO), packetDTO };
    }

    BuiltPacket ChatPacketBuilder::makeGroupFileStreamRequestConfirmation(UserIdentity userId, UserIdentity friendId, GroupIdentity groupId, std::string &packetId, FileIdentity fileId, bool accept){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(GROUP_FILE_STREAM_REQUEST_CONFIRMATION);
        packetDTO->setUserIdentity(userId);
        packetDTO->setFriendIdentity(friendId);
        packetDTO->setGroupId(groupId);
        packetDTO->setPacketID(packetId);
        packetDTO->setFileIdentity(fileId);
        packetDTO->setFileAcceptReject(accept);

        return{ parser->parse(packetDTO), packetDTO };
    }

    BuiltPacket ChatPacketBuilder::makeGroupFileSessionRequest(UserIdentity userId, GroupIdentity groupId, std::string &packetId, FileIdentity fileId){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(GROUP_FILE_SESSION_REQUEST);
        packetDTO->setUserIdentity(userId);
        packetDTO->setGroupId(groupId);
        packetDTO->setPacketID(packetId);
        packetDTO->setFileIdentity(fileId);

        return{ parser->parse(packetDTO), packetDTO };
    }

    BuiltPacket ChatPacketBuilder::makeGroupFileSessionRequestConfirmation(UserIdentity userId, GroupIdentity groupId, std::string &packetId, FileIdentity fileId, int fileTransferPort){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(GROUP_FILE_SESSION_REQUEST_CONFIRMATION);
        packetDTO->setUserIdentity(userId);
        packetDTO->setGroupId(groupId);
        packetDTO->setPacketID(packetId);
        packetDTO->setFileIdentity(fileId);
        packetDTO->setFileTransferPort(fileTransferPort);

        return{ parser->parse(packetDTO), packetDTO };
    }

    BuiltPacket ChatPacketBuilder::makeGroupFileIdel(UserIdentity userId, GroupIdentity groupId, int platform) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(GROUP_FILE_IDEL);
        packetDTO->setUserIdentity(userId);
        packetDTO->setGroupId(groupId);
        packetDTO->setDevice(platform);

        return{ parser->parse(packetDTO), packetDTO };
    }
    
    BuiltPacket ChatPacketBuilder::makeFriendFileIdelPacket(UserIdentity userId, UserIdentity friendId, int platform){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(FRIEND_FILE_IDEL);
        packetDTO->setUserIdentity(userId);
        packetDTO->setFriendIdentity(friendId);
        packetDTO->setDevice(platform);
        
        return{ parser->parse(packetDTO), packetDTO };
    }
    
    //Anonymous friend chat
    BuiltPacket ChatPacketBuilder::makeAnonymousFriendChatRegisterPacket(UserIdentity userId, UserIdentity friendId, std::string &packetId, int platform){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(ANONYMOUS_REGISTER);
        packetDTO->setUserIdentity(userId);
        packetDTO->setFriendIdentity(friendId);
        packetDTO->setPacketID(packetId);
        packetDTO->setDevice(platform);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
	BuiltPacket ChatPacketBuilder::makeAnonymousFriendChatRegisterConfirmationPacket(UserIdentity userId, UserIdentity friendId, std::string &packetId, int bindingPort, long long serverDate){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(ANONYMOUS_REGISTER_CONFIRMATION);
		packetDTO->setFriendIdentity(userId);
		packetDTO->setFriendIdentity(friendId);
        packetDTO->setPacketID(packetId);
        packetDTO->setChatBindingPort(bindingPort);
        packetDTO->setServerDate(serverDate);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeAnonymousFriendChatUnregisterPacket(UserIdentity userId, UserIdentity friendId, std::string &packetId, int onlineStatus, int onlineMood){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(ANONYMOUS_UNREGISTER);
        packetDTO->setUserIdentity(userId);
        packetDTO->setFriendIdentity(friendId);
        packetDTO->setPacketID(packetId);
        packetDTO->setOnlineStatus(onlineStatus);
        packetDTO->setOnlineMood(onlineMood);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeShadowIdInfoRequestPacket(UserIdentity userId, std::string &packetID, std::vector<UserIdentity> &shadowIdList, int platform){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(SHADOW_IDS_INFO_REQUEST);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPacketID(packetID);
        packetDTO->setShadowIdList(shadowIdList);
        packetDTO->setDevice(platform);

        return {parser->parse(packetDTO), packetDTO};
    }

BuiltPacket ChatPacketBuilder::makeFriendFileStreamRequestPacket(UserIdentity userId, UserIdentity friendId, std::string &packetId, FileIdentity fileId, bool fileAcceptReject, long long fileOffset){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(FRIEND_FILE_STREAM_REQUEST);
        packetDTO->setUserIdentity(userId);
        packetDTO->setFriendIdentity(friendId);
        packetDTO->setPacketID(packetId);
        packetDTO->setFileIdentity(fileId);
        packetDTO->setFileAcceptReject(fileAcceptReject);
        packetDTO->setFileOffset(fileOffset);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeFriendFileStreamRequestConfirmationPacket(UserIdentity userId, UserIdentity friendId, std::string &packetId, FileIdentity fileId, bool fileAcceptReject){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(FRIEND_FILE_STREAM_REQUEST_CONFIRMATION);
        packetDTO->setUserIdentity(userId);
        packetDTO->setFriendIdentity(friendId);
        packetDTO->setPacketID(packetId);
        packetDTO->setFileIdentity(fileId);
        packetDTO->setFileAcceptReject(fileAcceptReject);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeFriendFileSessionRequestPacket(UserIdentity userId, UserIdentity friendId, std::string &packetId, FileIdentity fileId){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(FRIEND_FILE_SESSION_REQUEST);
        packetDTO->setUserIdentity(userId);
        packetDTO->setFriendIdentity(friendId);
        packetDTO->setPacketID(packetId);
        packetDTO->setFileIdentity(fileId);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeFriendGetChatMessagePacket(UserIdentity userId, UserIdentity friendId, std::string &packetId, int platform){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(FRIEND_GET_CHAT_MESSAGE);
        packetDTO->setUserIdentity(userId);
        packetDTO->setFriendIdentity(friendId);
        packetDTO->setPacketID(packetId);
        packetDTO->setDevice(platform);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeGroupGetChatMessagePacket(UserIdentity userId, GroupIdentity groupId, std::string &packetId, int platform){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(GROUP_GET_CHAT_MESSAGE);
        packetDTO->setUserIdentity(userId);
        packetDTO->setGroupId(groupId);
        packetDTO->setPacketID(packetId);
        packetDTO->setDevice(platform);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makePublicChatLikeMemberListRequest(UserIdentity userId, RoomIdentity roomId, std::string &generatedPacketId, std::string &originalPacketId, UserIdentity lastLikerId, int limit, int appversion){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(PUBLIC_CHAT_LIKE_MEMBER_LIST_REQUEST);
        packetDTO->setUserIdentity(userId);
        packetDTO->setRoomId(roomId);
        packetDTO->setPacketID(generatedPacketId);
        packetDTO->setOriginalPacketID(originalPacketId);
        packetDTO->setLastLikerId(lastLikerId);
        packetDTO->setLimit(limit);
        packetDTO->setAppVersion(appversion);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeOfflinePublicChatCategoryListRequest(UserIdentity userId, std::string &packetId, std::string pagingState, int limit, int platform){
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(OFFLINE_PUBLIC_CHAT_CATEGORY_LIST_REQUEST);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPacketID(packetId);
        packetDTO->setPagingState(pagingState);
        packetDTO->setLimit(limit);
        packetDTO->setDevice(platform);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeLiveStreamChatRegisterPacket(UserIdentity userId, UserIdentity publisherId, std::string &packetId, int platform)
    {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(LIVE_STREAM_CHAT_REGISTER);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPublisherId(publisherId);
        packetDTO->setPacketID(packetId);
        packetDTO->setDevice(platform);

        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makeFriendInitChunkFileDownloadPacket(UserIdentity userId,
            UserIdentity friendId, std::string packetId, std::string fileDownloadId, int fileChunkCount,
            int fileChunkSize, long long fileSize, int fileDomainType, int secretTimeout, long long messageDate, bool isSecretVisible, std::string caption, int widthOrSize, int heightOrDuration) {

        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();

        packetDTO->setPacketType(FRIEND_INIT_CHUNK_FILE_DOWNLOAD);
        packetDTO->setUserIdentity(userId);
        packetDTO->setFriendIdentity(friendId);
        packetDTO->setPacketID(packetId);
        packetDTO->setFileDownloadId(fileDownloadId);
        packetDTO->setFileChunkCount(fileChunkCount);
        packetDTO->setFileChunkSize(fileChunkSize);
        packetDTO->setFileSize(fileSize);
        packetDTO->setFileDomainType(fileDomainType);
        packetDTO->setTimeout(secretTimeout);
        packetDTO->setMessageDate(messageDate);
        packetDTO->setIsSecretVisible(isSecretVisible);
        packetDTO->setCaption(caption);
        packetDTO->setWidthOrFileSize(widthOrSize);
        packetDTO->setHeightOrDuration(heightOrDuration);

        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeLiveStreamChatUnregisterPacket(UserIdentity userId, UserIdentity publisherId, std::string &packetId, int onlineStatus, int onlineMood)
    {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(LIVE_STREAM_CHAT_UNREGISTER);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPublisherId(publisherId);
        packetDTO->setPacketID(packetId);
        packetDTO->setOnlineStatus(onlineStatus);
        packetDTO->setOnlineMood(onlineMood);

        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makeFriendFileChunkUploadedPacket(UserIdentity userId,
            UserIdentity friendId, std::string packetId, bool isManifest,
            std::string &fileDownloadId, std::string &fileChunkDownloadKey) {

        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();

        packetDTO->setPacketType(FRIEND_FILE_CHUNK_UPLOADED);
        packetDTO->setUserIdentity(userId);
        packetDTO->setFriendIdentity(friendId);
        packetDTO->setPacketID(packetId);
        packetDTO->setFileManifest(isManifest);
        packetDTO->setFileDownloadId(fileDownloadId);
        packetDTO->setFileChunkDownloadKey(fileChunkDownloadKey);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeLiveStreamChatRegisterConfirmationPacket(UserIdentity publisherId, std::string &packetId, int chatBindingPort, long long serverDate)
    {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(LIVE_STREAM_CHAT_REGISTER_CONFIRMATION);
        packetDTO->setPublisherId(publisherId);
        packetDTO->setPacketID(packetId);
        packetDTO->setChatBindingPort(chatBindingPort);
        packetDTO->setServerDate(serverDate);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeLiveStreamChatIdlePacket(UserIdentity userId, UserIdentity publisherId, int platform)
    {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(LIVE_STREAM_CHAT_IDEL);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPublisherId(publisherId);
        packetDTO->setDevice(platform);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeLiveStreamChatMessageTypingPacket(UserIdentity userId, UserIdentity publisherId, int platform)
    {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(LIVE_STREAM_CHAT_MESSAGE_TYPING);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPublisherId(publisherId);
        packetDTO->setDevice(platform);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeLiveStreamChatMessagePacket(UserIdentity userId, UserIdentity publisherId, std::string &packetId, int messageType, std::string &message, long long serverDate, std::string &fullName)
    {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(LIVE_STREAM_CHAT_MESSAGE);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPublisherId(publisherId);
        packetDTO->setPacketID(packetId);
        packetDTO->setMessageType(messageType);
        packetDTO->setMessage(message);
        packetDTO->setMessageDate(serverDate);
        packetDTO->setFullName(fullName);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeLiveStreamChatMessageDeliveredPacket(UserIdentity userId, UserIdentity publisherId, std::string &packetId)
    {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(LIVE_STREAM_CHAT_MESSAGE_DELIVERED);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPublisherId(publisherId);
        packetDTO->setPacketID(packetId);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeLiveStreamChatMessageSentPacket(UserIdentity publisherId, std::string &packetId)
    {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(LIVE_STREAM_CHAT_MESSAGE_SENT);
        packetDTO->setPublisherId(publisherId);
        packetDTO->setPacketID(packetId);

        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makeLiveStreamChatBlockUserPacket(UserIdentity publisherId, UserIdentity blockedUserId, std::string &packetId)
    {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(LIVE_STREAM_CHAT_BLOCK_USER);
        packetDTO->setPublisherId(publisherId);
        packetDTO->setUserIdentity(blockedUserId);
        packetDTO->setPacketID(packetId);

        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makeLiveStreamChatBlockUserConfirmationPacket(UserIdentity publisherId, UserIdentity userId, std::string &packetId)
    {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(LIVE_STREAM_CHAT_BLOCK_USER_CONFIRMATION);
        packetDTO->setPublisherId(publisherId);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPacketID(packetId);

        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makeFriendFileChunkConfirmationPacket(UserIdentity userId,
            UserIdentity friendId, std::string &packetId) {

        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();

        packetDTO->setPacketType(FRIEND_FILE_CHUNK_CONFIRMATION);
        packetDTO->setUserIdentity(userId);
        packetDTO->setFriendIdentity(friendId);
        packetDTO->setPacketID(packetId);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makeFriendChatMediaTransferCancelPacket(UserIdentity userId, UserIdentity friendId, std::string &packetId) {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();

        packetDTO->setPacketType(FRIEND_CHAT_MEDIA_TRANSFER_CANCEL);
        packetDTO->setUserIdentity(userId);
        packetDTO->setFriendIdentity(friendId);
        packetDTO->setPacketID(packetId);

        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makeGroupInitChunkFileDownloadPacket(UserIdentity userId,
            GroupIdentity groupId, std::string packetId, std::string fileDownloadId, int fileChunkCount, 
            int fileChunkSize, long long fileSize, int fileDomainType, long long messageDate, std::string caption, int widthOrSize, int heightOrDuration){
        
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();

        packetDTO->setPacketType(GROUP_INIT_CHUNK_FILE_DOWNLOAD);
        packetDTO->setUserIdentity(userId);
        packetDTO->setGroupId(groupId);
        packetDTO->setPacketID(packetId);
        packetDTO->setFileDownloadId(fileDownloadId);
        packetDTO->setFileChunkCount(fileChunkCount);
        packetDTO->setFileChunkSize(fileChunkSize);
        packetDTO->setFileSize(fileSize);
        packetDTO->setFileDomainType(fileDomainType);
        packetDTO->setMessageDate(messageDate);
        packetDTO->setCaption(caption);
        packetDTO->setWidthOrFileSize(widthOrSize);
        packetDTO->setHeightOrDuration(heightOrDuration);

        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeGroupFileChunkUploadedPacket(UserIdentity userId, 
            GroupIdentity groupId, std::string packetId, bool isManifest, 
            std::string &fileDownloadId, std::string &fileChunkDownloadKey){
        
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();

        packetDTO->setPacketType(GROUP_FILE_CHUNK_UPLOADED);
        packetDTO->setUserIdentity(userId);
        packetDTO->setGroupId(groupId);
        packetDTO->setPacketID(packetId);
        packetDTO->setFileManifest(isManifest);
        packetDTO->setFileDownloadId(fileDownloadId);
        packetDTO->setFileChunkDownloadKey(fileChunkDownloadKey);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
        
    }
    
    BuiltPacket ChatPacketBuilder::makeGroupFileChunkConfirmationPacket(UserIdentity userId, 
            GroupIdentity groupId, std::string &packetId){
        
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();

        packetDTO->setPacketType(GROUP_FILE_CHUNK_CONFIRMATION);
        packetDTO->setUserIdentity(userId);
        packetDTO->setGroupId(groupId);
        packetDTO->setPacketID(packetId);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makeGroupChatMediaTransferCancelPacket(UserIdentity userId,
            GroupIdentity groupId, std::string &packetId){

        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();

        packetDTO->setPacketType(GROUP_CHAT_MEDIA_TRANSFER_CANCEL);
        packetDTO->setUserIdentity(userId);
        packetDTO->setGroupId(groupId);
        packetDTO->setPacketID(packetId);

        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }


    BuiltPacket ChatPacketBuilder::makeGetSyncConversationRequest(UserIdentity userId, 
            std::string &packetId, long long lastSyncTime, int platform){

        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(GET_SYNC_CONVERSATION_REQUEST);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPacketID(packetId);
        packetDTO->setLastSyncTime(lastSyncTime);
        packetDTO->setSelfPlatform(platform);

        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makeGetSyncConversationStatus(UserIdentity userId, std::string &packetId){

        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(SYNC_CONVERSATION_CONFIRMATION);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPacketID(packetId);

        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makeSyncFriendHistoryMessageRequest(UserIdentity userId,
        UserIdentity friendId, std::string &packetId, long long lastSyncTime, int platform, int appType, int appVersion, UserIdentity pageOwnerId, int limit, int direction){

        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(SYNC_FRIEND_HISTORY_MESSAGE_REQUEST);
        packetDTO->setUserIdentity(userId);
        packetDTO->setFriendIdentity(friendId);
        packetDTO->setPacketID(packetId);
        packetDTO->setLastSyncTime(lastSyncTime);
        packetDTO->setSelfPlatform(platform);
        packetDTO->setAppType(appType);
        packetDTO->setAppVersion(appVersion);
        packetDTO->setPageOwnerId(pageOwnerId);
        packetDTO->setLimit(limit);
        packetDTO->setUpDownStatus(direction);

        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makeSyncGroupHistoryMessageRequest(UserIdentity userId,
        GroupIdentity groupId, std::string &packetId, long long lastSyncTime, int appVersion, int platform, int limit, int direction){

        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(SYNC_GROUP_HISTORY_MESSAGE_REQUEST);
        packetDTO->setUserIdentity(userId);
        packetDTO->setGroupId(groupId);
        packetDTO->setPacketID(packetId);
        packetDTO->setLastSyncTime(lastSyncTime);
        packetDTO->setAppVersion(appVersion);
        packetDTO->setSelfPlatform(platform);
        packetDTO->setLimit(limit);
        packetDTO->setUpDownStatus(direction);

        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }

    BuiltPacket ChatPacketBuilder::makeGetMyGroupListPagingRequest(UserIdentity userId, std::string &packetId, std::string &pivotId, int limit, int direction, int platform){

        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(GET_MY_GROUP_LIST_PAGING);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPacketID(packetId);
        packetDTO->setPivotID(pivotId);
        packetDTO->setLimit(limit);
        packetDTO->setUpDownStatus(direction);
        packetDTO->setSelfPlatform(platform);

        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeAddNotice(UserIdentity userId, std::string &packetId, int messageType, long long disburseTime, long long expireTime, std::string &notice, std::vector<std::string> &isoCountryList)
    {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(ADD_NOTICE);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPacketID(packetId);
        packetDTO->setMessageType(messageType);
        packetDTO->setDisburseTime(disburseTime);
        packetDTO->setExpireTime(expireTime);
        packetDTO->setNotice(notice);
        packetDTO->setIsoList(isoCountryList);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }
    
    BuiltPacket ChatPacketBuilder::makeAddNoticeConfirmation(UserIdentity userId, std::string &packetId)
    {
        std::shared_ptr< PacketDTO> packetDTO = std::make_shared<PacketDTO>();
        packetDTO->setPacketType(ADD_NOTICE_CONFIRMATION);
        packetDTO->setUserIdentity(userId);
        packetDTO->setPacketID(packetId);
        
        return
        {
            parser->parse(packetDTO), packetDTO
        };
    }


}
