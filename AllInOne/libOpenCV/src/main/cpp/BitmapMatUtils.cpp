#include "BitmapMatUtils.h"
#include <android/log.h>

#define LOG_TAG "BitmapMatUtils"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

int BitmapMatUtils::bitmap2mat(JNIEnv *env, jobject bitmap, Mat &mat) {
    // 1. Get bitmap info
    AndroidBitmapInfo bitmapInfo;
    if (AndroidBitmap_getInfo(env, bitmap, &bitmapInfo) < 0) {
        LOGE("AndroidBitmap_getInfo() failed !");
        return -1;
    }

    // 2. Lock pixels
    void *pixels = nullptr;
    if (AndroidBitmap_lockPixels(env, bitmap, &pixels) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed !");
        return -2;
    }

    if (pixels == nullptr) {
        LOGE("AndroidBitmap_lockPixels() failed ! pixels is null");
        AndroidBitmap_unlockPixels(env, bitmap);
        return -3;
    }

    // 3. Create Mat object based on bitmap format
    LOGE("bitmap format: %d", bitmapInfo.format);
    if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        // RGBA_8888 -> CV_8UC4
        Mat temp(bitmapInfo.height, bitmapInfo.width, CV_8UC4, pixels);
        temp.copyTo(mat);
    } else if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGB_565) {
        // RGB_565 -> CV_8UC2
        Mat temp(bitmapInfo.height, bitmapInfo.width, CV_8UC2, pixels);
        cvtColor(temp, mat, COLOR_BGR5652RGBA); // Convert to a common format like RGBA
    } else if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_A_8) {
        // A_8 -> CV_8UC1 (Grayscale)
        Mat temp(bitmapInfo.height, bitmapInfo.width, CV_8UC1, pixels);
        temp.copyTo(mat);
    } else {
        LOGE("Unsupported bitmap format: %d", bitmapInfo.format);
        AndroidBitmap_unlockPixels(env, bitmap);
        return -4;
    }

    // 4. Unlock pixels
    AndroidBitmap_unlockPixels(env, bitmap);

    return 0;
}


int BitmapMatUtils::mat2bitmap(JNIEnv *env, Mat mat, jobject &bitmap) {
    // 1. Get bitmap info
    AndroidBitmapInfo bitmapInfo;
    if (AndroidBitmap_getInfo(env, bitmap, &bitmapInfo) < 0) {
        LOGE("AndroidBitmap_getInfo() failed !");
        return -1;
    }

    // Check if Mat dimensions match bitmap dimensions
    if (mat.cols != (int) bitmapInfo.width || mat.rows != (int) bitmapInfo.height) {
        LOGE("Mat dimensions do not match bitmap dimensions.");
        return -2;
    }

    // 2. Lock pixels
    void *pixels = nullptr;
    if (AndroidBitmap_lockPixels(env, bitmap, &pixels) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed !");
        return -3;
    }

    if (pixels == nullptr) {
        LOGE("AndroidBitmap_lockPixels() failed ! pixels is null");
        AndroidBitmap_unlockPixels(env, bitmap);
        return -4;
    }

    // 3. Copy/Convert Mat data to bitmap pixels
    if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        Mat temp(bitmapInfo.height, bitmapInfo.width, CV_8UC4, pixels);
        switch (mat.type()) {
            case CV_8UC1: // Grayscale
                cvtColor(mat, temp, COLOR_GRAY2RGBA);
                break;
            case CV_8UC3: // BGR
                cvtColor(mat, temp, COLOR_BGR2RGBA);
                break;
            case CV_8UC4: // BGRA or RGBA
                // Assuming input is BGRA, which is common in OpenCV
//                cvtColor(mat, temp, COLOR_BGRA2RGBA);
                //这里转RGBA是错误的，会出现缺色的情况，不由得怀疑上面两个转换是不是一样的问题
                mat.copyTo(temp);
                break;
            default:
                LOGE("Unsupported Mat type for RGBA_8888 bitmap: %d", mat.type());
                AndroidBitmap_unlockPixels(env, bitmap);
                return -5;
        }
    } else if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGB_565) {
        Mat temp(bitmapInfo.height, bitmapInfo.width, CV_8UC2, pixels);
        switch (mat.type()) {
            case CV_8UC1:
                cvtColor(mat, temp, COLOR_GRAY2BGR565);
                break;
            case CV_8UC3:
                cvtColor(mat, temp, COLOR_BGR2BGR565);
                break;
            case CV_8UC4:
                cvtColor(mat, temp, COLOR_RGBA2BGR565);
                break;
            default:
                LOGE("Unsupported Mat type for RGB_565 bitmap: %d", mat.type());
                AndroidBitmap_unlockPixels(env, bitmap);
                return -5;
        }
    } else if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_A_8) {
        Mat temp(bitmapInfo.height, bitmapInfo.width, CV_8UC1, pixels);
        switch (mat.type()) {
            case CV_8UC1:
                mat.copyTo(temp);
                break;
            case CV_8UC3:
                cvtColor(mat, temp, COLOR_BGR2GRAY);
                break;
            case CV_8UC4:
                cvtColor(mat, temp, COLOR_RGBA2GRAY);
                break;
            default:
                LOGE("Unsupported Mat type for A_8 bitmap: %d", mat.type());
                AndroidBitmap_unlockPixels(env, bitmap);
                return -5;
        }
    } else {
        LOGE("Unsupported bitmap format: %d", bitmapInfo.format);
        AndroidBitmap_unlockPixels(env, bitmap);
        return -6;
    }

    // 4. Unlock pixels
    AndroidBitmap_unlockPixels(env, bitmap);

    return 0;
}


