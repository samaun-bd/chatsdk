#include <mutex>

#include "PacketTemplate.h"
#include "ResendProcessor.h"
#include "ResourceManager.h"
#include "CloudNotificationHandler.h"
#include "Logger.h"
#include "Chat.h"
#include "EventProcessor.h"

#define module "CloudMediaTransfer"

namespace imsdk {

CloudUploadNotificationHandler::CloudUploadNotificationHandler() {
    setUploadHandler(true);
    packetBuilder = std::make_shared<ChatPacketBuilder>();
}    

void CloudUploadNotificationHandler::on_complete(ipvcore::cloud::NotificationType type,
        std::string key, std::string /*file_path*/, std::shared_ptr< ipvcore::cloud::Response> response)
{
    bool isManifest{false};
    auto uploadResponse = std::static_pointer_cast<ipvcore::cloud::UploadResponse>(response);
    std::string downloadKey = uploadResponse->download_key();

    Chat::startServices();
    
    if (type == ipvcore::cloud::NotificationType::MANIFEST_FILE) {
        isManifest = true;
        
        auto manifestUploadedPacket = std::make_shared<PacketDTO>();
        
        manifestUploadedPacket->setFileChunkDownloadKey(downloadKey);
        manifestUploadedPacket->setFileDomainType(getFileDomainType());
        manifestUploadedPacket->setCaption(caption);
        manifestUploadedPacket->setWidthOrFileSize(widthOrFileSize);
        manifestUploadedPacket->setHeightOrDuration(heightOrDuration);
        manifestUploadedPacket->setPacketID(getPacketId());
        
        if(getTransferType() == TransferType::FRIEND_CHAT_MEDIA){
			manifestUploadedPacket->setUserIdentity(getUserId());
			manifestUploadedPacket->setFriendIdentity(getFriendId());
            manifestUploadedPacket->setTimeout(getSecretTimeout());
            EventProcessor::getInstance().push(ChatEvent(ChatEvent::FILE_MANIFEST_UPLOADED, manifestUploadedPacket));
        }
        else if (getTransferType() == TransferType::GROUP_CHAT_MEDIA){
            manifestUploadedPacket->setGroupId(getGroupId());
            EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_FILE_MANIFEST_UPLOADED, manifestUploadedPacket));       
        }     
    }
    
    if(getTransferType() == TransferType::FRIEND_CHAT_MEDIA)
    {
		auto friendInfo = ResourceManager::getInstance().getFriendInfo(getUserId(), getFriendId());

        if (!friendInfo) {
            Log(module, "Connection not found");
            return;
        }

        std::string chunkPacketId = getPacketId() + "_" + ResourceManager::getInstance().toString(uploadedChunkCount);
        if(isManifest){
            chunkPacketId = getPacketId() + "_" + ResourceManager::getInstance().toString(uploadedChunkCount+1);
        }
        
        BuiltPacket builtPacket = packetBuilder->makeFriendFileChunkUploadedPacket(
				getUserId(), getFriendId(), chunkPacketId,
                isManifest, key, downloadKey);

        if (!builtPacket.byteArray) {
            Log(module, "Packet builder error");
            return;
        }

        auto connection = friendInfo->getConnection();
        auto sendCode = connection->sendToChatServer(builtPacket.byteArray);

        if (sendCode < 0) {
            Log(module, "Socket returned " << sendCode);
        }
                        
        ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(chunkPacketId,
                builtPacket.byteArray, builtPacket.packet, connection,
                ResendProcessor::DestinationType::Chat, 3));
    }
    else if (getTransferType() == TransferType::GROUP_CHAT_MEDIA){
        
        auto groupConnection = ResourceManager::getInstance().getGroupConnection(getGroupId());
        
        if(!groupConnection){
            Log(module, "Error - Group connection not found for groupId: "<<getGroupId());
            return;
        }
        
        std::string chunkPacketId = getPacketId() + "_" + ResourceManager::getInstance().toString(uploadedChunkCount);
        
        if(isManifest){
            chunkPacketId = getPacketId() + "_" + ResourceManager::getInstance().toString(uploadedChunkCount+1);
        }
        
        BuiltPacket builtPacket = packetBuilder->makeGroupFileChunkUploadedPacket(
                ResourceManager::getInstance().getUserId(), getGroupId(), chunkPacketId, isManifest,
                key, downloadKey);

        if (!builtPacket.byteArray)
        {
            Log(module, "Packet builder error");
            return;
        }
             
        auto sendCode = groupConnection->sendToChatServer(builtPacket.byteArray);
        if (sendCode<0)
        {
            Log(module, "Socket returned "<<sendCode);
        }
                
        ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(chunkPacketId,
                builtPacket.byteArray, builtPacket.packet, groupConnection,
                ResendProcessor::DestinationType::Chat, 3));
    }

    if(isManifest){
        CloudNotificationManager::getInstance().removeCloudNotificationHandler(getPacketId());
    }
}

