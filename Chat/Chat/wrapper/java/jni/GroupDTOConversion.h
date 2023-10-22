/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GroupDTOConversion.h
 * Author: noman
 *
 * Created on February 1, 2016, 2:50 PM
 */

#ifndef GROUPDTOCONVERSION_H
#define GROUPDTOCONVERSION_H

#include "jni.h"
#include "GroupDTO.h"

namespace imsdk {
void onloadGroupDTO(JNIEnv *env);
void onunloadGroupDTO(JNIEnv *env);
GroupDTO getGroupDTO(JNIEnv *env, const jobject &jgroupDTO);
jobject getJGroupDTO(JNIEnv *env, const GroupDTO &groupDTO);
std::vector<GroupDTO> getGroupList(JNIEnv *env, const jobject &jgroupList);
jobject getJGroupList(JNIEnv *env, const std::vector<GroupDTO> &groupList);
}
#endif /* GROUPDTOCONVERSION_H */

