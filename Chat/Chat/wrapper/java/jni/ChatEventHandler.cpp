/* 
 * File:   ChatEventHandler.cpp
 * Author: dipal
 * 
 * Created on September 29, 2015, 1:07 PM
 */

#include "ChatEventHandler.h"
#include "MemberDTOConversion.h"
#include "SeenPacketDTOConversion.h"
#include "Logger.h"
#include "FriendMessageStatusDTOConversion.h"
#include "GroupActivityDTOConversion.h"
#include "GroupDTOConversion.h"
#include "ArrayListManipulation.h"
#include "RoomDTOConversion.h"
#include "PublicChatMemberDTOConversion.h"
#include "SDKMessageDTOConversion.h"
#include "DataCounterConversion.h"
#include <iostream>
#include <vector>

#define module "jni"

namespace imsdk {
jclass JChatEventHandler;

jmethodID cehOnFriendChatRegisterSuccess;
jmethodID cehOnFriendChatRegisterFailure;
jmethodID cehOnFriendRegistrationExpired;
jmethodID cehOnFriendUnregistered;
jmethodID cehOnGroupChatRegisterSuccess;
jmethodID cehOnGroupChatRegisterFailure;
jmethodID cehOnGroupRegistrationExpired;
jmethodID cehOnFriendChatReceived;
jmethodID cehOnFriendChatDelivered;
jmethodID cehOnFriendChatSent;
jmethodID cehOnFriendChatFailedToSend;
jmethodID cehOnFriendChatSeen;
jmethodID cehOnFriendChatSeenConfirmed;
jmethodID cehOnFriendChatTyping;
jmethodID cehOnFriendChatIdle;
jmethodID cehOnFriendChatEdited;
jmethodID cehOnFriendChatDeleted;
jmethodID cehOnFriendChatDeleteRequestStatus;
jmethodID cehOnBlocked;
jmethodID cehOnUnblocked;
jmethodID cehOnBlockUnblockRequestStatus;
jmethodID cehOnGroupChatSent;
jmethodID cehOnGroupChatReceived;
jmethodID cehOnGroupChatDelivered;
jmethodID cehOnGroupChatDeleted;
jmethodID cehOnGroupChatDeleteRequestStatus;
jmethodID cehOnGroupChatSeen;
jmethodID cehOnGroupChatSeenRequestStatus;
jmethodID cehOnGroupChatTyping;
jmethodID cehOnGroupChatIdle;
jmethodID cehOnGroupChatEdited;
jmethodID cehOnGroupMemberRemoveLeaveRequestStatus;
jmethodID cehOnGroupMemberRemovedOrLeft;
jmethodID cehOnGroupMemberAddRequestStatus;
jmethodID cehOnGroupMemberAdded;
jmethodID cehOnGroupMemberStatusChangeRequestStatus;
jmethodID cehOnGroupMemberStatusChanged;
jmethodID cehOnGroupChatFailedToSend;
jmethodID cehShouldCheckFreindPresence;
jmethodID cehShouldCheckServerAddressForFriend;
jmethodID cehShouldCheckServerAddressForGroup;
jmethodID cehShouldCheckOfflineServerAddress;
jmethodID cehOnServerTimeSynced;
jmethodID cehShouldUpdateUserPassword;
//jmethodID cehonFriendFileTransferRequestReceived;
jmethodID cehOnSDKError;
jmethodID cehOnFriendHistoryMessageReceived;
jmethodID cehOnFriendMessagesStatusReceived;
jmethodID cehOnFriendHistoryCompleted;
jmethodID cehOnGroupHistoryMessageReceived;
jmethodID cehOnGroupHistoryCompleted;
jmethodID cehOnGroupInformationWithMembersReceived;
jmethodID cehOnGroupInformationWithMembersRequestStatus;
jmethodID cehOnGroupInformationActivityReceived;
jmethodID cehOnGroupInformationActivityFromHistoryMessageReceived;
jmethodID cehOnMyGroupListReceived;
jmethodID cehOnMyGroupListPagingReceived;
jmethodID cehOnMyGroupListReceiveCompleted;
jmethodID cehOnGroupCreated;
jmethodID cehOnGroupInformationChangeRequestStatus;
jmethodID cehOnGroupNameChanged;
jmethodID cehOnGroupUrlChanged;
jmethodID cehOnFriendHistoryMessageRequestStatus;
jmethodID cehOnGroupHistoryMessageRequestStatus;

jmethodID cehOnPublicRoomChatRegisterSuccess;
jmethodID cehOnPublicRoomChatRegisterFailure;
jmethodID cehOnPublicRoomChatRegistrationExpired;
jmethodID cehOnPublicRoomChatDelivered;
jmethodID cehOnPublicRoomChatFailedToSend;
jmethodID cehOnPublicRoomChatReceived;
jmethodID cehOnPublicRoomListReceived;
jmethodID cehOnPublicRoomInformationReceived;
jmethodID cehOnPublicRoomChatHistoryReceived;
jmethodID cehOnPublicRoomChatHistoryCompleted;
jmethodID cehOnPublicRoomChatEdited;
jmethodID cehOnPublicRoomChatTyping;
jmethodID cehonPublicChatMemberListReceived;
jmethodID cehOnPublicChatMemberCountChanged;
jmethodID cehshouldCheckServerAddressForRoom;
jmethodID cehOnPublicRoomListRequestStatus;
jmethodID cehOnPublicRoomInformationRequestFailed;
jmethodID cehOnPublicRoomChatHistoryRequestStatus;
jmethodID cehOnPublicRoomMemberListRequestStatus;
jmethodID cehOnShadowIdsInfoRequestFailed;
jmethodID cehOnShadowIdsInfoResponseReceived;
jmethodID cehOnGroupChatMessageSeenListReceived;
jmethodID cehOnFriendChatConversationListReceived;
jmethodID cehOnGroupChatConversationListReceived;
jmethodID cehOnChatConversationListRequestStatus;
jmethodID cehOnChatConversationListCompleted;
jmethodID cehOnConversationListDeleteRequestStatus;
jmethodID cehOnConversationListMarkAsSeenRequestStatus;
jmethodID cehOnNetworkDataCounted;
jmethodID cehOnPublicChatMessageDeleted;
jmethodID cehOnPublicChatMessageLiked;
jmethodID cehOnPublicChatMessageUnliked;
jmethodID cehOnPublicChatMessageReported;
jmethodID cehOnPublicChatCategoryListReceived;
jmethodID cehOnPublicChatLikeMemberListReceived;
jmethodID cehOnPublicChatDeleteRequestStatus;
jmethodID cehOnPublicChatLikeUnlikeRequestStatus;
jmethodID cehOnPublicChatReportRequestStatus;
jmethodID cehOnPublicChatLikeMemberListRequestStatus;
jmethodID cehOnPublicChatCategoryListRequestStatus;

jmethodID cehOnLiveStreamChatRegisterSuccess;
jmethodID cehOnLiveStreamChatRegisterFailure;
jmethodID cehOnLiveStreamChatRegistrationExpired;
jmethodID cehOnLiveStreamChatDelivered;
jmethodID cehOnLiveStreamChatFailedToSend;
jmethodID cehOnLiveStreamChatReceived;
jmethodID cehOnLiveStreamChatTyping;
jmethodID cehShouldCheckServerAddressForLiveStreamChat;
jmethodID cehOnLiveStreamChatBlockUserRequestStatus;
jmethodID cehOnLiveStreamChatUserBlocked;

jmethodID cehOnFriendFileManifestUploaded;
jmethodID cehOnFriendIncomingChatMedia;
jmethodID cehOnFriendChatMediaTransferProgress;
jmethodID cehOnFriendChatMediaTransferFailed;
jmethodID cehOnFriendChatMediaTransferCanceled;
jmethodID cehOnFriendChatMediaDownloadCompleted;

jmethodID cehOnGroupFileManifestUploaded;
jmethodID cehOnGroupIncomingChatMedia;
jmethodID cehOnGroupChatMediaTransferProgress;
jmethodID cehOnGroupChatMediaTransferFailed;
jmethodID cehOnGroupChatMediaTransferCanceled;
jmethodID cehOnGroupChatMediaDownloadCompleted;

jmethodID cehOnChatMediaTransferDirectoryError;
jmethodID cehShouldUpdateAppSessionID;
jmethodID cehOnActivaeOrDeactivateUserAccountStatus;

jmethodID cehOnSyncConversationRequestStatus;

jmethodID cehOnSyncFriendHistoryMessageRequestStatus;
jmethodID cehOnSyncFriendHistoryMessageReceived;
jmethodID cehOnSyncFriendHistoryMessageReceiveCompleted;

jmethodID cehOnSyncGroupHistoryMessageRequestStatus;
jmethodID cehOnSyncGroupHistoryMessageReceived;
jmethodID cehOnSyncGroupHistoryMessageReceiveCompleted;
jmethodID cehOnGeneralEncryptedPacketReceived;
jmethodID cehOnGeneralEncryptedPacketConfirmationReceived;
//cehonFileTransferProgress;
//cehonFileTransferCompleted;
//cehonFileTransferCanceled;
//cehonFileTransferFailed;

void onloadChatEventHandler(JNIEnv *env)
{
    jclass localChatEventHandler = env->FindClass("com/ringid/imsdk/IChatEventHandler");
    JChatEventHandler = (jclass) env->NewGlobalRef(localChatEventHandler);
    
     cehOnFriendChatRegisterSuccess = env->GetMethodID(JChatEventHandler, "onFriendChatRegisterSuccess", "(JJJLjava/lang/String;Z)V");
     cehOnFriendChatRegisterFailure = env->GetMethodID(JChatEventHandler, "onFriendChatRegisterFailure", "(JJLjava/lang/String;Z)V");
     cehOnFriendRegistrationExpired = env->GetMethodID(JChatEventHandler, "onFriendRegistrationExpired", "(JJZ)V");
     cehOnFriendUnregistered = env->GetMethodID(JChatEventHandler, "onFriendUnregistered", "(JJIIZI)V");
     cehOnGroupChatRegisterSuccess = env->GetMethodID(JChatEventHandler, "onGroupChatRegisterSuccess", "(JJLjava/lang/String;)V");
     cehOnGroupChatRegisterFailure = env->GetMethodID(JChatEventHandler, "onGroupChatRegisterFailure", "(JLjava/lang/String;)V");
     cehOnGroupRegistrationExpired = env->GetMethodID(JChatEventHandler, "onGroupRegistrationExpired", "(JJ)V");
     cehOnFriendChatReceived = env->GetMethodID(JChatEventHandler, "onFriendChatReceived", "(JJLjava/lang/String;IILjava/lang/String;JZZZ)V");
     cehOnFriendChatDelivered = env->GetMethodID(JChatEventHandler, "onFriendChatDelivered", "(JJLjava/lang/String;ZZZ)V");
     cehOnFriendChatSent = env->GetMethodID(JChatEventHandler, "onFriendChatSent", "(JJLjava/lang/String;Z)V");
     cehOnFriendChatFailedToSend = env->GetMethodID(JChatEventHandler, "onFriendChatFailedToSend", "(JJLjava/lang/String;Z)V");
     cehOnFriendChatSeen = env->GetMethodID(JChatEventHandler, "onFriendChatSeen", "(JJLjava/util/ArrayList;Z)V");
     cehOnFriendChatSeenConfirmed = env->GetMethodID(JChatEventHandler, "onFriendChatSeenConfirmed", "(JJLjava/util/ArrayList;Z)V");
     cehOnFriendChatTyping = env->GetMethodID(JChatEventHandler, "onFriendChatTyping", "(JJZ)V");
     cehOnFriendChatIdle = env->GetMethodID(JChatEventHandler, "onFriendChatIdle", "(JZ)V");
     cehOnFriendChatEdited = env->GetMethodID(JChatEventHandler, "onFriendChatEdited", "(JJLjava/lang/String;IILjava/lang/String;JZZZ)V");
     cehOnFriendChatDeleted = env->GetMethodID(JChatEventHandler, "onFriendChatDeleted", "(JJLjava/util/ArrayList;Z)V");
     cehOnFriendChatDeleteRequestStatus = env->GetMethodID(JChatEventHandler, "onFriendChatDeleteRequestStatus", "(JJLjava/lang/String;Ljava/util/ArrayList;ZZI)V");
     cehOnBlocked = env->GetMethodID(JChatEventHandler, "onBlocked", "(JJJZ)V");
     cehOnUnblocked = env->GetMethodID(JChatEventHandler, "onUnblocked", "(JJJ)V");
     cehOnBlockUnblockRequestStatus = env->GetMethodID(JChatEventHandler, "onBlockUnblockRequestStatus", "(JJLjava/lang/String;JZZ)V");
     cehOnGroupChatSent = env->GetMethodID(JChatEventHandler, "onGroupChatSent", "(JLjava/lang/String;Z)V");
     cehOnGroupChatReceived = env->GetMethodID(JChatEventHandler, "onGroupChatReceived", "(JJLjava/lang/String;ILjava/lang/String;JZ)V");
     cehOnGroupChatDelivered = env->GetMethodID(JChatEventHandler, "onGroupChatDelivered", "(JJLjava/lang/String;)V");
     cehOnGroupChatDeleted = env->GetMethodID(JChatEventHandler, "onGroupChatDeleted", "(JJLjava/util/ArrayList;)V");
     cehOnGroupChatDeleteRequestStatus = env->GetMethodID(JChatEventHandler, "onGroupChatDeleteRequestStatus", "(JLjava/lang/String;Ljava/util/ArrayList;Z)V");
     cehOnGroupChatSeen = env->GetMethodID(JChatEventHandler, "onGroupChatSeen", "(JJLjava/util/ArrayList;)V");
     cehOnGroupChatSeenRequestStatus = env->GetMethodID(JChatEventHandler, "onGroupChatSeenRequestStatus", "(JLjava/util/ArrayList;Z)V");
     cehOnGroupChatTyping = env->GetMethodID(JChatEventHandler, "onGroupChatTyping", "(JJ)V");
     cehOnGroupChatIdle = env->GetMethodID(JChatEventHandler, "onGroupChatIdle", "(JJ)V");
     cehOnGroupChatEdited = env->GetMethodID(JChatEventHandler, "onGroupChatEdited", "(JJLjava/lang/String;ILjava/lang/String;JZ)V");
     cehOnGroupMemberRemoveLeaveRequestStatus = env->GetMethodID(JChatEventHandler, "onGroupMemberRemoveLeaveRequestStatus", "(JLjava/lang/String;ZZ)V");
     cehOnGroupMemberRemovedOrLeft = env->GetMethodID(JChatEventHandler, "onGroupMemberRemovedOrLeft", "(JJLjava/util/ArrayList;Ljava/lang/String;Z)V");
     cehOnGroupMemberAddRequestStatus = env->GetMethodID(JChatEventHandler, "onGroupMemberAddRequestStatus", "(JLjava/lang/String;ZLjava/util/ArrayList;)V");
     cehOnGroupMemberAdded = env->GetMethodID(JChatEventHandler, "onGroupMemberAdded", "(JJLjava/util/ArrayList;Ljava/lang/String;)V");
     cehOnGroupMemberStatusChangeRequestStatus = env->GetMethodID(JChatEventHandler, "onGroupMemberStatusChangeRequestStatus", "(JLjava/lang/String;Z)V");
     cehOnGroupMemberStatusChanged = env->GetMethodID(JChatEventHandler, "onGroupMemberStatusChanged", "(JJLjava/util/ArrayList;Ljava/lang/String;)V");
     cehOnGroupChatFailedToSend = env->GetMethodID(JChatEventHandler, "onGroupChatFailedToSend", "(JLjava/lang/String;)V");
     cehShouldCheckFreindPresence = env->GetMethodID(JChatEventHandler, "shouldCheckFriendPresence", "(JJZI)V");
     cehShouldCheckServerAddressForFriend = env->GetMethodID(JChatEventHandler, "shouldCheckServerAddressForFriend", "(JJZ)V");
     cehShouldCheckServerAddressForGroup = env->GetMethodID(JChatEventHandler, "shouldCheckServerAddressForGroup", "(J)V");
     cehShouldCheckOfflineServerAddress = env->GetMethodID(JChatEventHandler, "shouldCheckOfflineServerAddress", "()V");
     cehOnServerTimeSynced = env->GetMethodID(JChatEventHandler, "onServerTimeSynced", "(J)V");
     cehShouldUpdateUserPassword = env->GetMethodID(JChatEventHandler, "shouldUpdateUserPassword", "()V");
//     cehonFriendFileTransferRequestReceived = env->GetMethodID(JChatEventHandler, "onFriendFileTransferRequestReceived", "(JLjava/lang/String;JJ)V");
     cehOnSDKError = env->GetMethodID(JChatEventHandler, "onSDKError", "(ILjava/lang/String;)V");
     cehOnFriendHistoryMessageReceived = env->GetMethodID(JChatEventHandler, "onFriendHistoryMessageReceived", "(JJLjava/util/ArrayList;I)V");
     cehOnFriendMessagesStatusReceived = env->GetMethodID(JChatEventHandler, "onFriendMessagesStatusReceived", "(JJLjava/util/ArrayList;)V");
     cehOnFriendHistoryCompleted = env->GetMethodID(JChatEventHandler, "onFriendHistoryCompleted", "(JJI)V");
     cehOnGroupHistoryMessageReceived = env->GetMethodID(JChatEventHandler, "onGroupHistoryMessageReceived", "(JLjava/util/ArrayList;I)V");
     cehOnGroupHistoryCompleted = env->GetMethodID(JChatEventHandler, "onGroupHistoryCompleted", "(JI)V");
     cehOnGroupInformationWithMembersReceived = env->GetMethodID(JChatEventHandler, "onGroupInformationWithMembersReceived", "(JLjava/lang/String;Ljava/lang/String;Ljava/util/ArrayList;)V");
     cehOnGroupInformationWithMembersRequestStatus = env->GetMethodID(JChatEventHandler, "onGroupInformationWithMembersRequestStatus", "(JLjava/lang/String;Z)V");
     cehOnGroupInformationActivityReceived = env->GetMethodID(JChatEventHandler, "onGroupInformationActivityReceived", "(Ljava/util/ArrayList;)V");
     cehOnGroupInformationActivityFromHistoryMessageReceived = env->GetMethodID(JChatEventHandler, "onGroupInformationActivityFromHistoryMessageReceived", "(JLjava/util/ArrayList;I)V");
     cehOnMyGroupListReceived = env->GetMethodID(JChatEventHandler, "onMyGroupListReceived", "(Ljava/util/ArrayList;)V");
     cehOnMyGroupListPagingReceived = env->GetMethodID(JChatEventHandler, "onMyGroupListPagingReceived", "(Ljava/util/ArrayList;Ljava/lang/String;I)V");
     cehOnMyGroupListReceiveCompleted = env->GetMethodID(JChatEventHandler, "onMyGroupListReceiveCompleted", "()V");
     cehOnGroupCreated = env->GetMethodID(JChatEventHandler, "onGroupCreated", "(JLjava/lang/String;Z)V");
     cehOnGroupInformationChangeRequestStatus = env->GetMethodID(JChatEventHandler, "onGroupInformationChangeRequestStatus", "(JLjava/lang/String;Z)V");
     cehOnGroupNameChanged = env->GetMethodID(JChatEventHandler, "onGroupNameChanged", "(Ljava/lang/String;JJLjava/lang/String;)V");
     cehOnGroupUrlChanged = env->GetMethodID(JChatEventHandler, "onGroupUrlChanged", "(Ljava/lang/String;JJLjava/lang/String;)V");
     cehOnFriendHistoryMessageRequestStatus = env->GetMethodID(JChatEventHandler, "onFriendHistoryMessageRequestStatus", "(JJLjava/lang/String;Z)V");
     cehOnGroupHistoryMessageRequestStatus = env->GetMethodID(JChatEventHandler, "onGroupHistoryMessageRequestStatus", "(JLjava/lang/String;Z)V");;
     
    cehOnPublicRoomChatRegisterSuccess = env->GetMethodID(JChatEventHandler, "onPublicRoomChatRegisterSuccess", "(Ljava/lang/String;Ljava/lang/String;IJ)V");
    cehOnPublicRoomChatRegisterFailure = env->GetMethodID(JChatEventHandler, "onPublicRoomChatRegisterFailure", "(Ljava/lang/String;Ljava/lang/String;)V");
    cehOnPublicRoomChatRegistrationExpired = env->GetMethodID(JChatEventHandler, "onPublicRoomChatRegistrationExpired", "(Ljava/lang/String;)V");
    cehOnPublicRoomChatDelivered = env->GetMethodID(JChatEventHandler, "onPublicRoomChatDelivered", "(Ljava/lang/String;Ljava/lang/String;Z)V");
    cehOnPublicRoomChatFailedToSend = env->GetMethodID(JChatEventHandler, "onPublicRoomChatFailedToSend", "(Ljava/lang/String;Ljava/lang/String;)V");
    cehOnPublicRoomChatReceived = env->GetMethodID(JChatEventHandler, "onPublicRoomChatReceived", "(Ljava/lang/String;JLjava/lang/String;ILjava/lang/String;JLjava/lang/String;Ljava/lang/String;)V");
    cehOnPublicRoomListReceived = env->GetMethodID(JChatEventHandler, "onPublicRoomListReceived", "(Ljava/util/ArrayList;Z)V");
    cehOnPublicRoomInformationReceived = env->GetMethodID(JChatEventHandler, "onPublicRoomInformationReceived", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    cehOnPublicRoomChatHistoryReceived = env->GetMethodID(JChatEventHandler, "onPublicRoomChatHistoryReceived", "(Ljava/lang/String;Ljava/util/ArrayList;)V");
    cehOnPublicRoomChatHistoryCompleted = env->GetMethodID(JChatEventHandler, "onPublicRoomChatHistoryCompleted", "(Ljava/lang/String;)V");
    cehOnPublicRoomChatEdited = env->GetMethodID(JChatEventHandler, "onPublicRoomChatEdited", "(Ljava/lang/String;JLjava/lang/String;ILjava/lang/String;JLjava/lang/String;Ljava/lang/String;)V"); 
    cehOnPublicRoomChatTyping = env->GetMethodID(JChatEventHandler, "onPublicRoomChatTyping", "(Ljava/lang/String;JLjava/lang/String;)V");
    cehonPublicChatMemberListReceived = env->GetMethodID(JChatEventHandler, "onPublicChatMemberListReceived", "(Ljava/lang/String;Ljava/lang/String;Ljava/util/ArrayList;)V");
    cehOnPublicChatMemberCountChanged = env->GetMethodID(JChatEventHandler, "onPublicChatMemberCountChanged", "(Ljava/lang/String;I)V");
    cehshouldCheckServerAddressForRoom = env->GetMethodID(JChatEventHandler, "shouldCheckServerAddressForRoom", "(Ljava/lang/String;)V");
    cehOnPublicRoomListRequestStatus = env->GetMethodID(JChatEventHandler, "onPublicRoomListRequestStatus", "(Ljava/lang/String;Z)V");
    cehOnPublicRoomInformationRequestFailed = env->GetMethodID(JChatEventHandler, "onPublicRoomInformationRequestFailed", "(Ljava/lang/String;Ljava/lang/String;)V");
    cehOnPublicRoomChatHistoryRequestStatus = env->GetMethodID(JChatEventHandler, "onPublicRoomChatHistoryRequestStatus", "(Ljava/lang/String;Ljava/lang/String;Z)V");
    cehOnPublicRoomMemberListRequestStatus = env->GetMethodID(JChatEventHandler, "onPublicRoomMemberListRequestStatus", "(Ljava/lang/String;Ljava/lang/String;Z)V");
    
    cehOnShadowIdsInfoRequestFailed = env->GetMethodID(JChatEventHandler, "onShadowIdsInfoRequestFailed", "(Ljava/lang/String;)V");
    cehOnShadowIdsInfoResponseReceived = env->GetMethodID(JChatEventHandler, "onShadowIdsInfoResponseReceived", "(Ljava/util/ArrayList;)V");
    cehOnGroupChatMessageSeenListReceived = env->GetMethodID(JChatEventHandler, "onGroupChatMessageSeenListReceived", "(JLjava/lang/String;Ljava/util/ArrayList;)V");
    cehOnFriendChatConversationListReceived = env->GetMethodID(JChatEventHandler, "onFriendChatConversationListReceived", "(JLjava/util/ArrayList;Z)V");

            
    cehOnGroupChatConversationListReceived = env->GetMethodID(JChatEventHandler, "onGroupChatConversationListReceived", "(Ljava/util/ArrayList;Z)V");
    cehOnChatConversationListRequestStatus = env->GetMethodID(JChatEventHandler, "onChatConversationListRequestStatus", "(JJLjava/lang/String;Z)V");
    cehOnChatConversationListCompleted = env->GetMethodID(JChatEventHandler, "onChatConversationListCompleted", "(JZ)V");
    cehOnConversationListDeleteRequestStatus = env->GetMethodID(JChatEventHandler, "onConversationListDeleteRequestStatus", "(JLjava/lang/String;Z)V");
    cehOnConversationListMarkAsSeenRequestStatus = env->GetMethodID(JChatEventHandler, "onConversationListMarkAsSeenRequestStatus", "(JLjava/lang/String;Z)V");
    cehOnNetworkDataCounted = env->GetMethodID(JChatEventHandler, "onNetworkDataCounted", "(Lcom/ringid/imsdk/DataCounter;)V");
    
    cehOnPublicChatMessageDeleted = env->GetMethodID(JChatEventHandler, "onPublicChatMessageDeleted", "(Ljava/lang/String;Ljava/util/ArrayList;)V");
    cehOnPublicChatMessageLiked = env->GetMethodID(JChatEventHandler, "onPublicChatMessageLiked", "(Ljava/lang/String;Ljava/lang/String;J)V");
    cehOnPublicChatMessageUnliked = env->GetMethodID(JChatEventHandler, "onPublicChatMessageUnliked", "(Ljava/lang/String;Ljava/lang/String;J)V");
    cehOnPublicChatMessageReported = env->GetMethodID(JChatEventHandler, "onPublicChatMessageReported", "(Ljava/lang/String;Ljava/lang/String;J)V");
    
    cehOnPublicChatCategoryListReceived = env->GetMethodID(JChatEventHandler, "onPublicChatCategoryListReceived", "(Ljava/util/ArrayList;)V");
    cehOnPublicChatLikeMemberListReceived = env->GetMethodID(JChatEventHandler, "onPublicChatLikeMemberListReceived", "(Ljava/lang/String;Ljava/lang/String;Ljava/util/ArrayList;)V");
    
    cehOnPublicChatDeleteRequestStatus = env->GetMethodID(JChatEventHandler, "onPublicChatDeleteRequestStatus", "(Ljava/lang/String;Ljava/lang/String;Z)V");
    cehOnPublicChatLikeUnlikeRequestStatus = env->GetMethodID(JChatEventHandler, "onPublicChatLikeUnlikeRequestStatus", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ZZ)V");
    cehOnPublicChatReportRequestStatus = env->GetMethodID(JChatEventHandler, "onPublicChatReportRequestStatus", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");
    cehOnPublicChatLikeMemberListRequestStatus = env->GetMethodID(JChatEventHandler, "onPublicChatLikeMemberListRequestStatus", "(Ljava/lang/String;Ljava/lang/String;Z)V");
    cehOnPublicChatCategoryListRequestStatus = env->GetMethodID(JChatEventHandler, "onPublicChatCategoryListRequestStatus", "(Ljava/lang/String;Z)V");
    
    //Chunk chat media transfer
    cehOnFriendFileManifestUploaded = env->GetMethodID(JChatEventHandler, "onFriendFileManifestUploaded", "(JJLjava/lang/String;Ljava/lang/String;IILjava/lang/String;II)V");
    cehOnFriendIncomingChatMedia = env->GetMethodID(JChatEventHandler, "onFriendIncomingChatMedia", "(JJLjava/lang/String;Ljava/lang/String;IIJZLjava/lang/String;II)V");
    cehOnFriendChatMediaTransferProgress = env->GetMethodID(JChatEventHandler, "onFriendChatMediaTransferProgress", "(JJLjava/lang/String;DZLjava/lang/String;)V");
    cehOnFriendChatMediaTransferFailed = env->GetMethodID(JChatEventHandler, "onFriendChatMediaTransferFailed", "(JJLjava/lang/String;Ljava/lang/String;ZZ)V");
    cehOnFriendChatMediaTransferCanceled = env->GetMethodID(JChatEventHandler, "onFriendChatMediaTransferCanceled", "(JJJLjava/lang/String;Ljava/lang/String;ZZ)V");
    cehOnFriendChatMediaDownloadCompleted = env->GetMethodID(JChatEventHandler, "onFriendChatMediaDownloadCompleted", "(JJLjava/lang/String;Ljava/lang/String;II)V");
    cehOnGroupFileManifestUploaded = env->GetMethodID(JChatEventHandler, "onGroupFileManifestUploaded", "(JLjava/lang/String;Ljava/lang/String;ILjava/lang/String;II)V");
    cehOnGroupIncomingChatMedia = env->GetMethodID(JChatEventHandler, "onGroupIncomingChatMedia", "(JJLjava/lang/String;Ljava/lang/String;IJLjava/lang/String;II)V");
    cehOnGroupChatMediaTransferProgress = env->GetMethodID(JChatEventHandler, "onGroupChatMediaTransferProgress", "(JJLjava/lang/String;DZLjava/lang/String;)V");
    cehOnGroupChatMediaTransferFailed = env->GetMethodID(JChatEventHandler, "onGroupChatMediaTransferFailed", "(JJLjava/lang/String;Ljava/lang/String;ZZ)V");
    cehOnGroupChatMediaTransferCanceled = env->GetMethodID(JChatEventHandler, "onGroupChatMediaTransferCanceled", "(JJJLjava/lang/String;Ljava/lang/String;ZZ)V");
    cehOnGroupChatMediaDownloadCompleted = env->GetMethodID(JChatEventHandler, "onGroupChatMediaDownloadCompleted", "(JJLjava/lang/String;Ljava/lang/String;I)V");
	cehOnGeneralEncryptedPacketReceived = env->GetMethodID(JChatEventHandler, "onGeneralEncryptedPacketReceived", "(JJLjava/lang/String;IILjava/lang/String;)V");
	cehOnGeneralEncryptedPacketConfirmationReceived = env->GetMethodID(JChatEventHandler, "onGeneralEncryptedPacketConfirmationReceived", "(JJLjava/lang/String;II)V");
    
		cehOnChatMediaTransferDirectoryError = env->GetMethodID(JChatEventHandler, "onChatMediaTransferDirectoryError", "(Ljava/lang/String;)V");
    cehShouldUpdateAppSessionID = env->GetMethodID(JChatEventHandler, "shouldUpdateAppSessionID", "()V");
    cehOnActivaeOrDeactivateUserAccountStatus = env->GetMethodID(JChatEventHandler, "onActivaeOrDeactivateUserAccountStatus", "(JLjava/lang/String;ZZ)V");
    //Live stream chat message
    cehOnLiveStreamChatRegisterSuccess = env->GetMethodID(JChatEventHandler, "onLiveStreamChatRegisterSuccess", "(JLjava/lang/String;)V");
    cehOnLiveStreamChatRegisterFailure = env->GetMethodID(JChatEventHandler, "onLiveStreamChatRegisterFailure", "(JLjava/lang/String;)V");
    cehOnLiveStreamChatRegistrationExpired = env->GetMethodID(JChatEventHandler, "onLiveStreamChatRegistrationExpired", "(J)V");
    cehOnLiveStreamChatDelivered = env->GetMethodID(JChatEventHandler, "onLiveStreamChatDelivered", "(JLjava/lang/String;)V");
    cehOnLiveStreamChatFailedToSend = env->GetMethodID(JChatEventHandler, "onLiveStreamChatFailedToSend", "(JLjava/lang/String;)V");
    cehOnLiveStreamChatReceived = env->GetMethodID(JChatEventHandler, "onLiveStreamChatReceived", "(JJLjava/lang/String;ILjava/lang/String;JLjava/lang/String;)V");
    cehOnLiveStreamChatTyping = env->GetMethodID(JChatEventHandler, "onLiveStreamChatTyping", "(JJ)V");
    cehShouldCheckServerAddressForLiveStreamChat = env->GetMethodID(JChatEventHandler, "shouldCheckServerAddressForLiveStreamChat", "(J)V");
    cehOnLiveStreamChatBlockUserRequestStatus = env->GetMethodID(JChatEventHandler, "onLiveStreamChatBlockUserRequestStatus", "(JLjava/lang/String;)V");
    cehOnLiveStreamChatUserBlocked = env->GetMethodID(JChatEventHandler, "onLiveStreamChatUserBlocked", "(JJ)V");
    
    cehOnSyncConversationRequestStatus = env->GetMethodID(JChatEventHandler, "onSyncConversationRequestStatus", "(JLjava/lang/String;JZ)V");
    
    cehOnSyncFriendHistoryMessageRequestStatus = env->GetMethodID(JChatEventHandler, "onSyncFriendHistoryMessageRequestStatus", "(JJLjava/lang/String;JIZ)V");
    cehOnSyncFriendHistoryMessageReceived = env->GetMethodID(JChatEventHandler, "onSyncFriendHistoryMessageReceived", "(JJLjava/lang/String;Ljava/util/ArrayList;JI)V");
    cehOnSyncFriendHistoryMessageReceiveCompleted = env->GetMethodID(JChatEventHandler, "onSyncFriendHistoryMessageReceiveCompleted", "(JJLjava/lang/String;I)V");
    
    cehOnSyncGroupHistoryMessageRequestStatus = env->GetMethodID(JChatEventHandler, "onSyncGroupHistoryMessageRequestStatus", "(JLjava/lang/String;JIZ)V");
    cehOnSyncGroupHistoryMessageReceived = env->GetMethodID(JChatEventHandler, "onSyncGroupHistoryMessageReceived", "(JLjava/lang/String;Ljava/util/ArrayList;Ljava/util/ArrayList;JI)V");
    cehOnSyncGroupHistoryMessageReceiveCompleted = env->GetMethodID(JChatEventHandler, "onSyncGroupHistoryMessageReceiveCompleted", "(JLjava/lang/String;I)V");

    
    //     cehonFileTransferProgress = env->GetMethodID(JChatEventHandler, "onFileTransferProgress", "(JJJ)V");
//     cehonFileTransferCompleted = env->GetMethodID(JChatEventHandler, "onFileTransferCompleted", "(JJJ)V");
//     cehonFileTransferCanceled = env->GetMethodID(JChatEventHandler, "onFileTransferCanceled", "(JJJ)V");
//     cehonFileTransferFailed = env->GetMethodID(JChatEventHandler, "onFileTransferFailed", "(JJJ)V");
}

void onunloadChatEventHandler(JNIEnv *env)
{
    if (JChatEventHandler) {
        env->DeleteGlobalRef(JChatEventHandler);
    }
}


ChatEventHandler::ChatEventHandler(JavaVM* vm, JNIEnv *env, jobject jEventHandler) {

    this->javaVM = vm;
    this->eventHandler = env->NewGlobalRef(jEventHandler);
}

ChatEventHandler::~ChatEventHandler() {
}

void ChatEventHandler::onEventHandlerAttached() {
    JNIEnv *env;

    int getEnvStat = javaVM->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
#ifdef __ANDROID__        
        if (javaVM->AttachCurrentThread(&env, NULL) != 0) {
        }
#else
        if (javaVM->AttachCurrentThread((void **) &env, NULL) != 0) {
        }
#endif        
    } else if (getEnvStat == JNI_OK) {
        //
    } else if (getEnvStat == JNI_EVERSION) {
    }

    this->env = env;
}

void ChatEventHandler::onEventHandlerDetached() {
    javaVM->DetachCurrentThread();
}

void ChatEventHandler::onActivaeOrDeactivateUserAccountStatus(UserIdentity userId, const std::string &packetId, bool isAccountActivate, bool status)
{
    
}

void ChatEventHandler::onGetUserInfoReceived(UserIdentity userId, UserIdentity friendId, const std::string &packetId, std::string friendName, UserIdentity friendRingId, std::string friendProfileImageUrl, int friendProfileType)
{
    
}

void ChatEventHandler::onGetUserInfoFailure(UserIdentity userId, UserIdentity friendId, const std::string &packetId)
{
    
}

void ChatEventHandler::onFriendChatRegisterSuccess(UserIdentity userId, UserIdentity friendId, long long serverDate, const std::string &packetId, bool fromAnonymousUser) {
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnFriendChatRegisterSuccess, userId, friendId, serverDate, jpacketId, fromAnonymousUser);
    env->DeleteLocalRef(jpacketId);
    checkForException(env);
}

void ChatEventHandler::onFriendChatRegisterFailure(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool fromAnonymousUser) {
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnFriendChatRegisterFailure, userId, friendId, jpacketId, fromAnonymousUser);
    env->DeleteLocalRef(jpacketId);
    checkForException(env);
}

