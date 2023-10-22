/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FriendMessageStatusDTOConversion.h
 * Author: noman
 *
 * Created on February 1, 2016, 4:20 PM
 */

#ifndef FRIENDMESSAGESTATUSDTOCONVERSION_H
#define FRIENDMESSAGESTATUSDTOCONVERSION_H

#include "jni.h"
#include "FriendMessageStatusDTO.h"

namespace imsdk {
void onloadFriendMessageStatusDTO(JNIEnv *env);
void onunloadFriendMessageStatusDTO(JNIEnv *env);
FriendMessageStatusDTO getFriendMessageStatusDTO(JNIEnv *env, const jobject &jfriendMessageStatusDTO);
jobject getJFriendMessageStatusDTO(JNIEnv *env, const FriendMessageStatusDTO &friendMessageStatusDTO);
std::vector<FriendMessageStatusDTO> getFriendMessageStatusList(JNIEnv *env, const jobject &jfriendMessageStatusList);
jobject getJFriendMessageStatusList(JNIEnv *env, const std::vector<FriendMessageStatusDTO> &friendMessageStatusList);
}

#endif /* FRIENDMESSAGESTATUSDTOCONVERSION_H */

