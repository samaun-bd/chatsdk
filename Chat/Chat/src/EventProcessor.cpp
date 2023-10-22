/* 
 * File:   EventProcessor.cpp
 * Author: dipal
 * 
 * Created on August 18, 2015, 1:12 PM
 */

#include <iostream>
#include <cstdlib>
#include "EventProcessor.h"
#include "Logger.h"
#include "KeepaliveProcessor.h"
#include "ResourceManager.h"
#include "Chat.h"
#include "ResendProcessor.h"
#include "PacketProcessor.h"
#include "PacketReceiver.h"

#define module "EventProc"

namespace imsdk {

EventProcessor::EventProcessor() {
    this->setThreadName("IM_EVENT_PROC");
    ChatEvent::initEventNames();
}

EventProcessor::~EventProcessor() {
}

EventProcessor& EventProcessor::getInstance()
{
    static EventProcessor eventProcessor;
    return eventProcessor;
}

void EventProcessor::setEventHandler(std::shared_ptr< IChatEventHandler> eventHandler)
{
    this->eventHandler = eventHandler;
}

void EventProcessor::unsetEventHandler()
{
    push(ChatEvent(ChatEvent::INTERNAL_DETACH_HANDLER, nullptr), Priority::l5);
}

void EventProcessor::clear()
{
    Processor::clear();
    duplicateChecker.clear();
}

void EventProcessor::run()
{
    if (eventHandler && !empty())
    {
        ChatEvent event = top();
        pop();
        
        if(event.getEventType() == ChatEvent::NO_EVENT) {
            return;
        }

        Log(module, "Generating event "<<ChatEvent::getEventName(event.getEventType()));
        auto packet = event.getPacket();
        std::stringstream hash;
        switch (event.getEventType())
        {
            case ChatEvent::EVENT_HANDLER_ATTACHED :
            {
                eventHandler->onEventHandlerAttached();
                break;
            }
            case ChatEvent::EVENT_HANDLER_DETACHED:
            {
                //eventHandler->onEventHandlerDetached();
                break;
            }
            case ChatEvent::INTERNAL_DETACH_HANDLER:
            {
                eventHandler.reset();
                //eventHandler->onEventHandlerDetached();
                break;
            }
            case ChatEvent::ACTIVATE_DEACTIVATE_USER_ACCOUNT_STATUS:
			{
                hash << ChatEvent::ACTIVATE_DEACTIVATE_USER_ACCOUNT_STATUS << packet->getPacketID();
				if (duplicateChecker.isSafe(hash.str()))
				{
                    eventHandler->onActivaeOrDeactivateUserAccountStatus(packet->getUserIdentity(), packet->getPacketID(), packet->getIsActivateUserAccount(), packet->getRequestStatus());
				}
				break;
			}

            case ChatEvent::GET_USER_INFO_DETAILS_RECEIVED:
            {
                hash << ChatEvent::GET_USER_INFO_DETAILS_RECEIVED << packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGetUserInfoReceived(packet->getUserIdentity(), packet->getFriendIdentity(), packet->getPacketID(), packet->getFullName(), packet->getRingId(), packet->getFriendProfileImageUrl(), packet->getProfileType());
                }
                break;
            }

            case ChatEvent::GET_USER_INFO_DETAILS_FAILURE:
            {
                hash << ChatEvent::GET_USER_INFO_DETAILS_FAILURE << packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGetUserInfoFailure(packet->getUserIdentity(), packet->getFriendIdentity(), packet->getPacketID());
                }
                break;
            }

            case ChatEvent::FRIEND_REGISTER_SUCCESS :
            {
                hash<<ChatEvent::FRIEND_REGISTER_SUCCESS<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onFriendChatRegisterSuccess(packet->getUserIdentity(), packet->getFriendIdentity(), packet->getServerDate(), packet->getPacketID(), packet->isFromAnonymous());
                }
                break;
            }
            case ChatEvent::FRIEND_REGISTER_FAILURE :
            {
				eventHandler->onFriendChatRegisterFailure(packet->getUserIdentity(), packet->getFriendIdentity(), packet->getPacketID(), packet->isFromAnonymous());
                break;
            }
            case ChatEvent::FRIEND_REGISTRATION_EXPIRED :
            {
				eventHandler->onFriendRegistrationExpired(packet->getUserIdentity(), packet->getFriendIdentity(), packet->isFromAnonymous());
                break;
            }
            
            case ChatEvent::FRIEND_UNREGISTERED :
            {
//                hash<<ChatEvent::FRIEND_UNREGISTERED<<packet->getFriendIdentity();
//                if (duplicateChecker.isSafe(hash.str()))
//                {
				eventHandler->onFriendUnregistered(packet->getFriendIdentity(), packet->getUserIdentity(), packet->getOnlineStatus(), packet->getOnlineMood(), packet->isFromAnonymous(), packet->getProfileType());
//                }
                break;
            }
            
            case ChatEvent::GROUP_REGISTER_SUCCESS:
            {
                hash<<ChatEvent::GROUP_REGISTER_SUCCESS<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupChatRegisterSuccess(packet->getGroupId(), packet->getServerDate(), packet->getPacketID());
                }
                break;
            }
            
            case ChatEvent::GROUP_REGISTER_FAILURE:
            {
                eventHandler->onGroupChatRegisterFailure(packet->getGroupId(), packet->getPacketID());
                break;
            }
            
            case ChatEvent::GROUP_REGISTRATION_EXPIRED :
            {
                eventHandler->onGroupRegistrationExpired(packet->getGroupId(), packet->getMessageDate());
                break;
            }
            
            case ChatEvent::FRIEND_NEW_CHAT_RECEIVED :
            {
                std::string packetId = packet->getPacketID();
                std::string message = packet->getMessage();
                
                UserIdentity sender, receiver;
                Log(module, "New friend chat received. message "<<message<<" packet.userId : "<<packet->getUserIdentity()<<" packet.friendId : "<<packet->getFriendIdentity());
                hash<<ChatEvent::FRIEND_NEW_CHAT_RECEIVED<<packetId<<packet->getMessageDate();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    sender = packet->getUserIdentity();
                    receiver = packet->getFriendIdentity();
                    
                    if(sender == 0 || receiver == 0)
                    {
                        Log(module, "message won't be forwarded because snederId: "<<sender <<" ;receiverID: "<<receiver);
                        break;
                    }
                    
                    Log(module, "Callling event function from event handler");
                    eventHandler->onFriendChatReceived(sender, receiver, packetId, packet->getMessageType(), packet->getTimeout(), message, packet->getMessageDate(), packet->getIsSecretVisible(), packet->isOnline(), packet->isFromAnonymous());
                    Log(module, "Callling completed event function from event handler");
                }
                else
                {
                    Log(module, "friend chat event not fired. message "<<message);
                }
                break;
            }
            
            case ChatEvent::FRIEND_CHAT_DELIVERED :
            {
                std::string packetId = packet->getPacketID();
                Log(module, "Friend chat delivered. friendId "<<packet->getUserIdentity()<<" packetId "<<packetId);
				eventHandler->onFriendChatDelivered(packet->getFriendIdentity(), packet->getUserIdentity(), packetId, packet->isFromAnonymous(), packet->isMessageEdited(), packet->isOnline());
                break;
            }
            
            case ChatEvent::FRIEND_CHAT_SENT :
            {
                std::string packetId = packet->getPacketID();
				eventHandler->onFriendChatSent(packet->getUserIdentity(), packet->getFriendIdentity(), packetId, packet->isFromAnonymous());
                break;
            }
            
            case ChatEvent::FRIEND_CHAT_IS_SEEN:
            {
                hash<<ChatEvent::FRIEND_CHAT_IS_SEEN<<packet->getPacketID();
                auto seenMessageList = packet->getSeenMessageList();
                if (duplicateChecker.isSafe(hash.str()))
                {
					eventHandler->onFriendChatSeen(packet->getFriendIdentity(), packet->getUserIdentity(), seenMessageList, packet->isFromAnonymous());
                }
                else
                {
                    Log(module, "friend chat Seen. but event not fired ");
                }
                break;
            }
            
            case ChatEvent::FRIEND_CHAT_IS_SEEN_CONFIRMED:
            {
                hash<<ChatEvent::FRIEND_CHAT_IS_SEEN_CONFIRMED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    std::vector<SeenPacketDTO> seenPacketList = packet->getSeenMessageList();
					eventHandler->onFriendChatSeenConfirmed(packet->getUserIdentity(), packet->getFriendIdentity(), seenPacketList, packet->isFromAnonymous());
                }
                break;
            }
            
            case ChatEvent::FRIEND_CHAT_TYPING:
            {
				eventHandler->onFriendChatTyping(packet->getFriendIdentity(), packet->getUserIdentity(), packet->isFromAnonymous());
                break;
            }
            
            case ChatEvent::FRIEND_CHAT_IDLE:
            {
                eventHandler->onFriendChatIdle(packet->getUserIdentity(), packet->isFromAnonymous());
                break;
            }
            
            case ChatEvent::FRIEND_CHAT_FAILED_TO_SEND:
            {
                std::string packetId = packet->getPacketID();
				eventHandler->onFriendChatFailedToSend(packet->getUserIdentity(), packet->getFriendIdentity(), packetId, packet->isFromAnonymous());
                break;
            }
            
            case ChatEvent::FRIEND_CHAT_EDITED:
            {
                std::string packetId = packet->getPacketID();
                std::string message = packet->getMessage();
                UserIdentity sender, receiver;
                
                Log(module, "Friend chat edited. packetId "<<packetId);
                hash<<ChatEvent::FRIEND_CHAT_EDITED<<packet->getPacketID()<<packet->getMessageDate();
                if (duplicateChecker.isSafe(hash.str()))
                {                   
                    sender = packet->getUserIdentity();
                    receiver = packet->getFriendIdentity();
                    eventHandler->onFriendChatEdited(sender, receiver, packetId, packet->getMessageType(), packet->getTimeout(), message, packet->getMessageDate(), packet->getIsSecretVisible(), packet->isOnline(), packet->isFromAnonymous());
                }
                break;
            }
            
            case ChatEvent::FRIEND_CHAT_DELETED:
            {
                std::string packetId = packet->getPacketID();
                Log(module, "Friend chat deleted. friendId "<<packet->getUserIdentity()<<" packetId "<<packetId);
                hash<<ChatEvent::FRIEND_CHAT_DELETED<<packet->getPacketID();
                auto packetIds = packet->getPacketIDs();
                if (duplicateChecker.isSafe(hash.str()))
                {
					eventHandler->onFriendChatDeleted(packet->getUserIdentity(), packet->getFriendIdentity(), packetIds, packet->isFromAnonymous());
                }
                break;
            }
            
            case ChatEvent::FRIEND_CHAT_DELETE_STATUS_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                std::vector<std::string> packetIds = packet->getPacketIDs();
                bool requestStatus = packet->getRequestStatus();
				UserIdentity userId = requestStatus ? packet->getFriendIdentity() : packet->getUserIdentity();
				UserIdentity friendId = requestStatus ? packet->getUserIdentity() : packet->getFriendIdentity();
                hash<<ChatEvent::FRIEND_CHAT_DELETE_STATUS_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