void ChatEventHandler::onFriendRegistrationExpired(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser) {
    env->CallVoidMethod(eventHandler, cehOnFriendRegistrationExpired, userId, friendId, fromAnonymousUser);
    checkForException(env);
}

void ChatEventHandler::onFriendUnregistered(UserIdentity userId, UserIdentity friendId, int onlineStatus, int onlineMood, bool fromAnonymousUser, int profileType) {
    env->CallVoidMethod(eventHandler, cehOnFriendUnregistered, userId, friendId, onlineStatus, onlineMood, fromAnonymousUser, profileType);
    checkForException(env);
}

void ChatEventHandler::onGroupChatRegisterSuccess(GroupIdentity groupId, long long serverDate, const std::string &packetId) {
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnGroupChatRegisterSuccess, groupId, serverDate, jpacketId);
    env->DeleteLocalRef(jpacketId);
    checkForException(env);
}

void ChatEventHandler::onGroupChatRegisterFailure(GroupIdentity groupId, const std::string &packetId) {
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnGroupChatRegisterFailure, groupId, jpacketId);
    env->DeleteLocalRef(jpacketId);
    checkForException(env);
}

void ChatEventHandler::onGroupRegistrationExpired(GroupIdentity groupId, long long lastActivityTime) {
    env->CallVoidMethod(eventHandler, cehOnGroupRegistrationExpired, groupId, lastActivityTime);
    checkForException(env);
}

