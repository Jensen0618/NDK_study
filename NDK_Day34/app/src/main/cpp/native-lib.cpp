#include <jni.h>
#include <string>
#include "LinkedList.hpp"
//定义TAG之后，我们可以在LogCat通过TAG过滤出NDK打印的日志
#define TAG "NDK_Day34"
// 定义info信息
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

#include <android/log.h>
extern "C" JNIEXPORT jstring JNICALL
Java_com_ndk_day34_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    //测试代码
    LinkedList<int> linkedList;

//    time_t start = clock();
//
//    for (int i = 0; i < 50000; ++i) {
//        linkedList.push(i);
//    }
//
//    time_t end = clock();
//
//    LOGD("耗时：%d",(end-start)/CLOCKS_PER_SEC);
    

    linkedList.push(0);//0
    linkedList.push(1);//1
    linkedList.push(2);//2


    linkedList.insert(0, 10);
    linkedList.insert(2, 20);
    linkedList.insert(5, 50);
    linkedList.insert(6, 100);



    for (int i = 0; i < linkedList.size(); ++i) {
        LOGD("%d",linkedList.get(i));
    }

    LOGD("删除元素");

    linkedList.remove(0);
    linkedList.remove(2);
    linkedList.remove(linkedList.size() - 1);

    for (int i = 0; i < linkedList.size(); ++i) {
        LOGD("%d",linkedList.get(i));
    }


    return env->NewStringUTF(hello.c_str());
}