void CloudUploadNotificationHandler::on_error(ipvcore::cloud::NotificationType type,
        std::string /*key*/, std::string file_path, std::shared_ptr< ipvcore::cloud::Response> response)
{
    Log(module, "Cloud error: " << type);
    if(type == ipvcore::cloud::NotificationType::FILE_SYSTEM_ERROR)
    {
        auto fileErrorPacket = std::make_shared<PacketDTO>();
        fileErrorPacket->setPacketID(getPacketId());
        fileErrorPacket->setLocalFilePath(file_path);
        EventProcessor::getInstance().push(ChatEvent(ChatEvent::CHAT_MEDIA_TRANSFER_DIRECTORY_ERROR,
                fileErrorPacket));
    }

    if(response->message() == "Chunk Upload Error: 401 Unauthorized") //Later, this check will be based on NotificationType
    {
        auto invalidSessionErrorPacket = std::make_shared<PacketDTO>();
        invalidSessionErrorPacket->setPacketID(getPacketId());
        EventProcessor::getInstance().push(ChatEvent(ChatEvent::SHOULD_UPDATE_APP_SESSION_ID,
                invalidSessionErrorPacket));
    }

    auto transferFailedPacket = std::make_shared<PacketDTO>();

	transferFailedPacket->setUserIdentity(getUserId());
	transferFailedPacket->setFriendIdentity(getFriendId());
    transferFailedPacket->setFileDownloadId(getFileName());
    transferFailedPacket->setPacketID(getPacketId());
    transferFailedPacket->setMediaTransferTypeUpload(true);
    transferFailedPacket->setChunkedTransfer(isChunkedTransfer());
    
    if(getTransferType() == TransferType::FRIEND_CHAT_MEDIA){
        EventProcessor::getInstance().push(ChatEvent(ChatEvent::CHAT_MEDIA_TRANSFER_FAILED,
                transferFailedPacket));
    }
    else if (getTransferType() == TransferType::GROUP_CHAT_MEDIA){
        transferFailedPacket->setGroupId(getGroupId());
        EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_MEDIA_TRANSFER_FAILED,
                transferFailedPacket));        
    }
    
    CloudNotificationManager::getInstance().removeCloudNotificationHandler(getPacketId());
    Log(module, "Cloud upload error: " + response->message());
}

