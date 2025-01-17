#include <jni.h>
#include <string>
#include <android/log.h>
#include "BitmapMatUtils.h"
#include "cardocr.h"

#define TAG "Jensen"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)    // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__)        // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)        // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__)    // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__)    // 定义LOGF类型

using namespace std;


extern "C" JNIEXPORT jstring JNICALL
Java_com_ndk_day31_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_ndk_day31_BankCardOcr_cardOcr(JNIEnv *env, jclass clazz, jobject bitmap) {
//    1. bitmap->mat
    Mat mat;//原始图片Mat
    BitmapMatUtils::bitmap2mat(env, bitmap, mat);
    LOGD("宽=%d,高=%d,颜色类型=%d", mat.cols, mat.rows, mat.type());

//    2. 轮廓增强
    Rect rect;
    co1::find_card_area(mat, rect);
    LOGD("裁剪区域：w=%d,h=%d",rect.width,rect.height);
//对过滤到的银行卡区域进行裁剪
    Mat card_mat(mat, rect);//裁剪后的Mat
    imwrite("/storage/emulated/0/card_mat.jpg", card_mat);

    Rect card_number_rect;
    co1::find_card_number_area(card_mat, card_number_rect);

    Mat card_number_mat(card_mat,card_number_rect);
    imwrite("/storage/emulated/0/card_number_mat.jpg", card_number_mat);

    vector<Mat> numbers;
    co1::find_card_numbers(card_number_mat, numbers);


//    BitmapMatUtils::mat2bitmap(env, bitmap, card_number_mat);这样不行，bitmap和mat的宽高不符

    return env->NewStringUTF("123456");
}