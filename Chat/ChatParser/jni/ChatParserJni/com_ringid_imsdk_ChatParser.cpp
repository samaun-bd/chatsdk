
#include "com_ringid_imsdk_ChatParser.h"
#include "ChatParser.h"
#include "PacketDTO.h"
#include <string.h>
#include <iostream>

using namespace std;

jclass JMessageDTO;
jclass JMemberDTO;
jclass JFileChunk;
jclass HashSet;
jclass ArrayList;
jclass Iterator;
jclass Long;


//MessageDTO
jmethodID mdtoConstructor;
jmethodID mdtoSetPacketType;
jmethodID mdtoSetPacketID;
jmethodID mdtoSetUserIdentity;
jmethodID mdtoSetFullName;
jmethodID mdtoSetFriendIdentity;
jmethodID mdtoSetMessage;
jmethodID mdtoSetMessageType;
jmethodID mdtoSetMessageDate;
jmethodID mdtoSetDevice;
jmethodID mdtoSetDeviceToken;
jmethodID mdtoSetTimeout;
jmethodID mdtoSetLatitude;
jmethodID mdtoSetLongitude;
jmethodID mdtoSetGroupId;
jmethodID mdtoSetNumberOfMembers;
jmethodID mdtoSetMemberList;
jmethodID mdtoSetOnlineStatus;
jmethodID mdtoSetNumberOfMessage;
jmethodID mdtoSetPacketIDs;
jmethodID mdtoSetMessageList;
jmethodID mdtoSetSequenceNumber;
jmethodID mdtoSetChatBindingPort;
jmethodID mdtoSetAppType;
jmethodID mdtoSetOnlineMood;
jmethodID mdtoSetFileTotalChunk;
jmethodID mdtoSetFileChunkCurrentIndex;
jmethodID mdtoSetFileContent;
jmethodID mdtoSetFileChunkList;
jmethodID mdtoSetIsAddToBlock;
jmethodID mdtoSetGroupName;
jmethodID mdtoSetGroupUrl;
jmethodID mdtoSetIsUpdateGroupInformation;
jmethodID mdtoSetTotalGroupMembers;

//MemberDTO
jmethodID memdtoConstructor;
jmethodID memdtoConstructorValued;
jmethodID memdtoGetMemberIdentity;
jmethodID memdtoGetFullName;
jmethodID memdtoGetStatus;
jmethodID memdtoGetAddedBy;
jmethodID memdtoSetMemberIdentity;
jmethodID memdtoSetFullName;
jmethodID memdtoSetStatus;
jmethodID memdtoSetAddedBy;

//FileChunk
jmethodID fcConstructor;
jmethodID fcGetIndexFrom;
jmethodID fcGetIndexTo;

jmethodID arrayListConstruct;
jmethodID arrayListGet;
jmethodID arrayListAdd;
jmethodID arrayListSize;
jmethodID hashSetConstruct;
jmethodID hashSetIterator;
jmethodID iteratorHasNext;
jmethodID iteratorNext;
jmethodID longValue;

