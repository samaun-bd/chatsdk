#ifndef CLOUDNOTIFICATIONHANDLER_H
#define	CLOUDNOTIFICATIONHANDLER_H

#include <unordered_map>

#include "PacketDTO.h"
#include "ByteArray.h"
#include "ChatParser.h"
#include "ChatPacketBuilder.h"
#include "cloud/notification_handler.h"
#include "Types.h"

namespace imsdk {

enum TransferType {
    FRIEND_CHAT_MEDIA,
    GROUP_CHAT_MEDIA,
    PUBLIC_CHAT_MEDIA
};

class CloudNotificationHandler : public ipvcore::cloud::NotificationHandler {
private:
    std::string packetId;
    TransferType transferType;
	UserIdentity userId{ 0 };
	UserIdentity friendId{ 0 };
    GroupIdentity groupId{0};
    std::string fileName; // download_id
    int fileDomainType{0};
    std::size_t initChunkCount{0};
    std::size_t initChunkSize{0};
    std::int64_t initFileSize{0};
    int secretTimeout{0};
    bool uploadHandler;
    bool chunkedTransfer{true};
    UserIdentity canceledBy{0};
    
public:
    void setSecretTimeout(int secretTimeout);
    int getSecretTimeout() const;
    void setInitFileSize(std::int64_t initFileSize);
    std::int64_t getInitFileSize() const;
    void setInitChunkSize(std::size_t initChunkSize);
    std::size_t getInitChunkSize() const;
    void setInitChunkCount(std::size_t initChunkCount);
    std::size_t getInitChunkCount() const;
    void setFileDomainType(int fileDomainType);
    int getFileDomainType() const;
    void setFileName(std::string fileName);
    std::string getFileName() const;
    void setGroupId(GroupIdentity groupId);
    GroupIdentity getGroupId() const;
	void setUserId(UserIdentity userId);
	UserIdentity getUserId() const;
    void setFriendId(UserIdentity friendId);
    UserIdentity getFriendId() const;
    void setTransferType(TransferType transferType);
    TransferType getTransferType() const;
    void setPacketId(std::string packetId);
    std::string getPacketId() const;
    bool isUploadHandler() const;
    void setUploadHandler(bool uploadHandler);
    void setChunkedTransfer(bool chunkedTransfer);
    bool isChunkedTransfer() const;
    void setCanceledBy(UserIdentity canceledBy);
    UserIdentity getCanceledBy() const;
};

class CloudUploadNotificationHandler : public imsdk::CloudNotificationHandler {
private:
    std::size_t uploadedChunkCount{0};
    std::string caption;
    int widthOrFileSize{0};     // width for image, fileSize (KB) for audio or video
    int heightOrDuration{0};    // height for image, duration for audio or video
    bool isSecretVisible{false};
    long long messageDate{0};
    
    std::shared_ptr< ChatPacketBuilder> packetBuilder{nullptr};
    
public:
    CloudUploadNotificationHandler();

    void on_complete(ipvcore::cloud::NotificationType type, std::string key, std::string file_path,
            std::shared_ptr< ipvcore::cloud::Response> response);

    void on_error(ipvcore::cloud::NotificationType type, std::string key, std::string file_path,
            std::shared_ptr< ipvcore::cloud::Response> response) override;

    void on_chunked_upload_init(std::string key, std::string file_path, std::size_t chunk_count,
            std::size_t chunk_size, std::int64_t file_size) override;

    void on_progress(std::int64_t /*downloaded*/, std::int64_t /*total_download*/,
                            std::int64_t uploaded, std::int64_t total_upload) override;

    virtual void on_cancel_completed(ipvcore::cloud::NotificationType /*type*/, std::string /*key*/, std::string /*file_path*/,
            std::shared_ptr< ipvcore::cloud::Response> response) override;

    void setHeightOrDuration(int heightOrDuration);
    void setWidthOrFileSize(int widthOrFileSize);
    void setCaption(std::string caption);
    void setMessageDate(long long messageDate);
    void setSecretVisible(bool SecretVisible);
};

class CloudDownloadNotificationHandler : public imsdk::CloudNotificationHandler {
private:
    bool downloadAllowed{false};
    std::string targetFilePath;
    bool chunkPacketReceived{false};

public:
    CloudDownloadNotificationHandler();
    void on_complete(ipvcore::cloud::NotificationType type, std::string key, std::string file_path,
            std::shared_ptr< ipvcore::cloud::Response> response);

    void on_error(ipvcore::cloud::NotificationType type, std::string key, std::string file_path,
            std::shared_ptr< ipvcore::cloud::Response> response) override;

    void on_progress(std::int64_t downloaded, std::int64_t total_download,
                            std::int64_t /*uploaded*/, std::int64_t /*total_upload*/) override;

    virtual void on_cancel_completed(ipvcore::cloud::NotificationType /*type*/, std::string /*key*/, std::string /*file_path*/,
            std::shared_ptr< ipvcore::cloud::Response> response) override;

    void setDownloadAllowed(bool downloadAllowed);
    bool isDownloadAllowed() const;
    void setTargetFilePath(std::string targetFilePath);
    std::string getTargetFilePath() const;
    void setChunkPacketReceived(bool chunkPacketReceived);
    bool isChunkPacketReceived() const;
};

class CloudNotificationManager {
private:
    std::unordered_map<std::string, std::shared_ptr< ipvcore::cloud::NotificationHandler>> notificationHandlerMap; //key=packetId
    std::mutex notificationHandlerMutex;

public:
    static CloudNotificationManager& getInstance();

    void addCloudNotificationHandler(std::string packetId,
            std::shared_ptr< ipvcore::cloud::NotificationHandler> notificationHandler);
    void removeCloudNotificationHandler(std::string packetId);

    std::shared_ptr< ipvcore::cloud::NotificationHandler> getCloudNotificationHandler(
            std::string packetId);

    std::vector<std::string> getPendingChatMediaList(ConversationType conversationType, bool isUpload, bool isChunked);
};

}

#endif

