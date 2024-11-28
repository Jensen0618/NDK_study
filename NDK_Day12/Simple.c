#include "com_jensen_ndk12_NdkSimple.h"
#include "com_jensen_ndk12_NdkSimple1.h"

/*
 * Class:     com_jensen_ndk12_NdkSimple
 * Method:    getSignaturePassword
 * Signature: ()Ljava/lang/String;
 */
 //JNIEXPORT һ���ؼ��֣������٣������ܹ������ñ�������Ǹ÷������Ա��ⲿ����
 //jstring ����java��String����
 //JNICALL �ؼ��֣�������
 //JNIEnv �����c��java�໥���õ�����������֮��
 //jobject java���������Ķ��󣬾��Ǳ���Ŀ�е�NdkSimple����
 //jclass java����������class��������Ǿ�̬����������������Ǳ���Ŀ�е�NdkSimple.class
JNIEXPORT jstring JNICALL Java_com_jensen_ndk12_NdkSimple_getSignaturePassword
(JNIEnv* env, jobject jobject) {
	//typedef const struct JNINativeInterface_* JNIEnv;������һ���ṹ��ָ�����
	//JNIEnvʵ�����Ѿ���һ���ṹ��ָ���ˣ����ǲ��������ּ���һ��*���൱��env�����һ������ָ��
	//����(*env)�����ú����JNIEnv�������ܹ�ʹ��->���÷���
	return (*env)->NewStringUTF(env, "900215");
}




/*
 * Class:     com_jensen_ndk12_NdkSimple1
 * Method:    changeName
 * Signature: ()V
 * �޸����������ԣ�˽�ж���Ҳû������
 */
JNIEXPORT void JNICALL Java_com_jensen_ndk12_NdkSimple1_changeName
(JNIEnv* env, jobject jobject) {
	//��ȡjclass
	jclass jclazz = (*env)->GetObjectClass(env, jobject);
	//��ȡjfieldID
	//name���ֶε�����
	//sig��ǩ����Ϣ����javap��ȡ
	jfieldID jid = (*env)->GetFieldID(env, jclazz, "name", "Ljava/lang/String;");
	//��������ֵ
	jstring name = (*env)->NewStringUTF(env, "Linzs");
	//�޸Ķ�������
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
 * ����java������uuid����
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
	//��Ҫnew��javaȫ������.��Ҫ�滻��/
	jclass jclz = (*env)->FindClass(env, "com/jensen/ndk12/Person");
	//��Ĺ��췽���������췽���̶�λ"<init>"
	jmethodID jmid = (*env)->GetMethodID(env, jclz, "<init>", "(Ljava/lang/String;Ljava/lang/String;I)V");
	//�����ַ���
	jstring id = (*env)->NewStringUTF(env, "350181199002152812");
	jstring name = (*env)->NewStringUTF(env, "Jensen");
	//����Person����
	//java���ַ�����jstring��c��char*�������ǲ�ͬ�ģ�������Ҫͨ��env��char*ת��jstring�ٴ��뷽��
	jobject person= (*env)->NewObject(env, jclz, jmid, id, name, 18);

	//����toString����
	jmethodID jtostring = (*env)->GetMethodID(env, jclz, "toString", "()Ljava/lang/String;");
	printf("%s\n", (*env)->GetStringUTFChars(env, (*env)->CallObjectMethod(env, person, jtostring), NULL));

	//����set�����޸�
	jmethodID jsetage = (*env)->GetMethodID(env, jclz, "setAge", "(I)V");
	(*env)->CallObjectMethod(env, person, jsetage, 20);
	printf("%s\n", (*env)->GetStringUTFChars(env, (*env)->CallObjectMethod(env, person, jtostring), NULL));

	//ֱ�����ö��������ֵ
	jfieldID jage = (*env)->GetFieldID(env, jclz, "age", "I");
	(*env)->SetIntField(env, person, jage, 35);
	printf("%s\n", (*env)->GetStringUTFChars(env, (*env)->CallObjectMethod(env, person, jtostring), NULL));

	return person;
}



//����ָ���ָ�볣��
void main() {
	int a = 100;
	int b = 200;

	//����ָ�� ָ������ָ�룬ָ����ǳ��������޸ģ�ָ����Ը�
	//����     ָ��
	const int* p = &a;
	//const ���Σ�*p��������*p�ǳ����������޸�
	//*p = 111;//�������ݲ��ܸ�
	p = &b;//��ַ���Ը�

	//ָ�볣�� ָ���Ǹ�������ָ���ֵ���Ըģ�ָ�벻�ܸ�
	// ָ�� ����
	int* const p2 = &a;
	//const����p2��p2�ǳ����������޸�
	*p2 = 222;
	//p2 = &b;

	//����char*��int�ļӷ�
	char* s = (char*)malloc(1024);
	int i = 1;
	printf("s+i=%s\n", s + i);
	//printf("s+i=%d\n", s + i);
	getchar();


}