void ChatEventHandler::onFriendChatReceived(UserIdentity senderId, UserIdentity receiverId, const std::string &packetId, int messageType, int timeout, const std::string &message, long long messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser) {
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jstring jmessage = toUtf8JString(env, message);
    
    env->CallVoidMethod(eventHandler, cehOnFriendChatReceived, senderId, receiverId, jpacketId, messageType, timeout, jmessage, messageDate, isSecretVisible, fromOnline, fromAnonymousUser);
    checkForException(env);
#ifdef __ANDROID__
     JNIEnv *env;

    int getEnvStat = javaVM->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
    } else if (getEnvStat == JNI_OK) {
    } else if (getEnvStat == JNI_EVERSION) {
    }
#endif
    
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jmessage);
}

void ChatEventHandler::onFriendChatDelivered(UserIdentity userId, UserIdentity friendid, const std::string &packetId, bool fromAnonymousUser, bool isEdited, bool fromOnline) {
    jstring jpacketId = env->NewStringUTF(packetId.c_str());

    env->CallVoidMethod(eventHandler, cehOnFriendChatDelivered, userId, friendid, jpacketId, fromAnonymousUser, isEdited, fromOnline);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onFriendChatSent(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool fromAnonymousUser) {
    jstring jpacketId = env->NewStringUTF(packetId.c_str());

    env->CallVoidMethod(eventHandler, cehOnFriendChatSent, userId, friendId, jpacketId, fromAnonymousUser);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onFriendChatFailedToSend(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool fromAnonymousUser) {
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnFriendChatFailedToSend, userId, friendId, jpacketId, fromAnonymousUser);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onFriendChatSeen(UserIdentity userId, UserIdentity friendid, const std::vector<SeenPacketDTO> &seenPacketList, bool fromAnonymousUser) {
    jobject jseenPacketList = getJSeenPacketList(env, seenPacketList);

    env->CallVoidMethod(eventHandler, cehOnFriendChatSeen, userId, friendid, jseenPacketList, fromAnonymousUser);
    checkForException(env);
    env->DeleteLocalRef(jseenPacketList);
}

void ChatEventHandler::onFriendChatSeenConfirmed(UserIdentity userId, UserIdentity friendid, std::vector<SeenPacketDTO> &seenPacketList, bool fromAnonymousUser) {
    jobject jseenPacketList = getJSeenPacketList(env, seenPacketList);

    env->CallVoidMethod(eventHandler, cehOnFriendChatSeenConfirmed, userId, friendid, jseenPacketList, fromAnonymousUser);
    checkForException(env);
    env->DeleteLocalRef(jseenPacketList);
}

void ChatEventHandler::onFriendChatTyping(UserIdentity userId, UserIdentity friendid, bool fromAnonymousUser) {
    env->CallVoidMethod(eventHandler, cehOnFriendChatTyping, userId, friendid, fromAnonymousUser);
    checkForException(env);
}

void ChatEventHandler::onFriendChatIdle(UserIdentity friendid, bool fromAnonymousUser) {
    env->CallVoidMethod(eventHandler, cehOnFriendChatIdle, friendid, fromAnonymousUser);
    checkForException(env);
}

void ChatEventHandler::onFriendChatEdited(UserIdentity senderId, UserIdentity receiverId, const std::string &packetId, int messageType, int timeout, const std::string &message, long long messageDate, bool isSecretVisible, bool fromOnline, bool fromAnonymousUser) {
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jstring jmessage = toUtf8JString(env, message);;

    env->CallVoidMethod(eventHandler, cehOnFriendChatEdited, senderId, receiverId, jpacketId, messageType, timeout, jmessage, messageDate, isSecretVisible, fromOnline, fromAnonymousUser);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jmessage);
}

void ChatEventHandler::onFriendChatDeleted(UserIdentity senderId, UserIdentity friendid, const std::vector<std::string> &packetId, bool fromAnonymousUser) {
    jobject jpacketIds = getNewArrayList(env);
    for (int i=0; i<packetId.size(); i++)
    {
        jobject packetIdList = (jobject)env->NewStringUTF(packetId[i].c_str());
        arrayListAdd(env, jpacketIds, packetIdList);
        env->DeleteLocalRef(packetIdList);
    }

    env->CallVoidMethod(eventHandler, cehOnFriendChatDeleted, senderId, friendid, jpacketIds, fromAnonymousUser);
    checkForException(env);
    env->DeleteLocalRef(jpacketIds);
}

void ChatEventHandler::onFriendChatDeleteRequestStatus(UserIdentity userId, UserIdentity friendid, const std::string &packetId, const std::vector<std::string> &packetIds, bool fromAnonymousUser, bool status, int deleteType) {
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jobject jpacketIds = getNewArrayList(env);
    for (int i=0; i<packetIds.size(); i++)
    {
        jobject jpacketId = (jobject)env->NewStringUTF(packetIds[i].c_str());
        arrayListAdd(env, jpacketIds, jpacketId);
        env->DeleteLocalRef(jpacketId);
    }

    env->CallVoidMethod(eventHandler, cehOnFriendChatDeleteRequestStatus, userId, friendid, jpacketId, jpacketIds, fromAnonymousUser, status, deleteType);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jpacketIds);
}

