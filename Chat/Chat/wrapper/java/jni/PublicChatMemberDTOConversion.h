/* 
 * File:   PublicChatMemberDTOConversion.h
 * Author: towhid
 *
 * Created on April 9, 2016, 6:29 PM
 */

#ifndef PUBLICCHATMEMBERDTOCONVERSION_H
#define	PUBLICCHATMEMBERDTOCONVERSION_H

#include "jni.h"
#include "PublicChatMemberDTO.h"
#include <vector>


namespace imsdk {
void onloadPublicChatMemberDTO(JNIEnv *env);
void onunloadPublicChatMemberDTO(JNIEnv *env);
PublicChatMemberDTO getPublicChatMemberDTO(JNIEnv *env, const jobject &jpublicChatMemberDTO);
jobject getJPublicChatMemberDTO(JNIEnv *env, const PublicChatMemberDTO &publicChatMemberDTO);
std::vector<PublicChatMemberDTO> getPublicChatMemberList(JNIEnv *env, const jobject &jpublicChatMemberList);
jobject getJPublicChatMemberList(JNIEnv *env, const std::vector<PublicChatMemberDTO> &publicChatMemberList);
}

#endif	/* PUBLICCHATMEMBERDTOCONVERSION_H */