jmethodID mdtoGetPacketType;
jmethodID mdtoGetPacketID;
jmethodID mdtoGetUserIdentity;
jmethodID mdtoGetFullName;
jmethodID mdtoGetFriendIdentity;
jmethodID mdtoGetMessage;
jmethodID mdtoGetMessageType;
jmethodID mdtoGetMessageDate;
jmethodID mdtoGetDevice;
jmethodID mdtoGetDeviceToken;
jmethodID mdtoGetTimeout;
jmethodID mdtoGetLatitude;
jmethodID mdtoGetLongitude;
jmethodID mdtoGetGroupId;
jmethodID mdtoGetNumberOfMembers;
jmethodID mdtoGetMemberList;
jmethodID mdtoGetOnlineStatus;
jmethodID mdtoGetNumberOfMessage;
jmethodID mdtoGetPacketIDs;
jmethodID mdtoGetMessageList;
jmethodID mdtoGetSequenceNumber;
jmethodID mdtoGetChatBindingPort;
jmethodID mdtoGetServerDate;
jmethodID mdtoGetAppType;
jmethodID mdtoGetOnlineMood;
jmethodID mdtoGetFileTotalChunk;
jmethodID mdtoGetFileChunkCurrentIndex;
jmethodID mdtoGetFileContent;
jmethodID mdtoGetFileChunkList;
jmethodID mdtoGetIsAddToBlock;
jmethodID mdtoGetGroupName;
jmethodID mdtoGetGroupUrl;
jmethodID mdtoGetIsUpdateGroupInformation;
jmethodID mdtoGetTotalGroupMembers;

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env;

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    } else {

        jclass localMessageDTO = env->FindClass("com/ringid/imsdk/MessageDTO");
        jclass localMemberDTO = env->FindClass("com/ringid/imsdk/MemberDTO");
        jclass localFileChunk = env->FindClass("com/ringid/imsdk/FileChunk");
        jclass localHashSet = env->FindClass("java/util/HashSet");
        jclass localArrayList = env->FindClass("java/util/ArrayList");
        jclass localIterator = env->FindClass("java/util/Iterator");
        jclass localLong = env->FindClass("java/lang/Long");

        JMessageDTO = (jclass) env->NewGlobalRef(localMessageDTO);
        JMemberDTO = (jclass) env->NewGlobalRef(localMemberDTO);
        JFileChunk = (jclass) env->NewGlobalRef(localFileChunk);
        HashSet = (jclass) env->NewGlobalRef(localHashSet);
        ArrayList = (jclass) env->NewGlobalRef(localArrayList);
        Iterator = (jclass) env->NewGlobalRef(localIterator);
        Long = (jclass) env->NewGlobalRef(localLong);

        mdtoConstructor = env->GetMethodID(JMessageDTO, "<init>", "()V");
        mdtoSetPacketType = env->GetMethodID(JMessageDTO, "setPacketType", "(I)V");
        mdtoSetPacketID = env->GetMethodID(JMessageDTO, "setPacketID", "(Ljava/lang/String;)V");
        mdtoSetUserIdentity = env->GetMethodID(JMessageDTO, "setUserIdentity", "(J)V");
        mdtoSetFullName = env->GetMethodID(JMessageDTO, "setFullName", "(Ljava/lang/String;)V");
        mdtoSetFriendIdentity = env->GetMethodID(JMessageDTO, "setFriendIdentity", "(J)V");
        mdtoSetMessage = env->GetMethodID(JMessageDTO, "setMessage", "(Ljava/lang/String;)V");
        mdtoSetMessageType = env->GetMethodID(JMessageDTO, "setMessageType", "(I)V");
        mdtoSetMessageDate = env->GetMethodID(JMessageDTO, "setMessageDate", "(J)V");
        mdtoSetDevice = env->GetMethodID(JMessageDTO, "setDevice", "(I)V");
        mdtoSetDeviceToken = env->GetMethodID(JMessageDTO, "setDeviceToken", "(Ljava/lang/String;)V");
        mdtoSetTimeout = env->GetMethodID(JMessageDTO, "setTimeout", "(I)V");
        mdtoSetLatitude = env->GetMethodID(JMessageDTO, "setLatitude", "(F)V");
        mdtoSetLongitude = env->GetMethodID(JMessageDTO, "setLongitude", "(F)V");
        mdtoSetGroupId = env->GetMethodID(JMessageDTO, "setGroupId", "(J)V");
        mdtoSetNumberOfMembers = env->GetMethodID(JMessageDTO, "setNumberOfMembers", "(I)V");
        mdtoSetMemberList = env->GetMethodID(JMessageDTO, "setMemberList", "(Ljava/util/ArrayList;)V");
        mdtoSetOnlineStatus = env->GetMethodID(JMessageDTO, "setOnlineStatus", "(I)V");
        mdtoSetNumberOfMessage = env->GetMethodID(JMessageDTO, "setNumberOfMessage", "(I)V");
        mdtoSetPacketIDs = env->GetMethodID(JMessageDTO, "setPacketIDs", "(Ljava/util/ArrayList;)V");
        mdtoSetMessageList = env->GetMethodID(JMessageDTO, "setMessageList", "(Ljava/util/ArrayList;)V");
        mdtoSetSequenceNumber = env->GetMethodID(JMessageDTO, "setSequenceNumber", "(I)V");
        mdtoSetChatBindingPort = env->GetMethodID(JMessageDTO, "setChatBindingPort", "(I)V");
        mdtoSetAppType = env->GetMethodID(JMessageDTO, "setAppType", "(I)V");
        mdtoSetOnlineMood = env->GetMethodID(JMessageDTO, "setOnlineMood", "(I)V");
        mdtoSetFileTotalChunk = env->GetMethodID(JMessageDTO, "setFileTotalChunk", "(I)V");
        mdtoSetFileChunkCurrentIndex = env->GetMethodID(JMessageDTO, "setFileChunkCurrentIndex", "(I)V");
        mdtoSetFileContent = env->GetMethodID(JMessageDTO, "setFileContent", "(Ljava/lang/String;)V");
        mdtoSetFileChunkList = env->GetMethodID(JMessageDTO, "setFileChunkList", "(Ljava/util/ArrayList;)V");
        mdtoSetIsAddToBlock = env->GetMethodID(JMessageDTO, "setIsAddToBlock", "(Z)V");
        mdtoSetGroupName = env->GetMethodID(JMessageDTO, "setGroupName", "(Ljava/lang/String;)V");
        mdtoSetGroupUrl = env->GetMethodID(JMessageDTO, "setGroupUrl", "(Ljava/lang/String;)V");
        mdtoSetIsUpdateGroupInformation = env->GetMethodID(JMessageDTO, "setIsUpdateGroupInformation", "(Z)V");
        mdtoSetTotalGroupMembers = env->GetMethodID(JMessageDTO, "setTotalGroupMembers", "(I)V");

        mdtoConstructor = env->GetMethodID(JMessageDTO, "<init>", "()V");
        mdtoGetPacketType = env->GetMethodID(JMessageDTO, "getPacketType", "()I");
        mdtoGetPacketID = env->GetMethodID(JMessageDTO, "getPacketID", "()Ljava/lang/String;");
        mdtoGetUserIdentity = env->GetMethodID(JMessageDTO, "getUserIdentity", "()J");
        mdtoGetFullName = env->GetMethodID(JMessageDTO, "getFullName", "()Ljava/lang/String;");
        mdtoGetFriendIdentity = env->GetMethodID(JMessageDTO, "getFriendIdentity", "()J");
        mdtoGetMessage = env->GetMethodID(JMessageDTO, "getMessage", "()Ljava/lang/String;");
        mdtoGetMessageType = env->GetMethodID(JMessageDTO, "getMessageType", "()I");
        mdtoGetMessageDate = env->GetMethodID(JMessageDTO, "getMessageDate", "()J");
        mdtoGetDevice = env->GetMethodID(JMessageDTO, "getDevice", "()I");
        mdtoGetDeviceToken = env->GetMethodID(JMessageDTO, "getDeviceToken", "()Ljava/lang/String;");
        mdtoGetTimeout = env->GetMethodID(JMessageDTO, "getTimeout", "()I");
        mdtoGetLatitude = env->GetMethodID(JMessageDTO, "getLatitude", "()F");
        mdtoGetLongitude = env->GetMethodID(JMessageDTO, "getLongitude", "()F");
        mdtoGetGroupId = env->GetMethodID(JMessageDTO, "getGroupId", "()J");
        mdtoGetNumberOfMembers = env->GetMethodID(JMessageDTO, "getNumberOfMembers", "()I");
        mdtoGetMemberList = env->GetMethodID(JMessageDTO, "getMemberList", "()Ljava/util/ArrayList;");
        mdtoGetOnlineStatus = env->GetMethodID(JMessageDTO, "getOnlineStatus", "()I");
        mdtoGetNumberOfMessage = env->GetMethodID(JMessageDTO, "getNumberOfMessage", "()I");
        mdtoGetPacketIDs = env->GetMethodID(JMessageDTO, "getPacketIDs", "()Ljava/util/ArrayList;");
        mdtoGetMessageList = env->GetMethodID(JMessageDTO, "getMessageList", "()Ljava/util/ArrayList;");
        mdtoGetSequenceNumber = env->GetMethodID(JMessageDTO, "getSequenceNumber", "()I");
        mdtoGetChatBindingPort = env->GetMethodID(JMessageDTO, "getChatBindingPort", "()I");
        mdtoGetServerDate = env->GetMethodID(JMessageDTO, "getServerDate", "()J");
        mdtoGetAppType = env->GetMethodID(JMessageDTO, "getAppType", "()I");
        mdtoGetOnlineMood = env->GetMethodID(JMessageDTO, "getOnlineMood", "()I");
        mdtoGetFileTotalChunk = env->GetMethodID(JMessageDTO, "getFileTotalChunk", "()I");
        mdtoGetFileChunkCurrentIndex = env->GetMethodID(JMessageDTO, "getFileChunkCurrentIndex", "()I");
        mdtoGetFileContent = env->GetMethodID(JMessageDTO, "getFileContent", "()Ljava/lang/String;");
        mdtoGetFileChunkList = env->GetMethodID(JMessageDTO, "getFileChunkList", "()Ljava/util/ArrayList;");
        mdtoGetIsAddToBlock = env->GetMethodID(JMessageDTO, "getIsAddToBlock", "()Z");
        mdtoGetGroupName = env->GetMethodID(JMessageDTO, "getGroupName", "()Ljava/lang/String;");
        mdtoGetGroupUrl = env->GetMethodID(JMessageDTO, "getGroupUrl", "()Ljava/lang/String;");
        mdtoGetIsUpdateGroupInformation = env->GetMethodID(JMessageDTO, "getIsUpdateGroupInformation", "()Z");
        mdtoGetTotalGroupMembers = env->GetMethodID(JMessageDTO, "getTotalGroupMembers", "()I");

        memdtoConstructor = env->GetMethodID(JMemberDTO, "<init>", "()V");
        memdtoConstructorValued = env->GetMethodID(JMemberDTO, "<init>", "(JLjava/lang/String;IJ)V");
        memdtoGetMemberIdentity = env->GetMethodID(JMemberDTO, "getMemberIdentity", "()J");
        memdtoGetFullName = env->GetMethodID(JMemberDTO, "getFullName", "()Ljava/lang/String;");
        memdtoGetStatus = env->GetMethodID(JMemberDTO, "getStatus", "()I");
        memdtoGetAddedBy = env->GetMethodID(JMemberDTO, "getAddedBy", "()J");
        memdtoSetMemberIdentity = env->GetMethodID(JMemberDTO, "setMemberIdentity", "(J)V");
        memdtoSetFullName = env->GetMethodID(JMemberDTO, "setFullName", "(Ljava/lang/String;)V");
        memdtoSetStatus = env->GetMethodID(JMemberDTO, "setStatus", "(I)V");
        memdtoSetAddedBy = env->GetMethodID(JMemberDTO, "setAddedBy", "(J)V");

        fcConstructor = env->GetMethodID(JFileChunk, "<init>", "(II)V");
        fcGetIndexFrom = env->GetMethodID(JFileChunk, "getIndexFrom", "()I");
        fcGetIndexTo = env->GetMethodID(JFileChunk, "getIndexTo", "()I");

        arrayListConstruct = env->GetMethodID(ArrayList, "<init>", "()V");
        arrayListGet = env->GetMethodID(ArrayList, "get", "(I)Ljava/lang/Object;");
        arrayListAdd = env->GetMethodID(ArrayList, "add", "(Ljava/lang/Object;)Z");
        arrayListSize = env->GetMethodID(ArrayList, "size", "()I");
        hashSetConstruct = env->GetMethodID(HashSet, "<init>", "()V");
        hashSetIterator = env->GetMethodID(HashSet, "iterator", "()Ljava/util/Iterator;");
        iteratorHasNext = env->GetMethodID(Iterator, "hasNext", "()Z");
        iteratorNext = env->GetMethodID(Iterator, "next", "()Ljava/lang/Object;");
        longValue = env->GetMethodID(Long, "longValue", "()J");


    }
    return JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM *vm, void *reserved) {
    JNIEnv* env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return;
    } else {
        // delete global references so the GC can collect them

        if (JMessageDTO != NULL) {
            env->DeleteGlobalRef(JMessageDTO);
        }
        if (HashSet != NULL) {
            env->DeleteGlobalRef(HashSet);
        }
        if (ArrayList != NULL) {
            env->DeleteGlobalRef(ArrayList);
        }
        if (Iterator != NULL) {
            env->DeleteGlobalRef(Iterator);
        }
        if (Long != NULL) {
            env->DeleteGlobalRef(Long);
        }
    }
}

