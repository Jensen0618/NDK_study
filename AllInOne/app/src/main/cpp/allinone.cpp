#include <jni.h>
#include <android/bitmap.h>
#include <android/log.h>

#define TAG "BitmapUtil"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)    // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__)        // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)        // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__)    // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__)    // 定义LOGF类型
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
    int ret = 0;
    AndroidBitmapInfo info;//用来接收bitmap信息，常用的有宽、高、格式
    //第三个参数：AndroidBitmapInfo* info 是个指针，需要使用&取地址
    ret = AndroidBitmap_getInfo(env, src, &info);
    if (ret != ANDROID_BITMAP_RESULT_SUCCESS) {
        return ret;
    }
    LOGD("format:%d", info.format);//rgb565 format:4；argb888 format:1
    //void可以接收任意类型的指针
    void *pixels;
    //第三个参数：void** addrPtr 是void类型的双重指针，pixels是void*类型，需要再次取地址
    ret = AndroidBitmap_lockPixels(env, src, &pixels);

    //像素数组的长度=宽*高，下面针对每个像素进行颜色变换
    int length = info.width * info.height;
    if (ANDROID_BITMAP_FORMAT_RGBA_8888 == info.format) {
        for (int i = 0; i < length; ++i) {
            //将void*指针转换为4字节的int*指针，每次遍历时+i，指针指向当前像素
            uint32_t *pixel_p = reinterpret_cast<uint32_t *>(pixels) + i;
            //*在右侧，取值，取出当前像素
            uint32_t pixel = *pixel_p;
            int a = pixel >> 24 & 0xff;
            int r = pixel >> 16 & 0xff;
            int g = pixel >> 8 & 0xff;
            int b = pixel & 0xff;

            int gray = (int) (0.11 * b + 0.59 * g + 0.30 * r);
            //左值
            *pixel_p = a << 24 | gray << 16 | gray << 8 | gray;

            //将ARGB_8888转为RGB_565
//            int a = pixel >> 24 & 0xff;
//            int r = (pixel >> 16 & 0xff) >> 3;
//            int g = (pixel >> 8 & 0xff) >> 2;
//            int b = (pixel & 0xff) >> 3;
//            *pixel_p = a << 24 | r << 3 << 16 | g << 2 << 8 | b << 3;
        }
    } else if (ANDROID_BITMAP_FORMAT_RGB_565 == info.format) {
        for (int i = 0; i < length; ++i) {
            //将void*指针转换为4字节的int*指针，每次遍历时+i，指针指向当前像素
            uint16_t *pixel_p = reinterpret_cast<uint16_t *>(pixels) + i;
            //*在右侧，取值，取出当前像素
            uint16_t pixel = *pixel_p;

            //加上括号保证运算顺序！
            int r = (pixel >> 11 & 0x1f) << 3;
            int g = (pixel >> 5 & 0x3f) << 2;
            int b = (pixel & 0x1f) << 3;

            //这个公式只能用于32位的计算！16未的565需补成888
            int gray = (int) (0.11 * b + 0.59 * g + 0.30 * r);
            //要把补位的还回来
            *pixel_p = gray >> 3 << 11 | gray >> 2 << 5 | gray >> 3;
        }
    }

    //和前面lockPixels配套的unlockPixels
    AndroidBitmap_unlockPixels(env, src);
    return ret;
}