void ChatEventHandler::onBlocked(UserIdentity blockerId, UserIdentity blockedId, long long blockUnblockDate, bool addToBlock) {
    env->CallVoidMethod(eventHandler, cehOnBlocked, blockerId, blockedId, blockUnblockDate, addToBlock);
    checkForException(env);
}

void ChatEventHandler::onUnblocked(UserIdentity blockerId, UserIdentity blockedId, long long blockUnblockDate) {
    env->CallVoidMethod(eventHandler, cehOnUnblocked, blockerId, blockedId, blockUnblockDate);
    checkForException(env);
}

void ChatEventHandler::onBlockUnblockRequestStatus(UserIdentity userId, UserIdentity friendid, const std::string &packetId, long long blockUnblockDate, bool status, bool isBlockRequest) {
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnBlockUnblockRequestStatus, userId, friendid, jpacketId, blockUnblockDate, status, isBlockRequest);
    env->DeleteLocalRef(jpacketId);
    checkForException(env);
}

void ChatEventHandler::onGroupChatSent(GroupIdentity groupId, const std::string &packetId, bool isEdited) {
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnGroupChatSent, groupId, jpacketId, isEdited);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onGroupChatReceived(UserIdentity senderId, GroupIdentity groupid, const std::string &packetId, int messageType, const std::string &message, long long messageDate, bool fromOnline) {
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jstring jmessage = toUtf8JString(env, message);
    
    env->CallVoidMethod(eventHandler, cehOnGroupChatReceived, senderId, groupid, jpacketId, messageType, jmessage, messageDate, fromOnline);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jmessage);
}

void ChatEventHandler::onGroupChatEdited(UserIdentity senderId, GroupIdentity groupId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, bool fromOnline){
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jstring jmessage = toUtf8JString(env, message);;
    
    env->CallVoidMethod(eventHandler, cehOnGroupChatEdited, senderId, groupId, jpacketId, messageType, jmessage, messageDate, fromOnline);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jmessage);
}