jobject getJMemberDTO(JNIEnv *env, MemberDTO &memberDTO) {

    return env->NewObject(JMemberDTO, memdtoConstructorValued,
            memberDTO.getMemberIdentity(),
            env->NewStringUTF(memberDTO.getFullName().c_str()),
            memberDTO.getStatus(),
            memberDTO.getAddedBy()
            );
}

jobject getJMessageDTO(JNIEnv *env, const shared_ptr<PacketDTO> &packet) {

    jobject messageDTO = env->NewObject(JMessageDTO, mdtoConstructor);

    env->CallObjectMethod(messageDTO, mdtoSetPacketType, packet->getPacketType());
    env->CallObjectMethod(messageDTO, mdtoSetPacketID, env->NewStringUTF(packet->getPacketID().c_str()));
    env->CallObjectMethod(messageDTO, mdtoSetUserIdentity, packet->getUserIdentity());
    env->CallObjectMethod(messageDTO, mdtoSetFullName, env->NewStringUTF(packet->getFullName().c_str()));
    env->CallObjectMethod(messageDTO, mdtoSetFriendIdentity, packet->getFriendIdentity());
    env->CallObjectMethod(messageDTO, mdtoSetMessage, env->NewStringUTF(packet->getMessage().c_str()));
    env->CallObjectMethod(messageDTO, mdtoSetMessageType, packet->getMessageType());
    env->CallObjectMethod(messageDTO, mdtoSetMessageDate, packet->getMessageDate());
    env->CallObjectMethod(messageDTO, mdtoSetDevice, packet->getDevice());
    env->CallObjectMethod(messageDTO, mdtoSetDeviceToken, env->NewStringUTF(packet->getFriendDeviceToken().c_str()));
    env->CallObjectMethod(messageDTO, mdtoSetTimeout, packet->getTimeout());
    env->CallObjectMethod(messageDTO, mdtoSetLatitude, packet->getLatitude());
    env->CallObjectMethod(messageDTO, mdtoSetLongitude, packet->getLongitude());
    env->CallObjectMethod(messageDTO, mdtoSetGroupId, packet->getGroupId());
    env->CallObjectMethod(messageDTO, mdtoSetNumberOfMembers, packet->getNumberOfMembers());


    //env->CallObjectMethod(messageDTO, mdtoSetMemberList, packet->getMemberList());

    vector<MemberDTO> memberList = packet->getMemberList();
    if (memberList.size() > 0) {
        jobject memberListObject = env->NewObject(ArrayList, arrayListConstruct);

        for (int i = 0; i < memberList.size(); i++) {
            env->CallObjectMethod(memberListObject, arrayListAdd, getJMemberDTO(env, memberList[i]));
        }

        env->CallObjectMethod(messageDTO, mdtoSetMemberList, memberListObject);
    }

    env->CallObjectMethod(messageDTO, mdtoSetOnlineStatus, packet->getOnlineStatus());
    env->CallObjectMethod(messageDTO, mdtoSetNumberOfMessage, packet->getNumberOfMessage());

    //env->CallObjectMethod(messageDTO, mdtoSetPacketIDs, packet->getPacketIDs());

    vector<string> packetIDs = packet->getPacketIDs();
    if (packetIDs.size() > 0) {
        jobject packetIDsObject = env->NewObject(ArrayList, arrayListConstruct);
        for (int i = 0; i < packetIDs.size(); i++) {
            env->CallObjectMethod(packetIDsObject, arrayListAdd, env->NewStringUTF(packetIDs[i].c_str()));
        }
        env->CallObjectMethod(messageDTO, mdtoSetPacketIDs, packetIDsObject);
    }


    //env->CallObjectMethod(messageDTO, mdtoSetMessageList, packet->getMessageList());

    vector<shared_ptr < PacketDTO>> messageList = packet->getMessageList();
    if (messageList.size() > 0) {
        jobject messageListObject = env->NewObject(ArrayList, arrayListConstruct);
        for (int i = 0; i < messageList.size(); i++) {
            env->CallObjectMethod(messageListObject, arrayListAdd, getJMessageDTO(env, messageList[i]));
        }

        env->CallObjectMethod(messageDTO, mdtoSetMessageList, messageListObject);
    }


    env->CallObjectMethod(messageDTO, mdtoSetSequenceNumber, packet->getSequenceNumber());
    env->CallObjectMethod(messageDTO, mdtoSetChatBindingPort, packet->getChatBindingPort());
    env->CallObjectMethod(messageDTO, mdtoSetAppType, packet->getAppType());
    env->CallObjectMethod(messageDTO, mdtoSetOnlineMood, packet->getOnlineMood());
    env->CallObjectMethod(messageDTO, mdtoSetFileTotalChunk, packet->getFileTotalChunk());
    env->CallObjectMethod(messageDTO, mdtoSetFileChunkCurrentIndex, packet->getFileChunkCurrentIndex());
    env->CallObjectMethod(messageDTO, mdtoSetFileContent, env->NewStringUTF(packet->getFileContent().c_str()));

    vector<pair<int, int> > fileChunkList = packet->getFileChunkList();
    if (fileChunkList.size() > 0) {
        jobject jfileChunkList = env->NewObject(ArrayList, arrayListConstruct);
        for (int i = 0; i < fileChunkList.size(); i++) {
            jobject fileChunk = env->NewObject(JFileChunk, fcConstructor, fileChunkList[i].first, fileChunkList[i].second);
            env->CallObjectMethod(jfileChunkList, arrayListAdd, fileChunk);
        }

        env->CallObjectMethod(messageDTO, mdtoSetFileChunkList, jfileChunkList);
    }

    env->CallObjectMethod(messageDTO, mdtoSetIsAddToBlock, packet->getIsAddToBlock());
    env->CallObjectMethod(messageDTO, mdtoSetGroupName, env->NewStringUTF(packet->getGroupName().c_str()));
    env->CallObjectMethod(messageDTO, mdtoSetGroupUrl, env->NewStringUTF(packet->getGroupUrl().c_str()));
    env->CallObjectMethod(messageDTO, mdtoSetTotalGroupMembers, packet->getTotalGroupMembers());
    env->CallObjectMethod(messageDTO, mdtoSetIsUpdateGroupInformation, packet->getIsUpdateGroupInformation());

    return messageDTO;
}

