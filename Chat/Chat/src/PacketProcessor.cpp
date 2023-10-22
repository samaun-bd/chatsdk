/*
 * File:   PacketProcessor.cpp
 * Author: dipal
 *
 * Created on August 17, 2015, 2:32 PM
 */

#include <algorithm>

#include "PacketProcessor.h"
#include "PacketTemplate.h"
#include "ResendProcessor.h"
#include "EventProcessor.h"
#include "ResourceManager.h"
#include "Chat.h"
#include "KeepaliveProcessor.h"
#include "Logger.h"
#include "DataEncryption.h"
#include "cloud/manager.h"
#include "InternetChecker.h"

#define module "PacketProc"

namespace imsdk {
	PacketProcessor::PacketProcessor() {

		packetBuilder = std::make_shared<ChatPacketBuilder>();
		this->setThreadName("IM_PP_PROC");
	}

	PacketProcessor::~PacketProcessor() {
	}

	PacketProcessor& PacketProcessor::getInstance() {
		static PacketProcessor packetProcessor;
		return packetProcessor;
	}

	void PacketProcessor::handleBrokenChat(std::shared_ptr< PacketDTO> packet)
	{
		UserIdentity friendId = packet->getUserIdentity();
		UserIdentity userId = packet->getFriendIdentity();

		auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);

		if (friendInfo)
		{
			auto connection = friendInfo->getConnection();
			std::string packetId = packet->getPacketID();
			packetId += "_" + ResourceManager::toString(packet->getSequenceNumber());
			BuiltPacket deliveredPacket = packetBuilder->makeFriendChatMessageDelivered(userId, friendId, packetId);
			connection->sendToChatServer(deliveredPacket.byteArray);
		}

		Log(module, "handle broken. packetId " << packet->getPacketID());
		std::string brokenPacketId = packet->getPacketID();

		Log(module, "broken packetId " << brokenPacketId);

