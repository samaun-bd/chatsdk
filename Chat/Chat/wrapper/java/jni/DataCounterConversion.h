/* 
 * File:   DataCounterConversion.h
 * Author: towhid
 *
 * Created on August 2, 2016, 11:10 AM
 */

#ifndef DATACOUNTERCONVERSION_H
#define	DATACOUNTERCONVERSION_H

#include "jni.h"
#include "DataCounter.h"

namespace imsdk {
void onloadDataCounter(JNIEnv *env);
void onunloadDataCounter(JNIEnv *env);
DataCounter getDataCounter(JNIEnv *env, const jobject &jdataCounter);
jobject getJDataCounter(JNIEnv *env, const DataCounter &dataCounter);
}

#endif	/* DATACOUNTERCONVERSION_H */

