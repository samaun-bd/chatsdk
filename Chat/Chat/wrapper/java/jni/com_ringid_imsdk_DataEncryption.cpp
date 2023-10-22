#include "com_ringid_imsdk_DataEncryption.h"
#include "DataEncryption.h"
#include "ArrayListManipulation.h"

ipvsdk::security::DataEncryption *dataEncryption = nullptr;

JNIEXPORT jbyteArray JNICALL Java_com_ringid_imsdk_DataEncryption_encryptData
  (JNIEnv *env, jclass, jbyteArray jdata, jbyteArray jkey, jint startIndex) {
    if(jdata == NULL || jkey == NULL) {
        jbyteArray jemptyByteArray = env->NewByteArray(0);
        return jemptyByteArray;
    }
    imsdk::ByteArray dataBytes = imsdk::toByteArray(env, jdata);
    imsdk::ByteArray keyBytes = imsdk::toByteArray(env, jkey);

    imsdk::ByteArray encryptedDataBytes = ipvsdk::security::DataEncryption::encryptMessage(dataBytes, keyBytes, startIndex);

    jbyteArray jencryptedDataBytes = imsdk::toJByteArray(env, encryptedDataBytes);
    
    int jlen = env->GetArrayLength(jencryptedDataBytes);
        
    return jencryptedDataBytes;
}

JNIEXPORT jbyteArray JNICALL Java_com_ringid_imsdk_DataEncryption_decryptData
  (JNIEnv *env, jclass, jbyteArray jdata, jbyteArray jkey, jint startIndex) {
    if(jdata == NULL || jkey == NULL) {
        jbyteArray jemptyByteArray = env->NewByteArray(0);
        return jemptyByteArray;
    }
    imsdk::ByteArray dataBytes = imsdk::toByteArray(env, jdata);
    imsdk::ByteArray keyBytes = imsdk::toByteArray(env, jkey);

    imsdk::ByteArray decryptedDataBytes = ipvsdk::security::DataEncryption::decryptMessage(dataBytes, keyBytes, startIndex);
    
    jbyteArray jdecryptedDataBytes = imsdk::toJByteArray(env, decryptedDataBytes);

    return jdecryptedDataBytes;
}

JNIEXPORT jstring JNICALL Java_com_ringid_imsdk_DataEncryption_getSessionlessKey
  (JNIEnv *env, jclass, jstring jipAddress, jlong ringId) {
    std::string ipAddress = "";
    if(jipAddress != NULL) {
        ipAddress = env->GetStringUTFChars(jipAddress, NULL);
    }

    std::string sessionlessKey = ipvsdk::security::DataEncryption::getSessionlessKey(ipAddress, ringId);
    jstring jsessionlessKey = env->NewStringUTF(sessionlessKey.c_str());

    env->DeleteLocalRef(jipAddress);

    return jsessionlessKey;
}