void ChatEventHandler::onGroupChatDelivered(UserIdentity friendid, GroupIdentity groupid, const std::string &packetId) {
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnGroupChatDelivered, friendid, groupid, jpacketId);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onGroupChatSeen(GroupIdentity groupid, UserIdentity userId, const std::vector<std::string> &packetIds) {
        
    jobject jpacketIds = getNewArrayList(env);
    for (int i=0; i<packetIds.size(); i++)
    {
        jobject packetIdList = (jobject)env->NewStringUTF(packetIds[i].c_str());
        arrayListAdd(env, jpacketIds, packetIdList);
        env->DeleteLocalRef(packetIdList);
    }
    
    env->CallVoidMethod(eventHandler, cehOnGroupChatSeen, groupid, userId, jpacketIds);
    checkForException(env);
    env->DeleteLocalRef(jpacketIds);
}

void ChatEventHandler::onGroupChatSeenRequestStatus(GroupIdentity groupid, const std::vector<std::string> &packetIds, bool status)
{
    jobject jpacketIds = getNewArrayList(env);
    for (int i=0; i<packetIds.size(); i++)
    {
        jobject packetIdList = (jobject)env->NewStringUTF(packetIds[i].c_str());
        arrayListAdd(env, jpacketIds, packetIdList);
        env->DeleteLocalRef(packetIdList);
    }
    
    env->CallVoidMethod(eventHandler, cehOnGroupChatSeenRequestStatus, groupid, jpacketIds, status);
    checkForException(env);
    env->DeleteLocalRef(jpacketIds);
}

void ChatEventHandler::onGroupChatTyping(UserIdentity friendid, GroupIdentity groupid) {
    env->CallVoidMethod(eventHandler, cehOnGroupChatTyping, friendid, groupid);
    checkForException(env);
}

void ChatEventHandler::onGroupChatIdle(UserIdentity friendid, GroupIdentity groupid) {
    env->CallVoidMethod(eventHandler, cehOnGroupChatIdle, friendid, groupid);
    checkForException(env);
}

void ChatEventHandler::onGroupMemberRemoveLeaveRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::vector<MemberDTO> &memberList, bool isHide){
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnGroupMemberRemoveLeaveRequestStatus, groupId, jpacketId, status, isHide);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onGroupMemberAddRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::vector<MemberDTO> &memberList){
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jobject jmemberList = getJMemberList(env, memberList);
    
    env->CallVoidMethod(eventHandler, cehOnGroupMemberAddRequestStatus, groupId, jpacketId, status, jmemberList);
    checkForException(env);
    
    env->DeleteLocalRef(jmemberList);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onGroupNameChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::string &groupName)
{
    jstring jpacketId = env->NewStringUTF(packetId.c_str());

    env->CallVoidMethod(eventHandler, cehOnGroupInformationChangeRequestStatus, groupId, jpacketId, status);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onGroupUrlChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::string &groupUrl)
{
    jstring jpacketId = env->NewStringUTF(packetId.c_str());

    env->CallVoidMethod(eventHandler, cehOnGroupInformationChangeRequestStatus, groupId, jpacketId, status);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onGroupMemberStatusChangeRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status, const std::vector<MemberDTO> &memberList){
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnGroupMemberStatusChangeRequestStatus, groupId, jpacketId, status);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onGroupMemberRemovedOrLeft(UserIdentity friendid, GroupIdentity groupid, const std::vector<UserIdentity> &memberList, const std::string &packetId, bool isHide) {
    jobject jmemberIds = getNewArrayList(env);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jclass cls = env->FindClass("java/lang/Long");
    jmethodID longConstructor = env->GetMethodID(cls,"<init>","(J)V");
    
    for (int i=0; i<memberList.size(); i++)
    {
        jlong memberId = memberList[i];
        jobject obj = env->NewObject(cls, longConstructor, memberId);
        arrayListAdd(env, jmemberIds, obj);
        env->DeleteLocalRef(obj);
    }
    
    env->CallVoidMethod(eventHandler, cehOnGroupMemberRemovedOrLeft, friendid, groupid, jmemberIds, jpacketId, isHide);
    checkForException(env);
    env->DeleteLocalRef(cls);
    env->DeleteLocalRef(jmemberIds);
}

void ChatEventHandler::onGroupMemberAdded(UserIdentity friendid, GroupIdentity groupid, const std::vector<MemberDTO> &memberList, const std::string &packetId) {
    jobject jmemberList = getJMemberList(env, memberList);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnGroupMemberAdded, friendid, groupid, jmemberList, jpacketId);
    checkForException(env);
    env->DeleteLocalRef(jmemberList);
}

void ChatEventHandler::onGroupMemberStatusChanged(UserIdentity senderid, GroupIdentity groupid, const std::vector<MemberDTO> &memberList, const std::string &packetId) {
    jobject jmemberList = getJMemberList(env, memberList);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnGroupMemberStatusChanged, senderid, groupid, jmemberList, jpacketId);
    checkForException(env);
    env->DeleteLocalRef(jmemberList);
}

void ChatEventHandler::onGroupChatFailedToSend(GroupIdentity groupId, const std::string &packetId)
{
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnGroupChatFailedToSend, groupId, jpacketId);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::shouldCheckFriendPresence(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser, int profileType) {
    env->CallVoidMethod(eventHandler, cehShouldCheckFreindPresence, userId, friendId, fromAnonymousUser, profileType);
    checkForException(env);
}

void ChatEventHandler::shouldCheckServerAddressForFriend(UserIdentity userId, UserIdentity friendId, bool fromAnonymousUser) {
    env->CallVoidMethod(eventHandler, cehShouldCheckServerAddressForFriend, userId, friendId, fromAnonymousUser);
    checkForException(env);
}

void ChatEventHandler::shouldCheckServerAddressForGroup(GroupIdentity groupId)
{
    env->CallVoidMethod(eventHandler, cehShouldCheckServerAddressForGroup, groupId);
    checkForException(env);
}

void ChatEventHandler::shouldCheckOfflineServerAddress()
{
    env->CallVoidMethod(eventHandler, cehShouldCheckOfflineServerAddress);
    checkForException(env);
}

void ChatEventHandler::onServerTimeSynced(long long timeDifference)
{
    env->CallVoidMethod(eventHandler, cehOnServerTimeSynced, timeDifference);
    checkForException(env);
}

void ChatEventHandler::shouldUpdateUserPassword()
{
    env->CallVoidMethod(eventHandler, cehShouldUpdateUserPassword);
    checkForException(env);
}

void ChatEventHandler::onGroupChatDeleted(UserIdentity friendid, GroupIdentity groupid, const std::vector<std::string> &packetIds){
    jobject jpacketIds = getNewArrayList(env);
    for (int i=0; i<packetIds.size(); i++)
    {
        jobject packetIdList = (jobject)env->NewStringUTF(packetIds[i].c_str());
        arrayListAdd(env, jpacketIds, packetIdList);
        env->DeleteLocalRef(packetIdList);
    }
    
    env->CallVoidMethod(eventHandler, cehOnGroupChatDeleted, friendid, groupid, jpacketIds);
    checkForException(env);
    env->DeleteLocalRef(jpacketIds);
}

void ChatEventHandler::onGroupChatDeleteRequestStatus(GroupIdentity groupid, const std::string &packetId, const std::vector<std::string> &packetIds, bool status){
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    jobject jpacketIds = getNewArrayList(env);
    for (int i=0; i<packetIds.size(); i++)
    {
        jobject packetIdList = (jobject)env->NewStringUTF(packetIds[i].c_str());
        arrayListAdd(env, jpacketIds, packetIdList);
        env->DeleteLocalRef(packetIdList);
    }

    env->CallVoidMethod(eventHandler, cehOnGroupChatDeleteRequestStatus, groupid, jpacketId, jpacketIds, status);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jpacketIds);
}

//void ChatEventHandler::onFriendFileTransferRequestReceived(UserIdentity friendId, std::string fileName, FileIdentity fileId, long long fileSize){
//    Log(module, "onFriendFileTransferRequestReceived event called ");
//    jstring jfileName = env->NewStringUTF(fileName.c_str());
//
//    env->CallVoidMethod(eventHandler, cehonFriendFileTransferRequestReceived, friendId, jfileName, fileId, fileSize);
//}
//
//void ChatEventHandler::onFileTransferProgress(IPVLongType fileID, IPVLongType friendName, IPVLongType receivedLength){
//    Log(module, "JNI: onFileTransferProgress event called, Received bytes "<<receivedLength);
//
//    env->CallVoidMethod(eventHandler, cehonFileTransferProgress, fileID, friendName, receivedLength);
//}
//
//void ChatEventHandler::onFileTransferCompleted(IPVLongType fileID, IPVLongType friendName, IPVLongType receivedLength){
//    Log(module, "JNI: onFileTransferCompleted event called, Received bytes "<<receivedLength);
//
//    env->CallVoidMethod(eventHandler, cehonFileTransferCompleted, fileID, friendName, receivedLength);
//}
//
//void ChatEventHandler::onFileTransferCanceled(IPVLongType fileID, IPVLongType friendName, IPVLongType receivedLength){
//    Log(module, "JNI: onFileTransferCanceled event called, Received bytes "<<receivedLength);
//
//    env->CallVoidMethod(eventHandler, cehonFileTransferCanceled, fileID, friendName, receivedLength);
//}
//
//void ChatEventHandler::onFileTransferFailed(IPVLongType fileID, IPVLongType friendName, IPVLongType receivedLength){
//    Log(module, "JNI: onFileTransferFailed event called, Received bytes "<<receivedLength);
//
//    env->CallVoidMethod(eventHandler, cehonFileTransferFailed, fileID, friendName, receivedLength);
//}

void ChatEventHandler::onSDKError(int errorCode, const std::string &packetId) {
    jstring jpacketId = env->NewStringUTF(packetId.c_str());

    env->CallVoidMethod(eventHandler, cehOnSDKError, errorCode, jpacketId);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onFriendHistoryMessageReceived(UserIdentity userId, UserIdentity friendId, const std::vector<SDKMessageDTO> &friendHistoryMessageList, int direction) {
    
    jobject jfriendHistoryMessageList = getJMessageList(env, friendHistoryMessageList);
    env->CallVoidMethod(eventHandler, cehOnFriendHistoryMessageReceived, userId, friendId, jfriendHistoryMessageList, direction);
    checkForException(env);
    env->DeleteLocalRef(jfriendHistoryMessageList);
}

void ChatEventHandler::onFriendMessagesStatusReceived(UserIdentity userId, UserIdentity friendId, const std::vector<FriendMessageStatusDTO> &messageList) {
    
    jobject jmessageList = getJFriendMessageStatusList(env, messageList);

    env->CallVoidMethod(eventHandler, cehOnFriendMessagesStatusReceived, userId, friendId, jmessageList);
    checkForException(env);
    env->DeleteLocalRef(jmessageList);
}

void ChatEventHandler::onFriendHistoryCompleted(UserIdentity userId, UserIdentity friendId, int direction){
    env->CallVoidMethod(eventHandler, cehOnFriendHistoryCompleted, userId, friendId, direction);
    checkForException(env);
}

void ChatEventHandler::onGroupHistoryMessageReceived(GroupIdentity groupId, const std::vector<SDKMessageDTO> &groupHistoryMessageList, int direction) {
    jobject jgroupHistoryMessageList = getJMessageList(env, groupHistoryMessageList);

    env->CallVoidMethod(eventHandler, cehOnGroupHistoryMessageReceived, groupId, jgroupHistoryMessageList, direction);
    checkForException(env);
}

void ChatEventHandler::onGroupHistoryCompleted(GroupIdentity groupId, int direction){
    env->CallVoidMethod(eventHandler, cehOnGroupHistoryCompleted, groupId, direction);
    checkForException(env);
}

void ChatEventHandler::onGroupInformationWithMembersReceived(GroupIdentity groupId, const std::string &groupName, const std::string &groupUrl, const std::vector<MemberDTO> &memberList) {
    jstring jgroupName = toUtf8JString(env, groupName);;
    jstring jgroupUrl = toUtf8JString(env, groupUrl);;
    
    jobject jmemberList = getJMemberList(env, memberList);

    env->CallVoidMethod(eventHandler, cehOnGroupInformationWithMembersReceived, groupId, jgroupName, jgroupUrl, jmemberList);
    checkForException(env);
            
    env->DeleteLocalRef(jgroupName);
    env->DeleteLocalRef(jgroupUrl);
    env->DeleteLocalRef(jmemberList);
}

void ChatEventHandler::onGroupInformationWithMembersRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status){
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnGroupInformationWithMembersRequestStatus, groupId, jpacketId, status);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onGroupInformationActivityReceived(const std::vector<GroupActivityDTO> &groupActivityList) {
    Log(module, "jni : onGroupInformationActivityReceived size : "<<groupActivityList.size());
    jobject jgroupActivityList = getJGroupActivityList(env, groupActivityList);
    Log(module, "jni : onGroupInformationActivityReceived completed");
    
    env->CallVoidMethod(eventHandler, cehOnGroupInformationActivityReceived, jgroupActivityList);

    checkForException(env);
    
    env->DeleteLocalRef(jgroupActivityList);
}

