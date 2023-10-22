/* 
 * File:   ResendProcessor.cpp
 * Author: dipal
 * 
 * Created on August 17, 2015, 11:52 AM
 */

#include "ResendProcessor.h"
#include "EventProcessor.h"
#include "PacketTemplate.h"
#include "ResourceManager.h"
#include "Logger.h"

#define module "ResendProc"

namespace imsdk {
ResendProcessor::ResendProcessor() {
    this->setThreadName("IM_RESEND_PROC");
}

ResendProcessor::~ResendProcessor() {
}

ResendProcessor& ResendProcessor::getInstance()
{
    static ResendProcessor resendProcessor;
    return resendProcessor;
}

void ResendProcessor::addResendPacket(ResendPacket resendPacket)
{
    resendMapMutex.lock();
    if (resendPacket.packet)
    {
        //cout<<"ADDING to resend proc destination = "<<resendPacket.destinationType<<endl;
        resendPacketMap[resendPacket.packetId] = resendPacket;
    }
    else 
    {
        //error
    }
    resendMapMutex.unlock();
}

std::shared_ptr< PacketDTO> ResendProcessor::getPacketDTO(std::string &packetId)
{
    std::shared_ptr< PacketDTO> packet = nullptr;
    
    resendMapMutex.lock();
    
    auto it = resendPacketMap.find(packetId);
    if (it!=resendPacketMap.end())
    {
        packet = (*it).second.packet;
    }
    
    resendMapMutex.unlock();
    
    return packet;
}

void ResendProcessor::removePacket(const std::string &packetID)
{
    resendMapMutex.lock();
    auto it = resendPacketMap.find(packetID);
    if (it!=resendPacketMap.end())
    {
        resendPacketMap.erase(it);
    }
    resendMapMutex.unlock();
}

void ResendProcessor::updatePendingDestination(UserIdentity userId, UserIdentity friendId, int presence)
{
    resendMapMutex.lock();
    for (auto it = resendPacketMap.begin(); it!=resendPacketMap.end(); it++)
    {
		if ((*it).second.packet->getUserIdentity() != userId || (*it).second.packet->getFriendIdentity() != friendId) continue;
        (*it).second.isWaitingForPresence = false;
        (*it).second.isWaitingForServerUpdate = false;
        (*it).second.resendCount = 0;
        if ((*it).second.destinationType==Register) continue;
        if (presence != OnlineStatus::ONLINE) //offline of away
        {
            (*it).second.destinationType = Offline;
            (*it).second.connection = ResourceManager::getInstance().getOfflineConnection();
        }
        else 
        {
            (*it).second.destinationType = Chat;
        }
    }
    resendMapMutex.unlock();
}

void ResendProcessor::expirePendingMessagesForFriend(UserIdentity userId, UserIdentity friendId)
{
    resendMapMutex.lock();
    for (auto it = resendPacketMap.begin(); it!=resendPacketMap.end(); it++)
    {
		if ((*it).second.packet->getUserIdentity() != userId || (*it).second.packet->getFriendIdentity() != friendId)
            continue;
        (*it).second.timeInQ = maxTimeInQ + 1;
    }
    resendMapMutex.unlock();
}

void ResendProcessor::expirePendingMessagesForGroup(GroupIdentity groupId)
{
    resendMapMutex.lock();
    for (auto it = resendPacketMap.begin(); it!=resendPacketMap.end(); it++)
    {
        if ((*it).second.packet->getGroupId() != groupId) 
            continue;
        (*it).second.timeInQ = maxTimeInQ + 1;
    }
    resendMapMutex.unlock();
}

void ResendProcessor::clear()
{
    resendMapMutex.lock();
    
    resendPacketMap.clear();
    
    resendMapMutex.unlock();
}

std::vector<std::string> ResendProcessor::getFriendResendPacket(UserIdentity userId)
{
    std::vector<std::string> friendResendPacketList;
    resendMapMutex.lock();
    for(auto it = resendPacketMap.begin(); it!=resendPacketMap.end();it++)
    {
		UserIdentity activeId = (*it).second.packet->getUserIdentity();
        int packetType = (*it).second.packet->getPacketType();
		if (activeId == userId && (packetType == FRIEND_CHAT_MESSAGE || packetType == FRIEND_CHAT_MESSAGE_EDIT || packetType == FRIEND_CHAT_MESSAGE_BROKEN || packetType == FRIEND_CHAT_MESSAGE_BROKEN_EDIT))
        {
            friendResendPacketList.push_back((*it).second.packetId);
        }
    }
    resendMapMutex.unlock();
    return friendResendPacketList;
}

std::vector<std::string> ResendProcessor::getGroupResendPacket()
{
    std::vector<std::string> groupResendPacketList;
    resendMapMutex.lock();
    for(auto it = resendPacketMap.begin(); it!=resendPacketMap.end();it++)
    {
        int packetType = (*it).second.packet->getPacketType();
        if(packetType == GROUP_CHAT_MESSAGE || packetType == GROUP_CHAT_MESSAGE_EDIT || packetType == GROUP_CHAT_MESSAGE_BROKEN || packetType == GROUP_CHAT_MESSAGE_BROKEN_EDIT )
        {
            groupResendPacketList.push_back((*it).second.packetId);
        }
    }
    resendMapMutex.unlock();
    return groupResendPacketList;
}

void ResendProcessor::updatedServerAddress(UserIdentity userId, UserIdentity friendId)
{
    resendMapMutex.lock();
    for (auto it = resendPacketMap.begin(); it!=resendPacketMap.end(); it++)
    {
		if ((*it).second.packet->getUserIdentity() != userId || (*it).second.packet->getFriendIdentity() != friendId) continue;

        (*it).second.isWaitingForPresence = false;
        (*it).second.isWaitingForServerUpdate = false;
        (*it).second.resendCount = 0;
    }
    resendMapMutex.unlock();
}

void ResendProcessor::updateConnection(UserIdentity userId, UserIdentity friendId, std::shared_ptr< ChatConnection> &connection)
{
    Log(module, "update connection for "<<friendId);
    resendMapMutex.lock();
    for (auto it = resendPacketMap.begin(); it!=resendPacketMap.end(); it++)
    {
		if ((*it).second.packet->getUserIdentity() != userId || (*it).second.packet->getFriendIdentity() != friendId) continue;
        (*it).second.connection = connection;
    }
    resendMapMutex.unlock();
}

void ResendProcessor::updateGroupConnection(GroupIdentity groupId, std::shared_ptr< ChatConnection> &connection)
{
    Log(module, "update connection for "<<groupId);
    resendMapMutex.lock();
    for (auto it = resendPacketMap.begin(); it!=resendPacketMap.end(); it++)
    {
        if ((*it).second.packet->getGroupId() != groupId) continue;
        (*it).second.connection = connection;
        (*it).second.isWaitingForServerUpdate = false;
    }
    resendMapMutex.unlock();
}

void ResendProcessor::updateOfflineServer(std::string offlineServerAddress, int offlineServerPort)
{
    resendMapMutex.lock();
    for (auto it = resendPacketMap.begin(); it!=resendPacketMap.end(); it++)
    {
        if ((*it).second.connection) {
            (*it).second.connection->setOfflineServer(offlineServerAddress, offlineServerPort);
        }
    }
    resendMapMutex.unlock();
}

bool ResendProcessor::isExistInResendPacketMap(const std::string& packetID)
{
    bool isExist = false;
    
    resendMapMutex.lock();
    auto it = resendPacketMap.find(packetID);
    if (it!=resendPacketMap.end())
    {
        isExist = true;
    }
    else
        isExist = false;
    resendMapMutex.unlock();
    
    return isExist;
}

void ResendProcessor::processResendTasks()
{
    std::queue<ResendPacket> q;
    
    resendMapMutex.lock();
    for (auto it = resendPacketMap.begin(); it!=resendPacketMap.end(); it++)
    {
        q.push((*it).second);
    }
    resendPacketMap.clear();
    resendMapMutex.unlock();

    while (!q.empty())
    {
        auto pop = q.front();
        q.pop();
        pop.timeInQ++;

        //trade off: skip resend first time for duplicate safety 
//        if (pop.resendCount == 1)
//        {
//            pop.resendCount++;
//            addResendPacket(pop);
//            continue;
//        }



        if (pop.isWaitingForPresence) 
        {
            pop.waitingTimeForPresence++;
        }
        else if(pop.isWaitingForServerUpdate)
        {
            pop.waitingTimeForServerUpdate++;
        }



        if (pop.connection)
        {
            switch (pop.destinationType)
            {
                case DestinationType::Chat :
                {
                    if (pop.connection->getChatServerStatus() == ChatConnection::READY && !pop.isWaitingForPresence && !pop.isWaitingForServerUpdate)
                    {
                        pop.connection->sendToChatServer(pop.byteArray);
                        pop.resendCount++;
                        Log(module, "Sending packet "<<pop.packet->getPacketType()<<" to Chat "<<pop.connection->getRegisterServerAddress()<<":"<<pop.connection->getChatServerPort()<<pop.packet->getPacketType()<<" PID:"<<pop.packet->getPacketID());
                    }
                    break;
                }
                case DestinationType::Register :
                {
                    pop.connection->sendToRegisterServer(pop.byteArray);
                    pop.resendCount++;
                    Log(module, "Sending packet "<<pop.packet->getPacketType()<<" to Register");
                    break;
                }
                case DestinationType::Offline :
                {
                    pop.connection->sendToOfflineServer(pop.byteArray);
                    pop.resendCount++;
                    Log(module, "Sending packet "<<pop.packet->getPacketType()<<" to Offline "<<pop.packet->getPacketType()<<" PID:"<<pop.packet->getPacketID());
                    break;
                }
            }
        }

        if (pop.resendCount <= ResendProcessor::maxResend && 
                pop.waitingTimeForPresence <= ResendProcessor::maxWaitingTimeForPresence && 
                pop.waitingTimeForServerUpdate <= ResendProcessor::maxWaitingTimeForServerUpdate &&
                pop.timeInQ <= ResendProcessor::maxTimeInQ)
        {
            //cout<<"readding to resend packetId = "<<pop.packetId<<" destination = "<<pop.destinationType<<endl;
            addResendPacket(pop);
        }
        //resendCount exceed, time in q exceed, presence waiting time exceeds, server update time exceeds
        else
        {
            auto packet = pop.packet;
            switch(pop.packet->getPacketType())
            {
                case ACTIVATE_DEACTIVATE_USER_ACCOUNT:
				{
					packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::ACTIVATE_DEACTIVATE_USER_ACCOUNT_STATUS, packet));
					break;
				}

                case GET_USER_INFO:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::GET_USER_INFO_DETAILS_FAILURE, packet));
                    break;
                }

                case FRIEND_REGISTER:
                {
                    packet->setFromAnonymous(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_REGISTER_FAILURE, packet));
					ResourceManager::getInstance().removeFriendInfo(packet->getUserIdentity(), packet->getFriendIdentity());
                    break;
                }
                case ANONYMOUS_REGISTER:
                {
                    packet->setFromAnonymous(true);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_REGISTER_FAILURE, packet));
					ResourceManager::getInstance().removeFriendInfo(packet->getUserIdentity(), packet->getFriendIdentity());
                    break;
                }
                case FRIEND_UNREGISTER:
                {
					ResourceManager::getInstance().removeFriendInfo(packet->getUserIdentity(), packet->getFriendIdentity());
					KeepaliveProcessor::getInstance().removeFriendKeepalive(packet->getUserIdentity(), packet->getFriendIdentity());
                    break;
                }
                case GROUP_REGISTER:
                {
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_REGISTER_FAILURE, packet));
                    ResourceManager::getInstance().removeGroupRegistration(packet->getGroupId());
                    ResourceManager::getInstance().removeGroupConnection(packet->getGroupId());
                    break;
                }
                case LIVE_STREAM_CHAT_REGISTER:
                {
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::LIVE_STREAM_CHAT_REGISTER_FAILURE, packet));
                    ResourceManager::getInstance().removeLiveStreamChatInfo(packet->getPublisherId());
                    break;
                }
                case GROUP_MEMBER_REMOVE_LEAVE:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_MEMBER_REMOVE_LEAVE_SENT, packet));
                    break;
                }
                case GROUP_MEMBER_ADD:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_MEMBER_ADD_SENT, packet));
                    break;
                }
                case GROUP_MEMBER_TYPE_CHANGE:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_MEMBER_STATUS_CHANGE_SENT, packet));
                    break;
                }
                case OFFLINE_CREATE_GROUP:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CREATED, packet));
                    break;
                }
                case GROUP_INFORMATION:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_INFORMATION_SENT, packet));
                    break;
                }
                case OFFLINE_GET_INFORMATION_WITH_MEMBERS:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_INFORMATION_WITH_MEMBERS_REQUEST_STATUS, packet));
                    break;
                }
                case OFFLINE_FRIEND_HISTORY_MESSAGE_REQUEST:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_FRIEND_HISTORY_MESSAGE_CONFIRMATION_RECEIVED, packet));
                    break;
                }
                case OFFLINE_GROUP_HISTORY_MESSAGE_REQUEST:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_HISTORY_MESSAGE_CONFIRMATION_RECEIVED, packet));
                    break;
                }
                case FRIEND_CHAT_MESSAGE:
                case FRIEND_CHAT_MESSAGE_EDIT:
                case FRIEND_CHAT_MESSAGE_BROKEN:
                case FRIEND_CHAT_MESSAGE_BROKEN_EDIT:
                case FRIEND_CHAT_MESSAGE_SEEN:
                case FRIEND_BLOCK:
		case FRIEND_UNBLOCK:
                case FRIEND_CHAT_MULTIPLE_MESSAGE_DELETE:
                {
                    if (pop.destinationType == DestinationType::Offline || pop.timeInQ > maxTimeInQ)
                    {
                        if (    packet->getPacketType() == FRIEND_CHAT_MESSAGE || 
                                packet->getPacketType() == FRIEND_CHAT_MESSAGE_EDIT ||
                                packet->getPacketType() == FRIEND_CHAT_MESSAGE_BROKEN ||
                                packet->getPacketType() == FRIEND_CHAT_MESSAGE_BROKEN_EDIT)
                        {
                            Log(module, "time in queue: "<<pop.timeInQ<<" destination type: "<<pop.destinationType);
                            Log(module, "generating failed"<<" packetId:->"<<packet->getPacketID());
                                                                                    
                            EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_FAILED_TO_SEND, packet));
                        }
			else if (    packet->getPacketType() == FRIEND_BLOCK || 
	                             packet->getPacketType() == FRIEND_UNBLOCK)
			{
			    packet->setRequestStatus(false);
    			    EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_BLOCK_UNBLOCK_CONFIRMED, packet));	
			}
                        else if(packet->getPacketType() == FRIEND_CHAT_MULTIPLE_MESSAGE_DELETE) {
                            packet->setRequestStatus(false);
                            EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_DELETE_STATUS_RECEIVED, packet));
                        }
                        
                        
                        EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_CHECK_OFFLINE_SERVER_ADDRESS, packet));
                    }
                    else if (pop.resendCount > ResendProcessor::maxResend)
                    {
                        Log(module, "max resend time out. PT:"<<pop.packet->getPacketType()<<" PID:"<<pop.packet->getPacketID());
                        if (!pop.alreadyCheckedForPresence)
                        {
                            int profileType{0};
							auto friendInfo = ResourceManager::getInstance().getFriendInfo(packet->getUserIdentity(), packet->getFriendIdentity());
                            if(friendInfo) {
                                profileType = friendInfo->getProfileType();
                            }

                            packet->setProfileType(profileType);

                            EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_CHECK_FRIEND_PRESENCE, packet));
                            pop.resendCount = 0;
                            pop.isWaitingForPresence = true;
                            pop.alreadyCheckedForPresence = true;
                            pop.waitingTimeForPresence = 0;
                            addResendPacket(pop);
                        }
                        else 
                        {
                            EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_FRIEND, packet));
                            pop.resendCount = 0;
                            pop.isWaitingForServerUpdate = true;
                            pop.waitingTimeForServerUpdate = 0;
                            addResendPacket(pop);
                        }
                    }
                    else if (pop.waitingTimeForPresence > maxWaitingTimeForPresence)
                    {
                        Log(module, "waiting presence timeout"<<pop.packet->getPacketType()<<" PID:"<<pop.packet->getPacketID());
                        pop.resendCount = 0;
                        pop.isWaitingForPresence = false;
                        pop.waitingTimeForPresence = 0;
                        addResendPacket(pop);
                    }
                    else //pop.waitingTimeForServerUpdate > maxWaitingTimeForServerUpdate
                    {
                        Log(module, "waiting server update timeout"<<pop.packet->getPacketType()<<" PID:"<<pop.packet->getPacketID());
                        //send to offline
                        pop.isWaitingForServerUpdate = false;
                        pop.waitingTimeForServerUpdate = 0;
                        pop.destinationType = DestinationType::Offline;
                        pop.resendCount = 0;
                        pop.connection = ResourceManager::getInstance().getOfflineConnection();
                        addResendPacket(pop);
						ResendProcessor::getInstance().updateConnection(pop.packet->getUserIdentity(), pop.packet->getFriendIdentity(), pop.connection);
						ResendProcessor::getInstance().updatePendingDestination(pop.packet->getUserIdentity(), pop.packet->getFriendIdentity(), DestinationType::Offline);
						ResendProcessor::getInstance().updatedServerAddress(pop.packet->getUserIdentity(), pop.packet->getFriendIdentity());
                        
                        auto packetTimeId = ResourceManager::getInstance().generatePacketIdInSDK();
						auto friendId = pop.packet->getFriendIdentity();
						auto userId = pop.packet->getUserIdentity();
                        
						auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
                        if(!friendInfo){
                            Log(module, "Friend Info Not Found.");
                            break;
                        }
                        std::string userName = friendInfo->getUserName();
						auto deviceType = friendInfo->getDeviceType();
                        auto status = OnlineStatus::AWAY;
                        auto appType = friendInfo->getAppType();
                        auto deviceToken = friendInfo->getDeviceToken();
                        auto mood = friendInfo->getMood();
                        auto iosVoipPush = friendInfo->getIosVoipPush();
                       
                        auto connection = ResourceManager::getInstance().getOfflineConnection();
                        if(!connection){
                            Log(module, "Connection Not Found.");
                            break;
                        }
                                                
                        Log(module, "Sending friend information fid:"<<friendId<<" status:"<<status<<" apptype:"<<appType);
                        packetBuilder = std::make_shared<ChatPacketBuilder>();

                        auto ownProfileType = ResourceManager::getInstance().isUserPage(userId) ? UserProfileType::PAGE : UserProfileType::DEFAULT;
                        auto builtPacket = packetBuilder->makeOfflineFriendInformation(userId, friendId, packetTimeId.packetId, userName, deviceType, status, appType, deviceToken, mood, iosVoipPush, ResourceManager::getInstance().getDeviceType(), ownProfileType, friendInfo->getProfileType());
                        if (!builtPacket.byteArray)
                        {
                            Log(module, "Friend info packet builder error");
                            break;
                        }
                        
                        auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);
                        if (sendCode<0)
                        {
                            Log(module, "Friend info sending socket returned "<<sendCode);
                            break;
                        }
                        Log(module, "Adding "<<packetTimeId.packetId<<" for resend");
                        ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Offline));
                        
                        Log(module, "Sending blank message fid:"<<friendId<<" status:"<<status<<" apptype:"<<appType);
                        auto blankMessagePacketId = ResourceManager::getInstance().generatePacketIdInSDK();
                        long long messageDate = ResourceManager::getInstance().gettime() - ResourceManager::getInstance().getTimeDifference();
                        std::string message="";
						auto builtBlankMessagePacket = packetBuilder->makeFriendChatMessage(userId, friendId, blankMessagePacketId.packetId, MessageType::BLANK_MESSAGE, 0, message, messageDate, false, ResourceManager::getInstance().getDeviceType(), ResourceManager::getInstance().appVersion, ResourceManager::getInstance().getAppType(), ResourceManager::getInstance().getUserId());
                        if (!builtBlankMessagePacket.byteArray)
                        {
                            Log(module, "Blank message packet builder error");
                            break;
                        }
                        
                        sendCode = connection->sendToOfflineServer(builtBlankMessagePacket.byteArray);
                        if (sendCode<0)
                        {
                            Log(module, "Friend info sending socket returned "<<sendCode);
                            break;
                        }
                        Log(module, "Adding "<<packetTimeId.packetId<<" for resend");
                        ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtBlankMessagePacket.byteArray, builtBlankMessagePacket.packet, connection, ResendProcessor::DestinationType::Offline));
                        
                    }
                    break;
                }
                case GROUP_CHAT_MESSAGE:
                {
                    Log(module, "generating failed"<<" packetId:->"<<packet->getPacketID());
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_FAILED_TO_SEND, packet));
                    break;
                }
                
                case GROUP_CHAT_MESSAGE_SEEN:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_SEEN_CONFIRMATION, packet));
                    break;
                }
                
                case GROUP_CHAT_MESSAGE_SEEN_LIST:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_MESSAGE_SEEN_LIST_CONFIRMATION_RECEIVED, packet));
                    break;
                }
                
                case GROUP_CHAT_MULTIPLE_MESSAGE_DELETE:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_DELETE_CONFIRMED, packet));
                    break;
                }
                
                case OFFLINE_GET_CONVERSATION_REQUEST:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::CONVERSATION_LIST_REQUEST_STATUS, packet));
                    break;
                }
                
                case DELETE_CONVERSATION_REQUEST:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::CONVERSATION_LIST_DELETE_REQUEST_STATUS, packet));
                    break;
                }
                
                case MARK_CONVERSATION_SEEN_REQUEST:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::MARK_CONVERSATION_LIST_SEEN_REQUEST_STATUS, packet));
                    break;
                }

                case OFFLINE_GET_REQUEST_CONFIRMATION:
                {
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_CHECK_OFFLINE_SERVER_ADDRESS, packet));
                    break;
                }
                case OFFLINE_GROUP_IP_PORT:
                {
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_GROUP, packet));
                    break;
                }
                case PUBLIC_ROOM_REGISTER:
                case OFFLINE_PUBLIC_GET_ROOM_IPPORT:
                {
                    ResourceManager::getInstance().removeRoomInfo(packet->getRoomId());
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_CHAT_REGISTER_FAILURE, packet));
                    break;
                }
                case PUBLIC_ROOM_CHAT_MESSAGE:
                case PUBLIC_ROOM_CHAT_MESSAGE_EDIT:
                case PUBLIC_ROOM_CHAT_MESSAGE_BROKEN:
                case PUBLIC_ROOM_CHAT_MESSAGE_BROKEN_EDIT:
                {
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_CHAT_FAILED_TO_SEND, packet));
                    break;
                }
                case OFFLINE_PUBLIC_ROOM_LIST_REQUEST:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_LIST_REQUEST_STATUS, packet));
                    break;
                }
                case OFFLINE_ROOM_INFORMATION_REQUEST:
                {
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_INFORMATION_REQUEST_FAILED, packet));
                    break;
                }
                case OFFLINE_ROOM_GET_HISTORY:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_CHAT_HISTORY_REQUEST_STATUS, packet));
                    break;
                }
                case PUBLIC_CHAT_GET_MEMBER_LIST:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_MEMBER_LIST_REQUEST_STATUS, packet));
                    break;
                }
                case PUBLIC_CHAT_DELETE_MESSAGE:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_DELETE_MESSAGE_REQUEST_STATUS, packet));
                    break;
                }
                case PUBLIC_CHAT_LIKE_A_MESSAGE:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_LIKE_UNLIKE_REQUEST_STATUS, packet));
                    break;
                }                
                case PUBLIC_CHAT_UNLIKE_A_MESSAGE:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_LIKE_UNLIKE_REQUEST_STATUS, packet));
                    break;
                }
                case PUBLIC_CHAT_REPORT_A_MESSAGE:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_REPORT_A_MESSAGE_REQUEST_STATUS, packet));
                    break;
                }
                case PUBLIC_CHAT_LIKE_MEMBER_LIST_REQUEST:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_LIKE_MEMBER_LIST_REQUEST_STATUS, packet));
                    break;
                }
                case OFFLINE_PUBLIC_CHAT_CATEGORY_LIST_REQUEST:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_PUBLIC_CHAT_CATEGORY_LIST_REQUEST_STATUS, packet));
                    break;
                }
                
                case SHADOW_IDS_INFO_REQUEST:
                {
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHADOW_IDS_INFO_REQUEST_FAILED, packet));
                    break;
                }
                case GROUP_FILE_SESSION_REQUEST:
                {
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_FILE_TRANSFER_SESSION_REQUEST_FAILED, packet));
                    break;
                }
                case GROUP_FILE_STREAM_REQUEST:
                {
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_FILE_TRANSFER_STREAM_REQUEST_FAILED, packet));
                    break;
                }
                case FRIEND_FILE_SESSION_REQUEST:
                {
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_FILE_TRANSFER_SESSION_REQUEST_FAILED, packet));
                    break;
                }
                case FRIEND_FILE_STREAM_REQUEST:
                {
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_FILE_TRANSFER_STREAM_REQUEST_FAILED, packet));
                    break;
                }
                case FRIEND_GET_CHAT_MESSAGE:
                {
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_GET_CHAT_MESSAGE_FAILED_TO_SEND, packet));
                    break;
                }
                case GROUP_GET_CHAT_MESSAGE:
                {
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_GET_CHAT_MESSAGE_FAILED_TO_SEND, packet));
                    break;
                }
                case LIVE_STREAM_CHAT_MESSAGE:
                {
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::LIVE_STREAM_CHAT_MESSAGE_FAILED, packet));
                    break;
                }


                case SYNC_CONVERSATION_CONFIRMATION:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::SYNC_CONVERSATION_CONFIRMATION_RECEIVED, packet));
                    break;
                }

                case SYNC_FRIEND_HISTORY_MESSAGE_CONFIRMATION:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::SYNC_FRIEND_HISTORY_MESSAGE_CONFIRMATION_RECEIVED, packet));
                    break;
                }

                case SYNC_GROUP_HISTORY_MESSAGE_CONFIRMATION:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::SYNC_GROUP_HISTORY_MESSAGE_CONFIRMATION_RECEIVED, packet));
                    break;
                }
                    
                case ADD_NOTICE:
                {
                    packet->setRequestStatus(false);
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::ADD_NOTICE_STATUS, packet));
                    break;
                }
            }
        }
    }
}

void ResendProcessor::runner()
{
#ifdef IMSDK_LOG
#ifdef __APPLE__
    pthread_setname_np(getThreadName().c_str());
#endif
#endif
    while (isRunning())
    {
        processResendTasks();
#ifndef WINDOWS_PHONE_8
        std::this_thread::sleep_for(std::chrono::milliseconds(900));
#else
        Sleep(900);
#endif

    }
}
}