extern "C"
JNIEXPORT jlong JNICALL
Java_com_jensen_libopencv_Mat_nativeMatCreate(JNIEnv *env, jobject thiz) {
    Mat *mat = new Mat();
    return reinterpret_cast<jlong>(mat);
}
extern "C"
JNIEXPORT jlong JNICALL
Java_com_jensen_libopencv_Mat_nativeMatCreateIII__III(JNIEnv *env, jobject thiz, jint rows,
                                                      jint cols,
                                                      jint type) {
    Mat *mat = new Mat(rows, cols, type);
    return reinterpret_cast<jlong>(mat);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jensen_libopencv_Mat_nativeMatRelease(JNIEnv *env, jobject thiz, jlong native_ptr) {
    Mat *mat = reinterpret_cast<Mat *>(native_ptr);
    delete (mat);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jensen_libopencv_OpenCVUtil_bitmap2mat(JNIEnv *env, jclass clazz, jobject bitmap,
                                                jlong matPtr) {
    Mat *mat = reinterpret_cast<Mat *>(matPtr);
    BitmapMatUtils::bitmap2mat(env, bitmap, *mat);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_jensen_libopencv_OpenCVUtil_nativeFilter2D(JNIEnv *env, jclass clazz, jlong src, jlong dst,
                                                    jlong kennel) {
    Mat *matSrc = reinterpret_cast<Mat *>(src);
    Mat *matDst = reinterpret_cast<Mat *>(dst);
    Mat *matKennel = reinterpret_cast<Mat *>(kennel);


    filter2D(*matSrc, *matDst, matSrc->depth(), *matKennel);


}
extern "C"
JNIEXPORT void JNICALL
Java_com_jensen_libopencv_Mat_nativePut(JNIEnv *env, jobject thiz, jlong native_ptr, jint row,
                                        jint col, jfloat value) {
    Mat *mat = reinterpret_cast<Mat *>(native_ptr);
    mat->at<float>(row, col) = value;

}
extern "C"
JNIEXPORT void JNICALL
Java_com_jensen_libopencv_OpenCVUtil_mat2bitmap(JNIEnv *env, jclass clazz, jlong mat_ptr,
                                                jobject bitmap) {
    Mat *mat = reinterpret_cast<Mat *>(mat_ptr);
    BitmapMatUtils::mat2bitmap(env, *mat, bitmap);

}