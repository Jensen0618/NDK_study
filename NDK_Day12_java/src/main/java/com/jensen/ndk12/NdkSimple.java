package com.jensen.ndk12;

public class NdkSimple {
    public static void main(String[] args) {
        NdkSimple ndkSimple = new NdkSimple();

        String signaturePassword = ndkSimple.getSignaturePassword();

        System.out.println("密钥=" + signaturePassword);
    }

    //定义好本地的native方法
    public native String getSignaturePassword();

    static {
//        加载动态库
//        System.load();//加载一个具体路径下的.so库
//        System.loadLibrary();//加载apk中的libs目录下的.so库
        System.load("D:\\Workspace\\C++\\NDK_Day12\\x64\\Debug\\NDK_Day12.dll");
    }
}