void CloudUploadNotificationHandler::on_chunked_upload_init(std::string /*key*/, std::string /*file_path*/,
        std::size_t chunk_count, std::size_t chunk_size, std::int64_t file_size)
{
    this->setInitChunkCount(chunk_count);
    this->setInitChunkSize(chunk_size);
    this->setInitFileSize(file_size);
    
    Chat::startServices();

    if (getTransferType() == TransferType::FRIEND_CHAT_MEDIA){
        
		auto friendInfo = ResourceManager::getInstance().getFriendInfo(getUserId(), getFriendId());

        if (!friendInfo)
        {
            Log(module, "Connection not found");
            return;
        }

        BuiltPacket builtPacket = packetBuilder->makeFriendInitChunkFileDownloadPacket(
				getUserId(), getFriendId(), getPacketId(), getFileName(),
                getInitChunkCount(), getInitChunkSize(), getInitFileSize(), getFileDomainType(), getSecretTimeout(), messageDate, isSecretVisible, caption, widthOrFileSize, heightOrDuration);

        if (!builtPacket.byteArray)
        {
            Log(module, "Packet builder error");
            return;
        }

        auto connection = friendInfo->getConnection();
        auto sendCode = connection->sendToChatServer(builtPacket.byteArray);

        if (sendCode<0)
        {
            Log(module, "Socket returned "<<sendCode);
        }
        std::string packetId = getPacketId();
        ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId,
                builtPacket.byteArray, builtPacket.packet, connection,
                ResendProcessor::DestinationType::Chat, 3));
    }
    else if (getTransferType() == TransferType::GROUP_CHAT_MEDIA){
        //add group chat media transfer code here
        auto groupConnection = ResourceManager::getInstance().getGroupConnection(getGroupId());
        
        if(!groupConnection){
            Log(module, "Error - Group connection not found for groupId: "<<getGroupId());
            return;
        }
        
        BuiltPacket builtPacket = packetBuilder->makeGroupInitChunkFileDownloadPacket(
                ResourceManager::getInstance().getUserId(), getGroupId(), getPacketId(), getFileName(),
                getInitChunkCount(), getInitChunkSize(), getInitFileSize(), getFileDomainType(), messageDate, caption, widthOrFileSize, heightOrDuration);

        if (!builtPacket.byteArray)
        {
            Log(module, "Packet builder error");
            return;
        }
             
        auto sendCode = groupConnection->sendToChatServer(builtPacket.byteArray);
        if (sendCode<0)
        {
            Log(module, "Socket returned "<<sendCode);
        }
        std::string packetId = getPacketId();
        ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId,
                builtPacket.byteArray, builtPacket.packet, groupConnection,
                ResendProcessor::DestinationType::Chat, 3));
    }
}

void CloudUploadNotificationHandler::on_progress(std::int64_t /*downloaded*/, std::int64_t /*total_download*/, std::int64_t uploaded, std::int64_t total_upload){

    double fileUploadPercentage = uploaded * 100.0 / total_upload;

    auto uploadProgressPacket = std::make_shared<PacketDTO>();

	uploadProgressPacket->setUserIdentity(getUserId());
	uploadProgressPacket->setFriendIdentity(getFriendId());
    uploadProgressPacket->setFileDownloadId(getFileName());
    uploadProgressPacket->setChunkedMediaTransferPercentage(fileUploadPercentage);
    uploadProgressPacket->setMediaTransferTypeUpload(true);
    uploadProgressPacket->setPacketID(getPacketId());

    if(getTransferType() == TransferType::FRIEND_CHAT_MEDIA){
        EventProcessor::getInstance().push(ChatEvent(ChatEvent::CHAT_MEDIA_TRANSFER_PROGRESS, uploadProgressPacket));
    }
    else if (getTransferType() == TransferType::GROUP_CHAT_MEDIA){
        uploadProgressPacket->setGroupId(getGroupId());
        EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_MEDIA_TRANSFER_PROGRESS, uploadProgressPacket));
    }
}

