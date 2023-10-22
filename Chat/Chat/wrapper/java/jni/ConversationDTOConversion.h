/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConversationDTOConversion.h
 * Author: noman
 *
 * Created on October 19, 2016, 4:35 PM
 */

#ifndef CONVERSATIONDTOCONVERSION_H
#define CONVERSATIONDTOCONVERSION_H

#include <jni.h>
#include "ConversationDTO.h"

namespace imsdk {
void onloadConversationDTO(JNIEnv *env);
void onunloadConversationDTO(JNIEnv *env);
ConversationDTO getConversationDTO(JNIEnv *env, const jobject &jconversationDTO);
jobject getJConversationDTO(JNIEnv *env, const ConversationDTO &conversationDTO);
std::vector<ConversationDTO> getConversationList(JNIEnv *env, const jobject &jconversationList);
jobject getJConversationList(JNIEnv *env, const std::vector<ConversationDTO> &conversationList);
}

#endif /* CONVERSATIONDTOCONVERSION_H */

