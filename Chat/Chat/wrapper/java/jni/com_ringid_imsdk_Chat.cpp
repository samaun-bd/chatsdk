
#include "com_ringid_imsdk_Chat.h"
#include "Chat.h"
#include "ChatEventHandler.h"
#include "MemberDTOConversion.h"
#include "ArrayListManipulation.h"
#include "SeenPacketDTOConversion.h"
#include "FriendMessageStatusDTOConversion.h"
#include "GroupActivityDTOConversion.h"
#include "GroupDTOConversion.h"
#include "RoomDTOConversion.h"
#include "PublicChatMemberDTOConversion.h"
#include "SDKMessageDTOConversion.h"
#include "DataCounterConversion.h"
#include "ConversationDTOConversion.h"
#include "InternetChecker.h"
#ifdef __ANDROID__
#include <android/log.h>
#endif

extern internetchecker::InternetChecker *internetChecker;
imsdk::Chat *chat = nullptr;
std::shared_ptr<imsdk::ChatEventHandler> eventHandler{nullptr};
JavaVM* javaVM;

jclass JApiStatus;
jmethodID asCtor;

jclass JFriendInformation;
jmethodID frndInfoCtor;

jclass JGroupInformation;
jmethodID grpInfoCtor;

jclass JPacketTimeId;
jmethodID ptiCtor;




jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env;

    javaVM = vm;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    } else {
        jclass localApiStatus = env->FindClass("com/ringid/imsdk/ApiStatus");
        JApiStatus = (jclass) env->NewGlobalRef(localApiStatus);
        asCtor = env->GetMethodID(JApiStatus, "<init>", "(Ljava/lang/String;I)V");
        
        jclass localFriendInformation =env->FindClass("com/ringid/imsdk/FriendInformation");
        JFriendInformation = (jclass) env->NewGlobalRef(localFriendInformation);
        frndInfoCtor = env->GetMethodID(JFriendInformation,"<init>","(Ljava/lang/String;IIIIIZLjava/lang/String;Ljava/lang/String;I)V");
        
        jclass localGroupInformation =env->FindClass("com/ringid/imsdk/GroupInformation");
        JGroupInformation = (jclass) env->NewGlobalRef(localGroupInformation);
        grpInfoCtor = env->GetMethodID(JGroupInformation,"<init>","(JLjava/lang/String;IIJ)V");
        

        jclass localPacketTimeId = env->FindClass("com/ringid/imsdk/PacketTimeId");
        JPacketTimeId = (jclass) env->NewGlobalRef(localPacketTimeId);
        ptiCtor = env->GetMethodID(JPacketTimeId, "<init>", "(Ljava/lang/String;JJ)V");
        
        imsdk::onloadChatEventHandler(env);
        imsdk::onloadMemberDTO(env);
        imsdk::onLoadArrayList(env);
        imsdk::onloadSeenPacketDTO(env);
        imsdk::onloadFriendMessageStatusDTO(env);
        imsdk::onloadGroupActivityDTO(env);
        imsdk::onloadGroupDTO(env);
        imsdk::onloadRoomDTO(env);
        imsdk::onloadPublicChatMemberDTO(env);
        imsdk::onloadMessageDTO(env);
        imsdk::onloadDataCounter(env);
        imsdk::onloadConversationDTO(env);
    }
    return JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM *vm, void *reserved) {
    JNIEnv* env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return;
    } else {
        // delete global references so the GC can collect them
        if (chat) {
            delete chat;
        }

        if (internetChecker) {
            delete internetChecker;
        }

        if (eventHandler) {
            eventHandler.reset();
        }
        
        imsdk::onunloadChatEventHandler(env);
        imsdk::onunloadMemberDTO(env);
        imsdk::onUnloadArrayList(env);
        imsdk::onunloadSeenPacketDTO(env);
        imsdk::onunloadFriendMessageStatusDTO(env);
        imsdk::onunloadGroupActivityDTO(env);
        imsdk::onunloadGroupDTO(env);
        imsdk::onunloadRoomDTO(env);
        imsdk::onunloadPublicChatMemberDTO(env);
        imsdk::onunloadMessageDTO(env);
        imsdk::onunloadDataCounter(env);
        imsdk::onunloadConversationDTO(env);
    }
}