void CloudUploadNotificationHandler::on_cancel_completed(ipvcore::cloud::NotificationType /*type*/, std::string /*key*/, std::string /*file_path*/,
            std::shared_ptr< ipvcore::cloud::Response> response) {
    std::string packetId = getPacketId();

    auto transferCanceledPacket = std::make_shared<PacketDTO>();
	transferCanceledPacket->setUserIdentity(getUserId());
	transferCanceledPacket->setFriendIdentity(getFriendId());
    transferCanceledPacket->setFileDownloadId(getFileName());
    transferCanceledPacket->setPacketID(packetId);
    transferCanceledPacket->setMediaTransferTypeUpload(true);
    transferCanceledPacket->setChunkedTransfer(isChunkedTransfer());
    transferCanceledPacket->setOriginalUserId(getCanceledBy());

    if(getTransferType() == TransferType::FRIEND_CHAT_MEDIA){
        EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_MEDIA_TRANSFER_CANCELED,
                transferCanceledPacket));

		auto friendInfo = ResourceManager::getInstance().getFriendInfo(getUserId(), getFriendId());

        if (!friendInfo)
        {
            Log(module, "Connection not found");
            return;
        }

        BuiltPacket builtPacket = packetBuilder->makeFriendChatMediaTransferCancelPacket(
				getUserId(), getFriendId(), packetId);

        if (!builtPacket.byteArray)
        {
            Log(module, "Packet builder error");
            return;
        }
        auto connection = friendInfo->getConnection();

        auto sendCode = connection->sendToChatServer(builtPacket.byteArray);

        if (sendCode<0)
        {
            Log(module, "Socket returned "<<sendCode);
        }

        ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId,
            builtPacket.byteArray, builtPacket.packet, connection,
            ResendProcessor::DestinationType::Chat, 3));
    }
    else if (getTransferType() == TransferType::GROUP_CHAT_MEDIA){

        transferCanceledPacket->setGroupId(getGroupId());
        EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_MEDIA_TRANSFER_CANCELED,
                transferCanceledPacket));
        auto groupConnection = ResourceManager::getInstance().getGroupConnection(getGroupId());

        if(!groupConnection){
            Log(module, "Error - Group connection not found for groupId: "<<getGroupId());
            return;
        }

        BuiltPacket builtPacket = packetBuilder->makeGroupChatMediaTransferCancelPacket(
                ResourceManager::getInstance().getUserId(), getGroupId(), packetId);

        if (!builtPacket.byteArray)
        {
            Log(module, "Packet builder error");
            return;
        }

        auto sendCode = groupConnection->sendToChatServer(builtPacket.byteArray);
        if (sendCode<0)
        {
            Log(module, "Socket returned "<<sendCode);
        }

        ResendProcessor::getInstance().addResendPacket(ResendProcessor::ResendPacket(packetId,
                builtPacket.byteArray, builtPacket.packet, groupConnection,
                ResendProcessor::DestinationType::Chat, 3));
    }

    CloudNotificationManager::getInstance().removeCloudNotificationHandler(getPacketId());

    return;
}

void CloudUploadNotificationHandler::setHeightOrDuration(int heightOrDuration) {
    this->heightOrDuration = heightOrDuration;
}

void CloudUploadNotificationHandler::setWidthOrFileSize(int widthOrFileSize) {
    this->widthOrFileSize = widthOrFileSize;
}

void CloudUploadNotificationHandler::setCaption(std::string caption) {
    this->caption = caption;
}

void CloudUploadNotificationHandler::setMessageDate(long long messageDate) {
    this->messageDate = messageDate;
}

void CloudUploadNotificationHandler::setSecretVisible(bool SecretVisible) {
    isSecretVisible = SecretVisible;
}

CloudDownloadNotificationHandler::CloudDownloadNotificationHandler() {
    setUploadHandler(false);
}

