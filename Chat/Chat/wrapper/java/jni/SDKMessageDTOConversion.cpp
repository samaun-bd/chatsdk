/* 
 * File:   MessageDTOConversion.h
 * Author: towhid
 *
 * Created on May 7, 2016, 4:33 PM
 */

#include "SDKMessageDTOConversion.h"
#include "ArrayListManipulation.h"
#include "Logger.h"

#define module "jni"

namespace imsdk {

jclass JMessageDTO;

jmethodID msgDTOCtor;
jmethodID msgDTOGetSenderId;
jmethodID msgDTOGetReceiverId;
jmethodID msgDTOGetGroupId;
jmethodID msgDTOGetPacketId;
jmethodID msgDTOGetMessageType;
jmethodID msgDTOGetTimeOut;
jmethodID msgDTOGetMessage;
jmethodID msgDTOGetMessageDate;
jmethodID msgDTOGetMemberFullName;
jmethodID msgDTOGetMemberProfileUrl;
jmethodID msgDTOGetIsSecretVisible;
jmethodID msgDTOGetMessageStatus;
jmethodID msgDTOGetDirection;
jmethodID msgDTOGetIsEdited;
jmethodID msgDTOGetPublicChatLikeCount;
jmethodID msgDTOIsPublicChatILike;
jmethodID msgDTOIsPublicChatIReport;
jmethodID msgDTOUnreadCount;

void onloadMessageDTO(JNIEnv *env) {
    jclass localJMessageDTO = env->FindClass("com/ringid/imsdk/SDKMessageDTO");
    JMessageDTO = (jclass) env->NewGlobalRef(localJMessageDTO);

    msgDTOCtor = env->GetMethodID(JMessageDTO, "<init>", "(JJJLjava/lang/String;IILjava/lang/String;JLjava/lang/String;Ljava/lang/String;ZIIZIZZI)V");
    msgDTOGetSenderId = env->GetMethodID(JMessageDTO, "getSenderId", "()J");
    msgDTOGetReceiverId = env->GetMethodID(JMessageDTO, "getReceiverId", "()J");
    msgDTOGetGroupId = env->GetMethodID(JMessageDTO, "getGroupId", "()J");
    msgDTOGetPacketId = env->GetMethodID(JMessageDTO, "getPacketId", "()Ljava/lang/String;");
    msgDTOGetMessageType = env->GetMethodID(JMessageDTO, "getMessageType", "()I");
    msgDTOGetTimeOut = env->GetMethodID(JMessageDTO, "getTimeOut", "()I");
    msgDTOGetMessage = env->GetMethodID(JMessageDTO, "getMessage", "()Ljava/lang/String;");
    msgDTOGetMessageDate = env->GetMethodID(JMessageDTO, "getMessageDate", "()J");
    msgDTOGetMemberFullName = env->GetMethodID(JMessageDTO, "getMemberFullName", "()Ljava/lang/String;");
    msgDTOGetMemberProfileUrl = env->GetMethodID(JMessageDTO, "getMemberProfileUrl", "()Ljava/lang/String;");
    msgDTOGetIsSecretVisible = env->GetMethodID(JMessageDTO, "isIsSecretVisible", "()Z");
    msgDTOGetMessageStatus = env->GetMethodID(JMessageDTO, "getMessageStatus", "()I");
    msgDTOGetDirection = env->GetMethodID(JMessageDTO, "getDirection", "()I");
    msgDTOGetIsEdited = env->GetMethodID(JMessageDTO, "getIsEdited", "()Z");
    msgDTOGetPublicChatLikeCount = env->GetMethodID(JMessageDTO, "getPublicChatLikeCount", "()I");
    msgDTOIsPublicChatILike = env->GetMethodID(JMessageDTO, "isPublicChatILike", "()Z");
    msgDTOIsPublicChatIReport = env->GetMethodID(JMessageDTO, "isPublicChatIReport", "()Z");
    msgDTOUnreadCount = env->GetMethodID(JMessageDTO, "getUnreadCount", "()I");
}

void onunloadMessageDTO(JNIEnv *env) {
    if (JMessageDTO) {
        env->DeleteGlobalRef(JMessageDTO);
    }
}

SDKMessageDTO getMessageDTO(JNIEnv *env, const jobject &jmessageDTO){
    SDKMessageDTO messageDTO;
    
    messageDTO.setSenderId(env->CallLongMethod(jmessageDTO, msgDTOGetSenderId));
    messageDTO.setReceiverId(env->CallLongMethod(jmessageDTO, msgDTOGetReceiverId));
    messageDTO.setGroupId(env->CallLongMethod(jmessageDTO, msgDTOGetGroupId));
    messageDTO.setPacketId(env->GetStringUTFChars((jstring) env->CallObjectMethod(jmessageDTO, msgDTOGetPacketId), NULL));
    messageDTO.setMessageType(env->CallIntMethod(jmessageDTO, msgDTOGetMessageType));
    messageDTO.setTimeOut(env->CallIntMethod(jmessageDTO, msgDTOGetTimeOut));
    messageDTO.setMessage(imsdk::toUtf8CString(env, (jstring) env->CallObjectMethod(jmessageDTO, msgDTOGetMessage)));
    messageDTO.setMessageDate(env->CallLongMethod(jmessageDTO, msgDTOGetMessageDate));
    messageDTO.setMemberFullName(imsdk::toUtf8CString(env, (jstring) env->CallObjectMethod(jmessageDTO, msgDTOGetMemberFullName)));
    messageDTO.setMemberProfileUrl(imsdk::toUtf8CString(env, (jstring) env->CallObjectMethod(jmessageDTO, msgDTOGetMemberProfileUrl)));
    messageDTO.setSecretVisible(env->CallBooleanMethod(jmessageDTO, msgDTOGetIsSecretVisible));
    messageDTO.setMessageStatus(env->CallIntMethod(jmessageDTO, msgDTOGetMessageStatus));
    messageDTO.setDirection(env->CallIntMethod(jmessageDTO, msgDTOGetDirection));
    messageDTO.setIsEdited(env->CallBooleanMethod(jmessageDTO, msgDTOGetIsEdited));
    messageDTO.setPublicChatLikeCount(env->CallIntMethod(jmessageDTO, msgDTOGetPublicChatLikeCount));
    messageDTO.setPublicChatILike(env->CallBooleanMethod(jmessageDTO, msgDTOIsPublicChatILike));
    messageDTO.setPublicChatIReport(env->CallBooleanMethod(jmessageDTO, msgDTOIsPublicChatIReport));
    messageDTO.setUnreadCount(env->CallIntMethod(jmessageDTO, msgDTOUnreadCount));
    
    return messageDTO;
}

jobject getJMessageDTO(JNIEnv *env, const SDKMessageDTO &messageDTO){
    jstring jpacketId = env->NewStringUTF(messageDTO.getPacketId().c_str());
    jstring jmessage = toUtf8JString(env, messageDTO.getMessage());
    jstring jmemberFullName = toUtf8JString(env, messageDTO.getMemberFullName());
    jstring jmemberProfileUrl = toUtf8JString(env, messageDTO.getMemberProfileUrl());
        
    jobject jmessasgeDTO = env->NewObject(JMessageDTO, msgDTOCtor, messageDTO.getSenderId(), messageDTO.getReceiverId(), messageDTO.getGroupId(), jpacketId, messageDTO.getMessageType(), messageDTO.getTimeOut(), jmessage, messageDTO.getMessageDate(), jmemberFullName, jmemberProfileUrl, messageDTO.getIsSecretVisible(), messageDTO.getMessageStatus(), messageDTO.getDirection(), messageDTO.getIsEdited(), messageDTO.getPublicChatLikeCount(), messageDTO.isPublicChatILike(), messageDTO.isPublicChatIReport(), messageDTO.getUnreadCount());
    
    env->DeleteLocalRef(jpacketId);
    env->DeleteLocalRef(jmessage);
    env->DeleteLocalRef(jmemberFullName);
    env->DeleteLocalRef(jmemberProfileUrl);
    
    return jmessasgeDTO;
}

std::vector<SDKMessageDTO> getMessageList(JNIEnv *env, const jobject &jmessageList){
    std::vector<SDKMessageDTO> messageList;
    
    if (jmessageList)
    {
        int numberOfMessages = arrayListSize(env, jmessageList);
        for (int i=0; i<numberOfMessages; i++)
        {
            jobject jmessageDTO = arrayListGet(env, jmessageList, i);
            messageList.push_back(getMessageDTO(env, jmessageDTO));
        }
    }

    return messageList;
}

jobject getJMessageList(JNIEnv *env, const std::vector<SDKMessageDTO> &messageList){
    
    jobject jmessageList = getNewArrayList(env);
    
    for (int i=0; i<messageList.size(); i++)
    {
        jobject jmessageDTO = getJMessageDTO(env, messageList[i]);
        arrayListAdd(env, jmessageList, jmessageDTO);
        env->DeleteLocalRef(jmessageDTO);
    }

    return jmessageList;
}

}