void ChatEventHandler::onGroupInformationActivityFromHistoryMessageReceived(GroupIdentity groupId, const std::vector<GroupActivityDTO> &groupActivityList, int direction) {
    jobject jgroupActivityList = getJGroupActivityList(env, groupActivityList);

    env->CallVoidMethod(eventHandler, cehOnGroupInformationActivityFromHistoryMessageReceived, groupId, jgroupActivityList, direction);
    checkForException(env);
    env->DeleteLocalRef(jgroupActivityList);
}

void ChatEventHandler::onMyGroupListReceived(const std::vector<GroupDTO> &myGroupList) {
    jobject jmygroupList = getJGroupList(env, myGroupList);

    env->CallVoidMethod(eventHandler, cehOnMyGroupListReceived, jmygroupList);
    checkForException(env);
    env->DeleteLocalRef(jmygroupList);
}


void ChatEventHandler::onMyGroupListPagingReceived(const std::vector<GroupDTO> &myGroupList, const std::string &pivotId, int direction) {
    jobject jmygroupList = getJGroupList(env, myGroupList);
    jstring jpivotId = env->NewStringUTF(pivotId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnMyGroupListPagingReceived, jmygroupList, jpivotId, direction);
    checkForException(env);
    
    env->DeleteLocalRef(jmygroupList);
    env->DeleteLocalRef(jpivotId);
}

void ChatEventHandler::onMyGroupListReceiveCompleted() {
    env->CallVoidMethod(eventHandler, cehOnMyGroupListReceiveCompleted);
    checkForException(env);
}

void ChatEventHandler::onGroupCreated(GroupIdentity groupId, const std::string &packetId, bool status) {
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnGroupCreated, groupId, jpacketId, status);
    env->DeleteLocalRef(jpacketId);
    checkForException(env);
}

void ChatEventHandler::onGroupNameChanged(const std::string &packetId, UserIdentity friendid, GroupIdentity groupid, const std::string &groupName) {
    jstring jgroupName = toUtf8JString(env, groupName);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());

    env->CallVoidMethod(eventHandler, cehOnGroupNameChanged, jpacketId, friendid, groupid, jgroupName);
    checkForException(env);
    env->DeleteLocalRef(jgroupName);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onGroupUrlChanged(const std::string &packetId, UserIdentity friendid, GroupIdentity groupid, const std::string &groupUrl) {
    jstring jgroupUrl = toUtf8JString(env, groupUrl);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());

    env->CallVoidMethod(eventHandler, cehOnGroupUrlChanged, jpacketId, friendid, groupid, jgroupUrl);
    checkForException(env);
    env->DeleteLocalRef(jgroupUrl);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onFriendHistoryMessageRequestStatus(UserIdentity userId, UserIdentity friendId, const std::string &packetId, bool status){
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnFriendHistoryMessageRequestStatus, userId, friendId, jpacketId, status);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onGroupHistoryMessageRequestStatus(GroupIdentity groupId, const std::string &packetId, bool status){
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnGroupHistoryMessageRequestStatus, groupId, jpacketId, status);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onPublicRoomChatRegisterSuccess(RoomIdentity &roomId, const std::string &packetId, int numberOfMember, long long anonymousId){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnPublicRoomChatRegisterSuccess, jroomId, jpacketId, numberOfMember, anonymousId);
    checkForException(env);
    env->DeleteLocalRef(jroomId);
}

void ChatEventHandler::onPublicRoomChatRegisterFailure(RoomIdentity &roomId, const std::string &packetId){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnPublicRoomChatRegisterFailure, jroomId, jpacketId);
    checkForException(env);
    env->DeleteLocalRef(jroomId);
}

void ChatEventHandler::onPublicRoomChatRegistrationExpired(RoomIdentity& roomId){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnPublicRoomChatRegistrationExpired, jroomId);
    checkForException(env);
    env->DeleteLocalRef(jroomId);
}

void ChatEventHandler::onPublicRoomChatDelivered(RoomIdentity& roomId, const std::string &packetId, bool isEdited){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnPublicRoomChatDelivered, jroomId, jpacketId, isEdited);
    checkForException(env);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onPublicRoomChatFailedToSend(RoomIdentity &roomId, const std::string &packetId){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnPublicRoomChatFailedToSend, jroomId, jpacketId);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onPublicRoomChatReceived(RoomIdentity& roomId, UserIdentity friendId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, const std::string &memberFullName, const std::string &memberProfileUrl){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jstring jmessage = toUtf8JString(env, message);
    jstring jmemberFullName = toUtf8JString(env, memberFullName);
    jstring jmemberProfileUrl = toUtf8JString(env, memberProfileUrl);;
    
    env->CallVoidMethod(eventHandler, cehOnPublicRoomChatReceived, jroomId, friendId, jpacketId, messageType, jmessage, messageDate, jmemberFullName, jmemberProfileUrl);
    checkForException(env);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jmessage);
    env->DeleteLocalRef(jmemberFullName);
    env->DeleteLocalRef(jmemberProfileUrl);
}

void ChatEventHandler::onPublicRoomChatEdited(RoomIdentity& roomId, UserIdentity friendId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, const std::string &memberFullName, const std::string &memberProfileUrl){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jstring jmessage = toUtf8JString(env, message);
    jstring jmemberFullName = toUtf8JString(env, memberFullName);
    jstring jmemberProfileUrl = toUtf8JString(env, memberProfileUrl);;
    
    env->CallVoidMethod(eventHandler, cehOnPublicRoomChatEdited, jroomId, friendId, jpacketId, messageType, jmessage, messageDate, jmemberFullName, jmemberProfileUrl);
    checkForException(env);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jmessage);
    env->DeleteLocalRef(jmemberFullName);
    env->DeleteLocalRef(jmemberProfileUrl);
}

void ChatEventHandler::onPublicRoomChatTyping(RoomIdentity &roomId, UserIdentity friendId, const std::string &memberName){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jmemberName = toUtf8JString(env, memberName);;
    
    env->CallVoidMethod(eventHandler, cehOnPublicRoomChatTyping, jroomId, friendId, jmemberName);
    checkForException(env);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jmemberName);
}
void ChatEventHandler::onPublicRoomListReceived(const std::vector<RoomDTO>& roomList, bool roomListWithHistory){
    jobject jroomList = getJRoomList(env, roomList);
    
    env->CallVoidMethod(eventHandler, cehOnPublicRoomListReceived, jroomList, roomListWithHistory);
    checkForException(env);
    env->DeleteLocalRef(jroomList);
}

void ChatEventHandler::onPublicRoomInformationReceived(RoomIdentity &roomId, std::string &roomName, std::string &roomUrl, const std::string &packetId){
    jstring jroomId = toUtf8JString(env, roomId);
    jstring jroomName = toUtf8JString(env, roomName);
    jstring jroomUrl = toUtf8JString(env, roomUrl);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnPublicRoomInformationReceived, jroomId, jroomName, jroomUrl, jpacketId);
    checkForException(env);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jroomName);
    env->DeleteLocalRef(jroomUrl);    
}

void ChatEventHandler::onPublicRoomChatHistoryReceived(RoomIdentity& roomId, const std::vector<SDKMessageDTO> &messageList){
    jstring jroomId = toUtf8JString(env, roomId);
    jobject jmessageList = getJMessageList(env, messageList);
    
    env->CallVoidMethod(eventHandler, cehOnPublicRoomChatHistoryReceived, jroomId, jmessageList);

    checkForException(env);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jmessageList);
   
}

void ChatEventHandler::onPublicRoomChatHistoryCompleted(RoomIdentity &roomId){
    jstring jroomId = toUtf8JString(env, roomId);
    
    env->CallVoidMethod(eventHandler, cehOnPublicRoomChatHistoryCompleted, jroomId);

    checkForException(env);
    env->DeleteLocalRef(jroomId);
}

void ChatEventHandler::onPublicChatMemberListReceived(RoomIdentity &roomId, const std::string &pagingState, const std::vector<PublicChatMemberDTO> &publicChatMemberList){
    jobject jroomId = toUtf8JString(env, roomId);
    jobject jpagingState = NULL;
    if (pagingState != "") {
        jpagingState = toUtf8JString(env, pagingState);
    }
    jobject jpublicChatMemberList = getJPublicChatMemberList(env, publicChatMemberList);
    
    env->CallVoidMethod(eventHandler, cehonPublicChatMemberListReceived, jroomId, jpagingState, jpublicChatMemberList);
    checkForException(env);
    env->DeleteLocalRef(jpublicChatMemberList);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpagingState);
}

void ChatEventHandler::onPublicChatMemberCountChanged(RoomIdentity &roomId, int numberOfMembers){
    jobject jroomId = toUtf8JString(env, roomId);
    env->CallVoidMethod(eventHandler, cehOnPublicChatMemberCountChanged, jroomId, numberOfMembers);
    checkForException(env);
    env->DeleteLocalRef(jroomId);
}

void ChatEventHandler::shouldCheckServerAddressForRoom(RoomIdentity &roomId){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    
    env->CallVoidMethod(eventHandler, cehshouldCheckServerAddressForRoom, jroomId);
    checkForException(env);
    env->DeleteLocalRef(jroomId);
}

void ChatEventHandler::onPublicRoomListRequestStatus(const std::string &packetId, bool requestStatus){
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnPublicRoomListRequestStatus, jpacketId, requestStatus);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onPublicRoomInformationRequestFailed(RoomIdentity &roomId, const std::string &packetId){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnPublicRoomInformationRequestFailed, jroomId, jpacketId);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onPublicRoomChatHistoryRequestStatus(RoomIdentity &roomId, const std::string &packetId, bool requestStatus){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnPublicRoomChatHistoryRequestStatus, jroomId, jpacketId, requestStatus);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onPublicRoomMemberListRequestStatus(RoomIdentity &roomId, const std::string &packetId, bool requestStatus){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnPublicRoomMemberListRequestStatus, jroomId, jpacketId, requestStatus);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onShadowIdsInfoRequestFailed(const std::string &packetId){
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnShadowIdsInfoRequestFailed, jpacketId);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onShadowIdsInfoResponseReceived(const std::vector<PublicChatMemberDTO> &shadowIdsInfo){
    jobject jshadowIdInfo = getJPublicChatMemberList(env, shadowIdsInfo);

    env->CallVoidMethod(eventHandler, cehOnShadowIdsInfoResponseReceived, jshadowIdInfo);
    checkForException(env);
    env->DeleteLocalRef(jshadowIdInfo);
}