//                    std::vector<std::string> packetIDs = packet->getPacketIDs();
                    eventHandler->onFriendChatDeleteRequestStatus(userId, friendId, packetId, packetIds, packet->isFromAnonymous(), requestStatus, packet->getMessageDeleteType());
                }
                break;
            }
            
            case ChatEvent::FRIEND_BLOCKED:
            {
                hash<<ChatEvent::FRIEND_BLOCKED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onBlocked(packet->getUserIdentity(), packet->getFriendIdentity(), packet->getBlockUnblockDate(), packet->getIsAddToBlock());
                }
                break;
            }
            
            case ChatEvent::FRIEND_UNBLOCKED:
            {
                hash<<ChatEvent::FRIEND_UNBLOCKED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onUnblocked(packet->getUserIdentity(), packet->getFriendIdentity(), packet->getBlockUnblockDate());
                }
                break;
            }

            case ChatEvent::OFFLINE_FRIEND_HISTORY_MESSAGE_CONFIRMATION_RECEIVED:
            {
                hash << ChatEvent::OFFLINE_FRIEND_HISTORY_MESSAGE_CONFIRMATION_RECEIVED << packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
					eventHandler->onFriendHistoryMessageRequestStatus(packet->getUserIdentity(), packet->getFriendIdentity(), packet->getPacketID(), packet->getRequestStatus());
                }
                break;
            }
            
