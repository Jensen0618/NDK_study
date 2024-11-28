#include "com_jensen_ndk12_NdkSimple.h"
#include "com_jensen_ndk12_NdkSimple1.h"

/*
 * Class:     com_jensen_ndk12_NdkSimple
 * Method:    getSignaturePassword
 * Signature: ()Ljava/lang/String;
 */
 //JNIEXPORT 一个关键字，不能少（编译能过，调用报错），标记该方法可以被外部调用
 //jstring 代表java的String类型
 //JNICALL 关键字，可以少
 //JNIEnv 这个是c和java相互调用的桥梁，重中之重
 //jobject java传递下来的对象，就是本项目中的NdkSimple对象
 //jclass java传递下来的class对象，如果是静态方法就是这个，就是本项目中的NdkSimple.class
JNIEXPORT jstring JNICALL Java_com_jensen_ndk12_NdkSimple_getSignaturePassword
(JNIEnv* env, jobject jobject) {
	//typedef const struct JNINativeInterface_* JNIEnv;定义了一个结构体指针别名
	//JNIEnv实际上已经是一个结构体指针了，但是参数这里又加了一个*，相当于env变成了一个二级指针
	//所以(*env)解引用后才是JNIEnv，所以能够使用->调用方法
	return (*env)->NewStringUTF(env, "900215");
}




/*
 * Class:     com_jensen_ndk12_NdkSimple1
 * Method:    changeName
 * Signature: ()V
 * 修改类对象的属性，私有对象也没有问题
 */
JNIEXPORT void JNICALL Java_com_jensen_ndk12_NdkSimple1_changeName
(JNIEnv* env, jobject jobject) {
	//获取jclass
	jclass jclazz = (*env)->GetObjectClass(env, jobject);
	//获取jfieldID
	//name是字段的名字
	//sig是签名信息，用javap获取
	jfieldID jid = (*env)->GetFieldID(env, jclazz, "name", "Ljava/lang/String;");
	//创建属性值
	jstring name = (*env)->NewStringUTF(env, "Linzs");
	//修改对象属性
	(*env)->SetObjectField(env, jobject, jid, name);
}

/*
 * Class:     com_jensen_ndk12_NdkSimple1
 * Method:    changeInt
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_jensen_ndk12_NdkSimple1_changeInt
(JNIEnv* env, jclass jclazz) {
	jfieldID jid = (*env)->GetStaticFieldID(env, jclazz, "age", "I");
	(*env)->SetStaticIntField(env, jclazz, jid, 10086);
	return 10086;
}

/*
 * Class:     com_jensen_ndk12_NdkSimple1
 * Method:    getJavaUUID
 * Signature: ()Ljava/lang/String;
 * 调用java的生成uuid方法
 */
JNIEXPORT jstring JNICALL Java_com_jensen_ndk12_NdkSimple1_getJavaUUID
(JNIEnv* env, jclass jclz) {
	jmethodID j_methodid = (*env)->GetStaticMethodID(env, jclz, "getUUID", "()Ljava/lang/String;");
	jstring j_uuid = (*env)->CallStaticObjectMethod(env, jclz, j_methodid);
	char* uuid = (*env)->GetStringUTFChars(env, j_uuid, NULL);
	printf("UUID=%s", uuid);
	return j_uuid;
}

/*
 * Class:     com_jensen_ndk12_NdkSimple1
 * Method:    createPerson
 * Signature: ()Lcom/jensen/ndk12/Person;
 */
JNIEXPORT jobject JNICALL Java_com_jensen_ndk12_NdkSimple1_createPerson
(JNIEnv* env, jobject jobj) {
	//需要new的java全类名，.需要替换成/
	jclass jclz = (*env)->FindClass(env, "com/jensen/ndk12/Person");
	//类的构造方法名，构造方法固定位"<init>"
	jmethodID jmid = (*env)->GetMethodID(env, jclz, "<init>", "(Ljava/lang/String;Ljava/lang/String;I)V");
	//构造字符串
	jstring id = (*env)->NewStringUTF(env, "350181199002152812");
	jstring name = (*env)->NewStringUTF(env, "Jensen");
	//构造Person对象
	//java的字符串是jstring，c是char*，它们是不同的，这里需要通过env把char*转成jstring再传入方法
	jobject person= (*env)->NewObject(env, jclz, jmid, id, name, 18);

	//调用toString方法
	jmethodID jtostring = (*env)->GetMethodID(env, jclz, "toString", "()Ljava/lang/String;");
	printf("%s\n", (*env)->GetStringUTFChars(env, (*env)->CallObjectMethod(env, person, jtostring), NULL));

	//调用set方法修改
	jmethodID jsetage = (*env)->GetMethodID(env, jclz, "setAge", "(I)V");
	(*env)->CallObjectMethod(env, person, jsetage, 20);
	printf("%s\n", (*env)->GetStringUTFChars(env, (*env)->CallObjectMethod(env, person, jtostring), NULL));

	//直接设置对象的属性值
	jfieldID jage = (*env)->GetFieldID(env, jclz, "age", "I");
	(*env)->SetIntField(env, person, jage, 35);
	printf("%s\n", (*env)->GetStringUTFChars(env, (*env)->CallObjectMethod(env, person, jtostring), NULL));

	return person;
}



//常量指针和指针常量
void main() {
	int a = 100;
	int b = 200;

	//常量指针 指向常量的指针，指向的是常量不能修改，指向可以改
	//常量     指针
	const int* p = &a;
	//const 修饰（*p），所以*p是常量，不能修改
	//*p = 111;//报错，内容不能改
	p = &b;//地址可以改

	//指针常量 指针是个常量，指向的值可以改，指针不能改
	// 指针 常量
	int* const p2 = &a;
	//const修饰p2，p2是常量，不能修改
	*p2 = 222;
	//p2 = &b;

	//测试char*和int的加法
	char* s = (char*)malloc(1024);
	int i = 1;
	printf("s+i=%s\n", s + i);
	//printf("s+i=%d\n", s + i);
	getchar();


}