/* 

 * Author: S M Towhidul Islam
 * 
 */

#include "PublicChatMemberDTOConversion.h"
#include "ArrayListManipulation.h"
#include "Logger.h"

#define module "jni"

namespace imsdk {
jclass JPublicChatMemberDTO;

jmethodID mMCtor;
jmethodID mGetPublicChatRoomId;
jmethodID mGetFakeId;
jmethodID mGetMemberId;
jmethodID mGetMemberFullName;
jmethodID mGetProfileUrl;
jmethodID mGetAddedTime;
jmethodID mGetPublicChatMemberRingId;

    void onloadPublicChatMemberDTO(JNIEnv *env){
        jclass localJPublicChatMemberDTO = env->FindClass("com/ringid/imsdk/PublicChatMemberDTO");
        JPublicChatMemberDTO = (jclass) env->NewGlobalRef(localJPublicChatMemberDTO);

        mMCtor = env->GetMethodID(JPublicChatMemberDTO, "<init>", "(Ljava/lang/String;JJLjava/lang/String;Ljava/lang/String;JJ)V");
        mGetPublicChatRoomId = env->GetMethodID(JPublicChatMemberDTO, "getRoomId", "()Ljava/lang/String;");
        mGetMemberId = env->GetMethodID(JPublicChatMemberDTO, "getMemberId", "()J");
        mGetFakeId = env->GetMethodID(JPublicChatMemberDTO, "getFakeId", "()J");
        mGetMemberFullName = env->GetMethodID(JPublicChatMemberDTO, "getFullName", "()Ljava/lang/String;");
        mGetProfileUrl = env->GetMethodID(JPublicChatMemberDTO, "getProfileUrl", "()Ljava/lang/String;");
        mGetAddedTime = env->GetMethodID(JPublicChatMemberDTO, "getAddedTime", "()J");
        mGetPublicChatMemberRingId = env->GetMethodID(JPublicChatMemberDTO, "getRingId", "()J");
    }
    
    void onunloadPublicChatMemberDTO(JNIEnv *env){
        if (JPublicChatMemberDTO) {
            env->DeleteGlobalRef(JPublicChatMemberDTO);
        }
    }
    
    PublicChatMemberDTO getPublicChatMemberDTO(JNIEnv *env, const jobject &jmemberDTO){
        PublicChatMemberDTO publicChatMemberDTO;
        
        publicChatMemberDTO.setRoomId(env->GetStringUTFChars((jstring) env->CallObjectMethod(jmemberDTO, mGetPublicChatRoomId), NULL));
        publicChatMemberDTO.setMemberId(env->CallLongMethod(jmemberDTO, mGetMemberId));
        publicChatMemberDTO.setFakeId(env->CallLongMethod(jmemberDTO, mGetFakeId));
        publicChatMemberDTO.setFullName(imsdk::toUtf8CString(env, (jstring) env->CallObjectMethod(jmemberDTO, mGetMemberFullName)));
        publicChatMemberDTO.setProfileUrl(imsdk::toUtf8CString(env, (jstring) env->CallObjectMethod(jmemberDTO, mGetProfileUrl)));
        publicChatMemberDTO.setAddedTime(env->CallLongMethod(jmemberDTO, mGetAddedTime));
        publicChatMemberDTO.setRingId(env->CallLongMethod(jmemberDTO, mGetPublicChatMemberRingId));
        
        return publicChatMemberDTO;
    }
    
    jobject getJPublicChatMemberDTO(JNIEnv *env, const PublicChatMemberDTO &publicChatMemberDTO){
        std::string memberFullName = publicChatMemberDTO.getFullName();
        std::string memberProfileUrl = publicChatMemberDTO.getProfileUrl();
        std::string roomId = publicChatMemberDTO.getRoomId();
        jstring jmemberFullName = toUtf8JString(env, memberFullName);
        jstring jmemberProfileUrl = toUtf8JString(env, memberProfileUrl);
        jstring jroomId = toUtf8JString(env, roomId);
        
        jobject jpublicChatMemberDTO = env->NewObject(JPublicChatMemberDTO, mMCtor, jroomId, publicChatMemberDTO.getMemberId(), publicChatMemberDTO.getFakeId(), jmemberFullName, jmemberProfileUrl, publicChatMemberDTO.getAddedTime(), publicChatMemberDTO.getRingId());
        
        env->DeleteLocalRef(jmemberFullName);
        env->DeleteLocalRef(jmemberProfileUrl);
        env->DeleteLocalRef(jroomId);
        return jpublicChatMemberDTO;
    }
    
    std::vector<PublicChatMemberDTO> getPublicChatMemberList(JNIEnv *env, const jobject &jpublicChatMemberList){
        std::vector<PublicChatMemberDTO> publicChatMemberList;
        if (jpublicChatMemberList)
        {
            int numberOfRooms = arrayListSize(env, jpublicChatMemberList);
            for (int i=0; i<numberOfRooms; i++)
            {
                jobject jpublicChatMemberDTO = arrayListGet(env, jpublicChatMemberList, i);
                publicChatMemberList.push_back(getPublicChatMemberDTO(env, jpublicChatMemberDTO));
            }
        }

        return publicChatMemberList;
    }
    
    jobject getJPublicChatMemberList(JNIEnv *env, const std::vector<PublicChatMemberDTO> &publicChatMemberList){
        jobject jpublicChatMemberList = getNewArrayList(env);
        for (int i=0; i<publicChatMemberList.size(); i++)
        {
            jobject jpublicChatMemberDTO = getJPublicChatMemberDTO(env, publicChatMemberList[i]);
            arrayListAdd(env, jpublicChatMemberList, jpublicChatMemberDTO);
            env->DeleteLocalRef(jpublicChatMemberDTO);
        }

        Log(module, "Public Chat Member conversion completed");
        return jpublicChatMemberList;
    }
}
