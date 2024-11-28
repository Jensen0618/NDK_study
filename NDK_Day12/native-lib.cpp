
#include <string>
#include "com_example_ndk_day14_Parcel.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_ndk_1day14_MainActivity_stringFromJNI(
	JNIEnv * env,
	jobject /* this */) {
	std::string hello = "Hello from C++";
	return env->NewStringUTF(hello.c_str());
}

//结构体和对象 Parcel.cpp
class Parcel {
	char* mData;//这个东西是指针啊卧槽，太久没搞都忘记了艹
	int mDataPos;//指针偏移量

public:

	Parcel() {
		mData = (char*)malloc(1024);
		mDataPos = 0;
	}

	void writeInt(jint value) {
		//这里就是指针偏移
		*reinterpret_cast<int*>(mData + mDataPos) = value;
		mDataPos += sizeof(int);
	}

	void setDataPosition(jint pos) {
		mDataPos = pos;
	}


};

JNIEXPORT jlong JNICALL Java_com_example_ndk_day14_Parcel_nativeCreate
(JNIEnv* env, jobject jobj) {
	Parcel* parcel = new Parcel();
	return (jlong)parcel;
}

JNIEXPORT void JNICALL Java_com_example_ndk_day14_Parcel_nativeWriteInt
(JNIEnv*, jobject, jlong nativePtr, jint value) {
	Parcel* parcel = (Parcel*)nativePtr;
	parcel->writeInt(value);
}

JNIEXPORT jint JNICALL Java_com_example_ndk_day14_Parcel_nativeReadInt
(JNIEnv*, jobject, jlong pos) {

}

JNIEXPORT void JNICALL Java_com_example_ndk_day14_Parcel_nativeSetDataPosition
(JNIEnv*, jobject, jlong nativePtr, jint pos) {
	Parcel* parcel = (Parcel*)nativePtr;
	parcel->setDataPosition(pos);
}