using ChatWrapper;
using System;
using System.Collections.Generic;
using System.Linq;

namespace ChatLibGenerator.ChatMedia
{
    public class ChatPacketSender
    {
        public static IMManager service;

        private static ChatPacketSender _imPacketSender;
        public static ChatPacketSender IMPacketSender
        {
            get
            {
                return _imPacketSender = _imPacketSender ?? new ChatPacketSender();
            }
        }

        public async void RegisterEventHandler(long userId, string userName, string offlineServerAddress, int offlineServerPort, string authenticationServerAddress, int authenticationServerPort, int deviceType, string appSessionId, int appVersion, long timeDifference, string key, int profileType)
        {
            //var path = Windows.Storage.ApplicationData.Current.LocalFolder;
            string path = Windows.Storage.ApplicationData.Current.LocalFolder.Path;
            var settingDirectoryPaths = new string[] { path, path, path, path, path, path, path, path };

            System.Diagnostics.Debug.WriteLine("=> => => before initiating chat sdk...");

            service = new IMManager(userId, userName, offlineServerAddress, offlineServerPort, authenticationServerAddress, authenticationServerPort, deviceType, appSessionId, appVersion, timeDifference, settingDirectoryPaths, "https://images.ringid.com/", "https://images.ringid.com/", false, key, profileType, null);

            System.Diagnostics.Debug.WriteLine("=> => => after initiating chat sdk...");

            ChatPacketListener eventHandler = new ChatPacketListener();
            service.registerEventHandler(eventHandler);


            //ChatPacketSender.IMPacketSender.RegisterFriendChat("168629", "1068875", "_RING_SPECIAL_dipal", "https://imagesres.ringid.com/cloud/uploaded-141/2110000203/p10111731473227892886.jpg", "", 0, 0, "", 1, 0, 0, 0, 1500451313925, 1);
        }


        public void UnregisterEventHandler()
        {
            service.unregisterEventHandler();
        }

        public void SetOfflineServer(string offlineServerAddress, int offlineServerPort)
        {
            service.setOfflineServer(offlineServerAddress, offlineServerPort);
        }

        public void SetAuthenticationServer(string authenticationServerAddress, int authenticationServerPort)
        {
            service.setAuthenticationServer(authenticationServerAddress, authenticationServerPort);
        }

        public ManagedApiStatus RequestForOffline(Int64 messageDate, Int64 blockUpdateDate)
        {
            return service.requestForOffline(messageDate, (blockUpdateDate + 1));
        }

        public void CleanUp(int mood)
        {
            service.cleanUp(mood);
        }

        public void ClearRegisteredSessions(int mood)
        {
            service.clearRegisteredSessions(mood);
        }

        public ManagedApiStatus activateOrDeactivateUserAccount(bool isActivate)
        {
            return service.activateOrDeactivateUserAccount(isActivate);
        }

        public ManagedApiStatus getUserInfo(string friendId)
        {
            return service.getUserInfo(Convert.ToInt64(friendId));
        }

        public ManagedApiStatus RegisterFriendChat(string userId, string userName, string friendId, string friendName, string url, string registerServerAddress, int registerServerPort, int friednDeviceType, string friendDeviceToken, int friendAppType, int friendPresenceStatus, int friendPresenceMood, int iosVoipPush, Int64 authRegistrationTime, int profileType)
        {
            return service.registerFriendChat(Convert.ToInt64(userId), userName, Convert.ToInt64(friendId), friendName, url, registerServerAddress, registerServerPort, friednDeviceType, friendDeviceToken, friendAppType, friendPresenceStatus, friendPresenceMood, iosVoipPush, authRegistrationTime, profileType);
            //return service.registerFriendChat(Convert.ToInt64(friendId), friendName, url, "192.168.1.52", 1500, friednDeviceType, friendDeviceToken, friendAppType, friendPresenceStatus, friendPresenceMood, iosVoipPush, authRegistrationTime);
        }


        public bool IsExistsFriendConnection(string userId, string friendId)
        {
            return service.isExistsFriendConnection(Convert.ToInt64(userId), Convert.ToInt64(friendId));
        }

