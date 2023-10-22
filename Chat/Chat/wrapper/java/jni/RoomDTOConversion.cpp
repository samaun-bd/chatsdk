/* 

 * Author: S M Towhidul Islam
 * 
 */

#include "RoomDTOConversion.h"
#include "SDKMessageDTOConversion.h"
#include "ArrayListManipulation.h"
#include "Logger.h"
#include "MemberDTOConversion.h"

#define module "jni"

namespace imsdk {
jclass JRoomDTO;

jmethodID mRCtor;
jmethodID mGetRoomId;
jmethodID mGetRoomName;
jmethodID mGetRoomPictureUrl;
jmethodID mGetNumberOfRoomMember;
jmethodID mGetRoomMesageList;


    void onloadRoomDTO(JNIEnv *env){
        jclass localJRoomDTO = env->FindClass("com/ringid/imsdk/RoomDTO");
        JRoomDTO = (jclass) env->NewGlobalRef(localJRoomDTO);

        mRCtor = env->GetMethodID(JRoomDTO, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ILjava/util/ArrayList;)V");
        mGetRoomId = env->GetMethodID(JRoomDTO, "getRoomId", "()Ljava/lang/String;");
        mGetRoomName = env->GetMethodID(JRoomDTO, "getRoomName", "()Ljava/lang/String;");
        mGetRoomPictureUrl = env->GetMethodID(JRoomDTO, "getRoomPictureUrl", "()Ljava/lang/String;");
        mGetNumberOfRoomMember = env->GetMethodID(JRoomDTO, "getNumberOfMember", "()I");
        mGetRoomMesageList = env->GetMethodID(JRoomDTO, "getRoomMesageList", "()Ljava/util/ArrayList;");
    }
    
    void onunloadRoomDTO(JNIEnv *env){
        if (JRoomDTO) {
            env->DeleteGlobalRef(JRoomDTO);
        }
    }
    
    RoomDTO getRoomDTO(JNIEnv *env, const jobject &jroomDTO){
        RoomDTO roomDTO;
        roomDTO.setRoomId(env->GetStringUTFChars((jstring) env->CallObjectMethod(jroomDTO, mGetRoomId), NULL));
        roomDTO.setRoomFullName(imsdk::toUtf8CString(env, (jstring) env->CallObjectMethod(jroomDTO, mGetRoomName)));
        roomDTO.setRoomPictureUrl(imsdk::toUtf8CString(env, (jstring) env->CallObjectMethod(jroomDTO, mGetRoomPictureUrl)));
        roomDTO.setNumberOfMember(env->CallIntMethod(jroomDTO, mGetNumberOfRoomMember));
        roomDTO.setRoomMessageList(getMessageList(env, env->CallObjectMethod(jroomDTO, mGetRoomMesageList)));
        
        return roomDTO;
    }
    
    jobject getJRoomDTO(JNIEnv *env, const RoomDTO &roomDTO){
        jstring jroomId = env->NewStringUTF(roomDTO.getRoomId().c_str());
        jstring jroomFullName = toUtf8JString(env, roomDTO.getRoomFullName());
        jstring jroomPictureUrl = toUtf8JString(env, roomDTO.getRoomPictureUrl());
        jobject jroomMessageList = getNewArrayList(env);
        
        std::vector<SDKMessageDTO> messageList = roomDTO.getRoomMessageList();
        
        jroomMessageList = getJMessageList(env, messageList);       
        
        jobject jroomDTO = env->NewObject(JRoomDTO, mRCtor, jroomId, jroomFullName, jroomPictureUrl, roomDTO.getNumberOfMember(), jroomMessageList);
        
        env->DeleteLocalRef(jroomId);
        env->DeleteLocalRef(jroomFullName);
        env->DeleteLocalRef(jroomPictureUrl);
        env->DeleteLocalRef(jroomMessageList);
        
        return jroomDTO;
    }
    
    std::vector<RoomDTO> getRoomList(JNIEnv *env, const jobject &jroomList){
        std::vector<RoomDTO> roomList;
        if (jroomList)
        {
            int numberOfRooms = arrayListSize(env, jroomList);
            for (int i=0; i<numberOfRooms; i++)
            {
                jobject jroomDTO = arrayListGet(env, jroomList, i);
                roomList.push_back(getRoomDTO(env, jroomDTO));
            }
        }

        return roomList;
    }
    
    jobject getJRoomList(JNIEnv *env, const std::vector<RoomDTO> &roomList){
        jobject jroomList = getNewArrayList(env);
        for (int i=0; i<roomList.size(); i++)
        {
            jobject jroomDTO = getJRoomDTO(env, roomList[i]);
            arrayListAdd(env, jroomList, jroomDTO);
            env->DeleteLocalRef(jroomDTO);
        }

        Log(module, "Room conversion completed");
        return jroomList;
    }
}


