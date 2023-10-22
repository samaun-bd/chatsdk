/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GroupActivityDTOConversion.h
 * Author: noman
 *
 * Created on February 1, 2016, 3:42 PM
 */

#ifndef GROUPACTIVITYDTOCONVERSION_H
#define GROUPACTIVITYDTOCONVERSION_H

#include "jni.h"
#include "GroupActivityDTO.h"

namespace imsdk {
void onloadGroupActivityDTO(JNIEnv *env);
void onunloadGroupActivityDTO(JNIEnv *env);
GroupActivityDTO getGroupActivityDTO(JNIEnv *env, const jobject &jgroupActivityDTO);
jobject getJGroupActivityDTO(JNIEnv *env, const GroupActivityDTO &groupActivityDTO);
std::vector<GroupActivityDTO> getGroupActivityList(JNIEnv *env, const jobject &jgroupActivityList);
jobject getJGroupActivityList(JNIEnv *env, const std::vector<GroupActivityDTO> &groupActivityList);
}

#endif /* GROUPACTIVITYDTOCONVERSION_H */