void ChatEventHandler::onFileStreamRequestReceived(UserIdentity userId, UserIdentity friendId, FileIdentity fileId){}
void ChatEventHandler::onFriendFileSessionRequestSuccess(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId, int fileTransferPort){}
void ChatEventHandler::onFriendFileTransferSessionRequestFailed(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId){}
void ChatEventHandler::onFriendFileStreamRequestSuccess(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId){}
void ChatEventHandler::onFriendFileTransferStreamRequestFailed(UserIdentity userId, const std::string &packetId, UserIdentity friendId, FileIdentity fileId){}

//Live stream chat
void ChatEventHandler::onLiveStreamChatRegisterSuccess(UserIdentity publisherId, const std::string &packetId)
{
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnLiveStreamChatRegisterSuccess, publisherId, jpacketId);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onLiveStreamChatRegisterFailure(UserIdentity publisherId, const std::string &packetId)
{
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnLiveStreamChatRegisterFailure, publisherId, jpacketId);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onLiveStreamChatRegistrationExpired(UserIdentity publisherId)
{
    env->CallVoidMethod(eventHandler, cehOnLiveStreamChatRegistrationExpired, publisherId);
    checkForException(env);
}

void ChatEventHandler::onLiveStreamChatDelivered(UserIdentity publisherId, const std::string &packetId)
{
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnLiveStreamChatDelivered, publisherId, jpacketId);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onLiveStreamChatFailedToSend(UserIdentity publisherId, const std::string &packetId)
{
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnLiveStreamChatFailedToSend, publisherId, jpacketId);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onLiveStreamChatReceived(UserIdentity publisherId, UserIdentity senderId, const std::string &packetId, int messageType, const std::string &message, long long messageDate, const std::string &senderFullName)
{
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jstring jmessage = toUtf8JString(env, message);
    jstring jsenderFullName = env->NewStringUTF(senderFullName.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnLiveStreamChatReceived, publisherId, senderId, jpacketId, messageType, jmessage, messageDate, jsenderFullName);
    checkForException(env);
    
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jmessage);
    env->DeleteLocalRef(jsenderFullName);
}

void ChatEventHandler::onLiveStreamChatTyping(UserIdentity publisherId, UserIdentity senderId)
{
    env->CallVoidMethod(eventHandler, cehOnLiveStreamChatTyping, publisherId, senderId);
    checkForException(env);
}

void ChatEventHandler::shouldCheckServerAddressForLiveStreamChat(UserIdentity publisherId)
{
    env->CallVoidMethod(eventHandler, cehShouldCheckServerAddressForLiveStreamChat, publisherId);
    checkForException(env);
}

void ChatEventHandler::onLiveStreamChatBlockUserRequestStatus(UserIdentity blockedUserId, const std::string &packetId)
{
    jstring jpacketId = env->NewStringUTF(packetId.c_str());

    env->CallVoidMethod(eventHandler, cehOnLiveStreamChatBlockUserRequestStatus, blockedUserId, jpacketId);

    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onLiveStreamChatUserBlocked(UserIdentity publisherId, UserIdentity blockedUserId)
{
    env->CallVoidMethod(eventHandler, cehOnLiveStreamChatUserBlocked, publisherId, blockedUserId);
    checkForException(env);
}

//Group file transfer
void ChatEventHandler::onGroupFileStreamRequestReceived(UserIdentity friendId, GroupIdentity groupId, FileIdentity fileId){}
void ChatEventHandler::onGroupFileSessionRequestSuccess(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId, int fileTransferPort){}
void ChatEventHandler::onGroupFileTransferSessionRequestFailed(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId){}
void ChatEventHandler::onGroupFileStreamRequestSuccess(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId){}
void ChatEventHandler::onGroupFileTransferStreamRequestFailed(const std::string &packetId, GroupIdentity groupId, FileIdentity fileId){}

void ChatEventHandler::onFriendGetChatMessageReceived(UserIdentity userId, UserIdentity friendId, const SDKMessageDTO& friendChatMessageDTO){}

void ChatEventHandler::onGroupGetChatMessageReceived(GroupIdentity groupId, const SDKMessageDTO& groupChatMessageDTO){}

void ChatEventHandler::onFriendGetChatMessageFailedToSend(UserIdentity userId, UserIdentity friendId, const std::string &packetId){}

void ChatEventHandler::onGroupGetChatMessageFailedToSend(GroupIdentity groupId, const std::string &packetId){}

void ChatEventHandler::onNetworkDataCounted(const DataCounter& dataCounter){
    jobject jDataCounter = getJDataCounter(env, dataCounter);
    env->CallVoidMethod(eventHandler, cehOnNetworkDataCounted, jDataCounter);
    checkForException(env);
    env->DeleteLocalRef(jDataCounter);
}

void ChatEventHandler::onGroupChatMessageSeenListReceived(GroupIdentity groupId, const std::string &packetId, const std::vector<MemberDTO> &memberList){
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jobject jmemberList = getJMemberList(env, memberList);

    env->CallVoidMethod(eventHandler, cehOnGroupChatMessageSeenListReceived, groupId, jpacketId, jmemberList);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jmemberList);
}

void ChatEventHandler::onGroupChatMessageSeenListRequestStatus(GroupIdentity groupId, const std::string &requestPacketId, const std::string &messagePacketId, bool status)
{
    
}

void ChatEventHandler::onFriendChatConversationListReceived(UserIdentity userId, const std::vector<SDKMessageDTO> &conversationList, bool isFromSynced)
{
    jobject jfriendConversationList = getJMessageList(env, conversationList);
    env->CallVoidMethod(eventHandler, cehOnFriendChatConversationListReceived, userId, jfriendConversationList, isFromSynced);
    checkForException(env);
}
    
void ChatEventHandler::onGroupChatConversationListReceived(const std::vector<SDKMessageDTO> &conversationList, bool isFromSynced)
{
    jobject jgroupConversationList = getJMessageList(env, conversationList);
    env->CallVoidMethod(eventHandler, cehOnGroupChatConversationListReceived, jgroupConversationList, isFromSynced);
    checkForException(env);
}

void ChatEventHandler::onChatConversationListRequestStatus(UserIdentity userId, long long friendOrGroupId, const std::string &packetId, bool status)
{
    jstring jpacketId = env->NewStringUTF(packetId.c_str());

    env->CallVoidMethod(eventHandler, cehOnChatConversationListRequestStatus, userId, friendOrGroupId, jpacketId, status);

    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onChatConversationListCompleted(UserIdentity userId, bool isFromSynced)
{
    env->CallVoidMethod(eventHandler, cehOnChatConversationListCompleted, userId, isFromSynced);
    checkForException(env);
}

void ChatEventHandler::onConversationListDeleteRequestStatus(UserIdentity userId, const std::string &packetId, bool status)
{
    jstring jpacketId = env->NewStringUTF(packetId.c_str());

    env->CallVoidMethod(eventHandler, cehOnConversationListDeleteRequestStatus, userId, jpacketId, status);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}
    
void ChatEventHandler::onConversationListMarkAsSeenRequestStatus(UserIdentity userId, const std::string &packetId, bool status)
{
    jstring jpacketId = env->NewStringUTF(packetId.c_str());

    env->CallVoidMethod(eventHandler, cehOnConversationListMarkAsSeenRequestStatus, userId, jpacketId, status);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onPublicChatMessageDeleted(RoomIdentity& roomId, const std::vector<std::string>& deletedPacketIds){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    
    jobject jpacketIds = getNewArrayList(env);
    for (int i=0; i<deletedPacketIds.size(); i++)
    {
        jobject packetIdList = (jobject)env->NewStringUTF(deletedPacketIds[i].c_str());
        arrayListAdd(env, jpacketIds, packetIdList);
        env->DeleteLocalRef(packetIdList);
    }
    
    env->CallVoidMethod(eventHandler, cehOnPublicChatMessageDeleted, jroomId, jpacketIds);
    checkForException(env);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpacketIds);
}

void ChatEventHandler::onPublicChatMessageLiked(RoomIdentity& roomId, const std::string &packetId, UserIdentity likerId){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnPublicChatMessageLiked, jroomId, jpacketId, likerId);
    
    checkForException(env);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onPublicChatMessageUnliked(RoomIdentity& roomId, const std::string &packetId, UserIdentity unlikerId){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnPublicChatMessageUnliked, jroomId, jpacketId, unlikerId);
    
    checkForException(env);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onPublicChatMessageReported(RoomIdentity& roomId, const std::string &packetId, UserIdentity reporterId){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnPublicChatMessageReported, jroomId, jpacketId, reporterId);
    
    checkForException(env);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onPublicChatCategoryListReceived(std::vector<std::string> &publicChatCategoryList){
    
    jobject jpublicChatCategoryList = getNewArrayList(env);
    for (int i=0; i<publicChatCategoryList.size(); i++)
    {
        jobject jpublicChatCategory = (jobject)env->NewStringUTF(publicChatCategoryList[i].c_str());
        arrayListAdd(env, jpublicChatCategoryList, jpublicChatCategory);
        env->DeleteLocalRef(jpublicChatCategory);
    }
    env->CallVoidMethod(eventHandler, cehOnPublicChatCategoryListReceived, jpublicChatCategoryList);
    
    checkForException(env);
    
    env->DeleteLocalRef(jpublicChatCategoryList);
}

void ChatEventHandler::onPublicChatLikeMemberListReceived(RoomIdentity &roomId, const std::string &packetId, const std::vector<PublicChatMemberDTO> &publicChatMemberList){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jobject jpublicChatMemberList = getJPublicChatMemberList(env, publicChatMemberList);
    
    env->CallVoidMethod(eventHandler, cehOnPublicChatLikeMemberListReceived, jroomId, jpacketId, jpublicChatMemberList);
    
    checkForException(env);
    
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jpublicChatMemberList);
    
}

void ChatEventHandler::onPublicChatDeleteRequestStatus(RoomIdentity roomId, const std::string &packetId, bool status){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnPublicChatDeleteRequestStatus, jroomId, jpacketId, status);
    checkForException(env);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onPublicChatLikeUnlikeRequestStatus(RoomIdentity roomId, const std::string &requestPacketId, const std::string &messagePacketId, bool status, bool fromLikeRequest){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jrequestPacketId = env->NewStringUTF(requestPacketId.c_str());
    jstring jmessagePacketId = env->NewStringUTF(messagePacketId.c_str());
    env->CallVoidMethod(eventHandler, cehOnPublicChatLikeUnlikeRequestStatus, jroomId, jrequestPacketId, jmessagePacketId, status, fromLikeRequest);
    checkForException(env);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jrequestPacketId);
    env->DeleteLocalRef(jmessagePacketId);
}