jobject getJApiStatus(JNIEnv *env, imsdk::ApiStatus apiStatus) {
    jstring jpacketId = env->NewStringUTF(apiStatus.getPacketId().c_str());

    jobject japiStatus = env->NewObject(JApiStatus, asCtor, jpacketId, apiStatus.getErrorCode());
    env->DeleteLocalRef(jpacketId);
    return japiStatus;
}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_Chat_ctor
(JNIEnv *env, jobject, jlong juserId, jstring juserName, jstring jofflineServerAddress, jint jofflineServerPort, jstring jauthenticationServerAddress, jint jauthenticationServerPort, jint jdeviceType, jstring jappSessionId, jint appVersion, jlong timeDifference, jobject jdirectoryPaths, jstring jbaseUploadUrl, jstring jbaseDownloadUrl, jboolean jautoDownloadEnabled, jstring jkey, jint appType, jobject jpageIdList) {

    std::set<UserIdentity> pageIds;
    int numberOfPageIds = imsdk::arrayListSize(env, jpageIdList);
    for(int i=0;i<numberOfPageIds;i++){
        jobject jpageId = imsdk::arrayListGet(env, jpageIdList, i);
        
        jclass cls = env->FindClass("java/lang/Long");

        jmethodID longValueMethodId = env->GetMethodID(cls, "longValue", "()J");
        long long pageId = env->CallLongMethod(jpageId, longValueMethodId);
        pageIds.insert(pageId);
        
        env->DeleteLocalRef(jpageId);
        env->DeleteLocalRef(cls);
    }

    std::string userName = "";
    if(juserName != NULL)
    {
        userName = env->GetStringUTFChars(juserName, NULL);
    }

    std::string offlineServerAddress = "";
    if(jofflineServerAddress != NULL)
    {
        offlineServerAddress = env->GetStringUTFChars(jofflineServerAddress, NULL);
    }

    std::string authenticationServerAddress = "";
    if(jauthenticationServerAddress != NULL)
    {
        authenticationServerAddress = env->GetStringUTFChars(jauthenticationServerAddress, NULL);
    }

    std::string appSessionId = "";
    if(jappSessionId != NULL)
    {
        appSessionId = env->GetStringUTFChars(jappSessionId, NULL);
    }

    std::string key = "";
    if(jkey != NULL)
    {
        key = env->GetStringUTFChars(jkey, NULL);
    }

    std::vector<std::string> directoryPaths;
    if (jdirectoryPaths)
    {
        int numberOfDirectories = imsdk::arrayListSize(env, jdirectoryPaths);
        for (int i=0; i<numberOfDirectories; i++)
        {
            jstring jdirectoryPath = (jstring)imsdk::arrayListGet(env, jdirectoryPaths, i);
            directoryPaths.push_back(env->GetStringUTFChars(jdirectoryPath, NULL));
            env->DeleteLocalRef(jdirectoryPath);
        }
    }

    std::string baseUploadUrl = "";
    if(jbaseUploadUrl != NULL)
    {
        baseUploadUrl = env->GetStringUTFChars(jbaseUploadUrl, NULL);
    }

    std::string baseDownloadUrl = "";
    if(jbaseDownloadUrl != NULL)
    {
        baseDownloadUrl = env->GetStringUTFChars(jbaseDownloadUrl, NULL);
    }

    chat = new imsdk::Chat(juserId, userName, offlineServerAddress, jofflineServerPort, authenticationServerAddress, jauthenticationServerPort, jdeviceType, appSessionId, appVersion, timeDifference, directoryPaths, baseUploadUrl, baseDownloadUrl, jautoDownloadEnabled, key, appType, pageIds);
    
    env->DeleteLocalRef(juserName);
    env->DeleteLocalRef(jofflineServerAddress);
    env->DeleteLocalRef(jauthenticationServerAddress);
    env->DeleteLocalRef(jappSessionId);
    env->DeleteLocalRef(jdirectoryPaths);
    env->DeleteLocalRef(jbaseUploadUrl);
    env->DeleteLocalRef(jbaseDownloadUrl);
    env->DeleteLocalRef(jkey);
}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_Chat_reinitialize
  (JNIEnv *env, jobject, jlong juserId, jstring juserName, jstring jofflineServerAddress, jint jofflineServerPort, jstring jauthenticationServerAddress, jint jauthenticationServerPort, jint jdeviceType, jstring jappSessionId, jint appVersion, jlong timeDifference, jobject jdirectoryPaths, jboolean jautoDownloadEnabled, jstring jkey, jobject jpageIdList){

    std::set<UserIdentity> pageIds;
    int numberOfPageIds = imsdk::arrayListSize(env, jpageIdList);
    for(int i=0;i<numberOfPageIds;i++){
        jobject jpageId = imsdk::arrayListGet(env, jpageIdList, i);
        
        jclass cls = env->FindClass("java/lang/Long");

        jmethodID longValueMethodId = env->GetMethodID(cls, "longValue", "()J");
        long long pageId = env->CallLongMethod(jpageId, longValueMethodId);
        pageIds.insert(pageId);
        
        env->DeleteLocalRef(jpageId);
        env->DeleteLocalRef(cls);
    }

    std::string userName = "";
    if(juserName != NULL)
    {
        userName = env->GetStringUTFChars(juserName, NULL);
    }

    std::string offlineServerAddress = "";
    if(jofflineServerAddress != NULL)
    {
        offlineServerAddress = env->GetStringUTFChars(jofflineServerAddress, NULL);
    }

    std::string authenticationServerAddress = "";
    if(jauthenticationServerAddress != NULL)
    {
        authenticationServerAddress = env->GetStringUTFChars(jauthenticationServerAddress, NULL);
    }

    std::string appSessionId = "";
    if(jappSessionId != NULL)
    {
        appSessionId = env->GetStringUTFChars(jappSessionId, NULL);
    }


    std::string key = "";
    if(jkey != NULL)
    {
        key = env->GetStringUTFChars(jkey, NULL);
    }

    std::vector<std::string> directoryPaths;
    if (jdirectoryPaths)
    {
        int numberOfDirectories = imsdk::arrayListSize(env, jdirectoryPaths);
        for (int i=0; i<numberOfDirectories; i++)
        {
            jstring jdirectoryPath = (jstring)imsdk::arrayListGet(env, jdirectoryPaths, i);
            directoryPaths.push_back(env->GetStringUTFChars(jdirectoryPath, NULL));
            env->DeleteLocalRef(jdirectoryPath);
        }
    }
    
    chat->reinitialize(juserId, userName, offlineServerAddress, jofflineServerPort, authenticationServerAddress, jauthenticationServerPort, jdeviceType, appSessionId, appVersion, timeDifference, directoryPaths, jautoDownloadEnabled, key, pageIds);
    
    env->DeleteLocalRef(juserName);
    env->DeleteLocalRef(jofflineServerAddress);
    env->DeleteLocalRef(jauthenticationServerAddress);
    env->DeleteLocalRef(jappSessionId);
    env->DeleteLocalRef(jdirectoryPaths);
    env->DeleteLocalRef(jkey);
}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_Chat_setOfflineServer
  (JNIEnv *env, jobject, jstring jofflineServerAddress, jint jofflineServerPort)
{
    std::string offlineServerAddress = env->GetStringUTFChars(jofflineServerAddress, NULL);
    chat->setOfflineServer(offlineServerAddress, jofflineServerPort);
    env->DeleteLocalRef(jofflineServerAddress);
}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_Chat_setAuthenticationServer
  (JNIEnv *env, jobject, jstring jauthenticationServerAddress, jint jauthenticationServerPort)
{
    std::string authenticationServerAddress = env->GetStringUTFChars(jauthenticationServerAddress, NULL);
    chat->setOfflineServer(authenticationServerAddress, jauthenticationServerPort);
    env->DeleteLocalRef(jauthenticationServerAddress);
}

JNIEXPORT jboolean JNICALL Java_com_ringid_imsdk_Chat_isExistsFriendConnection
  (JNIEnv *env, jobject, jlong userId, jlong friendId)
{
    return chat->isExistsFriendConnection(userId, friendId);
}