void CloudDownloadNotificationHandler::on_complete(ipvcore::cloud::NotificationType type,
        std::string /*key*/, std::string /*file_path*/, std::shared_ptr< ipvcore::cloud::Response> /*response*/)
{
    if (type == ipvcore::cloud::NotificationType::COMPLETE_FILE)
    {
        auto downloadCompletedPacket = std::make_shared<PacketDTO>();

		downloadCompletedPacket->setUserIdentity(getUserId());
		downloadCompletedPacket->setFriendIdentity(getFriendId());
        downloadCompletedPacket->setLocalFilePath(targetFilePath);
        downloadCompletedPacket->setPacketID(getPacketId());
        downloadCompletedPacket->setMessageType(getFileDomainType());
        downloadCompletedPacket->setTimeout(getSecretTimeout());
        downloadCompletedPacket->setFileDomainType(getFileDomainType());

        if(getTransferType() == TransferType::FRIEND_CHAT_MEDIA){
            downloadCompletedPacket->setTimeout(getSecretTimeout());
            EventProcessor::getInstance().push(ChatEvent(ChatEvent::CHAT_MEDIA_DOWNLOAD_COMPLETED, downloadCompletedPacket));
        }
        else if (getTransferType() == TransferType::GROUP_CHAT_MEDIA){
            downloadCompletedPacket->setGroupId(getGroupId());
            EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_MEDIA_DOWNLOAD_COMPLETED, downloadCompletedPacket));       
        }
        
        CloudNotificationManager::getInstance().removeCloudNotificationHandler(getPacketId());
    }
}

void CloudDownloadNotificationHandler::on_error(ipvcore::cloud::NotificationType type,
        std::string /*key*/, std::string file_path, std::shared_ptr< ipvcore::cloud::Response> response)
{

    Log(module, "Cloud error: " << type);
    if(type == ipvcore::cloud::NotificationType::FILE_SYSTEM_ERROR)
    {
        auto fileErrorPacket = std::make_shared<PacketDTO>();
        fileErrorPacket->setPacketID(getPacketId());
        fileErrorPacket->setLocalFilePath(file_path);
        EventProcessor::getInstance().push(ChatEvent(ChatEvent::CHAT_MEDIA_TRANSFER_DIRECTORY_ERROR,
                fileErrorPacket));
    }

    if(!chunkPacketReceived || (chunkPacketReceived && downloadAllowed) || (chunkPacketReceived && ResourceManager::getInstance().isAutoDownloadEnabled())){
        auto transferFailedPacket = std::make_shared<PacketDTO>();

		transferFailedPacket->setUserIdentity(getUserId());
		transferFailedPacket->setFriendIdentity(getFriendId());
        transferFailedPacket->setFileDownloadId(getFileName());
        transferFailedPacket->setPacketID(getPacketId());
        transferFailedPacket->setMediaTransferTypeUpload(false);
        transferFailedPacket->setChunkedTransfer(isChunkedTransfer());

        if(getTransferType() == TransferType::FRIEND_CHAT_MEDIA){
            EventProcessor::getInstance().push(ChatEvent(ChatEvent::CHAT_MEDIA_TRANSFER_FAILED,
                    transferFailedPacket));
        }
        else if (getTransferType() == TransferType::GROUP_CHAT_MEDIA){
            transferFailedPacket->setGroupId(getGroupId());
            EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_MEDIA_TRANSFER_FAILED,
                    transferFailedPacket));
        }
    }
    
    Log(module, "Cloud download error: " << response->message());

    CloudNotificationManager::getInstance().removeCloudNotificationHandler(getPacketId());
}

void CloudDownloadNotificationHandler::on_progress(std::int64_t downloaded, std::int64_t total_download, std::int64_t /*uploaded*/, std::int64_t /*total_upload*/){

        double fileDownloadPercentage = downloaded * 100.0 / total_download;

        auto downloadProgressPacket = std::make_shared<PacketDTO>();
		
		downloadProgressPacket->setUserIdentity(getUserId());
		downloadProgressPacket->setFriendIdentity(getFriendId());
        downloadProgressPacket->setFileDownloadId(getFileName());
        downloadProgressPacket->setChunkedMediaTransferPercentage(fileDownloadPercentage);
        downloadProgressPacket->setMediaTransferTypeUpload(false);
        downloadProgressPacket->setPacketID(getPacketId());

        if(getTransferType() == TransferType::FRIEND_CHAT_MEDIA){
            EventProcessor::getInstance().push(ChatEvent(ChatEvent::CHAT_MEDIA_TRANSFER_PROGRESS, downloadProgressPacket));
        }
        else if (getTransferType() == TransferType::GROUP_CHAT_MEDIA){
            downloadProgressPacket->setGroupId(getGroupId());
            EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_MEDIA_TRANSFER_PROGRESS, downloadProgressPacket));
        }
}

