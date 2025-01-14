#include <jni.h>
#include <string>
#include "md5.h"

using namespace std;

//额外附加的字符串
static char *EXTRA_SIGNATURE = "DARREN";

//校验签名
static int is_verify=0;
static char* PACKAGE_NAME="com.ndk.day01";


extern "C"
JNIEXPORT jstring JNICALL
Java_com_ndk_day01_SignatureUtils_signatureParams(JNIEnv *env, jclass clazz, jstring params) {

    if (is_verify == 0) {
        return env->NewStringUTF("签名错误");
    }

    const char *_params = env->GetStringUTFChars(params, 0);

    //MD5签名规则，加点料
    //1. 字符串前面加点料
    string signature_str(_params);
    signature_str.insert(0, EXTRA_SIGNATURE);
    //2. 去掉后面两位
    signature_str = signature_str.substr(0, signature_str.length() - 2);
    //3. md5加密
    MD5 MD5(signature_str);
//    const byte *digest = MD5.getDigest();
    const string &basicString = MD5.toStr();
    //释放字符串资源
    env->ReleaseStringUTFChars(params, _params);
    return env->NewStringUTF(basicString.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_ndk_day01_SignatureUtils_signatureVerify(JNIEnv *env, jclass clazz, jobject context) {


}