        public ManagedApiStatus UnregisterFriendChat(string userId, string userName, string friendId, string friendName, string friendUrl, string registerServerAddress, int registerServerPort, int deviceType, string deviceToken, int appType, int status, int mood, int iosVoipPush, long authRegistrationTime, int profileType)
        {
            return service.registerFriendChat(Convert.ToInt64(userId), userName, Convert.ToInt64(friendId), friendName, friendUrl, registerServerAddress, registerServerPort, deviceType, deviceToken, appType, status, mood, iosVoipPush, authRegistrationTime, profileType);
        }


        public ManagedApiStatus GetConversationList(string userId, int conversationType, int startIndex, int limit, string friendOrGroupId)
        {
            return service != null ? service.getConversationList(Convert.ToInt64(userId), conversationType, startIndex, limit, (string.IsNullOrEmpty(friendOrGroupId) ? 0 : Convert.ToInt64(friendOrGroupId))) : null;
        }

        public ManagedApiStatus UnregisterFriendChat(string userId, string friendId, int status, int mood)
        {
            return service.unregisterFriendChat(Convert.ToInt64(userId), Convert.ToInt64(friendId), status, mood);
        }

        public ManagedApiStatus UpdateFriendRegisterServer(string userId, string friendId, string registerServerAddress, int registerServerPort)
        {
            return service.updateFriendRegisterServer(Convert.ToInt64(userId), Convert.ToInt64(friendId), registerServerAddress, registerServerPort);
        }

        public ManagedApiStatus UpdateFriendStatusAndMood(string userId, string friendId, int status, int mood)
        {
            return service.updateFriendStatusAndMood(Convert.ToInt64(userId), Convert.ToInt64(friendId), status, mood);
        }

        public ManagedApiStatus SendFriendChat(string userId, string packetId, string friendId, int messageType, int secretTimeout, string message, Int64 messageDate, bool isSecretVisible)
        {
            return service.sendFriendChat(packetId, Convert.ToInt64(userId), Convert.ToInt64(friendId), messageType, secretTimeout, message, messageDate, isSecretVisible);
        }

        public ManagedApiStatus DontSendPendingMessages(string userId, string friendId)
        {
            return service.dontSendPendingMessages(Convert.ToInt64(userId), Convert.ToInt64(friendId));
        }


        public ManagedApiStatus EditFriendChat(string packetId, Int64 userId, string friendId, int messageType, int secretTimeout, string message, Int64 messageDate, bool isSecretVisible)
        {
            return service.editFriendChat(packetId, Convert.ToInt64(userId), Convert.ToInt64(friendId), messageType, secretTimeout, message, messageDate, isSecretVisible);
        }

        public ManagedApiStatus SeenFriendChat(Int64 userId, string friendId, List<ManagedSeenPacketDTO> seenPacketList)
        {
            return service.seenFriendChat(Convert.ToInt64(userId), Convert.ToInt64(friendId), seenPacketList.ToArray());
        }

        public ManagedApiStatus TypingFriendChat(Int64 userId, string friendId)
        {
            return service.typingFriendChat(Convert.ToInt64(userId), Convert.ToInt64(friendId));
        }

        public ManagedApiStatus DeleteFriendChatMessage(Int64 userId, string friendId, List<String> packetIds)
        {
            return service.deleteFriendChatMessage(Convert.ToInt64(userId), Convert.ToInt64(friendId), packetIds.ToArray());
        }

        public ManagedApiStatus RequestFriendChatHistory(string userId, string friendId, string packetId, int direction, int limit)
        {
            return service.requestFriendChatHistory(Convert.ToInt64(userId), Convert.ToInt64(friendId), packetId, direction, limit);
        }

        public ManagedApiStatus GetFriendMessageStatus(string userId, string friendId, List<string> packetIds)
        {
            return service.getFriendMessageStatus(Convert.ToInt64(userId), Convert.ToInt64(friendId), packetIds.ToArray());
        }