void CloudDownloadNotificationHandler::on_cancel_completed(ipvcore::cloud::NotificationType /*type*/, std::string /*key*/, std::string /*file_path*/,
            std::shared_ptr< ipvcore::cloud::Response> response) {

    auto transferCanceledPacket = std::make_shared<PacketDTO>();

	transferCanceledPacket->setUserIdentity(getUserId());
	transferCanceledPacket->setFriendIdentity(getFriendId());
    transferCanceledPacket->setFileDownloadId(getFileName());
    transferCanceledPacket->setPacketID(getPacketId());
    transferCanceledPacket->setMediaTransferTypeUpload(false);
    transferCanceledPacket->setChunkedTransfer(isChunkedTransfer());
    transferCanceledPacket->setOriginalUserId(getCanceledBy());

    if(getTransferType() == TransferType::FRIEND_CHAT_MEDIA){
        EventProcessor::getInstance().push(ChatEvent(ChatEvent::FRIEND_CHAT_MEDIA_TRANSFER_CANCELED,
                transferCanceledPacket));
    }
    else if (getTransferType() == TransferType::GROUP_CHAT_MEDIA){
        transferCanceledPacket->setGroupId(getGroupId());
        EventProcessor::getInstance().push(ChatEvent(ChatEvent::GROUP_CHAT_MEDIA_TRANSFER_CANCELED,
                transferCanceledPacket));
    }

    CloudNotificationManager::getInstance().removeCloudNotificationHandler(getPacketId());

    return;
}

void CloudDownloadNotificationHandler::setDownloadAllowed(bool downloadAllowed) {
    this->downloadAllowed = downloadAllowed;
}

bool CloudDownloadNotificationHandler::isDownloadAllowed() const {
    return downloadAllowed;
}

void CloudDownloadNotificationHandler::setTargetFilePath(std::string targetFilePath) {
    this->targetFilePath = targetFilePath;
}

std::string CloudDownloadNotificationHandler::getTargetFilePath() const {
    return targetFilePath;
}

void CloudDownloadNotificationHandler::setChunkPacketReceived(bool chunkPacketReceived) {
    this->chunkPacketReceived = chunkPacketReceived;
}

bool CloudDownloadNotificationHandler::isChunkPacketReceived() const {
    return chunkPacketReceived;
}

CloudNotificationManager& CloudNotificationManager::getInstance() {
    static CloudNotificationManager cloudNotificationManager;

    return cloudNotificationManager;
}

void CloudNotificationManager::addCloudNotificationHandler(std::string packetId,
        std::shared_ptr< ipvcore::cloud::NotificationHandler> notificationHandler) {

    notificationHandlerMutex.lock();
    
    notificationHandlerMap[packetId] = notificationHandler;
        
    notificationHandlerMutex.unlock();
}

void CloudNotificationManager::removeCloudNotificationHandler(std::string packetId) {
    
    notificationHandlerMutex.lock();
    
    auto it = notificationHandlerMap.find(packetId);
    
    if (it != notificationHandlerMap.end())
    {
        notificationHandlerMap.erase(it);
    }
    
    notificationHandlerMutex.unlock();
}

std::shared_ptr< ipvcore::cloud::NotificationHandler> CloudNotificationManager::getCloudNotificationHandler(
        std::string packetId) {
 
    std::shared_ptr< ipvcore::cloud::NotificationHandler> cloudNotificationHandler = nullptr;
    
    notificationHandlerMutex.lock();
    
    auto it = notificationHandlerMap.find(packetId);
    if (it != notificationHandlerMap.end())
    {
        cloudNotificationHandler = (*it).second;
    }
    
    notificationHandlerMutex.unlock();
    
    return cloudNotificationHandler;
}

