#include <jni.h>
#include <string>
#include <android/log.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_ndk_day26_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

void c_throws() {
    throw 1;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ndk_day26_MainActivity_arraycopy(JNIEnv *env, jclass clazz, jobject src, jint src_pos,
                                          jobject dest, jint dest_pos, jint length) {
//这里需要类型转换，将jobject转成j数组

    jobjectArray srcArray = reinterpret_cast<jobjectArray>(src);
    jobjectArray destArray = reinterpret_cast<jobjectArray>(dest);

    if (srcArray != NULL && destArray != NULL) {
        __android_log_print(ANDROID_LOG_DEBUG, "ArrayCopy", "转换成功");

        for (int i = src_pos; i < length; ++i) {
            jobject oldObj = env->GetObjectArrayElement(srcArray, i);
            env->SetObjectArrayElement(destArray, i, oldObj);
        }
    }
    //异常处理
    //C++有一套自己的异常体系，用的名字和Java是一样的都叫Exception
    //同样是try...catch
    //C++能够捕捉任意类型的错误
    //NDK开发中最好抛Java的异常，C++/C中抛系统异常
    try {
//        throw 0.0f;
        c_throws();
    } catch (int n) {
        __android_log_print(ANDROID_LOG_DEBUG, "ArrayCopy", "%d", n);
    } catch (...) {//相当于Java的Exception e
        jclass je = env->FindClass("java/lang/Exception");
        env->ThrowNew(je, "unknown exception in JNI code");
    }


}


