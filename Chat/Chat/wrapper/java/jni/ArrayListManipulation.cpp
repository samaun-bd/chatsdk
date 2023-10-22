
#include "ArrayListManipulation.h"

namespace imsdk {
jclass ArrayList;

jmethodID arrayListConstructor;
jmethodID arrayListGetMethod;
jmethodID arrayListAddMethod;
jmethodID arrayListSizeMethod;

void onLoadArrayList(JNIEnv *env)
{
    jclass localArrayList = env->FindClass("java/util/ArrayList");
    ArrayList = (jclass) env->NewGlobalRef(localArrayList);

    arrayListConstructor = env->GetMethodID(ArrayList, "<init>", "()V");
    arrayListGetMethod = env->GetMethodID(ArrayList, "get", "(I)Ljava/lang/Object;");
    arrayListAddMethod = env->GetMethodID(ArrayList, "add", "(Ljava/lang/Object;)Z");
    arrayListSizeMethod = env->GetMethodID(ArrayList, "size", "()I");
}

void onUnloadArrayList(JNIEnv *env)
{
    if (ArrayList) {
        env->DeleteGlobalRef(ArrayList);
    }
}

jobject getNewArrayList(JNIEnv *env)
{
    return env->NewObject(ArrayList, arrayListConstructor);
}

jobject arrayListGet(JNIEnv *env, const jobject &jmemberList, int i)
{
    return env->CallObjectMethod(jmemberList, arrayListGetMethod, i);
}

void arrayListAdd(JNIEnv *env, jobject arrayListObject, const jobject &listItem)
{
    env->CallBooleanMethod(arrayListObject, arrayListAddMethod, listItem);
}

int arrayListSize(JNIEnv *env, const jobject &jmemberList)
{
    return env->CallIntMethod(jmemberList, arrayListSizeMethod);
}

jstring toUtf8JString(JNIEnv *env, const std::string &str){
    
        jbyteArray array = env->NewByteArray(str.size());
        env->SetByteArrayRegion(array, 0, str.size(), (const jbyte*)str.c_str());
        jstring strEncode = env->NewStringUTF("UTF-8");
        jclass cls = env->FindClass("java/lang/String");
        jmethodID ctor = env->GetMethodID(cls, "<init>", "([BLjava/lang/String;)V");
        jstring object = (jstring) env->NewObject(cls, ctor, array, strEncode);
        env->DeleteLocalRef(cls);
//        env->ReleaseByteArrayElements(array, (jbyte*)str.c_str(), JNI_ABORT);
        env->DeleteLocalRef(strEncode);
        env->DeleteLocalRef(array);
        return object;
}

std::string toUtf8CString(JNIEnv *env, jstring string){
        
        jclass cls = env->FindClass("java/lang/String");
        jmethodID getBytes = env->GetMethodID(cls, "getBytes", "(Ljava/lang/String;)[B");
        jstring strEncode = env->NewStringUTF("UTF-8");
        
        jbyteArray array = (jbyteArray) env->CallObjectMethod(string, getBytes, strEncode);
        
        int len = env->GetArrayLength(array);

        char* buf = new char[len];
        env->GetByteArrayRegion(array, 0, len, reinterpret_cast<jbyte*>(buf));
        std::string str(buf, len);

        delete[] buf;

        return str;
}

ByteArray toByteArray(JNIEnv *env, jbyteArray array) {
    int len = env->GetArrayLength(array);

    char* buf = new char[len];
    env->GetByteArrayRegion(array, 0, len, reinterpret_cast<jbyte*>(buf));

    ByteArray byteArray((const byte *)buf, len);
    delete[] buf;

    return byteArray;
}

jbyteArray toJByteArray(JNIEnv *env, ByteArray &byteArray) {
    int len = byteArray.size();

//    std::string dataString = byteArray.getString(0, len);

    jbyteArray jbAraay = env->NewByteArray(len);

    env->SetByteArrayRegion(jbAraay, 0, len, reinterpret_cast<const jbyte*>(byteArray.getDataPtr()));

    return jbAraay;
}

void checkForException(JNIEnv *env)
{
    jthrowable exc = env->ExceptionOccurred();
    if(exc) {
        env->ExceptionDescribe();  //----> NOTE THE COMMENTED STATEMENT
        env->ExceptionClear();  //-----> NOTE THE COMMENTED STATEMENT
        Log(module, "SDK developer has un-handled exception");
    }

    env->DeleteLocalRef(exc);
}
}