        public ManagedApiStatus BlockFriend(Int64 userId, string packetId, string friendId, Int64 blockUnblockDate, bool addToBlock)
        {
            return service.blockFriend(Convert.ToInt64(userId), packetId, Convert.ToInt64(friendId), blockUnblockDate, addToBlock);
        }

        public ManagedApiStatus UnblockFriend(Int64 userId, string packetId, string friendId, Int64 blockUnblockDate)
        {
            return service.unblockFriend(Convert.ToInt64(userId), packetId, Convert.ToInt64(friendId), blockUnblockDate);
        }

        public List<string> GetPendingFriendMessages(string userId)
        {
            var retVal = service.getPendingFriendMessages(Convert.ToInt64(userId));
            return retVal != null ? retVal.ToList() : null;
        }

        public ManagedFriendInformation GetFriendInformation(Int64 userId, string friendId)
        {
            return service.getFriendInformation(Convert.ToInt64(userId), Convert.ToInt64(friendId));
        }

        public List<string> GetRegisteredFriendsList(Int64 userId)
        {
            var retVal = service.getRegisteredFriendsList(Convert.ToInt64(userId));
            return retVal != null ? retVal.Select(x => x.ToString()).ToList() : null;
        }




        public bool IsExistsGroupConnection(string groupId)
        {
            return service.isExistsGroupConnection(Convert.ToInt64(groupId));
        }

        public ManagedApiStatus UnregisterGroupChat(string groupId, int status, int mood)
        {
            return service.unregisterGroupChat(Convert.ToInt64(groupId), status, mood);
        }

        public ManagedApiStatus SendGroupChat(string packetId, string groupId, int messageType, string message, Int64 messageDate)
        {
            return service.sendGroupChat(packetId, Convert.ToInt64(groupId), messageType, message, messageDate);
        }

        public ManagedApiStatus EditGroupChat(string packetId, string groupId, int messageType, string message, Int64 messageDate)
        {
            return service.editGroupChat(packetId, Convert.ToInt64(groupId), messageType, message, messageDate);
        }

        public ManagedApiStatus SeenGroupChat(string groupId, List<string> packetIds)
        {
            return service.seenGroupChat(Convert.ToInt64(groupId), packetIds.ToArray());
        }

        public ManagedApiStatus GetGroupMessageSeenList(string groupId, string packetId)
        {
            return service.getGroupMessageSeenList(Convert.ToInt64(groupId), packetId);
        }

        public ManagedApiStatus TypingGroupChat(string groupId)
        {
            return service.typingGroupChat(Convert.ToInt64(groupId));
        }

        public ManagedApiStatus DeleteGroupChatMessage(string groupId, List<string> packetIds)
        {
            return service.deleteGroupChatMessage(Convert.ToInt64(groupId), packetIds.ToArray());
        }

        public ManagedApiStatus ChangeGroupName(string groupId, string groupName)
        {
            return service.changeGroupName(Convert.ToInt64(groupId), groupName);
        }

        public ManagedApiStatus ChangeGroupUrl(string groupId, string groupUrl)
        {
            return service.changeGroupUrl(Convert.ToInt64(groupId), groupUrl);
        }

        public ManagedApiStatus AddGroupMembers(string groupId, List<ManagedMemberDTO> memberList)
        {
            return service.addGroupMembers(Convert.ToInt64(groupId), memberList.ToArray());
        }

        public ManagedApiStatus RemoveGroupMembers(string groupId, List<Int64> memberIds)
        {
            return service.removeGroupMembers(Convert.ToInt64(groupId), memberIds.ToArray());
        }

        public ManagedApiStatus LeaveGroup(string groupId)
        {
            return service.leaveGroup(Convert.ToInt64(groupId));
        }

        public ManagedApiStatus ChangeGroupMemberStatus(string groupId, List<ManagedMemberDTO> memberList)
        {
            return service.changeGroupMemberStatus(Convert.ToInt64(groupId), memberList.ToArray());
        }

        public ManagedApiStatus CreateGroup(string groupId, string groupName, string groupUrl, List<ManagedMemberDTO> memberList)
        {
            return service.createGroup(Convert.ToInt64(groupId), groupName, groupUrl, memberList.ToArray());
        }

