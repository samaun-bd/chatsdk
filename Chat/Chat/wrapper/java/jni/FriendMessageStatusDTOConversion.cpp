/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FriendMessageStatusDTOConversion.cpp
 * Author: noman
 * 
 * Created on February 1, 2016, 4:20 PM
 */

#include "FriendMessageStatusDTOConversion.h"
#include "ArrayListManipulation.h"
#include "Logger.h"

#define module "jni"

namespace imsdk {
jclass JFriendMessageStatusDTO;

jmethodID mFMSCtor;
jmethodID mGetPacketId;
jmethodID mGetUpdateDate;
jmethodID mGetMessageStatus;

    void onloadFriendMessageStatusDTO(JNIEnv *env){
        jclass localJFriendMessageStatusDTO = env->FindClass("com/ringid/imsdk/FriendMessageStatusDTO");
        JFriendMessageStatusDTO = (jclass) env->NewGlobalRef(localJFriendMessageStatusDTO);

        mFMSCtor = env->GetMethodID(JFriendMessageStatusDTO, "<init>", "(Ljava/lang/String;JI)V");
        mGetPacketId = env->GetMethodID(JFriendMessageStatusDTO, "getPacketId", "()Ljava/lang/String;");
        mGetUpdateDate = env->GetMethodID(JFriendMessageStatusDTO, "getUpdateDate", "()J");
        mGetMessageStatus = env->GetMethodID(JFriendMessageStatusDTO, "getMessageStatus", "()I");
    }
    
    void onunloadFriendMessageStatusDTO(JNIEnv *env){
        if (JFriendMessageStatusDTO) {
            env->DeleteGlobalRef(JFriendMessageStatusDTO);
        }
    }
    
    FriendMessageStatusDTO getFriendMessageStatusDTO(JNIEnv *env, const jobject &jfriendMessageStatusDTO){
        FriendMessageStatusDTO friendMessageStatusDTO;
        jstring jpacketId = (jstring) env->CallObjectMethod(jfriendMessageStatusDTO, mGetPacketId);
        if (jpacketId)
        {
            friendMessageStatusDTO.setPacketId(env->GetStringUTFChars(jpacketId, NULL));
        }
//        env->DeleteLocalRef(jpacketId);
        friendMessageStatusDTO.setUpdateDate(env->CallLongMethod(jfriendMessageStatusDTO, mGetUpdateDate));
        friendMessageStatusDTO.setMessageStatus(env->CallIntMethod(jfriendMessageStatusDTO, mGetMessageStatus));

        return friendMessageStatusDTO;
    }
    
    jobject getJFriendMessageStatusDTO(JNIEnv *env, const FriendMessageStatusDTO &friendMessageStatusDTO){
        
        jstring jpacketId = env->NewStringUTF(friendMessageStatusDTO.getPacketId().c_str());
        
        jobject friendMessageStatusDTOobject = env->NewObject(JFriendMessageStatusDTO, mFMSCtor,
            jpacketId,
            friendMessageStatusDTO.getUpdateDate(),
            friendMessageStatusDTO.getMessageStatus());
        
        env->DeleteLocalRef(jpacketId);
        return friendMessageStatusDTOobject;
    }
    
    std::vector<FriendMessageStatusDTO> getFriendMessageStatusList(JNIEnv *env, const jobject &jfriendMessageStatusList){
        std::vector<FriendMessageStatusDTO> friendMessageStatusList;
        if (jfriendMessageStatusList)
        {
            int numberOfFriendMessageStatus = arrayListSize(env, jfriendMessageStatusList);
            for (int i=0; i<numberOfFriendMessageStatus; i++)
            {
                jobject jfriendMessageStatusDTO = arrayListGet(env, jfriendMessageStatusList, i);
                friendMessageStatusList.push_back(getFriendMessageStatusDTO(env, jfriendMessageStatusDTO));
                env->DeleteLocalRef(jfriendMessageStatusDTO);
            }
        }

        return friendMessageStatusList;
    }
    
    jobject getJFriendMessageStatusList(JNIEnv *env, const std::vector<FriendMessageStatusDTO> &friendMessageStatusList){
        jobject jfriendMessageStatusList = getNewArrayList(env);
        for (int i=0; i<friendMessageStatusList.size(); i++)
        {
            jobject friendMessageStatusDTO = getJFriendMessageStatusDTO(env, friendMessageStatusList[i]);
            arrayListAdd(env, jfriendMessageStatusList, friendMessageStatusDTO);
            env->DeleteLocalRef(friendMessageStatusDTO);
        }

        Log(module, "Friend message status list conversion completed");
        
        return jfriendMessageStatusList;
    }
}

