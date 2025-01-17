//
// Created by linzs on 2025-01-15.
//

#include "BitmapMatUtils.h"


int BitmapMatUtils::bitmap2mat(JNIEnv *env, jobject bitmap, Mat &mat) {
//1. 锁定画布
//    void **pixels;//一个二级指针，参数这么要求的;下面Mat的构造函数需要一级指针，所以这里改一下
    void *pixels;
    //得到bitmap地址
    AndroidBitmap_lockPixels(env, bitmap, &pixels);
//    构建mat对象，还要判断什么颜色通道
    AndroidBitmapInfo bitmapInfo;
    //&bitmapInfo 这里是取地址，不是引用的意思;&只有在定义的时候才是引用的意思
    AndroidBitmap_getInfo(env, bitmap, &bitmapInfo);

//     Mat(int rows, int cols, int type);行（高），列（宽），颜色类型
//返回三通道
//还得是改成四通道的，find_card_area的时候报错了
    Mat createMat(bitmapInfo.height, bitmapInfo.width, CV_8UC4);
//    CV_8UC4->argb
//CV_8UC2->rgb
//CV_8UC1->灰度

    if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {//mat 里的四颜色通道
//        Mat(int rows, int cols, int type, void* data, size_t step=AUTO_STEP);
        Mat temp(bitmapInfo.height, bitmapInfo.width, CV_8UC4, pixels);
//        cvtColor(temp, createMat, COLOR_BGRA2BGR565);
        temp.copyTo(createMat);
    } else if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGB_565) {
        Mat temp(bitmapInfo.height, bitmapInfo.width, CV_8UC2, pixels);
//        temp.copyTo(createMat);
        cvtColor(temp, createMat, COLOR_BGR5652RGBA);
    }
    createMat.copyTo(mat);
    //2. 解锁画布
    AndroidBitmap_unlockPixels(env, bitmap);

    return 0;
}


int BitmapMatUtils::mat2bitmap(JNIEnv *env, jobject &bitmap, Mat mat) {
//1. 锁定画布
//    void **pixels;//一个二级指针，参数这么要求的;下面Mat的构造函数需要一级指针，所以这里改一下
    void *pixels;
    //得到bitmap地址
    AndroidBitmap_lockPixels(env, bitmap, &pixels);
//    构建mat对象，还要判断什么颜色通道
    AndroidBitmapInfo bitmapInfo;
    //&bitmapInfo 这里是取地址，不是引用的意思;&只有在定义的时候才是引用的意思
    AndroidBitmap_getInfo(env, bitmap, &bitmapInfo);

//     Mat(int rows, int cols, int type);行（高），列（宽），颜色类型
//返回三通道
//还得是改成四通道的，find_card_area的时候报错了
//    Mat createMat(bitmapInfo.height, bitmapInfo.width, CV_8UC4);
//    CV_8UC4->argb
//CV_8UC2->rgb
//CV_8UC1->灰度

    if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {//mat 里的四颜色通道
//        Mat(int rows, int cols, int type, void* data, size_t step=AUTO_STEP);
        Mat temp(bitmapInfo.height, bitmapInfo.width, CV_8UC4, pixels);
        if (mat.type() == CV_8UC4) {
            mat.copyTo(temp);
        } else if (mat.type() == CV_8UC2) {
            cvtColor(mat, temp, COLOR_BGR5652BGRA);
        }
    } else if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGB_565) {
        Mat temp(bitmapInfo.height, bitmapInfo.width, CV_8UC2, pixels);
        if (mat.type() == CV_8UC4) {
            cvtColor(mat, temp, COLOR_BGRA2BGR565);
        } else if (mat.type() == CV_8UC2) {
            mat.copyTo(temp);
        }
    }
    //2. 解锁画布
    AndroidBitmap_unlockPixels(env, bitmap);

    return 0;

}