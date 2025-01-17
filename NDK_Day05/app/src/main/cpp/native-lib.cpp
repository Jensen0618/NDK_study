#include <jni.h>
#include <string>
#include "opencv2/opencv.hpp"
#include <android/bitmap.h>


using namespace cv;


void bitmap2Mat(JNIEnv *pEnv, Mat &mat, jobject &bitmap);


void mat2Bitmap(JNIEnv *env, Mat &mat, jobject &bitmap);

void bitmap2Mat(JNIEnv *pEnv, Mat &mat, jobject &bitmap) {
//Mat里面有个type：CV_8UC4 对应Bitmap中的ARGB_8888，CV_8UC2对应Bitmap中的RGB_565
//获取bitmap信息
    AndroidBitmapInfo info;
    void *pixels;
    AndroidBitmap_getInfo(pEnv, bitmap, &info);

    //锁定Bitmap画布
    AndroidBitmap_lockPixels(pEnv, bitmap, &pixels);
    //指定Mat的宽高和type BGRA
    mat.create(info.height, info.width, CV_8UC4);

    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        //对应CV_8UC4
        Mat temp(info.height, info.width, CV_8UC4, pixels);
        temp.copyTo(mat);
    } else if (info.format == ANDROID_BITMAP_FORMAT_RGB_565) {
        //对应CV_8UC2
        Mat temp(info.height, info.width, CV_8UC2, pixels);
        //Mat是CV_UC4，CV_8UC2需要转成CV_8UC4
        cvtColor(temp, mat, COLOR_BGR5652BGRA);
    }
    //解锁画布
    AndroidBitmap_unlockPixels(pEnv, bitmap);

}

void mat2Bitmap(JNIEnv *env, Mat &mat, jobject &bitmap) {
    //Mat里面有个type：CV_8UC4 对应Bitmap中的ARGB_8888，CV_8UC2对应Bitmap中的RGB_565
    //获取bitmap信息
    AndroidBitmapInfo info;
    void *pixels;
    AndroidBitmap_getInfo(env, bitmap, &info);

    //锁定Bitmap画布
    AndroidBitmap_lockPixels(env, bitmap, &pixels);
    //指定Mat的宽高和type BGRA

    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        //对应CV_8UC4
        Mat temp(info.height, info.width, CV_8UC4, pixels);
        if (mat.type() == CV_8UC4) {
            mat.copyTo(temp);
        } else if (mat.type() == CV_8UC2) {
            cvtColor(mat, temp, COLOR_BGR5652BGRA);
        } else if (mat.type() == CV_8UC1) {//灰度
            cvtColor(mat, temp, COLOR_GRAY2BGRA);
        }
    } else if (info.format == ANDROID_BITMAP_FORMAT_RGB_565) {
        //对应CV_8UC2
        Mat temp(info.height, info.width, CV_8UC2, pixels);
        if (mat.type() == CV_8UC4) {
            cvtColor(mat, temp, COLOR_BGRA2BGR565);
        } else if (mat.type() == CV_8UC2) {
            mat.copyTo(temp);
        } else if (mat.type() == CV_8UC1) {//灰度
            cvtColor(mat, temp, COLOR_GRAY2BGR565);
        }
    }
    //解锁画布
    AndroidBitmap_unlockPixels(env, bitmap);

}



extern "C"
JNIEXPORT jint JNICALL
Java_com_ndk_day05_FaceUtil_dectFace(JNIEnv *env, jobject thiz, jobject bitmap) {
    //检测人脸，opencv有一个非常关键的类是Mat
    //opencv是C喝C++写的，只会处理Mat，android里是bitmap
    //1. Bitmap转成opencv能够操作的C++对象Mat，Mat是一个矩阵
    Mat mat;
    bitmap2Mat(env, mat, bitmap);

    //处理灰度 opencv处理灰度图，提高效率，一般所有操作都对对其进行灰度处理
    Mat gray_mat;
    cvtColor(mat, gray_mat, COLOR_BGRA2GRAY);

//    再次处理 直方均衡补偿
    Mat equalize_mat;
    equalizeHist(gray_mat, equalize_mat);

//    识别人脸



    //把mat放回bitmap
    mat2Bitmap(env, equalize_mat, bitmap);

    //保存人脸信息
    return 0;
}

