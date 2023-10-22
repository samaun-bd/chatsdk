/* 
 * File:   MemberDTOConversion.h
 * Author: dipal
 *
 * Created on October 18, 2015, 1:19 PM
 */

#ifndef MEMBERDTOCONVERSION_H
#define	MEMBERDTOCONVERSION_H

#include <jni.h>
#include "MemberDTO.h"

namespace imsdk {
void onloadMemberDTO(JNIEnv *env);
void onunloadMemberDTO(JNIEnv *env);
MemberDTO getMemberDTO(JNIEnv *env, const jobject &jmemberDTO);
jobject getJMemberDTO(JNIEnv *env, const MemberDTO &memberDTO);
std::vector<MemberDTO> getMemberList(JNIEnv *env, const jobject &jmemberList);
jobject getJMemberList(JNIEnv *env, const std::vector<MemberDTO> &memberList);
}

#endif	/* MEMBERDTOCONVERSION_H */