void ChatEventHandler::onPublicChatReportRequestStatus(RoomIdentity roomId, const std::string &requestPacketId, const std::string &messagePacketId, bool status){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jrequestPacketId = env->NewStringUTF(requestPacketId.c_str());
    jstring jmessagePacketId = env->NewStringUTF(messagePacketId.c_str());
    env->CallVoidMethod(eventHandler, cehOnPublicChatReportRequestStatus, jroomId, jrequestPacketId, jmessagePacketId, status);
    checkForException(env);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jrequestPacketId);
    env->DeleteLocalRef(jmessagePacketId);
}

void ChatEventHandler::onPublicChatLikeMemberListRequestStatus(RoomIdentity roomId, const std::string &packetId, bool status){
    jstring jroomId = env->NewStringUTF(roomId.c_str());
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnPublicChatLikeMemberListRequestStatus, jroomId, jpacketId, status);
    checkForException(env);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onPublicChatCategoryListRequestStatus(const std::string &packetId, bool status){
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    env->CallVoidMethod(eventHandler, cehOnPublicChatCategoryListRequestStatus, jpacketId, status);
    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onFriendFileManifestUploaded(UserIdentity userId, UserIdentity friendId, const std::string &packetId, std::string fileUrl, int mediaType, int timeout, std::string caption, int widthOrFileSize, int heightOrDuration){
    jstring jfileUrl = toUtf8JString(env, fileUrl);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jstring jcaption = toUtf8JString(env, caption);
    
    env->CallVoidMethod(eventHandler, cehOnFriendFileManifestUploaded, userId, friendId, jpacketId, jfileUrl, mediaType, timeout, jcaption, widthOrFileSize, heightOrDuration);
    
    checkForException(env);
    env->DeleteLocalRef(jfileUrl);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jcaption);
}

void ChatEventHandler::onFriendIncomingChatMedia(UserIdentity userId, UserIdentity friendId, std::string fileName, const std::string &packetId, int messageType, int timeout, long long messageDate, bool isSecretVisible, std::string caption, int widthOrSize, int heightOrDuration){
    jstring jfileName = toUtf8JString(env, fileName);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jstring jcaption = toUtf8JString(env, caption);
    
    env->CallVoidMethod(eventHandler, cehOnFriendIncomingChatMedia, userId, friendId, jfileName, jpacketId, messageType, timeout, messageDate, isSecretVisible, jcaption, widthOrSize, heightOrDuration);
    
    checkForException(env);
    env->DeleteLocalRef(jfileName);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jcaption);
}

void ChatEventHandler::onFriendChatMediaTransferProgress(UserIdentity userId, UserIdentity friendId, std::string fileName, double transferPercentage, bool isUpload, const std::string &packetId){
    jstring jfileName = toUtf8JString(env, fileName);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnFriendChatMediaTransferProgress, userId, friendId, jfileName, transferPercentage, isUpload, jpacketId);
    
    checkForException(env);
    env->DeleteLocalRef(jfileName);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onFriendChatMediaTransferFailed(UserIdentity userId, UserIdentity friendId, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer){
    jstring jfileName = toUtf8JString(env, fileName);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnFriendChatMediaTransferFailed, userId, friendId, jfileName, jpacketId, isUpload, isChunkedTransfer);
    
    checkForException(env);
    env->DeleteLocalRef(jfileName);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onFriendChatMediaTransferCanceled(UserIdentity userId, UserIdentity friendId, UserIdentity canceledBy, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer) {
    jstring jfileName = toUtf8JString(env, fileName);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());

    env->CallVoidMethod(eventHandler, cehOnFriendChatMediaTransferCanceled, userId, friendId, canceledBy, jfileName, jpacketId, isUpload, isChunkedTransfer);

    checkForException(env);
    env->DeleteLocalRef(jfileName);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onFriendChatMediaDownloadCompleted(UserIdentity userId, UserIdentity friendId, std::string fileNameWithPath, const std::string &packetId, int mediaType, int timeout){
    jstring jfileNameWithPath = toUtf8JString(env, fileNameWithPath);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnFriendChatMediaDownloadCompleted, userId, friendId, jfileNameWithPath, jpacketId, mediaType, timeout);

    checkForException(env);
    env->DeleteLocalRef(jfileNameWithPath);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onGroupFileManifestUploaded(GroupIdentity groupId, const std::string &packetId,
        std::string cloudManifestUrl, int messageType, std::string caption, int widthOrFileSize, int heightOrDuration){
    
    jstring jcloudManifestUrl = toUtf8JString(env, cloudManifestUrl);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jstring jcaption = toUtf8JString(env, caption);
    
    env->CallVoidMethod(eventHandler, cehOnGroupFileManifestUploaded, groupId, jpacketId, jcloudManifestUrl, messageType, jcaption, widthOrFileSize, heightOrDuration);
    
    checkForException(env);
    env->DeleteLocalRef(jcloudManifestUrl);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jcaption);
}    

void ChatEventHandler::onGroupIncomingChatMedia(UserIdentity friendId, GroupIdentity groupId, std::string fileName,
        const std::string &packetId, int messageType, long long messageDate, std::string caption, int widthOrSize, int heightOrDuration){    
    
    jstring jfileName = toUtf8JString(env, fileName);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jstring jcaption = toUtf8JString(env, caption);
    
    env->CallVoidMethod(eventHandler, cehOnGroupIncomingChatMedia, friendId, groupId, jfileName, jpacketId, messageType, messageDate, jcaption, widthOrSize, heightOrDuration);
    
    checkForException(env);
    env->DeleteLocalRef(jfileName);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jcaption);
}

void ChatEventHandler::onGroupChatMediaTransferProgress(UserIdentity friendId, GroupIdentity groupId,
        std::string fileName, double transferPercentage, bool isUpload, const std::string &packetId){
    
    jstring jfileName = toUtf8JString(env, fileName);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnGroupChatMediaTransferProgress, friendId, groupId, jfileName, transferPercentage, isUpload, jpacketId);
    
    checkForException(env);
    env->DeleteLocalRef(jfileName);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onGroupChatMediaTransferFailed(UserIdentity friendId, GroupIdentity groupId, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer){
    
    jstring jfileName = toUtf8JString(env, fileName);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnGroupChatMediaTransferFailed, friendId, groupId, jfileName, jpacketId, isUpload, isChunkedTransfer);
    
    checkForException(env);
    env->DeleteLocalRef(jfileName);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onGroupChatMediaTransferCanceled(UserIdentity friendId, GroupIdentity groupId, UserIdentity canceledBy, std::string fileName, const std::string &packetId, bool isUpload, bool isChunkedTransfer) {
    jstring jfileName = toUtf8JString(env, fileName);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());

    env->CallVoidMethod(eventHandler, cehOnGroupChatMediaTransferCanceled, friendId, groupId, canceledBy, jfileName, jpacketId, isUpload, isChunkedTransfer);

    checkForException(env);
    env->DeleteLocalRef(jfileName);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onGroupChatMediaDownloadCompleted(UserIdentity friendId, GroupIdentity groupId, std::string fileNameWithPath, const std::string &packetId, int mediaType){
   
    jstring jfileNameWithPath = toUtf8JString(env, fileNameWithPath);
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnGroupChatMediaDownloadCompleted, friendId, groupId, jfileNameWithPath, jpacketId, mediaType);

    checkForException(env);
    env->DeleteLocalRef(jfileNameWithPath);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onGeneralEncryptedPacketReceived(UserIdentity userID, UserIdentity friendID, const std::string &packetID, int type, int informationType, const std::string &information)
{
	jstring jinfo = toUtf8JString(env, information);
	jstring jpacketId = env->NewStringUTF(packetID.c_str());
	env->CallVoidMethod(eventHandler, cehOnGeneralEncryptedPacketReceived, userID, friendID, jpacketId, type, informationType, jinfo);
	env->DeleteLocalRef(jinfo);
	env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onGeneralEncryptedPacketConfirmationReceived(UserIdentity userID, UserIdentity friendID, const std::string &packetID, int type, int informationType)
{
	jstring jpacketId = env->NewStringUTF(packetID.c_str());
	env->CallVoidMethod(eventHandler, cehOnGeneralEncryptedPacketConfirmationReceived, userID, friendID, jpacketId, type, informationType);
	env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onChatMediaTransferDirectoryError(std::string directoryPath)
{
    jstring jdirectoryPath = env->NewStringUTF(directoryPath.c_str());
    env->CallVoidMethod(eventHandler, cehOnChatMediaTransferDirectoryError, jdirectoryPath);
    checkForException(env);
    env->DeleteLocalRef(jdirectoryPath);
}

void ChatEventHandler::shouldUpdateAppSessionID()
{
    env->CallVoidMethod(eventHandler, cehShouldUpdateAppSessionID);
    checkForException(env);
}

void ChatEventHandler::onSyncConversationRequestStatus(UserIdentity userId, const std::string &packetId, long long syncTime, bool status){
   
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnSyncConversationRequestStatus, userId, jpacketId, syncTime, status);

    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onSyncFriendHistoryMessageRequestStatus(UserIdentity userId, UserIdentity friendId, const std::string &packetId, long long syncTime, int direction, bool status){
   
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnSyncFriendHistoryMessageRequestStatus, userId, friendId, jpacketId, syncTime, direction, status);

    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onSyncFriendHistoryMessageReceived(UserIdentity userId, UserIdentity friendId, const std::string &packetId, const std::vector<SDKMessageDTO> &friendHistoryMessageList, long long oldestMessageDate, int direction){
   
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jobject jfriendHistoryMessageList = getJMessageList(env, friendHistoryMessageList);
    
    env->CallVoidMethod(eventHandler, cehOnSyncFriendHistoryMessageReceived, userId, friendId, jpacketId, jfriendHistoryMessageList, oldestMessageDate, direction);

    checkForException(env);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jfriendHistoryMessageList);

}

void ChatEventHandler::onSyncFriendHistoryMessageReceiveCompleted(UserIdentity userId, UserIdentity friendId, const std::string &packetId, int direction){
   
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnSyncFriendHistoryMessageReceiveCompleted, userId, friendId, jpacketId, direction);

    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onSyncGroupHistoryMessageRequestStatus(GroupIdentity groupId, const std::string &packetId, long long syncTime, int direction, bool status){
   
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnSyncGroupHistoryMessageRequestStatus, groupId, jpacketId, syncTime, direction, status);

    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onSyncGroupHistoryMessageReceived(GroupIdentity groupId, const std::string &packetId, const std::vector<SDKMessageDTO> &groupHistoryMessageList, const std::vector<GroupActivityDTO> &groupHistoryActivityList, long long oldestMessageDate, int direction){
   
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    jobject jgroupHistoryMessageList = getJMessageList(env, groupHistoryMessageList);
    jobject jgroupActivityList = getJGroupActivityList(env, groupHistoryActivityList);

    env->CallVoidMethod(eventHandler, cehOnSyncGroupHistoryMessageReceived, groupId, jpacketId, jgroupHistoryMessageList, jgroupActivityList, oldestMessageDate, direction);

    checkForException(env);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jgroupHistoryMessageList);
    env->DeleteLocalRef(jgroupActivityList);
}

void ChatEventHandler::onSyncGroupHistoryMessageReceiveCompleted(GroupIdentity groupId, const std::string &packetId, int direction){
   
    jstring jpacketId = env->NewStringUTF(packetId.c_str());
    
    env->CallVoidMethod(eventHandler, cehOnSyncGroupHistoryMessageReceiveCompleted, groupId, jpacketId, direction);

    checkForException(env);
    env->DeleteLocalRef(jpacketId);
}

void ChatEventHandler::onAddNoticeRequestStatus(const std::string &packetId, bool status){}

}