#include <jni.h>
#include <cstdio>

// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("main");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("main")
//      }
//    }
extern "C"
JNIEXPORT jstring JNICALL
Java_com_jensen_libffmpeg_FfmpegUtils_getFFmpegVersion(JNIEnv *env, jclass clazz) {

    return
}