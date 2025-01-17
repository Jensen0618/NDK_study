//
// Created by linzs on 2025-01-15.
//

#ifndef NDK_DAY31_BITMAPMATUTILS_H
#define NDK_DAY31_BITMAPMATUTILS_H

#include <jni.h>
#include <android/bitmap.h>
#include "opencv2/opencv.hpp"

using namespace cv;

class BitmapMatUtils {
public:

    //Java中是把想要的结果返回
    //C/C++中是把结果通过参数传毒，返回值返回是否成功
    int static mat2bitmap(JNIEnv *env, jobject &bitmap, Mat mat);

    int static bitmap2mat(JNIEnv *env, jobject bitmap, Mat &mat);
};


#endif //NDK_DAY31_BITMAPMATUTILS_H
