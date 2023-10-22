/*
* File:   Chat.cpp
* Author: dipal
*
* Created on August 17, 2015, 11:55 AM
*/


#include "Chat.h"
#include "Connection.h"
#include "EventProcessor.h"
#include "KeepaliveProcessor.h"
#include "PacketProcessor.h"
#include "ResendProcessor.h"
#include "ResourceManager.h"
#include "PacketReceiver.h"
#include "Logger.h"
//#include "FileSDKHandler.h"
#include "UnifiedProcessor.h"
#include "PacketTimeId.h"
#include "CloudNotificationHandler.h"
#include "DataEncryption.h"
#include <cstdlib>
#include <math.h>
#include "cloud/manager.h"
#include "InternetChecker.h"
#include <mutex>

#define CHAT_MESSAGE_MAX_SIZE               960//512

#define module "Chat"

namespace imsdk {
    std::mutex ResourceManager::startServicesMutex;

#define MASTER_THREAD

	Chat::Chat(UserIdentity userId, std::string userName, std::string offlineServerAddress, int offlineServerPort,
		std::string authenticationServerAddress, int authenticationServerPort, int deviceType,
		std::string appSessionId, int appVersion, long long timeDifference, std::vector<std::string> &directoryPaths,
		std::string baseUploadUrl, std::string baseDownloadUrl, bool autoDownloadEnabled, std::string key, int appType, std::set<UserIdentity> pageIdList)
	{
		if (key.empty())
		{
			auto eventPacketDTO = std::make_shared<PacketDTO>();
			eventPacketDTO->setPacketID(generatePacketId().packetId);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_PASSWORD, eventPacketDTO));
		}

        std::string logPath = "";

        #ifdef IMSDK_LOG
        #ifdef __ANDROID__
            logPath ="/sdcard/imsdk.log";
        #else
            //logPath = (directoryPaths.size() > 0 && !directoryPaths[0].empty()) ? (directoryPaths[0] + PATH_SEPARATOR + "imsdk.log") : "imsdk.log";
            std::string logFileName = "imsdk-" + std::to_string(userId) + "_" + std::to_string(deviceType) + ".log";
            logPath = (directoryPaths.size() > 0 && !directoryPaths[0].empty()) ? (directoryPaths[0] + PATH_SEPARATOR + logFileName) : logFileName;
        #endif
            Logger::getInstance().init(logPath);
        #endif

		Log(module, "imsdk initialized");
		Log(module, "Version: " << version());
		Log(module, "OS: " << Logger::getOs());
		Log(module, "Self userId: " << userId << " ;userName: " << userName << " ;offlineServerIP: " << offlineServerAddress << " ;offlineServerPort: " << offlineServerPort);
		Log(module, "SessionID: " << appSessionId << "; authServerIP: " << authenticationServerAddress << "; authServerPort: " << authenticationServerPort);
		Log(module, "KEY SHA1: " << key);

		//    char* curlVersion = curl_version();
		//    Log(module, "Curl Version: " << curlVersion);

		//    ResourceManager::getInstance().m_pFileTransferSDK = new CIPVConnectivityDLL();
		//    
		//    bool bInit = ResourceManager::getInstance().m_pFileTransferSDK->Init(userId, "FileTransferSDK.log", 5);
		//      
		//    ResourceManager::getInstance().m_pFileTransferSDK->SetNotifierForFileTransfer(&notifierForFileTransfer);

        ResourceManager::getInstance().setAuthSessionID(appSessionId);
        ResourceManager::getInstance().setOfflineServer(offlineServerAddress, offlineServerPort);
		ResourceManager::getInstance().setAuthenticationServer(authenticationServerAddress, authenticationServerPort);
		ResourceManager::getInstance().setTimeDifference(timeDifference);
		ResourceManager::getInstance().setUserId(userId);
		ResourceManager::getInstance().setUserPageIdList(pageIdList);
		ResourceManager::getInstance().setUserName(userName);
		ResourceManager::getInstance().setDeviceType(deviceType);
		ResourceManager::getInstance().setEncryptionDecryptionKey(std::make_shared<ByteArray>(key));
		ResourceManager::getInstance().setAppType(appType);

		//    ResourceManager::getInstance().m_pFileTransferSDK->SetAuthenticationServer(authenticationServerAddress, authenticationServerPort, appSessionId);

		if (directoryPaths.size() >= 8)
		{
			ipvcore::cloud::Manager::instance()->init(baseUploadUrl, baseDownloadUrl, appSessionId,
				ResourceManager::getInstance().toLongToString(userId), authenticationServerAddress,
				ResourceManager::getInstance().toString(authenticationServerPort),
				ResourceManager::getInstance().toString(appVersion), directoryPaths[1]);

			ResourceManager::getInstance().setMediaTransferTmpDirPath(directoryPaths[1]);
			ResourceManager::getInstance().setChatImageDownloadPath(directoryPaths[2]);
			ResourceManager::getInstance().setChatAudioDownloadPath(directoryPaths[3]);
			ResourceManager::getInstance().setChatVideoDownloadPath(directoryPaths[4]);
			ResourceManager::getInstance().setSecretChatImageDownloadPath(directoryPaths[5]);
			ResourceManager::getInstance().setSecretChatAudioDownloadPath(directoryPaths[6]);
			ResourceManager::getInstance().setSecretChatVideoDownloadPath(directoryPaths[7]);
		}
		else
		{
			Log(module, "Missing chat media download directory paths !");
		}

		ResourceManager::getInstance().appVersion = SDK_VERSION;

		ResourceManager::getInstance().setAutoDownloadEnabled(autoDownloadEnabled);
		ResourceManager::getInstance().setBaseUploadUrl(baseUploadUrl);
		ResourceManager::getInstance().setBaseDownloadUrl(baseDownloadUrl);



		packetBuilder = std::make_shared<ChatPacketBuilder>();
		srand(time(0));

		//start services
		startServices();
	}

	Chat::~Chat() {
		//stop services
		stopServices();
	}

	void Chat::reinitialize(UserIdentity userId, std::string userName, std::string offlineServerAddress,
		int offlineServerPort, std::string authenticationServerAddress, int authenticationServerPort,
		int deviceType, std::string appSessionId, int appVersion, long long timeDifference,
		std::vector<std::string> &directoryPaths, bool autoDownloadEnabled, std::string key, std::set<UserIdentity> pageIdList)
	{
		if (key.empty())
		{
			auto eventPacketDTO = std::make_shared<PacketDTO>();
			eventPacketDTO->setPacketID(generatePacketId().packetId);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_PASSWORD, eventPacketDTO));
			key = "wrong password";
		}

		Log(module, "imsdk re-initialized");
		Log(module, "Self userId: " << userId << " ;userName: " << userName << " ;offlineServerIP: " << offlineServerAddress << " ;offlineServerPort: " << offlineServerPort);

        ResourceManager::getInstance().setAuthSessionID(appSessionId);
        ResourceManager::getInstance().setOfflineServer(offlineServerAddress, offlineServerPort);
		ResourceManager::getInstance().createSocketIfNeeded();
		ResourceManager::getInstance().createOfflineConnectionIfNeeded();
		ResourceManager::getInstance().setAuthenticationServer(authenticationServerAddress, authenticationServerPort);
		ResourceManager::getInstance().setTimeDifference(timeDifference);
		ResourceManager::getInstance().setUserId(userId);
		ResourceManager::getInstance().setUserPageIdList(pageIdList);
		ResourceManager::getInstance().setUserName(userName);
		ResourceManager::getInstance().setDeviceType(deviceType);
		ResourceManager::getInstance().setEncryptionDecryptionKey(std::make_shared<ByteArray>(key));

		//    ResourceManager::getInstance().m_pFileTransferSDK->SetAuthenticationServer(authenticationServerAddress, authenticationServerPort, appSessionId);

		ResourceManager::getInstance().appVersion = SDK_VERSION;
		ResourceManager::getInstance().setAutoDownloadEnabled(autoDownloadEnabled);

		ipvcore::cloud::Manager::instance()->init(ResourceManager::getInstance().getBaseUploadUrl(),
			ResourceManager::getInstance().getBaseDownloadUrl(), appSessionId,
			ResourceManager::getInstance().toLongToString(userId), authenticationServerAddress,
			ResourceManager::getInstance().toString(authenticationServerPort),
			ResourceManager::getInstance().toString(appVersion), directoryPaths[1]);

		srand(time(0));

		//start services
		startServices();
	}

	void Chat::startServices()
	{
        std::lock_guard<std::mutex> lock(ResourceManager::startServicesMutex);

		if (!ResourceManager::getInstance().getIsRunningServices())
		{
			Log(module, "Starting services ...");

			ResourceManager::getInstance().createSocketIfNeeded();
			ResourceManager::getInstance().createOfflineConnectionIfNeeded();

			PacketReceiver::getInstance().start();
			EventProcessor::getInstance().start();

#ifdef MASTER_THREAD
			UnifiedProcessor::getInstance().start();
#else
			KeepaliveProcessor::getInstance().start();
			PacketProcessor::getInstance().start();
			ResendProcessor::getInstance().start();
#endif

			//detach services to run independently
			PacketReceiver::getInstance().detach();
			EventProcessor::getInstance().detach();

#ifdef MASTER_THREAD
			UnifiedProcessor::getInstance().detach();
#else
			KeepaliveProcessor::getInstance().detach();
			PacketProcessor::getInstance().detach();
			ResendProcessor::getInstance().detach();
#endif

			ResourceManager::getInstance().setIsRunningServices(true);

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::EVENT_HANDLER_ATTACHED, nullptr), Priority::l5);
		}
	}

	void Chat::stopServices()
	{
        std::lock_guard<std::mutex> lock(ResourceManager::startServicesMutex);

        if (ResourceManager::getInstance().getIsRunningServices())
		{

			PacketReceiver::getInstance().stop();
			EventProcessor::getInstance().stop();

#ifdef MASTER_THREAD
			UnifiedProcessor::getInstance().stop();
#else
			KeepaliveProcessor::getInstance().stop();
			PacketProcessor::getInstance().stop();
			ResendProcessor::getInstance().stop();
#endif

			ResourceManager::getInstance().setIsRunningServices(false);
		}
    }
	bool Chat::checkInternetConnection() {

		Log(module, "Checking Internet connection ...(ignoring. should use internet check module)");
		return false; // should use internet check module
	}

	void Chat::setOfflineServer(std::string offlineServerAddress, int offlineServerPort)
	{
		ResourceManager::getInstance().setOfflineServer(offlineServerAddress, offlineServerPort);
		ResendProcessor::getInstance().updateOfflineServer(offlineServerAddress, offlineServerPort);
	}

	void Chat::setAuthenticationServer(std::string authenticationServerAddress, int authenticationServerPort)
	{
		ResourceManager::getInstance().setAuthenticationServer(authenticationServerAddress, authenticationServerPort);
	}

	ApiStatus Chat::requestForOffline(long long groupUpdateDate, long long blockUpdateDate)
	{
        std::stringstream hash;
        hash << "REQUEST_FOR_OFFLINE" << ResourceManager::getInstance().getUserId();

        if (requestDuplicateChecker.isSafe(hash.str(), 30))
        {
            startServices();
            Log(module, "Offline server request ");
            auto packetTimeId = generatePacketId();

            std::set<UserIdentity> pageIdList = ResourceManager::getInstance().getUserPageIdList();
            auto connection = ResourceManager::getInstance().getOfflineConnection();

            BuiltPacket builtPacket = packetBuilder->makeOfflineGetRequest(ResourceManager::getInstance().getUserId(), packetTimeId.packetId, groupUpdateDate, blockUpdateDate, ResourceManager::getInstance().appVersion, ResourceManager::getInstance().getDeviceType(), ResourceManager::getInstance().getAppType(), pageIdList);
            if (!builtPacket.byteArray)
            {
                Log(module, "Packet builder error");
                return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
            }

            auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);

            if (sendCode < 0)
            {
                Log(module, "Socket returned " << sendCode);
            }

            Log(module, "Adding " << packetTimeId.packetId << " for resend");
            ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Offline));

            return{ packetTimeId.packetId };
        }

        Log(module, "A requestForOffline request is already in process");
        return {""};
	}

    ApiStatus Chat::registerFriendChat(UserIdentity userId, std::string userName, UserIdentity friendId, std::string friendName, std::string friendUrl, std::string registerServerAddress, int registerServerPort, int deviceType, std::string deviceToken, int appType, int status, int mood, int iosVoipPush, long long authRegistrationTime, int profileType)
	{
		Log(module, "====>> Registering friend chat for userId: " << userId << " userName: " << userName << " with " << friendId << " friendName = " << friendName << "friendUrl = " << friendUrl << " Chat server = " << registerServerAddress << ":" << registerServerPort << " status = " << status << " mood = " << mood << " deviceType = " << deviceType << " appType = " << appType);
		auto packetTimeId = generatePacketId();

		startServices();

		if (status != OnlineStatus::ONLINE)
		{//If status not online then send friend Info to offline server
			Log(module, "Friend status is not online. Sending friend information");

			auto connection = ResourceManager::getInstance().getOfflineConnection();

			ResendProcessor::getInstance().updateConnection(userId, friendId, connection);  //set offline server connection for friendId
			ResendProcessor::getInstance().updatedServerAddress(userId, friendId); //reset flags to send pending messages
            ResourceManager::getInstance().addFriendInfo(std::make_shared<FriendInfo>(userId, userName, friendId, friendName, friendUrl, connection, deviceType, deviceToken, appType, status, mood, iosVoipPush, false, ResourceManager::getInstance().getServerSyncedTime(), authRegistrationTime, profileType));

			Log(module, "====>> Sending friend information fid:" << friendId << " status:" << status << " apptype:" << appType);

            auto ownProfileType = ResourceManager::getInstance().isUserPage(userId) ? UserProfileType::PAGE : UserProfileType::DEFAULT;

			auto builtPacket = packetBuilder->makeOfflineFriendInformation(userId, friendId, packetTimeId.packetId, userName, deviceType, status, appType, deviceToken, mood, iosVoipPush, ResourceManager::getInstance().getDeviceType(), ownProfileType, profileType);
			if (!builtPacket.byteArray)
			{
				Log(module, "Friend info packet builder error");
				return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
			}

			auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);
			if (sendCode < 0)
			{
				Log(module, "Friend info sending socket returned " << sendCode);
			}
			Log(module, "Friend " << friendId << " is not online. will be sent to offline");
			ResendProcessor::getInstance().updatePendingDestination(userId, friendId, status);

			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Offline));

			auto blankMessagePacketId = generatePacketId();
			long long messageDate = ResourceManager::getInstance().gettime() - ResourceManager::getInstance().getTimeDifference();
			//        long long messageDate = ResourceManager::getInstance().gettime();
			std::string message = "";
			auto builtBlankMessagePacket = packetBuilder->makeFriendChatMessage(userId, friendId, blankMessagePacketId.packetId, MessageType::BLANK_MESSAGE, 0, message, messageDate, false, ResourceManager::getInstance().getDeviceType(), ResourceManager::getInstance().appVersion, ResourceManager::getInstance().getAppType(), ResourceManager::getInstance().getUserId());

			if (!builtBlankMessagePacket.byteArray)
			{
				Log(module, "blank message packet builder error");
				return{ blankMessagePacketId.packetId, ChatError::PACKET_BUILDER_ERROR };
			}

			sendCode = connection->sendToOfflineServer(builtBlankMessagePacket.byteArray);
			if (sendCode < 0)
			{
				Log(module, "Friend blank message sending socket returned " << sendCode);
			}

			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(blankMessagePacketId.packetId, builtBlankMessagePacket.byteArray, builtBlankMessagePacket.packet, connection, ResendProcessor::DestinationType::Offline));
			BuiltPacket keepalivePacket = packetBuilder->makeFriendChatIdel(userId, friendId, ResourceManager::getInstance().getDeviceType());
			if (keepalivePacket.byteArray)
			{
				KeepaliveProcessor::getInstance().addFriendKeepalivePacket(userId, friendId, static_cast<OnlineStatus>(status), std::make_shared<KeepalivePacket>(connection, keepalivePacket.byteArray));
			}
			return{ packetTimeId.packetId };
		}
		else
		{
			auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
			if (friendInfo && authRegistrationTime < friendInfo->getAuthRegisterTime())
			{
                Log(module, "Ignoring register for older register time. tm: " << authRegistrationTime << " existing register time: " << friendInfo->getAuthRegisterTime());
				return{ packetTimeId.packetId };
			}

			auto connection = std::make_shared<ChatConnection>(ResourceManager::getInstance().getSocket());
			connection->setRegisterServer(registerServerAddress, registerServerPort);

			ResendProcessor::getInstance().updateConnection(userId, friendId, connection);  //set offline server connection for friendId
            ResourceManager::getInstance().addFriendInfo(std::make_shared<FriendInfo>(userId, userName, friendId, friendName, friendUrl, connection, deviceType, deviceToken, appType, status, mood, iosVoipPush, false, ResourceManager::getInstance().getServerSyncedTime(), authRegistrationTime, profileType));

			BuiltPacket builtPacket = packetBuilder->makeFriendRegister(userId, friendId, packetTimeId.packetId, ResourceManager::getInstance().getDeviceType(), ResourceManager::getInstance().appVersion, ResourceManager::getInstance().getAppType(), ResourceManager::getInstance().getUserId());
			if (!builtPacket.byteArray)
			{
				Log(module, "Packet builder error");
				return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
			}

			auto sendCode = connection->sendToRegisterServer(builtPacket.byteArray);
			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetTimeId.packetId << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Register));
			return{ packetTimeId.packetId };
		}
	}

	bool Chat::isExistsFriendConnection(UserIdentity userId, UserIdentity friendId)
	{
		auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
        if (!friendInfo || friendInfo->getIsFriendBlocked())
		{
			return false;
		}

		auto connection = friendInfo->getConnection();

		if (!connection)
		{
			Log(module, "Connection not found");
			return false;
		}

		if (connection->getChatServerStatus() == ChatConnection::NOT_EXISTS)
		{
			return false;
		}

		return true;
	}

	ApiStatus Chat::registerGroupChat(GroupIdentity groupId, std::string registerServerAddress, int registerServerPort, long long authRegistrationTime)
	{

        if (ResourceManager::getInstance().GetGroupRegistrationTime(groupId) > authRegistrationTime)
        {
            Log(module, "Ignoring Registering group chat for " << groupId);
            return {""};
        }

		Log(module, "Registering group chat at " << groupId << " Chat server " << registerServerAddress << ":" << registerServerPort);
        auto packetTimeId = generatePacketId();

		startServices();

        ResourceManager::getInstance().addGroupRegistration(groupId, authRegistrationTime);

		auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
		if (!connection)
		{
			connection = std::make_shared<ChatConnection>(ResourceManager::getInstance().getSocket());
		}

		connection->setRegisterServer(registerServerAddress, registerServerPort);
		ResourceManager::getInstance().addGroupConnection(groupId, connection);

		ResendProcessor::getInstance().updateGroupConnection(groupId, connection);

		BuiltPacket builtPacket = packetBuilder->makeGroupRegister(ResourceManager::getInstance().getUserId(), groupId, packetTimeId.packetId, ResourceManager::getInstance().getDeviceType(), ResourceManager::getInstance().appVersion);
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto sendCode = connection->sendToRegisterServer(builtPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Register));
		return{ packetTimeId.packetId };
	}

	bool Chat::isExistsGroupConnection(GroupIdentity groupId)
	{
		
		auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
		return connection != nullptr;
	}

	ApiStatus Chat::unregisterFriendChat(UserIdentity userId, UserIdentity friendId, int status, int mood)
	{
		startServices();

		Log(module, "Unregistering for userId: " << userId << " friend " << friendId);
		auto packetTimeId = generatePacketId();
		auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
		if (!friendInfo)
		{
			Log(module, "Connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto builtPacket = packetBuilder->makeFriendUnregister(userId, friendId, packetTimeId.packetId, status, mood);
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = friendInfo->getConnection();
		auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_REMOVE_DUPLICATE_INFO_FOR_FRIEND, builtPacket.packet));

		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Register, 3));
		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::unregisterGroupChat(GroupIdentity groupId, int status, int mood)
	{
		startServices();

		Log(module, "Unregistering group " << groupId);
		auto packetTimeId = generatePacketId();
		auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
		if (!connection)
		{
			Log(module, "Connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto builtPacket = packetBuilder->makeGroupUnregister(ResourceManager::getInstance().getUserId(), groupId, packetTimeId.packetId, status, mood);
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

        ResourceManager::getInstance().removeGroupRegistration(groupId);
        ResourceManager::getInstance().removeGroupConnection(groupId);
		KeepaliveProcessor::getInstance().removeGroupKeepalive(groupId);
		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::updateFriendRegisterServer(UserIdentity userId, UserIdentity friendId, std::string registerServerAddress, int registerServerPort)
	{
		startServices();
		auto packetTimeId = generatePacketId();

		auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
		if (!friendInfo) {
			Log(module, "Friend info not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto connection = friendInfo->getConnection();
		connection->setRegisterServer(registerServerAddress, registerServerPort);

		BuiltPacket builtPacket = packetBuilder->makeFriendRegister(userId, friendId, packetTimeId.packetId, friendInfo->getDeviceType(), ResourceManager::getInstance().appVersion, ResourceManager::getInstance().getAppType(), ResourceManager::getInstance().getUserId());
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto sendCode = connection->sendToRegisterServer(builtPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Register));
		KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId);
		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::updateFriendStatusAndMood(UserIdentity userId, UserIdentity friendId, int status, int mood)
	{
		Log(module, "updateFriendStatusAndMood userId: " << userId << " friendId: " << friendId << " status:" << status << " mood:" << mood);
		startServices();
		auto packetTimeId = generatePacketId();

		ResendProcessor::getInstance().updatePendingDestination(userId, friendId, status);
		ResourceManager::getInstance().updateFriendInfoStatus(userId, friendId, status);

		auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
		if (!friendInfo) {
			Log(module, "Friend info not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		friendInfo->setStatus(status);
		friendInfo->setMood(mood);

		std::string friendDeviceToken = friendInfo->getDeviceToken();
		std::string userName = ResourceManager::getInstance().getUserName();
		Log(module, "====>> Sending friend information fid:" << friendId << " status:" << status << " apptype:" << friendInfo->getAppType());

        auto ownProfileType = ResourceManager::getInstance().isUserPage(userId) ? UserProfileType::PAGE : UserProfileType::DEFAULT;

        auto builtPacket = packetBuilder->makeOfflineFriendInformation(userId, friendId, packetTimeId.packetId, userName, friendInfo->getDeviceType(), status, friendInfo->getAppType(), friendDeviceToken, mood, friendInfo->getIosVoipPush(), ResourceManager::getInstance().getDeviceType(), ownProfileType, friendInfo->getProfileType());
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getOfflineConnection();

		auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Offline));

		if (status != OnlineStatus::ONLINE && mood != OnlineMood::DONT_DISTRUBE)
		{
			auto blankMessagePacketId = generatePacketId();
			long long messageDate = ResourceManager::getInstance().gettime() - ResourceManager::getInstance().getTimeDifference();
			//    long long messageDate = ResourceManager::getInstance().gettime();

			std::string message = "";
			auto builtBlankMessagePacket = packetBuilder->makeFriendChatMessage(userId, friendId, blankMessagePacketId.packetId, MessageType::BLANK_MESSAGE, 0, message, messageDate, false, ResourceManager::getInstance().getDeviceType(), ResourceManager::getInstance().appVersion, ResourceManager::getInstance().getAppType(), ResourceManager::getInstance().getUserId());

			if (!builtBlankMessagePacket.byteArray)
			{
				Log(module, "blank message packet builder error");
				return{ blankMessagePacketId.packetId, ChatError::PACKET_BUILDER_ERROR };
			}

			sendCode = connection->sendToOfflineServer(builtBlankMessagePacket.byteArray);
			if (sendCode < 0)
			{
				Log(module, "Friend blank message sending socket returned " << sendCode);
			}

			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(blankMessagePacketId.packetId, builtBlankMessagePacket.byteArray, builtBlankMessagePacket.packet, connection, ResendProcessor::DestinationType::Offline));
		}
		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::sendOrEditBrokenFriendChat(int packetType, UserIdentity userId, UserIdentity friendId, std::string &packetId, int totalNumberOfPackets, int chunkNumber, int messageType, int secretTimeout, std::string &message, long long messageDate, bool isSecretVisible)
	{
		Log(module, "Sending friend chat from userId: " << userId << " to " << friendId << " message:" << message);

		ByteArray messageBytes(message);
		ByteArray encryptedMessageBytes = ipvsdk::security::DataEncryption::encryptMessage(messageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
		message = encryptedMessageBytes.getString(0, encryptedMessageBytes.size());

		BuiltPacket friendChatPacket;
		if (packetType == FRIEND_CHAT_MESSAGE_BROKEN)
		{
			friendChatPacket = packetBuilder->makeFriendChatMessageBroken(userId, friendId, packetId, totalNumberOfPackets, chunkNumber, messageType, secretTimeout, message, messageDate, isSecretVisible, ResourceManager::getInstance().getDeviceType(), ResourceManager::getInstance().appVersion, ResourceManager::getInstance().getAppType(), ResourceManager::getInstance().getUserId());
		}
		else if (packetType == FRIEND_CHAT_MESSAGE_BROKEN_EDIT)
		{
			friendChatPacket = packetBuilder->makeFriendChatMessageBrokenEdit(userId, friendId, packetId, totalNumberOfPackets, chunkNumber, messageType, secretTimeout, message, messageDate, isSecretVisible, ResourceManager::getInstance().getDeviceType(), ResourceManager::getInstance().appVersion, ResourceManager::getInstance().getAppType(), ResourceManager::getInstance().getUserId());
		}
		if (!friendChatPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		std::string brokenPacketId;
		brokenPacketId = packetId;
		brokenPacketId += "_";
		brokenPacketId += ResourceManager::toString(chunkNumber);

		auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
		if (!friendInfo)
		{
			Log(module, "Friend info not found. Pushing for pending.");
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_FRIEND, friendChatPacket.packet));

			auto resendPacket = ResendProcessor::ResendPacket(brokenPacketId, friendChatPacket.byteArray, friendChatPacket.packet, nullptr, ResendProcessor::Chat, 0);
			resendPacket.isWaitingForServerUpdate = true;
			ResendProcessor::getInstance().addResendPacket(resendPacket);
			return{ packetId };
		}

		ResendProcessor::DestinationType destination;
		int sendCode;

		std::shared_ptr< ChatConnection> connection = nullptr;
		if (friendInfo->getStatus() == OnlineStatus::ONLINE)
		{
			destination = ResendProcessor::DestinationType::Chat;
			connection = friendInfo->getConnection();
			if (connection->getChatServerStatus() != ChatConnection::READY)
			{
				Log(module, "Connection status is not ready.");
				ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(brokenPacketId, friendChatPacket.byteArray, friendChatPacket.packet, connection, ResendProcessor::Chat, 0));
				return{ packetId };
			}
			sendCode = connection->sendToChatServer(friendChatPacket.byteArray);
		}
		else
		{
			destination = ResendProcessor::DestinationType::Offline;
			auto connection = ResourceManager::getInstance().getOfflineConnection();

			sendCode = connection->sendToOfflineServer(friendChatPacket.byteArray);
		}

		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << brokenPacketId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(brokenPacketId, friendChatPacket.byteArray, friendChatPacket.packet, connection, destination));

		return{ packetId };
	}

	ApiStatus Chat::sendGeneralEncryptedInformation(UserIdentity userID, UserIdentity friendID, std::string &packetID, int type, int informationType, std::string &information)
	{
		startServices();
		Log(module, "SendGeneralEncryptedInformation");
		ByteArray informationBytes(information);
		ByteArray encryptedInformationBytes = ipvsdk::security::DataEncryption::encryptMessage(informationBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
		information = encryptedInformationBytes.getString(0, encryptedInformationBytes.size());

		BuiltPacket generalEncryptedPacket = packetBuilder->makeGenerateEncryptedPacketInformation(userID, friendID, packetID, type, informationType, information);

		if (!generalEncryptedPacket.byteArray)
		{
			Log(module, "SendGeneralEncryptedInformation Packet builder error");
			return{ packetID, ChatError::PACKET_BUILDER_ERROR };
		}

		if (type == 1){
			auto friendInfo = ResourceManager::getInstance().getFriendInfo(userID, friendID);
			if (!friendInfo)
			{
				Log(module, "SendGeneralEncryptedInformation Friend info not found. Pushing for pending.");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_FRIEND, generalEncryptedPacket.packet));
				auto resendPacket = ResendProcessor::ResendPacket(packetID, generalEncryptedPacket.byteArray, generalEncryptedPacket.packet, nullptr, ResendProcessor::Chat, 0);
				resendPacket.isWaitingForServerUpdate = true;
				ResendProcessor::getInstance().addResendPacket(resendPacket);
				return{ packetID };
			}

			ResendProcessor::DestinationType destination;
			int sendCode;

			std::shared_ptr< ChatConnection> connection = nullptr;
			if (friendInfo->getStatus() == OnlineStatus::ONLINE)
			{
				destination = ResendProcessor::DestinationType::Chat;
				connection = friendInfo->getConnection();
				if (connection->getChatServerStatus() != ChatConnection::READY)
				{
					Log(module, "SendGeneralEncryptedInformation Connection status is not ready.");
					ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetID, generalEncryptedPacket.byteArray, generalEncryptedPacket.packet, connection, ResendProcessor::Chat, 0));
					return{ packetID };
				}
				sendCode = connection->sendToChatServer(generalEncryptedPacket.byteArray);
			}
			else
			{
				destination = ResendProcessor::DestinationType::Offline;
				connection = ResourceManager::getInstance().getOfflineConnection();
				sendCode = connection->sendToOfflineServer(generalEncryptedPacket.byteArray);
			}

			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetID << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetID, generalEncryptedPacket.byteArray, generalEncryptedPacket.packet, connection, destination, 0));
			KeepaliveProcessor::getInstance().resetFriendKeepalive(userID, friendID);
		}

		if (type == 2){
			auto connection = ResourceManager::getInstance().getGroupConnection(friendID);
			if (!connection)
			{
				Log(module, "Group info not found. Pushing for pending.");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_GROUP, generalEncryptedPacket.packet));
				auto resendPacket = ResendProcessor::ResendPacket(packetID, generalEncryptedPacket.byteArray, generalEncryptedPacket.packet, nullptr, ResendProcessor::Chat, 0);
				resendPacket.isWaitingForServerUpdate = true;
				ResendProcessor::getInstance().addResendPacket(resendPacket);
				return{ packetID };
			}

			auto sendCode = connection->sendToChatServer(generalEncryptedPacket.byteArray);
			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetID << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetID, generalEncryptedPacket.byteArray, generalEncryptedPacket.packet, connection, ResendProcessor::Chat));
		
			KeepaliveProcessor::getInstance().resetGroupKeepalive(friendID);
		}

		return{ packetID };
	}

	ApiStatus Chat::sendFriendChat(std::string &packetId, UserIdentity userId, UserIdentity friendId, int messageType, int secretTimeout, std::string &message, long long messageDate, bool isSecretVisible)
	{
		Log(module, "Sending friend chat from userId: " << userId << " to " << friendId << " message:" << message << " messageType " << messageType << " packetId " << packetId);

		startServices();

		bool keyValid = isExistsValidKey(packetId, friendId);
		if (!keyValid) {
			Log(module, "Error! Invalid key");
			return{ packetId, ChatError::FAILED_TO_SEND };
		}

		size_t fixedLength = LEN_PACKET_TYPE + LEN_USER_IDENTITY + LEN_FRIEND_IDENTITY + LEN_PACKETID_LENGTH + (int)packetId.length() + LEN_MESSAGE_TYPE + LEN_TIMEOUT + LEN_MESSAGE_LENGTH + LEN_MESSAGE_DATE + LEN_IS_SECRET_VISIBLE + LEN_PLATFORM + LEN_APP_VERSION + LEN_FRIEND_APP_TYPE + LEN_USER_IDENTITY;
		size_t availableMsgLength = CHAT_MESSAGE_MAX_SIZE - fixedLength;

		int numberOfBrokenChatMessage;
		int startIndex = 0;
		std::string brokenMessage;

		time_t myTime = (time_t)(messageDate / 1000);
		Log(module, "Sending friend chat message date before calling time difference  " << ctime(&myTime));

		if (message.length() > availableMsgLength) {

			numberOfBrokenChatMessage = ceil(((double)message.length() / (double)availableMsgLength));

			for (int chunkNumber = 0; chunkNumber < numberOfBrokenChatMessage; chunkNumber++)
			{
				brokenMessage = message.substr(startIndex, availableMsgLength);
				startIndex = startIndex + availableMsgLength;

				sendOrEditBrokenFriendChat(FRIEND_CHAT_MESSAGE_BROKEN, userId, friendId, packetId, numberOfBrokenChatMessage, chunkNumber, messageType, secretTimeout, brokenMessage, messageDate, isSecretVisible);

			}
		}
		else
		{
			ByteArray messageBytes(message);
			ByteArray encryptedMessageBytes = ipvsdk::security::DataEncryption::encryptMessage(messageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
			message = encryptedMessageBytes.getString(0, encryptedMessageBytes.size());

			BuiltPacket friendChatPacket = packetBuilder->makeFriendChatMessage(userId, friendId, packetId, messageType, secretTimeout, message, messageDate, isSecretVisible, ResourceManager::getInstance().getDeviceType(), ResourceManager::getInstance().appVersion, ResourceManager::getInstance().getAppType(), ResourceManager::getInstance().getUserId());
			if (!friendChatPacket.byteArray)
			{
				Log(module, "Packet builder error");
				return{ packetId, ChatError::PACKET_BUILDER_ERROR };
			}

			auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
			if (!friendInfo)
			{
				Log(module, "Friend info not found. Pushing for pending.");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_FRIEND, friendChatPacket.packet));
				auto resendPacket = ResendProcessor::ResendPacket(packetId, friendChatPacket.byteArray, friendChatPacket.packet, nullptr, ResendProcessor::Chat, 0);
				resendPacket.isWaitingForServerUpdate = true;
				ResendProcessor::getInstance().addResendPacket(resendPacket);
				return{ packetId };
			}

			ResendProcessor::DestinationType destination;
			int sendCode;

			std::shared_ptr< ChatConnection> connection = nullptr;
			if (friendInfo->getStatus() == OnlineStatus::ONLINE)
			{
				destination = ResendProcessor::DestinationType::Chat;
				connection = friendInfo->getConnection();
				if (connection->getChatServerStatus() != ChatConnection::READY)
				{
					Log(module, "Connection status is not ready.");
					ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, friendChatPacket.byteArray, friendChatPacket.packet, connection, ResendProcessor::Chat, 0));
					return{ packetId };
				}
				sendCode = connection->sendToChatServer(friendChatPacket.byteArray);
			}
			else
			{
				destination = ResendProcessor::DestinationType::Offline;
				connection = ResourceManager::getInstance().getOfflineConnection();
				sendCode = connection->sendToOfflineServer(friendChatPacket.byteArray);
			}

			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetId << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, friendChatPacket.byteArray, friendChatPacket.packet, connection, destination, 0));

		}

		KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId);
		return{ packetId };
	}

	ApiStatus Chat::dontSendPendingMessages(UserIdentity userId, UserIdentity friendId)
	{
		startServices();
		ResendProcessor::getInstance().expirePendingMessagesForFriend(userId, friendId);
		return{ "" };
	}

	ApiStatus Chat::sendFriendCallBusyMessage(UserIdentity userId, UserIdentity friendId, std::string &message, long long messageDate, std::string &packetId)
	{
		Log(module, "Sending friend chat from " << userId << " to " << friendId << " message:" << message << " packetId: " << packetId);

		startServices();

		ByteArray messageBytes(message);
		ByteArray encryptedMessageBytes = ipvsdk::security::DataEncryption::encryptMessage(messageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
		message = encryptedMessageBytes.getString(0, encryptedMessageBytes.size());

		auto friendChatPacket = packetBuilder->makeFriendCallBusyMessage(userId, friendId, packetId, MessageType::PLAIN_MESSAGE, 0, message, messageDate, false, ResourceManager::getInstance().getDeviceType());

		if (!friendChatPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		ResendProcessor::DestinationType destination;
		int sendCode;

		std::shared_ptr< ChatConnection> connection = nullptr;

		destination = ResendProcessor::DestinationType::Offline;
		connection = ResourceManager::getInstance().getOfflineConnection();
		sendCode = connection->sendToOfflineServer(friendChatPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, friendChatPacket.byteArray, friendChatPacket.packet, connection, destination));

		return{ packetId };
	}

	ApiStatus Chat::sendFriendCallLogMessage(UserIdentity userId, UserIdentity friendId, std::string &message, long long messageDate, std::string &packetId)
	{
		Log(module, "Sending friend call log message from " << userId << " to " << friendId << " message:" << message << " packetId: " << packetId);

		startServices();

		ByteArray messageBytes(message);
		ByteArray encryptedMessageBytes = ipvsdk::security::DataEncryption::encryptMessage(messageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
		message = encryptedMessageBytes.getString(0, encryptedMessageBytes.size());

		auto friendChatPacket = packetBuilder->makeFriendChatMessage(userId, friendId, packetId, MessageType::CALL_LOG_MESSAGE, 0, message, messageDate, false, ResourceManager::getInstance().getDeviceType(), ResourceManager::getInstance().appVersion, ResourceManager::getInstance().getAppType(), ResourceManager::getInstance().getUserId());

		if (!friendChatPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		ResendProcessor::DestinationType destination;
		int sendCode;

		std::shared_ptr< ChatConnection> connection = nullptr;

		destination = ResendProcessor::DestinationType::Offline;
		connection = ResourceManager::getInstance().getOfflineConnection();
		sendCode = connection->sendToOfflineServer(friendChatPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, friendChatPacket.byteArray, friendChatPacket.packet, connection, destination));

		return{ packetId };
	}

	ApiStatus Chat::editFriendChat(std::string &packetId, UserIdentity userId, UserIdentity friendId, int messageType, int secretTimeout, std::string &message, long long messageDate, bool isSecretVisible)
	{
		Log(module, "Edit friend chat. packetId " << packetId << " friendId " << friendId << " message " << message);

		startServices();

		bool keyValid = isExistsValidKey(packetId, friendId);
		if (!keyValid) {
			return{ packetId, ChatError::FAILED_TO_SEND };
		}

		size_t fixedLength = LEN_PACKET_TYPE + LEN_USER_IDENTITY + LEN_FRIEND_IDENTITY + LEN_PACKETID_LENGTH + (int)packetId.length() + LEN_MESSAGE_TYPE + LEN_TIMEOUT + LEN_MESSAGE_LENGTH + LEN_MESSAGE_DATE + LEN_IS_SECRET_VISIBLE + LEN_PLATFORM + LEN_APP_VERSION + LEN_FRIEND_APP_TYPE + LEN_PAGE_OWNER_IDENTITY;
		size_t availableMsgLength = CHAT_MESSAGE_MAX_SIZE - fixedLength;

		int numberOfBrokenChatMessage;
		int startIndex = 0;
		std::string brokenMessage;

		//    messageDate = messageDate - ResourceManager::getInstance().getTimeDifference();

		if (message.length() > availableMsgLength) {

			numberOfBrokenChatMessage = ceil(((double)message.length() / (double)availableMsgLength));

			for (int chunkNumber = 0; chunkNumber < numberOfBrokenChatMessage; chunkNumber++)
			{
				brokenMessage = message.substr(startIndex, availableMsgLength);
				startIndex = startIndex + availableMsgLength;

                sendOrEditBrokenFriendChat(FRIEND_CHAT_MESSAGE_BROKEN_EDIT, userId, friendId, packetId, numberOfBrokenChatMessage, chunkNumber, messageType, secretTimeout, brokenMessage, ResourceManager::getInstance().getServerSyncedTime(), isSecretVisible);

			}
		}
		else
		{
			ByteArray messageBytes(message);
			ByteArray encryptedMessageBytes = ipvsdk::security::DataEncryption::encryptMessage(messageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
			message = encryptedMessageBytes.getString(0, encryptedMessageBytes.size());

            BuiltPacket editFriendChatPacket = packetBuilder->makeFriendChatMessageEdit(userId, friendId, packetId, messageType, secretTimeout, message, ResourceManager::getInstance().getServerSyncedTime(), isSecretVisible, ResourceManager::getInstance().getDeviceType(), ResourceManager::getInstance().appVersion, ResourceManager::getInstance().getAppType(), ResourceManager::getInstance().getUserId());

			if (!editFriendChatPacket.byteArray)
			{
				Log(module, "Packet builder error");
				return{ packetId, ChatError::PACKET_BUILDER_ERROR };
			}

			auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
			if (!friendInfo)
			{
				Log(module, "Friend info not found. Pushing for pending.");
				editFriendChatPacket.packet->setFromAnonymous(false);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_FRIEND, editFriendChatPacket.packet));
				auto resendPacket = ResendProcessor::ResendPacket(packetId, editFriendChatPacket.byteArray, editFriendChatPacket.packet, nullptr, ResendProcessor::Chat, 0);
				resendPacket.isWaitingForServerUpdate = true;
				ResendProcessor::getInstance().addResendPacket(resendPacket);
				return{ packetId };
			}

			ResendProcessor::DestinationType destination;
			int sendCode;

			std::shared_ptr< ChatConnection> connection = nullptr;
			if (friendInfo->getStatus() == OnlineStatus::ONLINE)
			{
				destination = ResendProcessor::DestinationType::Chat;
				connection = friendInfo->getConnection();
				if (connection->getChatServerStatus() != ChatConnection::READY)
				{
					Log(module, "Connection status is not ready.");
					ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, editFriendChatPacket.byteArray, editFriendChatPacket.packet, connection, ResendProcessor::Chat, 0));
					return{ packetId };
				}
				sendCode = connection->sendToChatServer(editFriendChatPacket.byteArray);
			}
			else
			{
				destination = ResendProcessor::DestinationType::Offline;
				auto connection = ResourceManager::getInstance().getOfflineConnection();
				sendCode = connection->sendToOfflineServer(editFriendChatPacket.byteArray);
			}

			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetId << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, editFriendChatPacket.byteArray, editFriendChatPacket.packet, connection, destination));

		}

		KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId);
		return{ packetId };
	}

	ApiStatus Chat::seenFriendChat(UserIdentity userId, UserIdentity friendId, std::vector<SeenPacketDTO> &seenPacketList)
	{
		Log(module, "Seen friend chat. for userId: " << userId << " friendId " << friendId);

		startServices();
		
        std::string retPacketId;
		for (std::vector<SeenPacketDTO>::size_type i = 0; i < seenPacketList.size();)
		{
			auto packetTimeId = generatePacketId();
			retPacketId = packetTimeId.packetId;

			std::vector<SeenPacketDTO> packetIdsToSend;

			for (std::vector<SeenPacketDTO>::size_type j = 0; j < 10 && i < seenPacketList.size(); j++, i++)
			{
				packetIdsToSend.push_back(seenPacketList[i]);
			}

			BuiltPacket seenPacket = packetBuilder->makeFriendChatMessageSeen(userId, friendId, packetTimeId.packetId, packetIdsToSend);

			if (!seenPacket.byteArray)
			{
				Log(module, "Packet builder error");
				return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
			}

			auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
			std::shared_ptr< ChatConnection> connection = nullptr;
			ResendProcessor::DestinationType destination;
			int sendCode;

			if (!friendInfo)
			{
				Log(module, "Connection not found");

				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_FRIEND, seenPacket.packet));
				auto resendPacket = ResendProcessor::ResendPacket(packetTimeId.packetId, seenPacket.byteArray, seenPacket.packet, nullptr, ResendProcessor::Chat, 0);
				resendPacket.isWaitingForServerUpdate = true;
				ResendProcessor::getInstance().addResendPacket(resendPacket);
				return{ packetTimeId.packetId };
			}

			if (friendInfo->getStatus() != OnlineStatus::ONLINE)
			{
				connection = ResourceManager::getInstance().getOfflineConnection();
				sendCode = connection->sendToOfflineServer(seenPacket.byteArray);
				destination = ResendProcessor::DestinationType::Offline;
			}
			else
			{
				connection = friendInfo->getConnection();
				sendCode = connection->sendToChatServer(seenPacket.byteArray);
				destination = ResendProcessor::DestinationType::Chat;
			}

			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, seenPacket.byteArray, seenPacket.packet, connection, destination));
		}

		KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId);
		return{ retPacketId };
	}

	ApiStatus Chat::typingFriendChat(UserIdentity userId, UserIdentity friendId)
	{
		Log(module, "Typing friend chat. for userId: " << userId << " friendId " << friendId);

		startServices();

		auto packetTimeId = generatePacketId();

		BuiltPacket typingPacket = packetBuilder->makeFriendChatMessageTyping(userId, friendId, ResourceManager::getInstance().getDeviceType(), packetTimeId.packetId);

		if (!typingPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
		if (!friendInfo)
		{
			Log(module, "Connection not found");

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_FRIEND, typingPacket.packet));
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		if (friendInfo->getStatus() == OnlineStatus::ONLINE)
		{
			auto connection = friendInfo->getConnection();
			auto sendCode = connection->sendToChatServer(typingPacket.byteArray);
			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}
		}

		KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId);
		return{ packetTimeId.packetId };
	}

    ApiStatus Chat::deleteFriendChatMessage(UserIdentity userId, UserIdentity friendId, std::vector<std::string> &packetIds, int deleteType)
	{
		startServices();

		Log(module, "Delete friend chat. for userId: " << userId << " friendId " << friendId);
		std::string retPacketId;

		for (std::vector<std::string>::size_type i = 0; i < packetIds.size();)
		{
			auto packetTimeId = generatePacketId();
			retPacketId = packetTimeId.packetId;

			std::vector<std::string> packetIdsToSend;

			for (int j = 0; j < 11 && i < packetIds.size(); j++, i++)
			{
				packetIdsToSend.push_back(packetIds[i]);
			}

            BuiltPacket deleteFriendChatPacket = packetBuilder->makeFriendChatMultipleMessageDelete(userId, friendId, packetTimeId.packetId, packetIdsToSend, ResourceManager::getInstance().getDeviceType(), deleteType);

			if (!deleteFriendChatPacket.byteArray)
			{
				Log(module, "Packet builder error");
				return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
			}

            std::shared_ptr< ChatConnection> connection = nullptr;
            ResendProcessor::DestinationType destination;

            if (deleteType == MessageDeleteType::SELF_DEVICE)
            {
                connection = ResourceManager::getInstance().getOfflineConnection();
                connection->sendToOfflineServer(deleteFriendChatPacket.byteArray);
                destination = ResendProcessor::DestinationType::Offline;
            }

            else
            {
                auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
                if (!friendInfo)
                {
                    Log(module, "Friend info not found. Pushing for pending.");
                    EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_FRIEND, deleteFriendChatPacket.packet));
                    auto resendPacket = ResendProcessor::ResendPacket(packetTimeId.packetId, deleteFriendChatPacket.byteArray, deleteFriendChatPacket.packet, nullptr, ResendProcessor::DestinationType::Chat, 0);
                    resendPacket.isWaitingForServerUpdate = true;
                    ResendProcessor::getInstance().addResendPacket(resendPacket);
                    return{ packetTimeId.packetId };
                }

                if (friendInfo->getStatus() != OnlineStatus::ONLINE)
                {
                    connection = ResourceManager::getInstance().getOfflineConnection();
                    connection->sendToOfflineServer(deleteFriendChatPacket.byteArray);
                    destination = ResendProcessor::DestinationType::Offline;
                }
                else
                {
                    connection = friendInfo->getConnection();
                    auto sendCode = connection->sendToChatServer(deleteFriendChatPacket.byteArray);
                    destination = ResendProcessor::DestinationType::Chat;
                    if (sendCode < 0)
                    {
                        Log(module, "Socket returned " << sendCode);
                    }
                }
            }

			Log(module, "Adding " << packetTimeId.packetId << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, deleteFriendChatPacket.byteArray, deleteFriendChatPacket.packet, connection, destination));

		}

		KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId);
		return{ retPacketId };
	}

	ApiStatus Chat::requestFriendChatHistory(UserIdentity userId, UserIdentity friendId, std::string &packetId, int direction, int limit)
	{
		startServices();
		Log(module, "Request friend chat history for user : " << userId << " && friend: " << friendId);

		auto connection = ResourceManager::getInstance().getOfflineConnection();

		BuiltPacket friendChatHistoryRequestPacket = packetBuilder->makeOfflineFriendHistoryMessageRequest(userId, friendId, packetId, direction, limit, ResourceManager::getInstance().getDeviceType(), ResourceManager::getInstance().getAppType(), SDK_VERSION, ResourceManager::getInstance().getUserId());
		if (!friendChatHistoryRequestPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto sendCode = connection->sendToOfflineServer(friendChatHistoryRequestPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned, sendcode: " << sendCode);
		}

		std::string modifiedPacketId = packetId + ResourceManager::toLongToString(ResourceManager::getInstance().getUserId());
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(modifiedPacketId, friendChatHistoryRequestPacket.byteArray, friendChatHistoryRequestPacket.packet, connection, ResendProcessor::Offline));
		return{ packetId };
	}

	ApiStatus Chat::getFriendMessageStatus(UserIdentity userId, UserIdentity friendId, std::vector<std::string> &packetIds)
	{
        startServices();

        Log(module, "Get friend message status for user: " << userId << " && friend: " << friendId);

        std::string retPacketId;

        for (std::vector<std::string>::size_type i = 0; i < packetIds.size();)
        {
            auto packetTimeId = generatePacketId();
            retPacketId = packetTimeId.packetId;

            std::vector<std::string> packetIdsToSend;

            for (int j = 0; j < 11 && i < packetIds.size(); j++, i++)
            {
                packetIdsToSend.push_back(packetIds[i]);
            }

            BuiltPacket getFriendmessageStatusPacket = packetBuilder->makeOfflineGetFriendMessgaeStatus(userId, friendId, packetTimeId.packetId, packetIdsToSend);

            if (!getFriendmessageStatusPacket.byteArray)
            {
                Log(module, "Packet builder error");
                return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
            }

            std::shared_ptr< ChatConnection> connection = ResourceManager::getInstance().getOfflineConnection();

            if (!getFriendmessageStatusPacket.byteArray)
            {
                Log(module, "Packet builder error");
                return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
            }

            auto sendCode = connection->sendToOfflineServer(getFriendmessageStatusPacket.byteArray);

            if (sendCode < 0)
            {
                Log(module, "Socket returned, sendcode: " << sendCode);
            }

            ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, getFriendmessageStatusPacket.byteArray, getFriendmessageStatusPacket.packet, connection, ResendProcessor::Offline));
        }

        KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId);
        return{ retPacketId };
	}

	ApiStatus Chat::blockFriend(UserIdentity userId, std::string &packetId, UserIdentity friendId, long long blockUnblockDate, bool addToBlock)
	{
		startServices();
		Log(module, "Block friend. from userId: " << userId << " friendId " << friendId << " addToBlock " << addToBlock);

		//    blockUnblockDate = blockUnblockDate - ResourceManager::getInstance().getTimeDifference();


		auto blockPacket = packetBuilder->makeFriendBlock(userId, friendId, packetId, blockUnblockDate, addToBlock);
		if (!blockPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
		if (!friendInfo)
		{
			Log(module, "Friend info not found");
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_FRIEND, blockPacket.packet));
			auto resendPacket = ResendProcessor::ResendPacket(packetId, blockPacket.byteArray, blockPacket.packet, nullptr, ResendProcessor::Chat, 0);
			resendPacket.isWaitingForServerUpdate = true;
			ResendProcessor::getInstance().addResendPacket(resendPacket);
			return{ packetId };
		}

		auto connection = friendInfo->getConnection();

		if (friendInfo->getStatus() == OnlineStatus::ONLINE)
		{
			auto sendCode = connection->sendToChatServer(blockPacket.byteArray);
			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetId << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, blockPacket.byteArray, blockPacket.packet, connection, ResendProcessor::Chat));
		}
		else
		{
			auto connection = ResourceManager::getInstance().getOfflineConnection();
			auto sendCode = connection->sendToOfflineServer(blockPacket.byteArray);
			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetId << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, blockPacket.byteArray, blockPacket.packet, connection, ResendProcessor::Offline));
		}
		KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId);
		return{ packetId };
	}

	ApiStatus Chat::unblockFriend(UserIdentity userId, std::string &packetId, UserIdentity friendId, long long blockUnblockDate)
	{
		startServices();
		Log(module, "Unblock friend. from userId: " << userId << " friendId " << friendId);

		//    blockUnblockDate = blockUnblockDate - ResourceManager::getInstance().getTimeDifference();

		auto unblockPacket = packetBuilder->makeFriendUnblock(userId, friendId, packetId, blockUnblockDate);
		if (!unblockPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
		if (!friendInfo)
		{
			Log(module, "Connection not found");
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_FRIEND, unblockPacket.packet));
			auto resendPacket = ResendProcessor::ResendPacket(packetId, unblockPacket.byteArray, unblockPacket.packet, nullptr, ResendProcessor::Chat, 0);
			resendPacket.isWaitingForServerUpdate = true;
			ResendProcessor::getInstance().addResendPacket(resendPacket);
			return{ packetId };
		}

		if (friendInfo->getStatus() == OnlineStatus::ONLINE)
		{
			auto connection = friendInfo->getConnection();
			auto sendCode = connection->sendToChatServer(unblockPacket.byteArray);
			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetId << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, unblockPacket.byteArray, unblockPacket.packet, connection, ResendProcessor::Chat));
		}
		else
		{
			auto connection = ResourceManager::getInstance().getOfflineConnection();
			auto sendCode = connection->sendToOfflineServer(unblockPacket.byteArray);
			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetId << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, unblockPacket.byteArray, unblockPacket.packet, connection, ResendProcessor::Offline));
		}
		KeepaliveProcessor::getInstance().resetFriendKeepalive(userId, friendId);
		return{ packetId };
	}

	ApiStatus Chat::sendOrEditBrokenGroupChat(int packetType, GroupIdentity groupId, std::string &packetId, int totalNumberOfPackets, int chunkNumber, int messageType, std::string &message, long long messageDate)
	{
		Log(module, "Sending group chat to " << groupId << " message:" << message);

		ByteArray messageBytes(message);
		ByteArray encryptedMessageBytes = ipvsdk::security::DataEncryption::encryptMessage(messageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
		message = encryptedMessageBytes.getString(0, encryptedMessageBytes.size());

		std::string brokenPacketId;
		brokenPacketId = packetId;
		brokenPacketId += "_";
		brokenPacketId += ResourceManager::toString(chunkNumber);

		auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
		if (!connection)
		{
			Log(module, "Connection not found");
			return{ brokenPacketId, ChatError::CONNECTION_NOT_FOUND };
		}

		BuiltPacket groupChatPacket;

		if (packetType == GROUP_CHAT_MESSAGE_BROKEN)
		{
			groupChatPacket = packetBuilder->makeGroupChatMessageBroken(ResourceManager::getInstance().getUserId(), groupId, packetId, totalNumberOfPackets, chunkNumber, messageType, message, messageDate);
		}
		else if (packetType == GROUP_CHAT_MESSAGE_BROKEN_EDIT)
		{
			groupChatPacket = packetBuilder->makeGroupChatMessageBrokenEdit(ResourceManager::getInstance().getUserId(), groupId, packetId, totalNumberOfPackets, chunkNumber, messageType, message, messageDate);
		}

		if (!groupChatPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ brokenPacketId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto sendCode = connection->sendToChatServer(groupChatPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << brokenPacketId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(brokenPacketId, groupChatPacket.byteArray, groupChatPacket.packet, connection, ResendProcessor::Chat));

		return{ brokenPacketId };
	}

	ApiStatus Chat::sendOrEditBrokenPublicRoomChat(int packetType, RoomIdentity roomId, std::string &packetId, int totalNumberOfPackets, int chunkNumber, int messageType, std::string &message, long long messageDate, std::string &memberFullName, std::string &memberProfileUrl){
		Log(module, "Sending Public Room Chat Message. Chat room " << roomId << " Message:" << message);

		std::string brokenPacketId;
		brokenPacketId = packetId;
		brokenPacketId += "_";
		brokenPacketId += ResourceManager::toString(chunkNumber);

		auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
		if (!roomInfo)
		{
			Log(module, "Room Info Not Found for roomId: " + roomId);
			return{ packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto connection = roomInfo->getConnection();
		if (!connection)
		{
			Log(module, "Connection not found");
			return{ brokenPacketId, ChatError::CONNECTION_NOT_FOUND };
		}

		BuiltPacket publicRoomChatPacket;

		if (packetType == PUBLIC_ROOM_CHAT_MESSAGE_BROKEN)
		{
			publicRoomChatPacket = packetBuilder->makePublicRoomChatMessageBrokenPacket(ResourceManager::getInstance().getUserId(), roomId, packetId, totalNumberOfPackets, chunkNumber, messageType, message, messageDate, memberFullName, memberProfileUrl);
		}
		else if (packetType == PUBLIC_ROOM_CHAT_MESSAGE_BROKEN_EDIT)
		{
			publicRoomChatPacket = packetBuilder->makePublicRoomChatMessageBrokenEditPacket(ResourceManager::getInstance().getUserId(), roomId, packetId, totalNumberOfPackets, chunkNumber, messageType, message, messageDate, memberFullName, memberProfileUrl);
		}

		if (!publicRoomChatPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ brokenPacketId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto sendCode = connection->sendToChatServer(publicRoomChatPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << brokenPacketId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(brokenPacketId, publicRoomChatPacket.byteArray, publicRoomChatPacket.packet, connection, ResendProcessor::Chat));

		return{ brokenPacketId };
	}

	ApiStatus Chat::sendGroupChat(std::string &packetId, GroupIdentity groupId, int messageType, std::string &message, long long messageDate)
	{
		Log(module, "Send group chat. groupId " << groupId << " message " << message);

		startServices();

		bool keyValid = isExistsValidKey(packetId, 0, groupId);
		if (!keyValid) {
			return{ packetId, ChatError::FAILED_TO_SEND };
		}

		size_t fixedLength = LEN_PACKET_TYPE + LEN_USER_IDENTITY + LEN_GROUPID + LEN_PACKETID_LENGTH + (int)packetId.length() + LEN_MESSAGE_TYPE + LEN_MESSAGE_LENGTH + LEN_MESSAGE_DATE;
		size_t availableMsgLength = CHAT_MESSAGE_MAX_SIZE - fixedLength;

		int numberOfBrokenChatMessage;
		int startIndex = 0;
		std::string brokenMessage;

		//    messageDate = messageDate - ResourceManager::getInstance().getTimeDifference();

		if (message.length() > availableMsgLength) {

			numberOfBrokenChatMessage = ceil(((double)message.length() / (double)availableMsgLength));

			for (int chunkNumber = 0; chunkNumber < numberOfBrokenChatMessage; chunkNumber++)
			{
				brokenMessage = message.substr(startIndex, availableMsgLength);
				startIndex = startIndex + availableMsgLength;

				sendOrEditBrokenGroupChat(GROUP_CHAT_MESSAGE_BROKEN, groupId, packetId, numberOfBrokenChatMessage, chunkNumber, messageType, brokenMessage, messageDate);
			}
		}
		else
		{
			ByteArray messageBytes(message);
			ByteArray encryptedMessageBytes = ipvsdk::security::DataEncryption::encryptMessage(messageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
			message = encryptedMessageBytes.getString(0, encryptedMessageBytes.size());

			auto groupChatPacket = packetBuilder->makeGroupChatMessage(ResourceManager::getInstance().getUserId(), groupId, packetId, messageType, message, messageDate);
			if (!groupChatPacket.byteArray)
			{
				Log(module, "Packet builder error");
				return{ packetId, ChatError::PACKET_BUILDER_ERROR };
			}

			auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
			if (!connection)
			{
				Log(module, "Group info not found. Pushing for pending.");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_GROUP, groupChatPacket.packet));
				auto resendPacket = ResendProcessor::ResendPacket(packetId, groupChatPacket.byteArray, groupChatPacket.packet, nullptr, ResendProcessor::Chat, 0);
				resendPacket.isWaitingForServerUpdate = true;
				ResendProcessor::getInstance().addResendPacket(resendPacket);
				return{ packetId };
			}

			auto sendCode = connection->sendToChatServer(groupChatPacket.byteArray);
			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetId << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, groupChatPacket.byteArray, groupChatPacket.packet, connection, ResendProcessor::Chat));
		}
		KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);

		return{ packetId };
	}

	ApiStatus Chat::editGroupChat(std::string &packetId, GroupIdentity groupId, int messageType, std::string &message, long long messageDate)
	{
		Log(module, "Edit group chat. packetId " << packetId << " groupId " << groupId << " message " << message);

		startServices();

		bool keyValid = isExistsValidKey(packetId, 0, groupId);
		if (!keyValid) {
			return{ packetId, ChatError::FAILED_TO_SEND };
		}

		size_t fixedLength = LEN_PACKET_TYPE + LEN_USER_IDENTITY + LEN_GROUPID + LEN_PACKETID_LENGTH + (int)packetId.length() + LEN_MESSAGE_TYPE + LEN_MESSAGE_LENGTH + LEN_MESSAGE_DATE;
		size_t availableMsgLength = CHAT_MESSAGE_MAX_SIZE - fixedLength;

		int numberOfBrokenChatMessage;
		int startIndex = 0;
		std::string brokenMessage;

		//    messageDate = messageDate - ResourceManager::getInstance().getTimeDifference();

		if (message.length() > availableMsgLength) {

			numberOfBrokenChatMessage = ceil(((double)message.length() / (double)availableMsgLength));

			for (int chunkNumber = 0; chunkNumber < numberOfBrokenChatMessage; chunkNumber++)
			{
				brokenMessage = message.substr(startIndex, availableMsgLength);
				startIndex = startIndex + availableMsgLength;

				sendOrEditBrokenGroupChat(GROUP_CHAT_MESSAGE_BROKEN_EDIT, groupId, packetId, numberOfBrokenChatMessage, chunkNumber, messageType, brokenMessage, messageDate);

			}
		}
		else
		{
			ByteArray messageBytes(message);
			ByteArray encryptedMessageBytes = ipvsdk::security::DataEncryption::encryptMessage(messageBytes, (*ResourceManager::getInstance().getEncryptionDecryptionKey()));
			message = encryptedMessageBytes.getString(0, encryptedMessageBytes.size());

			BuiltPacket editGroupChatPacket = packetBuilder->makeGroupChatMessageEdit(ResourceManager::getInstance().getUserId(), groupId, packetId, messageType, message, messageDate);
			if (!editGroupChatPacket.byteArray)
			{
				Log(module, "Packet builder error");
				return{ packetId, ChatError::PACKET_BUILDER_ERROR };
			}

			auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
			if (!connection)
			{
				Log(module, "Group info not found. Pushing for pending.");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_GROUP, editGroupChatPacket.packet));
				auto resendPacket = ResendProcessor::ResendPacket(packetId, editGroupChatPacket.byteArray, editGroupChatPacket.packet, nullptr, ResendProcessor::Chat, 0);
				resendPacket.isWaitingForServerUpdate = true;
				ResendProcessor::getInstance().addResendPacket(resendPacket);
				return{ packetId };
			}

			auto sendCode = connection->sendToChatServer(editGroupChatPacket.byteArray);
			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetId << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, editGroupChatPacket.byteArray, editGroupChatPacket.packet, connection, ResendProcessor::Chat));
		}

		KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);
		return{ packetId };
	}

    ApiStatus Chat::seenGroupChat(GroupIdentity groupId, std::vector<std::string> &packetIds)
    {
        Log(module, "Seen group chat. groupId " << groupId);
        startServices();

        std::string retPacketId;
        for (std::vector<SeenPacketDTO>::size_type i = 0; i < packetIds.size();)
        {
            auto packetTimeId = generatePacketId();
            retPacketId = packetTimeId.packetId;

            std::vector<std::string> packetIdsToSend;

            for (std::vector<std::string>::size_type j = 0; j < 12 && i < packetIds.size(); j++, i++)
            {
                packetIdsToSend.push_back(packetIds[i]);
            }

            BuiltPacket seenGroupChatPacket = packetBuilder->makeGroupChatMessageSeen(ResourceManager::getInstance().getUserId(), groupId, packetTimeId.packetId, packetIdsToSend);

            if (!seenGroupChatPacket.byteArray)
            {
                Log(module, "Packet builder error");
                return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
            }

            auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
            if (!connection)
            {
                Log(module, "Connection not found");
                EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_GROUP, seenGroupChatPacket.packet));
                return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
            }

            auto sendCode = connection->sendToChatServer(seenGroupChatPacket.byteArray);
            if (sendCode < 0)
            {
                Log(module, "Socket returned " << sendCode);
            }

            Log(module, "Adding " << packetTimeId.packetId << " for resend");
            ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, seenGroupChatPacket.byteArray, seenGroupChatPacket.packet, connection, ResendProcessor::Chat));
        }

        KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);
        return{ retPacketId };
    }

	ApiStatus Chat::typingGroupChat(GroupIdentity groupId)
	{
		Log(module, "Typing group chat. groupId " << groupId);

		startServices();

		auto packetTimeId = generatePacketId();

        auto typingGroupChatPacket = packetBuilder->makeGroupChatMessageTyping(ResourceManager::getInstance().getUserId(), groupId, ResourceManager::getInstance().getDeviceType(), packetTimeId.packetId);
		if (!typingGroupChatPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
		if (!connection)
		{
			Log(module, "Connection not found");
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_GROUP, typingGroupChatPacket.packet));
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto sendCode = connection->sendToChatServer(typingGroupChatPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);
		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::deleteGroupChatMessage(GroupIdentity groupId, std::vector<std::string> &packetIds)
	{
		startServices();

		Log(module, "Delete group chat. GroupId " << groupId);
		std::string retPacketId;

		for (std::vector<std::string>::size_type i = 0; i < packetIds.size();)
		{
			auto packetTimeId = generatePacketId();
			retPacketId = packetTimeId.packetId;

			std::vector<std::string> packetIdsToSend;

			for (int j = 0; j < 11 && i < packetIds.size(); j++, i++)
			{
				packetIdsToSend.push_back(packetIds[i]);
			}

			BuiltPacket deleteGroupChatPacket = packetBuilder->makeGroupChatMultipleMessageDelete(ResourceManager::getInstance().getUserId(), groupId, packetTimeId.packetId, packetIdsToSend);
			if (!deleteGroupChatPacket.byteArray)
			{
				Log(module, "Packet builder error");
				return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
			}
			auto groupConnection = ResourceManager::getInstance().getGroupConnection(groupId);
			if (!groupConnection)
			{
				Log(module, "Connection not found");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_GROUP, deleteGroupChatPacket.packet));
				auto resendPacket = ResendProcessor::ResendPacket(packetTimeId.packetId, deleteGroupChatPacket.byteArray, deleteGroupChatPacket.packet, nullptr, ResendProcessor::Chat, 0);
				resendPacket.isWaitingForServerUpdate = true;
				ResendProcessor::getInstance().addResendPacket(resendPacket);
				return{ packetTimeId.packetId };
			}

			auto sendCode = groupConnection->sendToChatServer(deleteGroupChatPacket.byteArray);
			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetTimeId.packetId << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, deleteGroupChatPacket.byteArray, deleteGroupChatPacket.packet, groupConnection, ResendProcessor::Chat));
		}

		KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);
		return{ retPacketId };
	}

	ApiStatus Chat::removeGroupMembers(GroupIdentity groupId, std::vector<UserIdentity> &memberIds)
	{
		startServices();
		Log(module, "Remove group members. groupId " << groupId << " number of member " << memberIds.size());

		std::vector<MemberDTO> memberList;

		for (std::vector<UserIdentity>::size_type i = 0; i < memberIds.size(); i++) {
			MemberDTO member;
			member.setMemberIdentity(memberIds[i]);
			memberList.push_back(member);
		}

		auto packetTimeId = generatePacketId();

		auto removeGroupMembersPacket = packetBuilder->makeGroupMemberRemoveLeave(ResourceManager::getInstance().getUserId(), groupId, packetTimeId.packetId, memberList);
		if (!removeGroupMembersPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
		if (!connection)
		{
			Log(module, "Connection not found");
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_GROUP, removeGroupMembersPacket.packet));
			auto resendPacket = ResendProcessor::ResendPacket(packetTimeId.packetId, removeGroupMembersPacket.byteArray, removeGroupMembersPacket.packet, nullptr, ResendProcessor::Chat, 0);
			resendPacket.isWaitingForServerUpdate = true;
			ResendProcessor::getInstance().addResendPacket(resendPacket);
			return{ packetTimeId.packetId };
		}

		auto sendCode = connection->sendToChatServer(removeGroupMembersPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, removeGroupMembersPacket.byteArray, removeGroupMembersPacket.packet, connection, ResendProcessor::Chat));
		KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);
		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::addGroupMembers(GroupIdentity groupId, std::vector<MemberDTO> &memberList)
	{
		startServices();
		Log(module, "Add group member. groupId " << groupId << " number of member " << memberList.size());

		std::string retPacketId;

		for (std::vector<MemberDTO>::size_type i = 0; i < memberList.size();)
		{
			auto packetTimeId = generatePacketId();
			retPacketId = packetTimeId.packetId;

			std::vector<MemberDTO> memberListToSend;

			int constantSize = LEN_USER_IDENTITY + LEN_GROUPID + LEN_PACKETID_LENGTH + retPacketId.size() + LEN_NUMBER_OF_MEMBERS_ID_N_S;

			for (; constantSize < CHAT_MESSAGE_MAX_SIZE && i < memberList.size(); i++)
			{
				memberListToSend.push_back(memberList[i]);
				constantSize += LEN_USER_IDENTITY + LEN_RING_ID + LEN_FULLNAME_LENGTH + memberList[i].getFullName().size() + LEN_MEMBER_STATUS;
			}

			auto addGroupMembersPacket = packetBuilder->makeGroupMemberAdd(ResourceManager::getInstance().getUserId(), groupId, packetTimeId.packetId, memberListToSend);
			if (!addGroupMembersPacket.byteArray)
			{
				Log(module, "Packet builder error");
				return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
			}

			auto connection = ResourceManager::getInstance().getGroupConnection(groupId);

			if (!connection)
			{
				Log(module, "Connection not found");
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_GROUP, addGroupMembersPacket.packet));
				auto resendPacket = ResendProcessor::ResendPacket(packetTimeId.packetId, addGroupMembersPacket.byteArray, addGroupMembersPacket.packet, nullptr, ResendProcessor::Chat, 0);
				resendPacket.isWaitingForServerUpdate = true;
				ResendProcessor::getInstance().addResendPacket(resendPacket);
				return{ packetTimeId.packetId };
			}

			auto sendCode = connection->sendToChatServer(addGroupMembersPacket.byteArray);
			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetTimeId.packetId << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, addGroupMembersPacket.byteArray, addGroupMembersPacket.packet, connection, ResendProcessor::Chat));
		}

		KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);
		return{ retPacketId };
	}

	ApiStatus Chat::changeGroupName(GroupIdentity groupId, std::string &groupName)
	{
		startServices();
		auto packetTimeId = generatePacketId();

		Log(module, "Update group information for group: " << groupId);

		BuiltPacket updateGroupInformationPacket = packetBuilder->makeGroupInformation(ResourceManager::getInstance().getUserId(), groupId, packetTimeId.packetId, GroupChangeActivity::GROUP_RENAME, groupName);
		if (!updateGroupInformationPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
		if (!connection)
		{
			Log(module, "Connection not found");
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_GROUP, updateGroupInformationPacket.packet));
			auto resendPacket = ResendProcessor::ResendPacket(packetTimeId.packetId, updateGroupInformationPacket.byteArray, updateGroupInformationPacket.packet, nullptr, ResendProcessor::Chat, 0);
			resendPacket.isWaitingForServerUpdate = true;
			ResendProcessor::getInstance().addResendPacket(resendPacket);
			return{ packetTimeId.packetId };
		}

		auto sendCode = connection->sendToChatServer(updateGroupInformationPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned, sendcode: " << sendCode);
		}

		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, updateGroupInformationPacket.byteArray, updateGroupInformationPacket.packet, connection, ResendProcessor::Chat));
		KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);
		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::changeGroupUrl(GroupIdentity groupId, std::string &groupUrl)
	{
		startServices();
		auto packetTimeId = generatePacketId();

		Log(module, "Update group information for group: " << groupId);

		BuiltPacket updateGroupInformationPacket = packetBuilder->makeGroupInformation(ResourceManager::getInstance().getUserId(), groupId, packetTimeId.packetId, GroupChangeActivity::GROUP_URL_RENAME, groupUrl);
		if (!updateGroupInformationPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
		if (!connection)
		{
			Log(module, "Connection not found");
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_GROUP, updateGroupInformationPacket.packet));
			auto resendPacket = ResendProcessor::ResendPacket(packetTimeId.packetId, updateGroupInformationPacket.byteArray, updateGroupInformationPacket.packet, nullptr, ResendProcessor::Chat, 0);
			resendPacket.isWaitingForServerUpdate = true;
			ResendProcessor::getInstance().addResendPacket(resendPacket);
			return{ packetTimeId.packetId };
		}

		auto sendCode = connection->sendToChatServer(updateGroupInformationPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned, sendcode: " << sendCode);
		}

		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, updateGroupInformationPacket.byteArray, updateGroupInformationPacket.packet, connection, ResendProcessor::Chat));
		KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);
		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::changeGroupMemberStatus(GroupIdentity groupId, std::vector<MemberDTO> &memberList)
	{
		startServices();
		Log(module, "Change member status. groupId " << groupId);
        for (int i=0; i<memberList.size(); i++)
        {
            Log(module, memberList[i].getMemberIdentity() << " " + memberList[i].getFullName() << " " << memberList[i].getRingId() << memberList[i].getStatus());
        }

		auto packetTimeId = generatePacketId();

		auto groupMemberStatusChangePacket = packetBuilder->makeGroupMemberTypeChange(ResourceManager::getInstance().getUserId(), groupId, packetTimeId.packetId, memberList);
		if (!groupMemberStatusChangePacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
		if (!connection)
		{
			Log(module, "Connection not found");
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_GROUP, groupMemberStatusChangePacket.packet));
			auto resendPacket = ResendProcessor::ResendPacket(packetTimeId.packetId, groupMemberStatusChangePacket.byteArray, groupMemberStatusChangePacket.packet, nullptr, ResendProcessor::Chat, 0);
			resendPacket.isWaitingForServerUpdate = true;
			ResendProcessor::getInstance().addResendPacket(resendPacket);
			return{ packetTimeId.packetId };
		}

		auto sendCode = connection->sendToChatServer(groupMemberStatusChangePacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, groupMemberStatusChangePacket.byteArray, groupMemberStatusChangePacket.packet, connection, ResendProcessor::Chat));
		KeepaliveProcessor::getInstance().resetGroupKeepalive(groupId);
		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::createGroup(GroupIdentity groupId, std::string &groupName, std::string &groupUrl, std::vector<MemberDTO> &memberList)
	{
		startServices();
		auto packetTimeId = generatePacketId();

		Log(module, "Create group with groupId: " << groupId);
        for (int i=0; i<memberList.size(); i++)
        {
            Log(module, memberList[i].getMemberIdentity() << " " + memberList[i].getFullName() << " " << memberList[i].getRingId() << memberList[i].getStatus());
        }

		auto connection = ResourceManager::getInstance().getOfflineConnection();

		BuiltPacket createGroupPacket = packetBuilder->makeOfflineCreateGroup(ResourceManager::getInstance().getUserId(), groupId, packetTimeId.packetId, groupName, groupUrl, memberList);

		if (!createGroupPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		int numberOfBytePacket = ceil(((double)createGroupPacket.byteArray->size() / (double)CHAT_MESSAGE_MAX_SIZE));

		int sendCode;
		if (numberOfBytePacket > 1)
		{
			for (int i = 0, j = 0; i < numberOfBytePacket; i++, j += CHAT_MESSAGE_MAX_SIZE)
			{
				std::shared_ptr< ByteArray> ba = std::make_shared<ByteArray>(createGroupPacket.byteArray->getDataPtr() + j, CHAT_MESSAGE_MAX_SIZE);

				std::string brokenPacketIdString = packetTimeId.packetId;
				brokenPacketIdString = brokenPacketIdString + "_" + ResourceManager::getInstance().toString(i);

				BuiltPacket brokenCreateGroupPacket = packetBuilder->makeOfflineBrokenPacket(packetTimeId.packetId, numberOfBytePacket, i, ba);
				sendCode = connection->sendToOfflineServer(brokenCreateGroupPacket.byteArray);

				ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(brokenPacketIdString, brokenCreateGroupPacket.byteArray, brokenCreateGroupPacket.packet, connection, ResendProcessor::Offline));
			}
		}
		else
		{
			sendCode = connection->sendToOfflineServer(createGroupPacket.byteArray);
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, createGroupPacket.byteArray, createGroupPacket.packet, connection, ResendProcessor::Offline));
		}

		if (sendCode < 0)
		{
			Log(module, "Socket returned, sendCode: " << sendCode);
		}

		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::requestGroupChatHistory(GroupIdentity groupId, std::string &packetId, int direction, int limit)
	{
		startServices();
		Log(module, "Request group chat history for groupId: " << groupId);

		auto connection = ResourceManager::getInstance().getOfflineConnection();

		BuiltPacket requestGroupChatHistoryPacket = packetBuilder->makeOfflineGroupHistoryMessageRequest(ResourceManager::getInstance().getUserId(), groupId, packetId, direction, limit, ResourceManager::getInstance().appVersion);
		if (!requestGroupChatHistoryPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto sendCode = connection->sendToOfflineServer(requestGroupChatHistoryPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned, sendCode: " << sendCode);
		}

		std::string modifiedPacketId = packetId + ResourceManager::toLongToString(ResourceManager::getInstance().getUserId());
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(modifiedPacketId, requestGroupChatHistoryPacket.byteArray, requestGroupChatHistoryPacket.packet, connection, ResendProcessor::Offline));
		return{ packetId };
	}

	ApiStatus Chat::getGroupInformationWithMembers(GroupIdentity groupId)
	{
		startServices();
		Log(module, "Get information with members for groupId: " << groupId);
		auto packetTimeId = generatePacketId();

		auto connection = ResourceManager::getInstance().getOfflineConnection();

		BuiltPacket getGroupInformationWithMembersPacket = packetBuilder->makeOfflineGetInformationWithMembers(ResourceManager::getInstance().getUserId(), groupId, packetTimeId.packetId);
		if (!getGroupInformationWithMembersPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto sendCode = connection->sendToOfflineServer(getGroupInformationWithMembersPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned, sendCode: " << sendCode);
		}

		std::string modifiedPacketId = packetTimeId.packetId + ResourceManager::toLongToString(ResourceManager::getInstance().getUserId());
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(modifiedPacketId, getGroupInformationWithMembersPacket.byteArray, getGroupInformationWithMembersPacket.packet, connection, ResendProcessor::Offline));
		return{ packetTimeId.packetId };
	}

    ApiStatus Chat::leaveGroup(GroupIdentity groupId, bool isHide)
	{
		startServices();
        Log(module, "Leave group. groupId " << groupId << " isHide" << isHide);

		KeepaliveProcessor::getInstance().removeGroupKeepalive(groupId);

		auto packetTimeId = generatePacketId();

		std::vector<MemberDTO> memberList(1);
		memberList[0].setMemberIdentity(ResourceManager::getInstance().getUserId());

        int leaveType = isHide ? 2 : 1;
        auto removeGroupMembersPacket = packetBuilder->makeGroupMemberRemoveLeave(ResourceManager::getInstance().getUserId(), groupId, packetTimeId.packetId, memberList, leaveType);
		if (!removeGroupMembersPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
		if (!connection)
		{
			Log(module, "Connection not found");
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_GROUP, removeGroupMembersPacket.packet));
			auto resendPacket = ResendProcessor::ResendPacket(packetTimeId.packetId, removeGroupMembersPacket.byteArray, removeGroupMembersPacket.packet, nullptr, ResendProcessor::Chat, 0);
			resendPacket.isWaitingForServerUpdate = true;
			ResendProcessor::getInstance().addResendPacket(resendPacket);
			return{ packetTimeId.packetId };
		}

		auto sendCode = connection->sendToChatServer(removeGroupMembersPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, removeGroupMembersPacket.byteArray, removeGroupMembersPacket.packet, connection, ResendProcessor::Chat));
		return{ packetTimeId.packetId };
	}

	std::shared_ptr< ByteArray> Chat::getGroupFileTransferIdlePacket(GroupIdentity groupId)
	{
		auto groupFileIdelPacket = packetBuilder->makeGroupFileIdelPacket(ResourceManager::getInstance().getUserId(), groupId, ResourceManager::getInstance().getDeviceType());
		if (!groupFileIdelPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return nullptr;
		}
		return groupFileIdelPacket.byteArray;
	}

	std::shared_ptr< ByteArray> Chat::getGroupFileIdlePacket(GroupIdentity groupId)
	{
		auto chatIdlePacket = packetBuilder->makeGroupFileIdel(ResourceManager::getInstance().getUserId(), groupId, ResourceManager::getInstance().getDeviceType());
		if (!chatIdlePacket.byteArray)
		{
			Log(module, "Packet builder error");
			return nullptr;
		}
		return chatIdlePacket.byteArray;
	}

	std::shared_ptr< ByteArray> Chat::getFriendFileIdelPacket(UserIdentity userId, UserIdentity friendId)
	{
		auto friendFileIdlePacket = packetBuilder->makeFriendFileIdelPacket(userId, friendId, ResourceManager::getInstance().getDeviceType());
		if (!friendFileIdlePacket.byteArray)
		{
			Log(module, "Packet builder error");
			return nullptr;
		}
		return friendFileIdlePacket.byteArray;
	}

	std::vector<std::string> Chat::getPendingFriendMessages(UserIdentity userId)
	{
		return ResendProcessor::getInstance().getFriendResendPacket(userId);
	}

	std::vector<std::string> Chat::getPendingGroupMessages()
	{
		return ResendProcessor::getInstance().getGroupResendPacket();
	}

	void Chat::setLogfile(std::string fileName)
	{
		Logger::getInstance().init(fileName);
		Log(module, "Initialized Chat with user " << ResourceManager::getInstance().getUserId());
	}




    ApiStatus Chat::activateOrDeactivateUserAccount(bool isAccountActivate)
	{
		startServices();
		Log(module, "Deactivating user:" << ResourceManager::getInstance().getUserId());
		
		auto packetTimeId = generatePacketId();
        BuiltPacket activateOrDeactivateAccountPacket = packetBuilder->makeActivateOrDeactivateUserPacket(ResourceManager::getInstance().getUserId(), packetTimeId.packetId, isAccountActivate, ResourceManager::getInstance().getDeviceType());

		std::shared_ptr< ChatConnection> connection = ResourceManager::getInstance().getOfflineConnection();
		ResendProcessor::DestinationType destination = ResendProcessor::DestinationType::Offline;
        connection->sendToOfflineServer(activateOrDeactivateAccountPacket.byteArray);

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
        ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, activateOrDeactivateAccountPacket.byteArray, activateOrDeactivateAccountPacket.packet, connection, destination));
		
		return{ packetTimeId.packetId };
	}


    ApiStatus Chat::getUserInfo(UserIdentity friendId)
    {
        startServices();
        Log(module, "getUserInfo senderId:" << ResourceManager::getInstance().getUserId());

        auto packetTimeId = generatePacketId();
        BuiltPacket userInfoPacket = packetBuilder->makeGetUserInfoPacket(ResourceManager::getInstance().getUserId(), friendId, packetTimeId.packetId, ResourceManager::getInstance().getDeviceType());

        std::shared_ptr< ChatConnection> connection = ResourceManager::getInstance().getOfflineConnection();
        ResendProcessor::DestinationType destination = ResendProcessor::DestinationType::Offline;
        connection->sendToOfflineServer(userInfoPacket.byteArray);

        Log(module, "Adding " << packetTimeId.packetId << " for resend");
        ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, userInfoPacket.byteArray, userInfoPacket.packet, connection, destination));

        return{ packetTimeId.packetId };
    }


	void Chat::registerEventHandler(std::shared_ptr< IChatEventHandler> eventHandler)
	{
		startServices();
		Log(module, "Registered event handler");
		EventProcessor::getInstance().setEventHandler(eventHandler);
		EventProcessor::getInstance().push(ChatEvent(ChatEvent::EVENT_HANDLER_ATTACHED, nullptr), Priority::l5);
	}

	void Chat::unregisterEventHandler()
	{
		startServices();
		Log(module, "Unregister event handler");
		EventProcessor::getInstance().unsetEventHandler();
	}

	std::shared_ptr< FriendInformation> Chat::getFriendInformation(UserIdentity userId, UserIdentity friendId)
	{
		
		auto friendInformation = ResourceManager::getInstance().getFriendInfo(userId, friendId);

		if (!friendInformation){
			Log(module, "Chat::getFriendInformation FRIEND INFORMATION NOT FOUND");
			return nullptr;
		}

		auto connection = friendInformation->getConnection();

		if (!connection){
			Log(module, "Connection not found");
			return nullptr;
		}

		std::string friendRegisterServerAddress = connection->getRegisterServerAddress();
		int friendRegisterServerPort = connection->getRegisterServerPort();
		int friendChatServerPort = connection->getChatServerPort();
		int friendStatus = friendInformation->getStatus();
		int friendMood = friendInformation->getMood();
		int friendDeviceType = friendInformation->getDeviceType();
		bool blockStatus = friendInformation->getIsFriendBlocked();
		std::string friendName = friendInformation->getFriendName();
		std::string friendUrl = friendInformation->getFriendUrl();
		int profileType = friendInformation->getProfileType();

		return std::make_shared<FriendInformation>(friendRegisterServerAddress, friendRegisterServerPort, friendChatServerPort, friendDeviceType, friendStatus, friendMood, blockStatus, friendName, friendUrl, profileType);
	}

	std::shared_ptr< GroupInformation> Chat::getGroupInformation(GroupIdentity groupId)
	{
		
		auto groupConnection = ResourceManager::getInstance().getGroupConnection(groupId);

		if (!groupConnection){
			Log(module, "GROUP CONNECTION NOT FOUND");
			return nullptr;
		}

		std::string registerServerIp = groupConnection->getRegisterServerAddress();
		int registerServerPort = groupConnection->getRegisterServerPort();
		int bindingPort = groupConnection->getChatServerPort();

		auto groupKeepalivePacket = KeepaliveProcessor::getInstance().getGroupKeepalivePacket(groupId);

		return std::make_shared<GroupInformation>(groupId, registerServerIp, registerServerPort, bindingPort, groupKeepalivePacket.lastActivityTime);
	}

	std::vector<UserIdentity> Chat::getRegisteredFriendsList(UserIdentity userId)
	{

		return ResourceManager::getInstance().getAllRegisteredFriendIDs(userId);
	}

	std::vector<std::shared_ptr< GroupInformation>> Chat::getRegisteredGroupList()
	{
		
		std::vector<std::shared_ptr< GroupInformation>> groupInformationList;
		std::vector<KeepaliveProcessor::GroupKeepalivePacket> groupKeepaliveList =
			KeepaliveProcessor::getInstance().getAllGroupKeepalivePacket();

		for (std::vector<KeepaliveProcessor::GroupKeepalivePacket>::size_type i = 0; i < groupKeepaliveList.size(); i++)
		{
			auto groupConnection = ResourceManager::getInstance().getGroupConnection(groupKeepaliveList[i].groupId);
			if (!groupConnection)
			{
				continue;
			}

			std::string registerServerIp = groupConnection->getRegisterServerAddress();
			int registerServerPort = groupConnection->getRegisterServerPort();
			int bindingPort = groupConnection->getChatServerPort();

			groupInformationList.push_back(std::make_shared<GroupInformation>(groupKeepaliveList[i].groupId, registerServerIp, registerServerPort, bindingPort, groupKeepaliveList[i].lastActivityTime));
		}

		return groupInformationList;
	}

	DataCounter Chat::getDataSentReceived(){
		
		long long dataSent = ResourceManager::getInstance().getSocket()->getSocketDataSent();
		long long dataReceived = PacketReceiver::getInstance().getDataReceived();
		return{ dataSent, dataReceived };
	}

	void Chat::cleanUp(int mood)
	{
		Log(module, "Cleaning up with mood " << mood);

		sendUnregisterForRegisteredSessions(mood);

		stopServices();

		EventProcessor::getInstance().clear();

		KeepaliveProcessor::getInstance().clear();

		PacketProcessor::getInstance().clear();

		ResendProcessor::getInstance().clear();

		ResourceManager::getInstance().clear();



		PacketReceiver::getInstance().clearSocketList();

		ResourceManager::getInstance().clearOfflineConnection();

		ResourceManager::getInstance().clearSocket();
	}

	void Chat::clearRegisteredSessions(int mood)
	{
		
		sendUnregisterForRegisteredSessions(mood);
		KeepaliveProcessor::getInstance().clear();
	}

	void Chat::sendUnregisterForRegisteredSessions(int mood)
	{
		Log(module, "Send unregiseter for all sessions");

        std::vector<std::shared_ptr< FriendInfo>> friendConnections = ResourceManager::getInstance().getAllFriendConnection();
		std::vector<std::shared_ptr< GroupInfo>> groupConnections = ResourceManager::getInstance().getAllGroupInfo();
		std::vector<std::shared_ptr< RoomInfo>> roomConnections = ResourceManager::getInstance().getAllRoomConnection();

		const int maxSendTime = 3;

		for (std::vector<std::shared_ptr< FriendInfo>>::size_type sendTime = 0; sendTime < maxSendTime; sendTime++)
		{
			for (std::vector<std::shared_ptr< FriendInfo>>::size_type i = 0; i < friendConnections.size(); i++)
			{
				if (!friendConnections[i])
				{
					continue;
				}

				if (friendConnections[i]->getIsFriendBlocked())
				{
					continue;
				}

				if (friendConnections[i]->getStatus() == OnlineStatus::ONLINE)
				{
					PacketTimeId packetTimeId = generatePacketId();
					Log(module, "Sending unregister to friend " << friendConnections[i]->getFriendId());
					auto builtPacket = packetBuilder->makeFriendUnregister(friendConnections[i]->getUserId(), friendConnections[i]->getFriendId(), packetTimeId.packetId, OnlineStatus::AWAY, mood);
					if (!builtPacket.byteArray)
					{
						Log(module, "Packet builder error");
						continue;
					}

					auto connection = friendConnections[i]->getConnection();
					if (!connection)
					{
						continue;
					}

					connection->sendToRegisterServer(builtPacket.byteArray);
				}

				if (sendTime == maxSendTime - 1){
					ResourceManager::getInstance().removeFriendInfo(friendConnections[i]->getUserId(), friendConnections[i]->getFriendId());
				}
			}

			for (std::vector<std::shared_ptr< GroupInfo>>::size_type i = 0; i < groupConnections.size(); i++)
			{
				if (!groupConnections[i])
				{
					continue;
				}

				PacketTimeId packetTimeId = generatePacketId();
				GroupIdentity groupId = groupConnections[i]->groupId;
				Log(module, "Sending unregister to group " << groupId);
				auto builtPacket = packetBuilder->makeGroupUnregister(ResourceManager::getInstance().getUserId(), groupId, packetTimeId.packetId, OnlineStatus::AWAY, mood);
				if (!builtPacket.byteArray)
				{
					Log(module, "Packet builder error");
					continue;
				}

				auto connection = groupConnections[i]->groupConnection;
				if (!connection)
				{
					continue;
				}

				connection->sendToRegisterServer(builtPacket.byteArray);

				if (sendTime == maxSendTime - 1){
                    ResourceManager::getInstance().removeGroupRegistration(groupId);
                    ResourceManager::getInstance().removeGroupConnection(groupId);
				}
			}

			for (std::vector<std::shared_ptr< RoomInfo>>::size_type i = 0; i < roomConnections.size(); i++)
			{
				if (!roomConnections[i])
				{
					continue;
				}

				PacketTimeId packetTimeId = generatePacketId();
				std::string roomId = roomConnections[i]->getRoomId();
				Log(module, "Sending unregister to room " << roomId);
				auto builtPacket = packetBuilder->makePublicRoomUnregisterPacket(ResourceManager::getInstance().getUserId(), roomId, packetTimeId.packetId, roomConnections[i]->getAnonymousId(), roomConnections[i]->getRingId());
				if (!builtPacket.byteArray)
				{
					Log(module, "Packet builder error");
					continue;
				}

				auto connection = roomConnections[i]->getConnection();
				if (!connection)
				{
					continue;
				}

				connection->sendToRegisterServer(builtPacket.byteArray);

				if (sendTime == maxSendTime - 1){
					ResourceManager::getInstance().removeRoomInfo(roomId);
				}
			}
#ifndef WINDOWS_PHONE_8
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
#else
			Sleep(200);
#endif
		}
	}

	bool Chat::isExistsValidKey(std::string &packetId, UserIdentity friendId, GroupIdentity groupId)
	{
		if (ResourceManager::getInstance().getEncryptionDecryptionKey()->size() > 0) {
			return true;
		}
		else
		{
			auto eventPacketDTO = std::make_shared<PacketDTO>();
			eventPacketDTO->setPacketID(packetId);

			if (groupId == 0)
			{
				eventPacketDTO->setFriendIdentity(friendId);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_FAILED_TO_SEND, eventPacketDTO));
			}
			else
			{
				eventPacketDTO->setGroupId(groupId);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_FAILED_TO_SEND, eventPacketDTO));
			}

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_PASSWORD, eventPacketDTO));

			return false;
		}
	}

	ApiStatus Chat::friendFileTransferSessionRequest(UserIdentity userId, UserIdentity friendId, FileIdentity fileId){

		Log(module, "Requesting File Session for userId: " << userId << " friendId: " << friendId);
		startServices();
		auto packetTimeId = generatePacketId();

		auto builtPacket = packetBuilder->makeFriendFileSessionRequestPacket(userId, friendId, packetTimeId.packetId, fileId);

		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
		if (!friendInfo)
		{
			Log(module, "Connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}
		auto connection = friendInfo->getConnection();
		auto sendCode = connection->sendToRegisterServer(builtPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Register));

		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::friendFileTransferStreamRequest(UserIdentity userId, UserIdentity friendId, FileIdentity fileId)
	{
		auto packetId = generatePacketId().packetId;
		startServices();
		Log(module, "Requesting File Stream from userId: " << userId << " friendId: " << friendId);

		auto builtPacket = packetBuilder->makeFriendFileStreamRequestPacket(userId, friendId, packetId, fileId, true, 0);

		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
		if (!friendInfo)
		{
			Log(module, "Connection not found");
			return{ packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto connection = friendInfo->getConnection();
		auto sendCode = connection->sendToChatServer(builtPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Chat));

		return{ packetId };
	}

	ApiStatus Chat::groupFileTransferSessionRequest(GroupIdentity groupId, FileIdentity fileId)
	{
		Log(module, "Requesting File Session for groupId - " << groupId);
		startServices();
		std::string packetId = generatePacketId().packetId;

		BuiltPacket builtPacket = packetBuilder->makeGroupFileSessionRequest(ResourceManager::getInstance().getUserId(), groupId, packetId, fileId);
		if (!builtPacket.byteArray){
			Log(module, "Packet Builder Error");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
		if (!connection){
			Log(module, "connection not found for group: " << groupId);
			return{ packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto sendCode = connection->sendToRegisterServer(builtPacket.byteArray);
		if (sendCode < 0){
			Log(module, "Socket Error");
		}

		Log(module, "Adding " << packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Register));

		return{ packetId };
	}

	ApiStatus Chat::groupFileTransferStreamRequest(UserIdentity friendId, GroupIdentity groupId, FileIdentity fileId)
	{
		Log(module, "Requesting File Stream for groupId - " << groupId << " friendId: " << friendId);
		startServices();
		std::string packetId = generatePacketId().packetId;

		BuiltPacket fileStreamRequest = packetBuilder->makeGroupFileStreamRequest(ResourceManager::getInstance().getUserId(), friendId, groupId, packetId, fileId, true, 0);
		if (!fileStreamRequest.byteArray){
			Log(module, "Packet Builder Error");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
		if (!connection){
			Log(module, "connection not found for group: " << groupId);
			return{ packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto sendCode = connection->sendToChatServer(fileStreamRequest.byteArray);
		if (sendCode < 0){
			Log(module, "Socket Error");
		}

		Log(module, "Adding " << packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, fileStreamRequest.byteArray, fileStreamRequest.packet, connection, ResendProcessor::Chat));

		return{ packetId };
	}

	ApiStatus Chat::getFriendChatMessage(UserIdentity userId, UserIdentity friendId, std::string &packetId){
		Log(module, "Getting Friend Chat Message for user: " << userId << " && friendId: " << friendId);

		startServices();

		auto builtPacket = packetBuilder->makeFriendGetChatMessagePacket(userId, friendId, packetId, ResourceManager::getInstance().getDeviceType());
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getOfflineConnection();
		if (!connection){
			Log(module, "Offline connection not found");
			return{ packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Offline));

		return{ packetId };
	}

	ApiStatus Chat::getGroupChatMessage(GroupIdentity groupId, std::string &packetId){
		Log(module, "Getting Group Chat Message for groupId: " << groupId);

		startServices();

		auto builtPacket = packetBuilder->makeGroupGetChatMessagePacket(ResourceManager::getInstance().getUserId(), groupId, packetId, ResourceManager::getInstance().getDeviceType());
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getOfflineConnection();
		if (!connection){
			Log(module, "Offline connection not found");
			return{ packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Offline));

		return{ packetId };
	}

	ApiStatus Chat::getGroupMessageSeenList(GroupIdentity groupId, std::string &packetId){
		Log(module, "Getting Group Chat Message Seen List for groupId: " << groupId);

		startServices();

		auto packetTimeId = generatePacketId();

		auto builtPacket = packetBuilder->makeGroupChatGetMessageSeenListRequest(ResourceManager::getInstance().getUserId(), groupId, packetTimeId.packetId, packetId, ResourceManager::getInstance().getDeviceType());
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getGroupConnection(groupId);
		if (!connection){
			Log(module, "connection not found for group: " << groupId);
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto sendCode = connection->sendToChatServer(builtPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Chat));

		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::getConversationList(UserIdentity userId, ConversationType conversationType, int startIndex, int limit, long long friendOrGroupId)
	{
		Log(module, "Get conversation list: user: " << userId << " conversation type: " << conversationType << " startIndex: " << startIndex << " limit: " << limit << " friendOrGroupId: " << friendOrGroupId);
		startServices();

		PacketTimeId packetTimeId = generatePacketId();

		auto builtPacket = packetBuilder->makeOfflineGetConversationList(userId, packetTimeId.packetId, startIndex, limit, conversationType, friendOrGroupId, ResourceManager::getInstance().getDeviceType(), SDK_VERSION);
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getOfflineConnection();
		if (!connection){
			Log(module, "Offline connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Offline));

		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::deleteConversation(UserIdentity userId, std::vector<ConversationDTO> &conversationList)
	{
		Log(module, "delete conversation list for user: " << userId);
		startServices();

		PacketTimeId packetTimeId = generatePacketId();

		auto builtPacket = packetBuilder->makeOfflineDeleteConversationRequest(userId, packetTimeId.packetId, conversationList, ResourceManager::getInstance().getDeviceType());
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getOfflineConnection();
		if (!connection){
			Log(module, "Offline connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Offline));

		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::markConversationSeen(UserIdentity userId, std::vector<ConversationDTO> &conversationList)
	{
		Log(module, "Mark conversation seen for user: " << userId);
		startServices();

		PacketTimeId packetTimeId = generatePacketId();

		auto builtPacket = packetBuilder->makeOfflineMarkConversationSeenRequest(userId, packetTimeId.packetId, conversationList, ResourceManager::getInstance().getDeviceType());
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getOfflineConnection();
		if (!connection){
			Log(module, "Offline connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Offline));

		return{ packetTimeId.packetId };
	}

	void Chat::updateUserPassword(std::string password)
	{
        startServices();

		if (password.empty())
		{
			auto eventPacketDTO = std::make_shared<PacketDTO>();
			eventPacketDTO->setPacketID(generatePacketId().packetId);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_PASSWORD, eventPacketDTO));
			password = "wrong password";
		}

		Log(module, "Password update request with new password: " << password);

		ResourceManager::getInstance().setEncryptionDecryptionKey(std::make_shared<ByteArray>(password));

		std::unordered_map<std::string, std::shared_ptr< ChatConnection>> alreadyRequestedConnection;

		auto friendConnections = ResourceManager::getInstance().getAllFriendConnection();
		auto groupConnections = ResourceManager::getInstance().getAllGroupInfo();

		std::string ip_port;

		for (size_t i = 0; i < friendConnections.size(); i++)
		{
			auto connection = friendConnections[i]->getConnection();

			if (connection)
			{
				ip_port = connection->getRegisterServerAddress() + "_" + ResourceManager::toString(connection->getRegisterServerPort());
			}

			if (!ip_port.empty())
			{
				alreadyRequestedConnection[ip_port] = connection;
			}
		}

		for (size_t i = 0; i < groupConnections.size(); i++)
		{
			auto connection = groupConnections[i]->groupConnection;

			if (connection)
			{
				ip_port = connection->getRegisterServerAddress() + "_" + ResourceManager::toString(connection->getRegisterServerPort());
			}

			if (!ip_port.empty())
			{
				alreadyRequestedConnection[ip_port] = connection;
			}
		}

		std::string retPacketId;

		for (auto it = alreadyRequestedConnection.begin(); it != alreadyRequestedConnection.end(); it++)
		{
			auto connection = it->second;

			PacketTimeId packetTimeId = generatePacketId();

			retPacketId = packetTimeId.packetId;

			auto builtPacket = packetBuilder->makeUserPasswordUpdateRequest(ResourceManager::getInstance().getUserId(), packetTimeId.packetId);
			if (!builtPacket.byteArray)
			{
				Log(module, "Packet builder error");
				continue;
			}

			auto sendCode = connection->sendToRegisterServer(builtPacket.byteArray);

			if (sendCode < 0)
			{
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetTimeId.packetId << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Register));
		}

		alreadyRequestedConnection.clear();

		return;
	}

	// Public Room Chat

	ApiStatus Chat::registerPublicRoomChat(RoomIdentity &roomId, std::string &memberName, std::string &memberUrl, UserIdentity ringId){
		Log(module, "Registering Public Room Chat at Room ID: " << roomId << " memberName: " << memberName << " ringId: " << ringId);

		startServices();

		auto packetTimeId = generatePacketId();

		auto connection = ResourceManager::getInstance().getOfflineConnection();

		if (memberName.size() > 127) {
			memberName = memberName.substr(0, 127);
		}

		BuiltPacket builtPacket = packetBuilder->makeOfflinePublicGetRoomIPPort(ResourceManager::getInstance().getUserId(), roomId, packetTimeId.packetId, ResourceManager::getInstance().getDeviceType());

		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Offline));

		auto roomInfo = std::make_shared<RoomInfo>(roomId, nullptr, memberName, memberUrl, 0, ringId);
		ResourceManager::getInstance().addRoomInfo(roomInfo);

		return{ packetTimeId.packetId };

	}

	ApiStatus Chat::sendPublicRoomChat(std::string &packetId, RoomIdentity roomId, int messageType, std::string &message, long long messageDate, std::string &memberFullName, std::string &memberProfileUrl)
	{
		Log(module, "Send Public Room Chat to roomId " << roomId << " . message " << message);

		startServices();

		size_t fixedLength = LEN_PACKET_TYPE + LEN_USER_IDENTITY + LEN_ROOM_IDENTITY_LENGTH + (int)roomId.length() + LEN_PACKETID_LENGTH + (int)packetId.length() + LEN_MESSAGE_TYPE + LEN_MESSAGE_LENGTH + LEN_MESSAGE_DATE + LEN_ROOM_FULL_NAME_LENGTH + LEN_MEMBER_PROFILE_URL_LENGTH;
		size_t availableMsgLength = CHAT_MESSAGE_MAX_SIZE - fixedLength;

		int numberOfBrokenChatMessage;
		int startIndex = 0;
		std::string brokenMessage;

		if (memberFullName.size() > 127) {
			memberFullName = memberFullName.substr(0, 127);
		}

		if (message.length() > availableMsgLength) {
			numberOfBrokenChatMessage = ceil(((double)message.length() / (double)availableMsgLength));

			for (int chunkNumber = 0; chunkNumber < numberOfBrokenChatMessage; chunkNumber++){
				brokenMessage = message.substr(startIndex, availableMsgLength);
				startIndex += availableMsgLength;

				sendOrEditBrokenPublicRoomChat(PUBLIC_ROOM_CHAT_MESSAGE_BROKEN, roomId, packetId, numberOfBrokenChatMessage, chunkNumber, messageType, brokenMessage, messageDate, memberFullName, memberProfileUrl);
			}
		}
		else{

			auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
			if (!roomInfo)
			{
				Log(module, "Room Info Not Found for roomId: " + roomId);
				auto eventPacketDTO = std::make_shared<PacketDTO>();
				eventPacketDTO->setPacketID(packetId);
				eventPacketDTO->setRoomId(roomId);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_CHECK_SERVER_ADDRESS_FOR_ROOM, eventPacketDTO));
				return{ packetId, ChatError::CONNECTION_NOT_FOUND };
			}

			BuiltPacket builtPacket = packetBuilder->makePublicRoomChatMessagePacket(ResourceManager::getInstance().getUserId(), roomId, packetId, messageType, message, messageDate, memberFullName, memberProfileUrl);
			if (!builtPacket.byteArray)
			{
				Log(module, "Packet builder error");
				return{ packetId, ChatError::PACKET_BUILDER_ERROR };
			}

			auto connection = roomInfo->getConnection();

			if (!connection){
				Log(module, "Room Connection Not Found for roomId: " + roomId);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_CHECK_SERVER_ADDRESS_FOR_ROOM, builtPacket.packet));
				return{ packetId, ChatError::CONNECTION_NOT_FOUND };
			}

			auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
			if (sendCode < 0){
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetId << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Chat));
		}
		KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(roomId);

		return{ packetId };

	}

	ApiStatus Chat::editPublicRoomChat(std::string &packetId, RoomIdentity roomId, int messageType, std::string &message, long long messageDate, std::string &memberFullName, std::string &memberProfileUrl){

		Log(module, "Edit Public Room Chat to roomId " << roomId << " . message " << message);

		startServices();

		size_t fixedLength = LEN_PACKET_TYPE + LEN_USER_IDENTITY + LEN_ROOM_IDENTITY_LENGTH + (int)roomId.length() + LEN_PACKETID_LENGTH + (int)packetId.length() + LEN_MESSAGE_TYPE + LEN_MESSAGE_LENGTH + LEN_MESSAGE_DATE;
		size_t availableMsgLength = CHAT_MESSAGE_MAX_SIZE - fixedLength;

		int numberOfBrokenChatMessage;
		int startIndex = 0;
		std::string brokenMessage;

		if (memberFullName.size() > 127) {
			memberFullName = memberFullName.substr(0, 127);
		}

		if (message.length() > availableMsgLength) {
			numberOfBrokenChatMessage = ceil(((double)message.length() / (double)availableMsgLength));

			for (int chunkNumber = 0; chunkNumber < numberOfBrokenChatMessage; chunkNumber++){
				brokenMessage = message.substr(startIndex, availableMsgLength);
				startIndex += availableMsgLength;

				sendOrEditBrokenPublicRoomChat(PUBLIC_ROOM_CHAT_MESSAGE_BROKEN_EDIT, roomId, packetId, numberOfBrokenChatMessage, chunkNumber, messageType, brokenMessage, messageDate, memberFullName, memberProfileUrl);
			}
		}
		else{
			auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
			if (!roomInfo)
			{
				Log(module, "Room Info Not Found for roomId: " + roomId);
				auto eventPacketDTO = std::make_shared<PacketDTO>();
				eventPacketDTO->setPacketID(packetId);
				eventPacketDTO->setRoomId(roomId);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_CHECK_SERVER_ADDRESS_FOR_ROOM, eventPacketDTO));
				return{ packetId, ChatError::CONNECTION_NOT_FOUND };
			}

			BuiltPacket builtPacket = packetBuilder->makePublicRoomChatMessageEditPacket(ResourceManager::getInstance().getUserId(), roomId, packetId, messageType, message, messageDate, memberFullName, memberProfileUrl);
			if (!builtPacket.byteArray)
			{
				Log(module, "Packet builder error");
				return{ packetId, ChatError::PACKET_BUILDER_ERROR };
			}

			auto connection = roomInfo->getConnection();

			if (!connection){
				Log(module, "Room Connection Not Found for roomId: " + roomId);
				EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_CHECK_SERVER_ADDRESS_FOR_ROOM, builtPacket.packet));
				return{ packetId, ChatError::CONNECTION_NOT_FOUND };
			}

			auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
			if (sendCode < 0){
				Log(module, "Socket returned " << sendCode);
			}

			Log(module, "Adding " << packetId << " for resend");
			ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Chat));
		}
		KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(roomId);

		return{ packetId };

	}


	ApiStatus Chat::getRoomList(int startIndex, int limit){
		Log(module, "Requesting Public Room List. Start Index = " << startIndex << " Limit = " << limit);

		startServices();

		auto packetTimeId = generatePacketId();
		BuiltPacket builtPacket = packetBuilder->makeOfflinePublicRoomListRequest(ResourceManager::getInstance().getUserId(), packetTimeId.packetId, startIndex, limit, ResourceManager::getInstance().getDeviceType());
		if (!builtPacket.byteArray){
			Log(module, "Packet Builder Error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getOfflineConnection();
		if (!connection){
			Log(module, "Room connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);
		if (sendCode < 0){
			Log(module, "Socket Error");
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Offline));

		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::getRoomListWithHistory(int startIndex, int limit){
		Log(module, "Requesting Public Room List With History. Start Index = " << startIndex << " Limit = " << limit);

		startServices();

		auto packetTimeId = generatePacketId();
		BuiltPacket builtPacket = packetBuilder->makeOfflinePublicRoomListWithHistoryRequest(ResourceManager::getInstance().getUserId(), packetTimeId.packetId, startIndex, limit, ResourceManager::getInstance().getDeviceType());
		if (!builtPacket.byteArray){
			Log(module, "Packet Builder Error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getOfflineConnection();
		if (!connection){
			Log(module, "Room connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);
		if (sendCode < 0){
			Log(module, "Socket Error");
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Offline));

		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::getRoomMemberList(RoomIdentity roomId, std::string pagingState, int limit){
		Log(module, "Getting Public Chat room member list: " << roomId << " pagingState: " << pagingState << " limit: " << limit);
		startServices();

		auto packetTimeId = generatePacketId();
		auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);

		if (!roomInfo)
		{
			Log(module, "Room Info Not Found for roomId: " + roomId);
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto connection = roomInfo->getConnection();
		if (!connection)
		{
			Log(module, "Connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}



		BuiltPacket builtPacket = packetBuilder->makePublicChatGetMemberList(ResourceManager::getInstance().getUserId(), roomId, packetTimeId.packetId, pagingState, limit, ResourceManager::getInstance().appVersion);
		if (!builtPacket.byteArray) {
			Log(module, "Packet Builder Error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto sendCode = connection->sendToChatServer(builtPacket.byteArray);

		if (sendCode < 0){
			Log(module, "Socket Error");
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Chat));

		KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(roomId);

		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::searchRoomList(std::string &searchName, std::string &country, std::string &category, int startIndex, int limit){
		Log(module, "Search Public Room List. Search Name: " << searchName << "Start Index: " << startIndex << " Limit: " << limit << " Country: " << country << " Category: " << category);

		startServices();

		auto packetTimeId = generatePacketId();
		BuiltPacket builtPacket = packetBuilder->makeOfflinePublicRoomListSearchRequest(ResourceManager::getInstance().getUserId(), packetTimeId.packetId, startIndex, limit, searchName, country, category, ResourceManager::getInstance().getDeviceType());
		if (!builtPacket.byteArray){
			Log(module, "Packet Builder Error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getOfflineConnection();
		if (!connection){
			Log(module, "Room connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);
		if (sendCode < 0){
			Log(module, "Socket Error");
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Offline));

		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::getPublicChatLikeMemberList(RoomIdentity roomId, std::string &packetId, UserIdentity lastLikerId, int limit){
		Log(module, "Getting public room chat like memberList. RoomID: " << roomId << " PacketId: " << packetId);

		startServices();

		auto packetTimeId = generatePacketId();

		auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);

		if (!roomInfo)
		{
			Log(module, "Room Info Not Found for roomId: " + roomId);
			return{ packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto connection = roomInfo->getConnection();
		if (!connection)
		{
			Log(module, "Connection not found");
			return{ packetId, ChatError::CONNECTION_NOT_FOUND };
		}


		BuiltPacket builtPacket = packetBuilder->makePublicChatLikeMemberListRequest(ResourceManager::getInstance().getUserId(), roomId, packetTimeId.packetId, packetId, lastLikerId, limit, ResourceManager::getInstance().appVersion);
		if (!builtPacket.byteArray) {
			Log(module, "Packet Builder Error");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto sendCode = connection->sendToChatServer(builtPacket.byteArray);

		if (sendCode < 0){
			Log(module, "Socket Error");
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Chat));

		KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(roomId);

		return{ packetId };
	}

	ApiStatus Chat::getPublicChatRoomCategoryList(std::string &lastCategory, int limit){
		Log(module, "Getting public room chat category list. Paging State - " << lastCategory);

		startServices();

		auto packetTimeId = generatePacketId();
		BuiltPacket builtPacket = packetBuilder->makeOfflinePublicChatCategoryListRequest(ResourceManager::getInstance().getUserId(), packetTimeId.packetId, lastCategory, limit, ResourceManager::getInstance().getDeviceType());
		if (!builtPacket.byteArray){
			Log(module, "Packet Builder Error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getOfflineConnection();
		if (!connection){
			Log(module, "Room connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);
		if (sendCode < 0){
			Log(module, "Socket Error");
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Offline));

		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::unregisterPublicRoomChat(RoomIdentity roomId){
		Log(module, "Unregistering public room chat " << roomId);
		

		auto packetTimeId = generatePacketId();
		auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
		if (!roomInfo)
		{
			Log(module, "Room Info Not Found for roomId: " + roomId);
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto connection = roomInfo->getConnection();
		if (!connection)
		{
			Log(module, "Connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto builtPacket = packetBuilder->makePublicRoomUnregisterPacket(ResourceManager::getInstance().getUserId(), roomId, packetTimeId.packetId, roomInfo->getAnonymousId(), roomInfo->getRingId());
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		connection->sendToRegisterServer(builtPacket.byteArray);
		connection->sendToRegisterServer(builtPacket.byteArray);
		connection->sendToRegisterServer(builtPacket.byteArray);

		ResourceManager::getInstance().removeRoomInfo(roomId);

		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::typingPublicRoomChat(RoomIdentity roomId){

		Log(module, "Typing public room chat. roomId " << roomId);

		startServices();

		auto packetTimeId = generatePacketId();

		auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);

		if (!roomInfo)
		{
			Log(module, "Room Info Not Found for roomId: " + roomId);
			auto eventPacketDTO = std::make_shared<PacketDTO>();
			eventPacketDTO->setPacketID(packetTimeId.packetId);
			eventPacketDTO->setRoomId(roomId);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_CHECK_SERVER_ADDRESS_FOR_ROOM, eventPacketDTO));
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto memberName = roomInfo->getMemberName();

		auto typingPublicRoomChatPacket = packetBuilder->makePublicRoomChatTypingPacket(ResourceManager::getInstance().getUserId(), roomId, memberName, ResourceManager::getInstance().getDeviceType());
		if (!typingPublicRoomChatPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = roomInfo->getConnection();
		if (!connection)
		{
			Log(module, "Connection not found");
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_CHECK_SERVER_ADDRESS_FOR_ROOM, typingPublicRoomChatPacket.packet));
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto sendCode = connection->sendToChatServer(typingPublicRoomChatPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(roomId);
		return{ packetTimeId.packetId };
	}

	bool Chat::isExistsRoomConnection(RoomIdentity roomId){
		
		auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
		if (roomInfo == nullptr){
			Log(module, "Room Info does not exist for room id " << roomId);
			return false;
		}

		if (roomInfo->getConnection()){
			Log(module, "Room Connection exists for room id " << roomId);
			return true;
		}
		else return false;
	}

	ApiStatus Chat::getRoomInformation(RoomIdentity roomId){
		Log(module, "Get Room Information request. roomId = " << roomId);

		startServices();

		auto packetTimeId = generatePacketId();
		BuiltPacket builtPacket = packetBuilder->makeOfflineRoomInformationRequest(ResourceManager::getInstance().getUserId(), roomId, packetTimeId.packetId, ResourceManager::getInstance().getDeviceType());
		if (!builtPacket.byteArray){
			Log(module, "Packet Builder Error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getOfflineConnection();
		if (!connection){
			Log(module, "Offline connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);
		if (sendCode < 0){
			Log(module, "Socket Error");
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Offline));

		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::requestRoomChatHistory(RoomIdentity roomId, std::string &packetId, int year, int month, int direction, int limit)
	{
		Log(module, "Get Room history request. roomId = " << roomId << " packetId = " << packetId << " year = " << year << " month = " << month);

		startServices();

		//    auto packetTimeId = generatePacketId(); 
		BuiltPacket builtPacket = packetBuilder->makeOfflineRoomGetHistoryPacket(ResourceManager::getInstance().getUserId(), roomId, packetId, month, year, direction, limit, ResourceManager::getInstance().getDeviceType(), ResourceManager::getInstance().appVersion);
		if (!builtPacket.byteArray){
			Log(module, "Packet Builder Error");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getOfflineConnection();
		if (!connection){
			Log(module, "Offline connection not found");
			return{ packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);
		if (sendCode < 0){
			Log(module, "Socket Error");
		}

		Log(module, "Adding " << packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Offline));

		KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(roomId);

		return{ packetId };
	}

	void Chat::enterPublicChatScreen(RoomIdentity roomId){
		Log(module, "Entering Public Chat Screen.");
		startServices();
		KeepaliveProcessor::getInstance().updateIsOnPublicChatScreen(roomId, true);
	}

	void Chat::exitPublicChatScreen(RoomIdentity roomId){
		Log(module, "Exiting Public Chat Screen.");
		startServices();
		KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(roomId);
		KeepaliveProcessor::getInstance().updateIsOnPublicChatScreen(roomId, false);
	}

	ApiStatus Chat::deletePublicChatMessage(RoomIdentity &roomId, std::vector<std::string> &packetIds){
		Log(module, "Delete Public Chat Message.");
		startServices();
		auto packetTimeId = generatePacketId();
		auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
		if (!roomInfo)
		{
			Log(module, "Room Info Not Found for roomId: " + roomId);
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto connection = roomInfo->getConnection();
		if (!connection)
		{
			Log(module, "Connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto builtPacket = packetBuilder->makePublicRoomChatDeleteMessagePacket(ResourceManager::getInstance().getUserId(), roomId, packetTimeId.packetId, packetIds);
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}
		auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
		if (sendCode < 0){
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Chat));

		KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(roomId);

		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::likePublicChatMessage(std::string &packetId, RoomIdentity &roomId, UserIdentity messageSenderId){
		Log(module, "Like Public Chat Message. RoomId: " << roomId + " PacketId: " << packetId + " MessageSenderId: " << messageSenderId);
		startServices();

		auto packetTimeId = generatePacketId();

		auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
		if (!roomInfo)
		{
			Log(module, "Room Info Not Found for roomId: " + roomId);
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto connection = roomInfo->getConnection();
		if (!connection)
		{
			Log(module, "Connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto builtPacket = packetBuilder->makePublicRoomChatLikeMessagePacket(ResourceManager::getInstance().getUserId(), roomId, packetTimeId.packetId, messageSenderId, packetId);
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
		if (sendCode < 0){
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Chat));

		KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(roomId);

		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::unlikePublicChatMessage(std::string &packetId, RoomIdentity &roomId, UserIdentity messageSenderId){
		Log(module, "Unlike Public Chat Message. RoomId: " << roomId << " PacketId: " << packetId << " MessageSenderId: " << messageSenderId);
		startServices();

		auto packetTimeId = generatePacketId();

		auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
		if (!roomInfo)
		{
			Log(module, "Room Info Not Found for roomId: " + roomId);
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto connection = roomInfo->getConnection();
		if (!connection)
		{
			Log(module, "Connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto builtPacket = packetBuilder->makePublicRoomChatUnlikeMessagePacket(ResourceManager::getInstance().getUserId(), roomId, packetTimeId.packetId, messageSenderId, packetId);
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
		if (sendCode < 0){
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Chat));

		KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(roomId);

		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::reportPublicChatMessage(std::string &packetId, RoomIdentity &roomId, UserIdentity messageSenderId, std::string &reportMessage){
		Log(module, "Report Public Chat Message.");
		startServices();

		auto packetTimeId = generatePacketId();

		auto roomInfo = ResourceManager::getInstance().getRoomInfo(roomId);
		if (!roomInfo)
		{
			Log(module, "Room Info Not Found for roomId: " + roomId);
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto connection = roomInfo->getConnection();
		if (!connection)
		{
			Log(module, "Connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto builtPacket = packetBuilder->makePublicRoomChatReportMessagePacket(ResourceManager::getInstance().getUserId(), roomId, packetTimeId.packetId, reportMessage, messageSenderId, packetId);
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
		if (sendCode < 0){
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Chat));

		KeepaliveProcessor::getInstance().resetPublicRoomKeepalive(roomId);

		return{ packetTimeId.packetId };
	}

	//Anonymous friend chat
	ApiStatus Chat::registerAnonymousFriendChat(UserIdentity selfAnonymousUserId, UserIdentity friendAnonymousId, UserIdentity originalFriendId, std::string registerServerAddress, int registerServerPort, int deviceType, std::string deviceToken, int appType, int status, int mood)
	{
		startServices();
		Log(module, "Register anonymous friend, selfAnonymousId: " << selfAnonymousUserId << " friendAnonymousId: " << friendAnonymousId << " originalFriendId:" << originalFriendId << " registerserver address and port: " << registerServerAddress << " : " << registerServerPort);
		auto connection = std::make_shared<ChatConnection>(ResourceManager::getInstance().getSocket());
		connection->setRegisterServer(registerServerAddress, registerServerPort);

        std::string userName = ResourceManager::getInstance().getUserName();
		ResendProcessor::getInstance().updateConnection(selfAnonymousUserId, friendAnonymousId, connection);  //set offline server connection for friendId
		ResourceManager::getInstance().addFriendInfo(std::make_shared<FriendInfo>(selfAnonymousUserId, userName, friendAnonymousId, "", "", connection, deviceType, deviceToken, appType, status, mood, false, false, ResourceManager::getInstance().getServerSyncedTime(), 0, 0/*profileType*/));

		AnonymousUserIdentity anonymousUserIdentity;
		anonymousUserIdentity.selfAnonymousId = selfAnonymousUserId;
		anonymousUserIdentity.originalFriendId = originalFriendId;

		ResourceManager::getInstance().addAnonymousUser(friendAnonymousId, anonymousUserIdentity);

		PacketTimeId packetTimeId = generatePacketId();
		BuiltPacket builtPacket = packetBuilder->makeAnonymousFriendChatRegisterPacket(selfAnonymousUserId, friendAnonymousId, packetTimeId.packetId, ResourceManager::getInstance().getDeviceType());
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto sendCode = connection->sendToRegisterServer(builtPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Register));
		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::unregisterAnonymousFriendChat(UserIdentity userId, UserIdentity friendId, int status, int mood)
	{
		Log(module, "Unregistering Anonymous friend chat " << friendId);
		startServices();
		auto packetTimeId = generatePacketId();
		auto friendInfo = ResourceManager::getInstance().getFriendInfo(userId, friendId);
		if (!friendInfo)
		{
			Log(module, "Connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto builtPacket = packetBuilder->makeAnonymousFriendChatUnregisterPacket(ResourceManager::getInstance().getAnonymousUser(friendId).selfAnonymousId, friendId, packetTimeId.packetId, status, mood);
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = friendInfo->getConnection();
		auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Register, 3));
		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::getShadowIdInfo(std::vector<UserIdentity> &userIds)
	{
		Log(module, "Request shadow ID info ");
		startServices();
		auto packetTimeId = generatePacketId();

		auto builtPacket = packetBuilder->makeShadowIdInfoRequestPacket(ResourceManager::getInstance().getUserId(), packetTimeId.packetId, userIds, ResourceManager::getInstance().getDeviceType());
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = ResourceManager::getInstance().getOfflineConnection();
		auto sendCode = connection->sendToOfflineServer(builtPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Offline));
		return{ packetTimeId.packetId };
	}

	//Live-stream-chat
	ApiStatus Chat::registerLiveStreamChat(UserIdentity publisherId, std::string registerServerAddress, int registerServerPort, std::string fullName)
	{
		Log(module, "Registering Live stream Chat with Publisher ID: " << publisherId);

		startServices();

		auto packetTimeId = generatePacketId();

		std::shared_ptr< ChatConnection> connection = nullptr;

		auto liveStreamChatInfo = ResourceManager::getInstance().getLiveStreamChatInfo(publisherId);
		if (!liveStreamChatInfo)
		{
			connection = std::make_shared<ChatConnection>(ResourceManager::getInstance().getSocket());
			connection->setRegisterServer(registerServerAddress, registerServerPort);

			ResourceManager::getInstance().addLiveStreamChatInfo(std::make_shared<LiveStreamChatInfo>(publisherId, connection, fullName));
		}
		else
		{
			connection = liveStreamChatInfo->getConnection();
			connection->setRegisterServer(registerServerAddress, registerServerPort);
		}

		ResourceManager::getInstance().setLatestPublisherId(publisherId);

		BuiltPacket builtPacket = packetBuilder->makeLiveStreamChatRegisterPacket(ResourceManager::getInstance().getUserId(), publisherId, packetTimeId.packetId, ResourceManager::getInstance().getDeviceType());

		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto sendCode = connection->sendToRegisterServer(builtPacket.byteArray);

		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetTimeId.packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Register));

		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::unregisterLiveStreamChat(UserIdentity publisherId, int onlineStatus, int onlineMood)
	{
		startServices();

		Log(module, "Unregistering live stream stream chat with publisher: " << publisherId << " ;online status: " << onlineStatus << " online mood: " << onlineMood);

		auto packetTimeId = generatePacketId();
		auto liveStreamChatInfo = ResourceManager::getInstance().getLiveStreamChatInfo(publisherId);
		if (!liveStreamChatInfo)
		{
			Log(module, "Connection not found");
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto builtPacket = packetBuilder->makeLiveStreamChatUnregisterPacket(ResourceManager::getInstance().getUserId(), publisherId, packetTimeId.packetId, onlineStatus, onlineMood);
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = liveStreamChatInfo->getConnection();
		auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetTimeId.packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::DestinationType::Register, 3));
		KeepaliveProcessor::getInstance().removeLiveStreamChatKeepalive(publisherId);
		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::typingLiveStreamChat(UserIdentity publisherId)
	{
		Log(module, "Typing live stream chat. publisherId: " << publisherId);

		startServices();

		auto packetTimeId = generatePacketId();

		auto typingLiveStreamChatPacket = packetBuilder->makeLiveStreamChatMessageTypingPacket(ResourceManager::getInstance().getUserId(), publisherId, ResourceManager::getInstance().getDeviceType());
		if (!typingLiveStreamChatPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetTimeId.packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto liveStreamChatInfo = ResourceManager::getInstance().getLiveStreamChatInfo(publisherId);
		if (!liveStreamChatInfo)
		{
			Log(module, "Connection not found");
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_LIVE_STREAM_CHAT, typingLiveStreamChatPacket.packet));
			return{ packetTimeId.packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto connection = liveStreamChatInfo->getConnection();
		auto sendCode = connection->sendToChatServer(typingLiveStreamChatPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		KeepaliveProcessor::getInstance().resetLiveStreamChatKeepalive(publisherId);
		return{ packetTimeId.packetId };
	}

	ApiStatus Chat::sendLiveStreamChat(std::string &packetId, UserIdentity publisherId, int messageType, std::string &message, long long messageDate)
	{
		Log(module, "Send live stream Chat to publisher " << publisherId << " . message " << message);

		startServices();

		auto liveStreamChatInfo = ResourceManager::getInstance().getLiveStreamChatInfo(publisherId);
		if (!liveStreamChatInfo)
		{
			Log(module, "Live stream chat Info Not Found for publisherId: " << publisherId);
			auto eventPacketDto = std::make_shared<PacketDTO>();
			eventPacketDto->setPacketID(packetId);
			eventPacketDto->setPublisherId(publisherId);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_LIVE_STREAM_CHAT, eventPacketDto));
			return{ packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		std::string userName = liveStreamChatInfo->getUserName();
		BuiltPacket builtPacket = packetBuilder->makeLiveStreamChatMessagePacket(ResourceManager::getInstance().getUserId(), publisherId, packetId, messageType, message, messageDate, userName);
		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}


		auto connection = liveStreamChatInfo->getConnection();

		auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Chat));

		KeepaliveProcessor::getInstance().resetLiveStreamChatKeepalive(publisherId);

		return{ packetId };
	}

	ApiStatus Chat::blockUserFromLiveStreamChat(UserIdentity blockedUserId, std::string &packetId)
	{
		Log(module, "Sending blockUserFromLiveStreamChat request for blocked userId: " << blockedUserId);

		startServices();

		UserIdentity publisherId = ResourceManager::getInstance().getUserId();
		auto liveStreamChatInfo = ResourceManager::getInstance().getLiveStreamChatInfo(publisherId);
		if (!liveStreamChatInfo)
		{
			Log(module, "Live stream chat Info Not Found for publisherId: " << publisherId);
			auto eventPacketDto = std::make_shared<PacketDTO>();
			eventPacketDto->setPacketID(packetId);
			eventPacketDto->setPublisherId(publisherId);
			EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_SERVER_ADDRESS_FOR_LIVE_STREAM_CHAT, eventPacketDto));
			return{ packetId, ChatError::CONNECTION_NOT_FOUND };
		}

		auto builtPacket = packetBuilder->makeLiveStreamChatBlockUserPacket(publisherId, blockedUserId, packetId);

		if (!builtPacket.byteArray)
		{
			Log(module, "Packet builder error in blockUserFromLiveStreamChat");
			return{ packetId, ChatError::PACKET_BUILDER_ERROR };
		}

		auto connection = liveStreamChatInfo->getConnection();

		auto sendCode = connection->sendToChatServer(builtPacket.byteArray);
		if (sendCode < 0)
		{
			Log(module, "Socket returned " << sendCode);
		}

		Log(module, "Adding " << packetId << " for resend");
		ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, builtPacket.byteArray, builtPacket.packet, connection, ResendProcessor::Chat));

		KeepaliveProcessor::getInstance().resetLiveStreamChatKeepalive(publisherId);

		return{ packetId };
	}

	void Chat::addUserPage(UserIdentity pageId)
	{
		
		ResourceManager::getInstance().addNewPage(pageId);
	}

	void Chat::removeUserPage(UserIdentity pageId)
	{
		
		ResourceManager::getInstance().removePage(pageId);
	}

	PacketTimeId Chat::generatePacketId(UserIdentity userId)
	{
		
		PacketTimeId packetTimeId = ResourceManager::getInstance().generatePacketIdInSDK(userId);
		return packetTimeId;
	}

	PacketTimeId Chat::generatePacketId(long long timeMili, UserIdentity userId)
	{
		
		PacketTimeId packetTimeId = ResourceManager::getInstance().generatePacketIdInSDK(timeMili, userId);
		return packetTimeId;
	}

	std::string Chat::version()
	{
		return "imsdk " + std::string(ResourceManager::toString(SDK_VERSION)) + " (compiled " + std::string(__TIME__) + ", " + std::string(__DATE__) + ")";
	}

	long long Chat::getCurrentServerSyncedTime()
	{
		
		return ResourceManager::getInstance().getServerSyncedTime();
	}

	long long Chat::UUIDToTime(std::string UUID){

		
		return ResourceManager::getInstance().UUIDToTime(UUID);

	}

	bool Chat::sendFriendChatMedia(UserIdentity userId, UserIdentity friendId, std::string &packetId, int mediaType, const std::string filePath, std::string caption,
		int widthOrFileSize, int heightOrDuration, int secretTimeout, long long messageDate, bool isSecretVisible) {
		Log(module, "Start Chat Media Transfer. for userId: " << userId << " FriendID: " << friendId << " File: " << filePath);

        startServices();
        
		std::string fileExtension = ipvcore::generic::utills::get_suffix(filePath, ".");
		std::string fileName = packetId + "." + fileExtension;

		std::shared_ptr< ipvcore::cloud::RequestParams> requestParams =
			std::make_shared<ipvcore::cloud::RequestParams>();

		requestParams->file_path = filePath;
		requestParams->key = fileName;
		requestParams->strategy = ipvcore::cloud::Strategy::CHUNKED;

        if (mediaType == IMAGE_FILE_FROM_GALLERY || mediaType == IMAGE_FILE_FROM_CAMERA || mediaType == GIF_FILE) {
			requestParams->domain = ipvcore::cloud::Domain::CHAT_IMAGE;
		}
		else if (mediaType == AUDIO_FILE) {
			requestParams->domain = ipvcore::cloud::Domain::CHAT_AUDIO;
		}
		else if (mediaType == VIDEO_FILE) {
			requestParams->domain = ipvcore::cloud::Domain::CHAT_VIDEO;
		}

		std::shared_ptr< CloudUploadNotificationHandler> cloudUploadNotificationHandler =
			std::make_shared<CloudUploadNotificationHandler>();
		cloudUploadNotificationHandler->setTransferType(TransferType::FRIEND_CHAT_MEDIA);
		cloudUploadNotificationHandler->setUserId(userId);
		cloudUploadNotificationHandler->setFriendId(friendId);
		cloudUploadNotificationHandler->setFileName(fileName);
		cloudUploadNotificationHandler->setFileDomainType(mediaType);
		cloudUploadNotificationHandler->setCaption(caption);
		cloudUploadNotificationHandler->setWidthOrFileSize(widthOrFileSize);
		cloudUploadNotificationHandler->setHeightOrDuration(heightOrDuration);
		cloudUploadNotificationHandler->setPacketId(packetId);
		cloudUploadNotificationHandler->setSecretTimeout(secretTimeout);
		cloudUploadNotificationHandler->setMessageDate(messageDate);
		cloudUploadNotificationHandler->setSecretVisible(isSecretVisible);

		CloudNotificationManager::getInstance().addCloudNotificationHandler(packetId, cloudUploadNotificationHandler);

		std::shared_ptr< ipvcore::cloud::UploadResponse> uploadResponse =
			ipvcore::cloud::Manager::instance()->upload(requestParams, cloudUploadNotificationHandler);

		Log(module, "Init upload response message: " << uploadResponse->message());

		return uploadResponse->success();
	}

	bool Chat::downloadFriendChatMedia(UserIdentity userId, UserIdentity friendId, std::string &packetId, const std::string manifestUrl, int mediaType, int secretTimeout) {
		Log(module, "Download Chat Media from userId: " << userId << " friendId " << friendId << ". Cloud File Manifest Url: " << manifestUrl);

        startServices();
        
		std::string cloudFileName = ipvcore::generic::utills::get_suffix(manifestUrl, "/");

		std::size_t found = cloudFileName.find_first_of("_");
		std::string fileName = cloudFileName.substr(found + 1);

		auto downloadNotificationHandler = std::static_pointer_cast<CloudDownloadNotificationHandler>(
			CloudNotificationManager::getInstance().getCloudNotificationHandler(packetId));

		if (downloadNotificationHandler) {
			Log(module, "Download in progress. fileName: " << fileName);
			return true; //Download already in progress
		}

		std::string targetFileWithPath = internetchecker::InternetChecker::getInstance().getIpListFilePath() +
			ipvcore::generic::file_system::kDirSep + fileName;

        if (mediaType == IMAGE_FILE_FROM_GALLERY || mediaType == IMAGE_FILE_FROM_CAMERA || mediaType == GIF_FILE) {
			if (secretTimeout == 0){
				targetFileWithPath = ResourceManager::getInstance().getChatImageDownloadPath() + ipvcore::generic::file_system::kDirSep + fileName;
			}
			else {
				targetFileWithPath = ResourceManager::getInstance().getSecretChatImageDownloadPath() + ipvcore::generic::file_system::kDirSep + fileName;
			}
		}
		else if (mediaType == AUDIO_FILE) {
			if (secretTimeout == 0){
				targetFileWithPath = ResourceManager::getInstance().getChatAudioDownloadPath() + ipvcore::generic::file_system::kDirSep + fileName;
			}
			else {
				targetFileWithPath = ResourceManager::getInstance().getSecretChatAudioDownloadPath() + ipvcore::generic::file_system::kDirSep + fileName;
			}
		}
		else if (mediaType == VIDEO_FILE) {
			if (secretTimeout == 0){
				targetFileWithPath = ResourceManager::getInstance().getChatVideoDownloadPath() + ipvcore::generic::file_system::kDirSep + fileName;
			}
			else {
				targetFileWithPath = ResourceManager::getInstance().getSecretChatVideoDownloadPath() + ipvcore::generic::file_system::kDirSep + fileName;
			}
		}

		std::ifstream targetFile(targetFileWithPath.c_str());

		if (targetFile.is_open()) {
			targetFile.close();

			auto downloadAlreadyCompletedPacket = std::make_shared<PacketDTO>();

			downloadAlreadyCompletedPacket->setFriendIdentity(friendId);
			downloadAlreadyCompletedPacket->setLocalFilePath(targetFileWithPath);
			downloadAlreadyCompletedPacket->setPacketID(packetId);
			downloadAlreadyCompletedPacket->setTimeout(secretTimeout);
			downloadAlreadyCompletedPacket->setFileDomainType(mediaType);

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::CHAT_MEDIA_DOWNLOAD_COMPLETED, downloadAlreadyCompletedPacket));
			Log(module, "Chat media download completed already or in progress. fileName: " << fileName);
			return true;
		}

		std::shared_ptr< ipvcore::cloud::RequestParams> download_params =
			std::make_shared<ipvcore::cloud::RequestParams>();

		download_params->file_path = targetFileWithPath;
		download_params->key = manifestUrl;
		download_params->strategy = ipvcore::cloud::Strategy::NON_BLOCKING;
		download_params->domain = ipvcore::cloud::Domain::CHAT_IMAGE;       // not used, but a value is required here

		std::shared_ptr< CloudDownloadNotificationHandler> cloudDownloadNotificationHandler =
			std::make_shared<CloudDownloadNotificationHandler>();
		cloudDownloadNotificationHandler->setTransferType(TransferType::FRIEND_CHAT_MEDIA);
		cloudDownloadNotificationHandler->setUserId(userId);
		cloudDownloadNotificationHandler->setFriendId(friendId);
		cloudDownloadNotificationHandler->setFileName(fileName);
		cloudDownloadNotificationHandler->setPacketId(packetId);
		cloudDownloadNotificationHandler->setSecretTimeout(secretTimeout);
		cloudDownloadNotificationHandler->setTargetFilePath(targetFileWithPath);
		cloudDownloadNotificationHandler->setFileDomainType(mediaType);
		cloudDownloadNotificationHandler->setChunkedTransfer(false);

		CloudNotificationManager::getInstance().addCloudNotificationHandler(packetId, cloudDownloadNotificationHandler);

		std::shared_ptr< ipvcore::cloud::DownloadResponse> download_response =
			ipvcore::cloud::Manager::instance()->download(download_params, cloudDownloadNotificationHandler);

		Log(module, "Cloud download response: " << download_response->message());

		return download_response->success();
	}

	bool Chat::acceptChatMedia(std::string packetId) {
		auto downloadNotificationHandler = std::static_pointer_cast<CloudDownloadNotificationHandler>(
			CloudNotificationManager::getInstance().getCloudNotificationHandler(packetId));

		if (downloadNotificationHandler) {
			downloadNotificationHandler->setDownloadAllowed(true);
			return true;
		}

		return false;
	}

	bool Chat::sendGroupChatMedia(GroupIdentity groupId, std::string &packetId, int mediaType, const std::string filePath, std::string caption,
		int widthOrFileSize, int heightOrDuration, long long messageDate) {
		Log(module, "Start Group Chat Media Transfer. GroupID: " << groupId << " File: " << filePath);

        startServices();
        
		std::string fileExtension = ipvcore::generic::utills::get_suffix(filePath, ".");
		std::string fileName = packetId + "." + fileExtension;

		std::shared_ptr< ipvcore::cloud::RequestParams> requestParams =
			std::make_shared<ipvcore::cloud::RequestParams>();

		requestParams->file_path = filePath;
		requestParams->key = fileName;
		requestParams->strategy = ipvcore::cloud::Strategy::CHUNKED;

        if (mediaType == IMAGE_FILE_FROM_GALLERY || mediaType == IMAGE_FILE_FROM_CAMERA || mediaType == GIF_FILE) {
			requestParams->domain = ipvcore::cloud::Domain::CHAT_IMAGE;
		}
		else if (mediaType == AUDIO_FILE) {
			requestParams->domain = ipvcore::cloud::Domain::CHAT_AUDIO;
		}
		else if (mediaType == VIDEO_FILE) {
			requestParams->domain = ipvcore::cloud::Domain::CHAT_VIDEO;
		}

		std::shared_ptr< CloudUploadNotificationHandler> cloudUploadNotificationHandler =
			std::make_shared<CloudUploadNotificationHandler>();
		cloudUploadNotificationHandler->setTransferType(TransferType::GROUP_CHAT_MEDIA);
		cloudUploadNotificationHandler->setGroupId(groupId);
		cloudUploadNotificationHandler->setFileName(fileName);
		cloudUploadNotificationHandler->setFileDomainType(mediaType);
		cloudUploadNotificationHandler->setCaption(caption);
		cloudUploadNotificationHandler->setWidthOrFileSize(widthOrFileSize);
		cloudUploadNotificationHandler->setHeightOrDuration(heightOrDuration);
		cloudUploadNotificationHandler->setPacketId(packetId);
		cloudUploadNotificationHandler->setMessageDate(messageDate);

		CloudNotificationManager::getInstance().addCloudNotificationHandler(packetId, cloudUploadNotificationHandler);

		std::shared_ptr< ipvcore::cloud::UploadResponse> uploadResponse =
			ipvcore::cloud::Manager::instance()->upload(requestParams, cloudUploadNotificationHandler);

		Log(module, "Init upload response message: " << uploadResponse->message());

		return uploadResponse->success();
	}

	bool Chat::downloadGroupChatMedia(GroupIdentity groupId, UserIdentity friendId, std::string &packetId, const std::string manifestUrl, int mediaType) {
		Log(module, "Download Group Chat Media for groupId " << groupId << ". Cloud File Manifest Url: " << manifestUrl);
        startServices();
        
		std::string cloudFileName = ipvcore::generic::utills::get_suffix(manifestUrl, "/");

		std::size_t found = cloudFileName.find_first_of("_");
		std::string fileName = cloudFileName.substr(found + 1);

		auto downloadNotificationHandler = std::static_pointer_cast<CloudDownloadNotificationHandler>(
			CloudNotificationManager::getInstance().getCloudNotificationHandler(packetId));

		if (downloadNotificationHandler) {
			Log(module, "Download in progress. fileName: " << fileName);
			return true; //Download already in progress
		}

		std::string targetFileWithPath = internetchecker::InternetChecker::getInstance().getIpListFilePath() +
			ipvcore::generic::file_system::kDirSep + fileName;

        if (mediaType == IMAGE_FILE_FROM_GALLERY || mediaType == IMAGE_FILE_FROM_CAMERA || mediaType == GIF_FILE) {
			targetFileWithPath = ResourceManager::getInstance().getChatImageDownloadPath() + ipvcore::generic::file_system::kDirSep + fileName;
		}
		else if (mediaType == AUDIO_FILE) {
			targetFileWithPath = ResourceManager::getInstance().getChatAudioDownloadPath() + ipvcore::generic::file_system::kDirSep + fileName;
		}
		else if (mediaType == VIDEO_FILE) {
			targetFileWithPath = ResourceManager::getInstance().getChatVideoDownloadPath() + ipvcore::generic::file_system::kDirSep + fileName;
		}

		std::ifstream targetFile(targetFileWithPath.c_str());

		if (targetFile.is_open()) {
			targetFile.close();

			auto downloadAlreadyCompletedPacket = std::make_shared<PacketDTO>();

			downloadAlreadyCompletedPacket->setGroupId(groupId);
			downloadAlreadyCompletedPacket->setFriendIdentity(friendId);
			downloadAlreadyCompletedPacket->setLocalFilePath(targetFileWithPath);
			downloadAlreadyCompletedPacket->setPacketID(packetId);
			downloadAlreadyCompletedPacket->setFileDomainType(mediaType);

			EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_MEDIA_DOWNLOAD_COMPLETED, downloadAlreadyCompletedPacket));
			Log(module, "Group chat media download completed already or in progress. fileName: " << fileName);
			return true;
		}

		std::shared_ptr< ipvcore::cloud::RequestParams> download_params =
			std::make_shared<ipvcore::cloud::RequestParams>();

		download_params->file_path = targetFileWithPath;
		download_params->key = manifestUrl;
		download_params->strategy = ipvcore::cloud::Strategy::NON_BLOCKING;
		download_params->domain = ipvcore::cloud::Domain::CHAT_IMAGE;       // not used, but a value is required here

		std::shared_ptr< CloudDownloadNotificationHandler> cloudDownloadNotificationHandler =
			std::make_shared<CloudDownloadNotificationHandler>();
		cloudDownloadNotificationHandler->setTransferType(TransferType::GROUP_CHAT_MEDIA);
		cloudDownloadNotificationHandler->setGroupId(groupId);
		cloudDownloadNotificationHandler->setFriendId(friendId);
		cloudDownloadNotificationHandler->setFileName(fileName);
		cloudDownloadNotificationHandler->setPacketId(packetId);
		cloudDownloadNotificationHandler->setTargetFilePath(targetFileWithPath);
		cloudDownloadNotificationHandler->setFileDomainType(mediaType);
		cloudDownloadNotificationHandler->setChunkedTransfer(false);

		CloudNotificationManager::getInstance().addCloudNotificationHandler(packetId, cloudDownloadNotificationHandler);

		std::shared_ptr< ipvcore::cloud::DownloadResponse> download_response =
			ipvcore::cloud::Manager::instance()->download(download_params, cloudDownloadNotificationHandler);

		Log(module, "Cloud download responese" << download_response->message());

		return download_response->success();
	}

	void Chat::cancelChatMediaTransfer(std::string &packetId) {
		Log(module, "Cancelling media transfer. packetId: " << packetId);

        startServices();
        
		auto notificationHandler = CloudNotificationManager::getInstance().getCloudNotificationHandler(packetId);

		if (!notificationHandler) {
			Log(module, "No ongoing chat media transfer found with packetId: " << packetId);
			return;
		}
		else {
			auto downloadNotificationHandler = std::static_pointer_cast<CloudDownloadNotificationHandler>(notificationHandler);
			downloadNotificationHandler->setCanceledBy(downloadNotificationHandler->getUserId());

			ipvcore::cloud::Manager::instance()->cancel(notificationHandler);
			Log(module, "manager cancel called from userid: " << downloadNotificationHandler->getUserId());
		}
	}

	std::vector<std::string> Chat::getPendingChatMediaList(ConversationType conversationType, bool isUpload, bool isChunked) {
		return CloudNotificationManager::getInstance().getPendingChatMediaList(conversationType, isUpload, isChunked);
	}

	bool Chat::isChatMediaTransferInProgress(std::string packetId) {

		Log(module, "Calling isChatMediaTransferInProgress with packet id: " << packetId);

		bool inProgress{ false };

		auto cloudNotificationHandler = std::static_pointer_cast<CloudNotificationHandler>(CloudNotificationManager::getInstance().getCloudNotificationHandler(packetId));

		if (cloudNotificationHandler)
		{
			if (cloudNotificationHandler->isUploadHandler() == true) {
				inProgress = true;
			}
			else {
				auto cloudDownloadNotificationHandler = std::static_pointer_cast<CloudDownloadNotificationHandler>(cloudNotificationHandler);
				if ((cloudDownloadNotificationHandler->isDownloadAllowed() && cloudDownloadNotificationHandler->isChunkPacketReceived()) || cloudDownloadNotificationHandler->isChunkedTransfer() == false)
				{
					inProgress = true;
				}
			}
		}
		else
		{
			Log(module, "No ongoing chat media transfer found with packetId: " << packetId);
		}

		return inProgress;
	}

	void Chat::updateAppSessionID(std::string appSessionId) {
		Log(module, "Updating App Session ID with: " << appSessionId);
        ResourceManager::getInstance().setAuthSessionID(appSessionId);
        ipvcore::cloud::Manager::instance()->set_storage_token(appSessionId);
	}

	std::string Chat::generatePacketId_v2()
	{
		static const std::string charset = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

		std::stringstream sin;

		sin << std::chrono::system_clock::now().time_since_epoch().count();
		int len = 8;
		for (int i = 0; i < len; i++)
		{
			sin << charset[rand() % charset.size()];
		}

		return sin.str();
	}
    
    std::string Chat::getRingIdPackageName()
    {
        std::string packageName = "dpn/sjohje/sjoh";
        
        for (int i=0; i<packageName.size(); i++)
        {
            packageName[i] = packageName[i]-1;
        }
        
        return packageName;
    }
    
    std::string Chat::getRingIncPackageName()
    {
        std::string packageName = "dpn/sjohje/sjohjod";
        
        for (int i=0; i<packageName.size(); i++)
        {
            packageName[i] = packageName[i]-1;
        }
        
        return packageName;
    }

	GroupIdentity Chat::generateGroupId()
	{
		long long timeSeconds = ResourceManager::getInstance().gettime() / 1000;

		long long groupID = timeSeconds * 1000000 + ResourceManager::getInstance().getUserId() % 1000000;

		return groupID;
	}

	void Chat::setLogEnabled(bool enableDisable)
	{
		Logger::getInstance().setLogEnabled(enableDisable);
	}

    ApiStatus Chat::getSyncedConversation(UserIdentity userId, std::string &packetId, long long lastSyncedTime)
    {
        std::stringstream hash;
        hash << "GET_SYNC_CONVERSATION_REQUEST" << userId;

        if (requestDuplicateChecker.isSafe(hash.str(), 30))
        {
            startServices();
            Log(module, "Get Synced Conversation. from userId: " << userId << " packetId: " << packetId << " lastSyncedTime: " << lastSyncedTime);

            auto getSyncedconversationPacket = packetBuilder->makeGetSyncConversationRequest(userId, packetId, lastSyncedTime, ResourceManager::getInstance().getDeviceType());
            if (!getSyncedconversationPacket.byteArray)
            {
                Log(module, "Packet builder error");
                return{ packetId, ChatError::PACKET_BUILDER_ERROR };
            }

            auto connection = ResourceManager::getInstance().getOfflineConnection();
            auto sendCode = connection->sendToOfflineServer(getSyncedconversationPacket.byteArray);
            if (sendCode < 0)
            {
                Log(module, "Socket returned " << sendCode);
            }

            Log(module, "Adding " << packetId << " for resend");
            ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, getSyncedconversationPacket.byteArray, getSyncedconversationPacket.packet, connection, ResendProcessor::Offline));

            return{ packetId };
        }

        Log(module, "A getSyncedConversation request is already in process");
        return{ "" };
    }


    ApiStatus Chat::getSyncedFriendHistoryMessage(UserIdentity userId, UserIdentity friendId, std::string &packetId, long long lastSyncedTime, int limit, int direction)
    {
        startServices();
        Log(module, "Get Synced Friend History Message. from userId: " << userId << " friendId: " << friendId << " packetId: " << packetId << " lastSyncedTime: " << lastSyncedTime);

        auto getSyncedFriendHistoryPacket = packetBuilder->makeSyncFriendHistoryMessageRequest(userId, friendId, packetId, lastSyncedTime, ResourceManager::getInstance().getDeviceType(), ResourceManager::getInstance().getAppType(), ResourceManager::getInstance().appVersion, ResourceManager::getInstance().getUserId(), limit, direction);
        if (!getSyncedFriendHistoryPacket.byteArray)
        {
            Log(module, "Packet builder error");
            return{ packetId, ChatError::PACKET_BUILDER_ERROR };
        }

        auto connection = ResourceManager::getInstance().getOfflineConnection();
        auto sendCode = connection->sendToOfflineServer(getSyncedFriendHistoryPacket.byteArray);
        if (sendCode < 0)
        {
            Log(module, "Socket returned " << sendCode);
        }

        Log(module, "Adding " << packetId << " for resend");
        ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, getSyncedFriendHistoryPacket.byteArray, getSyncedFriendHistoryPacket.packet, connection, ResendProcessor::Offline));

        return{ packetId };
    }


    ApiStatus Chat::getSyncedGroupHistoryMessage(UserIdentity userId, GroupIdentity groupId, std::string &packetId, long long lastSyncedTime, int limit, int direction)
    {
        startServices();
        Log(module, "Get Synced Group History Message. from userId: " << userId << " groupId: " << groupId << " packetId: " << packetId << " lastSyncedTime: " << lastSyncedTime);

        auto getSyncedGroupHistoryPacket = packetBuilder->makeSyncGroupHistoryMessageRequest(userId, groupId, packetId, lastSyncedTime, ResourceManager::getInstance().appVersion, ResourceManager::getInstance().getDeviceType(), limit, direction);
        if (!getSyncedGroupHistoryPacket.byteArray)
        {
            Log(module, "Packet builder error");
            return{ packetId, ChatError::PACKET_BUILDER_ERROR };
        }

        auto connection = ResourceManager::getInstance().getOfflineConnection();
        auto sendCode = connection->sendToOfflineServer(getSyncedGroupHistoryPacket.byteArray);
        if (sendCode < 0)
        {
            Log(module, "Socket returned " << sendCode);
        }

        Log(module, "Adding " << packetId << " for resend");
        ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, getSyncedGroupHistoryPacket.byteArray, getSyncedGroupHistoryPacket.packet, connection, ResendProcessor::Offline));

        return{ packetId };
    }


    ApiStatus Chat::getMyGroupListPaging(UserIdentity userId, std::string &packetId, std::string &pivotId, int limit, int direction)
    {
        startServices();
        Log(module, "Get My Group List Paging from userId: " << userId << " packetId: " << packetId << " pivotId: " << pivotId << " limit: " << limit << " direction: " << direction);

        auto getMyGroupListPagingPacket = packetBuilder->makeGetMyGroupListPagingRequest(userId, packetId, pivotId, limit, direction, ResourceManager::getInstance().getDeviceType());
        if (!getMyGroupListPagingPacket.byteArray)
        {
            Log(module, "Packet builder error");
            return{ packetId, ChatError::PACKET_BUILDER_ERROR };
        }

        auto connection = ResourceManager::getInstance().getOfflineConnection();
        auto sendCode = connection->sendToOfflineServer(getMyGroupListPagingPacket.byteArray);
        if (sendCode < 0)
        {
            Log(module, "Socket returned " << sendCode);
        }

        Log(module, "Adding " << packetId << " for resend");
        ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, getMyGroupListPagingPacket.byteArray, getMyGroupListPagingPacket.packet, connection, ResendProcessor::Offline));

        return{ packetId };
    }
    
    ApiStatus Chat::addNotice(int messageType, long long disburseTime, long long expireTime, std::string &notice, std::vector<std::string> &isoCountryList)
    {
        startServices();
        Log(module, "Add notice disburseTime: " << disburseTime << " expireTime: " << expireTime << " notice: " << notice);
        for (int i=0; i<isoCountryList.size(); i++)
        {
            Log(module, "Add notice ISO: " << isoCountryList[i]);
        }
        
        std::string packetId = generatePacketId().packetId;
        
        auto addNoticePacket = packetBuilder->makeAddNotice(ResourceManager::getInstance().getUserId(), packetId, messageType, disburseTime, expireTime, notice, isoCountryList);
        if (!addNoticePacket.byteArray)
        {
            Log(module, "Packet builder error");
            return{ packetId, ChatError::PACKET_BUILDER_ERROR };
        }
        
        auto connection = ResourceManager::getInstance().getOfflineConnection();
        auto sendCode = connection->sendToOfflineServer(addNoticePacket.byteArray);
        if (sendCode < 0)
        {
            Log(module, "Socket returned " << sendCode);
        }
        
        Log(module, "Adding " << packetId << " for resend");
        ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId, addNoticePacket.byteArray, addNoticePacket.packet, connection, ResendProcessor::Offline));
        
        return{ packetId };
    }

}
