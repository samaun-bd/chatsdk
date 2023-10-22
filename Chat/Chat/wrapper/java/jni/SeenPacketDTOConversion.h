/* 
 * File:   SeenPacketDTOConversion.h
 * Author: root
 *
 * Created on December 7, 2015, 5:27 PM
 */

#ifndef SEENPACKETDTOCONVERSION_H
#define	SEENPACKETDTOCONVERSION_H

#include "SeenPacketDTO.h"
#include "jni.h"

namespace imsdk {
void onloadSeenPacketDTO(JNIEnv *env);
void onunloadSeenPacketDTO(JNIEnv *env);
SeenPacketDTO getSeenPacketDTO(JNIEnv *env, const jobject &jseenPacketDTO);
jobject getJSeenPacketDTO(JNIEnv *env, const SeenPacketDTO &seenPacketDTO);
std::vector<SeenPacketDTO> getSeenPacketList(JNIEnv *env, const jobject &jseenPacketList);
jobject getJSeenPacketList(JNIEnv *env, const std::vector<SeenPacketDTO> &seenPacketList);
}

#endif	/* SEENPACKETDTOCONVERSION_H */

