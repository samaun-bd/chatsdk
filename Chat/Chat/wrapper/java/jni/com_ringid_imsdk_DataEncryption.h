/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_ringid_imsdk_DataEncryption */

#ifndef _Included_com_ringid_imsdk_DataEncryption
#define _Included_com_ringid_imsdk_DataEncryption
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_ringid_imsdk_DataEncryption
 * Method:    encryptData
 * Signature: ([B[BI)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_ringid_imsdk_DataEncryption_encryptData
  (JNIEnv *, jclass, jbyteArray, jbyteArray, jint);

/*
 * Class:     com_ringid_imsdk_DataEncryption
 * Method:    decryptData
 * Signature: ([B[BI)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_ringid_imsdk_DataEncryption_decryptData
  (JNIEnv *, jclass, jbyteArray, jbyteArray, jint);

/*
 * Class:     com_ringid_imsdk_DataEncryption
 * Method:    getSessionlessKey
 * Signature: (Ljava/lang/String;J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_ringid_imsdk_DataEncryption_getSessionlessKey
  (JNIEnv *, jclass, jstring, jlong);

#ifdef __cplusplus
}
#endif
#endif
