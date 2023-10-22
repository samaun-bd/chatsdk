/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GroupDTOConversion.cpp
 * Author: noman
 * 
 * Created on February 1, 2016, 2:51 PM
 */

#include "GroupDTOConversion.h"
#include "ArrayListManipulation.h"
#include "Logger.h"

#define module "jni"

namespace imsdk {
jclass JGroupDTO;

jmethodID mGCtor;
jmethodID mGetGroupId;
jmethodID mGetGroupName;
jmethodID mGetGroupUrl;
jmethodID mGetCreatorId;
jmethodID mGetNumberOfMembers;


    void onloadGroupDTO(JNIEnv *env){
        jclass localJGroupDTO = env->FindClass("com/ringid/imsdk/GroupDTO");
        JGroupDTO = (jclass) env->NewGlobalRef(localJGroupDTO);

        mGCtor = env->GetMethodID(JGroupDTO, "<init>", "(JLjava/lang/String;Ljava/lang/String;JI)V");
        mGetGroupId = env->GetMethodID(JGroupDTO, "getGroupId", "()J");
        mGetGroupName = env->GetMethodID(JGroupDTO, "getGroupName", "()Ljava/lang/String;");
        mGetGroupUrl = env->GetMethodID(JGroupDTO, "getGroupUrl", "()Ljava/lang/String;");
        mGetCreatorId = env->GetMethodID(JGroupDTO, "getCreatorId", "()J");
        mGetNumberOfMembers = env->GetMethodID(JGroupDTO, "getNumberOfMembers", "()I");
    }
    
    void onunloadGroupDTO(JNIEnv *env){
        if (JGroupDTO) {
            env->DeleteGlobalRef(JGroupDTO);
        }
    }
    
    GroupDTO getGroupDTO(JNIEnv *env, const jobject &jgroupDTO){
        GroupDTO groupDTO;
        groupDTO.setGroupId(env->CallLongMethod(jgroupDTO, mGetGroupId));
        jstring jgroupName = (jstring) env->CallObjectMethod(jgroupDTO, mGetGroupName);
        if (jgroupName)
        {
            groupDTO.setGroupName(imsdk::toUtf8CString(env, jgroupName));
        }
        //env->DeleteLocalRef(jgroupName);
        
        jstring jgroupUrl = (jstring) env->CallObjectMethod(jgroupDTO, mGetGroupUrl);
        if (jgroupUrl)
        {
            groupDTO.setGroupUrl(imsdk::toUtf8CString(env, jgroupUrl));
        }
        //env->DeleteLocalRef(jgroupUrl);
        groupDTO.setCreatorId(env->CallLongMethod(jgroupDTO, mGetCreatorId));
        groupDTO.setNumberOfMembers(env->CallIntMethod(jgroupDTO, mGetNumberOfMembers));

        return groupDTO;
    }
    
    jobject getJGroupDTO(JNIEnv *env, const GroupDTO &groupDTO){
        
        jstring jgroupName = toUtf8JString(env, groupDTO.getGroupName());
        jstring jgroupUrl = toUtf8JString(env, groupDTO.getGroupUrl());
        
        jobject jgroupDTOobject = env->NewObject(JGroupDTO, mGCtor,
            groupDTO.getGroupId(),
            jgroupName,
            jgroupUrl,
            groupDTO.getCreatorId(),
            groupDTO.getNumberOfMembers());
        
        env->DeleteLocalRef(jgroupName);
        env->DeleteLocalRef(jgroupUrl);
        return jgroupDTOobject;
    }
    
    std::vector<GroupDTO> getGroupList(JNIEnv *env, const jobject &jgroupList){
        std::vector<GroupDTO> groupList;
        if (jgroupList)
        {
            int numberOfGroups = arrayListSize(env, jgroupList);
            for (int i=0; i<numberOfGroups; i++)
            {
                jobject jgroupDTO = arrayListGet(env, jgroupList, i);
                groupList.push_back(getGroupDTO(env, jgroupDTO));
                env->DeleteLocalRef(jgroupDTO);
            }
        }

        return groupList;
    }
    
    jobject getJGroupList(JNIEnv *env, const std::vector<GroupDTO> &groupList){
        jobject jgroupList = getNewArrayList(env);
        for (int i=0; i<groupList.size(); i++)
        {
            jobject jgroupDTO = getJGroupDTO(env, groupList[i]);
            arrayListAdd(env, jgroupList, jgroupDTO);
            env->DeleteLocalRef(jgroupDTO);
        }

        Log(module, "group conversion completed");
        return jgroupList;
    }
    
}

