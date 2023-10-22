

#include "SeenPacketDTOConversion.h"
#include "ArrayListManipulation.h"

#ifdef __ANDROID__
#include <android/log.h>
#endif

namespace imsdk {
jclass JSeenPacketDTO;

jmethodID mSCtor;
jmethodID mGetPacketID;
jmethodID mGetMessageDate;
jmethodID mGetSeenMessageStatus;

void onloadSeenPacketDTO(JNIEnv *env) {
    jclass localJSeenPacketDTO = env->FindClass("com/ringid/imsdk/SeenPacketDTO");
    JSeenPacketDTO = (jclass) env->NewGlobalRef(localJSeenPacketDTO);

    mSCtor = env->GetMethodID(JSeenPacketDTO, "<init>", "(Ljava/lang/String;JI)V");
    mGetPacketID = env->GetMethodID(JSeenPacketDTO, "getPacketId", "()Ljava/lang/String;");
    mGetMessageDate = env->GetMethodID(JSeenPacketDTO, "getMessageDate", "()J");
    mGetSeenMessageStatus = env->GetMethodID(JSeenPacketDTO, "getMessageStatus", "()I");
}

void onunloadSeenPacketDTO(JNIEnv *env) {
    if (JSeenPacketDTO) {
        env->DeleteGlobalRef(JSeenPacketDTO);
    }
}

SeenPacketDTO getSeenPacketDTO(JNIEnv *env, const jobject &jseenPacketDTO) {
    SeenPacketDTO seenPacketDTO;
    if (jseenPacketDTO)
    {
        jstring jpacketId = (jstring)env->CallObjectMethod(jseenPacketDTO, mGetPacketID);
        if (jpacketId)
        {
            seenPacketDTO.setPacketID(env->GetStringUTFChars(jpacketId, NULL));
        }
//        env->DeleteLocalRef(jpacketId);
        seenPacketDTO.setMessageDate(env->CallLongMethod(jseenPacketDTO, mGetMessageDate));
        seenPacketDTO.setMessageStatus(env->CallIntMethod(jseenPacketDTO, mGetSeenMessageStatus));
    }
    return seenPacketDTO;
}

jobject getJSeenPacketDTO(JNIEnv *env, const SeenPacketDTO &seenPacketDTO) {
    jstring jpacketId = env->NewStringUTF(seenPacketDTO.getPacketID().c_str());
    jobject jseenPacketDTO = env->NewObject(JSeenPacketDTO, mSCtor,
            jpacketId,
            seenPacketDTO.getMessageDate(),
            seenPacketDTO.getMessageStatus());
    env->DeleteLocalRef(jpacketId);
    return jseenPacketDTO;
}

std::vector<SeenPacketDTO> getSeenPacketList(JNIEnv *env, const jobject &jseenPacketList) {
    std::vector<SeenPacketDTO> seenPacketList;
    if (jseenPacketList)
    {
        int numberOfSeenPackets = arrayListSize(env, jseenPacketList);
        for (int i=0; i<numberOfSeenPackets; i++)
        {
            jobject jseenPacketDTO = arrayListGet(env, jseenPacketList, i);
            seenPacketList.push_back(getSeenPacketDTO(env, jseenPacketDTO));
            env->DeleteLocalRef(jseenPacketDTO);
        }
    }
    
    return seenPacketList;
}

jobject getJSeenPacketList(JNIEnv *env, const std::vector<SeenPacketDTO> &seenPacketList) {
    jobject jseenPacketList = getNewArrayList(env);
    for (int i=0; i<seenPacketList.size(); i++)
    {
        jobject jseenPacketDTO = getJSeenPacketDTO(env, seenPacketList[i]);
        arrayListAdd(env, jseenPacketList, jseenPacketDTO);
        env->DeleteLocalRef(jseenPacketDTO);
    }
    
    return jseenPacketList;
}
}