        public ManagedApiStatus RequestGroupChatHistory(string groupId, string packetId, int direction, int limit)
        {
            return service.requestGroupChatHistory(Convert.ToInt64(groupId), packetId, direction, limit);
        }

        public ManagedApiStatus GetGroupInformationWithMembers(string groupId)
        {
            return service.getGroupInformationWithMembers(Convert.ToInt64(groupId));
        }

        public List<string> GetPendingGroupMessages()
        {
            var retVal = service.getPendingGroupMessages();
            return retVal != null ? retVal.Select(x => x.ToString()).ToList() : null;
        }

        public ManagedGroupInformation GetGroupInformation(string groupId)
        {
            return service.getGroupInformation(Convert.ToInt64(groupId));
        }







        public ManagedApiStatus sendPublicRoomChat(string packetId, string roomId, int messageType, string message, Int64 messageDate, string memberFullName, string memberProfileUrl)
        {
            return service.sendPublicRoomChat(packetId, roomId, messageType, message, messageDate, memberFullName, memberProfileUrl);
        }

        public ManagedApiStatus editPublicRoomChat(string packetId, string roomId, int messageType, string message, Int64 messageDate, string memberFullName, string memberProfileUrl)
        {
            return service.editPublicRoomChat(packetId, roomId, messageType, message, messageDate, memberFullName, memberProfileUrl);
        }

        public ManagedApiStatus getRoomList(int startIndex, int limit)
        {
            return service.getRoomList(startIndex, limit);
        }

        public ManagedApiStatus searchRoomList(string searchName, string country, string category, int startIndex, int limit)
        {
            return service.searchRoomList(searchName, country, category, startIndex, limit);
        }

        public ManagedApiStatus unregisterPublicRoomChat(string roomId)
        {
            return service.unregisterPublicRoomChat(roomId);
        }

        public ManagedApiStatus typingPublicRoomChat(string roomId)
        {
            return service.typingPublicRoomChat(roomId);
        }

        public bool isExistsRoomConnection(string roomId)
        {
            return service.isExistsRoomConnection(roomId);
        }

        public ManagedApiStatus getRoomInformation(string roomId)
        {
            return service.getRoomInformation(roomId);
        }

        public ManagedApiStatus requestRoomChatHistory(string roomId, string packetId, int year, int month, int direction, int limit)
        {
            return service.requestRoomChatHistory(roomId, packetId, year, month, direction, limit);
        }

        public ManagedApiStatus getRoomListWithHistory(int startIndex, int limit)
        {
            return service.getRoomListWithHistory(startIndex, limit);
        }

        public ManagedApiStatus getRoomMemberList(string roomId, string pagingState, int limit)
        {
            return service.getRoomMemberList(roomId, pagingState, limit);
        }

        public void enterPublicChatScreen(string roomId)
        {
            service.enterPublicChatScreen(roomId);
        }

        public void exitPublicChatScreen(string roomId)
        {
            service.exitPublicChatScreen(roomId);
        }

        public void addUserPage(string pageId)
        {
            service.addUserPage(Convert.ToInt64(pageId));
        }

        public void removeUserPage(string pageId)
        {
            service.removeUserPage(Convert.ToInt64(pageId));
        }

        public ManagedPacketTimeID GeneratePacketId(string userOrPageId = "168629")
        {
            return service.generatePacketId(Convert.ToInt64(userOrPageId));
        }

        public ManagedPacketTimeID GeneratePacketId(Int64 timeMili, string userId)
        {
            return service.generatePacketId(timeMili, Convert.ToInt64(userId));
        }

        public string GeneratePacketId_v2()
        {
            return IMManager.generatePacketId_v2();
        }

        public Int64 getCurrentServerSyncedTime()
        {
            return service.getCurrentServerSyncedTime();
        }

        public Int64 UUIDToTime(string UUID)
        {
            return service.UUIDToTime(UUID);
        }




