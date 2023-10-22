/* 
 * File:   DataCounterConversion.h
 * Author: towhid
 *
 * Created on August 2, 2016, 11:10 AM
 */

#include "DataCounterConversion.h"
#include "ArrayListManipulation.h"
#include "Logger.h"

#define module "jni"

namespace imsdk {
jclass JDataCounter;

jmethodID mDCCtor;
jmethodID mGetDataSent;
jmethodID mGetDataReceived;

    
void onloadDataCounter(JNIEnv *env){
    jclass localJDataCounter = env->FindClass("com/ringid/imsdk/DataCounter");
    JDataCounter = (jclass) env->NewGlobalRef(localJDataCounter);

    mDCCtor = env->GetMethodID(JDataCounter, "<init>", "(JJ)V");
    mGetDataSent = env->GetMethodID(JDataCounter, "getDataSent", "()J");
    mGetDataReceived = env->GetMethodID(JDataCounter, "getDataReceived", "()J");
}

void onunloadDataCounter(JNIEnv *env){
    if (JDataCounter) {
        env->DeleteGlobalRef(JDataCounter);
    }
}

DataCounter getDataCounter(JNIEnv *env, const jobject &jdataCounter){
    DataCounter dataCounter;
    
    dataCounter.setDataSent(env->CallLongMethod(jdataCounter, mGetDataSent));
    dataCounter.setDataReceived(env->CallLongMethod(jdataCounter, mGetDataReceived));
    
    return dataCounter;
}

jobject getJDataCounter(JNIEnv *env, const DataCounter &dataCounter){
    jobject jdataCounter = env->NewObject(JDataCounter, mDCCtor, dataCounter.getDataSent(), dataCounter.getDataReceived());
    return jdataCounter;
}

}
