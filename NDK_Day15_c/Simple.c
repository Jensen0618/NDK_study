#include <stdio.h>
#include <stdlib.h>
#include "com_jensen_day15_Simple.h"

int compare(int const* num1, int const* num2) {
	return *num1 - *num2;
}

//原来的函数指针定义方式
char (*pFun)(int);

char glFun(int a) {
	return a;
}


//使用typedef定义函数指针，更加优雅，成为一种类型
typedef char (*pFun2)(int);

pFun2 p2;

void main() {
	pFun = glFun;
	pFun(2);
	(*pFun)(2);

	p2 = glFun;
	p2(5);
	pFun2 p3 = glFun(5);
}

JNIEXPORT void JNICALL Java_com_jensen_day15_Simple_sort
(JNIEnv* env, jclass jclz, jintArray jarr) {
	//jintArray是java中的数据类型，c不能直接操作，需要转换成c中的数据类型
	// jint* 指向jint类型数组的头指针
	//base: 指向待排序数组的第一个元素的指针。
	jint* jintarry = (*env)->GetIntArrayElements(env, jarr, NULL);
	//nitems : 数组中的元素数量。
	jsize nums = (*env)->GetArrayLength(env, jarr);
	//size : 数组中每个元素的大小（以字节为单位）。
	size_t size = sizeof(jint);
	//  typedef int (__cdecl* _CoreCrtNonSecureSearchSortCompareFunction)(void const*, void const*);
	// 这是一个函数指针，指向一个函数
	// 用了typedef这种定义方式，差点没认出来
	// __cdecl是约定写法，不用理他
	// 简化一下：typedef int (*funcName)(void const*, void const*)
	// 原来的方式：int (*funcName)(void const*, void const*)
	//compar : 比较函数的指针，该函数用于比较两个元素。比较函数应当返回一个整数，表示比较结果：
	//小于零：表示第一个元素小于第二个元素。
	//等于零：表示两个元素相等。
	//大于零：表示第一个元素大于第二个元素。
	qsort(jintarry, nums, size, compare);

	//同步数组到java
	//这些常量定义在jni.h头文件中
	//0:同步并释放
	//1:JNI_COMMIT，只同步不释放
	//2:JNI_ABORT，只释放不同步
	(*env)->ReleaseIntArrayElements(env, jarr, jintarry, JNI_COMMIT);

}

JNIEXPORT void JNICALL Java_com_jensen_day15_Simple_localRef
(JNIEnv* env, jclass jclz) {
	jclass jclz_string = (*env)->FindClass(env, "java/lang/String");
	jmethodID jmid = (*env)->GetMethodID(env, jclz_string, "<init>", "()V");
	jobject jobj=(*env)->NewObject(env, jclz_string,jmid);

	(*env)->DeleteLocalRef(env, jobj);
}

jstring globalStr;

JNIEXPORT void JNICALL Java_com_jensen_day15_Simple_createGlobalRef
(JNIEnv* env, jclass jclz, jstring jstr) {
	//创建全局引用
	globalStr = (*env)->NewGlobalRef(env, jstr);
}

JNIEXPORT jstring JNICALL Java_com_jensen_day15_Simple_getGlobalRef
(JNIEnv* env, jclass jclz){
	return globalStr;
}

JNIEXPORT void JNICALL Java_com_jensen_day15_Simple_delGlobalRef
(JNIEnv* env, jclass jclz) {
	//释放全局引用
	(*env)->DeleteGlobalRef(env, globalStr);
}