        public ManagedApiStatus GearchRoomList(string searchName, string country, string category, int startIndex, int limit)
        {
            return service.searchRoomList(searchName, country, category, startIndex, limit);
        }
        public ManagedApiStatus DeletePublicChatMessage(string roomId, List<string> packetIds)
        {
            return service.deletePublicChatMessage(roomId, packetIds.ToArray());
        }
        public ManagedApiStatus LikePublicChatMessage(string packetId, string roomId, string recipientId)
        {
            return service.likePublicChatMessage(packetId, roomId, Convert.ToInt64(recipientId));
        }
        public ManagedApiStatus GetPublicChatLikeMemberList(string roomId, string packetId, string lastLikerId, int limit)
        {
            return service.getPublicChatLikeMemberList(roomId, packetId, Convert.ToInt64(lastLikerId), limit);
        }
        public ManagedApiStatus GetPublicChatRoomCategoryList(string pagingState, int limit)
        {
            return service.getPublicChatRoomCategoryList(pagingState, limit);
        }



        // chat media file transfer

        public bool sendFriendChatMedia(Int64 userId, Int64 friendId, string packetId, int mediaType, string filePath, string caption, int widthOrFileSize, int heightOrDuration, int secretTimeout, Int64 messageDate, bool isSecretVisible)
        {
            return service.sendFriendChatMedia(Convert.ToInt64(userId), friendId, packetId, mediaType, filePath, caption, widthOrFileSize, heightOrDuration, secretTimeout, messageDate, isSecretVisible);
        }
        public bool downloadFriendChatMedia(Int64 userId, Int64 friendId, string packetId, string manifestUrl, int mediaType, int secretTimeout)
        {
            return service.downloadFriendChatMedia(Convert.ToInt64(userId), friendId, packetId, manifestUrl, mediaType, secretTimeout);
        }
        public bool acceptChatMedia(string packetId)
        {
            return service.acceptChatMedia(packetId);
        }


        public bool sendGroupChatMedia(Int64 groupId, string packetId, int mediaType, string filePath, string caption, int widthOrFileSize, int heightOrDuration, Int64 messageDate)
        {
            return service.sendGroupChatMedia(groupId, packetId, mediaType, filePath, caption, widthOrFileSize, heightOrDuration, messageDate);
        }
        public bool downloadGroupChatMedia(Int64 groupId, Int64 friendId, string packetId, string manifestUrl, int mediaType)
        {
            return service.downloadGroupChatMedia(groupId, friendId, packetId, manifestUrl, mediaType);
        }
        public void cancelChatMediaTransfer(string packetId)
        {
            service.cancelChatMediaTransfer(packetId);
        }
        public List<string> getPendingChatMediaList(int conversationType, bool isUpload, bool isChunked)
        {
            var retVal = service.getPendingChatMediaList(conversationType, isUpload, isChunked);
            return retVal != null ? retVal.ToList() : null;
        }

        public bool isChatMediaTransferInProgress(string packetId)
        {
            return service.isChatMediaTransferInProgress(packetId);
        }

        public void updateAppSessionID(string appSessionId)
        {
            service.updateAppSessionID(appSessionId);
        }

        //Live-stream-chat

        public ManagedApiStatus registerLiveStreamChat(Int64 publisherId, string registerServerAddress, int registerServerPort, string fullName)
        {
            return service.registerLiveStreamChat(publisherId, registerServerAddress, registerServerPort, fullName);
        }
        public ManagedApiStatus unregisterLiveStreamChat(Int64 publisherId, int onlineStatus, int onlineMood)
        {
            return service.unregisterLiveStreamChat(publisherId, onlineStatus, onlineMood);
        }
        public ManagedApiStatus typingLiveStreamChat(Int64 publisherId)
        {
            return service.typingLiveStreamChat(publisherId);
        }
        public ManagedApiStatus sendLiveStreamChat(string packetId, Int64 publisherId, int messageType, string message, Int64 messageDate)
        {
            return service.sendLiveStreamChat(packetId, publisherId, messageType, message, messageDate);
        }
        public ManagedApiStatus blockUserFromLiveStreamChat(Int64 blockedUserId, string packetId)
        {
            return service.blockUserFromLiveStreamChat(blockedUserId, packetId);
        }




    }
}