JNIEXPORT jboolean JNICALL Java_com_ringid_imsdk_Chat_isExistsGroupConnection
  (JNIEnv *env, jobject, jlong groupId)
{
    return chat->isExistsGroupConnection(groupId);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_requestForOffline
  (JNIEnv *env, jobject, jlong jmessageDate, jlong jblockUpdateDate)
{
    auto apiStatus = chat->requestForOffline(jmessageDate, jblockUpdateDate);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_updateFriendRegisterServer
  (JNIEnv *env, jobject, jlong juserId, jlong jfriendId, jstring jregisterServerAddress, jint jregisterServerPort)
{
    std::string registerServerAddress = env->GetStringUTFChars(jregisterServerAddress, NULL);
    auto apiStatus = chat->updateFriendRegisterServer(juserId, jfriendId, registerServerAddress, jregisterServerPort);
    env->DeleteLocalRef(jregisterServerAddress);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_updateFriendStatusAndMood
  (JNIEnv *env, jobject, jlong juserId, jlong jfriendId, jint jstatus, jint jmood)
{
    auto apiStatus = chat->updateFriendStatusAndMood(juserId, jfriendId, jstatus, jmood);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_deleteFriendChatMessage
  (JNIEnv *env, jobject, jlong juserId, jlong jfriendId, jobject jpacketIds, jint jdeleteType)
{
    std::vector<std::string> packetIds;
    if (jpacketIds)
    {
        int numberOfPackets = imsdk::arrayListSize(env, jpacketIds);
        for (int i=0; i<numberOfPackets; i++)
        {
            jstring jPacketId = (jstring)imsdk::arrayListGet(env, jpacketIds, i);
            packetIds.push_back(env->GetStringUTFChars(jPacketId, NULL));
            env->DeleteLocalRef(jPacketId);
        }
    }
    auto apiStatus = chat->deleteFriendChatMessage(juserId, jfriendId, packetIds, jdeleteType);
    env->DeleteLocalRef(jpacketIds);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_requestFriendChatHistory
  (JNIEnv *env, jobject, jlong juserId, jlong jfriendId, jstring jpacketId, jint direction, jint limit)
{
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    auto apiStatus = chat->requestFriendChatHistory(juserId, jfriendId, packetId, direction, limit);
    env->DeleteLocalRef(jpacketId);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getFriendMessageStatus
  (JNIEnv *env, jobject, jlong juserId, jlong jfriendId, jobject jpacketIds)
{
    std::vector<std::string> packetIds;
    if (jpacketIds)
    {
        int numberOfPackets = imsdk::arrayListSize(env, jpacketIds);
        for (int i=0; i<numberOfPackets; i++)
        {
            jstring jPacketId = (jstring)imsdk::arrayListGet(env, jpacketIds, i);
            packetIds.push_back(env->GetStringUTFChars(jPacketId, NULL));
            env->DeleteLocalRef(jPacketId);
        }
    }
    auto apiStatus = chat->getFriendMessageStatus(juserId, jfriendId, packetIds);
    env->DeleteLocalRef(jpacketIds);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_blockFriend
  (JNIEnv *env, jobject, jlong juserId, jstring jpacketId, jlong jfriendId, jlong jblockUnblockDate, jboolean jaddToBlock)
{
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    auto apiStatus = chat->blockFriend(juserId, packetId, jfriendId, jblockUnblockDate, jaddToBlock);
    env->DeleteLocalRef(jpacketId);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_unblockFriend
  (JNIEnv *env, jobject, jlong juserId, jstring jpacketId, jlong jfriendId, jlong jblockUnblockDate)
{
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    auto apiStatus = chat->unblockFriend(juserId, packetId, jfriendId, jblockUnblockDate);
    env->DeleteLocalRef(jpacketId);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_deleteGroupChatMessage
  (JNIEnv *env, jobject, jlong jgroupId, jobject jpacketIds)
{
    std::vector<std::string> packetIds;
    if (jpacketIds)
    {
        int numberOfPackets = imsdk::arrayListSize(env, jpacketIds);
        for (int i=0; i<numberOfPackets; i++)
        {
            jstring jPacketId = (jstring)imsdk::arrayListGet(env, jpacketIds, i);
            packetIds.push_back(env->GetStringUTFChars(jPacketId, NULL));
            env->DeleteLocalRef(jPacketId);
        }
    }
    auto apiStatus = chat->deleteGroupChatMessage(jgroupId, packetIds);
    env->DeleteLocalRef(jpacketIds);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_registerFriendChat
(JNIEnv *env, jobject, jlong juserId, jstring juserName, jlong jfriendId, jstring jfriendName, jstring jfriendUrl, jstring jregisterServerAddress, jint jregisterServerPort, jint jdeviceType, jstring jdeviceToken, jint jappType, jint jstatus, jint jmood, jint iosVoipPush, jlong authRegistrationTime, jint profileType) {
    std::string registerServerAddress;
    if (jregisterServerAddress) 
    {
        registerServerAddress = env->GetStringUTFChars(jregisterServerAddress, NULL);
    }
    std::string userName = imsdk::toUtf8CString(env, juserName);
    std::string friendName = imsdk::toUtf8CString(env, jfriendName);
    std::string friendUrl = imsdk::toUtf8CString(env, jfriendUrl);
    std::string deviceToken = env->GetStringUTFChars(jdeviceToken, NULL);

    auto apiStatus = chat->registerFriendChat(juserId, userName, jfriendId, friendName, friendUrl, registerServerAddress, jregisterServerPort, jdeviceType, deviceToken, jappType, jstatus, jmood, iosVoipPush, authRegistrationTime, profileType);
    env->DeleteLocalRef(jregisterServerAddress);
    env->DeleteLocalRef(jdeviceToken);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_unregisterFriendChat
(JNIEnv *env, jobject, jlong juserId, jlong jfriendId, jint jonlineStatus, jint jonlineMood) {
    auto apiStatus = chat->unregisterFriendChat(juserId, jfriendId, jonlineStatus, jonlineMood);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_sendFriendChat
  (JNIEnv *env, jobject, jstring jpacketId, jlong juserId, jlong jfriendId, jint jmessageType, jint jsecretTimeout, jstring jmessage, jlong jmessageDate, jboolean isSecretVisible) {
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    std::string message = imsdk::toUtf8CString(env, jmessage);

    auto apiStatus = chat->sendFriendChat(packetId, juserId, jfriendId, jmessageType, jsecretTimeout, message, jmessageDate, isSecretVisible);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jmessage);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_sendGeneralEncryptedInformation
(JNIEnv *env, jobject, jlong juserID, jlong jfriendID, jstring jpacketID, jint jtype, jint jinformationType, jstring jinformation){
	std::string packetId = env->GetStringUTFChars(jpacketID, NULL);
	std::string information = imsdk::toUtf8CString(env, jinformation);

	auto apiStatus = chat->sendGeneralEncryptedInformation(juserID, jfriendID, packetId, jtype, jinformationType, information);
	env->DeleteLocalRef(jpacketID);
	env->DeleteLocalRef(jinformation);
	return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_dontSendPendingMessages
  (JNIEnv *env, jobject, jlong juserId, jlong jFriendId){
    auto apiStatus = chat->dontSendPendingMessages(juserId, jFriendId);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_sendFriendCallBusyMessage
  (JNIEnv *env, jobject, jlong juserId, jlong jfriendId, jstring jmessage, jlong jmessageDate, jstring jpacketId){
    std::string message = imsdk::toUtf8CString(env, jmessage);
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    
    auto apiStatus = chat->sendFriendCallBusyMessage(juserId, jfriendId, message, jmessageDate, packetId);
    env->DeleteLocalRef(jmessage);
    env->DeleteLocalRef(jpacketId);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_sendFriendCallLogMessage
  (JNIEnv *env, jobject, jlong juserId, jlong jfriendId, jstring jmessage, jlong jmessageDate, jstring jpacketId) {
    std::string message = imsdk::toUtf8CString(env, jmessage);
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);

    auto apiStatus = chat->sendFriendCallLogMessage(juserId, jfriendId, message, jmessageDate, packetId);
    env->DeleteLocalRef(jmessage);
    env->DeleteLocalRef(jpacketId);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_editFriendChat
(JNIEnv *env, jobject, jstring jpacketId, jlong juserId, jlong jfriendId, jint jmessageType, jint jsecretTimeout, jstring jmessage, jlong jmessageDate, jboolean isSecretVisible) {
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    std::string message = imsdk::toUtf8CString(env, jmessage);

    auto apiStatus = chat->editFriendChat(packetId, juserId, jfriendId, jmessageType, jsecretTimeout, message, jmessageDate, isSecretVisible);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jmessage);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_seenFriendChat
  (JNIEnv *env, jobject, jlong juserId, jlong jfriendId, jobject jseenPacketList){

    std::vector<imsdk::SeenPacketDTO> seenPacketList = imsdk::getSeenPacketList(env, jseenPacketList);

    auto apiStatus = chat->seenFriendChat(juserId, jfriendId, seenPacketList);
    env->DeleteLocalRef(jseenPacketList);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_typingFriendChat
(JNIEnv *env, jobject, jlong juserId, jlong jfriendId) {
    auto apiStatus = chat->typingFriendChat(juserId, jfriendId);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_Chat_registerEventHandler
(JNIEnv *env, jobject, jobject jEventHandler) {
    eventHandler = std::make_shared<imsdk::ChatEventHandler>(javaVM, env, jEventHandler);
    if (chat) {
        chat->registerEventHandler(eventHandler);
    }
    env->DeleteLocalRef(jEventHandler); //change in case
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_editGroupChat
  (JNIEnv *env, jobject, jstring jpacketId, jlong jgroupId, jint jmessageType, jstring jmessage, jlong jmessageDate){
    
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    std::string message = imsdk::toUtf8CString(env, jmessage);
    
    auto apiStatus = chat->editGroupChat(packetId, jgroupId, jmessageType, message, jmessageDate);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jmessage);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_registerGroupChat
(JNIEnv *env, jobject, jlong jgroupId, jstring jregisterServerAddress, jint jregisterServerPort, jlong authRegistrationTime) {
    std::string registerServerAddress = env->GetStringUTFChars(jregisterServerAddress, NULL);
    
    auto apiStatus = chat->registerGroupChat(jgroupId, registerServerAddress, jregisterServerPort, authRegistrationTime);
    env->DeleteLocalRef(jregisterServerAddress);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_unregisterGroupChat
(JNIEnv *env, jobject, jlong jgroupid, jint jonlineStatus, jint jonlineMood) {
    auto apiStatus = chat->unregisterGroupChat(jgroupid, jonlineStatus, jonlineMood);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_sendGroupChat
(JNIEnv *env, jobject, jstring jpacketId, jlong jgroupId, jint jmessageType, jstring jmessage, jlong jmessageDate) {
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    std::string message = imsdk::toUtf8CString(env, jmessage);
    
    auto apiStatus = chat->sendGroupChat(packetId, jgroupId, jmessageType, message, jmessageDate);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jmessage);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_seenGroupChat
(JNIEnv *env, jobject, jlong jgroupid, jobject jpacketIds) {
    
    std::vector<std::string> packetIds;
    if (jpacketIds)
    {
        int numberOfPackets = imsdk::arrayListSize(env, jpacketIds);
        for (int i=0; i<numberOfPackets; i++)
        {
            jstring jPacketId = (jstring)imsdk::arrayListGet(env, jpacketIds, i);
            packetIds.push_back(env->GetStringUTFChars(jPacketId, NULL));
            env->DeleteLocalRef(jPacketId);
        }
    }
    
    auto apiStatus = chat->seenGroupChat(jgroupid, packetIds);
    env->DeleteLocalRef(jpacketIds);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getGroupMessageSeenList
  (JNIEnv *env, jobject, jlong jgroupId, jstring jpacketId){
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    
    auto apiStatus = chat->getGroupMessageSeenList(jgroupId, packetId);
    
    env->DeleteLocalRef(jpacketId);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getConversationList
  (JNIEnv *env, jobject, jlong juserId, jint jconversationType, jint jstartIndex, jint jlimit, jlong jfriendOrGroupId){
       
    auto apiStatus = chat->getConversationList(juserId, static_cast<imsdk::ConversationType>(jconversationType), jstartIndex, jlimit, jfriendOrGroupId);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_deleteConversation
  (JNIEnv *env, jobject, jlong juserId, jobject jConversationList){
    std::vector<imsdk::ConversationDTO> conversationList = imsdk::getConversationList(env, jConversationList);
    
    auto apiStatus = chat->deleteConversation(juserId, conversationList);
    env->DeleteLocalRef(jConversationList);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_markConversationSeen
  (JNIEnv *env, jobject, jlong juserId, jobject jConversationList){
    std::vector<imsdk::ConversationDTO> conversationList = imsdk::getConversationList(env, jConversationList);
    
    auto apiStatus = chat->markConversationSeen(juserId, conversationList);
    env->DeleteLocalRef(jConversationList);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_Chat_updateUserPassword
  (JNIEnv *env, jobject, jstring jpassword)
{
    std::string password;
    
    if(!jpassword)
    {
        password = "";
    }
    password = imsdk::toUtf8CString(env, jpassword);
    chat->updateUserPassword(password);
    env->DeleteLocalRef(jpassword);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_typingGroupChat
(JNIEnv *env, jobject, jlong jgroupid) {
    auto apiStatus = chat->typingGroupChat(jgroupid);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_removeGroupMembers
(JNIEnv *env, jobject, jlong jgroupid, jobject jmemberList) {
    
    std::vector<UserIdentity> memberIds;
    int numberOfMembers = imsdk::arrayListSize(env, jmemberList);
    for(int i=0;i<numberOfMembers;i++){
        jobject jmemberID = imsdk::arrayListGet(env, jmemberList, i);
        
        jclass cls = env->FindClass("java/lang/Long");

        jmethodID longValueMethodId = env->GetMethodID(cls, "longValue", "()J");
        long long memberId = env->CallLongMethod(jmemberID, longValueMethodId);
        memberIds.push_back(memberId);
        
        env->DeleteLocalRef(jmemberID);
        env->DeleteLocalRef(cls);
    }

    auto apiStatus = chat->removeGroupMembers(jgroupid, memberIds);
    env->DeleteLocalRef(jmemberList);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_changeGroupName
  (JNIEnv *env, jobject, jlong jgroupId, jstring jgroupName)
{
    std::string groupName = imsdk::toUtf8CString(env, jgroupName);
    
    auto apiStatus = chat->changeGroupName(jgroupId, groupName);
    env->DeleteLocalRef(jgroupName);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_changeGroupUrl
  (JNIEnv *env, jobject, jlong jgroupId, jstring jgroupUrl)
{
    std::string groupUrl = imsdk::toUtf8CString(env, jgroupUrl);
    
    auto apiStatus = chat->changeGroupUrl(jgroupId, groupUrl);
    env->DeleteLocalRef(jgroupUrl);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_addGroupMembers
(JNIEnv *env, jobject, jlong jgroupid, jobject jmemberList) {
    std::vector<imsdk::MemberDTO> memberList = imsdk::getMemberList(env, jmemberList);
    
    auto apiStatus = chat->addGroupMembers(jgroupid, memberList);
    env->DeleteLocalRef(jmemberList);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_changeGroupMemberStatus
(JNIEnv *env, jobject, jlong jgroupid, jobject jmemberList) {
    std::vector<imsdk::MemberDTO> memberList = imsdk::getMemberList(env, jmemberList);
    
    auto apiStatus = chat->changeGroupMemberStatus(jgroupid, memberList);
    env->DeleteLocalRef(jmemberList);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_createGroup
  (JNIEnv *env, jobject, jlong jgroupId, jstring jgroupName, jstring jgroupUrl, jobject jmemberList)
{
    std::string groupName = imsdk::toUtf8CString(env, jgroupName);
    std::string groupUrl = imsdk::toUtf8CString(env, jgroupUrl);
    
    std::vector<imsdk::MemberDTO> memberList = imsdk::getMemberList(env, jmemberList);
    
    auto apiStatus = chat->createGroup(jgroupId, groupName, groupUrl, memberList);
    env->DeleteLocalRef(jgroupName);
    env->DeleteLocalRef(jgroupUrl);
    env->DeleteLocalRef(jmemberList);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_requestGroupChatHistory
  (JNIEnv *env, jobject, jlong jgroupId, jstring jpacketId, jint jdirection, jint jlimit)
{
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    
    auto apiStatus = chat->requestGroupChatHistory(jgroupId, packetId, jdirection, jlimit);
    env->DeleteLocalRef(jpacketId);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getGroupInformationWithMembers
  (JNIEnv *env, jobject, jlong jgroupId)
{
    auto apiStatus = chat->getGroupInformationWithMembers(jgroupId);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_leaveGroup
(JNIEnv *env, jobject, jlong jgroupid, jboolean isHide) {
    auto apiStatus = chat->leaveGroup(jgroupid, isHide);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_Chat_unregisterEventHandler
(JNIEnv *env, jobject) {
    if (chat) {
        chat->unregisterEventHandler();
    }
}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_Chat_setLogfile
(JNIEnv *env, jobject, jstring jfileName) {
    if (chat) {
        std::string fileName = env->GetStringUTFChars(jfileName, NULL);
        chat->setLogfile(fileName);
    }
    env->DeleteLocalRef(jfileName);
}

//JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_sendFileToFriend
//  (JNIEnv *env, jobject, jlong jfriendId, jint jmessageType, jint timeOut, jlong fileId, jstring jfileFullpath, jlong jfileSize, jlong jmessageDate, jboolean isSecretVisible)
//{
//    string senderFileFullPath = env->GetStringUTFChars(jfileFullpath, NULL);
//    
//    auto apiStatus = chat->sendFileToFriend(jfriendId, jmessageType, timeOut, fileId, senderFileFullPath, jfileSize, jmessageDate, isSecretVisible);
//    return getJApiStatus(env, apiStatus);
//}
//
//JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_startFileTransfer
//  (JNIEnv *env, jobject, jlong jfriendId, jlong jfileId, jstring jfilePath)
//{
//    string filePath = env->GetStringUTFChars(jfilePath, NULL);
//    
//    auto apiStatus = chat->startFileTransfer(jfriendId, jfileId, filePath);
//    return getJApiStatus(env, apiStatus);
//}
//
//JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_cancelFileTransfer
//  (JNIEnv *env, jobject, jlong jfriendId, jlong jfileId)
//{
//    auto apiStatus = chat->cancelFileTransfer(jfriendId, jfileId);
//    return getJApiStatus(env, apiStatus);
//}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_Chat_cleanUp
  (JNIEnv *env, jobject, jint mood){
    if (chat) {
        chat->cleanUp(mood);
    }
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getPendingFriendMessages
  (JNIEnv *env, jobject, jlong juserId)
{
    auto packetIds = chat->getPendingFriendMessages(juserId);
    jobject jpacketIds = imsdk::getNewArrayList(env);
    for (int i=0; i<packetIds.size(); i++)
    {
        jobject jpacketId = (jobject)env->NewStringUTF(packetIds[i].c_str());
        imsdk::arrayListAdd(env, jpacketIds, jpacketId);
        env->DeleteLocalRef(jpacketId);
    }
    
    //env->DeleteLocalRef(jpacketIds);
    
    return jpacketIds;
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getPendingGroupMessages
  (JNIEnv *env, jobject)
{
    auto packetIds = chat->getPendingGroupMessages();
    jobject jpacketIds = imsdk::getNewArrayList(env);
    for (int i=0; i<packetIds.size(); i++)
    {
        jobject jpacketId = (jobject)env->NewStringUTF(packetIds[i].c_str());
        imsdk::arrayListAdd(env, jpacketIds, jpacketId);
        env->DeleteLocalRef(jpacketId);
    }
    
    return jpacketIds;
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_generatePacketId__J
  (JNIEnv *env, jobject, jlong userId) {
    auto packetTimeId = chat->generatePacketId(userId);
    jstring jpacketId = env->NewStringUTF(packetTimeId.packetId.c_str());
    
    jobject jpacketTimeId = env->NewObject(JPacketTimeId, ptiCtor, jpacketId, packetTimeId.packetTime1970, packetTimeId.packetTime1582);
    env->DeleteLocalRef(jpacketId);
    
    return jpacketTimeId;
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_generatePacketId__JJ
  (JNIEnv *env, jobject, jlong timeMilli, jlong userId)
{
    auto packetTimeId = chat->generatePacketId(timeMilli, userId);
    jstring jpacketId = env->NewStringUTF(packetTimeId.packetId.c_str());
    
    jobject jpacketTimeId = env->NewObject(JPacketTimeId, ptiCtor, jpacketId, packetTimeId.packetTime1970, packetTimeId.packetTime1582);
    env->DeleteLocalRef(jpacketId);
    
    return jpacketTimeId;
}

JNIEXPORT jlong JNICALL Java_com_ringid_imsdk_Chat_generateGroupId
  (JNIEnv *env, jobject)
{
    return chat->generateGroupId();
}

JNIEXPORT jstring JNICALL Java_com_ringid_imsdk_Chat_version
(JNIEnv *env, jobject) {
    std::string version = chat->version();

    jstring jversion = env->NewStringUTF(version.c_str());

    return jversion;
}

JNIEXPORT jstring JNICALL Java_com_ringid_imsdk_Chat_getRingIdPackageName
(JNIEnv *env, jclass) {
    std::string packageName = imsdk::Chat::getRingIdPackageName();

    jstring jpackageName = env->NewStringUTF(packageName.c_str());

    return jpackageName;
}

JNIEXPORT jstring JNICALL Java_com_ringid_imsdk_Chat_getRingIncPackageName
(JNIEnv *env, jclass) {
    std::string packageName = imsdk::Chat::getRingIncPackageName();

    jstring jpackageName = env->NewStringUTF(packageName.c_str());

    return jpackageName;
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getFriendInformation
(JNIEnv *env, jobject, jlong userId, jlong friendId){
    auto friendInformation = chat->getFriendInformation(userId, friendId);
    
    if (!friendInformation) {
        return NULL;
    }
    
    jstring registerServerAddress = env->NewStringUTF(friendInformation->getFriendRegisterServerAddress().c_str());
    jint registerServerPort = friendInformation->getFriendRegisterServerPort();
    jint chatServerPort = friendInformation->getFriendChatServerPort();
    jint status = friendInformation->getFriendStatus();
    jint mood = friendInformation->getFriendMood();
    jint deviceType = friendInformation->getFriendDeviceType();
    jboolean blockStatus = friendInformation->getBlockStatus();
    jstring friendName = imsdk::toUtf8JString(env, friendInformation->getFriendName());
    jstring friendUrl = imsdk::toUtf8JString(env, friendInformation->getFriendUrl());
    jint profileType = friendInformation->getProfileType();
    
    jobject jfriendInformation = env->NewObject(JFriendInformation,frndInfoCtor,registerServerAddress,registerServerPort,chatServerPort,deviceType,status,mood,blockStatus,friendName,friendUrl, profileType);
    env->DeleteLocalRef(registerServerAddress);
    env->DeleteLocalRef(friendName);
    env->DeleteLocalRef(friendUrl);
    return jfriendInformation;
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getGroupInformation
  (JNIEnv *env, jobject, jlong groupId){
    auto groupInformation = chat->getGroupInformation(groupId);
    
    if(!groupInformation){
        return NULL;
    }
    
    jlong jgroupId = groupInformation->getGroupId();
    jstring registerServerAddress = env->NewStringUTF(groupInformation->getRegisterServerIp().c_str());
    jint registerServerPort = groupInformation->getRegisterServerPort();
    jint chatServerPort = groupInformation->getBindingPort();
    jlong lastActivityTime = groupInformation->getLastActivityTime();
    
    jobject jgroupInformation = env->NewObject(JGroupInformation, grpInfoCtor, jgroupId, registerServerAddress, registerServerPort, chatServerPort, lastActivityTime);
    env->DeleteLocalRef(registerServerAddress);
    return jgroupInformation;
    
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getRegisteredFriendsList
  (JNIEnv *env, jobject, jlong juserId){
    
    auto registeredFriendsList = chat->getRegisteredFriendsList(juserId);
    
    jobject jregisteredFriendsList = imsdk::getNewArrayList(env);
    
    jclass cls = env->FindClass("java/lang/Long");
    jmethodID longConstructor = env->GetMethodID(cls,"<init>","(J)V");
    
    for (int i=0; i<registeredFriendsList.size(); i++)
    {
        jlong friendId = registeredFriendsList[i];
        jobject obj = env->NewObject(cls, longConstructor, friendId);
        imsdk::arrayListAdd(env, jregisteredFriendsList, obj);
        env->DeleteLocalRef(obj);
    }
    env->DeleteLocalRef(cls);
    
    return jregisteredFriendsList;
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getRegisteredGroupList
  (JNIEnv *env, jobject){
    
    auto registeredGroupList = chat->getRegisteredGroupList();
    
    jobject jregisteredGroupList = imsdk::getNewArrayList(env);
    
    for (int i=0; i<registeredGroupList.size(); i++)
    {   
        jlong groupId = registeredGroupList[i]->getGroupId();
        jstring registerServerAddress = env->NewStringUTF(registeredGroupList[i]->getRegisterServerIp().c_str());
        jint registerServerPort = registeredGroupList[i]->getRegisterServerPort();
        jint chatServerPort = registeredGroupList[i]->getBindingPort();
        jlong lastActivityTime = registeredGroupList[i]->getLastActivityTime();
        
        jobject jgroupInformation = env->NewObject(JGroupInformation, grpInfoCtor, groupId, registerServerAddress, registerServerPort, chatServerPort, lastActivityTime);
        imsdk::arrayListAdd(env, jregisteredGroupList, jgroupInformation);
        env->DeleteLocalRef(registerServerAddress);
        env->DeleteLocalRef(jgroupInformation);
    }
    
    return jregisteredGroupList;
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_registerPublicRoomChat
  (JNIEnv *env, jobject, jstring jroomId, jstring jroomName, jstring jroomUrl, jlong ringId){
    
    std::string roomId = env->GetStringUTFChars(jroomId, NULL);
    std::string roomName = imsdk::toUtf8CString(env, jroomName);
    std::string roomUrl = imsdk::toUtf8CString(env, jroomUrl);
    
    auto apiStatus = chat->registerPublicRoomChat(roomId, roomName, roomUrl, ringId);
    
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jroomName);
    env->DeleteLocalRef(jroomUrl);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_sendPublicRoomChat
  (JNIEnv *env, jobject, jstring jpacketId, jstring jroomId, jint jmessageType, jstring jmessage, jlong jmessageDate, jstring jmemberFullName, jstring jmemberProfileUrl){
    
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    std::string roomId = env->GetStringUTFChars(jroomId, NULL);
    std::string message = imsdk::toUtf8CString(env, jmessage);
    std::string memberFullName = imsdk::toUtf8CString(env, jmemberFullName);
    std::string memberProfileUrl = imsdk::toUtf8CString(env, jmemberProfileUrl);
           
            
    auto apiStatus = chat->sendPublicRoomChat(packetId, roomId, jmessageType, message, jmessageDate, memberFullName, memberProfileUrl);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jmessage);
    env->DeleteLocalRef(jmemberFullName);
    env->DeleteLocalRef(jmemberProfileUrl);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_editPublicRoomChat
  (JNIEnv *env, jobject, jstring jpacketId, jstring jroomId, jint jmessageType, jstring jmessage, jlong jmessageDate, jstring jmemberFullName, jstring jmemberProfileUrl){
    
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    std::string roomId = env->GetStringUTFChars(jroomId, NULL);
    std::string message = imsdk::toUtf8CString(env, jmessage);
    std::string memberFullName = imsdk::toUtf8CString(env, jmemberFullName);
    std::string memberProfileUrl = imsdk::toUtf8CString(env, jmemberProfileUrl);
    
    auto apiStatus = chat->editPublicRoomChat(packetId, roomId, jmessageType, message, jmessageDate, memberFullName, memberProfileUrl);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jmessage);
    env->DeleteLocalRef(jmemberFullName);
    env->DeleteLocalRef(jmemberProfileUrl);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getRoomList
  (JNIEnv *env, jobject, jint jstartIndex, jint jlimit){
    
    auto apiStatus = chat->getRoomList(jstartIndex, jlimit);
    
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getRoomListWithHistory
  (JNIEnv *env, jobject, jint jstartIndex, jint jlimit){
    
    auto apiStatus = chat->getRoomListWithHistory(jstartIndex, jlimit);
    
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getRoomMemberList
  (JNIEnv *env, jobject, jstring jroomId, jstring jpagingState, jint jlimit){
    
    std::string roomId = env->GetStringUTFChars(jroomId, NULL);
    std::string pagingState = "";
    if (jpagingState)
    {
        pagingState = env->GetStringUTFChars(jpagingState, NULL);
    }
    
    auto apiStatus = chat->getRoomMemberList(roomId, pagingState, jlimit);
    
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_searchRoomList
  (JNIEnv *env, jobject, jstring jsearchName, jstring jcountry, jstring jcategory, jint jstartIndex, jint jlimit){
    
    std::string searchName = imsdk::toUtf8CString(env, jsearchName);
    std::string country = imsdk::toUtf8CString(env, jcountry);
    std::string category = imsdk::toUtf8CString(env, jcategory);
    
    auto apiStatus = chat->searchRoomList(searchName, country, category, jstartIndex, jlimit);
    env->DeleteLocalRef(jsearchName);
    env->DeleteLocalRef(jcountry);
    env->DeleteLocalRef(jcategory);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_unregisterPublicRoomChat
  (JNIEnv *env, jobject, jstring jroomId){
    
    std::string roomId = env->GetStringUTFChars(jroomId, NULL);
    
    auto apiStatus = chat->unregisterPublicRoomChat(roomId);
    env->DeleteLocalRef(jroomId);
    return getJApiStatus(env, apiStatus); 
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_typingPublicRoomChat
  (JNIEnv *env, jobject, jstring jroomId){
    
    std::string roomId = env->GetStringUTFChars(jroomId, NULL);
    
    auto apiStatus = chat->typingPublicRoomChat(roomId);
    env->DeleteLocalRef(jroomId);
    return getJApiStatus(env, apiStatus); 
}

JNIEXPORT jboolean JNICALL Java_com_ringid_imsdk_Chat_isExistsRoomConnection
  (JNIEnv *env, jobject, jstring jroomId){
    std::string roomId = env->GetStringUTFChars(jroomId, NULL);
    
    bool isExistsRoomConnection = chat->isExistsRoomConnection(roomId);
    
    env->DeleteLocalRef(jroomId);
    
    return isExistsRoomConnection;
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getRoomInformation
  (JNIEnv *env, jobject, jstring jroomId){
    std::string roomId = env->GetStringUTFChars(jroomId, NULL);
    
    auto apiStatus = chat->getRoomInformation(roomId);
    
    env->DeleteLocalRef(jroomId);
    
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_requestRoomChatHistory
  (JNIEnv *env, jobject, jstring jroomId, jstring jpacketId, jint jyear, jint jmonth, jint jdirection, jint jlimit){
    std::string roomId = env->GetStringUTFChars(jroomId, NULL);
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    
    auto apiStatus = chat->requestRoomChatHistory(roomId, packetId, jyear, jmonth, jdirection, jlimit);
    
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpacketId);
    
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_Chat_setLogEnabled
  (JNIEnv *env, jobject, jboolean enable){
    if(chat){
        chat->setLogEnabled(enable);
    }
}

JNIEXPORT jlong JNICALL Java_com_ringid_imsdk_Chat_getCurrentServerSyncedTime
  (JNIEnv *env, jobject){
    jlong curTime=0;
    if(chat){
        curTime = chat->getCurrentServerSyncedTime();
    }
    return curTime;
}

JNIEXPORT jlong JNICALL Java_com_ringid_imsdk_Chat_getTimeFromPacketId
  (JNIEnv *env, jobject, jstring jpacketId)
{
    jlong time = 0;
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    time = chat->UUIDToTime(packetId);
    env->DeleteLocalRef(jpacketId);
    return time;
}

JNIEXPORT jbyteArray JNICALL Java_com_ringid_imsdk_Chat_getGroupFileTransferIdlePacket
  (JNIEnv *env, jobject, jlong groupId){
    if(chat){
        chat->getGroupFileTransferIdlePacket(groupId);
    }
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_registerAnonymousFriendChat
  (JNIEnv *env, jobject, jlong jselfAnonymousUserId, jlong jfriendId, jlong originalFriendId, jstring jregisterServerAddress, jint jregisterServerPort, jint jdeviceType, jstring jdeviceToken, jint jappType, jint jstatus, jint jmood){
    std::string registerServerAddress;
    if (jregisterServerAddress) 
    {
        registerServerAddress = env->GetStringUTFChars(jregisterServerAddress, NULL);
    }
    std::string deviceToken = env->GetStringUTFChars(jdeviceToken, NULL);

    auto apiStatus = chat->registerAnonymousFriendChat(jselfAnonymousUserId, jfriendId, originalFriendId, registerServerAddress, jregisterServerPort, jdeviceType, deviceToken, jappType, jstatus, jmood);
    env->DeleteLocalRef(jregisterServerAddress);
    env->DeleteLocalRef(jdeviceToken);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_unregisterAnonymousFriendChat
  (JNIEnv *env, jobject, jlong juserId, jlong jfriendId, jint jonlineStatus, jint jonlineMood){
    auto apiStatus = chat->unregisterFriendChat(juserId, jfriendId, jonlineStatus, jonlineMood);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getShadowIdInfo
  (JNIEnv *env, jobject, jobject juserIds){
    
    std::vector<UserIdentity> userIds;
    int numberOfUsers = imsdk::arrayListSize(env, juserIds);
    for(int i=0;i<numberOfUsers;i++){
        jobject juserID = imsdk::arrayListGet(env, juserIds, i);
        
        jclass cls = env->FindClass("java/lang/Long");

        jmethodID longValueMethodId = env->GetMethodID(cls, "longValue", "()J");
        long long userId = env->CallLongMethod(juserID, longValueMethodId);
        userIds.push_back(userId);
        
        env->DeleteLocalRef(juserID);
        env->DeleteLocalRef(cls);
    }
    
    auto apiStatus = chat->getShadowIdInfo(userIds);
    env->DeleteLocalRef(juserIds);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_Chat_enterPublicChatScreen
  (JNIEnv *env, jobject, jstring jroomId){
   
    std::string roomId = env->GetStringUTFChars(jroomId, NULL);
    if(chat){
        chat->enterPublicChatScreen(roomId);
    }
    env->DeleteLocalRef(jroomId);
}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_Chat_exitPublicChatScreen
  (JNIEnv *env, jobject, jstring jroomId){
   
    std::string roomId = env->GetStringUTFChars(jroomId, NULL);
    if(chat){
        chat->exitPublicChatScreen(roomId);
    }
    env->DeleteLocalRef(jroomId);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getDataSentReceived
  (JNIEnv *env, jobject){
    auto dataCounter = chat->getDataSentReceived();
    return imsdk::getJDataCounter(env, dataCounter);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_deletePublicChatMessage
  (JNIEnv *env, jobject, jstring jroomId, jobject jpacketIds){
    
    std::string roomId = env->GetStringUTFChars(jroomId, NULL);
    std::vector<std::string> packetIds;
    if (jpacketIds)
    {
        int numberOfPackets = imsdk::arrayListSize(env, jpacketIds);
        for (int i=0; i<numberOfPackets; i++)
        {
            jstring jPacketId = (jstring)imsdk::arrayListGet(env, jpacketIds, i);
            packetIds.push_back(env->GetStringUTFChars(jPacketId, NULL));
            env->DeleteLocalRef(jPacketId);
        }
    }
    
    auto apiStatus = chat->deletePublicChatMessage(roomId, packetIds);
    
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpacketIds);
    
    return getJApiStatus(env, apiStatus);   
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_likePublicChatMessage
  (JNIEnv *env, jobject, jstring jpacketId, jstring jroomId, jlong jrecipientId){
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    std::string roomId = env->GetStringUTFChars(jroomId, NULL);
    
    auto apiStatus = chat->likePublicChatMessage(packetId, roomId, jrecipientId);
    
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpacketId);
    
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_unlikePublicChatMessage
  (JNIEnv *env, jobject, jstring jpacketId, jstring jroomId, jlong jrecipientId){
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    std::string roomId = env->GetStringUTFChars(jroomId, NULL);
    
    auto apiStatus = chat->unlikePublicChatMessage(packetId, roomId, jrecipientId);
    
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpacketId);
    
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_reportPublicChatMessage
  (JNIEnv *env, jobject, jstring jpacketId, jstring jroomId, jlong jrecipientId, jstring jmessage){
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    std::string roomId = env->GetStringUTFChars(jroomId, NULL);
    std::string message = imsdk::toUtf8CString(env, jmessage);
    
    auto apiStatus = chat->reportPublicChatMessage(packetId, roomId, jrecipientId, message);
    
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jmessage);
    
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getPublicChatLikeMemberList
  (JNIEnv *env, jobject, jstring jroomId, jstring jpacketId, jlong jlastlikerid, jint jlimit){
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    std::string roomId = env->GetStringUTFChars(jroomId, NULL);
    
    auto apiStatus = chat->getPublicChatLikeMemberList(roomId, packetId, jlastlikerid, jlimit);
    
    env->DeleteLocalRef(jroomId);
    env->DeleteLocalRef(jpacketId);
    
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getPublicChatRoomCategoryList
  (JNIEnv *env, jobject, jstring jlastCategory, jint jlimit){
    
    std::string lastCategory = "";
    if (jlastCategory)
    {
        lastCategory = imsdk::toUtf8CString(env, jlastCategory);
    }
    
    auto apiStatus = chat->getPublicChatRoomCategoryList(lastCategory, jlimit);
    
    env->DeleteLocalRef(jlastCategory);
    
    return getJApiStatus(env, apiStatus);
    
}

JNIEXPORT jboolean JNICALL Java_com_ringid_imsdk_Chat_checkInternetConnection
  (JNIEnv *env, jobject){
    return chat->checkInternetConnection(); 
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_registerLiveStreamChat
  (JNIEnv *env, jobject, jlong publisherId, jstring jregisterServerAddress, jint registerServerPort, jstring jfullName)
{
    std::string registerServerAddress = env->GetStringUTFChars(jregisterServerAddress, NULL);
    std::string fullName = imsdk::toUtf8CString(env, jfullName);
    
    auto apiStatus = chat->registerLiveStreamChat(publisherId, registerServerAddress, registerServerPort, fullName);
    
    env->DeleteLocalRef(jregisterServerAddress);
    env->DeleteLocalRef(jfullName);
    
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_unregisterLiveStreamChat
  (JNIEnv *env, jobject, jlong publisherId, jint onlineStatus, jint onlineMood)
{
    auto apiStatus = chat->unregisterLiveStreamChat(publisherId, onlineStatus, onlineMood);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_typingLiveStreamChat
  (JNIEnv *env, jobject, jlong publisherId)
{
    auto apiStatus = chat->typingLiveStreamChat(publisherId);
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_sendLiveStreamChat
  (JNIEnv *env, jobject, jstring jpacketId, jlong publisherId, jint messageType, jstring jmessage, jlong messageDate)
{
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    std::string message = imsdk::toUtf8CString(env, jmessage);
    
    auto apiStatus = chat->sendLiveStreamChat(packetId, publisherId, messageType, message, messageDate);
    
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jmessage);
    
    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_blockUserFromLiveStreamChat
  (JNIEnv *env, jobject, jlong jblockedUserId, jstring jpacketId)
{
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);

    auto apiStatus = chat->blockUserFromLiveStreamChat(jblockedUserId, packetId);

    env->DeleteLocalRef(jpacketId);

    return getJApiStatus(env, apiStatus);
}

JNIEXPORT jboolean JNICALL Java_com_ringid_imsdk_Chat_sendFriendChatMedia
  (JNIEnv *env, jobject, jlong juserId, jlong jfriendId, jstring jpacketId, jint jmediaType, jstring jfilePath, jstring jcaption, jint jwidthOrFileSize, jint jheightOrDuration, jint jsecretTimeout, jlong jmessageDate, jboolean jisSecretVisible){
    
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    std::string filePath = env->GetStringUTFChars(jfilePath, NULL);
    std::string caption = imsdk::toUtf8CString(env, jcaption);
    
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jfilePath);
    env->DeleteLocalRef(jcaption);
    
    return chat->sendFriendChatMedia(juserId, jfriendId, packetId, jmediaType, filePath, caption, jwidthOrFileSize, jheightOrDuration, jsecretTimeout, jmessageDate, jisSecretVisible);
}

JNIEXPORT jboolean JNICALL Java_com_ringid_imsdk_Chat_downloadFriendChatMedia
  (JNIEnv *env, jobject, jlong juserId, jlong jfriendId, jstring jpacketId, jstring jfileManifestUrl, jint jmediaType, jint jsecretTimeout){
    
    std::string fileManifestUrl = env->GetStringUTFChars(jfileManifestUrl, NULL);
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);

    env->DeleteLocalRef(jfileManifestUrl);
    env->DeleteLocalRef(jpacketId);

    return chat->downloadFriendChatMedia(juserId, jfriendId, packetId, fileManifestUrl, jmediaType, jsecretTimeout);
}

JNIEXPORT jboolean JNICALL Java_com_ringid_imsdk_Chat_acceptChatMedia
  (JNIEnv *env, jobject, jstring jpacketId){
    
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
        
    bool accepted = chat->acceptChatMedia(packetId);
    
    env->DeleteLocalRef(jpacketId);
    
    return accepted;
}

JNIEXPORT jboolean JNICALL Java_com_ringid_imsdk_Chat_sendGroupChatMedia
  (JNIEnv *env, jobject, jlong jgroupId, jstring jpacketId, jint jmediaType, jstring jfilePath, jstring jcaption, jint jwidthOrSize, jint jheightOrDuration, jlong jmessageDate){
   
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    std::string filePath = env->GetStringUTFChars(jfilePath, NULL);
    std::string caption = imsdk::toUtf8CString(env, jcaption);
    
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jfilePath);
    env->DeleteLocalRef(jcaption);
    
    return chat->sendGroupChatMedia(jgroupId, packetId, jmediaType, filePath, caption, jwidthOrSize, jheightOrDuration, jmessageDate);
}

JNIEXPORT jboolean JNICALL Java_com_ringid_imsdk_Chat_downloadGroupChatMedia
  (JNIEnv *env, jobject, jlong jgroupId, jlong jfriendId, jstring jpacketId, jstring jmanifestUrl, jint jmediaType){
    
    std::string manifestUrl = env->GetStringUTFChars(jmanifestUrl, NULL);
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);

    env->DeleteLocalRef(jmanifestUrl);
    env->DeleteLocalRef(jpacketId);

    return chat->downloadGroupChatMedia(jgroupId, jfriendId, packetId, manifestUrl, jmediaType);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getPendingChatMediaList
  (JNIEnv *env, jobject, jint jconversationType, jboolean uploadingMediaList, jboolean isChunkedTransfer){

    auto packetIds = chat->getPendingChatMediaList(static_cast<imsdk::ConversationType>(jconversationType), uploadingMediaList, isChunkedTransfer);

    jobject jpacketIds = imsdk::getNewArrayList(env);
    for (int i=0; i<packetIds.size(); i++)
    {
        jobject jpacketId = (jobject)env->NewStringUTF(packetIds[i].c_str());
        imsdk::arrayListAdd(env, jpacketIds, jpacketId);
        env->DeleteLocalRef(jpacketId);
    }

    return jpacketIds;
}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_Chat_cancelChatMediaTransfer
  (JNIEnv *env, jobject, jstring jpacketId){
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);

    chat->cancelChatMediaTransfer(packetId);

    env->DeleteLocalRef(jpacketId);
}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_Chat_updateAppSessionID
  (JNIEnv *env, jobject, jstring jappSessionId)
{
    std::string appSessionId = env->GetStringUTFChars(jappSessionId, NULL);

    chat->updateAppSessionID(appSessionId);

    env->DeleteLocalRef(jappSessionId);
}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_Chat_addUserPage
  (JNIEnv *, jobject, jlong jpageId)
{
    chat->addUserPage(jpageId);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_activateOrDeactivateUserAccount
  (JNIEnv *env, jobject, jboolean isActivate)
{
    auto apiStatus = chat->activateOrDeactivateUserAccount(isActivate);

    return getJApiStatus(env, apiStatus);
}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_Chat_removeUserPage
  (JNIEnv *, jobject, jlong jpageId)
{
    chat->removeUserPage(jpageId);
}


JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getSyncedConversation
  (JNIEnv *env, jobject, jlong juserId, jstring jpacketId, jlong jlastSyncedTime)
{
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    
    auto apiStatus = chat->getSyncedConversation(juserId, packetId, jlastSyncedTime);
    
    env->DeleteLocalRef(jpacketId);
    
    return getJApiStatus(env, apiStatus);
}


JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getSyncedFriendHistoryMessage
  (JNIEnv *env, jobject, jlong juserId, jlong jfriendId, jstring jpacketId, jlong jlastSyncedTime, jint limit, jint direction)
{
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    
    auto apiStatus = chat->getSyncedFriendHistoryMessage(juserId, jfriendId, packetId, jlastSyncedTime, limit, direction);
    
    env->DeleteLocalRef(jpacketId);
    
    return getJApiStatus(env, apiStatus);
}


JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getSyncedGroupHistoryMessage
  (JNIEnv *env, jobject, jlong juserId, jlong jgroupId, jstring jpacketId, jlong jlastSyncedTime, jint limit, jint direction)
{
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    
    auto apiStatus = chat->getSyncedGroupHistoryMessage(juserId, jgroupId, packetId, jlastSyncedTime, limit, direction);
    
    env->DeleteLocalRef(jpacketId);
    
    return getJApiStatus(env, apiStatus);
}

//JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getMyGroupListPaging
 // (JNIEnv *, jobject, jlong, jlong, jstring, jint);

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_Chat_getMyGroupListPaging
  (JNIEnv *env, jobject, jlong juserId, jstring jpacketId, jstring jpivotId, jint limit, jint direction)
{
    
    std::string packetId = env->GetStringUTFChars(jpacketId, NULL);
    std::string pivotId = jpivotId == NULL ? "" : env->GetStringUTFChars(jpivotId, NULL);
    
    auto apiStatus = chat->getMyGroupListPaging(juserId, packetId, pivotId, limit, direction);
    
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jpivotId);
    
    return getJApiStatus(env, apiStatus);
}