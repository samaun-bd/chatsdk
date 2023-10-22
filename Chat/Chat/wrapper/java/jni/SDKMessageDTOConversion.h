/* 
 * File:   MessageDTOConversion.h
 * Author: towhid
 *
 * Created on May 7, 2016, 4:33 PM
 */

#ifndef MESSAGEDTOCONVERSION_H
#define	MESSAGEDTOCONVERSION_H

#include <jni.h>
#include "SDKMessageDTO.h"

namespace imsdk{
void onloadMessageDTO(JNIEnv *env);
void onunloadMessageDTO(JNIEnv *env);
SDKMessageDTO getMessageDTO(JNIEnv *env, const jobject &jmessageDTO);
jobject getJMessageDTO(JNIEnv *env, const SDKMessageDTO &messageDTO);
std::vector<SDKMessageDTO> getMessageList(JNIEnv *env, const jobject &jmessageList);
jobject getJMessageList(JNIEnv *env, const std::vector<SDKMessageDTO> &messageList);
}

#endif	/* MESSAGEDTOCONVERSION_H */

