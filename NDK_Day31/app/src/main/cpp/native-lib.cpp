#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_ndk_day31_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_ndk_day31_BankCardOcr_cardOcr(JNIEnv *env, jclass clazz, jobject bitmap) {

    return env->NewStringUTF("123456");
}