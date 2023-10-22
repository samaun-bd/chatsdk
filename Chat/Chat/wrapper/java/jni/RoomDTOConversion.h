/* 
 * File:   RoomDTOConversion.h
 * Author: towhid
 *
 * Created on April 5, 2016, 3:18 PM
 */

#ifndef ROOMDTOCONVERSION_H
#define	ROOMDTOCONVERSION_H

#include "jni.h"
#include "RoomDTO.h"
#include <vector>

namespace imsdk {
void onloadRoomDTO(JNIEnv *env);
void onunloadRoomDTO(JNIEnv *env);
RoomDTO getRoomDTO(JNIEnv *env, const jobject &jroomDTO);
jobject getJRoomDTO(JNIEnv *env, const RoomDTO &roomDTO);
std::vector<RoomDTO> getRoomList(JNIEnv *env, const jobject &jroomList);
jobject getJRoomList(JNIEnv *env, const std::vector<RoomDTO> &roomList);
}


#endif	/* ROOMDTOCONVERSION_H */

