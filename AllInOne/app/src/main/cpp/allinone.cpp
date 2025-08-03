#include <jni.h>
#include <android/bitmap.h>

// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("allinone");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("allinone")
//      }
//    }

extern "C"
JNIEXPORT jint JNICALL
Java_com_jensen_allinone_BitmapUtil_cvtColorNative(JNIEnv *env, jclass clazz, jobject src) {
    int ret=0;
    AndroidBitmapInfo info;

    ret = AndroidBitmap_getInfo(env, src, &info);
    if (ret != ANDROID_BITMAP_RESULT_SUCCESS) {
        return ret;
    }
    void *pixels;
    ret=AndroidBitmap_lockPixels(env, src, &pixels);

    int length = info.width * info.height;
    for (int i = 0; i < length; ++i) {
        uint32_t *pixel_p = reinterpret_cast<uint32_t *>(pixels)+i;
        uint32_t pixel = *pixel_p;
        int a = pixel >> 24 & 0xff;
        int r = pixel >> 16 & 0xff;
        int g = pixel >> 8 & 0xff;
        int b = pixel & 0xff;

        int gray = (int) (0.11 * b + 0.59 * g + 0.30 * r);

        *pixel_p = a << 24 | gray << 16 | gray << 8 | gray;
    }


    AndroidBitmap_unlockPixels(env, src);
    return ret;
}