		auto it = brokenPacketMap.find(brokenPacketId);
		if (it != brokenPacketMap.end())
		{
			if (!(*it).second.isComplete())
			{
				if ((*it).second.message[packet->getSequenceNumber()].empty())
				{
					std::string encryptedMessage = packet->getMessage();
					ByteArray encryptedMessageBytes(encryptedMessage);
					ByteArray decryptedMessageBytes = ipvsdk::security::DataEncryption::decryptMessage(encryptedMessageBytes, *(ResourceManager::getInstance().getEncryptionDecryptionKey()));
					packet->setMessage(decryptedMessageBytes.getString(0, decryptedMessageBytes.size()));

					(*it).second.message[packet->getSequenceNumber()] = packet->getMessage();
					(*it).second.arrivedPacket++;
				}
			}

			if ((*it).second.isComplete())
			{
				packet->setMessage(brokenPacketMap[brokenPacketId].getMessage());

				//            packet->setMessageDate(packet->getMessageDate() + ResourceManager::getInstance().getTimeDifference());
				if (packet->getPacketType() == FRIEND_CHAT_MESSAGE_BROKEN)
				{
					packet->setOnline(true);
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_NEW_CHAT_RECEIVED, packet));
				}
				else if (packet->getPacketType() == FRIEND_CHAT_MESSAGE_BROKEN_EDIT)
				{
					packet->setOnline(true);
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_EDITED, packet));
				}

				if (friendInfo)
				{
					auto connection = friendInfo->getConnection();
					BuiltPacket deliveredPacket = packetBuilder->makeFriendChatMessageDelivered(userId, friendId, brokenPacketId);
					connection->sendToChatServer(deliveredPacket.byteArray);
				}
				brokenPacketMap.erase(brokenPacketId);
			}
		}
		else{
			BrokenMessage msg;
			msg.arrivedPacket = 1;
			msg.totalPacket = packet->getNumberOfMessage();
			msg.message.resize(packet->getNumberOfMessage());

			std::string encryptedMessage = packet->getMessage();
			ByteArray encryptedMessageBytes(encryptedMessage);
			ByteArray decryptedMessageBytes = ipvsdk::security::DataEncryption::decryptMessage(encryptedMessageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
			packet->setMessage(decryptedMessageBytes.getString(0, decryptedMessageBytes.size()));

			msg.message[packet->getSequenceNumber()] = packet->getMessage();
			brokenPacketMap[brokenPacketId] = msg;
		}

		KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId);
	}

	void PacketProcessor::handleBrokenGroupChat(std::shared_ptr< PacketDTO> packet)
	{
		UserIdentity groupId = packet->getGroupId();
		UserIdentity friendId = packet->getUserIdentity();

		auto connection = ResourceManager::getInstance().getGroupConnection(groupId);

		if (connection)
		{
			std::string packetId = packet->getPacketID();
			packetId += "_" + ResourceManager::toString(packet->getSequenceNumber());
			BuiltPacket deliveredPacket = packetBuilder->makeGroupChatMessageDelivered(ResourceManager::getInstance().getUserId(), friendId, groupId, packetId);
			connection->sendToChatServer(deliveredPacket.byteArray);
		}

		//    std::string chunkNumber = "";
		//    chunkNumber += ResourceManager::toString(packet->getSequenceNumber());
		//    std::string brokenPacketId;
		//    int brokenPacketIdLen = (int)packet->getPacketID().length() - (int)chunkNumber.length();
		//    brokenPacketId = packet->getPacketID().substr(0,brokenPacketIdLen);

		std::string brokenPacketId = packet->getPacketID();

		auto it = brokenGroupPacketMap.find(brokenPacketId);
		if (it != brokenGroupPacketMap.end())
		{
			if (!(*it).second.isComplete())
			{
				if ((*it).second.message[packet->getSequenceNumber()].empty())
				{
					std::string encryptedMessage = packet->getMessage();
					ByteArray encryptedMessageBytes(encryptedMessage);
					ByteArray decryptedMessageBytes = ipvsdk::security::DataEncryption::decryptMessage(encryptedMessageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
					packet->setMessage(decryptedMessageBytes.getString(0, decryptedMessageBytes.size()));

					(*it).second.message[packet->getSequenceNumber()] = packet->getMessage();
					(*it).second.arrivedPacket++;
				}
			}

			if ((*it).second.isComplete())
			{
				packet->setMessage(brokenGroupPacketMap[brokenPacketId].getMessage());

				//            packet->setMessageDate(packet->getMessageDate() + ResourceManager::getInstance().getTimeDifference());
				if (packet->getPacketType() == GROUP_CHAT_MESSAGE_BROKEN)
				{
					packet->setOnline(true);
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_NEW_CHAT_RECEIVED, packet));
				}
				else if (packet->getPacketType() == GROUP_CHAT_MESSAGE_BROKEN_EDIT)
				{
					packet->setOnline(true);
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_EDITED, packet));
				}

				if (connection)
				{
					BuiltPacket deliveredPacket = packetBuilder->makeGroupChatMessageDelivered(ResourceManager::getInstance().getUserId(), friendId, groupId, brokenPacketId);
					connection->sendToChatServer(deliveredPacket.byteArray);
				}
				brokenGroupPacketMap.erase(brokenPacketId);
			}
		}
		else{
			BrokenMessage msg;
			msg.arrivedPacket = 1;
			msg.totalPacket = packet->getNumberOfMessage();
			msg.message.resize(packet->getNumberOfMessage());

			std::string encryptedMessage = packet->getMessage();
			ByteArray encryptedMessageBytes(encryptedMessage);
			ByteArray decryptedMessageBytes = ipvsdk::security::DataEncryption::decryptMessage(encryptedMessageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
			packet->setMessage(decryptedMessageBytes.getString(0, decryptedMessageBytes.size()));

			msg.message[packet->getSequenceNumber()] = packet->getMessage();
			brokenGroupPacketMap[brokenPacketId] = msg;
		}

		KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);
	}

	void PacketProcessor::handleBrokenPublicRoomChat(std::shared_ptr< PacketDTO> packet){

		RoomIdentity roomId = packet->getRoomId();
		UserIdentity friendId = packet->getUserIdentity();

		auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
		if (!roomInfo)
		{
			Log(module, "Roominfo does not exists for broken chat packet for roomId " << roomId);
			return;
		}

		auto connection = roomInfo->getConnection();
		if (connection)
		{
			std::string packetId = packet->getPacketID();
			packetId += "_" + ResourceManager::toString(packet->getSequenceNumber());
			BuiltPacket deliveredPacket = packetBuilder->makePublicRoomChatMessageDeliveredPacket(ResourceManager::getInstance().getUserId(), friendId, roomId, packetId);
			connection->sendToChatServer(deliveredPacket.byteArray);
		}

		std::string packetId = packet->getPacketID();

		auto it = brokenPublicChatPacketMap.find(packetId);
		if (it != brokenPublicChatPacketMap.end())
		{
			if (!(*it).second.isComplete())
			{
				if ((*it).second.message[packet->getSequenceNumber()].empty())
				{
					(*it).second.message[packet->getSequenceNumber()] = packet->getMessage();
					(*it).second.arrivedPacket++;
				}
			}

			if ((*it).second.isComplete())
			{
				packet->setMessage(brokenPublicChatPacketMap[packetId].getMessage());

				//            packet->setMessageDate(packet->getMessageDate() + ResourceManager::getInstance().getTimeDifference());
				if (packet->getPacketType() == PUBLIC_ROOM_CHAT_MESSAGE_BROKEN)
				{
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_CHAT_MESSAGE_RECEIVED, packet));
				}
				else if (packet->getPacketType() == PUBLIC_ROOM_CHAT_MESSAGE_BROKEN_EDIT)
				{
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_CHAT_EDITED, packet));
				}
				brokenPublicChatPacketMap.erase(packetId);
			}
		}
		else{
			BrokenMessage msg;
			msg.arrivedPacket = 1;
			msg.totalPacket = packet->getNumberOfMessage();
			msg.message.resize(packet->getNumberOfMessage());
			msg.message[packet->getSequenceNumber()] = packet->getMessage();
			brokenPublicChatPacketMap[packetId] = msg;
		}

		KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(roomId);
	}

	ByteArray PacketProcessor::handleBrokenDataPacket(std::shared_ptr< PacketDTO> packet)
	{
		GroupIdentity groupId = packet->getGroupId();

		auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
		if (connection)
		{
			std::string packetId = packet->getPacketID();
			int sequenceNumber = packet->getSequenceNumber();
			packetId += "_" + ResourceManager::toString(packet->getSequenceNumber());
			BuiltPacket deliveredPacket = packetBuilder->makeGroupBrokenPacketConfirmation(ResourceManager::getInstance().getUserId(), groupId, packetId, sequenceNumber);
			connection->sendToChatServer(deliveredPacket.byteArray);
		}

		std::string chunkNumber = "";
		chunkNumber += ResourceManager::toString(packet->getSequenceNumber());
		std::string brokenPacketId;
		int brokenPacketIdLen = (int)packet->getPacketID().length() - (int)chunkNumber.length();
		brokenPacketId = packet->getPacketID().substr(0, brokenPacketIdLen);

		auto it = brokenData.find(brokenPacketId);
		if (it != brokenData.end())
		{
			if (!(*it).second.isComplete())
			{
				if ((*it).second.packetData[packet->getSequenceNumber()]->size() != 0)
				{
					(*it).second.packetData[packet->getSequenceNumber()] = packet->getDataBytes();
					(*it).second.arrivedPacket++;
				}
			}

			if ((*it).second.isComplete())
			{
				KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);

				ByteArray ba = brokenData[brokenPacketId].getTotalPacket();
				brokenData.erase(brokenPacketId);
				return ba;
			}
		}
		else{
			BrokenPacket pkt;
			pkt.arrivedPacket = 1;
			pkt.totalPacket = packet->getNumberOfMessage();
			pkt.packetData.resize(packet->getNumberOfMessage());
			for (int i = 0; i < packet->getNumberOfMessage(); i++){
				pkt.packetData[i] = std::make_shared<ByteArray>();
			}
			pkt.packetData[packet->getSequenceNumber()] = packet->getDataBytes();
			brokenData[brokenPacketId] = pkt;

			auto completeIt = brokenData.find(brokenPacketId);
			if ((*completeIt).second.isComplete())
			{
				ByteArray ba = brokenData[brokenPacketId].getTotalPacket();
				brokenData.erase(brokenPacketId);
				return ba;
			}
		}

		ByteArray ba;
		return ba;
	}

	ByteArray PacketProcessor::handleOfflineBrokenPacket(std::shared_ptr< PacketDTO> packet)
	{
		auto connection = ResourceManager::getInstance().getOfflineConnection();
		if (connection)
		{
			std::string packetId = packet->getPacketID();
			int sequenceNumber = packet->getSequenceNumber();
			//        packetId += "_"+ResourceManager::toString(packet->getSequenceNumber());
			BuiltPacket deliveredPacket = packetBuilder->makeOfflineBrokenPacketConfirmation(ResourceManager::getInstance().getUserId(), packetId, sequenceNumber);
			//        connection->sendToChatServer(deliveredPacket.byteArray);
			connection->sendToOfflineServer(deliveredPacket.byteArray);
		}

		//    std::string chunkNumber = "";
		//    chunkNumber += ResourceManager::toString(packet->getSequenceNumber());
		//    std::string brokenPacketId;
		//    int brokenPacketIdLen = packet->getPacketID().length() - chunkNumber.length();
		//    brokenPacketId = packet->getPacketID().substr(0,brokenPacketIdLen);

		//    cout<<"Total packet: "<<packet->getNumberOfMessage()<<" ;sequence number: "<<packet->getSequenceNumber()<<endl;
		auto it = brokenData.find(packet->getPacketID());
		if (it != brokenData.end())
		{
			if (!(*it).second.isComplete())
			{
				if ((*it).second.packetData[packet->getSequenceNumber()]->size() == 0)
				{
					(*it).second.packetData[packet->getSequenceNumber()] = packet->getDataBytes();
					(*it).second.arrivedPacket++;
				}
			}

			if ((*it).second.isComplete())
			{
				//brokenData[packet->getPacketID()].getTotalPacket().printByteArray();
				ByteArray ba = brokenData[packet->getPacketID()].getTotalPacket();
				brokenData.erase(packet->getPacketID());
				return ba;
			}
		}
		else{
			BrokenPacket pkt;
			pkt.arrivedPacket = 1;
			pkt.totalPacket = packet->getNumberOfMessage();
			pkt.packetData.resize(packet->getNumberOfMessage());
			for (int i = 0; i < packet->getNumberOfMessage(); i++){
				pkt.packetData[i] = std::make_shared<ByteArray>();
			}
			pkt.packetData[packet->getSequenceNumber()] = packet->getDataBytes();
			brokenData[packet->getPacketID()] = pkt;

			auto completeIt = brokenData.find(packet->getPacketID());
			if ((*completeIt).second.isComplete())
			{
				ByteArray ba = brokenData[packet->getPacketID()].getTotalPacket();
				brokenData.erase(packet->getPacketID());
				return ba;
			}
		}
		ByteArray ba;
		return ba;
	}

	ByteArray PacketProcessor::handleRoomBrokenPacket(std::shared_ptr< PacketDTO> packet)
	{
		RoomIdentity roomId = packet->getRoomId();
		auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);

		if (!roomInfo)
		{
			Log(module, "Room Info Not Found for roomId: " + roomId);
			return{};
		}

		auto connection = roomInfo->getConnection();
		if (connection)
		{
			std::string packetId = packet->getPacketID();
			int sequenceNumber = packet->getSequenceNumber();
			BuiltPacket deliveredPacket = packetBuilder->makeRoomBrokenPacketConfirmation(ResourceManager::getInstance().getUserId(), roomId, packetId, sequenceNumber);
			connection->sendToChatServer(deliveredPacket.byteArray);
		}
		else
		{
			Log(module, "Room Info Not Found for roomId: " + roomId);
			return{};
		}

		auto it = brokenData.find(packet->getPacketID());
		if (it != brokenData.end())
		{
			if (!(*it).second.isComplete())
			{
				if ((*it).second.packetData[packet->getSequenceNumber()]->size() == 0)
				{
					(*it).second.packetData[packet->getSequenceNumber()] = packet->getDataBytes();
					(*it).second.arrivedPacket++;
				}
			}

			if ((*it).second.isComplete())
			{
				ByteArray ba = brokenData[packet->getPacketID()].getTotalPacket();
				brokenData.erase(packet->getPacketID());
				return ba;
			}
		}
		else
		{
			BrokenPacket pkt;
			pkt.arrivedPacket = 1;
			pkt.totalPacket = packet->getNumberOfMessage();
			pkt.packetData.resize(packet->getNumberOfMessage());
			for (int i = 0; i < packet->getNumberOfMessage(); i++){
				pkt.packetData[i] = std::make_shared<ByteArray>();
			}
			pkt.packetData[packet->getSequenceNumber()] = packet->getDataBytes();
			brokenData[packet->getPacketID()] = pkt;

			auto completeIt = brokenData.find(packet->getPacketID());
			if ((*completeIt).second.isComplete())
			{
				ByteArray ba = brokenData[packet->getPacketID()].getTotalPacket();
				brokenData.erase(packet->getPacketID());
				return ba;
			}
		}


		ByteArray ba;
		return ba;
	}

	void PacketProcessor::createSDKMessageDTOListFromPacket(std::shared_ptr< PacketDTO> packet, bool isFromHistoryBroken)
	{
		std::vector<SDKMessageDTO> chatMessageList;
		std::vector<std::shared_ptr< PacketDTO>> messageList = packet->getMessageList();

		for (std::vector<std::shared_ptr< PacketDTO>>::size_type i = 0; i < messageList.size(); i++)
		{
			SDKMessageDTO chatMessageDTO;
			chatMessageDTO.setDirection(messageList[i]->getUpDownStatus());
			chatMessageDTO.setSecretVisible(messageList[i]->getIsSecretVisible());

			std::string encryptedMessage = messageList[i]->getMessage();
			ByteArray encryptedMessageBytes(encryptedMessage);
			ByteArray decryptedMessage = ipvsdk::security::DataEncryption::decryptMessage(encryptedMessageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
			messageList[i]->setMessage(decryptedMessage.getString(0, decryptedMessage.size()));
			chatMessageDTO.setMessage(messageList[i]->getMessage());

			chatMessageDTO.setMessageDate(messageList[i]->getMessageDate());
			chatMessageDTO.setMessageType(messageList[i]->getMessageType());
			chatMessageDTO.setPacketId(messageList[i]->getPacketID());
			chatMessageDTO.setSenderId(messageList[i]->getUserIdentity());

            if (messageList[i]->getMessageStatus() < MessageStatus::DELIVERED_STATUS)
            {
                chatMessageDTO.setMessageStatus(MessageStatus::DELIVERED_STATUS);
            }
            else
            {
                chatMessageDTO.setMessageStatus(messageList[i]->getMessageStatus());
            }

			if (!isFromHistoryBroken)
			{
                if (messageList[i]->getUserIdentity() == packet->getUserIdentity())
				{
					chatMessageDTO.setReceiverId(packet->getFriendIdentity());
				}
				else
				{
					chatMessageDTO.setReceiverId(packet->getUserIdentity());
				}
			}
            else
            {
                chatMessageDTO.setReceiverId(messageList[i]->getFriendIdentity());
            }

			chatMessageDTO.setTimeOut(messageList[i]->getTimeout());

			if (messageList[i]->getPacketType() == FRIEND_CHAT_MESSAGE_EDIT){
				chatMessageDTO.setIsEdited(true);
			}
			else
			{
				chatMessageDTO.setIsEdited(false);
			}
			chatMessageList.push_back(chatMessageDTO);
		}
		packet->setChatMessageList(chatMessageList);
	}

	std::vector<SDKMessageDTO> PacketProcessor::generateSDKMessageDTOListForGroupFromPacket(std::vector<std::shared_ptr< PacketDTO>> messageList)
	{
		std::vector<SDKMessageDTO> chatMessageList;

		for (std::vector<std::shared_ptr< PacketDTO>>::size_type i = 0; i < messageList.size(); i++)
		{
			SDKMessageDTO chatMessageDTO;
			chatMessageDTO.setDirection(messageList[i]->getUpDownStatus());

			chatMessageDTO.setMessage(messageList[i]->getMessage());

			chatMessageDTO.setMessageDate(messageList[i]->getMessageDate());
			chatMessageDTO.setMessageType(messageList[i]->getMessageType());
			chatMessageDTO.setPacketId(messageList[i]->getPacketID());
			chatMessageDTO.setSenderId(messageList[i]->getUserIdentity());

			if (messageList[i]->getPacketType() == GROUP_CHAT_MESSAGE_EDIT){
				chatMessageDTO.setIsEdited(true);
			}
			else
			{
				chatMessageDTO.setIsEdited(false);
			}

			chatMessageList.push_back(chatMessageDTO);
		}
		return chatMessageList;
	}

	void PacketProcessor::processPacketProcessTasks()
	{
		if (empty()) {
			return;
		}

		ByteArray byteArray = top();
		pop();

		if (byteArray.size() == 0) {
			return;
		}

        Log(module, "Parsing packet : firstByte: " << (int) byteArray[0]);
        std::shared_ptr< PacketDTO> packet(parser.parse(byteArray).packet);
        
        //    cout<<"Processing packet "<<byteArray[0]<<endl;
        //    cout<<"full byte array: "<<byteArray.toString()<<endl;
        if (!packet) {
            Log(module, "Parsing failed packet : " << byteArray.toString());
            EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_ERROR, packet, ChatError::PARSING_FAILED));
            return;
        }
        
        std::stringstream hash;
        
		Log(module, "Processing packet " << packet->getPacketType());

		switch (packet->getPacketType()) {

		case FRIEND_REGISTER_CONFIRMATION:
		{
            std::string packetId = packet->getPacketID();
			auto resendPacketTodel = ResendProcessor::getInstance().getPacketDTO(packetId);
			if (resendPacketTodel)
			{
				ResendProcessor::getInstance().removePacket(packet->getPacketID());

				packet->setUserIdentity(resendPacketTodel->getUserIdentity());
				auto friendInfo = ResourceManager::getInstance().getFriendInfo(packet->getUserIdentity(), packet->getFriendIdentity());
				std::shared_ptr< ChatConnection> connection = nullptr;
				if (friendInfo)
				{
					connection = friendInfo->getConnection();
					connection->setChatServerPort(packet->getChatBindingPort());
				}

				long long serverTime = packet->getServerDate();
				Log(module, "server time " << serverTime);
				time_t myTime = (time_t)(serverTime / 1000);
				Log(module, "Received server time " << ctime(&myTime));
				long long timeDifference = serverTime - ResourceManager::getInstance().gettime();
				Log(module, "Time diff " << timeDifference);
				ResourceManager::getInstance().setTimeDifference(timeDifference);

				ResendProcessor::getInstance().updatedServerAddress(packet->getUserIdentity(), packet->getFriendIdentity());

				//            packet->setServerDate(packet->getServerDate() + ResourceManager::getInstance().getTimeDifference());
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SERVER_TIME_DIFFERENCE_SYNCED, nullptr));

				packet->setFromAnonymous(false);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_REGISTER_SUCCESS, packet));
				BuiltPacket keepalivePacket = packetBuilder->makeFriendChatIdel(packet->getUserIdentity(), packet->getFriendIdentity(), ResourceManager::getInstance().getDeviceType());
				if (keepalivePacket.byteArray)
				{
					if (connection)
					{
						KeepaliveProcessor::getInstance().addFriendKeepalivePacket(packet->getUserIdentity(), packet->getFriendIdentity(), OnlineStatus::ONLINE, std::make_shared<KeepalivePacket>(connection, keepalivePacket.byteArray));
						connection->sendToChatServer(keepalivePacket.byteArray);
						auto packetTimeId = ResourceManager::getInstance().generatePacketIdInSDK();
						auto resendPacket = ResendProcessor::ResendPacket(packetTimeId.packetId, keepalivePacket.byteArray, keepalivePacket.packet, connection, ResendProcessor::Chat, 0);
						ResendProcessor::getInstance().addResendPacket(resendPacket);
					}
				}
				else
				{
					Log(module, "Packet builder error");
				}
			}
			break;
		}

        case ACTIVATE_DEACTIVATE_USER_ACCOUNT_CONFIRMATION:
		{
            std::string packetId = packet->getPacketID();
			auto delPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
			if (delPacket)
			{
				packet->setRequestStatus(true);
				ResendProcessor::getInstance().removePacket(packet->getPacketID());
                EventProcessor::getInstance().push(ChatEvent(ChatEvent::ACTIVATE_DEACTIVATE_USER_ACCOUNT_STATUS, packet));
			}
			break;
		}

        case USER_INFO_DETAILS:
        {
            std::string packetId = packet->getPacketID();
            auto delPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
            if (delPacket)
            {
                packet->setRequestStatus(true);
                ResendProcessor::getInstance().removePacket(packet->getPacketID());
                EventProcessor::getInstance().push(ChatEvent(ChatEvent::GET_USER_INFO_DETAILS_RECEIVED, packet));
            }
            break;
        }

		case GROUP_REGISTER_CONFIRMATION:
		{
            std::string packetId = packet->getPacketID();

			auto resendPacketTodel = ResendProcessor::getInstance().getPacketDTO(packetId);
			if (resendPacketTodel)
			{
				ResendProcessor::getInstance().removePacket(packet->getPacketID());

				if (!packet->isMemberInGroup())
				{
					Log(module, "Removed group " << packet->getGroupId() << " because server said member not in group.");
                    ResourceManager::getInstance().removeGroupRegistration(packet->getGroupId());
                    ResourceManager::getInstance().removeGroupConnection(packet->getGroupId());
					KeepaliveProcessor::getInstance().removeGroupKeepalive(packet->getGroupId());
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_REGISTER_FAILURE, packet));
					ResendProcessor::getInstance().expirePendingMessagesForGroup(packet->getGroupId());
					break;
				}

				std::shared_ptr< ChatConnection> connection = ResourceManager::getInstance().getGroupConnection(packet->getGroupId());
				if (connection)
				{
					Log(module, "Chat binding port received from server: " << packet->getChatBindingPort());
					connection->setChatServerPort(packet->getChatBindingPort());

					long long serverTime = packet->getServerDate();
					long long timeDifference = serverTime - ResourceManager::getInstance().gettime();
					ResourceManager::getInstance().setTimeDifference(timeDifference);

					//                packet->setServerDate(packet->getServerDate() + ResourceManager::getInstance().getTimeDifference());

					EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_REGISTER_SUCCESS, packet));
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::SERVER_TIME_DIFFERENCE_SYNCED, nullptr));
					BuiltPacket keepalivePacket = packetBuilder->makeGroupChatIdel(ResourceManager::getInstance().getUserId(), packet->getGroupId(), ResourceManager::getInstance().getDeviceType());
					if (keepalivePacket.byteArray)
					{
						KeepaliveProcessor::getInstance().addGroupKeepalivePacket(packet->getGroupId(), std::make_shared<KeepalivePacket>(connection, keepalivePacket.byteArray));
						connection->sendToChatServer(keepalivePacket.byteArray);
						auto packetTimeId = ResourceManager::getInstance().generatePacketIdInSDK();
						auto resendPacket = ResendProcessor::ResendPacket(packetTimeId.packetId, keepalivePacket.byteArray, keepalivePacket.packet, connection, ResendProcessor::Chat, 0);
						ResendProcessor::getInstance().addResendPacket(resendPacket);
					}
					else
					{
						Log(module, "Packet builder error");
					}
					ResendProcessor::getInstance().updateGroupConnection(packet->getGroupId(), connection);
					//ResendProcessor::getInstance().removePacket(packet->getPacketID());

					auto blankMessagePacketId = ResourceManager::getInstance().generatePacketIdInSDK().packetId;
					long long messageDate = ResourceManager::getInstance().gettime() - ResourceManager::getInstance().getTimeDifference();

					std::string message = "";
					auto builtBlankMessagePacket = packetBuilder->makeGroupChatMessage(ResourceManager::getInstance().getUserId(), packet->getGroupId(), blankMessagePacketId, MessageType::BLANK_MESSAGE, message, messageDate);

					if (!builtBlankMessagePacket.byteArray)
					{
						Log(module, "blank message packet builder error");
						break;
					}

					int sendCode = connection->sendToChatServer(builtBlankMessagePacket.byteArray);
					if (sendCode < 0)
					{
						Log(module, "Group blank message sending socket returned " << sendCode);
						break;
					}
					auto resendPacket = ResendProcessor::ResendPacket(blankMessagePacketId, builtBlankMessagePacket.byteArray, builtBlankMessagePacket.packet, connection, ResendProcessor::Chat, 0);
					ResendProcessor::getInstance().addResendPacket(resendPacket);
				}
				else
				{
					Log(module, "Connection not found");
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_ERROR, packet, ChatError::CONNECTION_NOT_FOUND));
				}
				KeepaliveProcessor::getInstance().resetGroupKeepalive(packet->getGroupId());
			}
			break;
		}
		case FRIEND_UNREGISTER:
		{
            Log(module, "Received FRIEND_UNREGISTER, userId: " << packet->getUserIdentity() << " friendId: " << packet->getFriendIdentity());
			UserIdentity userId = packet->getFriendIdentity();
			UserIdentity friendId = packet->getUserIdentity();

			auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);

			std::string packetId = packet->getPacketID();
			long long unregisterTime = ResourceManager::getInstance().UUIDToTime(packetId);
			if (friendInfo && unregisterTime < friendInfo->getCurrentRegisterTime()){
                Log(module, "Ignoring old unregister packet. unregisterTime: " << unregisterTime << " getCurrentRegisterTime: " << friendInfo->getCurrentRegisterTime());
				break;
			}

			std::string friendInfoPacketId = ResourceManager::getInstance().generatePacketIdInSDK().packetId;
			

			if (friendInfo)
			{
                std::string userName = friendInfo->getUserName();
				ResourceManager::getInstance().updateFriendInfoStatus(userId, friendId, OnlineStatus::AWAY);
				std::string deviceToken = friendInfo->getDeviceToken();
				Log(module, "====>> Sending friend information fid:" << friendId << " status:" << packet->getOnlineStatus() << " apptype:" << friendInfo->getAppType());

                auto ownProfileType = ResourceManager::getInstance().isUserPage(userId) ? UserProfileType::PAGE : UserProfileType::DEFAULT;

                auto builtPacket = packetBuilder->makeOfflineFriendInformation(userId, friendId, friendInfoPacketId, userName, friendInfo->getDeviceType(), packet->getOnlineStatus(), friendInfo->getAppType(), deviceToken, packet->getOnlineMood(), friendInfo->getIosVoipPush(), ResourceManager::getInstance().getDeviceType(), ownProfileType, friendInfo->getProfileType());
				if (!builtPacket.byteArray)
				{
					Log(module, "Friend info packet builder error");
					break;
				}

				auto connection = ResourceManager::getInstance().getOfflineConnection();
				auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);
				if (sendCode < 0)
				{
					Log(module, "Friend info sending socket returned " << sendCode);
					break;
				}
				
                ResendProcessor::getInstance().updatePendingDestination(userId, friendId, packet->getOnlineStatus());

				ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(friendInfoPacketId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Offline));

				auto blankMessagePacketId = ResourceManager::getInstance().generatePacketIdInSDK().packetId;
				long long messageDate = ResourceManager::getInstance().gettime() - ResourceManager::getInstance().getTimeDifference();
				//    long long messageDate = ResourceManager::getInstance().gettime();

				std::string message = "";
				auto builtBlankMessagePacket = packetBuilder->makeFriendChatMessage(userId, friendId, blankMessagePacketId, MessageType::BLANK_MESSAGE, 0, message, messageDate, false, ResourceManager::getInstance().getDeviceType(), ResourceManager::getInstance().appVersion, ResourceManager::getInstance().getAppType(), ResourceManager::getInstance().getUserId());

				if (!builtBlankMessagePacket.byteArray)
				{
					Log(module, "blank message packet builder error");
					break;
				}

				sendCode = connection->sendToOfflineServer(builtBlankMessagePacket.byteArray);
				if (sendCode < 0)
				{
					Log(module, "Friend blank message sending socket returned " << sendCode);
					break;
				}

				ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(blankMessagePacketId, builtBlankMessagePacket.byteArray, builtBlankMessagePacket.packet, connection, ResendProcessor::DestinationType::Offline));

				int profileType{ 0 };
				auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
				if (friendInfo) {
					profileType = friendInfo->getProfileType();
				}
				packet->setProfileType(profileType);

                Log(module, "Removing friendInfo. userId: " << userId << " frienId: " << friendId);
				ResourceManager::getInstance().removeFriendInfo(userId, friendId);
				KeepaliveProcessor::getInstance().removeFriendKeepalive(userId, friendId);
				packet->setFromAnonymous(false);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_UNREGISTERED, packet));
			}
            else
            {
                Log(module, "Friendinfo not found");
            }
			break;
		}
		case FRIEND_CHAT_MESSAGE_BROKEN:
		{
			handleBrokenChat(packet);
			break;
		}
		case FRIEND_CHAT_MESSAGE:
		{
			UserIdentity friendid = packet->getUserIdentity();
			UserIdentity userid = packet->getFriendIdentity();
			auto friendInfo = ResourceManager::getInstance().getFriendInfo(userid, friendid);

			time_t myTime = (time_t)(packet->getMessageDate() / 1000);
			Log(module, "receiving friend chat message date before calling time difference  " << ctime(&myTime));
			//            packet->setMessageDate(packet->getMessageDate() + ResourceManager::getInstance().getTimeDifference());
			myTime = (time_t)(packet->getMessageDate() / 1000);
			Log(module, "receiving friend chat message date after calling time difference  " << ctime(&myTime));

			BuiltPacket deliveredPacket;
			std::string packetId = packet->getPacketID();

			switch (packet->getMessageType()){

#ifndef _WIN32
			case FILE_STREAM:
			{
				break;
			}
			case FILE_STREAM_MENIFEST:
			{
				break;
			}
#endif
			case BLANK_MESSAGE:
			{
				break;
			}
			default:
			{
				if (friendInfo){
					packet->setOnline(true);
				}
				else{
					packet->setOnline(false);
				}

				if (offlinePacketIdMap.find(packetId) != offlinePacketIdMap.end() && offlinePacketIdMap[packetId]->getPacketType() == OFFLINE_BROKEN_HISTORY_PACKET)
				{
					std::shared_ptr< PacketDTO> messageList = std::make_shared<PacketDTO>();

					messageList->setPacketID(packet->getPacketID());
                    messageList->appendMessage(packet);
                    if (packet->getUserIdentity() == ResourceManager::getInstance().getUserId() || ResourceManager::getInstance().isUserPage(packet->getUserIdentity()))
                    {
                        messageList->setUserIdentity(packet->getUserIdentity());
                        messageList->setFriendIdentity(packet->getFriendIdentity());
                    }
                    else
                    {
                        messageList->setUserIdentity(packet->getFriendIdentity());
                        messageList->setFriendIdentity(packet->getUserIdentity());
                    }
					createSDKMessageDTOListFromPacket(messageList, true);
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_FRIEND_HISTORY_MESSAGE_RECEIVED, messageList));
					offlinePacketIdMap.erase(packetId);
				}
				else
				{
					std::string encryptedMessage = packet->getMessage();
					ByteArray encryptedMessageBytes(encryptedMessage);
					ByteArray decryptedMessage = ipvsdk::security::DataEncryption::decryptMessage(encryptedMessageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
					packet->setMessage(decryptedMessage.getString(0, decryptedMessage.size()));
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_NEW_CHAT_RECEIVED, packet));
				}
				packetId = packet->getPacketID();
			}
		}

			if (friendInfo)
			{
                if (friendid != ResourceManager::getInstance().getUserId() && !ResourceManager::getInstance().isUserPage(friendid))
				{
					deliveredPacket = packetBuilder->makeFriendChatMessageDelivered(userid, friendid, packetId);
					auto connection = friendInfo->getConnection();
					if (!connection)
					{
						Log(module, "connection not found");
						break;
					}

					connection->sendToChatServer(deliveredPacket.byteArray);
				}
			}
			else
			{
				Log(module, "Received from offline");

				deliveredPacket = packetBuilder->makeFriendChatMessageDelivered(userid, friendid, packetId);
				auto connection = ResourceManager::getInstance().getOfflineConnection();
				connection->sendToOfflineServer(deliveredPacket.byteArray);
				connection->sendToOfflineServer(deliveredPacket.byteArray);
				connection->sendToOfflineServer(deliveredPacket.byteArray);
			}
			KeepaliveProcessor::getInstance().resetFriendKeepalive(userid, friendid);
			break;
		}
		case FRIEND_CALL_BUSY_MESSAGE:
		{
			UserIdentity friendid = packet->getUserIdentity();
			UserIdentity userid = packet->getFriendIdentity();

			//            packet->setMessageDate(packet->getMessageDate() + ResourceManager::getInstance().getTimeDifference());

			BuiltPacket deliveredPacket;
			std::string packetId;

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_NEW_CHAT_RECEIVED, packet));
			packetId = packet->getPacketID();
			deliveredPacket = packetBuilder->makeFriendChatMessageDelivered(userid, friendid, packetId);

			std::shared_ptr< ChatConnection> connection = nullptr;

			connection = ResourceManager::getInstance().getOfflineConnection();
			connection->sendToOfflineServer(deliveredPacket.byteArray);

			break;
		}
		case FRIEND_CHAT_MESSAGE_DELIVERED:
		{
			Log(module, "received delivered: packet userID: " << packet->getUserIdentity() << " packet friendID: " << packet->getFriendIdentity());
			std::string packetId = packet->getPacketID();

			auto pos = packetId.find('_');
			if (pos != std::string::npos)
			{
				std::string actualPacketId = packetId.substr(0, pos);
				packet->setPacketID(actualPacketId);
			}

			auto resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);

			if (resendPacket && resendPacket->getMessageType() != MessageType::BLANK_MESSAGE)
			{
				Log(module, "resend packet exist");
				if (resendPacket->getPacketType() != FRIEND_CHAT_MESSAGE_BROKEN && resendPacket->getPacketType() != FRIEND_CHAT_MESSAGE_BROKEN_EDIT)
				{
					if (resendPacket->getPacketType() == FRIEND_CHAT_MESSAGE_EDIT){
						packet->setMessageEdited(true);
					}
					packet->setOnline(true);
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_DELIVERED, packet));
				}
				else if (resendPacket->getSequenceNumber() == (resendPacket->getNumberOfMessage() - 1))
				{
					if (resendPacket->getPacketType() == FRIEND_CHAT_MESSAGE_BROKEN_EDIT){
						packet->setMessageEdited(true);
					}
					packet->setOnline(true);
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_DELIVERED, packet));
				}
			}

			ResendProcessor::getInstance().removePacket(packetId);
			break;
		}
		case FRIEND_CHAT_MESSAGE_SENT:
		{
			std::string packetId = packet->getPacketID();

			Log(module, "Received sent PID:" << packetId);

			auto pos = packetId.find('_');
			if (pos != std::string::npos)
			{
				std::string actualPacketId = packetId.substr(0, pos);
				packet->setPacketID(actualPacketId);
			}

			auto resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);

			if (resendPacket && resendPacket->getMessageType() != MessageType::BLANK_MESSAGE)
			{
				Log(module, "resend packet exist");
				if (resendPacket->getPacketType() != FRIEND_CHAT_MESSAGE_BROKEN && resendPacket->getPacketType() != FRIEND_CHAT_MESSAGE_BROKEN_EDIT)
				{
					if (resendPacket->getPacketType() == FRIEND_CHAT_MESSAGE_EDIT){
						packet->setMessageEdited(true);
					}
					packet->setOnline(false);
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_DELIVERED, packet));
				}
				else if (resendPacket->getSequenceNumber() == (resendPacket->getNumberOfMessage() - 1))
				{
					if (resendPacket->getPacketType() == FRIEND_CHAT_MESSAGE_BROKEN_EDIT){
						packet->setMessageEdited(true);
					}
					packet->setOnline(false);
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_DELIVERED, packet));
				}
			}

			ResendProcessor::getInstance().removePacket(packetId);
			break;
		}
		case FRIEND_CHAT_MESSAGE_SEEN:
		{
			UserIdentity friendid = packet->getUserIdentity();
			UserIdentity userid = packet->getFriendIdentity();
			std::string packetId = packet->getPacketID();

			std::vector<SeenPacketDTO> packetDtos = packet->getSeenMessageList();
			//            for(int i=0;i<packetDtos.size();i++)
			//            {
			//                packetDtos[i].setMessageDate(packetDtos[i].getMessageDate() + ResourceManager::getInstance().getTimeDifference());
			//            }
			packet->setSeenMessageList(packetDtos);

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_IS_SEEN, packet));
			BuiltPacket deliveredPacket = packetBuilder->makeFriendChatMessageSeenConfirmation(userid, friendid, packetId);

			auto friendInfo = ResourceManager::getInstance().getFriendInfo(userid, friendid);
			if (friendInfo)
			{
				auto connection = friendInfo->getConnection();
				if (!connection)
				{
					Log(module, "connection not found");
					break;
				}

				connection->sendToChatServer(deliveredPacket.byteArray);
			}
			else
			{
				auto connection = ResourceManager::getInstance().getOfflineConnection();
				connection->sendToOfflineServer(deliveredPacket.byteArray);
			}
			KeepaliveProcessor::getInstance().resetFriendKeepalive(userid, friendid);
			break;
		}
		case FRIEND_CHAT_MESSAGE_SEEN_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			std::shared_ptr< PacketDTO> resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
			if (resendPacket)
			{
				ResendProcessor::getInstance().removePacket(packetId);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_IS_SEEN_CONFIRMED, resendPacket));
			}
			break;
		}
		case FRIEND_CHAT_MESSAGE_TYPING:
		{
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_TYPING, packet));
			KeepaliveProcessor::getInstance().resetFriendKeepalive(packet->getFriendIdentity(), packet->getUserIdentity());
			break;
		}
		case FRIEND_CHAT_IDEL:
		{
			//EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_IDLE, packet), Priority::l1);
			break;
		}
		case FRIEND_CHAT_MESSAGE_BROKEN_EDIT:
		{
			handleBrokenChat(packet);
			break;
		}
		case FRIEND_CHAT_MESSAGE_EDIT:
		{
			UserIdentity friendid = packet->getUserIdentity();
			UserIdentity userid = packet->getFriendIdentity();
			auto friendInfo = ResourceManager::getInstance().getFriendInfo(userid, friendid);

			std::string encryptedMessage = packet->getMessage();
			ByteArray encryptedMessageBytes(encryptedMessage);
			ByteArray decryptedMessage = ipvsdk::security::DataEncryption::decryptMessage(encryptedMessageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
			packet->setMessage(decryptedMessage.getString(0, decryptedMessage.size()));

			BuiltPacket deliveredPacket;
			std::string packetId = packet->getPacketID();

			if (friendInfo)
			{
				packet->setOnline(true);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_EDITED, packet));
				deliveredPacket = packetBuilder->makeFriendChatMessageDelivered(userid, friendid, packetId);

				auto connection = friendInfo->getConnection();
				if (!connection)
				{
					Log(module, "connection not found");
					break;
				}

				connection->sendToChatServer(deliveredPacket.byteArray);
			}
			else
			{
				Log(module, "Received from offline");

				packet->setOnline(false);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_EDITED, packet));
				deliveredPacket = packetBuilder->makeFriendChatMessageDelivered(userid, friendid, packetId);
				auto connection = ResourceManager::getInstance().getOfflineConnection();
				connection->sendToOfflineServer(deliveredPacket.byteArray);
				connection->sendToOfflineServer(deliveredPacket.byteArray);
				connection->sendToOfflineServer(deliveredPacket.byteArray);
			}
			KeepaliveProcessor::getInstance().resetFriendKeepalive(userid, friendid);
			break;
		}
		case FRIEND_CHAT_MULTIPLE_MESSAGE_DELETE:
		{
			UserIdentity friendid = packet->getUserIdentity();
			UserIdentity userid = packet->getFriendIdentity();

			if (friendid == ResourceManager::getInstance().getUserId() || ResourceManager::getInstance().isUserPage(friendid))
			{
				friendid = packet->getFriendIdentity();
				userid = packet->getUserIdentity();
			}

			auto friendInfo = ResourceManager::getInstance().getFriendInfo(userid, friendid);

			if (friendInfo)
			{
				std::string packetId = packet->getPacketID();
				BuiltPacket confirmationPacket = packetBuilder->makeFriendChatMessageDeleteConfirmation(userid, friendid, packetId);

				auto connection = friendInfo->getConnection();
				if (!connection)
				{
					Log(module, "connection not found");
					break;
				}

				connection->sendToChatServer(confirmationPacket.byteArray);
			}

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_DELETED, packet));

			KeepaliveProcessor::getInstance().resetFriendKeepalive(userid, friendid);
			break;
		}
		case FRIEND_CHAT_MESSAGE_DELETE_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			std::shared_ptr<PacketDTO> resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
			if (!resendPacket) {
                break;
			}
            packet->setMessageDeleteType(resendPacket->getMessageDeleteType());
            packet->setPacketIDs(resendPacket->getPacketIDs());
			ResendProcessor::getInstance().removePacket(packetId);
			packet->setRequestStatus(true);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_DELETE_STATUS_RECEIVED, packet));
			break;
		}

		case USER_PASSWORD_UPDATE_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			ResendProcessor::getInstance().removePacket(packetId);
			break;
		}

		case GENERAL_ENCRYPTED_PACKET:
		{

			UserIdentity friendid = packet->getUserIdentity();
			UserIdentity userid = packet->getFriendIdentity();
			int type = packet->getType();
			std::string packetId = packet->getPacketID();

			if (type == 1){

				BuiltPacket deliveredPacket = packetBuilder->makeGeneralEncryptedPacketConfirmation(userid, friendid, packetId, type, packet->getInformationType());
				auto friendInfo = ResourceManager::getInstance().getFriendInfo(userid, friendid);
				if (friendInfo)
				{
					auto connection = friendInfo->getConnection();
					if (!connection)
					{
						Log(module, "connection not found");
						break;
					}

					Log(module, "GENERAL_ENCRYPTED_PACKET confirmation sent");
					connection->sendToChatServer(deliveredPacket.byteArray);
				}
				else
				{
					auto connection = ResourceManager::getInstance().getOfflineConnection();
					Log(module, "GENERAL_ENCRYPTED_PACKET confirmation sent");
					connection->sendToOfflineServer(deliveredPacket.byteArray);
				}
				KeepaliveProcessor::getInstance().resetFriendKeepalive(userid, friendid);
			}

			if (type == 2)
			{
				
				BuiltPacket deliveredPacket = packetBuilder->makeGeneralEncryptedPacketConfirmation(ResourceManager::getInstance().getUserId(), packet->getFriendIdentity(), packetId, type, packet->getInformationType());
				auto groupConnection = ResourceManager::getInstance().getGroupConnection(packet->getFriendIdentity());

				if (groupConnection)
				{
					groupConnection->sendToChatServer(deliveredPacket.byteArray);
					Log(module, "GENERAL_ENCRYPTED_PACKET confirmation sent");
				}
				else
				{
					Log(module, "Connection not found");
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_ERROR, packet, ChatError::CONNECTION_NOT_FOUND));
				}

				KeepaliveProcessor::getInstance().resetGroupKeepalive(packet->getFriendIdentity());
			}



			std::string encryptedInformation = packet->getInformation();
			ByteArray encryptedInformationBytes(encryptedInformation);
			ByteArray decryptedMessage = ipvsdk::security::DataEncryption::decryptMessage(encryptedInformationBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
			packet->setInformation(decryptedMessage.getString(0, decryptedMessage.size()));
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::GENERAL_ENCRYPTED_PACKET_EVENT, packet));

			break;
		}

		case GENERAL_ENCRYPTED_CONFIRMATION:
		{
			Log(module, "GENERAL_ENCRYPTED_CONFIRMATION received");
			ResendProcessor::getInstance().removePacket(packet->getPacketID());
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::GENERAL_ENCRYPTED_PACKET_CONFIRMATION_EVENT, packet));		
			break;
		}

		case FRIEND_BLOCK:
		{
			UserIdentity friendId = packet->getUserIdentity();
			UserIdentity userId = packet->getFriendIdentity();
            if (friendId == ResourceManager::getInstance().getUserId() || ResourceManager::getInstance().isUserPage(friendId))
            {
                friendId = packet->getFriendIdentity();
                userId = packet->getUserIdentity();
            }
			auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);

			if (friendInfo)
			{
				friendInfo->setIsFriendBlocked(true);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_BLOCKED, packet));
				std::string packetId = packet->getPacketID();
				auto confirmationPacket = packetBuilder->makeFriendBlockUnblockConfirmation(userId, friendId, packetId);

				KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId, 7);

				auto connection = friendInfo->getConnection();
				if (!connection)
				{
					Log(module, "connection not found");
					break;
				}

				connection->sendToChatServer(confirmationPacket.byteArray);
			}
			else
			{
				//                Log(module, "Connection not found");
				//                EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_ERROR, packet, ChatError::CONNECTION_NOT_FOUND));
				Log(module, "Received block packet from offline");

				std::string packetId = packet->getPacketID();
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_BLOCKED, packet));
				auto deliveredPacket = packetBuilder->makeFriendBlockUnblockConfirmation(userId, friendId, packetId);
				auto connection = ResourceManager::getInstance().getOfflineConnection();
				connection->sendToOfflineServer(deliveredPacket.byteArray);
				connection->sendToOfflineServer(deliveredPacket.byteArray);
				connection->sendToOfflineServer(deliveredPacket.byteArray);
			}
			//KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId);
			break;
		}
		case FRIEND_UNBLOCK:
		{
			UserIdentity friendId = packet->getUserIdentity();
			UserIdentity userId = packet->getFriendIdentity();
            if (friendId == ResourceManager::getInstance().getUserId() || ResourceManager::getInstance().isUserPage(friendId))
            {
                friendId = packet->getFriendIdentity();
                userId = packet->getUserIdentity();
            }
			auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);

			if (friendInfo)
			{
				friendInfo->setIsFriendBlocked(false);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_UNBLOCKED, packet));
				std::string packetId = packet->getPacketID();
				auto confirmationPacket = packetBuilder->makeFriendBlockUnblockConfirmation(userId, friendId, packetId);

				KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId);

				auto connection = friendInfo->getConnection();
				if (!connection)
				{
					Log(module, "connection not found");
					break;
				}

				connection->sendToChatServer(confirmationPacket.byteArray);
			}
			else
			{
				//                Log(module, "Connection not found");
				//                EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_ERROR, packet, ChatError::CONNECTION_NOT_FOUND));
				Log(module, "Received unblock packet from offline");

				std::string packetId = packet->getPacketID();
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_UNBLOCKED, packet));
				auto deliveredPacket = packetBuilder->makeFriendBlockUnblockConfirmation(userId, friendId, packetId);
				auto connection = ResourceManager::getInstance().getOfflineConnection();
				connection->sendToOfflineServer(deliveredPacket.byteArray);
				connection->sendToOfflineServer(deliveredPacket.byteArray);
				connection->sendToOfflineServer(deliveredPacket.byteArray);
			}
			//KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId);
			break;
		}
		case FRIEND_BLOCK_UNBLOCK_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();

			std::shared_ptr< PacketDTO> resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
			if (!resendPacket){
				break;
			}

            auto friendInfo = ResourceManager::getInstance().getFriendInfo(resendPacket->getUserIdentity(), resendPacket->getFriendIdentity());
            if (friendInfo)
            {
                if (resendPacket->getPacketType() == FRIEND_BLOCK)
                {
                    friendInfo->setIsFriendBlocked(true);
                }
                else
                {
                    friendInfo->setIsFriendBlocked(false);
                }
            }

			resendPacket->setRequestStatus(true);
			ResendProcessor::getInstance().removePacket(packetId);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_BLOCK_UNBLOCK_CONFIRMED, resendPacket));

			break;
		}
		case OFFLINE_FRIEND_INFORMATION_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			ResendProcessor::getInstance().removePacket(packetId);
			break;
		}
		case OFFLINE_FRIEND_UNREAD_MESSAGE:
		{
			Log(module, "Friend unread message: size: " << packet->getMessageList().size());
			auto connection = ResourceManager::getInstance().getOfflineConnection();

            Log(module, "Friend unread message: connection: " << connection);
            if (connection)
			{
				std::string packetId = packet->getPacketID();
				UserIdentity userId = packet->getUserIdentity();
				std::vector<std::shared_ptr< PacketDTO>> messageList = packet->getMessageList();
				std::vector<std::string> packetIDs;

				for (std::vector<std::shared_ptr< PacketDTO>>::size_type i = 0; i < messageList.size(); i++)
				{
					//long long timeDifference = ResourceManager::getInstance().gettime() - (messageList[i]->getMessageDate() + ResourceManager::getInstance().getTimeDifference());
					long long timeDifference = (ResourceManager::getInstance().gettime() + ResourceManager::getInstance().getTimeDifference()) - messageList[i]->getMessageDate();

                    Log(module, "Friend unread message ::: packetId: " << messageList[i]->getPacketID() << " FriendIdentity: " << messageList[i]->getFriendIdentity() << " UserIdentity: " << messageList[i]->getUserIdentity() << " message: " << messageList[i]->getMessage() << " timeDifference: " << timeDifference);

					//if(timeDifference<180000 && ResourceManager::getInstance().getFriendInfo(packet->getFriendIdentity()) == nullptr) //check carefully
					if (timeDifference < 30000)
					{
						std::shared_ptr< PacketDTO> serverUpdatePacket = std::make_shared<PacketDTO>();
						serverUpdatePacket->setUserIdentity(messageList[i]->getFriendIdentity());
						serverUpdatePacket->setFriendIdentity(messageList[i]->getUserIdentity());
						serverUpdatePacket->setFromAnonymous(false);
						EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_FRIEND, serverUpdatePacket));
					}

					if (messageList[i]->getMessageType() != MessageType::BLANK_MESSAGE)
					{
						packetIDs.push_back(messageList[i]->getPacketID());
						messageList[i]->setOnline(false);

						std::string encryptedMessage = messageList[i]->getMessage();
						ByteArray encryptedMessageBytes(encryptedMessage);
						ByteArray decryptedMessage = ipvsdk::security::DataEncryption::decryptMessage(encryptedMessageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
						messageList[i]->setMessage(decryptedMessage.getString(0, decryptedMessage.size()));
						Log(module, "Decrypted FRIEND_CHAT_MESSAGE, decrypted message: " << messageList[i]->getMessage());

						if (messageList[i]->getPacketType() == FRIEND_CHAT_MESSAGE)
						{
							EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_NEW_CHAT_RECEIVED, messageList[i]));
						}
						else if (messageList[i]->getPacketType() == FRIEND_CHAT_MESSAGE_EDIT)
						{
							EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_EDITED, messageList[i]));
						}
					}
				}

				BuiltPacket deliveredPacket = packetBuilder->makeOfflineFriendUnreadMessageConfirmation(userId, packetId, packetIDs);
				connection->sendToOfflineServer(deliveredPacket.byteArray);
			}
			else
			{
				Log(module, "Connection not found");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_ERROR, packet, ChatError::CONNECTION_NOT_FOUND));
			}
			break;
		}
		case OFFLINE_GET_REQUEST_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			long long serverTime = packet->getServerDate();
			long long timeDifference = serverTime - ResourceManager::getInstance().gettime();
			ResourceManager::getInstance().setTimeDifference(timeDifference);

			auto resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
			if (resendPacket)
			{
				if (resendPacket->getPacketType() == OFFLINE_GET_CONVERSATION_REQUEST)
				{
					resendPacket->setRequestStatus(true);
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::CONVERSATION_LIST_REQUEST_STATUS, resendPacket));
				}
				else if (resendPacket->getPacketType() == DELETE_CONVERSATION_REQUEST)
				{
					resendPacket->setRequestStatus(true);
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::CONVERSATION_LIST_DELETE_REQUEST_STATUS, resendPacket));
				}
				else if (resendPacket->getPacketType() == MARK_CONVERSATION_SEEN_REQUEST)
				{
					resendPacket->setRequestStatus(true);
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::MARK_CONVERSATION_LIST_SEEN_REQUEST_STATUS, resendPacket));
				}
			}
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SERVER_TIME_DIFFERENCE_SYNCED, nullptr));

			ResendProcessor::getInstance().removePacket(packetId);
			break;
		}
		case OFFLINE_FRIEND_HISTORY_MESSAGE_CONFIRMATION:
		{
			packet->setRequestStatus(true);
			std::string packetId = packet->getPacketID() + ResourceManager::toLongToString(ResourceManager::getInstance().getUserId());

			auto delPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
			if (delPacket)
			{
				packet->setUserIdentity(delPacket->getUserIdentity());
				ResendProcessor::getInstance().removePacket(packetId);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_FRIEND_HISTORY_MESSAGE_CONFIRMATION_RECEIVED, packet));
			}
			break;
		}
		case OFFLINE_FRIEND_HISTORY_MESSAGE:
		{
			//            cout<<"history message list size: "<<packet->getMessageList().size()<<endl;
			auto connection = ResourceManager::getInstance().getOfflineConnection();

			std::string packetId = packet->getPacketID();

			BuiltPacket offlineFriendHistoryMessageConfirmation = packetBuilder->makeOfflineFriendHistoryMessageConfirmation(packet->getFriendIdentity(), packetId);
			connection->sendToOfflineServer(offlineFriendHistoryMessageConfirmation.byteArray);

			int msgCount = packet->getMessageList().size();

			if (msgCount > 0)
			{
				createSDKMessageDTOListFromPacket(packet, false);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_FRIEND_HISTORY_MESSAGE_RECEIVED, packet));
			}
			else{
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_FRIEND_HISTORY_MESSAGE_RECEIVE_COMPLETED, packet));
			}
			break;
		}
		case OFFLINE_GET_FRIEND_MESSGAE_STATUS_CONFIRMATION:
		{
                    std::string packetId = packet->getPacketID();
			auto resendPacketToRemove = ResendProcessor::getInstance().getPacketDTO(packetId);

			if (resendPacketToRemove)
			{
				std::vector<FriendMessageStatusDTO> friendMessageStatusDtoList = packet->getFriendMessageStatusDTOList();
				//            for(int i=0;i<friendMessageStatusDtoList.size();i++){
				//                friendMessageStatusDtoList[i].setUpdateDate(friendMessageStatusDtoList[i].getUpdateDate() + ResourceManager::getInstance().getTimeDifference());
				//            }
				packet->setFriendMessageStatusDTOList(friendMessageStatusDtoList);
				packet->setUserIdentity(resendPacketToRemove->getUserIdentity());

				EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_FRIEND_MESSAGES_STATUS_RECEIVED, packet));
				ResendProcessor::getInstance().removePacket(packet->getPacketID());
			}
			break;
		}
		////////////////// new group flow/////////////////////////
		case GROUP_INFORMATION_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			auto resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
			if (resendPacket)
			{
				resendPacket->setRequestStatus(true);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_INFORMATION_SENT, resendPacket));
			}

			ResendProcessor::getInstance().removePacket(packetId);

			break;
		}
		case GROUP_INFORMATION:
		{
			GroupIdentity groupId = packet->getGroupId();
			std::string packetId = packet->getPacketID();

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_INFORMATION_RECEIVED, packet));
			auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
			auto confirmationPacket = packetBuilder->makeGroupInformationConfirmation(ResourceManager::getInstance().getUserId(), groupId, packetId);
			connection->sendToChatServer(confirmationPacket.byteArray);

			KeepaliveProcessor::getInstance().resetGroupKeepalive(packet->getGroupId());
			break;
		}
		case GROUP_MEMBER_ADD:
		{
			GroupIdentity groupId = packet->getGroupId();
			std::string packetId = packet->getPacketID();

			auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
			if (connection)
			{
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_MEMBER_ADDED, packet));
				auto groupMemberAddConfirmationPacket = packetBuilder->makeGroupMemberAddConfirmation(ResourceManager::getInstance().getUserId(), groupId, packetId);
				connection->sendToChatServer(groupMemberAddConfirmationPacket.byteArray);
			}
			else
			{
				Log(module, "Connection not found");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_ERROR, packet, ChatError::CONNECTION_NOT_FOUND));
			}
			ResendProcessor::getInstance().removePacket(packetId);
			break;
		}
		case GROUP_MEMBER_ADD_CONFIRMATION:
		{
			Log(module, "GROUP_MEMBER_ADD_CONFIRMATION");
			std::string packetId = packet->getPacketID();
			packet->setRequestStatus(true);
			//            std::shared_ptr< PacketDTO> resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
			auto resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
			if (resendPacket)
			{
				resendPacket->setRequestStatus(true);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_MEMBER_ADD_SENT, resendPacket));
			}
			ResendProcessor::getInstance().removePacket(packetId);
			break;
		}
		case GROUP_MEMBER_REMOVE_LEAVE:
		{
			GroupIdentity groupId = packet->getGroupId();
			std::string packetId = packet->getPacketID();

			auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
			if (connection)
			{
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_MEMBER_REMOVED_OR_LEFT, packet));
				auto confirmationPacket = packetBuilder->makeGroupMemberRemoveLeaveConfirmation(ResourceManager::getInstance().getUserId(), groupId, packetId);
				connection->sendToChatServer(confirmationPacket.byteArray);
			}
			else
			{
				Log(module, "Connection not found");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_ERROR, packet, ChatError::CONNECTION_NOT_FOUND));
			}

			std::vector<MemberDTO> memberList = packet->getMemberList();

			for (std::vector<MemberDTO>::size_type i = 0; i < memberList.size(); i++)
			{
				if (memberList[i].getMemberIdentity() == ResourceManager::getInstance().getUserId()){
                    ResourceManager::getInstance().removeGroupRegistration(groupId);
                    ResourceManager::getInstance().removeGroupConnection(groupId);
					KeepaliveProcessor::getInstance().removeGroupKeepalive(groupId);
					break;
				}
			}

			break;
		}
		case GROUP_MEMBER_REMOVE_LEAVE_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();

			std::shared_ptr< PacketDTO> resendPacketDTO = ResendProcessor::getInstance().getPacketDTO(packetId);

			if (resendPacketDTO)
			{
				std::vector<MemberDTO> memberList = resendPacketDTO->getMemberList();

				if (memberList.size() == 1 && memberList[0].getMemberIdentity() == ResourceManager::getInstance().getUserId()){
                    ResourceManager::getInstance().removeGroupRegistration(packet->getGroupId());
                    ResourceManager::getInstance().removeGroupConnection(packet->getGroupId());
					KeepaliveProcessor::getInstance().removeGroupKeepalive(packet->getGroupId());
				}
				resendPacketDTO->setRequestStatus(true);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_MEMBER_REMOVE_LEAVE_SENT, resendPacketDTO));
			}

			ResendProcessor::getInstance().removePacket(packetId);
			break;
		}
		case GROUP_MEMBER_TYPE_CHANGE:
		{
            Log(module, "Received: GROUP_MEMBER_TYPE_CHANGE");
			std::string packetId = packet->getPacketID();
			GroupIdentity groupId = packet->getGroupId();

			auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
			if (connection)
			{
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_MEMBER_STATUS_CHANGED, packet));
				auto confirmationPacket = packetBuilder->makeGroupMemberTypeChangeConfirmation(ResourceManager::getInstance().getUserId(), groupId, packetId);
				connection->sendToChatServer(confirmationPacket.byteArray);
			}
			else
			{
				Log(module, "Connection not found");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_ERROR, packet, ChatError::CONNECTION_NOT_FOUND));
			}
			break;
		}
		case GROUP_MEMBER_TYPE_CHANGE_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			auto resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
			if (resendPacket)
			{
				resendPacket->setRequestStatus(true);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_MEMBER_STATUS_CHANGE_SENT, resendPacket));
			}
			ResendProcessor::getInstance().removePacket(packetId);
			break;
		}
		case GROUP_CHAT_IDEL:
		{
			break;
		}
		case GROUP_CHAT_MESSAGE_TYPING:
		{
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_TYPING, packet));
			KeepaliveProcessor::getInstance().resetGroupKeepalive(packet->getGroupId());
			break;
		}
		case GROUP_CHAT_MESSAGE:
		{
			UserIdentity friendId = packet->getUserIdentity();
			GroupIdentity groupId = packet->getGroupId();
			std::string packetId = packet->getPacketID();

			//            packet->setMessageDate(packet->getMessageDate() + ResourceManager::getInstance().getTimeDifference());

			auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
			if (connection)
			{
				packet->setOnline(true);
				if (packet->getMessageType() != MessageType::BLANK_MESSAGE)
				{
					std::string encryptedMessage = packet->getMessage();
					ByteArray encryptedMessageBytes(encryptedMessage);
					ByteArray decryptedMessage = ipvsdk::security::DataEncryption::decryptMessage(encryptedMessageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
					packet->setMessage(decryptedMessage.getString(0, decryptedMessage.size()));
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_NEW_CHAT_RECEIVED, packet));
				}
				auto deliveredPacket = packetBuilder->makeGroupChatMessageDelivered(ResourceManager::getInstance().getUserId(), friendId, groupId, packetId);
				connection->sendToChatServer(deliveredPacket.byteArray);
			}
			else
			{
				Log(module, "Connection not found");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_ERROR, packet, ChatError::CONNECTION_NOT_FOUND));
			}
			KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);
			break;
		}
		case GROUP_CHAT_MESSAGE_SENT:
		{
			std::string packetId = packet->getPacketID();

			auto pos = packetId.find('_');
			if (pos != std::string::npos)
			{
				std::string actualPacketId = packetId.substr(0, pos);
				packet->setPacketID(actualPacketId);
			}

			auto resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);

			if (resendPacket && resendPacket->getMessageType() != MessageType::BLANK_MESSAGE)
			{
				if (resendPacket->getPacketType() != GROUP_CHAT_MESSAGE_BROKEN && resendPacket->getPacketType() != GROUP_CHAT_MESSAGE_BROKEN_EDIT)
				{
					if (resendPacket->getPacketType() == GROUP_CHAT_MESSAGE_EDIT){
						packet->setMessageEdited(true);
					}
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_SENT, packet));
				}
				else if (resendPacket->getSequenceNumber() == (resendPacket->getNumberOfMessage() - 1))
				{
					if (resendPacket->getPacketType() == GROUP_CHAT_MESSAGE_BROKEN_EDIT){
						packet->setMessageEdited(true);
					}
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_SENT, packet));
				}
			}
			else if (!resendPacket)
			{
				Log(module, "No resend packet");
			}
			else
			{
				Log(module, "Received sent of blank message");
			}

			ResendProcessor::getInstance().removePacket(packetId);

			break;
		}
		case GROUP_CHAT_MESSAGE_DELIVERED:
		{
			std::string packetId = packet->getPacketID();
			auto pos = packetId.find('_');
			if (pos != std::string::npos)
			{
				std::string actualPacketId = packetId.substr(0, pos);
				packet->setPacketID(actualPacketId);
			}
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_DELIVERED, packet));
			break;
		}
		case GROUP_CHAT_MESSAGE_EDIT:
		{
			UserIdentity friendId = packet->getUserIdentity();
			GroupIdentity groupId = packet->getGroupId();
			std::string packetId = packet->getPacketID();

			//            packet->setMessageDate(packet->getMessageDate() + ResourceManager::getInstance().getTimeDifference());

			auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
			if (connection)
			{
				packet->setOnline(true);

				std::string encryptedMessage = packet->getMessage();
				ByteArray encryptedMessageBytes(encryptedMessage);
				ByteArray decryptedMessage = ipvsdk::security::DataEncryption::decryptMessage(encryptedMessageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
				packet->setMessage(decryptedMessage.getString(0, decryptedMessage.size()));

				EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_EDITED, packet));
				auto deliveredPacket = packetBuilder->makeGroupChatMessageDelivered(ResourceManager::getInstance().getUserId(), friendId, groupId, packetId);
				connection->sendToChatServer(deliveredPacket.byteArray);
			}
			else
			{
				Log(module, "Connection not found");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_ERROR, packet, ChatError::CONNECTION_NOT_FOUND));
			}
			KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);
			break;
		}
		case GROUP_CHAT_MESSAGE_BROKEN:
		{
			handleBrokenGroupChat(packet);
			break;
		}
		case GROUP_CHAT_MESSAGE_BROKEN_EDIT:
		{
			handleBrokenGroupChat(packet);
			break;
		}
		case GROUP_CHAT_MESSAGE_SEEN:
		{
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_SEEN, packet));
			GroupIdentity groupId = packet->getGroupId();
			std::string packetId = packet->getPacketID();

			auto groupConnection = ResourceManager::getInstance().getGroupConnection(groupId);

			if (groupConnection)
			{
				BuiltPacket confirmationPacket = packetBuilder->makeGroupChatMessageSeenConfirmation(ResourceManager::getInstance().getUserId(), groupId, packetId);
				groupConnection->sendToChatServer(confirmationPacket.byteArray);
			}
			else
			{
				Log(module, "Connection not found");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_ERROR, packet, ChatError::CONNECTION_NOT_FOUND));
			}

			KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);
			break;
		}
		case GROUP_CHAT_MESSAGE_SEEN_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			auto resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
			if (resendPacket)
			{
				resendPacket->setRequestStatus(true);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_SEEN_CONFIRMATION, resendPacket));
			}
			ResendProcessor::getInstance().removePacket(packetId);
			break;
		}
		case GROUP_CHAT_MESSAGE_SEEN_LIST_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			auto resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
			if (resendPacket)
			{
				resendPacket->setRequestStatus(true);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_MESSAGE_SEEN_LIST_CONFIRMATION_RECEIVED, resendPacket));
			}
			ResendProcessor::getInstance().removePacket(packetId);
			break;
		}
		case GROUP_CHAT_MESSAGE_SEEN_LIST:
		{
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_MESSAGE_SEEN_LIST_RECEIVED, packet));
			GroupIdentity groupId = packet->getGroupId();
			std::string packetId = packet->getPacketID();

			auto groupConnection = ResourceManager::getInstance().getGroupConnection(groupId);

			if (groupConnection)
			{
				BuiltPacket confirmationPacket = packetBuilder->makeGroupChatMessageSeenListConfirmation(ResourceManager::getInstance().getUserId(), groupId, packetId);
				groupConnection->sendToChatServer(confirmationPacket.byteArray);
			}
			else
			{
				Log(module, "Connection not found");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_ERROR, packet, ChatError::CONNECTION_NOT_FOUND));
			}

			KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);
			break;
		}
		case GROUP_CHAT_MULTIPLE_MESSAGE_DELETE:
		{
			GroupIdentity groupId = packet->getGroupId();
			std::string packetId = packet->getPacketID();
			auto groupConnection = ResourceManager::getInstance().getGroupConnection(groupId);

			if (groupConnection)
			{
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_DELETED, packet));
				BuiltPacket confirmationPacket = packetBuilder->makeGroupChatMessageDeleteConfirmation(ResourceManager::getInstance().getUserId(), groupId, packetId);
				groupConnection->sendToChatServer(confirmationPacket.byteArray);
			}
			else
			{
				Log(module, "Connection not found");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_ERROR, packet, ChatError::CONNECTION_NOT_FOUND));
			}
			KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);
			break;
		}
		case GROUP_CHAT_MESSAGE_DELETE_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			if (ResendProcessor::getInstance().isExistInResendPacketMap(packetId))
			{
				//std::shared_ptr< PacketDTO> resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
				std::shared_ptr<PacketDTO> resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
				std::vector<std::string> packetIds;
				if (resendPacket) {
					packetIds = resendPacket->getPacketIDs();
				}
				packet->setPacketIDs(packetIds);

				ResendProcessor::getInstance().removePacket(packetId);
				packet->setRequestStatus(true);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_DELETE_CONFIRMED, packet));
			}
			break;
		}
		case GROUP_BROKEN_PACKET:
		{
			ByteArray totalPacket;
			totalPacket = handleBrokenDataPacket(packet);

			if (totalPacket.size() != 0){
				ParsedObject object;
				ChatParser parser;
				std::shared_ptr< PacketDTO> packet(parser.parse(totalPacket).packet);
			}
			break;
		}
		case OFFLINE_MY_GROUP_LIST:
		{
			auto connection = ResourceManager::getInstance().getOfflineConnection();
            
			std::string packetId = packet->getPacketID();
			BuiltPacket offlineGroupHistoryMessageConfirmation = packetBuilder->makeOfflineGroupConfirmation(packet->getGroupId(), packetId);
			connection->sendToOfflineServer(offlineGroupHistoryMessageConfirmation.byteArray);

            if (packet->getGroupDTOList().size() > 0)
            {
                if (!packet->getPivotID().empty() && packet->getUpDownStatus() != 0)
                {
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_MY_GROUP_LIST_PAGING_RECEIVED, packet));
                }
                else
                {
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_MY_GROUP_LIST_RECEIVED, packet));
                }
            }
            else
            {
                EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_MY_GROUP_LIST_RECEIVED_COMPLETED, packet));
            }


			break;
		}
		case OFFLINE_GROUP_UNREAD_MESSAGE:
		{
			Log(module, "GROUP unread message: size: " << packet->getMessageList().size());
			auto connection = ResourceManager::getInstance().getOfflineConnection();
			if (connection)
			{
				std::string packetId = packet->getPacketID();
				std::vector<std::shared_ptr< PacketDTO>> messageList = packet->getMessageList(); //packet->getPacketIDs();
				std::vector<std::string> packetIds;

				std::vector<GroupActivityDTO> groupActivityList;
                std::set<GroupIdentity> requestedGroupIds;

				for (std::vector<std::shared_ptr< PacketDTO>>::size_type i = 0; i < messageList.size(); i++) {

					//long long timeDifference = ResourceManager::getInstance().gettime() - (messageList[i]->getMessageDate() + ResourceManager::getInstance().getTimeDifference());
					long long timeDifference = (ResourceManager::getInstance().gettime() + ResourceManager::getInstance().getTimeDifference()) - messageList[i]->getMessageDate();

					GroupIdentity currGroupId = messageList[i]->getGroupId();
                    if (timeDifference < 30000)
					{
						std::string packetId = ResourceManager::getInstance().generatePacketIdInSDK().packetId;
						Log(module, "Request IP port for group: " << packet->getGroupId());

						auto connection = ResourceManager::getInstance().getOfflineConnection();

						std::string serverIp = "";
                        BuiltPacket offlineGroupIPPortRequest = packetBuilder->makeOfflineGroupIPPortRequest(ResourceManager::getInstance().getUserId(), currGroupId, packetId, ResourceManager::getInstance().getDeviceType(), serverIp, 0);

						if (!offlineGroupIPPortRequest.byteArray)
						{
							Log(module, "Packet builder error");
						}
						else
						{
							auto sendCode = connection->sendToOfflineServer(offlineGroupIPPortRequest.byteArray);

							if (sendCode < 0)
							{
								Log(module, "Socket returned, sendCode: " << sendCode);
							}

                            requestedGroupIds.insert(currGroupId);
							ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, offlineGroupIPPortRequest.byteArray, offlineGroupIPPortRequest.packet, connection, ResendProcessor::Offline));
						}
					}

					if (messageList[i]->getMessageType() == MessageType::GROUP_ACTIVITY)
					{
						std::string encryptedMessage = messageList[i]->getMessage();
						ByteArray encryptedMessageBytes(encryptedMessage);
						ByteArray decryptedMessageBytes = ipvsdk::security::DataEncryption::decryptMessage(encryptedMessageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
						messageList[i]->setMessage(decryptedMessageBytes.getString(0, decryptedMessageBytes.size()));

						groupActivityList.push_back(parser.parseGroupActivity(messageList[i]));
					}
					else if (messageList[i]->getMessageType() != MessageType::BLANK_MESSAGE)
					{
						messageList[i]->setOnline(false);
						packetIds.push_back(messageList[i]->getPacketID());
						//                    messageList[i]->setMessageDate(messageList[i]->getMessageDate() + ResourceManager::getInstance().getTimeDifference());
						if (messageList[i]->getPacketType() == GROUP_CHAT_MESSAGE)
						{
							std::string encryptedMessage = messageList[i]->getMessage();
							ByteArray encryptedMessageBytes(encryptedMessage);
							ByteArray decryptedMessageBytes = ipvsdk::security::DataEncryption::decryptMessage(encryptedMessageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
							messageList[i]->setMessage(decryptedMessageBytes.getString(0, decryptedMessageBytes.size()));
							Log(module, "Decrypted GROUP_CHAT_MESSAGE, decrypted message: " << messageList[i]->getMessage());
							EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_NEW_CHAT_RECEIVED, messageList[i]));
						}
						else if (messageList[i]->getPacketType() == GROUP_CHAT_MESSAGE_EDIT)
						{
							std::string encryptedMessage = messageList[i]->getMessage();
							ByteArray encryptedMessageBytes(encryptedMessage);
							ByteArray decryptedMessageBytes = ipvsdk::security::DataEncryption::decryptMessage(encryptedMessageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
							messageList[i]->setMessage(decryptedMessageBytes.getString(0, decryptedMessageBytes.size()));
							Log(module, "Decrypted GROUP_CHAT_MESSAGE_EDIT, decrypted message: " << messageList[i]->getMessage());
							EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_EDITED, messageList[i]));
						}
					}
				}

				if (groupActivityList.size() > 0)
				{

					//                    for(int i=0;i<groupActivityList.size();i++){
					//                        groupActivityList[i].setUpdateTime(groupActivityList[i].getUpdateTime() + ResourceManager::getInstance().getTimeDifference());
					//                    }
					packet->setGroupActivities(groupActivityList);

					for (std::vector<GroupActivityDTO>::size_type i = 0; i < groupActivityList.size(); i++){
						packetIds.push_back(groupActivityList[i].getPacketId());
					}

					EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_INFORMATION_ACTIVITY_RECEIVED, packet));

				}

				if (offlinePacketIdMap.find(packetId) != offlinePacketIdMap.end() && offlinePacketIdMap[packetId]->getPacketType() == OFFLINE_BROKEN_PACKET)
				{
					for (std::vector<std::string>::size_type i = 0; i < packetIds.size();)
					{
						std::vector<std::string> packetIdsToSend;

						for (std::vector<std::string>::size_type j = 0; j < 11 && i < packetIds.size(); j++, i++)
						{
							packetIdsToSend.push_back(packetIds[i]);
						}

						std::string confPacketId = ResourceManager::getInstance().generatePacketIdInSDK().packetId + ResourceManager::toString(i);
						BuiltPacket deliveredPacket;
						deliveredPacket = packetBuilder->makeOfflineGroupUnreadMessageConfirmation(ResourceManager::getInstance().getUserId(), confPacketId, packetIdsToSend);
						connection->sendToOfflineServer(deliveredPacket.byteArray);
						connection->sendToOfflineServer(deliveredPacket.byteArray);
						connection->sendToOfflineServer(deliveredPacket.byteArray);
					}
					offlinePacketIdMap.erase(packetId);
				}
				else
				{
					BuiltPacket deliveredPacket;
					deliveredPacket = packetBuilder->makeOfflineGroupUnreadMessageConfirmation(ResourceManager::getInstance().getUserId(), packetId, packetIds);
					connection->sendToOfflineServer(deliveredPacket.byteArray);
				}
			}
			else
			{
				Log(module, "Connection not found");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SDK_ERROR, packet, ChatError::CONNECTION_NOT_FOUND));
			}

			KeepaliveProcessor::getInstance().resetGroupKeepalive(packet->getGroupId());
			break;
		}
		case OFFLINE_CREATE_GROUP_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			auto resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
			if (resendPacket)
			{
				resendPacket->setRequestStatus(true);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CREATED, resendPacket, ChatError::NO_ERROR_IN_SDK));
			}
			ResendProcessor::getInstance().removePacket(packet->getPacketID());
			break;
		}
		case OFFLINE_GROUP_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			std::string modifiedPacketId = packetId + ResourceManager::toLongToString(ResourceManager::getInstance().getUserId());
			auto resendPacketDTO = ResendProcessor::getInstance().getPacketDTO(modifiedPacketId);
			if (resendPacketDTO && resendPacketDTO->getPacketType() == OFFLINE_GROUP_HISTORY_MESSAGE_REQUEST){
				resendPacketDTO->setRequestStatus(true);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_HISTORY_MESSAGE_CONFIRMATION_RECEIVED, resendPacketDTO));
			}
			else if (resendPacketDTO && resendPacketDTO->getPacketType() == OFFLINE_GET_INFORMATION_WITH_MEMBERS){
				resendPacketDTO->setRequestStatus(true);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_INFORMATION_WITH_MEMBERS_REQUEST_STATUS, resendPacketDTO));
			}

            ResendProcessor::getInstance().removePacket(packetId);
            ResendProcessor::getInstance().removePacket(modifiedPacketId);
			break;
		}
		case OFFLINE_GROUP_HISTORY_MESSAGE:
		{
			auto connection = ResourceManager::getInstance().getOfflineConnection();

			std::string packetId = packet->getPacketID();
			BuiltPacket offlineGroupHistoryMessageConfirmation = packetBuilder->makeOfflineGroupConfirmation(packet->getGroupId(), packetId);
			connection->sendToOfflineServer(offlineGroupHistoryMessageConfirmation.byteArray);

			std::vector<std::shared_ptr< PacketDTO>> messageList;
			std::vector<GroupActivityDTO> activityList;

			auto innerPacketList = packet->getMessageList();
			for (size_t i = 0; i < innerPacketList.size(); i++)
			{
				std::string encryptedMessage = innerPacketList[i]->getMessage();
				ByteArray encryptedMessageBytes(encryptedMessage);
				ByteArray decryptedMessageBytes = ipvsdk::security::DataEncryption::decryptMessage(encryptedMessageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
				innerPacketList[i]->setMessage(decryptedMessageBytes.getString(0, decryptedMessageBytes.size()));

				if (innerPacketList[i]->getMessageType() == MessageType::GROUP_ACTIVITY)
				{
					activityList.push_back(parser.parseGroupActivity(innerPacketList[i]));
				}
				else
				{
					messageList.push_back(innerPacketList[i]);
				}
			}

			int messageCount = messageList.size();
			int activityCount = activityList.size();

			Log(module, "Number of message: " << messageCount << " ;Number of activity: " << activityCount << " ;upDownStatus: " << packet->getUpDownStatus());

			auto sdkMessagDTOList = generateSDKMessageDTOListForGroupFromPacket(messageList);
			packet->setChatMessageList(sdkMessagDTOList);
			packet->setGroupActivities(activityList);

			if (messageCount > 0 && activityCount > 0)
			{
				long long messageTime = messageList[0]->getMessageDate();
				long long activityTime = activityList[0].getUpdateTime();

				if (packet->getUpDownStatus() == UP)
				{
					if (messageTime > activityTime)
					{
						EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_HISTORY_MESSAGE_RECEIVED, packet));
						EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_INFORMATION_ACTIVITY_FROM_GROUP_HISTORY_MESSAGE_RECEIVED, packet));
					}
					else
					{
						EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_INFORMATION_ACTIVITY_FROM_GROUP_HISTORY_MESSAGE_RECEIVED, packet));
						EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_HISTORY_MESSAGE_RECEIVED, packet));
					}
				}
				else
				{
					if (messageTime < activityTime)
					{
						EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_HISTORY_MESSAGE_RECEIVED, packet));
						EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_INFORMATION_ACTIVITY_FROM_GROUP_HISTORY_MESSAGE_RECEIVED, packet));
					}
					else
					{
						EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_INFORMATION_ACTIVITY_FROM_GROUP_HISTORY_MESSAGE_RECEIVED, packet));
						EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_HISTORY_MESSAGE_RECEIVED, packet));
					}
				}
			}

			else  if (messageCount > 0)
			{
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_HISTORY_MESSAGE_RECEIVED, packet));
			}
			else if (activityCount > 0)
			{
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_INFORMATION_ACTIVITY_FROM_GROUP_HISTORY_MESSAGE_RECEIVED, packet));
			}

			if (messageCount == 1 && activityCount == 0)
			{
				auto messageDTO = messageList[0];
				if (messageDTO->getMessageType() == MessageType::PAGING_MESSAGE)
				{
					auto historyPacketId = messageDTO->getPacketID();
					auto historyPacket = packetBuilder->makeOfflineGroupHistoryMessageRequest(messageDTO->getUserIdentity(), packet->getGroupId(), historyPacketId, Direction::UP, 10, ResourceManager::getInstance().appVersion);
					auto connection = ResourceManager::getInstance().getOfflineConnection();
					int sendCode = connection->sendToOfflineServer(historyPacket.byteArray);
					if (sendCode < 0)
					{
						Log(module, "Socket returned, sendCode: " << sendCode);
						break;
					}

					ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, historyPacket.byteArray, historyPacket.packet, connection, ResendProcessor::Offline));
				}
			}

			if (messageCount + activityCount == 0)
			{
				Log(module, "No more history for group " << packet->getGroupId());
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_HISTORY_MESSAGE_RECEIVE_COMPLETED, packet));
			}

			ResendProcessor::getInstance().removePacket(packet->getPacketID());
			break;
		}
		case OFFLINE_INFORMATION_WITH_MEMBERS:
		{
			auto connection = ResourceManager::getInstance().getOfflineConnection();

			std::string packetId = packet->getPacketID();
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_GROUP_INFORMATION_WITH_MEMBERS_RECEIVED, packet));
			BuiltPacket offlineGroupHistoryMessageConfirmation = packetBuilder->makeOfflineGroupConfirmation(packet->getGroupId(), packetId);
			connection->sendToOfflineServer(offlineGroupHistoryMessageConfirmation.byteArray);

			ResendProcessor::getInstance().removePacket(packet->getPacketID());
			break;
		}
		case OFFLINE_BROKEN_HISTORY_PACKET:
		case OFFLINE_BROKEN_PACKET:
		{
			ByteArray fullByteArray;
			fullByteArray = handleOfflineBrokenPacket(packet);

			if (fullByteArray.size() != 0){

				ParsedObject headerObject = parser.parseHeader(fullByteArray);
				if (headerObject.packet)
				{
					offlinePacketIdMap[headerObject.packet->getPacketID()] = packet;
				}
				push(fullByteArray);
			}
			break;
		}

		case OFFLINE_BROKEN_PACKET_CONFIRMATION:
		{
			std::string originalPacketId = packet->getPacketID();
			int sequenceNumber = packet->getSequenceNumber();
			std::string brokenPacketId = originalPacketId + "_" + ResourceManager::getInstance().toString(sequenceNumber);;

			if (sequenceNumber == 0)
			{
				auto resendPacket = ResendProcessor::getInstance().getPacketDTO(brokenPacketId);
				if (resendPacket)
				{
					auto byteArray = resendPacket->getDataBytes();

					if (byteArray)
					{
						auto byteArrayCopy = *byteArray;
						ParsedObject headerObject = parser.parseHeader(byteArrayCopy);

						if (headerObject.packet)
						{
							auto eventPacketDTO = std::make_shared<PacketDTO>();
							eventPacketDTO->setRequestStatus(true);
							eventPacketDTO->setGroupId(headerObject.packet->getGroupId());
							eventPacketDTO->setPacketID(originalPacketId);
							eventPacketDTO->setUserIdentity(headerObject.packet->getUserIdentity());

							if (headerObject.packet->getPacketType() == OFFLINE_CREATE_GROUP)
							{
								EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CREATED, eventPacketDTO));
							}
						}
					}
				}
				else
				{
					break;
				}
			}

			ResendProcessor::getInstance().removePacket(brokenPacketId);
			break;
		}

		case ROOM_BROKEN_PACKET:
		{
			ByteArray fullByteArray;
			fullByteArray = handleRoomBrokenPacket(packet);

			if (fullByteArray.size() != 0){
				push(fullByteArray);
			}
			break;
		}

		case OFFLINE_MESSAGE_CONVERSATION_LIST:
		{
			std::string packetId = packet->getPacketID();

			std::vector<SDKMessageDTO> friendChatMessageList;
			std::vector<SDKMessageDTO> groupChatMessageList;

			std::vector<std::shared_ptr< PacketDTO>> messageList = packet->getMessageList();

			if (messageList.size() == 0)
			{
                EventProcessor::getInstance().push(ChatEvent(ChatEvent::CONVERSATION_LIST_RECEIVE_COMPLETED, packet));
				break;
			}

			for (auto message : messageList)
			{
				SDKMessageDTO messageDTO;

				messageDTO.setSenderId(message->getUserIdentity());
				messageDTO.setPacketId(message->getPacketID());
				messageDTO.setMessageType(message->getMessageType());
				messageDTO.setMessage(message->getMessage());
				messageDTO.setMessageDate(message->getMessageDate());
				messageDTO.setUnreadCount(message->getUnreadCount());
                messageDTO.setTimeOut(message->getTimeout());

				if (message->getPacketType() == FRIEND_CHAT_MESSAGE)
				{
					messageDTO.setReceiverId(message->getFriendOrGroupId());
					friendChatMessageList.push_back(messageDTO);
				}
				else if (message->getPacketType() == GROUP_CHAT_MESSAGE)
				{
					messageDTO.setGroupId(message->getFriendOrGroupId());
					groupChatMessageList.push_back(messageDTO);
				}
			}

			if (!friendChatMessageList.empty()){
				std::shared_ptr< PacketDTO> friendChatPacket = std::make_shared<PacketDTO>();
                friendChatPacket->setUserIdentity(packet->getUserIdentity());
				friendChatPacket->setPacketID(packetId);
				friendChatPacket->setChatMessageList(friendChatMessageList);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CONVERSATION_LIST_RECEIVED, friendChatPacket));
			}

			if (!groupChatMessageList.empty()){
				std::shared_ptr< PacketDTO> groupChatPacket = std::make_shared<PacketDTO>();
				groupChatPacket->setPacketID(packetId);
				groupChatPacket->setChatMessageList(groupChatMessageList);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CONVERSATION_LIST_RECEIVED, groupChatPacket));
			}

			break;
		}
		case OFFLINE_GROUP_IP_PORT:
		{
			std::string serverIp = packet->getServerIp();
			int serverPort = packet->getServerPort();
			GroupIdentity groupId = packet->getGroupId();

            ResendProcessor::getInstance().removePacket(packet->getPacketID());

			if (serverIp == "" || serverPort == 0)
			{
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_GROUP, packet));
				break;
			}

			Log(module, "Registering group chat at " << groupId << " Chat server " << serverIp << ":" << serverPort);
			auto packetTimeId = ResourceManager::getInstance().generatePacketIdInSDK();

			auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
			if (!connection)
			{
				connection = std::make_shared<ChatConnection>(ResourceManager::getInstance().getSocket());
			}

			connection->setRegisterServer(serverIp, serverPort);
			ResourceManager::getInstance().addGroupConnection(groupId, connection);

			ResendProcessor::getInstance().updateGroupConnection(groupId, connection);

			BuiltPacket builtPacket = packetBuilder->makeGroupRegister(ResourceManager::getInstance().getUserId(), groupId, packetTimeId.packetId, ResourceManager::getInstance().getDeviceType(), ResourceManager::getInstance().appVersion);
			if (!builtPacket.byteArray)
			{
				Log(module, "Packet builder error");
				break;
			}

			auto sendCode = connection->sendToRegisterServer(builtPacket.byteArray);
			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetTimeId.packetId << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Register));
			break;
		}

		case OFFLINE_PUBLIC_ROOM_IPPORT_CONFIRMATION:
		{
			hash << OFFLINE_PUBLIC_ROOM_IPPORT_CONFIRMATION << packet->getPacketID();

			if (duplicateChecker.isSafe(hash.str()))
			{
				ResendProcessor::getInstance().removePacket(packet->getPacketID());

				std::string roomServerIp = packet->getServerIp();
				int roomServerPort = packet->getServerPort();

				//            std::string roomServerIp = "192.168.1.251";
				//            int roomServerPort = 1500;

				Log(module, "Public Chat Server Ip " << roomServerIp << ". Port " << roomServerPort);

				auto connection = std::make_shared<ChatConnection>(ResourceManager::getInstance().getSocket());
				connection->setRegisterServer(roomServerIp, roomServerPort);

				auto roomId = packet->getRoomId();
				auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
				if (!roomInfo) {
					Log(module, "Room Info Not Found for roomId: " + roomId);
					break;
				}
				roomInfo->setConnection(connection);
				roomInfo->setNumberOfMember(packet->getNumberOfMembers());

				std::string packetId = ResourceManager::getInstance().generatePacketIdInSDK().packetId;
				std::string memberFullName = roomInfo->getMemberName();
				std::string memberUrl = roomInfo->getMemberUrl();

				BuiltPacket builtPacket = packetBuilder->makePublicRoomRegisterPacket(ResourceManager::getInstance().getUserId(), roomId, packetId, memberFullName, memberUrl, ResourceManager::getInstance().getDeviceType(), roomInfo->getRingId());

				if (!builtPacket.byteArray) {
					Log(module, "Packet builder error");
					break;
				}

				auto sendCode = connection->sendToRegisterServer(builtPacket.byteArray);
				if (sendCode < 0) {
					Log(module, "Socket returned " << sendCode);
					break;
				}

				Log(module, "Adding " << packetId << " for resend");
				ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Register));
			}
			break;
		}

		case PUBLIC_ROOM_REGISTER_CONFIRMATION:
		{
			hash << PUBLIC_ROOM_REGISTER_CONFIRMATION << packet->getPacketID();

			if (duplicateChecker.isSafe(hash.str()))
			{

				ResendProcessor::getInstance().removePacket(packet->getPacketID());

				//UserIdentity userId = packet->getUserIdentity();
				RoomIdentity roomId = packet->getRoomId();
				std::string packetId = ResourceManager::getInstance().generatePacketIdInSDK().packetId;
				auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
				if (!roomInfo) {
					Log(module, "Room Info Not Found for roomId: " + roomId);
					break;
				}

				roomInfo->setAnonymousId(packet->getRecipientId());

				auto connection = roomInfo->getConnection();

				connection->setChatServerPort(packet->getChatBindingPort());

				//                //Get Member List of the Chat room
				//                Log(module, "Getting Public Chat room member list: " + roomId);
				//
				//                BuiltPacket builtPacket = packetBuilder->makePublicChatGetMemberList(ResourceManager::getInstance().getUserId(), roomId, packetId);
				//                if (!builtPacket.byteArray) {
				//                    Log(module, "Packet Builder Error");
				//                    break;
				//                }
				//
				//                if (!connection) {
				//                    Log(module, "Room Connection Not found");
				//                    break;
				//                }
				//
				//                connection->sendToChatServer(builtPacket.byteArray);

				packet->setNumberOfMembers(roomInfo->getNumberOfMember());
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_CHAT_REGISTER_SUCCESS, packet));

				// Add Room Keep alive

				//                Log(module, "Adding " << packetId << " for resend");
				//                ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Chat));

				BuiltPacket keepalivePacket = packetBuilder->makePublicRoomChatIdelPacket(ResourceManager::getInstance().getUserId(), roomId, ResourceManager::getInstance().getDeviceType()); //platform = 2
				if (keepalivePacket.byteArray) {
					KeepaliveProcessor::getInstance().addPublicRoomKeepalivePacket(roomId, std::make_shared<KeepalivePacket>(connection, keepalivePacket.byteArray));
					connection->sendToChatServer(keepalivePacket.byteArray);
					auto packetTimeId = ResourceManager::getInstance().generatePacketIdInSDK();
					auto resendPacket = ResendProcessor::ResendPacket(packetTimeId.packetId, keepalivePacket.byteArray, keepalivePacket.packet, connection, ResendProcessor::Chat, 0);
					ResendProcessor::getInstance().addResendPacket(resendPacket);
				}
				else {
					Log(module, "Packet builder error");
				}

			}
			break;
		}

		case PUBLIC_ROOM_CHAT_MESSAGE_SENT:
		{
			std::string packetId = packet->getPacketID();

			auto pos = packetId.find('_');
			if (pos != std::string::npos)
			{
				std::string actualPacketId = packetId.substr(0, pos);
				packet->setPacketID(actualPacketId);
			}

			auto resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);

			if (resendPacket)
			{
				Log(module, "resend packet exist");
				if (resendPacket->getPacketType() != PUBLIC_ROOM_CHAT_MESSAGE_BROKEN && resendPacket->getPacketType() != PUBLIC_ROOM_CHAT_MESSAGE_BROKEN_EDIT)
				{
					if (resendPacket->getPacketType() == PUBLIC_ROOM_CHAT_MESSAGE_EDIT){
						packet->setMessageEdited(true);
					}
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_CHAT_DELIVERED, packet));
				}
				else if (resendPacket->getSequenceNumber() == (resendPacket->getNumberOfMessage() - 1))
				{
					if (resendPacket->getPacketType() == PUBLIC_ROOM_CHAT_MESSAGE_BROKEN_EDIT){
						packet->setMessageEdited(true);
					}
					EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_CHAT_DELIVERED, packet));
				}
			}

			ResendProcessor::getInstance().removePacket(packetId);
			break;
		}

		case PUBLIC_ROOM_CHAT_MESSAGE:
		{
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_CHAT_MESSAGE_RECEIVED, packet));
			KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(packet->getRoomId());

			UserIdentity friendId = packet->getUserIdentity();
			RoomIdentity roomId = packet->getRoomId();
			std::string packetId = packet->getPacketID();

			auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
			if (!roomInfo) {
				Log(module, "Room Info Not Found for roomId: " + roomId);
				break;
			}

			BuiltPacket builtPacket = packetBuilder->makePublicRoomChatMessageDeliveredPacket(ResourceManager::getInstance().getUserId(), friendId, roomId, packetId);
			if (!builtPacket.byteArray) {
				Log(module, "Packet builder error");
				break;
			}

			auto connection = roomInfo->getConnection();

			if (!connection) {
				Log(module, "Room Connection Not Found for roomId: " + roomId);
				break;
			}

			auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
			if (sendCode < 0) {
				Log(module, "Socket returned " << sendCode);
				break;
			}


			break;
		}

		case PUBLIC_ROOM_CHAT_MESSAGE_EDIT:
		{
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_CHAT_EDITED, packet));
			KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(packet->getRoomId());

			UserIdentity friendId = packet->getUserIdentity();
			RoomIdentity roomId = packet->getRoomId();
			std::string packetId = packet->getPacketID();

			auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
			if (!roomInfo) {
				Log(module, "Room Info Not Found for roomId: " + roomId);
				break;
			}

			BuiltPacket builtPacket = packetBuilder->makePublicRoomChatMessageDeliveredPacket(ResourceManager::getInstance().getUserId(), friendId, roomId, packetId);
			if (!builtPacket.byteArray) {
				Log(module, "Packet builder error");
				break;
			}

			auto connection = roomInfo->getConnection();

			if (!connection) {
				Log(module, "Room Connection Not Found for roomId: " + roomId);
				break;
			}

			auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
			if (sendCode < 0) {
				Log(module, "Socket returned " << sendCode);
				break;
			}


			break;
		}

		case PUBLIC_CHAT_DELETE_MESSAGE:
		{
			RoomIdentity roomId = packet->getRoomId();
			std::string packetId = packet->getPacketID();

			auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
			if (!roomInfo) {
				Log(module, "Room Info Not Found for roomId: " + roomId);
				break;
			}

			BuiltPacket builtPacket = packetBuilder->makePublicRoomChatDeleteMessagePacketConfirmation(ResourceManager::getInstance().getUserId(), roomId, packetId);
			if (!builtPacket.byteArray) {
				Log(module, "Packet builder error");
				break;
			}

			auto connection = roomInfo->getConnection();

			if (!connection) {
				Log(module, "Room Connection Not Found for roomId: " + roomId);
				break;
			}

			auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
			if (sendCode < 0) {
				Log(module, "Socket returned " << sendCode);
				break;
			}

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_MESSAGE_DELETED, packet));

			break;
		}

		case PUBLIC_CHAT_DELETE_MESSAGE_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			ResendProcessor::getInstance().removePacket(packetId);
			packet->setRequestStatus(true);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_DELETE_MESSAGE_REQUEST_STATUS, packet));
			break;
		}

		case PUBLIC_CHAT_LIKE_A_MESSAGE:
		{
			RoomIdentity roomId = packet->getRoomId();
			std::string packetId = packet->getPacketID();

			auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
			if (!roomInfo) {
				Log(module, "Room Info Not Found for roomId: " + roomId);
				break;
			}

			BuiltPacket builtPacket = packetBuilder->makePublicRoomChatLikeUnlikeConfirmation(ResourceManager::getInstance().getUserId(), roomId, packetId);
			if (!builtPacket.byteArray) {
				Log(module, "Packet builder error");
				break;
			}

			auto connection = roomInfo->getConnection();

			if (!connection) {
				Log(module, "Room Connection Not Found for roomId: " + roomId);
				break;
			}

			auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
			if (sendCode < 0) {
				Log(module, "Socket returned " << sendCode);
				break;
			}

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_MESSAGE_LIKED, packet));

			break;
		}

		case PUBLIC_CHAT_UNLIKE_A_MESSAGE:
		{
			RoomIdentity roomId = packet->getRoomId();
			std::string packetId = packet->getPacketID();

			auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
			if (!roomInfo) {
				Log(module, "Room Info Not Found for roomId: " + roomId);
				break;
			}

			BuiltPacket builtPacket = packetBuilder->makePublicRoomChatLikeUnlikeConfirmation(ResourceManager::getInstance().getUserId(), roomId, packetId);
			if (!builtPacket.byteArray) {
				Log(module, "Packet builder error");
				break;
			}

			auto connection = roomInfo->getConnection();

			if (!connection) {
				Log(module, "Room Connection Not Found for roomId: " + roomId);
				break;
			}

			auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
			if (sendCode < 0) {
				Log(module, "Socket returned " << sendCode);
				break;
			}

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_MESSAGE_UNLIKED, packet));

			break;
		}

		case PUBLIC_CHAT_LIKE_UNLIKE_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			auto resendPacketDTO = ResendProcessor::getInstance().getPacketDTO(packetId);

			if (resendPacketDTO)
			{
				resendPacketDTO->setRequestStatus(true);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_LIKE_UNLIKE_REQUEST_STATUS, resendPacketDTO));
			}

			ResendProcessor::getInstance().removePacket(packetId);
			break;
		}

		case PUBLIC_CHAT_REPORT_A_MESSAGE:
		{
			RoomIdentity roomId = packet->getRoomId();
			std::string packetId = packet->getPacketID();

			auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
			if (!roomInfo) {
				Log(module, "Room Info Not Found for roomId: " + roomId);
				break;
			}

			BuiltPacket builtPacket = packetBuilder->makePublicRoomChatReportMessagePacketConfirmation(ResourceManager::getInstance().getUserId(), roomId, packetId);
			if (!builtPacket.byteArray) {
				Log(module, "Packet builder error");
				break;
			}

			auto connection = roomInfo->getConnection();

			if (!connection) {
				Log(module, "Room Connection Not Found for roomId: " + roomId);
				break;
			}

			auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
			if (sendCode < 0) {
				Log(module, "Socket returned " << sendCode);
				break;
			}

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_MESSAGE_REPORTED, packet));

			break;
		}

		case PUBLIC_CHAT_REPORT_A_MESSAGE_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			auto resendPacketDTO = ResendProcessor::getInstance().getPacketDTO(packetId);

			if (resendPacketDTO)
			{
				resendPacketDTO->setRequestStatus(true);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_REPORT_A_MESSAGE_REQUEST_STATUS, resendPacketDTO));
			}

			ResendProcessor::getInstance().removePacket(packetId);
			break;
		}

		case OFFLINE_PUBLIC_ROOM_LIST_REQUEST_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			ResendProcessor::getInstance().removePacket(packetId);
			packet->setRequestStatus(true);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_LIST_REQUEST_STATUS, packet));
			break;
		}

		case OFFLINE_PUBLIC_ROOM_LIST:
		{
			std::string packetId = packet->getPacketID();

			BuiltPacket builtPacket = packetBuilder->makeOfflinePublicRoomListRequestConfirmation(packetId);
			if (!builtPacket.byteArray) {
				Log(module, "Packet builder error");
				break;
			}

			auto connection = ResourceManager::getInstance().getOfflineConnection();

			if (!connection) {
				Log(module, "Offline Connection Not found");
				break;
			}

			auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);
			if (sendCode < 0) {
				Log(module, "Socket returned " << sendCode);
				break;
			}

			packet->setRoomListFromHistory(false);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_LIST_RECEIVED, packet));

			break;
		}

		case OFFLINE_PUBLIC_ROOM_LIST_WITH_HISTORY:
		{
			std::string packetId = packet->getPacketID();

			BuiltPacket builtPacket = packetBuilder->makeOfflinePublicRoomListRequestConfirmation(packetId);
			if (!builtPacket.byteArray) {
				Log(module, "Packet builder error");
				break;
			}

			auto connection = ResourceManager::getInstance().getOfflineConnection();

			if (!connection) {
				Log(module, "Offline Connection Not found");
				break;
			}

			auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);
			if (sendCode < 0) {
				Log(module, "Socket returned " << sendCode);
				break;
			}

			packet->setRoomListFromHistory(true);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_LIST_RECEIVED, packet));

			break;
		}

		case OFFLINE_ROOM_INFORMATION:
		{
			std::string packetId = packet->getPacketID();
			ResendProcessor::getInstance().removePacket(packetId);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::ROOM_INFORMATION_RECEIVED, packet));
			break;
		}

		case PUBLIC_ROOM_CHAT_MESSAGE_BROKEN:
		{
			handleBrokenPublicRoomChat(packet);
			KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(packet->getRoomId());
			break;
		}

		case PUBLIC_ROOM_CHAT_MESSAGE_BROKEN_EDIT:
		{
			handleBrokenPublicRoomChat(packet);
			KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(packet->getRoomId());
			break;
		}

		case PUBLIC_ROOM_CHAT_MESSAGE_TYPING:
		{
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_CHAT_TYPING, packet));
			KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(packet->getRoomId());
			break;
		}

		case PUBLIC_CHAT_GET_MEMBER_LIST_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			ResendProcessor::getInstance().removePacket(packetId);
			packet->setRequestStatus(true);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_MEMBER_LIST_REQUEST_STATUS, packet));
			break;
		}

		case PUBLIC_CHAT_MEMBER_LIST:
		{
			RoomIdentity roomId = packet->getRoomId();
			std::string packetId = packet->getPacketID();

			auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
			if (!roomInfo) {
				Log(module, "Room Info Not Found for roomId: " + roomId);
				break;
			}

			BuiltPacket builtPacket = packetBuilder->makePublicChatGetMemberListConfirmation(ResourceManager::getInstance().getUserId(), roomId, packetId);
			if (!builtPacket.byteArray) {
				Log(module, "Packet builder error");
				break;
			}

			auto connection = roomInfo->getConnection();

			if (!connection) {
				Log(module, "Room Connection Not found");
				break;
			}

			auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
			if (sendCode < 0) {
				Log(module, "Socket returned " << sendCode);
				break;
			}

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_MEMBER_LIST_RECEIVED, packet));

			break;
		}

		case PUBLIC_CHAT_MEMBER_COUNT_CHANGE:
		{

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_MEMBER_COUNT_CHANGED, packet));

			RoomIdentity roomId = packet->getRoomId();
			std::string packetId = packet->getPacketID();

			auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
			if (!roomInfo) {
				Log(module, "Room Info Not Found for roomId: " + roomId);
				break;
			}

			BuiltPacket builtPacket = packetBuilder->makePublicRoomChatMemberCountChangeConfirmation(ResourceManager::getInstance().getUserId(), roomId, packetId);
			if (!builtPacket.byteArray) {
				Log(module, "Packet builder error");
				break;
			}

			auto connection = roomInfo->getConnection();

			if (!connection) {
				Log(module, "Room Connection Not found");
				break;
			}

			auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
			if (sendCode < 0) {
				Log(module, "Socket returned " << sendCode);
				break;
			}

			break;
		}

		case OFFLINE_ROOM_GET_HISTORY_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			ResendProcessor::getInstance().removePacket(packetId);
			packet->setRequestStatus(true);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_CHAT_HISTORY_REQUEST_STATUS, packet));
			break;
		}

		case OFFLINE_ROOM_HISTORY_MESSAGE_LIST:
		{
			auto connection = ResourceManager::getInstance().getOfflineConnection();

			std::string packetId = packet->getPacketID();
			std::string roomId = packet->getRoomId();

			BuiltPacket offlineRoomHistoryMessageConfirmation = packetBuilder->makeOfflineRoomGetHistoryConfirmationPacket(roomId, packetId);
			connection->sendToOfflineServer(offlineRoomHistoryMessageConfirmation.byteArray);

			int messageCount = packet->getMessageList().size();

			if (messageCount > 0)
			{
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::ROOM_HISTORY_RECEIVED, packet));
			}
			else{
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_ROOM_CHAT_HISTORY_MESSAGE_RECEIVE_COMPLETED, packet));
			}

			break;
		}

		//Live-stream-chat
		case LIVE_STREAM_CHAT_REGISTER_CONFIRMATION:
		{
			ResendProcessor::getInstance().removePacket(packet->getPacketID());

			auto liveStreamChatInfo = ResourceManager::getInstance().getLiveStreamChatInfo(packet->getPublisherId());

			std::shared_ptr< ChatConnection> connection = nullptr;
			if (liveStreamChatInfo)
			{
				connection = liveStreamChatInfo->getConnection();
				connection->setChatServerPort(packet->getChatBindingPort());
			}

			long long serverTime = packet->getServerDate();
			Log(module, "Server time: " << serverTime);
			long long timeDifference = serverTime - ResourceManager::getInstance().gettime();
			Log(module, "Time difference: " << timeDifference);
			ResourceManager::getInstance().setTimeDifference(timeDifference);

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SERVER_TIME_DIFFERENCE_SYNCED, nullptr));
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::LIVE_STREAM_CHAT_REGISTER_SUCCESS, packet));

			BuiltPacket keepalivePacket = packetBuilder->makeLiveStreamChatIdlePacket(ResourceManager::getInstance().getUserId(), packet->getPublisherId(), ResourceManager::getInstance().getDeviceType());
			if (keepalivePacket.byteArray)
			{
				if (connection)
				{
					KeepaliveProcessor::getInstance().addLiveStreamChatKeepalivePacket(packet->getPublisherId(), std::make_shared<KeepalivePacket>(connection, keepalivePacket.byteArray));
					connection->sendToChatServer(keepalivePacket.byteArray);
					connection->sendToChatServer(keepalivePacket.byteArray);
					connection->sendToChatServer(keepalivePacket.byteArray);
					auto packetTimeId = ResourceManager::getInstance().generatePacketIdInSDK();
					auto resendPacket = ResendProcessor::ResendPacket(packetTimeId.packetId, keepalivePacket.byteArray, keepalivePacket.packet, connection, ResendProcessor::Chat, 0);
					ResendProcessor::getInstance().addResendPacket(resendPacket);
				}
			}
			else
			{
				Log(module, "Packet builder error");
			}
			break;
		}

		case LIVE_STREAM_CHAT_MESSAGE_TYPING:
		{
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::LIVE_STREAM_CHAT_TYPING, packet));
			KeepaliveProcessor::getInstance().resetLiveStreamChatKeepalive(packet->getPublisherId());
			break;
		}

		case LIVE_STREAM_CHAT_MESSAGE:
		{
			if (packet->getPublisherId() == ResourceManager::getInstance().getLatestPublisherId())
			{
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::LIVE_STREAM_CHAT_MESSAGE_RECEIVED, packet));
			}

			KeepaliveProcessor::getInstance().resetLiveStreamChatKeepalive(packet->getPublisherId());

			UserIdentity publisherId = packet->getPublisherId();
			std::string packetId = packet->getPacketID();

			auto liveStreamChatInfo = ResourceManager::getInstance().getLiveStreamChatInfo(packet->getPublisherId());
			if (!liveStreamChatInfo) {
				Log(module, "Live stream chat Info Not Found for publisher id: " + publisherId);
				break;
			}

			BuiltPacket builtPacket = packetBuilder->makeLiveStreamChatMessageDeliveredPacket(ResourceManager::getInstance().getUserId(), publisherId, packetId);
			if (!builtPacket.byteArray) {
				Log(module, "Packet builder error");
				break;
			}

			auto connection = liveStreamChatInfo->getConnection();

			if (!connection) {
				Log(module, "Live stream chat Not Found for publisher id: " + publisherId);
				break;
			}

			auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
			if (sendCode < 0) {
				Log(module, "Socket returned " << sendCode);
				break;
			}

			break;
		}

		case LIVE_STREAM_CHAT_MESSAGE_DELIVERED:
		{
			break;
		}

		case LIVE_STREAM_CHAT_MESSAGE_SENT:
		{
			std::string packetId = packet->getPacketID();
			auto resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);

			if (resendPacket)
			{
				Log(module, "resend packet exist");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::LIVE_STREAM_CHAT_DELIVERED, packet));
			}

			ResendProcessor::getInstance().removePacket(packetId);
			break;
		}

		case LIVE_STREAM_CHAT_BLOCK_USER:
		{
			std::string packetId = packet->getPacketID();
			UserIdentity publisherId = packet->getPublisherId();

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::LIVE_STREAM_CHAT_USER_BLOCKED, packet));

			auto liveStreamChatInfo = ResourceManager::getInstance().getLiveStreamChatInfo(publisherId);
			if (!liveStreamChatInfo) {
				Log(module, "Live stream chat Info Not Found for publisher id: " + publisherId);
				break;
			}

			auto connection = liveStreamChatInfo->getConnection();

			if (!connection) {
				Log(module, "Live stream chat Not Found for publisher id: " + publisherId);
				break;
			}

			BuiltPacket builtPacket = packetBuilder->makeLiveStreamChatBlockUserConfirmationPacket(publisherId, ResourceManager::getInstance().getUserId(), packetId);
			if (!builtPacket.byteArray) {
				Log(module, "Packet builder error");
				break;
			}

			auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
			if (sendCode < 0) {
				Log(module, "Socket returned " << sendCode);
				break;
			}

			break;
		}

		case LIVE_STREAM_CHAT_BLOCK_USER_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			ResendProcessor::getInstance().removePacket(packetId);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::LIVE_STREAM_CHAT_BLOCK_USER_REQUEST_STATUS, packet));
			break;
		}

		//Anonymous friend chat
		case ANONYMOUS_REGISTER_CONFIRMATION:
		{
			auto friendInfo = ResourceManager::getInstance().getFriendInfo(packet->getUserIdentity(), packet->getFriendIdentity());
			std::shared_ptr< ChatConnection> connection = nullptr;
			if (friendInfo)
			{
				connection = friendInfo->getConnection();
				connection->setChatServerPort(packet->getChatBindingPort());
			}

			packet->setFromAnonymous(true);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_REGISTER_SUCCESS, packet));
			ResendProcessor::getInstance().removePacket(packet->getPacketID());
			BuiltPacket keepalivePacket = packetBuilder->makeFriendChatIdel(ResourceManager::getInstance().getAnonymousUser(packet->getFriendIdentity()).selfAnonymousId, packet->getFriendIdentity(), ResourceManager::getInstance().getDeviceType());
			if (keepalivePacket.byteArray)
			{
				if (connection)
				{
					KeepaliveProcessor::getInstance().addFriendKeepalivePacket(packet->getUserIdentity(), packet->getFriendIdentity(), OnlineStatus::ONLINE, std::make_shared<KeepalivePacket>(connection, keepalivePacket.byteArray));
				}
			}
			else
			{
				Log(module, "Packet builder error");
			}
			break;
		}

		case ANONYMOUS_UNREGISTER:
		{
			UserIdentity userId = packet->getFriendIdentity();
			UserIdentity friendId = packet->getUserIdentity();

			auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);

			if (friendInfo)
			{
				ResourceManager::getInstance().removeFriendInfo(userId, friendId);
				KeepaliveProcessor::getInstance().removeFriendKeepalive(userId, friendId);
				packet->setFromAnonymous(true);
				ResourceManager::getInstance().removeAnonymousUser(friendId);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_UNREGISTERED, packet));
			}
			break;
		}
		case SHADOW_IDS_INFO_RESPONSE:
		{
			std::string packetId = packet->getPacketID();
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHADOW_IDS_INFO_RESPONSE_RECEIVED, packet));
			ResendProcessor::getInstance().removePacket(packetId);
			break;
		}
		//Group file transfer
		case GROUP_FILE_SESSION_REQUEST_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			ResendProcessor::getInstance().removePacket(packetId);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_FILE_TRANSFER_SESSION_REQUEST_SUCCESS, packet));
			break;
		}

		case GROUP_FILE_STREAM_REQUEST:
		{
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_FILE_TRANSFER_STREAM_REQUEST_RECEIVED, packet));

			UserIdentity friendId = packet->getUserIdentity();
			GroupIdentity groupId = packet->getGroupId();
			std::string packetId = packet->getPacketID();

			BuiltPacket fileStreanRequestConfirmation = packetBuilder->makeGroupFileStreamRequestConfirmation(ResourceManager::getInstance().getUserId(), friendId, groupId, packetId, packet->getFileIdentity(), true);
			if (!fileStreanRequestConfirmation.byteArray){
				Log(module, "Packet Builder Error");
				return;
			}

			auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
			if (!connection){
				Log(module, "connection not found for group: " << groupId);
				return;
			}

			auto sendCode = connection->sendToChatServer(fileStreanRequestConfirmation.byteArray);
			if (sendCode < 0){
				Log(module, "Socket Error");
				return;
			}

			break;
		}

		case GROUP_FILE_STREAM_REQUEST_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			ResendProcessor::getInstance().removePacket(packetId);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_FILE_TRANSFER_STREAM_REQUEST_SUCCESS, packet));
			break;
		}

		case FRIEND_FILE_STREAM_REQUEST:
		{
			UserIdentity userdId = packet->getFriendIdentity();
			UserIdentity friendId = packet->getUserIdentity();
			FileIdentity fileId = packet->getFileIdentity();

			Log(module, "Sending File Stream Request Confirmation to - " << friendId);
			auto packetId = packet->getPacketID();

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_FILE_TRANSFER_STREAM_REQUEST_RECEIVED, packet));

			auto builtPacket = packetBuilder->makeFriendFileStreamRequestConfirmationPacket(userdId, friendId, packetId, fileId, true);

			if (!builtPacket.byteArray)
			{
				Log(module, "Packet builder error");
				break;
			}

			auto friendInfo = ResourceManager::getInstance().getFriendInfo(userdId, friendId);
			if (!friendInfo)
			{
				Log(module, "Connection not found");
				break;
			}
			auto connection = friendInfo->getConnection();
			auto sendCode = connection->sendToChatServer(builtPacket.byteArray);

			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			break;
		}

		case FRIEND_FILE_STREAM_REQUEST_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			ResendProcessor::getInstance().removePacket(packetId);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_FILE_TRANSFER_STREAM_REQUEST_SUCCESS, packet));
			break;
		}

		case FRIEND_FILE_SESSION_REQUEST_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			ResendProcessor::getInstance().removePacket(packetId);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_FILE_TRANSFER_SESSION_REQUEST_SUCCESS, packet));
			break;
		}

		case FRIEND_GET_CHAT_MESSAGE_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			ResendProcessor::getInstance().removePacket(packetId);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_GET_CHAT_MESSAGE_RECEIVED, packet));
			break;
		}

		case GROUP_GET_CHAT_MESSAGE_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			ResendProcessor::getInstance().removePacket(packetId);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_GET_CHAT_MESSAGE_RECEIVED, packet));
			break;
		}

		case OFFLINE_PUBLIC_CHAT_CATEGORY_LIST:
		{
			std::string packetId = packet->getPacketID();
			ResendProcessor::getInstance().removePacket(packetId);
			packet->setRequestStatus(true);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::OFFLINE_PUBLIC_CHAT_CATEGORY_LIST_REQUEST_STATUS, packet));
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_ROOM_CATEGORY_LIST_RECEIVED, packet));
			break;
		}

		case PUBLIC_CHAT_LIKE_MEMBER_LIST:
		{
			std::string packetId = packet->getPacketID();

			auto resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
			if (resendPacket)
			{
				resendPacket->setRequestStatus(true);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_LIKE_MEMBER_LIST_REQUEST_STATUS, resendPacket));
				packet->setOriginalPacketID(resendPacket->getOriginalPacketID());
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::PUBLIC_CHAT_LIKE_MEMBER_LIST_RECEIVED, packet));
				ResendProcessor::getInstance().removePacket(packetId);
			}
			break;
		}

		case FRIEND_INIT_CHUNK_FILE_DOWNLOAD:
		{
			UserIdentity userId = packet->getFriendIdentity();
			UserIdentity friendId = packet->getUserIdentity();
			std::string packetId = packet->getPacketID();
			std::string fileName = packet->getFileDownloadId(); // file name was used as download_id
			int fileDomainType = packet->getFileDomainType();
			int secretTimeout = packet->getTimeout();

			auto packetIncomingMedia = std::make_shared<PacketDTO>();

			packetIncomingMedia->setUserIdentity(userId);
			packetIncomingMedia->setFriendIdentity(friendId);
			packetIncomingMedia->setLocalFilePath(fileName);
			packetIncomingMedia->setPacketID(packetId);
			packetIncomingMedia->setMessageType(packet->getFileDomainType());
			packetIncomingMedia->setMessageDate(packet->getMessageDate());
			packetIncomingMedia->setTimeout(secretTimeout);
			packetIncomingMedia->setIsSecretVisible(packet->getIsSecretVisible());
			packetIncomingMedia->setCaption(packet->getCaption());
			packetIncomingMedia->setWidthOrFileSize(packet->getWidthOrFileSize());
			packetIncomingMedia->setHeightOrDuration(packet->getHeightOrDuration());

			EventProcessor::getInstance().push(ChatEvent(
				ChatEvent::INCOMING_CHAT_MEDIA_FILE, packetIncomingMedia));

			auto cloudDownloadNotificationHandler = std::static_pointer_cast<CloudDownloadNotificationHandler>(
				CloudNotificationManager::getInstance().getCloudNotificationHandler(packetId));

			if (!cloudDownloadNotificationHandler){ // Create handler only once even if INIT packet received multiple times for same packetId

				std::shared_ptr< CloudDownloadNotificationHandler> cloudDownloadNotificationHandler =
					std::make_shared<CloudDownloadNotificationHandler>();

				cloudDownloadNotificationHandler->setTransferType(TransferType::FRIEND_CHAT_MEDIA);
				cloudDownloadNotificationHandler->setUserId(userId);
				cloudDownloadNotificationHandler->setFriendId(friendId);
				cloudDownloadNotificationHandler->setFileName(fileName);
				cloudDownloadNotificationHandler->setFileDomainType(fileDomainType);
				cloudDownloadNotificationHandler->setInitChunkCount(packet->getFileChunkCount());
				cloudDownloadNotificationHandler->setInitChunkSize(packet->getFileChunkSize());
				cloudDownloadNotificationHandler->setInitFileSize(packet->getFileSize());
				cloudDownloadNotificationHandler->setPacketId(packetId);
				cloudDownloadNotificationHandler->setSecretTimeout(secretTimeout);
				cloudDownloadNotificationHandler->setChunkedTransfer(true);

				ipvcore::cloud::Domain fileDomain;
				std::string targetPath = internetchecker::InternetChecker::getInstance().getIpListFilePath() +
					ipvcore::generic::file_system::kDirSep + fileName;

                if (fileDomainType == IMAGE_FILE_FROM_GALLERY || fileDomainType == IMAGE_FILE_FROM_CAMERA || fileDomainType == GIF_FILE) {
					fileDomain = ipvcore::cloud::Domain::CHAT_IMAGE;

					std::string chatImageDownloadPath;
					if (secretTimeout > 0){ //secret chat
						chatImageDownloadPath = ResourceManager::getInstance().getSecretChatImageDownloadPath();
					}
					else {
						chatImageDownloadPath = ResourceManager::getInstance().getChatImageDownloadPath();
					}

					if (!chatImageDownloadPath.empty()){
						targetPath = chatImageDownloadPath + ipvcore::generic::file_system::kDirSep + fileName;
					}
				}
				else if (fileDomainType == AUDIO_FILE) {
					fileDomain = ipvcore::cloud::Domain::CHAT_AUDIO;

					std::string chatAudioDownloadPath;
					if (secretTimeout > 0){
						chatAudioDownloadPath = ResourceManager::getInstance().getSecretChatAudioDownloadPath();
					}
					else {
						chatAudioDownloadPath = ResourceManager::getInstance().getChatAudioDownloadPath();
					}

					if (!chatAudioDownloadPath.empty()){
						targetPath = chatAudioDownloadPath + ipvcore::generic::file_system::kDirSep + fileName;
					}
				}
				else if (fileDomainType == VIDEO_FILE) {
					fileDomain = ipvcore::cloud::Domain::CHAT_VIDEO;

					std::string chatVideoDownloadPath;
					if (secretTimeout > 0){
						chatVideoDownloadPath = ResourceManager::getInstance().getSecretChatVideoDownloadPath();
					}
					else {
						chatVideoDownloadPath = ResourceManager::getInstance().getChatVideoDownloadPath();
					}

					if (!chatVideoDownloadPath.empty()){
						targetPath = chatVideoDownloadPath + ipvcore::generic::file_system::kDirSep + fileName;
					}
				}

				cloudDownloadNotificationHandler->setTargetFilePath(targetPath);

				CloudNotificationManager::getInstance().addCloudNotificationHandler(
					packetId, cloudDownloadNotificationHandler);

				std::shared_ptr< ipvcore::cloud::ChunkedDownloadParams> init_download_params =
					std::make_shared<ipvcore::cloud::ChunkedDownloadParams>();

				init_download_params->download_id = fileName;

				init_download_params->uploader_id = ResourceManager::toLongToString(cloudDownloadNotificationHandler->getFriendId());

				init_download_params->chunk_count = packet->getFileChunkCount();
				init_download_params->chunk_size = packet->getFileChunkSize();
				init_download_params->file_size = packet->getFileSize();
				init_download_params->domain = fileDomain;
				init_download_params->file_path = targetPath;

				std::shared_ptr< ipvcore::cloud::DownloadResponse> downloadResponse =
					ipvcore::cloud::Manager::instance()->init_chunked_download(
					init_download_params, cloudDownloadNotificationHandler);

				if (downloadResponse->success()) {
					Log(module, "Init chunked download successful: " << downloadResponse->message());
				}
				else {
					Log(module, "Init chunked download failed: " << downloadResponse->message());
				}
			}

			auto builtPacket = packetBuilder->makeFriendFileChunkConfirmationPacket(
				userId, friendId, packetId);

			if (!builtPacket.byteArray)
			{
				Log(module, "Packet builder error");
				break;
			}

			auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
			if (!friendInfo)
			{
				Log(module, "Connection not found");
				break;
			}

			auto connection = friendInfo->getConnection();
			auto sendCode = connection->sendToChatServer(builtPacket.byteArray);

			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId);

			break;
		}

		case GROUP_INIT_CHUNK_FILE_DOWNLOAD:
		{
			UserIdentity friendId = packet->getUserIdentity();
			GroupIdentity groupId = packet->getGroupId();
			std::string packetId = packet->getPacketID();
			std::string fileName = packet->getFileDownloadId(); // file name was used as download_id
			int fileDomainType = packet->getFileDomainType();

			auto packetIncomingMedia = std::make_shared<PacketDTO>();
			packetIncomingMedia->setFriendIdentity(friendId);
			packetIncomingMedia->setGroupId(groupId);
			packetIncomingMedia->setLocalFilePath(fileName);
			packetIncomingMedia->setPacketID(packetId);
			packetIncomingMedia->setMessageType(packet->getFileDomainType());
			packetIncomingMedia->setMessageDate(packet->getMessageDate());
			packetIncomingMedia->setCaption(packet->getCaption());
			packetIncomingMedia->setWidthOrFileSize(packet->getWidthOrFileSize());
			packetIncomingMedia->setHeightOrDuration(packet->getHeightOrDuration());

			EventProcessor::getInstance().push(ChatEvent(
				ChatEvent::INCOMING_GROUP_CHAT_MEDIA_FILE, packetIncomingMedia));

			auto cloudDownloadNotificationHandler = std::static_pointer_cast<CloudDownloadNotificationHandler>(
				CloudNotificationManager::getInstance().getCloudNotificationHandler(packetId));

			if (!cloudDownloadNotificationHandler){ // Create handler only once even if INIT packet received multiple times for same packetId

				std::shared_ptr< CloudDownloadNotificationHandler> cloudDownloadNotificationHandler =
					std::make_shared<CloudDownloadNotificationHandler>();

				cloudDownloadNotificationHandler->setTransferType(TransferType::GROUP_CHAT_MEDIA);
				cloudDownloadNotificationHandler->setFriendId(friendId);
				cloudDownloadNotificationHandler->setGroupId(groupId);
				cloudDownloadNotificationHandler->setFileName(fileName);
				cloudDownloadNotificationHandler->setFileDomainType(fileDomainType);
				cloudDownloadNotificationHandler->setInitChunkCount(packet->getFileChunkCount());
				cloudDownloadNotificationHandler->setInitChunkSize(packet->getFileChunkSize());
				cloudDownloadNotificationHandler->setInitFileSize(packet->getFileSize());
				cloudDownloadNotificationHandler->setPacketId(packetId);
				cloudDownloadNotificationHandler->setChunkedTransfer(true);

				ipvcore::cloud::Domain fileDomain;
				std::string targetPath = internetchecker::InternetChecker::getInstance().getIpListFilePath() +
					ipvcore::generic::file_system::kDirSep + fileName;

                if (fileDomainType == IMAGE_FILE_FROM_GALLERY || fileDomainType == IMAGE_FILE_FROM_CAMERA || fileDomainType == GIF_FILE) {
					fileDomain = ipvcore::cloud::Domain::CHAT_IMAGE;

					std::string chatImageDownloadPath = ResourceManager::getInstance().getChatImageDownloadPath();

					if (!chatImageDownloadPath.empty()){
						targetPath = chatImageDownloadPath + ipvcore::generic::file_system::kDirSep + fileName;
					}
				}
				else if (fileDomainType == AUDIO_FILE) {
					fileDomain = ipvcore::cloud::Domain::CHAT_AUDIO;

					std::string chatAudioDownloadPath = ResourceManager::getInstance().getChatAudioDownloadPath();

					if (!chatAudioDownloadPath.empty()){
						targetPath = chatAudioDownloadPath + ipvcore::generic::file_system::kDirSep + fileName;
					}
				}
				else if (fileDomainType == VIDEO_FILE) {
					fileDomain = ipvcore::cloud::Domain::CHAT_VIDEO;

					std::string chatVideoDownloadPath = ResourceManager::getInstance().getChatVideoDownloadPath();

					if (!chatVideoDownloadPath.empty()){
						targetPath = chatVideoDownloadPath + ipvcore::generic::file_system::kDirSep + fileName;
					}
				}

				cloudDownloadNotificationHandler->setTargetFilePath(targetPath);

				CloudNotificationManager::getInstance().addCloudNotificationHandler(
					packetId, cloudDownloadNotificationHandler);

				std::shared_ptr< ipvcore::cloud::ChunkedDownloadParams> init_download_params =
					std::make_shared<ipvcore::cloud::ChunkedDownloadParams>();

				init_download_params->download_id = fileName;

				init_download_params->uploader_id = ResourceManager::toLongToString(cloudDownloadNotificationHandler->getFriendId());

				init_download_params->chunk_count = packet->getFileChunkCount();
				init_download_params->chunk_size = packet->getFileChunkSize();
				init_download_params->file_size = packet->getFileSize();
				init_download_params->domain = fileDomain;
				init_download_params->file_path = targetPath;

				std::shared_ptr< ipvcore::cloud::DownloadResponse> downloadResponse =
					ipvcore::cloud::Manager::instance()->init_chunked_download(
					init_download_params, cloudDownloadNotificationHandler);

				if (downloadResponse->success()) {
					Log(module, "Init chunked download successful: " << downloadResponse->message());
				}
				else {
					Log(module, "Init chunked download failed: " << downloadResponse->message());
				}

			}

			auto builtPacket = packetBuilder->makeGroupFileChunkConfirmationPacket(
				ResourceManager::getInstance().getUserId(), groupId, packetId);

			if (!builtPacket.byteArray)
			{
				Log(module, "Packet builder error");
				break;
			}

			auto groupConnection = ResourceManager::getInstance().getGroupConnection(groupId);
			if (!groupConnection)
			{
				Log(module, "Connection not found for group id: " << groupId);
				break;
			}

			auto sendCode = groupConnection->sendToChatServer(builtPacket.byteArray);

			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);

			break;
		}

		case GROUP_FILE_CHUNK_UPLOADED:
		case FRIEND_FILE_CHUNK_UPLOADED:
		{
			int packetType = packet->getPacketType();

			UserIdentity userId;
			UserIdentity friendId;
			GroupIdentity groupId;

			if (packetType == FRIEND_FILE_CHUNK_UPLOADED){
				userId = packet->getFriendIdentity();
				friendId = packet->getUserIdentity();
			}
			else if (packetType == GROUP_FILE_CHUNK_UPLOADED){
				groupId = packet->getGroupId();
			}

			std::string chunkPacketId = packet->getPacketID();

			std::size_t found = chunkPacketId.find_last_of("_");
			std::string originalPacketId = chunkPacketId.substr(0, found);

			bool isManifest = packet->isFileManifest();
			std::string fileName = packet->getFileDownloadId(); // fileName

			auto cloudDownloadNotificationHandler = std::static_pointer_cast<CloudDownloadNotificationHandler>(
				CloudNotificationManager::getInstance().getCloudNotificationHandler(originalPacketId));

			bool downloadAllowed = ResourceManager::getInstance().isAutoDownloadEnabled();

			if (cloudDownloadNotificationHandler){
				cloudDownloadNotificationHandler->setChunkPacketReceived(true);
			}

			if (cloudDownloadNotificationHandler && !downloadAllowed) {
				downloadAllowed = cloudDownloadNotificationHandler->isDownloadAllowed();
			}

			if (cloudDownloadNotificationHandler && downloadAllowed) {

				int fileDomainType = cloudDownloadNotificationHandler->getFileDomainType();
				ipvcore::cloud::Domain fileDomain;

                if (fileDomainType == IMAGE_FILE_FROM_GALLERY || fileDomainType == IMAGE_FILE_FROM_CAMERA || fileDomainType == GIF_FILE) {
					fileDomain = ipvcore::cloud::Domain::CHAT_IMAGE;
				}
				else if (fileDomainType == AUDIO_FILE){
					fileDomain = ipvcore::cloud::Domain::CHAT_AUDIO;
				}
				else if (fileDomainType == VIDEO_FILE){
					fileDomain = ipvcore::cloud::Domain::CHAT_VIDEO;
				}

				std::shared_ptr< ipvcore::cloud::ChunkedDownloadParams> download_params =
					std::make_shared<ipvcore::cloud::ChunkedDownloadParams>();

				download_params->domain = fileDomain;
				download_params->download_id = fileName;
				download_params->key = packet->getFileChunkDownloadKey();
				download_params->file_path = cloudDownloadNotificationHandler->getTargetFilePath();
				download_params->strategy = isManifest ? ipvcore::cloud::Strategy::MANIFEST :
					ipvcore::cloud::Strategy::CHUNKED;

				std::shared_ptr< ipvcore::cloud::DownloadResponse> download_response =
					ipvcore::cloud::Manager::instance()->download(download_params, cloudDownloadNotificationHandler);
			}
			else
			{
				Log(module, "Download not allowed for fileName: " << fileName);
			}

			if (isManifest && !downloadAllowed) {
				CloudNotificationManager::getInstance().removeCloudNotificationHandler(originalPacketId);
			}
			if (packetType == FRIEND_FILE_CHUNK_UPLOADED){
				auto builtPacket = packetBuilder->makeFriendFileChunkConfirmationPacket(
					userId, friendId, chunkPacketId);

				if (!builtPacket.byteArray)
				{
					Log(module, "Packet builder error");
					break;
				}

				auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
				if (!friendInfo)
				{
					Log(module, "Connection not found");
					break;
				}

				auto connection = friendInfo->getConnection();
				auto sendCode = connection->sendToChatServer(builtPacket.byteArray);

				if (sendCode < 0)
				{
					Log(module, "Socket returned " << sendCode);
				}

				KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId);
			}
			else if (packetType == GROUP_FILE_CHUNK_UPLOADED){
				auto builtPacket = packetBuilder->makeGroupFileChunkConfirmationPacket(
					ResourceManager::getInstance().getUserId(), groupId, chunkPacketId);

				if (!builtPacket.byteArray)
				{
					Log(module, "Packet builder error");
					break;
				}

				auto groupConnection = ResourceManager::getInstance().getGroupConnection(groupId);
				if (!groupConnection)
				{
					Log(module, "Connection not found for group id: " << groupId);
					break;
				}

				auto sendCode = groupConnection->sendToChatServer(builtPacket.byteArray);

				if (sendCode < 0)
				{
					Log(module, "Socket returned " << sendCode);
				}

				KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);
			}

			break;
		}

		case FRIEND_CHAT_MEDIA_TRANSFER_CANCEL:
		{
			std::string packetId = packet->getPacketID();

			Log(module, "Friend chat media transfer cancel received. packetId: " << packetId << " friendId: " << packet->getFriendIdentity());

			auto notificationHandler = CloudNotificationManager::getInstance().getCloudNotificationHandler(packetId);

			if (!notificationHandler) {
				Log(module, "No ongoing friend chat media transfer found with packetId: " << packetId);
				break;
			}
			else {
				auto downloadNotificationHandler = std::static_pointer_cast<CloudDownloadNotificationHandler>(notificationHandler);
				downloadNotificationHandler->setCanceledBy(packet->getUserIdentity());

				ipvcore::cloud::Manager::instance()->cancel(notificationHandler);
				Log(module, "manager::cancel() called from userid: " << packet->getUserIdentity());
			}

			UserIdentity userId = packet->getFriendIdentity();
			UserIdentity friendId = packet->getUserIdentity();
			Log(module, "Sending chat media cancel confirmation to friendId: " << friendId);

			auto builtPacket = packetBuilder->makeFriendFileChunkConfirmationPacket(
				userId, friendId, packetId);

			if (!builtPacket.byteArray)
			{
				Log(module, "Packet builder error");
				break;
			}

			auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
			if (!friendInfo)
			{
				Log(module, "Connection not found");
				break;
			}

			auto connection = friendInfo->getConnection();
			auto sendCode = connection->sendToChatServer(builtPacket.byteArray);

			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}
			else {
				Log(module, "Sending chat media cancel confirmation to friendId: " << friendId << " successful");
			}
			KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId);

			break;
		}

		case GROUP_CHAT_MEDIA_TRANSFER_CANCEL:
		{
			std::string packetId = packet->getPacketID();

			Log(module, "Group chat media transfer cancel received. packetId: " << packetId << " groupId: " << packet->getGroupId());

			auto notificationHandler = CloudNotificationManager::getInstance().getCloudNotificationHandler(packetId);

			if (!notificationHandler) {
				Log(module, "No ongoing group chat media transfer found with packetId: " << packetId);
				break;
			}
			else {
				auto downloadNotificationHandler = std::static_pointer_cast<CloudDownloadNotificationHandler>(notificationHandler);
				downloadNotificationHandler->setCanceledBy(packet->getUserIdentity());

				ipvcore::cloud::Manager::instance()->cancel(notificationHandler);
				Log(module, "manager::cancel() called for packetId: " << packetId);
			}

			GroupIdentity groupId = packet->getGroupId();

			auto builtPacket = packetBuilder->makeGroupFileChunkConfirmationPacket(
				ResourceManager::getInstance().getUserId(), groupId, packetId);

			if (!builtPacket.byteArray)
			{
				Log(module, "Packet builder error");
				break;
			}

			auto groupConnection = ResourceManager::getInstance().getGroupConnection(groupId);
			if (!groupConnection)
			{
				Log(module, "Connection not found for group id: " << groupId);
				break;
			}

			auto sendCode = groupConnection->sendToChatServer(builtPacket.byteArray);

			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);

			break;
		}

		case GROUP_FILE_CHUNK_CONFIRMATION:
		case FRIEND_FILE_CHUNK_CONFIRMATION:
		{
			std::string packetId = packet->getPacketID();
			ResendProcessor::getInstance().removePacket(packetId);

			break;
		}

        case SYNC_CONVERSATION_CONFIRMATION:
        {
            auto packetID = packet->getPacketID();
            auto resendPacketTodel = ResendProcessor::getInstance().getPacketDTO(packetID);
            if (resendPacketTodel)
            {
                ResendProcessor::getInstance().removePacket(packet->getPacketID());

                long long serverTime = packet->getServerDate();
                long long timeDifference = serverTime - ResourceManager::getInstance().gettime();
                ResourceManager::getInstance().setTimeDifference(timeDifference);
            }

            packet->setRequestStatus(true);
            EventProcessor::getInstance().push(ChatEvent(ChatEvent::SYNC_CONVERSATION_CONFIRMATION_RECEIVED, packet));
            break;
        }

        case SYNC_CONVERSATION_LIST:
        {
            std::string packetId = packet->getPacketID();

            Log(module, "SYNC_CONVERSATION_LIST received; packetId: " << packetId);

            std::vector<SDKMessageDTO> friendChatMessageList;
            std::vector<SDKMessageDTO> groupChatMessageList;
            auto builtPacket = packetBuilder->makeGetSyncConversationStatus(packet->getUserIdentity(), packetId);
            
            if (!builtPacket.byteArray)
            {
                Log(module, "Packet builder error");
                break;
            }

            auto connection = ResourceManager::getInstance().getOfflineConnection();

            auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);

            if (sendCode < 0)
            {
                Log(module, "Socket returned " << sendCode);
            }

            std::vector<std::shared_ptr< PacketDTO>> messageList = packet->getMessageList();


            if (messageList.size() == 0)
            {
                packet->setIsFromSynced(true);
                EventProcessor::getInstance().push(ChatEvent(ChatEvent::CONVERSATION_LIST_RECEIVE_COMPLETED, packet));
                break;
            }

            for (auto message : messageList)
            {
                SDKMessageDTO messageDTO;

                messageDTO.setSenderId(message->getUserIdentity());
                messageDTO.setPacketId(message->getPacketID());
                messageDTO.setMessageType(message->getMessageType());
                messageDTO.setMessage(message->getMessage());
                messageDTO.setMessageDate(message->getMessageDate());
                messageDTO.setUnreadCount(message->getUnreadCount());
                messageDTO.setTimeOut(message->getTimeout());

                if (message->getPacketType() == FRIEND_CHAT_MESSAGE)
                {
                    messageDTO.setReceiverId(message->getFriendOrGroupId());
                    friendChatMessageList.push_back(messageDTO);
                }
                else if (message->getPacketType() == GROUP_CHAT_MESSAGE)
                {
                    messageDTO.setGroupId(message->getFriendOrGroupId());
                    groupChatMessageList.push_back(messageDTO);
                }
            }

            if (!friendChatMessageList.empty()){
                std::shared_ptr< PacketDTO> friendChatPacket = std::make_shared<PacketDTO>();
                friendChatPacket->setUserIdentity(packet->getUserIdentity());
                friendChatPacket->setPacketID(packetId);
                friendChatPacket->setChatMessageList(friendChatMessageList);
                friendChatPacket->setIsFromSynced(true);
                EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CONVERSATION_LIST_RECEIVED, friendChatPacket));
            }

            if (!groupChatMessageList.empty()){
                std::shared_ptr< PacketDTO> groupChatPacket = std::make_shared<PacketDTO>();
                groupChatPacket->setPacketID(packetId);
                groupChatPacket->setChatMessageList(groupChatMessageList);
                groupChatPacket->setIsFromSynced(true);
                EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CONVERSATION_LIST_RECEIVED, groupChatPacket));
            }

            break;
        }

        case SYNC_FRIEND_HISTORY_MESSAGE_CONFIRMATION:
        {
            std::string packetId = packet->getPacketID();
            auto resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
            if (resendPacket)
            {
                int upDownStatus = resendPacket->getUpDownStatus();
                packet->setUpDownStatus(upDownStatus);
                packet->setRequestStatus(true);
                EventProcessor::getInstance().push(ChatEvent(ChatEvent::SYNC_FRIEND_HISTORY_MESSAGE_CONFIRMATION_RECEIVED, packet));

                ResendProcessor::getInstance().removePacket(packetId);
            }
            break;
        }

        case SYNC_FRIEND_HISTORY_MESSAGE:
        {
            if (packet->getMessageList().size() > 0)
            {
                long long oldestMessageTime = 0;

                auto innerPacketList = packet->getMessageList();
                for (size_t i = 0; i < innerPacketList.size(); i++)
                {
                    if (oldestMessageTime == 0 || innerPacketList[i]->getMessageDate() < oldestMessageTime)
                        oldestMessageTime = innerPacketList[i]->getMessageDate();
                }

                packet->setOldestMessageTime(oldestMessageTime);
                createSDKMessageDTOListFromPacket(packet, false);
                EventProcessor::getInstance().push(ChatEvent(ChatEvent::SYNC_FRIEND_HISTORY_MESSAGE_RECEIVED, packet));
            }
            else
            {
                EventProcessor::getInstance().push(ChatEvent(ChatEvent::SYNC_FRIEND_HISTORY_MESSAGE_RECEIVE_COMPLETED, packet));
            }
            break;
        }

        case SYNC_GROUP_HISTORY_MESSAGE_CONFIRMATION:
        {
            std::string packetId = packet->getPacketID();
            auto resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
            if (resendPacket)
            {
                int upDownStatus = resendPacket->getUpDownStatus();
                packet->setUpDownStatus(upDownStatus);
                packet->setRequestStatus(true);
                EventProcessor::getInstance().push(ChatEvent(ChatEvent::SYNC_GROUP_HISTORY_MESSAGE_CONFIRMATION_RECEIVED, packet));
                ResendProcessor::getInstance().removePacket(packetId);
            }
            break;
        }

        case SYNC_GROUP_HISTORY_MESSAGE:
        {
            if (packet->getMessageList().size() > 0)
            {
                std::vector<std::shared_ptr<PacketDTO>> messageList;
                std::vector<GroupActivityDTO> activityList;

                long long oldestMessageTime = 0;

                auto innerPacketList = packet->getMessageList();
                for (size_t i = 0; i < innerPacketList.size(); i++)
                {
                    std::string encryptedMessage = innerPacketList[i]->getMessage();
                    ByteArray encryptedMessageBytes(encryptedMessage);
                    ByteArray decryptedMessageBytes = ipvsdk::security::DataEncryption::decryptMessage(encryptedMessageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
                    innerPacketList[i]->setMessage(decryptedMessageBytes.getString(0, decryptedMessageBytes.size()));

                    if (oldestMessageTime == 0 || innerPacketList[i]->getMessageDate() < oldestMessageTime)
                        oldestMessageTime = innerPacketList[i]->getMessageDate();

                    if (innerPacketList[i]->getMessageType() == MessageType::GROUP_ACTIVITY)
                    {
                        activityList.push_back(parser.parseGroupActivity(innerPacketList[i]));
                    }
                    else
                    {
                        messageList.push_back(innerPacketList[i]);
                    }
                }

                Log(module, "Number of message: " << messageList.size() << " ;Number of activity: " << activityList.size() << " ;upDownStatus: " << packet->getUpDownStatus());

                auto sdkMessagDTOList = generateSDKMessageDTOListForGroupFromPacket(messageList);
                packet->setChatMessageList(sdkMessagDTOList);
                packet->setGroupActivities(activityList);
                packet->setOldestMessageTime(oldestMessageTime);

                EventProcessor::getInstance().push(ChatEvent(ChatEvent::SYNC_GROUP_HISTORY_MESSAGE_RECEIVED, packet));
            }
            else
            {
                Log(module, "No more synced history for group " << packet->getGroupId());
                EventProcessor::getInstance().push(ChatEvent(ChatEvent::SYNC_GROUP_HISTORY_MESSAGE_RECEIVE_COMPLETED, packet));
            }
            break;
        }
                
        case ADD_NOTICE_CONFIRMATION:
        {
            std::string packetId = packet->getPacketID();
            auto resendPacket = ResendProcessor::getInstance().getPacketDTO(packetId);
            if (resendPacket)
            {
                packet->setRequestStatus(true);
                EventProcessor::getInstance().push(ChatEvent(ChatEvent::ADD_NOTICE_STATUS, packet));
                ResendProcessor::getInstance().removePacket(packetId);
            }
            break;
        }
	}
}

	void PacketProcessor::clear()
	{
		Processor::clear();
		brokenPacketMap.clear();
		brokenGroupPacketMap.clear();
		brokenPublicChatPacketMap.clear();
		brokenData.clear();
		offlinePacketIdMap.clear();
		duplicateChecker.clear();
	}

	void PacketProcessor::run()
	{
		processPacketProcessTasks();
	}
}
