#include <jni.h>
#include <string>
#include <android/log.h>
#include "ArrayList.hpp"

extern "C" JNIEXPORT jstring JNICALL
Java_com_ndk_day25_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    ArrayList<int> *list = new ArrayList<int>(100);

    for (int i = 0; i < 10; ++i) {
        list->add(i);
    }

    int remove1 = list->remove(1);
    __android_log_print(ANDROID_LOG_INFO, "native-lib", "remove元素：%d", remove1);




    for (int i = 0; i < list->size(); ++i) {
        __android_log_print(ANDROID_LOG_INFO, "native-lib", "元素：%d", list->get(i));
    }


    delete (list);

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}