/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GroupActivityDTOConversion.cpp
 * Author: noman
 * 
 * Created on February 1, 2016, 3:42 PM
 */

#include <vector>

#include "GroupActivityDTOConversion.h"
#include "ArrayListManipulation.h"
#include "Logger.h"

#define module "jni"

namespace imsdk {
jclass JGroupActivityDTO;

jmethodID mGACtor;
jmethodID mGetActivityType;
jmethodID mGetGAMemberIdentity;
jmethodID mGetGAringId;
jmethodID mGetGroupNameOrUrlString;
jmethodID mGetMemberType;
jmethodID mGetChangedByUserId;
jmethodID mGetUpdateTime;
jmethodID mGetGAGroupId;
jmethodID mGetGAPacketId;

    void onloadGroupActivityDTO(JNIEnv *env){
        jclass localJGroupActivityDTO = env->FindClass("com/ringid/imsdk/GroupActivityDTO");
        JGroupActivityDTO = (jclass) env->NewGlobalRef(localJGroupActivityDTO);

        mGACtor = env->GetMethodID(JGroupActivityDTO, "<init>", "(IJJLjava/lang/String;IJJJLjava/lang/String;)V");
        mGetActivityType = env->GetMethodID(JGroupActivityDTO, "getActivityType", "()I");
        mGetGAMemberIdentity = env->GetMethodID(JGroupActivityDTO, "getMemberIdentity", "()J");
        mGetGAringId = env->GetMethodID(JGroupActivityDTO, "getRingId", "()J");
        mGetGroupNameOrUrlString = env->GetMethodID(JGroupActivityDTO, "getGroupNameOrUrlString", "()Ljava/lang/String;");
        mGetMemberType = env->GetMethodID(JGroupActivityDTO, "getMemberType", "()I");
        mGetChangedByUserId = env->GetMethodID(JGroupActivityDTO, "getChangedByUserId", "()J");
        mGetUpdateTime = env->GetMethodID(JGroupActivityDTO, "getUpdateTime", "()J");
        mGetGAGroupId = env->GetMethodID(JGroupActivityDTO, "getGroupId", "()J");
        mGetGAPacketId = env->GetMethodID(JGroupActivityDTO, "getPacketId", "()Ljava/lang/String;");
    }
    
    void onunloadGroupActivityDTO(JNIEnv *env){
        if (JGroupActivityDTO) {
            env->DeleteGlobalRef(JGroupActivityDTO);
        }
    }
    
    GroupActivityDTO getGroupActivityDTO(JNIEnv *env, const jobject &jgroupActivityDTO){
        GroupActivityDTO groupActivityDTO;
        groupActivityDTO.setActivityType(env->CallIntMethod(jgroupActivityDTO, mGetActivityType));
        groupActivityDTO.setMemberIdentity(env->CallLongMethod(jgroupActivityDTO, mGetGAMemberIdentity));
        groupActivityDTO.setRingId(env->CallLongMethod(jgroupActivityDTO, mGetGAringId));
        jstring jgroupNameOrUrlString = (jstring) env->CallObjectMethod(jgroupActivityDTO, mGetGroupNameOrUrlString);
        groupActivityDTO.setGroupNameOrUrlString(imsdk::toUtf8CString(env, jgroupNameOrUrlString));
        env->DeleteLocalRef(jgroupNameOrUrlString);
        groupActivityDTO.setMemberType(env->CallIntMethod(jgroupActivityDTO, mGetMemberType));
        groupActivityDTO.setChangedByUserId(env->CallLongMethod(jgroupActivityDTO, mGetChangedByUserId));
        groupActivityDTO.setUpdateTime(env->CallLongMethod(jgroupActivityDTO, mGetUpdateTime));
        groupActivityDTO.setGroupId(env->CallLongMethod(jgroupActivityDTO, mGetGAGroupId));
        jstring jgroupActivityPacketId = (jstring) env->CallObjectMethod(jgroupActivityDTO, mGetGAPacketId);
        groupActivityDTO.setPacketId(env->GetStringUTFChars(jgroupActivityPacketId, NULL));
        env->DeleteLocalRef(jgroupActivityPacketId);

        return groupActivityDTO;
    }
    
    jobject getJGroupActivityDTO(JNIEnv *env, const GroupActivityDTO &groupActivityDTO){
        Log(module,"getJGroupActivityDTO returns a DTO");
        
        jstring jgroupNameOrUrlString = toUtf8JString(env, groupActivityDTO.getGroupNameOrUrlString());
        jstring jgroupActivityPacketId = env->NewStringUTF(groupActivityDTO.getPacketId().c_str());
        jobject jgroupActivityDTOobject = env->NewObject(JGroupActivityDTO, mGACtor,
            groupActivityDTO.getActivityType(),
            groupActivityDTO.getMemberIdentity(),
            groupActivityDTO.getRingId(),
            jgroupNameOrUrlString,
            groupActivityDTO.getMemberType(),
            groupActivityDTO.getChangedByUserId(),
            groupActivityDTO.getUpdateTime(),
            groupActivityDTO.getGroupId(),
            jgroupActivityPacketId);
        env->DeleteLocalRef(jgroupNameOrUrlString);
        env->DeleteLocalRef(jgroupActivityPacketId);
        return jgroupActivityDTOobject;
    }
    
    std::vector<GroupActivityDTO> getGroupActivityList(JNIEnv *env, const jobject &jgroupActivityList){
        std::vector<GroupActivityDTO> groupActivityList;
        if (jgroupActivityList)
        {
            int numberOfGroupActivities = arrayListSize(env, jgroupActivityList);
            for (int i=0; i<numberOfGroupActivities; i++)
            {
                jobject jgroupActivityDTO = arrayListGet(env, jgroupActivityList, i);
                groupActivityList.push_back(getGroupActivityDTO(env, jgroupActivityDTO));
                env->DeleteLocalRef(jgroupActivityDTO);
            }
        }

        return groupActivityList;
    }
    
    jobject getJGroupActivityList(JNIEnv *env, const std::vector<GroupActivityDTO> &groupActivityList){
        jobject jgroupActivityList = getNewArrayList(env);
        Log(module, "jni: processing conversion. size: "<<groupActivityList.size());
        for (int i=0; i<groupActivityList.size(); i++)
        {
            Log(module, "Calling arraylistadd for one groupActivity : "<<i);
            jobject jgroupActivityDTO = getJGroupActivityDTO(env, groupActivityList[i]);
            arrayListAdd(env, jgroupActivityList, jgroupActivityDTO);
            Log(module,"Calling arraylistadd completed for one groupActivity : "<<i);
            env->DeleteLocalRef(jgroupActivityDTO);
        }

        Log(module, "groupActivityDTO conversion completed");
        return jgroupActivityList;
    }
}

