#include <stdio.h>
#include <stdlib.h>
#include "com_jensen_day15_Simple.h"

int compare(int const* num1, int const* num2) {
	return *num1 - *num2;
}

//ԭ���ĺ���ָ�붨�巽ʽ
char (*pFun)(int);

char glFun(int a) {
	return a;
}


//ʹ��typedef���庯��ָ�룬�������ţ���Ϊһ������
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


//��native��ʵ�����򷽷�
JNIEXPORT void JNICALL Java_com_jensen_day15_Simple_sort
(JNIEnv* env, jclass jclz, jintArray jarr) {
	//jintArray��java�е��������ͣ�c����ֱ�Ӳ�������Ҫת����c�е���������
	// jint* ָ��jint���������ͷָ��
	//base: ָ�����������ĵ�һ��Ԫ�ص�ָ�롣
	jint* jintarry = (*env)->GetIntArrayElements(env, jarr, NULL);
	//nitems : �����е�Ԫ��������
	jsize nums = (*env)->GetArrayLength(env, jarr);
	//size : ������ÿ��Ԫ�صĴ�С�����ֽ�Ϊ��λ����
	size_t size = sizeof(jint);
	//  typedef int (__cdecl* _CoreCrtNonSecureSearchSortCompareFunction)(void const*, void const*);
	// ����һ������ָ�룬ָ��һ������
	// ����typedef���ֶ��巽ʽ�����û�ϳ���
	// __cdecl��Լ��д������������
	// ��һ�£�typedef int (*funcName)(void const*, void const*)
	// ԭ���ķ�ʽ��int (*funcName)(void const*, void const*)
	//compar : �ȽϺ�����ָ�룬�ú������ڱȽ�����Ԫ�ء��ȽϺ���Ӧ������һ����������ʾ�ȽϽ����
	//С���㣺��ʾ��һ��Ԫ��С�ڵڶ���Ԫ�ء�
	//�����㣺��ʾ����Ԫ����ȡ�
	//�����㣺��ʾ��һ��Ԫ�ش��ڵڶ���Ԫ�ء�
	qsort(jintarry, nums, size, compare);

	//ͬ�����鵽java
	//��Щ����������jni.hͷ�ļ���
	//0:ͬ�����ͷ�
	//1:JNI_COMMIT��ֻͬ�����ͷ�
	//2:JNI_ABORT��ֻ�ͷŲ�ͬ��
	(*env)->ReleaseIntArrayElements(env, jarr, jintarry, JNI_COMMIT);

}

JNIEXPORT void JNICALL Java_com_jensen_day15_Simple_localRef
(JNIEnv* env, jclass jclz) {
	jclass jclz_string = (*env)->FindClass(env, "java/lang/String");
	jmethodID jmid = (*env)->GetMethodID(env, jclz_string, "<init>", "()V");
	//����String�Ĺ��췽��
	jobject jobj = (*env)->NewObject(env, jclz_string, jmid);

	//���軹��100�д��룬��Ҫ�õ����湹���java����

	//����ʹ�õĶ�����Ҫ�ֶ�����
	(*env)->DeleteLocalRef(env, jobj);

	//ɾ���˾Ͳ�����ʹ���ˣ�c��c++����Ҫ�Լ��ͷ��ڴ棨��̬���ٵĲ���Ҫ����̬malloc����Ҫ��
}

jstring globalStr;

JNIEXPORT void JNICALL Java_com_jensen_day15_Simple_createGlobalRef
(JNIEnv* env, jclass jclz, jstring jstr) {
	//����ȫ������
	globalStr = (*env)->NewGlobalRef(env, jstr);
}

JNIEXPORT jstring JNICALL Java_com_jensen_day15_Simple_getGlobalRef
(JNIEnv* env, jclass jclz) {
	return globalStr;
}

JNIEXPORT void JNICALL Java_com_jensen_day15_Simple_delGlobalRef
(JNIEnv* env, jclass jclz) {
	//�ͷ�ȫ������
	(*env)->DeleteGlobalRef(env, globalStr);
}


//����Simple����name��ֵ
JNIEXPORT void JNICALL Java_com_jensen_day15_Simple_staticLocalCache
(JNIEnv* env, jclass jclz, jstring jstr) {
	//ʹ��static���Σ��������ø÷�����ֻ���ʼ��һ��
	static jfieldID j_fieldID = NULL;
	if (j_fieldID == NULL)
	{
		j_fieldID = (*env)->GetStaticFieldID(env, jclz, "name", "Ljava/lang/String;");
	}
	else {
		//native�е������java����һ��Ƶ���ģ�����Ҫjava�������ſ�ʼ
		printf("j_fieldID not Null\n");
	}
	//�޸ľ�̬������ֵ
	(*env)->SetStaticObjectField(env, jclz, j_fieldID, jstr);
}

//ȫ�־�̬��һ���ŵ���ʼ��������ȥ��


//native����java�쳣
JNIEXPORT void JNICALL Java_com_jensen_day15_Simple_nativeException
(JNIEnv* env, jclass jclz) {
	jfieldID j_fieldID = (*env)->GetStaticFieldID(env, jclz, "name2", "Ljava/lang/String;");
	jthrowable j_throwable = (*env)->ExceptionOccurred(env);//�����java�������쳣��Ϣ
	if (j_throwable)
	{
		(*env)->ExceptionClear(env);//����쳣��������
		printf("can't find name2");
		j_fieldID = (*env)->GetStaticFieldID(env, jclz, "name", "Ljava/lang/String;");
		//�ֶ����쳣
		jclass j_e = (*env)->FindClass(env, "java/lang/NoSuchFieldException");
		(*env)->ThrowNew(env, j_e, "cant' find name2");
		return;//�����쳣Ҫreturn����Ȼ����������

	}
	jstring jstr = (*env)->NewStringUTF(env, "ABC");
	(*env)->SetStaticObjectField(env, jclz, j_fieldID, jstr);


}

//����ָ�� constд����ǰ�棬��ָ�룬���Բ���ָ�룬���ܲ�������
void test2(const char* str) {
	str++;
	*str = "123";

	int a = 100;
	const int* p = &a;

	p++;
	*p = 200;

}

//ָ�볣����const����str�����ܲ���ָ�룬���Բ�������
void test1(char* const str) {
	str++;
	*str = "123";

	int a = 100;
	int* const p = &a;

	p++;
	*p = 200;

}
