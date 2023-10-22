/* 
 * File:   PacketDTO.cpp
 * Author: dipal
 * 
 * Created on July 12, 2015, 2:20 PM
 */

#include "PacketDTO.h"

namespace imsdk {
PacketDTO::PacketDTO () {
initAttributes();
}

void PacketDTO::setProfileType(int profileType) {
    this->profileType = profileType;
}

int PacketDTO::getProfileType() const {
    return profileType;
}

void PacketDTO::setFriendProfileType(int friendProfileType) {
    this->friendProfileType = friendProfileType;
}

int PacketDTO::getFriendProfileType() const {
    return friendProfileType;
}

void PacketDTO::setAppVersion(int appVersion) {
    this->appVersion = appVersion;
}

int PacketDTO::getMessageDeleteType() const {
    return this->deleteType;
}

void PacketDTO::setMessageDeleteType(int deleteType) {
    this->deleteType = deleteType;
}

int PacketDTO::getAppVersion() {
    return appVersion;
}

void PacketDTO::setOnline(bool Online) {
    fromOnline = Online;
}

bool PacketDTO::isOnline() {
    return fromOnline;
}

void PacketDTO::setServerPort(int serverPort) {
    this->serverPort = serverPort;
}

int PacketDTO::getServerPort() const {
    return serverPort;
}

void PacketDTO::setServerIp(std::string serverIp) {
    this->serverIp = serverIp;
}

std::string PacketDTO::getServerIp() const {
    return serverIp;
}


void PacketDTO::setRoomList(std::vector<RoomDTO> &roomList) {
    this->roomList = roomList;
}

std::vector<RoomDTO> PacketDTO::getRoomList() const {
    return roomList;
}

void PacketDTO::appendRoom(RoomDTO &roomDTO) {
    this->roomList.push_back(roomDTO);
}

void PacketDTO::setStartIndex(int startIndex) {
    this->startIndex = startIndex;
}

int PacketDTO::getStartIndex() const {
    return startIndex;
}

void PacketDTO::setSelfPlatform(int selfPlatform) {
    this->selfPlatform = selfPlatform;
}

int PacketDTO::getSelfPlatform() const {
    return selfPlatform;
}

void PacketDTO::setRoomSearchName(std::string roomSearchName) {
    this->roomSearchName = roomSearchName;
}

std::string PacketDTO::getRoomSearchName() const {
    return roomSearchName;
}

void PacketDTO::setRoomUrl(std::string roomUrl) {
    this->roomUrl = roomUrl;
}

std::string PacketDTO::getRoomUrl() const {
    return roomUrl;
}

void PacketDTO::setRoomFullName(std::string roomFullName) {
    this->roomFullName = roomFullName;
}

std::string PacketDTO::getRoomFullName() const {
    return roomFullName;
}

void PacketDTO::setRoomId(std::string roomId) {
    this->roomId = roomId;
}

std::string PacketDTO::getRoomId() const {
    return roomId;
}

void PacketDTO::setPublicChatMemberList(std::vector<PublicChatMemberDTO> publicChatMemberList) {
    this->publicChatMemberList = publicChatMemberList;
}

std::vector<PublicChatMemberDTO> PacketDTO::getPublicChatMemberList() const {
    return publicChatMemberList;
}

void PacketDTO::setYear(int year) {
    this->year = year;
}

int PacketDTO::getYear() const {
    return year;
}

void PacketDTO::setMonth(int month) {
    this->month = month;
}

int PacketDTO::getMonth() const {
    return month;
}

void PacketDTO::setChatMessageList(std::vector<SDKMessageDTO> &chatMessageList){
    this->chatMessageList = chatMessageList;
}

std::vector<SDKMessageDTO> PacketDTO::getChatMessageList() const{
    return chatMessageList;
}

void PacketDTO::setPagingState(std::string pagingState) {
    this->pagingState = pagingState;
}

std::string PacketDTO::getPagingState() const {
    return pagingState;
}

void PacketDTO::setRecipientId(long long recepientId) {
    this->recipientId = recepientId;
}

long long PacketDTO::getRecipientId() const {
    return recipientId;
}

void PacketDTO::setGroupActivityType(int groupActivityType) {
    this->groupActivityType = groupActivityType;
}

int PacketDTO::getGroupActivityType() {
    return groupActivityType;
}

void PacketDTO::setFriendMessageStatusDTOList(std::vector<FriendMessageStatusDTO> friendMessageStatusDTOList) {
    this->friendMessageStatusDTOList = friendMessageStatusDTOList;
}

std::vector<FriendMessageStatusDTO> PacketDTO::getFriendMessageStatusDTOList() {
    return friendMessageStatusDTOList;
}

void PacketDTO::appendFriendMessageStatusDTO(FriendMessageStatusDTO friendMessageStatusDTO) {
    this->friendMessageStatusDTOList.push_back(friendMessageStatusDTO);
}

void PacketDTO::setDataBytes(std::shared_ptr<ByteArray> dataBytes) {
    this->dataBytes = dataBytes;
}

std::shared_ptr<ByteArray> PacketDTO::getDataBytes() {
    return dataBytes;
}

void PacketDTO::setNumberOfGroups(int numberOfGroups) {
    this->numberOfGroups = numberOfGroups;
}

int PacketDTO::getNumberOfGroups() {
    return numberOfGroups;
}

void PacketDTO::setGroupDTOList(std::vector<GroupDTO> groupDTOList) {
    this->groupDTOList = groupDTOList;
}

std::vector<GroupDTO> PacketDTO::getGroupDTOList() {
    return groupDTOList;
}

void PacketDTO::appendGroupDTO(GroupDTO groupDTO) {
    this->groupDTOList.push_back(groupDTO);
}

void PacketDTO::setGroupActivities(std::vector<GroupActivityDTO> groupActivities) {
    this->groupActivities = groupActivities;
}

std::vector<GroupActivityDTO> PacketDTO::getGroupActivities() {
    return groupActivities;
}

void PacketDTO::appendGroupAcitivity(GroupActivityDTO groupActivity){
    this->groupActivities.push_back(groupActivity);
}

void PacketDTO::setLimit(int limit) {
    this->limit = limit;
}

int PacketDTO::getLimit() {
    return limit;
}

void PacketDTO::setUpDownStatus(int upDownStatus) {
    this->upDownStatus = upDownStatus;
}

int PacketDTO::getUpDownStatus() {
    return upDownStatus;
}

void PacketDTO::setGroupUpdateDate(long long groupUpdateDate) {
    this->groupUpdateDate = groupUpdateDate;
}

long long PacketDTO::getGroupUpdateDate() {
    return groupUpdateDate;
}

void PacketDTO::setBlockUnblockDate(long long blockUnblockDate) {
    this->blockUnblockDate = blockUnblockDate;
}

long long PacketDTO::getBlockUnblockDate() {
    return blockUnblockDate;
}

void PacketDTO::setMessageStatus(int messageStatus) {
    this->messageStatus = messageStatus;
}

int PacketDTO::getMessageStatus() {
    return messageStatus;
}

void PacketDTO::setIsSecretVisible(bool SecretVisible) {
    isSecretVisible = SecretVisible;
}

bool PacketDTO::getIsSecretVisible() {
    return isSecretVisible;
}

void PacketDTO::setRequestStatus(bool status){
    this->requestStatus = status;
}

bool PacketDTO::getRequestStatus() const{
    return requestStatus;
}

void PacketDTO::setFromAnonymous(bool fromAnonymous) {
    this->fromAnonymous = fromAnonymous;
}

bool PacketDTO::isFromAnonymous() const {
    return fromAnonymous;
}

void PacketDTO::setOriginalUserId(long long originalUserId) {
    this->originalUserId = originalUserId;
}

long long PacketDTO::getOriginalUserId() const {
    return originalUserId;
}

void PacketDTO::setShadowIdList(std::vector<UserIdentity> &shadowIdList) {
    this->shadowIdList = shadowIdList;
}

std::vector<UserIdentity> PacketDTO::getShadowIdList() const {
    return shadowIdList;
}

void PacketDTO::setFileAcceptReject(bool fileAcceptReject) {
    this->fileAcceptReject = fileAcceptReject;
}

bool PacketDTO::isFileAcceptReject() const {
    return fileAcceptReject;
}

void PacketDTO::setIosVoipPush(int IosVoipPush) {
    iosVoipPush = IosVoipPush;
}

int PacketDTO::getIosVoipPush() const {
    return iosVoipPush;
}

void PacketDTO::setOriginalPacketType(int originalPacketType) {
    this->originalPacketType = originalPacketType;
}

int PacketDTO::getOriginalPacketType() const {
    return originalPacketType;
}

void PacketDTO::setDataCounter(DataCounter dataCounter) {
    this->dataCounter = dataCounter;
}

DataCounter PacketDTO::getDataCounter() {
    return dataCounter;
}

void PacketDTO::setOriginalPacketID(std::string originalPacketID) {
    this->originalPacketID = originalPacketID;
}

std::string PacketDTO::getOriginalPacketID() const {
    return originalPacketID;
}

void PacketDTO::setLastLikerId(long long lastLikerId) {
    this->lastLikerId = lastLikerId;
}

long long PacketDTO::getLastLikerId() const {
    return lastLikerId;
}

void PacketDTO::setNumberOfPublicChatLikersId(int numberOfPublicChatLikersId) {
    this->numberOfPublicChatLikersId = numberOfPublicChatLikersId;
}

int PacketDTO::getNumberOfPublicChatLikersId() const {
    return numberOfPublicChatLikersId;
}

void PacketDTO::setPublicChatUserIDList(std::vector<UserIdentity> publicChatUserIDList) {
    this->publicChatUserIDList = publicChatUserIDList;
}

std::vector<UserIdentity> PacketDTO::getPublicChatUserIDList() const {
    return publicChatUserIDList;
}

void PacketDTO::setNumberOfPublicRoomCategory(int numberOfPublicRoomCategory) {
    this->numberOfPublicRoomCategory = numberOfPublicRoomCategory;
}

int PacketDTO::getNumberOfPublicRoomCategory() const {
    return numberOfPublicRoomCategory;
}

void PacketDTO::setPublicRoomCategoryList(std::vector<std::string> publicRoomCategoryList) {
    this->publicRoomCategoryList = publicRoomCategoryList;
}

std::vector<std::string> PacketDTO::getPublicRoomCategoryList() const {
    return publicRoomCategoryList;
}

void PacketDTO::setCountryOfPublicChatRoom(std::string countryOfPublicChatRoom) {
    this->countryOfPublicChatRoom = countryOfPublicChatRoom;
}

std::string PacketDTO::getCountryOfPublicChatRoom() const {
    return countryOfPublicChatRoom;
}

void PacketDTO::setCategoryOfPublicChatRoom(std::string categoryOfPublicChatRoom) {
    this->categoryOfPublicChatRoom = categoryOfPublicChatRoom;
}

std::string PacketDTO::getCategoryOfPublicChatRoom() const {
    return categoryOfPublicChatRoom;
}

void PacketDTO::setPublicChatLikeCount(int publicChatLikeCount) {
    this->publicChatLikeCount = publicChatLikeCount;
}

int PacketDTO::getPublicChatLikeCount() const {
    return publicChatLikeCount;
}

void PacketDTO::setPublicChatILike(bool publicChatILike) {
    this->publicChatILike = publicChatILike;
}

bool PacketDTO::isPublicChatILike() const {
    return publicChatILike;
}

void PacketDTO::setPublicChatIReport(bool publicChatIReport) {
    this->publicChatIReport = publicChatIReport;
}

bool PacketDTO::isPublicChatIReport() const {
    return publicChatIReport;
}

void PacketDTO::setFriendOrGroupId(long long friendOrGroupId) {
    this->friendOrGroupId = friendOrGroupId;
}

long long PacketDTO::getFriendOrGroupId() const {
    return friendOrGroupId;
}

void PacketDTO::setConversationType(int conversationType) {
    this->conversationType = conversationType;
}

int PacketDTO::getConversationType() const {
    return conversationType;
}

void PacketDTO::setUnreadCount(int unreadCount) {
    this->unreadCount = unreadCount;
}

int PacketDTO::getUnreadCount() const {
    return unreadCount;
}

void PacketDTO::setNumberOfConversation(int numberOfConversation) {
    this->numberOfConversation = numberOfConversation;
}

int PacketDTO::getNumberOfConversation() const {
    return numberOfConversation;
}

void PacketDTO::setMessageEdited(bool messageEdited) {
    this->messageEdited = messageEdited;
}

bool PacketDTO::isMessageEdited() const {
    return messageEdited;
}

void PacketDTO::setRingId(long long ringId) {
    this->ringId = ringId;
}

long long PacketDTO::getRingId() const {
    return ringId;
}

void PacketDTO::setNetworkConnectionAvailable(bool networkConnectionAvailable) {
    this->networkConnectionAvailable = networkConnectionAvailable;
}

bool PacketDTO::isNetworkConnectionAvailable() const {
    return networkConnectionAvailable;
}

void PacketDTO::setConversationList(std::vector<ConversationDTO> conversationList) {
    this->conversationList = conversationList;
}

std::vector<ConversationDTO> PacketDTO::getConversationList() const {
    return conversationList;
}

void PacketDTO::setPublisherId(long long publisherId) {
    this->publisherId = publisherId;
}

long long PacketDTO::getPublisherId() const {
    return publisherId;
}

void PacketDTO::setFileChunkDownloadKey(std::string fileChunkDownloadKey) {
    this->fileChunkDownloadKey = fileChunkDownloadKey;
}

std::string PacketDTO::getFileChunkDownloadKey() const {
    return fileChunkDownloadKey;
}

void PacketDTO::setFileSize(long long fileSize) {
    this->fileSize = fileSize;
}

long long PacketDTO::getFileSize() const {
    return fileSize;
}

void PacketDTO::setFileChunkSize(int fileChunkSize) {
    this->fileChunkSize = fileChunkSize;
}

int PacketDTO::getFileChunkSize() const {
    return fileChunkSize;
}

void PacketDTO::setFileChunkCount(int fileChunkCount) {
    this->fileChunkCount = fileChunkCount;
}

int PacketDTO::getFileChunkCount() const {
    return fileChunkCount;
}

void PacketDTO::setFileDownloadId(std::string fileDownloadId) {
    this->fileDownloadId = fileDownloadId;
}

std::string PacketDTO::getFileDownloadId() const {
    return fileDownloadId;
}

void PacketDTO::setFileManifest(bool fileManifest) {
    this->fileManifest = fileManifest;
}

bool PacketDTO::isFileManifest() const {
    return fileManifest;
}

void PacketDTO::setFileDomainType(int fileDomainType) {
    this->fileDomainType = fileDomainType;
}

int PacketDTO::getFileDomainType() const {
    return fileDomainType;
}

void PacketDTO::setLocalFilePath(std::string localFilePath) {
    this->localFilePath = localFilePath;
}

std::string PacketDTO::getLocalFilePath() const {
    return localFilePath;
}

void PacketDTO::setChunkedMediaTransferPercentage(double chunkedMediaTransferPercentage) {
    this->chunkedMediaTransferPercentage = chunkedMediaTransferPercentage;
}

double PacketDTO::getChunkedMediaTransferPercentage() const {
    return chunkedMediaTransferPercentage;
}

void PacketDTO::setMediaTransferTypeUpload(bool mediaTransferTypeUpload) {
    this->mediaTransferTypeUpload = mediaTransferTypeUpload;
}

bool PacketDTO::isMediaTransferTypeUpload() const {
    return mediaTransferTypeUpload;
}

void PacketDTO::setRoomListFromHistory(bool roomListFromHistory) {
    this->roomListFromHistory = roomListFromHistory;
}

bool PacketDTO::isRoomListFromHistory() const {
    return roomListFromHistory;
}

void PacketDTO::setHeightOrDuration(int heightOrDuration) {
    this->heightOrDuration = heightOrDuration;
}

int PacketDTO::getHeightOrDuration() const {
    return heightOrDuration;
}

void PacketDTO::setWidthOrFileSize(int widthOrFileSize) {
    this->widthOrFileSize = widthOrFileSize;
}

int PacketDTO::getWidthOrFileSize() const {
    return widthOrFileSize;
}

void PacketDTO::setCaption(std::string caption) {
    this->caption = caption;
}

std::string PacketDTO::getCaption() const {
    return caption;
}

void PacketDTO::setFriendProfileImageUrl(std::string profileImageUrl) {
    this->friendProfileImageUrl = profileImageUrl;
}

std::string PacketDTO::getFriendProfileImageUrl() const {
    return friendProfileImageUrl;
}

void PacketDTO::setChunkedTransfer(bool chunkedTransfer) {
    this->chunkedTransfer = chunkedTransfer;
}

bool PacketDTO::isChunkedTransfer() const {
    return chunkedTransfer;
}


bool PacketDTO::getIsActivateUserAccount() const {
    return isActivateUserAccount;
}

void PacketDTO::setIsActivateUserAccount(bool isActivate) {
    this->isActivateUserAccount = isActivate;
}

void PacketDTO::setMemberInGroup(bool isMemberInGroup)
{
    this->memberInGroup = isMemberInGroup;
}
    
bool PacketDTO::isMemberInGroup()
{
    return memberInGroup;
}

void PacketDTO::setPageIdList(std::set<UserIdentity> &pageIdList) {
    this->pageIdList = pageIdList;
}

std::set<UserIdentity> PacketDTO::getPageIdList() const {
    return pageIdList;
}

void PacketDTO::setIsFromSynced(bool isFromSynced){
    this->isFromSynced = isFromSynced;
}

bool PacketDTO::getIsFromSynced() const {
    return this->isFromSynced;
}

void PacketDTO::setOldestMessageTime(long long oldestMessageTime) {
    this->oldestMessageTime = oldestMessageTime;
}

long long PacketDTO::getOldestMessageTime() const {
    return oldestMessageTime;
}

PacketDTO::~PacketDTO () { }

//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  

void PacketDTO::initAttributes () {
}
}