std::vector<std::string> CloudNotificationManager::getPendingChatMediaList(ConversationType conversationType, bool isUpload, bool isChunked) {

    std::vector<std::string> pendingChatMediaList;

    TransferType transferType;
    if(conversationType == ConversationType::FRIEND_ID) {
        transferType = TransferType::FRIEND_CHAT_MEDIA;
    }
    else if(conversationType == ConversationType::GROUP_ID) {
        transferType = TransferType::GROUP_CHAT_MEDIA;
    }

    for(auto it = notificationHandlerMap.begin(); it != notificationHandlerMap.end(); ++it)
    {
        auto notificationHandler = std::static_pointer_cast<CloudNotificationHandler>((*it).second);

        if(notificationHandler->getTransferType() == transferType && notificationHandler->isUploadHandler() == isUpload
                && notificationHandler->isChunkedTransfer() == isChunked) {
            pendingChatMediaList.push_back(notificationHandler->getPacketId());
        }
    }

    return pendingChatMediaList;
}

void CloudNotificationHandler::setSecretTimeout(int secretTimeout) {
    this->secretTimeout = secretTimeout;
}

int CloudNotificationHandler::getSecretTimeout() const {
    return secretTimeout;
}

void CloudNotificationHandler::setInitFileSize(std::int64_t initFileSize) {
    this->initFileSize = initFileSize;
}

std::int64_t CloudNotificationHandler::getInitFileSize() const {
    return initFileSize;
}

void CloudNotificationHandler::setInitChunkSize(std::size_t initChunkSize) {
    this->initChunkSize = initChunkSize;
}

std::size_t CloudNotificationHandler::getInitChunkSize() const {
    return initChunkSize;
}

void CloudNotificationHandler::setInitChunkCount(std::size_t initChunkCount) {
    this->initChunkCount = initChunkCount;
}

std::size_t CloudNotificationHandler::getInitChunkCount() const {
    return initChunkCount;
}

void CloudNotificationHandler::setFileDomainType(int fileDomainType) {
    this->fileDomainType = fileDomainType;
}

int CloudNotificationHandler::getFileDomainType() const {
    return fileDomainType;
}

void CloudNotificationHandler::setFileName(std::string fileName) {
    this->fileName = fileName;
}

std::string CloudNotificationHandler::getFileName() const {
    return fileName;
}

void CloudNotificationHandler::setGroupId(GroupIdentity groupId) {
    this->groupId = groupId;
}

GroupIdentity CloudNotificationHandler::getGroupId() const {
    return groupId;
}

void CloudNotificationHandler::setUserId(UserIdentity userId) {
	this->userId = userId;
}

UserIdentity CloudNotificationHandler::getUserId() const {
	return userId;
}

void CloudNotificationHandler::setFriendId(UserIdentity friendId) {
    this->friendId = friendId;
}

UserIdentity CloudNotificationHandler::getFriendId() const {
    return friendId;
}

void CloudNotificationHandler::setTransferType(TransferType transferType) {
    this->transferType = transferType;
}

TransferType CloudNotificationHandler::getTransferType() const {
    return transferType;
}

void CloudNotificationHandler::setPacketId(std::string packetId) {
    this->packetId = packetId;
}

std::string CloudNotificationHandler::getPacketId() const {
    return packetId;
    }

bool CloudNotificationHandler::isUploadHandler() const {
    return uploadHandler;
}

void CloudNotificationHandler::setUploadHandler(bool uploadHandler) {
    this->uploadHandler = uploadHandler;
}

void CloudNotificationHandler::setChunkedTransfer(bool chunkedTransfer) {
    this->chunkedTransfer = chunkedTransfer;
}

bool CloudNotificationHandler::isChunkedTransfer() const {
    return chunkedTransfer;
}

void CloudNotificationHandler::setCanceledBy(UserIdentity canceledBy) {
    this->canceledBy = canceledBy;
}

UserIdentity CloudNotificationHandler::getCanceledBy() const {
    return canceledBy;
}
}