//            case ChatEvent::FRIEND_FILE_TRANSFER_REQUEST_RECEIVED:
//            {
//                std::string message = packet->getMessage();
//                std::vector<std::string> fileInformation = ResourceManager::StringParser(message);
//                std::string fileName = fileInformation[0];
//                FileIdentity fileId = std::atol(fileInformation[1].c_str());
//                Log(module, "File ID while receiving: "<<fileId);
//                long long fileSize = std::atol(fileInformation[2].c_str());
//                
//                eventHandler->onFriendFileTransferRequestReceived(packet->getUserIdentity(), fileName, fileId, fileSize);
//                break;
//            }
            
            case ChatEvent::FRIEND_BLOCK_UNBLOCK_CONFIRMED:
            {
                hash<<ChatEvent::FRIEND_BLOCK_UNBLOCK_CONFIRMED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onBlockUnblockRequestStatus(packet->getUserIdentity(), packet->getFriendIdentity(), packet->getPacketID(), packet->getBlockUnblockDate(), packet->getRequestStatus(), (packet->getPacketType() == FRIEND_BLOCK));
                }
                break;
            }
            
            case ChatEvent::GROUP_CHAT_SENT:
            {
                std::string packetId = packet->getPacketID();
                eventHandler->onGroupChatSent(packet->getGroupId(), packetId, packet->isMessageEdited());
                break;
            }
            
            case ChatEvent::GROUP_NEW_CHAT_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                std::string message = packet->getMessage();
                hash<<ChatEvent::GROUP_NEW_CHAT_RECEIVED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    if(packet->getGroupId() == 0)
                    {
                        Log(module, "message won't be forwarded because groupId: "<<packet->getGroupId());
                        break;
                    }
                    eventHandler->onGroupChatReceived(packet->getUserIdentity(), packet->getGroupId(), packetId, packet->getMessageType(), message, packet->getMessageDate(), packet->isOnline());
                }
                break;
            }
            
            case ChatEvent::GROUP_CHAT_EDITED:
            {
                std::string packetId = packet->getPacketID();
                std::string message = packet->getMessage();
                Log(module, "Group chat edited by friendId "<<packet->getUserIdentity()<<" packetId "<<packetId);
                hash<<ChatEvent::GROUP_CHAT_EDITED<<packet->getPacketID()<<packet->getMessageDate();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupChatEdited(packet->getUserIdentity(), packet->getGroupId(), packetId, packet->getMessageType(), message, packet->getMessageDate(), packet->isOnline());
                }
                break;
            }
            
            case ChatEvent::GROUP_CHAT_DELIVERED:
            {
                UserIdentity friendId = packet->getUserIdentity();
                GroupIdentity groupId = packet->getGroupId();
                std::string packetId = packet->getPacketID();

                hash<<ChatEvent::GROUP_CHAT_DELIVERED<<packet->getPacketID()<<friendId<<groupId;
                if (duplicateChecker.isSafe(hash.str(), 4))
                {
                    eventHandler->onGroupChatDelivered(friendId, groupId, packetId);
                }
                break;
            }
            
            case ChatEvent::GROUP_CHAT_DELETED:
            {
                std::string packetId = packet->getPacketID();
                Log(module, "Group chat deleted. groupId: "<<packet->getGroupId()<<" packetId "<<packetId);
                auto packetIds = packet->getPacketIDs();
                hash<<ChatEvent::GROUP_CHAT_DELETED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupChatDeleted(packet->getUserIdentity(), packet->getGroupId(), packetIds);
                }
                break;
            }
            
            case ChatEvent::GROUP_CHAT_DELETE_CONFIRMED:
            {
                std::string packetId = packet->getPacketID();
                std::vector<std::string> packetIds = packet->getPacketIDs();
                hash<<ChatEvent::GROUP_CHAT_DELETE_CONFIRMED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    //std::vector<std::string> packetIDs = packet->getPacketIDs();
                    eventHandler->onGroupChatDeleteRequestStatus(packet->getGroupId(), packetId, packetIds, packet->getRequestStatus());
                }
                break;
            }
            
            case ChatEvent::GROUP_CHAT_SEEN:
            {
                GroupIdentity groupId = packet->getGroupId();
                std::vector<std::string> seenPacketIds = packet->getPacketIDs();
                
                hash<<ChatEvent::GROUP_CHAT_SEEN<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupChatSeen(groupId, packet->getUserIdentity(), seenPacketIds);
                }
                break;
            }
            
            case ChatEvent::GROUP_CHAT_SEEN_CONFIRMATION:
            {
                GroupIdentity groupId = packet->getGroupId();
                std::vector<std::string> seenPacketIds = packet->getPacketIDs();
                
                hash<<ChatEvent::GROUP_CHAT_SEEN_CONFIRMATION<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupChatSeenRequestStatus(groupId, seenPacketIds, packet->getRequestStatus());
                }
                break;
            }
            
            case ChatEvent::GROUP_CHAT_TYPING:
            {
                UserIdentity friendId = packet->getUserIdentity();
                GroupIdentity groupId = packet->getGroupId();
                eventHandler->onGroupChatTyping(friendId, groupId);
                break;
            }
            
            case ChatEvent::GROUP_CHAT_IDLE:
            {
                UserIdentity friendId = packet->getUserIdentity();
                GroupIdentity groupId = packet->getGroupId();
                eventHandler->onGroupChatIdle(friendId, groupId);
                break;
            }
            
            case ChatEvent::GROUP_MEMBER_REMOVE_LEAVE_SENT:
            {
                GroupIdentity groupId = packet->getGroupId();
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::GROUP_MEMBER_REMOVE_LEAVE_SENT<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
//                    std::vector<UserIdentity> userIds;
//                    std::vector<MemberDTO> memberDTOs = packet->getMemberList();
//                    for(int i=0;i<memberDTOs.size();i++){
//                        userIds.push_back(memberDTOs[i].getMemberIdentity());
//                    }
                    bool isHide = packet->getGroupLeaveType() == 2 ? true : false;
                    eventHandler->onGroupMemberRemoveLeaveRequestStatus(groupId, packetId, packet->getRequestStatus(), packet->getMemberList(), isHide);
                }
                break;
            }
            
            case ChatEvent::GROUP_MEMBER_REMOVED_OR_LEFT:
            {
                UserIdentity friendId = packet->getUserIdentity();
                GroupIdentity groupId = packet->getGroupId();
                std::string packetId = packet->getPacketID();
                std::vector<MemberDTO> memberList = packet->getMemberList();
                std::vector<UserIdentity> memberId;

                for (std::vector<MemberDTO>::size_type i = 0; i < memberList.size(); i++){
                    memberId.push_back(memberList[i].getMemberIdentity());
                }

                hash<<ChatEvent::GROUP_MEMBER_REMOVED_OR_LEFT<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    bool isHide = packet->getGroupLeaveType() == 2 ? true : false;
                    eventHandler->onGroupMemberRemovedOrLeft(friendId, groupId, memberId, packetId, isHide);
                }
                break;
            }
            
            case ChatEvent::GROUP_MEMBER_ADDED:
            {
                UserIdentity friendId = packet->getUserIdentity();
                GroupIdentity groupId = packet->getGroupId();
                std::string packetId = packet->getPacketID();
                auto memberList = packet->getMemberList();
                hash<<ChatEvent::GROUP_MEMBER_ADDED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupMemberAdded(friendId, groupId, memberList, packetId);
                }
                break;
            }
            
            case ChatEvent::GROUP_MEMBER_ADD_SENT:
            {
                GroupIdentity groupId = packet->getGroupId();
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::GROUP_MEMBER_ADD_SENT<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
//                    std::vector<UserIdentity> userIDs;
//                    std::vector<MemberDTO> memberDTOs = packet->getMemberList();
//                    for(int i=0;i<memberDTOs.size(); i++){
//                        userIDs.push_back(memberDTOs[i].getMemberIdentity());
//                    }
                    eventHandler->onGroupMemberAddRequestStatus(groupId, packetId, packet->getRequestStatus(), packet->getMemberList());
                }
                break;
            }
            
            case ChatEvent::GROUP_INFORMATION_RECEIVED:
            {
                UserIdentity friendId = packet->getUserIdentity();
                GroupIdentity groupId = packet->getGroupId();
                int activityType = packet->getGroupActivityType();
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::GROUP_INFORMATION_RECEIVED<<activityType<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    if (activityType == 3)
                    {
                        std::string groupName = packet->getGroupName();    
                        eventHandler->onGroupNameChanged(packetId, friendId, groupId, groupName);
                    }
                    else if (activityType == 5)
                    {
                        std::string groupUrl = packet->getGroupUrl();
                        eventHandler->onGroupUrlChanged(packetId, friendId, groupId, groupUrl);
                    }
                }
                
                break;
            }
            
            case ChatEvent::GROUP_INFORMATION_SENT:
            {
                GroupIdentity groupId = packet->getGroupId();
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::GROUP_INFORMATION_SENT<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    if (packet->getGroupActivityType() == GroupChangeActivity::GROUP_URL_RENAME)
                    {
                        std::string groupUrl = packet->getGroupUrl();
                        eventHandler->onGroupUrlChangeRequestStatus(groupId, packetId, packet->getRequestStatus(), groupUrl);
                    }
                    else if (packet->getGroupActivityType() ==  GroupChangeActivity::GROUP_RENAME)
                    {
                        std::string groupName = packet->getGroupName();
                        eventHandler->onGroupNameChangeRequestStatus(groupId, packetId, packet->getRequestStatus(), groupName);
                    }
                }
                break;
            }
            
            case ChatEvent::GROUP_MEMBER_STATUS_CHANGED:
            {
                UserIdentity senderId = packet->getUserIdentity();
                GroupIdentity groupId = packet->getGroupId();
                std::string packetId = packet->getPacketID();
                auto memberList = packet->getMemberList();
                hash<<ChatEvent::GROUP_MEMBER_STATUS_CHANGED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupMemberStatusChanged(senderId, groupId, memberList, packetId);
                }
                break;
            }
            
            case ChatEvent::GROUP_MEMBER_STATUS_CHANGE_SENT:
            {
                GroupIdentity groupId = packet->getGroupId();
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::GROUP_MEMBER_STATUS_CHANGE_SENT<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupMemberStatusChangeRequestStatus(groupId, packetId, packet->getRequestStatus(), packet->getMemberList());
                }
                break;
            }
            
            case ChatEvent::GROUP_CHAT_FAILED_TO_SEND :
            {
                GroupIdentity groupId = packet->getGroupId();
                std::string packetId = packet->getPacketID();
                eventHandler->onGroupChatFailedToSend(groupId, packetId);
                break;
            }
            
            case ChatEvent::SHOULD_CHECK_FRIEND_PRESENCE:
            {
				hash << ChatEvent::SHOULD_CHECK_FRIEND_PRESENCE << packet->getUserIdentity() << packet->getFriendIdentity();
                if (duplicateChecker.isSafe(hash.str(), 20))
                {
					eventHandler->shouldCheckFriendPresence(packet->getUserIdentity(), packet->getFriendIdentity(), packet->isFromAnonymous(), packet->getProfileType());
                }
                break;
            }
            
            case ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_FRIEND:
            {
				hash << ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_FRIEND << packet->getUserIdentity() << packet->getFriendIdentity();
                if (duplicateChecker.isSafe(hash.str(), 20))
                {
					eventHandler->shouldCheckServerAddressForFriend(packet->getUserIdentity(), packet->getFriendIdentity(), packet->isFromAnonymous());
                }
                else 
                {
                    Log(module, "Event skipped");
                }
                break;
            }
            
            case ChatEvent::SHOULD_REMOVE_DUPLICATE_INFO_FOR_FRIEND:
            {
				hash << ChatEvent::SHOULD_CHECK_FRIEND_PRESENCE << packet->getUserIdentity() << packet->getFriendIdentity();
                duplicateChecker.removeDuplicateInfo(hash.str());
                hash.str("");
				hash << ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_FRIEND << packet->getUserIdentity() << packet->getFriendIdentity();
                duplicateChecker.removeDuplicateInfo(hash.str());
                hash.str("");
                break;
            }
            
            case ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_GROUP:
            {
                hash<<ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_GROUP<<packet->getGroupId();
                if (duplicateChecker.isSafe(hash.str(), 20))
                {
                    eventHandler->shouldCheckServerAddressForGroup(packet->getGroupId());
                }
                break;
            }
            
            case ChatEvent::SHOULD_CHECK_OFFLINE_SERVER_ADDRESS:
            {
                hash<<ChatEvent::SHOULD_CHECK_OFFLINE_SERVER_ADDRESS;
                if (duplicateChecker.isSafe(hash.str(), 120))
                {
                    eventHandler->shouldCheckOfflineServerAddress();
                }
                break;
            }
            
            case ChatEvent::OFFLINE_FRIEND_HISTORY_MESSAGE_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::OFFLINE_FRIEND_HISTORY_MESSAGE_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
					eventHandler->onFriendHistoryMessageReceived(packet->getUserIdentity(), packet->getFriendIdentity(), packet->getChatMessageList(), packet->getUpDownStatus());
                }
                break;
            }

            case ChatEvent::OFFLINE_FRIEND_HISTORY_MESSAGE_RECEIVE_COMPLETED:
            {
                std::string packetId = packet->getPacketID();
                hash << ChatEvent::OFFLINE_FRIEND_HISTORY_MESSAGE_RECEIVE_COMPLETED << packetId;
                if (duplicateChecker.isSafe(hash.str(), 4))
                {
					eventHandler->onFriendHistoryCompleted(packet->getUserIdentity(), packet->getFriendIdentity(), packet->getUpDownStatus());
                }
                break;
            }

            case ChatEvent::OFFLINE_FRIEND_MESSAGES_STATUS_RECEIVED:
            {
                std::vector<FriendMessageStatusDTO> messageList = packet->getFriendMessageStatusDTOList();
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::OFFLINE_FRIEND_MESSAGES_STATUS_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str(), 4))
                {
					eventHandler->onFriendMessagesStatusReceived(packet->getUserIdentity(), packet->getFriendIdentity(), messageList);
                }
                break;
            }
            case ChatEvent::OFFLINE_GROUP_HISTORY_MESSAGE_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::OFFLINE_GROUP_HISTORY_MESSAGE_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {     
//                    std::vector<SDKMessageDTO> chatMessageList;
//                    std::vector<std::shared_ptr< PacketDTO>> messageList = packet->getMessageList();
//
//                    for (std::vector<std::shared_ptr< PacketDTO>>::size_type i = 0; i < messageList.size(); i++)
//                    {
//                        SDKMessageDTO chatMessageDTO;
//                        chatMessageDTO.setDirection(messageList[i]->getUpDownStatus());
//                        chatMessageDTO.setMessage(messageList[i]->getMessage());
//                        chatMessageDTO.setMessageDate(messageList[i]->getMessageDate());
//                        chatMessageDTO.setMessageType(messageList[i]->getMessageType());
//                        chatMessageDTO.setPacketId(messageList[i]->getPacketID());
//                        chatMessageDTO.setSenderId(messageList[i]->getUserIdentity());
//
//                        if (messageList[i]->getPacketType() == GROUP_CHAT_MESSAGE_EDIT){
//                            chatMessageDTO.setIsEdited(true);
//                        }
//                        else
//                        {
//                            chatMessageDTO.setIsEdited(false);
//                        }
//
//                        chatMessageList.push_back(chatMessageDTO);
//                    }
//                    packet->setChatMessageList(chatMessageList);
                    eventHandler->onGroupHistoryMessageReceived(packet->getGroupId(), packet->getChatMessageList(), packet->getUpDownStatus());//packet->getUserIdentity(), packetId, packet->getMessageType(), message, packet->getMessageDate(), packet->getUpDownStatus()
                }
                break;
            }
            case ChatEvent::OFFLINE_GROUP_HISTORY_MESSAGE_RECEIVE_COMPLETED:
            {
                std::string packetId = packet->getPacketID();
                hash << ChatEvent::OFFLINE_GROUP_HISTORY_MESSAGE_RECEIVE_COMPLETED << packetId;
                if (duplicateChecker.isSafe(hash.str(), 4))
                {
                    eventHandler->onGroupHistoryCompleted(packet->getGroupId(), packet->getUpDownStatus());
                }
                break;
            }
            case ChatEvent::OFFLINE_GROUP_INFORMATION_WITH_MEMBERS_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                std::string groupName = packet->getGroupName();
                std::string groupUrl = packet->getGroupUrl();
                auto memberList = packet->getMemberList();
                hash<<ChatEvent::OFFLINE_GROUP_INFORMATION_WITH_MEMBERS_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupInformationWithMembersReceived(packet->getGroupId(), groupName, groupUrl, memberList);
                }
                break;
            }

            case ChatEvent::OFFLINE_GROUP_INFORMATION_WITH_MEMBERS_REQUEST_STATUS:
            {
                hash << ChatEvent::OFFLINE_GROUP_INFORMATION_WITH_MEMBERS_REQUEST_STATUS << packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupInformationWithMembersRequestStatus(packet->getGroupId(), packet->getPacketID(), packet->getRequestStatus());
                }
                break;
            }

            case ChatEvent::OFFLINE_GROUP_INFORMATION_ACTIVITY_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                auto groupActivity = packet->getGroupActivities();
                hash<<ChatEvent::OFFLINE_GROUP_INFORMATION_ACTIVITY_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    Log(module, "event : onGroupInformationActivityReceived");
                    eventHandler->onGroupInformationActivityReceived(groupActivity);
                }
                break;
            }
            case ChatEvent::OFFLINE_GROUP_INFORMATION_ACTIVITY_FROM_GROUP_HISTORY_MESSAGE_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                auto groupActivity = packet->getGroupActivities();
                hash<<ChatEvent::OFFLINE_GROUP_INFORMATION_ACTIVITY_FROM_GROUP_HISTORY_MESSAGE_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupInformationActivityFromHistoryMessageReceived(packet->getGroupId(), groupActivity, packet->getUpDownStatus());
                }
                break;
            }

            case ChatEvent::OFFLINE_GROUP_HISTORY_MESSAGE_CONFIRMATION_RECEIVED:
            {
                hash << ChatEvent::OFFLINE_GROUP_HISTORY_MESSAGE_CONFIRMATION_RECEIVED << packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str(), 4))
                {
                    eventHandler->onGroupHistoryMessageRequestStatus(packet->getGroupId(), packet->getPacketID(), packet->getRequestStatus());
                }
                break;
            }

            case ChatEvent::OFFLINE_MY_GROUP_LIST_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                auto groupList = packet->getGroupDTOList();
                hash<<ChatEvent::OFFLINE_MY_GROUP_LIST_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onMyGroupListReceived(groupList);
                }
                break;
            }

            case ChatEvent::OFFLINE_MY_GROUP_LIST_PAGING_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                auto groupList = packet->getGroupDTOList();
                hash << ChatEvent::OFFLINE_MY_GROUP_LIST_PAGING_RECEIVED << packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onMyGroupListPagingReceived(groupList, packet->getPivotID(), packet->getUpDownStatus());
                }
                break;
            }

            case ChatEvent::OFFLINE_MY_GROUP_LIST_RECEIVED_COMPLETED:
            {
                std::string packetId = packet->getPacketID();
                hash << ChatEvent::OFFLINE_MY_GROUP_LIST_RECEIVED_COMPLETED << packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onMyGroupListReceiveCompleted();
                }
                break;
            }
            case ChatEvent::GROUP_CREATED:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::GROUP_CREATED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupCreated(packet->getGroupId(), packet->getPacketID(), packet->getRequestStatus());
                }
                break;
            }
            
            case ChatEvent::SDK_ERROR :
            {
                std::string packetId;
                if (packet) packetId = packet->getPacketID();
                eventHandler->onSDKError(event.getErrorCode(), packetId);
                break;
            }
            
            case ChatEvent::SERVICE_IDLE_TIMEOUT:
            {
                Chat::stopServices();
                KeepaliveProcessor::getInstance().clear();
                PacketProcessor::getInstance().clear();
                ResendProcessor::getInstance().clear();
                ResourceManager::getInstance().clear();

                PacketReceiver::getInstance().clearSocketList();
                ResourceManager::getInstance().clearOfflineConnection();
                ResourceManager::getInstance().clearSocket();
                break;
            }
            
            case ChatEvent::SERVER_TIME_DIFFERENCE_SYNCED:
            {
                Log(module, "Time difference "<<ResourceManager::getInstance().getTimeDifference());
                hash<<ChatEvent::SERVER_TIME_DIFFERENCE_SYNCED;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onServerTimeSynced(ResourceManager::getInstance().getTimeDifference());
                }
                break;
            }
            
            case ChatEvent::CONVERSATION_LIST_REQUEST_STATUS:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::CONVERSATION_LIST_REQUEST_STATUS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
					eventHandler->onChatConversationListRequestStatus(packet->getUserIdentity(), packet->getFriendOrGroupId(), packetId, packet->getRequestStatus());
                }
                break;
            }
            
            case ChatEvent::CONVERSATION_LIST_DELETE_REQUEST_STATUS:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::CONVERSATION_LIST_DELETE_REQUEST_STATUS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
					eventHandler->onConversationListDeleteRequestStatus(packet->getUserIdentity(), packetId, packet->getRequestStatus());
                }
                break;
            }
            
            case ChatEvent::MARK_CONVERSATION_LIST_SEEN_REQUEST_STATUS:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::MARK_CONVERSATION_LIST_SEEN_REQUEST_STATUS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
					eventHandler->onConversationListMarkAsSeenRequestStatus(packet->getUserIdentity(), packetId, packet->getRequestStatus());
                }
                break;
            }
            
            case ChatEvent::FRIEND_CONVERSATION_LIST_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::FRIEND_CONVERSATION_LIST_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    auto friendChatConversationList = packet->getChatMessageList();
                    eventHandler->onFriendChatConversationListReceived(packet->getUserIdentity(), friendChatConversationList, packet->getIsFromSynced());
                }
                break;
            }
            
            case ChatEvent::GROUP_CONVERSATION_LIST_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::GROUP_CONVERSATION_LIST_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    auto groupChatConversationList = packet->getChatMessageList();
                    eventHandler->onGroupChatConversationListReceived(groupChatConversationList, packet->getIsFromSynced());
                }
                break;
            }
            
            case ChatEvent::CONVERSATION_LIST_RECEIVE_COMPLETED:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::CONVERSATION_LIST_RECEIVE_COMPLETED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onChatConversationListCompleted(packet->getUserIdentity(), packet->getIsFromSynced());
                }
                break;
            }
            
            case ChatEvent::PUBLIC_ROOM_CHAT_REGISTER_SUCCESS:
            {
                RoomIdentity roomId = packet->getRoomId();
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::PUBLIC_ROOM_CHAT_REGISTER_SUCCESS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicRoomChatRegisterSuccess(roomId, packetId, packet->getNumberOfMembers(), packet->getRecipientId());
                }
                break;
            }
            
            case ChatEvent::PUBLIC_ROOM_CHAT_REGISTER_FAILURE:
            {
                RoomIdentity roomId = packet->getRoomId();
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::PUBLIC_ROOM_CHAT_REGISTER_FAILURE<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicRoomChatRegisterFailure(roomId, packetId);
                }
                break;
            }
            
            case ChatEvent::PUBLIC_ROOM_CHAT_REGISTRATION_EXPIRED:
            {
                RoomIdentity roomId = packet->getRoomId();
                hash<<ChatEvent::PUBLIC_ROOM_CHAT_REGISTRATION_EXPIRED<<packet->getRoomId();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicRoomChatRegistrationExpired(roomId);
                }
                break;
            }
            
            case ChatEvent::PUBLIC_ROOM_CHAT_DELIVERED:
            {
                RoomIdentity roomId = packet->getRoomId();
                std::string packetId = packet->getPacketID();
                eventHandler->onPublicRoomChatDelivered(roomId, packetId, packet->isMessageEdited());
                break; 
            }
            
            case ChatEvent::PUBLIC_ROOM_CHAT_MESSAGE_RECEIVED:
            {
                RoomIdentity roomId = packet->getRoomId();
                std::string packetId = packet->getPacketID();
                std::string message = packet->getMessage();
                std::string memberFullName = packet->getRoomFullName();
                std::string memberProfileUrl = packet->getRoomUrl();
                
                hash<<ChatEvent::PUBLIC_ROOM_CHAT_MESSAGE_RECEIVED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicRoomChatReceived(roomId, packet->getUserIdentity(), packetId, packet->getMessageType(), message, packet->getMessageDate(), memberFullName, memberProfileUrl);
                }
                break;
            }
            
            case ChatEvent::PUBLIC_ROOM_LIST_REQUEST_STATUS:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::PUBLIC_ROOM_LIST_REQUEST_STATUS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicRoomListRequestStatus(packetId, packet->getRequestStatus());
                }
                break;
            }
            
            case ChatEvent::PUBLIC_ROOM_INFORMATION_REQUEST_FAILED:
            {
                RoomIdentity roomId = packet->getRoomId();
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::PUBLIC_ROOM_INFORMATION_REQUEST_FAILED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicRoomInformationRequestFailed(roomId, packetId);
                }
                break;
            }
            
            case ChatEvent::PUBLIC_ROOM_CHAT_HISTORY_REQUEST_STATUS:
            {
                RoomIdentity roomId = packet->getRoomId();
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::PUBLIC_ROOM_CHAT_HISTORY_REQUEST_STATUS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicRoomChatHistoryRequestStatus(roomId, packetId, packet->getRequestStatus());
                }
                break;
            }
            
            case ChatEvent::PUBLIC_ROOM_MEMBER_LIST_REQUEST_STATUS:
            {
                RoomIdentity roomId = packet->getRoomId();
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::PUBLIC_ROOM_MEMBER_LIST_REQUEST_STATUS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicRoomMemberListRequestStatus(roomId, packetId, packet->getRequestStatus());
                }
                break;
            }
            
            case ChatEvent::PUBLIC_ROOM_LIST_RECEIVED:
            {
                std::vector<RoomDTO> roomList = packet->getRoomList();

                hash<<ChatEvent::PUBLIC_ROOM_LIST_RECEIVED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicRoomListReceived(roomList, packet->isRoomListFromHistory());
                }
                break;
                
            }
            
            case ChatEvent::ROOM_INFORMATION_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                std::string roomId = packet->getRoomId();
                std::string roomName = packet->getRoomFullName();
                std::string roomUrl = packet->getRoomUrl();
                
                hash<<ChatEvent::ROOM_INFORMATION_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicRoomInformationReceived(roomId, roomName, roomUrl, packetId);
                }
                break;
            }
            
            case ChatEvent::PUBLIC_ROOM_CHAT_EDITED:
            {
                RoomIdentity roomId = packet->getRoomId();
                std::string packetId = packet->getPacketID();
                std::string message = packet->getMessage();
                std::string memberFullName = packet->getRoomFullName();
                std::string memberProfileUrl = packet->getRoomUrl();
                
                hash<<ChatEvent::PUBLIC_ROOM_CHAT_EDITED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicRoomChatEdited(roomId, packet->getUserIdentity(), packetId, packet->getMessageType(), message, packet->getMessageDate(), memberFullName, memberProfileUrl);
                }
                break;
            }
            
            case ChatEvent::PUBLIC_ROOM_CHAT_TYPING:
            {
                RoomIdentity roomId = packet->getRoomId();
                UserIdentity memberId = packet->getUserIdentity();
                std::string memberName = packet->getRoomFullName();
                
                hash<<ChatEvent::PUBLIC_ROOM_CHAT_TYPING<<packet->getRoomId();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicRoomChatTyping(roomId, memberId, memberName);
                }
                break;
                
            }
            
            case ChatEvent::PUBLIC_ROOM_CHAT_FAILED_TO_SEND:
            {
                RoomIdentity roomId = packet->getRoomId();
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::PUBLIC_ROOM_CHAT_FAILED_TO_SEND<<packetId; 
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicRoomChatFailedToSend(roomId, packetId);
                }
                break;
            }
            
            case ChatEvent::PUBLIC_CHAT_MEMBER_LIST_RECEIVED:
            {
                RoomIdentity roomId = packet->getRoomId();
                std::string pagingState = packet->getPagingState();
                std::vector<PublicChatMemberDTO> publicChatMemberList = packet->getPublicChatMemberList();
                
                hash<<ChatEvent::PUBLIC_CHAT_MEMBER_LIST_RECEIVED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicChatMemberListReceived(roomId, pagingState, publicChatMemberList);
                }
                break;
            }
            
            case ChatEvent::PUBLIC_CHAT_MEMBER_COUNT_CHANGED:
            {
                RoomIdentity roomId = packet->getRoomId();
                int numberOfMembers = packet->getNumberOfMembers();
                
                hash<<ChatEvent::PUBLIC_CHAT_MEMBER_COUNT_CHANGED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicChatMemberCountChanged(roomId, numberOfMembers);
                }
                
                break;
            }
            
            case ChatEvent::ROOM_HISTORY_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                std::string roomId = packet->getRoomId();
                
                std::vector<std::shared_ptr< PacketDTO>> messageList = packet->getMessageList();
                std::vector<SDKMessageDTO> publicChatMessageList(messageList.size());

                for (std::vector<std::shared_ptr< PacketDTO>>::size_type i = 0; i < messageList.size(); i++)
                {
                    publicChatMessageList[i].setPacketId(messageList[i]->getPacketID());
                    publicChatMessageList[i].setSenderId(messageList[i]->getUserIdentity());
                    publicChatMessageList[i].setMessageType(messageList[i]->getMessageType());
                    publicChatMessageList[i].setMessage(messageList[i]->getMessage());
                    publicChatMessageList[i].setMessageDate(messageList[i]->getMessageDate());
                    publicChatMessageList[i].setMemberFullName(messageList[i]->getRoomFullName());
                    publicChatMessageList[i].setMemberProfileUrl(messageList[i]->getRoomUrl());
                    publicChatMessageList[i].setPublicChatLikeCount(messageList[i]->getPublicChatLikeCount());
                    publicChatMessageList[i].setPublicChatILike(messageList[i]->isPublicChatILike());
                    publicChatMessageList[i].setPublicChatIReport(messageList[i]->isPublicChatIReport());
                }
                
                hash<<ChatEvent::ROOM_HISTORY_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {              
                    eventHandler->onPublicRoomChatHistoryReceived(roomId, publicChatMessageList);
                }
                break;
            }
            
            case ChatEvent::PUBLIC_ROOM_CHAT_HISTORY_MESSAGE_RECEIVE_COMPLETED:
            {
                std::string packetId = packet->getPacketID();
                std::string roomId = packet->getRoomId();
                
                hash<<ChatEvent::PUBLIC_ROOM_CHAT_HISTORY_MESSAGE_RECEIVE_COMPLETED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {              
                    eventHandler->onPublicRoomChatHistoryCompleted(roomId);
                }
                break;
            }
            
            case ChatEvent::SHADOW_IDS_INFO_RESPONSE_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::SHADOW_IDS_INFO_RESPONSE_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    auto shadowIdInfo = packet->getPublicChatMemberList();
                    eventHandler->onShadowIdsInfoResponseReceived(shadowIdInfo);
                }
                break;
            }
            
            case ChatEvent::SHADOW_IDS_INFO_REQUEST_FAILED:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::SHADOW_IDS_INFO_REQUEST_FAILED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onShadowIdsInfoRequestFailed(packetId);
                }
                break;
            }
            
            case ChatEvent::SHOULD_CHECK_SERVER_ADDRESS_FOR_ROOM:
            {
                RoomIdentity roomId = packet->getRoomId();
                hash<<ChatEvent::SHOULD_CHECK_SERVER_ADDRESS_FOR_ROOM<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str(), 40))
                {
                    eventHandler->shouldCheckServerAddressForRoom(roomId);
                }
                break;
            }

            //Group file transfer
            case ChatEvent::GROUP_FILE_TRANSFER_STREAM_REQUEST_RECEIVED:
            {
                FileIdentity fileId= packet->getFileIdentity();
                UserIdentity friendId = packet->getUserIdentity();
                GroupIdentity groupId = packet->getGroupId();
                
                hash<<ChatEvent::GROUP_FILE_TRANSFER_STREAM_REQUEST_RECEIVED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupFileStreamRequestReceived(friendId, groupId, fileId);
                }                
                break;
            }
            
            case ChatEvent::GROUP_FILE_TRANSFER_STREAM_REQUEST_FAILED:
            {
                std::string packetId = packet->getPacketID();
                FileIdentity fileId = packet->getFileIdentity();
                GroupIdentity groupId = packet->getGroupId();
                hash<<ChatEvent::GROUP_FILE_TRANSFER_STREAM_REQUEST_FAILED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupFileTransferStreamRequestFailed(packetId, groupId, fileId);
                }
                break;
            }
            
            case ChatEvent::GROUP_FILE_TRANSFER_SESSION_REQUEST_FAILED:
            {
                std::string packetId = packet->getPacketID();
                FileIdentity fileId = packet->getFileIdentity();
                GroupIdentity groupId = packet->getGroupId();
                hash<<ChatEvent::GROUP_FILE_TRANSFER_SESSION_REQUEST_FAILED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupFileTransferSessionRequestFailed(packetId, groupId, fileId);
                }
                break;
            }
            
            case ChatEvent::GROUP_FILE_TRANSFER_SESSION_REQUEST_SUCCESS:
            {
                std::string packetId = packet->getPacketID();
                GroupIdentity groupId = packet->getGroupId();
                
                hash<<ChatEvent::GROUP_FILE_TRANSFER_SESSION_REQUEST_SUCCESS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupFileSessionRequestSuccess(packetId, groupId, packet->getFileIdentity(), packet->getFileTransferPort());
                }
                break;
            }
            
            case ChatEvent::GROUP_FILE_TRANSFER_STREAM_REQUEST_SUCCESS:
            {
                std::string packetId = packet->getPacketID();
                GroupIdentity groupId = packet->getGroupId();
                
                hash<<ChatEvent::GROUP_FILE_TRANSFER_STREAM_REQUEST_SUCCESS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupFileStreamRequestSuccess(packetId, groupId, packet->getFileIdentity());
                }
                break;
            }
            
            case ChatEvent::FRIEND_FILE_TRANSFER_STREAM_REQUEST_RECEIVED:
            {
                FileIdentity fileId= packet->getFileIdentity();
                UserIdentity friendId = packet->getUserIdentity();
                hash<<ChatEvent::FRIEND_FILE_TRANSFER_STREAM_REQUEST_RECEIVED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
					eventHandler->onFileStreamRequestReceived(packet->getUserIdentity(), friendId, fileId);
                }                
                break;
            }
            
            case ChatEvent::FRIEND_FILE_TRANSFER_STREAM_REQUEST_FAILED:
            {
                std::string packetId = packet->getPacketID();
                FileIdentity fileId = packet->getFileIdentity();
                UserIdentity friendId = packet->getFriendIdentity();
                hash<<ChatEvent::FRIEND_FILE_TRANSFER_STREAM_REQUEST_FAILED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
					eventHandler->onFriendFileTransferStreamRequestFailed(packet->getUserIdentity(), packetId, friendId, fileId);
                }
                break;
            }
            
            case ChatEvent::FRIEND_FILE_TRANSFER_SESSION_REQUEST_FAILED:
            {
                std::string packetId = packet->getPacketID();
                FileIdentity fileId = packet->getFileIdentity();
                UserIdentity friendId = packet->getFriendIdentity();
                hash<<ChatEvent::FRIEND_FILE_TRANSFER_SESSION_REQUEST_FAILED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
					eventHandler->onFriendFileTransferSessionRequestFailed(packet->getUserIdentity(), packetId, friendId, fileId);
                }
                break;
            }
            
            case ChatEvent::FRIEND_FILE_TRANSFER_SESSION_REQUEST_SUCCESS:
            {
                std::string packetId = packet->getPacketID();
                UserIdentity friendId = packet->getFriendIdentity();
                
                hash<<ChatEvent::FRIEND_FILE_TRANSFER_SESSION_REQUEST_SUCCESS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
					eventHandler->onFriendFileSessionRequestSuccess(packet->getUserIdentity(), packetId, friendId, packet->getFileIdentity(), packet->getFileTransferPort());
                }
                break;
            }
            
            case ChatEvent::FRIEND_FILE_TRANSFER_STREAM_REQUEST_SUCCESS:
            {
                std::string packetId = packet->getPacketID();
                UserIdentity friendId = packet->getFriendIdentity();
                
                hash<<ChatEvent::FRIEND_FILE_TRANSFER_STREAM_REQUEST_SUCCESS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
					eventHandler->onFriendFileStreamRequestSuccess(packet->getUserIdentity(), packetId, friendId, packet->getFileIdentity());
                }
                break;
            }
            
            case ChatEvent::FRIEND_GET_CHAT_MESSAGE_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                
                UserIdentity senderId = packet->getUserIdentity();
                UserIdentity receiverId = packet->getFriendIdentity();

                hash<<ChatEvent::FRIEND_GET_CHAT_MESSAGE_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    SDKMessageDTO friendChatMessageDTO;
                    friendChatMessageDTO.setSenderId(senderId);
                    friendChatMessageDTO.setReceiverId(receiverId);
                    friendChatMessageDTO.setPacketId(packetId);
                    friendChatMessageDTO.setMessageType(packet->getMessageType());
                    friendChatMessageDTO.setTimeOut(packet->getTimeout());
                    friendChatMessageDTO.setMessage(packet->getMessage());
                    friendChatMessageDTO.setMessageDate(packet->getMessageDate());
                    friendChatMessageDTO.setSecretVisible(packet->getIsSecretVisible());
                    friendChatMessageDTO.setIsEdited(packet->getOriginalPacketType()==FRIEND_CHAT_MESSAGE_EDIT);
                    
					eventHandler->onFriendGetChatMessageReceived(senderId, receiverId, friendChatMessageDTO);
                }
                break;
            }
            
            case ChatEvent::GROUP_GET_CHAT_MESSAGE_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                UserIdentity friendId = packet->getUserIdentity();
                UserIdentity groupId = packet->getGroupId();
                hash<<ChatEvent::GROUP_GET_CHAT_MESSAGE_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    SDKMessageDTO groupChatMessageDTO;
                    groupChatMessageDTO.setSenderId(friendId);
                    groupChatMessageDTO.setPacketId(packetId);
                    groupChatMessageDTO.setMessageType(packet->getMessageType());
                    groupChatMessageDTO.setTimeOut(packet->getTimeout());
                    groupChatMessageDTO.setMessage(packet->getMessage());
                    groupChatMessageDTO.setMessageDate(packet->getMessageDate());
                    groupChatMessageDTO.setSecretVisible(packet->getIsSecretVisible());
                    groupChatMessageDTO.setIsEdited(packet->getOriginalPacketType()==GROUP_CHAT_MESSAGE_EDIT);
                    
                    eventHandler->onGroupGetChatMessageReceived(groupId, groupChatMessageDTO);
                }
                break;
            }
            
            case ChatEvent::FRIEND_GET_CHAT_MESSAGE_FAILED_TO_SEND:
            {
                std::string packetId = packet->getPacketID();
                UserIdentity friendId = packet->getUserIdentity();
                hash<<ChatEvent::FRIEND_GET_CHAT_MESSAGE_FAILED_TO_SEND<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
					eventHandler->onFriendGetChatMessageFailedToSend(packet->getFriendIdentity(), friendId, packetId);
                }
                
                break;
            }
            
            case ChatEvent::GROUP_GET_CHAT_MESSAGE_FAILED_TO_SEND:
            {
                std::string packetId = packet->getPacketID();
                UserIdentity groupId = packet->getGroupId();
                hash<<ChatEvent::GROUP_GET_CHAT_MESSAGE_FAILED_TO_SEND<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupGetChatMessageFailedToSend(groupId, packetId);
                }
                
                break;
            }
            
            case ChatEvent::DATA_COUNTED:
            {
                DataCounter dataCounter = packet->getDataCounter();
                eventHandler->onNetworkDataCounted(dataCounter);
                break;
            }
            
            case ChatEvent::GROUP_CHAT_MESSAGE_SEEN_LIST_CONFIRMATION_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                std::string messagePacketId = packet->getOriginalPacketID();
                
                hash<<ChatEvent::GROUP_CHAT_MESSAGE_SEEN_LIST_CONFIRMATION_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupChatMessageSeenListRequestStatus(packet->getGroupId(), packetId, messagePacketId, packet->getRequestStatus());
                }
                
                break;
            }
            
            case ChatEvent::GROUP_CHAT_MESSAGE_SEEN_LIST_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                std::string originalPacketId = packet->getOriginalPacketID();
                UserIdentity groupId = packet->getGroupId();
                std::vector<MemberDTO> memberList= packet->getMemberList();
                
                hash<<ChatEvent::GROUP_CHAT_MESSAGE_SEEN_LIST_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupChatMessageSeenListReceived(groupId, originalPacketId, memberList);
                }
                
                break;
            }

			case ChatEvent::PUBLIC_CHAT_MESSAGE_DELETED:
            {
                std::string packetId = packet->getPacketID();
                RoomIdentity roomId = packet->getRoomId();
                std::vector<std::string> packetIds = packet->getPacketIDs();
                
                hash<<ChatEvent::PUBLIC_CHAT_MESSAGE_DELETED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicChatMessageDeleted(roomId, packetIds);
                }
                
                break;
            }
            
            case ChatEvent::PUBLIC_CHAT_MESSAGE_LIKED:
            {
                std::string packetId = packet->getPacketID();
                std::string originalPacketId = packet->getOriginalPacketID();
                RoomIdentity roomId = packet->getRoomId();
                UserIdentity likerId = packet->getUserIdentity();
                
                hash<<ChatEvent::PUBLIC_CHAT_MESSAGE_LIKED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicChatMessageLiked(roomId, originalPacketId, likerId);
                }
                
                break;
            }
            
            case ChatEvent::PUBLIC_CHAT_MESSAGE_UNLIKED:
            {
                std::string packetId = packet->getPacketID();
                std::string originalPacketId = packet->getOriginalPacketID();
                RoomIdentity roomId = packet->getRoomId();
                UserIdentity unlikerId = packet->getUserIdentity();
                
                hash<<ChatEvent::PUBLIC_CHAT_MESSAGE_UNLIKED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicChatMessageUnliked(roomId, originalPacketId, unlikerId);
                }
                
                break;
            }
            
            case ChatEvent::PUBLIC_CHAT_MESSAGE_REPORTED:
            {
                std::string packetId = packet->getPacketID();
                std::string originalPacketId = packet->getOriginalPacketID();
                RoomIdentity roomId = packet->getRoomId();
                UserIdentity reporterId = packet->getUserIdentity();
                
                hash<<ChatEvent::PUBLIC_CHAT_MESSAGE_REPORTED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicChatMessageReported(roomId, originalPacketId, reporterId);
                }
                
                break;
            }
            
            case ChatEvent::PUBLIC_CHAT_ROOM_CATEGORY_LIST_RECEIVED:
            {
                std::vector<std::string> publicChatCategoryList = packet->getPublicRoomCategoryList();
                hash<<ChatEvent::PUBLIC_CHAT_ROOM_CATEGORY_LIST_RECEIVED<<packet->getPacketID();
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicChatCategoryListReceived(publicChatCategoryList);
                }
                break;
            }
            
            case ChatEvent::PUBLIC_CHAT_LIKE_MEMBER_LIST_RECEIVED:
            {
                std::string roomId = packet->getRoomId();
                std::string packetId = packet->getPacketID();
                std::string originalPacketId = packet->getOriginalPacketID();
                
                std::vector<PublicChatMemberDTO> publicChatMemberList = packet->getPublicChatMemberList();
                hash<<ChatEvent::PUBLIC_CHAT_LIKE_MEMBER_LIST_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicChatLikeMemberListReceived(roomId, originalPacketId, publicChatMemberList);
                }
                break;
            }
            
            case ChatEvent::PUBLIC_CHAT_DELETE_MESSAGE_REQUEST_STATUS:
            {
                RoomIdentity roomId = packet->getRoomId();
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::PUBLIC_CHAT_DELETE_MESSAGE_REQUEST_STATUS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicChatDeleteRequestStatus(roomId, packetId, packet->getRequestStatus());
                }
                break;
            }
            
            case ChatEvent::PUBLIC_CHAT_LIKE_UNLIKE_REQUEST_STATUS:
            {
                RoomIdentity roomId = packet->getRoomId();
                std::string packetId = packet->getPacketID();
                std::string messagePacketId = packet->getOriginalPacketID();
                
                hash<<ChatEvent::PUBLIC_CHAT_LIKE_UNLIKE_REQUEST_STATUS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicChatLikeUnlikeRequestStatus(roomId, packetId, messagePacketId, packet->getRequestStatus(), (packet->getPacketType() == PUBLIC_CHAT_LIKE_A_MESSAGE));
                }
                break;
            }
            
            case ChatEvent::PUBLIC_CHAT_REPORT_A_MESSAGE_REQUEST_STATUS:
            {
                RoomIdentity roomId = packet->getRoomId();
                std::string packetId = packet->getPacketID();
                std::string messagePacketId = packet->getOriginalPacketID();
                
                hash<<ChatEvent::PUBLIC_CHAT_REPORT_A_MESSAGE_REQUEST_STATUS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicChatReportRequestStatus(roomId, packetId, messagePacketId, packet->getRequestStatus());
                }
                break;
            }
            
            case ChatEvent::PUBLIC_CHAT_LIKE_MEMBER_LIST_REQUEST_STATUS:
            {
                RoomIdentity roomId = packet->getRoomId();
                std::string packetId = packet->getPacketID();
                std::string originalPacketId = packet->getOriginalPacketID();
                
                hash<<ChatEvent::PUBLIC_CHAT_LIKE_MEMBER_LIST_REQUEST_STATUS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicChatLikeMemberListRequestStatus(roomId, originalPacketId, packet->getRequestStatus());
                }
                break;
            }
            
            case ChatEvent::OFFLINE_PUBLIC_CHAT_CATEGORY_LIST_REQUEST_STATUS:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::OFFLINE_PUBLIC_CHAT_CATEGORY_LIST_REQUEST_STATUS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onPublicChatCategoryListRequestStatus(packetId, packet->getRequestStatus());
                }
                break;
            }
            //Live stream chat event
            
            case ChatEvent::LIVE_STREAM_CHAT_REGISTER_SUCCESS:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::LIVE_STREAM_CHAT_REGISTER_SUCCESS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onLiveStreamChatRegisterSuccess(packet->getPublisherId(), packetId);
                }
                break;
            }
            
            case ChatEvent::LIVE_STREAM_CHAT_REGISTER_FAILURE:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::LIVE_STREAM_CHAT_REGISTER_FAILURE<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onLiveStreamChatRegisterFailure(packet->getPublisherId(), packetId);
                }
                break;
            }
            
            case ChatEvent::LIVE_STREAM_CHAT_REGISTRATION_EXPIRED:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::LIVE_STREAM_CHAT_REGISTRATION_EXPIRED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onLiveStreamChatRegistrationExpired(packet->getPublisherId());
                }
                break;
            }
            
            case ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_LIVE_STREAM_CHAT:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_LIVE_STREAM_CHAT<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->shouldCheckServerAddressForLiveStreamChat(packet->getPublisherId());
                }
                break;
            }
            
            case ChatEvent::LIVE_STREAM_CHAT_TYPING:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::LIVE_STREAM_CHAT_TYPING<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onLiveStreamChatTyping(packet->getPublisherId(), packet->getUserIdentity());
                }
                break;
            }
            
            case ChatEvent::LIVE_STREAM_CHAT_MESSAGE_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                std::string message = packet->getMessage();
                std::string senderFullName = packet->getFullName();
                
                hash<<ChatEvent::LIVE_STREAM_CHAT_MESSAGE_RECEIVED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onLiveStreamChatReceived(packet->getPublisherId(), packet->getUserIdentity(), packetId, packet->getMessageType(), message, packet->getMessageDate(), senderFullName);
                }
                break;
            }
            
            case ChatEvent::LIVE_STREAM_CHAT_DELIVERED:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::LIVE_STREAM_CHAT_DELIVERED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onLiveStreamChatDelivered(packet->getPublisherId(), packetId);
                }
                break;
            }
            
            case ChatEvent::LIVE_STREAM_CHAT_MESSAGE_FAILED:
            {
                std::string packetId = packet->getPacketID();
                hash<<ChatEvent::LIVE_STREAM_CHAT_MESSAGE_FAILED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onLiveStreamChatFailedToSend(packet->getPublisherId(), packetId);
                }
                break;
            }

            case ChatEvent::LIVE_STREAM_CHAT_BLOCK_USER_REQUEST_STATUS:
            {
                std::string packetId = packet->getPacketID();
                UserIdentity blockedUserId = packet->getUserIdentity();
                hash<<ChatEvent::LIVE_STREAM_CHAT_BLOCK_USER_REQUEST_STATUS<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onLiveStreamChatBlockUserRequestStatus(blockedUserId, packetId);
                }
                break;
            }

            case ChatEvent::LIVE_STREAM_CHAT_USER_BLOCKED:
            {
                std::string packetId = packet->getPacketID();
                UserIdentity publisherId = packet->getPublisherId();
                UserIdentity blockedUserId = packet->getUserIdentity();
                hash<<ChatEvent::LIVE_STREAM_CHAT_USER_BLOCKED<<packetId;
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onLiveStreamChatUserBlocked(publisherId, blockedUserId);
                }
                break;
            }

            case ChatEvent::FILE_MANIFEST_UPLOADED:
            {
				UserIdentity userId = packet->getUserIdentity();
				UserIdentity friendId = packet->getFriendIdentity();
                std::string fileUrl = packet->getFileChunkDownloadKey();
                int fileDomainType = packet->getFileDomainType();
                std::string caption = packet->getCaption();
                int widthOrFileSize = packet->getWidthOrFileSize();
                int heightOrDuration = packet->getHeightOrDuration();
                std::string packetId = packet->getPacketID();
                int secretTimeout = packet->getTimeout();
                
                hash<<ChatEvent::FILE_MANIFEST_UPLOADED<<packetId;
                
                if (duplicateChecker.isSafe(hash.str()))
                {
					eventHandler->onFriendFileManifestUploaded(userId, friendId, packetId, fileUrl, fileDomainType, secretTimeout, caption, widthOrFileSize, heightOrDuration);
                }
                
                break;
            }
            
            case ChatEvent::GROUP_FILE_MANIFEST_UPLOADED:
            {
                GroupIdentity groupId = packet->getGroupId();
                std::string fileUrl = packet->getFileChunkDownloadKey();
                int fileDomainType = packet->getFileDomainType();
                std::string caption = packet->getCaption();
                int widthOrFileSize = packet->getWidthOrFileSize();
                int heightOrDuration = packet->getHeightOrDuration();
                std::string packetId = packet->getPacketID();
                
                hash<<ChatEvent::GROUP_FILE_MANIFEST_UPLOADED<<packetId;
                
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupFileManifestUploaded(groupId, packetId, fileUrl, fileDomainType, caption, widthOrFileSize, heightOrDuration);
                }
                
                break;
            }
            
            case ChatEvent::INCOMING_CHAT_MEDIA_FILE:
            {
				UserIdentity userId = packet->getUserIdentity();
				UserIdentity friendId = packet->getFriendIdentity();
                std::string fileName = packet->getLocalFilePath();
                std::string packetId = packet->getPacketID();
                int messageType = packet->getMessageType();
                int timeout = packet->getTimeout();
                long long messageDate = packet->getMessageDate();
                bool isSecretVisible = packet->getIsSecretVisible();
                std::string caption = packet->getCaption();
                int widthOrSize = packet->getWidthOrFileSize();
                int heightOrDuration = packet->getHeightOrDuration();

                hash<<ChatEvent::INCOMING_CHAT_MEDIA_FILE<<fileName;
                
                if (duplicateChecker.isSafe(hash.str()))
                {
					eventHandler->onFriendIncomingChatMedia(userId, friendId, fileName, packetId, messageType, timeout, messageDate, isSecretVisible, caption, widthOrSize, heightOrDuration);
                }
                
                break;
            }
             
            case ChatEvent::INCOMING_GROUP_CHAT_MEDIA_FILE:
            {
                UserIdentity friendId = packet->getFriendIdentity();
                GroupIdentity groupId = packet->getGroupId();
                std::string fileName = packet->getLocalFilePath();
                std::string packetId = packet->getPacketID();
                int messageType = packet->getMessageType();
                long long messageDate = packet->getMessageDate();
                std::string caption = packet->getCaption();
                int widthOrSize = packet->getWidthOrFileSize();
                int heightOrDuration = packet->getHeightOrDuration();

                hash<<ChatEvent::INCOMING_GROUP_CHAT_MEDIA_FILE<<fileName;
                
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onGroupIncomingChatMedia(friendId, groupId, fileName, packetId, messageType, messageDate, caption, widthOrSize, heightOrDuration);
                }
                
                break;
            }
            
            case ChatEvent::CHAT_MEDIA_TRANSFER_PROGRESS:
            {
				UserIdentity userId = packet->getUserIdentity();
				UserIdentity friendId = packet->getFriendIdentity();
                std::string fileName = packet->getFileDownloadId();
                double transferPercentage = packet->getChunkedMediaTransferPercentage();
                bool mediaTransferTypeUpload = packet->isMediaTransferTypeUpload();
                std::string packetId = packet->getPacketID();
                
				eventHandler->onFriendChatMediaTransferProgress(userId, friendId, fileName, transferPercentage,
                        mediaTransferTypeUpload, packetId);
                
                break;
            }
            
            case ChatEvent::GROUP_CHAT_MEDIA_TRANSFER_PROGRESS:
            {
                UserIdentity friendId = packet->getFriendIdentity();
                GroupIdentity groupId = packet->getGroupId();
                std::string fileName = packet->getFileDownloadId();
                double transferPercentage = packet->getChunkedMediaTransferPercentage();
                bool mediaTransferTypeUpload = packet->isMediaTransferTypeUpload();
                std::string packetId = packet->getPacketID();
                
                eventHandler->onGroupChatMediaTransferProgress(friendId, groupId, fileName, transferPercentage,
                        mediaTransferTypeUpload, packetId);
                
                break;
            }

			case ChatEvent::GENERAL_ENCRYPTED_PACKET_EVENT:
			{
				eventHandler->onGeneralEncryptedPacketReceived(packet->getUserIdentity(), packet->getFriendIdentity(), packet->getPacketID(), packet->getType(),packet->getInformationType(), packet->getInformation());
				break;
			}

			case ChatEvent::GENERAL_ENCRYPTED_PACKET_CONFIRMATION_EVENT:
			{
				eventHandler->onGeneralEncryptedPacketConfirmationReceived(packet->getUserIdentity(), packet->getFriendIdentity(), packet->getPacketID(), packet->getType(), packet->getInformationType());
				break;
			}
            
            case ChatEvent::CHAT_MEDIA_DOWNLOAD_COMPLETED:
            {
				UserIdentity userId = packet->getUserIdentity();
				UserIdentity friendId = packet->getFriendIdentity();
                std::string fileNameWithPath = packet->getLocalFilePath();   
                std::string packetId = packet->getPacketID();
                int mediaType = packet->getFileDomainType();
                int timeout = packet->getTimeout();

				eventHandler->onFriendChatMediaDownloadCompleted(userId, friendId, fileNameWithPath, packetId, mediaType, timeout);
                
                break;
            }
            
            case ChatEvent::GROUP_CHAT_MEDIA_DOWNLOAD_COMPLETED:
            {
                UserIdentity friendId = packet->getFriendIdentity();
                GroupIdentity groupId = packet->getGroupId();
                std::string fileNameWithPath = packet->getLocalFilePath();   
                std::string packetId = packet->getPacketID();
                int mediaType = packet->getFileDomainType();
                
                eventHandler->onGroupChatMediaDownloadCompleted(friendId, groupId, fileNameWithPath, packetId, mediaType);
                
                break;
            }
            
            case ChatEvent::CHAT_MEDIA_TRANSFER_FAILED:
            {
				UserIdentity userId = packet->getUserIdentity();
				UserIdentity friendId = packet->getFriendIdentity();
                std::string fileName = packet->getFileDownloadId();
                bool isUpload = packet->isMediaTransferTypeUpload();
                std::string packetId = packet->getPacketID();
                bool chunkedTransfer = packet->isChunkedTransfer();
                
				eventHandler->onFriendChatMediaTransferFailed(userId, friendId, fileName, packetId, isUpload, chunkedTransfer);

                break;
            }
            
            case ChatEvent::GROUP_CHAT_MEDIA_TRANSFER_FAILED:
            {
                UserIdentity friendId = packet->getFriendIdentity();
                GroupIdentity groupId = packet->getGroupId();
                std::string fileName = packet->getFileDownloadId();
                bool isUpload = packet->isMediaTransferTypeUpload();
                std::string packetId = packet->getPacketID();
                bool chunkedTransfer = packet->isChunkedTransfer();
                
                eventHandler->onGroupChatMediaTransferFailed(friendId, groupId, fileName, packetId, isUpload, chunkedTransfer);

                break;
            }

            case ChatEvent::FRIEND_CHAT_MEDIA_TRANSFER_CANCELED:
            {
				UserIdentity userId = packet->getUserIdentity();
				UserIdentity friendId = packet->getFriendIdentity();
                std::string fileName = packet->getFileDownloadId();
                bool isUpload = packet->isMediaTransferTypeUpload();
                std::string packetId = packet->getPacketID();
                bool chunkedTransfer = packet->isChunkedTransfer();
                UserIdentity canceledBy = packet->getOriginalUserId();

				eventHandler->onFriendChatMediaTransferCanceled(userId, friendId, canceledBy, fileName, packetId, isUpload, chunkedTransfer);

                break;
            }

            case ChatEvent::GROUP_CHAT_MEDIA_TRANSFER_CANCELED:
            {
                UserIdentity friendId = packet->getFriendIdentity();
                GroupIdentity groupId = packet->getGroupId();
                std::string fileName = packet->getFileDownloadId();
                bool isUpload = packet->isMediaTransferTypeUpload();
                std::string packetId = packet->getPacketID();
                bool chunkedTransfer = packet->isChunkedTransfer();
                UserIdentity canceledBy = packet->getOriginalUserId();

                eventHandler->onGroupChatMediaTransferCanceled(friendId, groupId, canceledBy, fileName, packetId, isUpload, chunkedTransfer);

                break;
            }

            case ChatEvent::CHAT_MEDIA_TRANSFER_DIRECTORY_ERROR:
            {
                std::string packetId = packet->getPacketID();

                hash<<ChatEvent::CHAT_MEDIA_TRANSFER_DIRECTORY_ERROR<<packetId;

                if (duplicateChecker.isSafe(hash.str(), 4))
                {
                    std::string filePath = packet->getLocalFilePath();
                    if (!filePath.empty())
                    {
                        filePath = filePath.substr(0, filePath.find_last_of("\\/"));
                    }
                    eventHandler->onChatMediaTransferDirectoryError(filePath);
                }

                break;
            }

            case ChatEvent::SHOULD_UPDATE_APP_SESSION_ID:
            {
                hash<<ChatEvent::SHOULD_UPDATE_APP_SESSION_ID;

                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->shouldUpdateAppSessionID();
                }

                break;
            }

            case ChatEvent::SHOULD_UPDATE_PASSWORD:
            {
                std::string packetId = packet->getPacketID();
                
                hash<<ChatEvent::SHOULD_UPDATE_PASSWORD<<packetId;

                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->shouldUpdateUserPassword();
                }

                break;
            }

            case ChatEvent::SYNC_CONVERSATION_CONFIRMATION_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                hash << ChatEvent::SYNC_CONVERSATION_CONFIRMATION_RECEIVED << packetId;

                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onSyncConversationRequestStatus(packet->getUserIdentity(), packetId, ResourceManager::getInstance().getServerSyncedTime(), packet->getRequestStatus());
                }

                break;
            }

            case ChatEvent::SYNC_FRIEND_HISTORY_MESSAGE_CONFIRMATION_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                hash << ChatEvent::SYNC_FRIEND_HISTORY_MESSAGE_CONFIRMATION_RECEIVED << packetId;

                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onSyncFriendHistoryMessageRequestStatus(packet->getUserIdentity(), packet->getFriendIdentity(), packetId, ResourceManager::getInstance().getServerSyncedTime(), packet->getUpDownStatus(), packet->getRequestStatus());
                }

                break;
            }

            case ChatEvent::SYNC_FRIEND_HISTORY_MESSAGE_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                hash << ChatEvent::SYNC_FRIEND_HISTORY_MESSAGE_RECEIVED << packetId;

                if (duplicateChecker.isSafe(hash.str()))
                {
                    std::vector<SDKMessageDTO> messageList = packet->getChatMessageList();
                    eventHandler->onSyncFriendHistoryMessageReceived(packet->getUserIdentity(), packet->getFriendIdentity(), packet->getPacketID(), messageList, packet->getOldestMessageTime(), packet->getUpDownStatus());
                }

                break;
            }

            case ChatEvent::SYNC_FRIEND_HISTORY_MESSAGE_RECEIVE_COMPLETED:
            {
                std::string packetId = packet->getPacketID();
                hash << ChatEvent::SYNC_FRIEND_HISTORY_MESSAGE_RECEIVE_COMPLETED << packetId;

                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onSyncFriendHistoryMessageReceiveCompleted(packet->getUserIdentity(), packet->getFriendIdentity(), packet->getPacketID(), packet->getUpDownStatus());
                }

                break;
            }
            case ChatEvent::SYNC_GROUP_HISTORY_MESSAGE_CONFIRMATION_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                hash << ChatEvent::SYNC_GROUP_HISTORY_MESSAGE_CONFIRMATION_RECEIVED << packetId;

                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onSyncGroupHistoryMessageRequestStatus(packet->getGroupId(), packetId, ResourceManager::getInstance().getServerSyncedTime(), packet->getUpDownStatus(), packet->getRequestStatus());
                }

                break;
            }

            case ChatEvent::SYNC_GROUP_HISTORY_MESSAGE_RECEIVED:
            {
                std::string packetId = packet->getPacketID();
                hash << ChatEvent::SYNC_GROUP_HISTORY_MESSAGE_RECEIVED << packetId;

                if (duplicateChecker.isSafe(hash.str()))
                {
                    std::vector<SDKMessageDTO> groupMessage = packet->getChatMessageList();
                    std::vector<GroupActivityDTO> activityList = packet->getGroupActivities();
                    eventHandler->onSyncGroupHistoryMessageReceived(packet->getGroupId(), packet->getPacketID(), groupMessage, activityList, packet->getOldestMessageTime(), packet->getUpDownStatus());
                }

                break;
            }

            case ChatEvent::SYNC_GROUP_HISTORY_MESSAGE_RECEIVE_COMPLETED:
            {
                std::string packetId = packet->getPacketID();
                hash << ChatEvent::SYNC_GROUP_HISTORY_MESSAGE_RECEIVE_COMPLETED << packetId;

                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onSyncGroupHistoryMessageReceiveCompleted(packet->getGroupId(), packet->getPacketID(), packet->getUpDownStatus());
                }

                break;
            }
                
            case ChatEvent::ADD_NOTICE_STATUS:
            {
                std::string packetId = packet->getPacketID();
                hash << ChatEvent::ADD_NOTICE_STATUS << packetId;
                
                if (duplicateChecker.isSafe(hash.str()))
                {
                    eventHandler->onAddNoticeRequestStatus(packetId, packet->getRequestStatus());
                }

                break;
            }

        }

#ifndef WINDOWS_PHONE_8
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
#else
        Sleep(10);
#endif
    }
}

void EventProcessor::onThreadStopped()
{
    if (eventHandler)
    {
        eventHandler->onEventHandlerDetached();
    }
}
}
