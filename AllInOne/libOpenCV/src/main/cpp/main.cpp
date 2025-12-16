#include <jni.h>
#include "BitmapMatUtils.h"

extern "C"
JNIEXPORT jint JNICALL
Java_com_jensen_libopencv_OpenCVUtil_mirrorNative(JNIEnv *env, jclass clazz, jobject bitmap) {
    Mat src;
    BitmapMatUtils::bitmap2mat(env, bitmap, src);
    Mat dst(src.size(), src.type());

    int halfCols = src.cols >> 1;
    int qtrCols = halfCols >> 1;

    for (int i = 0; i < dst.rows; i++) {//行
        //左边半张
        for (int j = 0; j < halfCols; j++) {
            //y坐标无需变化
            //mat.at<uchar>(row, col) ，这个不是x，y坐标，而是行，列
            //typedef Vec<uchar, 4> Vec4b;
            //这里还需要判断是8888还是565
            dst.at<Vec4b>(i, j) = src.at<Vec4b>(i, qtrCols + j);
        }
        //右边半张
        for (int j = halfCols; j < dst.cols; j++) {
            dst.at<Vec4b>(i, j) = src.at<Vec4b>(i, src.cols - j + qtrCols);
        }
    }
    BitmapMatUtils::mat2bitmap(env, dst, bitmap);

    return 0;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_jensen_libopencv_OpenCVUtil_init__(JNIEnv *env, jobject thiz) {

}
extern "C"
JNIEXPORT void JNICALL
Java_com_jensen_libopencv_OpenCVUtil_init__I(JNIEnv *env, jobject thiz, jint age) {
    // TODO: implement init()
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_jensen_libopencv_OpenCVUtil_init__Ljava_lang_String_2(JNIEnv *env, jobject thiz,
                                                               jstring name) {
    // TODO: implement init()
}
