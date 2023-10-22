/* 
 * File:   MessageDTOConversion.cpp
 * Author: dipal
 * 
 * Created on October 18, 2015, 1:19 PM
 */

#include "MemberDTOConversion.h"
#include "ArrayListManipulation.h"
#include "Logger.h"

#define module "jni"

namespace imsdk {
jclass JMemberDTO;

jmethodID mCtor;
jmethodID mGetAddedBy;
jmethodID mGetStatus;
jmethodID mGetFullName;
jmethodID mGetMemberIdentity;
jmethodID mGetRingId;
jmethodID mGetSeenTime;
jmethodID mSetSeenTime;

void onloadMemberDTO(JNIEnv *env) {
    jclass localJMemberDTO = env->FindClass("com/ringid/imsdk/MemberDTO");
    JMemberDTO = (jclass) env->NewGlobalRef(localJMemberDTO);

    mCtor = env->GetMethodID(JMemberDTO, "<init>", "(JJLjava/lang/String;IJ)V");
    mGetAddedBy = env->GetMethodID(JMemberDTO, "getAddedBy", "()J");
    mGetStatus = env->GetMethodID(JMemberDTO, "getStatus", "()I");
    mGetFullName = env->GetMethodID(JMemberDTO, "getFullName", "()Ljava/lang/String;");
    mGetMemberIdentity = env->GetMethodID(JMemberDTO, "getMemberIdentity", "()J");
    mGetRingId = env->GetMethodID(JMemberDTO, "getRingId", "()J");
    mGetSeenTime = env->GetMethodID(JMemberDTO, "getSeenTime", "()J");
    mSetSeenTime = env->GetMethodID(JMemberDTO, "setSeenTime", "(J)V");
}

void onunloadMemberDTO(JNIEnv *env) {
    if (JMemberDTO) {
        env->DeleteGlobalRef(JMemberDTO);
    }
}

MemberDTO getMemberDTO(JNIEnv *env, const jobject &jmemberDTO) {
    MemberDTO memberDTO;
    memberDTO.setMemberIdentity(env->CallLongMethod(jmemberDTO, mGetMemberIdentity));
    memberDTO.setRingId(env->CallLongMethod(jmemberDTO, mGetRingId));
    jstring jfullName = (jstring) env->CallObjectMethod(jmemberDTO, mGetFullName);
    if (jfullName)
    {
        memberDTO.setFullName(imsdk::toUtf8CString(env, jfullName));
    }
//    env->DeleteLocalRef(jfullName);
    memberDTO.setStatus(env->CallIntMethod(jmemberDTO, mGetStatus));
    memberDTO.setAddedBy(env->CallLongMethod(jmemberDTO, mGetAddedBy));
    memberDTO.setSeenTime(env->CallLongMethod(jmemberDTO, mGetSeenTime));

    return memberDTO;
}

jobject getJMemberDTO(JNIEnv *env, const MemberDTO &memberDTO) {
    Log(module, "getJMemberDTO conversion memberId: " << memberDTO.getMemberIdentity() << " status: " << memberDTO.getRingId());
    jstring jmemberName = toUtf8JString(env, memberDTO.getFullName());
    jobject jmemberDTO = env->NewObject(JMemberDTO, mCtor,
            memberDTO.getMemberIdentity(),
            memberDTO.getRingId(),
            jmemberName,
            memberDTO.getStatus(),
            memberDTO.getAddedBy());
    
    env->CallVoidMethod(jmemberDTO, mSetSeenTime, memberDTO.getSeenTime());
    env->DeleteLocalRef(jmemberName);
    return jmemberDTO;
}

std::vector<MemberDTO> getMemberList(JNIEnv *env, const jobject &jmemberList) {
    std::vector<MemberDTO> memberList;
    if (jmemberList)
    {
        int numberOfMembers = arrayListSize(env, jmemberList);
        for (int i=0; i<numberOfMembers; i++)
        {
            jobject jmemberDTO = arrayListGet(env, jmemberList, i);
            memberList.push_back(getMemberDTO(env, jmemberDTO));
            env->DeleteLocalRef(jmemberDTO);
        }
    }
    
    return memberList;
}

jobject getJMemberList(JNIEnv *env, const std::vector<MemberDTO> &memberList) {
    Log(module, "getJMemberList memberList.size="<<memberList.size());
    jobject jmemberList = getNewArrayList(env);
    for (int i=0; i<memberList.size(); i++)
    {
        jobject jmemberDTO = getJMemberDTO(env, memberList[i]);
        arrayListAdd(env, jmemberList, jmemberDTO);
        env->DeleteLocalRef(jmemberDTO);
    }
    
    Log(module, "member conversion completed");
    return jmemberList;
}
}