jobject getMessageDTOHeader(JNIEnv *env, const shared_ptr<PacketDTO> &packet) {

    jobject messageDTO = env->NewObject(JMessageDTO, mdtoConstructor);

    env->CallObjectMethod(messageDTO, mdtoSetPacketType, packet->getPacketType());
    env->CallObjectMethod(messageDTO, mdtoSetUserIdentity, packet->getUserIdentity());
    env->CallObjectMethod(messageDTO, mdtoSetFriendIdentity, packet->getFriendIdentity());

    return messageDTO;
}

MemberDTO getMemberDTO(JNIEnv *env, jobject &jmemberDTO) {
    MemberDTO memberDTO;
    memberDTO.setMemberIdentity(env->CallLongMethod(jmemberDTO, memdtoGetMemberIdentity));
    memberDTO.setFullName(env->GetStringUTFChars((jstring) env->CallObjectMethod(jmemberDTO, memdtoGetFullName), NULL));
    memberDTO.setStatus(env->CallIntMethod(jmemberDTO, memdtoGetStatus));
    memberDTO.setMemberIdentity(env->CallLongMethod(jmemberDTO, memdtoGetMemberIdentity));

    return memberDTO;
}

shared_ptr<PacketDTO> getPacketDTO(JNIEnv *env, jobject &messageDTO) {

    shared_ptr<PacketDTO> packet = make_shared<PacketDTO>();


    packet->setPacketType(env->CallIntMethod(messageDTO, mdtoGetPacketType));
    jstring packetId = (jstring) env->CallObjectMethod(messageDTO, mdtoGetPacketID);
    if (packetId) {
        packet->setPacketID(env->GetStringUTFChars(packetId, NULL));
    }

    packet->setUserIdentity(env->CallLongMethod(messageDTO, mdtoGetUserIdentity));

    jstring fullName = (jstring) env->CallObjectMethod(messageDTO, mdtoGetFullName);
    if (fullName) {
        packet->setFullName(env->GetStringUTFChars(fullName, NULL));
    }

    packet->setFriendIdentity(env->CallLongMethod(messageDTO, mdtoGetFriendIdentity));

    jstring message = (jstring) env->CallObjectMethod(messageDTO, mdtoGetMessage);
    if (message) {
        packet->setMessage(env->GetStringUTFChars(message, NULL));
    }

    packet->setMessageType(env->CallIntMethod(messageDTO, mdtoGetMessageType));
    packet->setMessageDate(env->CallLongMethod(messageDTO, mdtoGetMessageDate));
    packet->setDevice(env->CallIntMethod(messageDTO, mdtoGetDevice));

    jstring deviceToken = (jstring) env->CallObjectMethod(messageDTO, mdtoGetDeviceToken);
    if (deviceToken) {
        packet->setFriendDeviceToken(env->GetStringUTFChars(deviceToken, NULL));
    }

    packet->setTimeout(env->CallIntMethod(messageDTO, mdtoGetTimeout));
    packet->setLatitude(env->CallFloatMethod(messageDTO, mdtoGetLatitude));
    packet->setLongitude(env->CallFloatMethod(messageDTO, mdtoGetLongitude));
    packet->setGroupId(env->CallLongMethod(messageDTO, mdtoGetGroupId));
    packet->setNumberOfMembers(env->CallIntMethod(messageDTO, mdtoGetNumberOfMembers));


    /*jobjectArray memberList = (jobjectArray) env->CallObjectMethod(messageDTO, mdtoGetMemberList);
    //jlongArray memberListArray = reinterpret_cast<jlongArray> (memberList);
    
    len = env->GetArrayLength(memberList);
    
    jobject valObject = env->GetObjectArrayElement(memberList, 1);
    longValue = env->GetMethodID(Long, "longValue", "()J");
    jlong value = env->CallLongMethod(valObject, longValue);
    
    cout<<value<<endl;
    
     */
    jobject memberList = env->CallObjectMethod(messageDTO, mdtoGetMemberList);
    if (memberList) {
        int numberOfMembers = env->CallIntMethod(memberList, arrayListSize);
        for (int i = 0; i < numberOfMembers; i++) {
            jobject member = env->CallObjectMethod(memberList, arrayListGet, i);
            packet->appendMember(getMemberDTO(env, member));
        }
    }

    packet->setOnlineStatus(env->CallIntMethod(messageDTO, mdtoGetOnlineStatus));
    packet->setNumberOfMessage(env->CallIntMethod(messageDTO, mdtoGetNumberOfMessage));


    jobject packetIDs = env->CallObjectMethod(messageDTO, mdtoGetPacketIDs);
    if (packetIDs) {
        int numberOfPacktID = env->CallIntMethod(packetIDs, arrayListSize);
        //cout<<"number of packetid : "<<numberOfPacktID<<endl;

        for (int i = 0; i < numberOfPacktID; i++) {
            jstring val = (jstring) env->CallObjectMethod(packetIDs, arrayListGet, i);
            packet->appendPacketID(env->GetStringUTFChars(val, NULL));
        }
        //cout<<endl;
    }

    //packet->setMessageList(env->CallObjectMethod(messageDTO, mdtoGetMessageList));
    jobject messageList = env->CallObjectMethod(messageDTO, mdtoGetMessageList);
    if (messageList) {
        int numberOfMessages = env->CallIntMethod(messageList, arrayListSize);
        for (int i = 0; i < numberOfMessages; i++) {
            jobject messageListElement = env->CallObjectMethod(messageList, arrayListGet, i);
            packet->appendMessage(getPacketDTO(env, messageListElement));
        }
    }

    packet->setSequenceNumber(env->CallIntMethod(messageDTO, mdtoGetSequenceNumber));
    packet->setChatBindingPort(env->CallIntMethod(messageDTO, mdtoGetChatBindingPort));
    packet->setServerDate(env->CallLongMethod(messageDTO, mdtoGetServerDate));
    packet->setAppType(env->CallIntMethod(messageDTO, mdtoGetAppType));
    packet->setOnlineMood(env->CallIntMethod(messageDTO, mdtoGetOnlineMood));
    packet->setFileTotalChunk(env->CallIntMethod(messageDTO, mdtoGetFileTotalChunk));
    packet->setFileChunkCurrentIndex(env->CallIntMethod(messageDTO, mdtoGetFileChunkCurrentIndex));

    jstring fileContent = (jstring) env->CallObjectMethod(messageDTO, mdtoGetFileContent);
    if (fileContent) {
        packet->setFileContent(env->GetStringUTFChars(fileContent, NULL));
    }

    jobject fileChunkList = env->CallObjectMethod(messageDTO, mdtoGetFileChunkList);
    if (fileChunkList) {
        int numberOfChunk = env->CallIntMethod(fileChunkList, arrayListSize);
        for (int i = 0; i < numberOfChunk; i++) {
            jobject fileChunk = env->CallObjectMethod(fileChunkList, arrayListGet, i);
            int fromIndex = env->CallIntMethod(fileChunk, fcGetIndexFrom);
            int toIndex = env->CallIntMethod(fileChunk, fcGetIndexTo);
            packet->appendFileChunk({fromIndex, toIndex});
        }
    }

    packet->setIsAddToBlock(env->CallBooleanMethod(messageDTO, mdtoGetIsAddToBlock));
    jstring groupName = (jstring) env->CallObjectMethod(messageDTO, mdtoGetGroupName);
    if (groupName) {
        packet->setGroupName(env->GetStringUTFChars(groupName, NULL));
    }
    
    jstring groupUrl = (jstring) env->CallObjectMethod(messageDTO, mdtoGetGroupUrl);
    if (groupUrl)
    {
        packet->setGroupUrl(env->GetStringUTFChars(groupUrl, NULL));
    }
    
    packet->setIsUpdateGroupInformation(env->CallBooleanMethod(messageDTO, mdtoGetIsUpdateGroupInformation));
    packet->setTotalGroupMembers(env->CallIntMethod(messageDTO, mdtoGetTotalGroupMembers));

    return packet;
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_ChatParser_parse___3B
(JNIEnv *env, jobject, jbyteArray byteArray) {
    //printf("hey from chatparser ");
    //cout<<endl;

    int len = env->GetArrayLength(byteArray);
    ByteArray data(len);

    env->GetByteArrayRegion(byteArray, 0, len, reinterpret_cast<jbyte*> (data.getDataPtr()));

    ChatParser parser;
    ParsedObject parsedObject = parser.parse(data);

    return getJMessageDTO(env, parsedObject.packet);
}

JNIEXPORT jobject JNICALL Java_com_ringid_imsdk_ChatParser_parseHeader
(JNIEnv *env, jobject, jbyteArray byteArray) {
    int len = env->GetArrayLength(byteArray);
    ByteArray data(len);

    env->GetByteArrayRegion(byteArray, 0, len, reinterpret_cast<jbyte*> (data.getDataPtr()));

    ChatParser parser;
    ParsedObject parsedObject = parser.parseHeader(data);

    return getMessageDTOHeader(env, parsedObject.packet);
}

JNIEXPORT jbyteArray JNICALL Java_com_ringid_imsdk_ChatParser_parse__Lcom_ringid_imsdk_MessageDTO_2
(JNIEnv *env, jobject, jobject messageDTO) {
    ChatParser parser;
    shared_ptr<PacketDTO> packet = getPacketDTO(env, messageDTO);
    shared_ptr<ByteArray> data = parser.parse(packet);

    jbyteArray byteData = env->NewByteArray(data->size());
    env->SetByteArrayRegion(byteData, 0, data->size(), reinterpret_cast<jbyte*> (data->getDataPtr()));

    return byteData;
}

JNIEXPORT jstring JNICALL Java_com_ringid_imsdk_ChatParser_version
(JNIEnv *env, jobject) {
    ChatParser parser;
    string version = parser.version();

    jstring jversion = env->NewStringUTF(version.c_str());

    return jversion;
}