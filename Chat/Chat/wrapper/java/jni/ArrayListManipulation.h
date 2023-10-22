/* 
 * File:   ArrayListManipulation.h
 * Author: root
 *
 * Created on November 17, 2015, 2:52 PM
 */

#ifndef ARRAYLISTMANIPULATION_H
#define	ARRAYLISTMANIPULATION_H

#include <jni.h>
#include <string>
#include <Logger.h>
#include "ByteArray.h"

#define module "jni"

namespace imsdk {
void onLoadArrayList(JNIEnv *env);
void onUnloadArrayList(JNIEnv *env);
jobject getNewArrayList(JNIEnv *env);
jobject arrayListGet(JNIEnv *env, const jobject &jmemberList, int i);
void arrayListAdd(JNIEnv *env, jobject arrayListObject, const jobject &listItem);
int arrayListSize(JNIEnv *env, const jobject &jmemberList);
jstring toUtf8JString(JNIEnv *env,const std::string &str);
std::string toUtf8CString(JNIEnv *env, jstring string);
void checkForException(JNIEnv *env);
ByteArray toByteArray(JNIEnv *env, jbyteArray array);
jbyteArray toJByteArray(JNIEnv *env, ByteArray &byteArray);
}
#endif	/* ARRAYLISTMANIPULATION_H */

