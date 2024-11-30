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


//在native中实现排序方法
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
	//调用String的构造方法
	jobject jobj = (*env)->NewObject(env, jclz_string, jmid);

	//假设还有100行代码，需要用到上面构造的java对象

	//不再使用的对象需要手动回收
	(*env)->DeleteLocalRef(env, jobj);

	//删除了就不能再使用了，c和c++都需要自己释放内存（静态开辟的不需要，动态malloc的需要）
}

jstring globalStr;

JNIEXPORT void JNICALL Java_com_jensen_day15_Simple_createGlobalRef
(JNIEnv* env, jclass jclz, jstring jstr) {
	//创建全局引用
	globalStr = (*env)->NewGlobalRef(env, jstr);
}

JNIEXPORT jstring JNICALL Java_com_jensen_day15_Simple_getGlobalRef
(JNIEnv* env, jclass jclz) {
	return globalStr;
}

JNIEXPORT void JNICALL Java_com_jensen_day15_Simple_delGlobalRef
(JNIEnv* env, jclass jclz) {
	//释放全局引用
	(*env)->DeleteGlobalRef(env, globalStr);
}


//设置Simple类中name的值
JNIEXPORT void JNICALL Java_com_jensen_day15_Simple_staticLocalCache
(JNIEnv* env, jclass jclz, jstring jstr) {
	//使用static修饰，反复调用该方法，只会初始化一次
	static jfieldID j_fieldID = NULL;
	if (j_fieldID == NULL)
	{
		j_fieldID = (*env)->GetStaticFieldID(env, jclz, "name", "Ljava/lang/String;");
	}
	else {
		//native中的输出和java不是一个频道的，总是要java都输出完才开始
		printf("j_fieldID not Null\n");
	}
	//修改静态变量的值
	(*env)->SetStaticObjectField(env, jclz, j_fieldID, jstr);
}

//全局静态，一般会放到初始化函数里去做


//native处理java异常
JNIEXPORT void JNICALL Java_com_jensen_day15_Simple_nativeException
(JNIEnv* env, jclass jclz) {
	jfieldID j_fieldID = (*env)->GetStaticFieldID(env, jclz, "name2", "Ljava/lang/String;");
	jthrowable j_throwable = (*env)->ExceptionOccurred(env);//有这句java就能有异常信息
	if (j_throwable)
	{
		(*env)->ExceptionClear(env);//清除异常，不抛了
		printf("can't find name2");
		j_fieldID = (*env)->GetStaticFieldID(env, jclz, "name", "Ljava/lang/String;");
		//手动抛异常
		jclass j_e = (*env)->FindClass(env, "java/lang/NoSuchFieldException");
		(*env)->ThrowNew(env, j_e, "cant' find name2");
		return;//抛完异常要return，不然又往下走了

	}
	jstring jstr = (*env)->NewStringUTF(env, "ABC");
	(*env)->SetStaticObjectField(env, jclz, j_fieldID, jstr);


}

//常量指针 const写在最前面，是指针，可以操作指针，不能操作变量
void test2(const char* str) {
	str++;
	*str = "123";

	int a = 100;
	const int* p = &a;

	p++;
	*p = 200;

}

//指针常量，const修饰str，不能操作指针，可以操作变量
void test1(char* const str) {
	str++;
	*str = "123";

	int a = 100;
	int* const p = &a;

	p++;
	*p = 200;

}
