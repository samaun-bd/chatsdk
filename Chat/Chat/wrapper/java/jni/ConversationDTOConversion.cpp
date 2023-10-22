/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConversationDTOConversion.cpp
 * Author: noman
 * 
 * Created on October 19, 2016, 4:35 PM
 */

#include "ConversationDTOConversion.h"
#include "ArrayListManipulation.h"
#include "Logger.h"

#define module "jni"

namespace imsdk {
jclass JConversationDTO;

jmethodID mCVtor;
jmethodID mGetConversationType;
jmethodID mGetCFriendId;
jmethodID mGetCGroupId;

void onloadConversationDTO(JNIEnv *env) {
    jclass localJConversationDTO = env->FindClass("com/ringid/imsdk/ConversationDTO");
    JConversationDTO = (jclass) env->NewGlobalRef(localJConversationDTO);

    mCVtor = env->GetMethodID(JConversationDTO, "<init>", "(IJJ)V");
    mGetConversationType = env->GetMethodID(JConversationDTO, "getConversationType", "()I");
    mGetCFriendId = env->GetMethodID(JConversationDTO, "getFriendId", "()J");
    mGetCGroupId = env->GetMethodID(JConversationDTO, "getGroupId", "()J");
}

void onunloadConversationDTO(JNIEnv *env) {
    if (JConversationDTO) {
        env->DeleteGlobalRef(JConversationDTO);
    }
}

ConversationDTO getConversationDTO(JNIEnv *env, const jobject &jconversationDTO) {
    ConversationDTO conversationDTO;
    conversationDTO.SetConversationType(env->CallIntMethod(jconversationDTO, mGetConversationType));
    conversationDTO.SetFriendId(env->CallLongMethod(jconversationDTO, mGetCFriendId));
    conversationDTO.SetGroupId(env->CallLongMethod(jconversationDTO, mGetCGroupId));

    return conversationDTO;
}

jobject getJConversationDTO(JNIEnv *env, const ConversationDTO &conversationDTO) {
    jobject jconversationDTO = env->NewObject(JConversationDTO, mCVtor,
            conversationDTO.GetConversationType(),
            conversationDTO.GetFriendId(),
            conversationDTO.GetGroupId());
    
    return jconversationDTO;
}

std::vector<ConversationDTO> getConversationList(JNIEnv *env, const jobject &jconversationList) {
    std::vector<ConversationDTO> conversationList;
    if (jconversationList)
    {
        int numberOfConversations = arrayListSize(env, jconversationList);
        for (int i=0; i<numberOfConversations; i++)
        {
            jobject jconversationDTO = arrayListGet(env, jconversationList, i);
            conversationList.push_back(getConversationDTO(env, jconversationDTO));
            env->DeleteLocalRef(jconversationDTO);
        }
    }
    
    return conversationList;
}

jobject getJConversationList(JNIEnv *env, const std::vector<ConversationDTO> &conversationList) {
    Log(module, "getJConversationList conversationList.size="<<conversationList.size());
    jobject jconversationList = getNewArrayList(env);
    for (int i=0; i<conversationList.size(); i++)
    {
        jobject jconversationDTO = getJConversationDTO(env, conversationList[i]);
        arrayListAdd(env, jconversationList, jconversationDTO);
        env->DeleteLocalRef(jconversationDTO);
    }
    
    Log(module, "conversationDTO conversion completed");
    return jconversationList;
}
}


