#include "com_ringid_imsdk_InternetChecker.h"
#include "InternetChecker.h"

internetchecker::InternetChecker *internetChecker = nullptr;

JNIEXPORT jboolean JNICALL Java_com_ringid_imsdk_InternetChecker_checkInternetConnection
  (JNIEnv *env, jobject){
    return internetChecker->checkInternetConnection();
}

JNIEXPORT void JNICALL Java_com_ringid_imsdk_InternetChecker_ctor
  (JNIEnv *env, jobject, jstring jipListFilePath){
    std::string ipListFilePath = env->GetStringUTFChars(jipListFilePath, NULL);

    internetChecker = new internetchecker::InternetChecker();
    internetChecker->setIpListFilePath(ipListFilePath);
    internetChecker->populateIPListIfNeeded();

    env->DeleteLocalRef(jipListFilePath);
}