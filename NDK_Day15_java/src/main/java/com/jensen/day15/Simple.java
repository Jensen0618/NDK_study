package com.jensen.day15;

public class Simple {
    public static void main(String[] args) {
//        int[] arr = {5, 9, 0, -5, 999, -1};
//        //排序
//        sort(arr);
//
//        for (int i : arr) {
//            System.out.println(i);
//        }
        //本地引用
//        localRef();

        //全局引用
        createGlobalRef("Hello jni");
        System.out.println(getGlobalRef());

        delGlobalRef();

        System.out.println(getGlobalRef());
    }


    static {
        System.load("D:\\Ndk\\NDK_Day15_c\\x64\\Debug\\NDK_Day15_c.dll");
    }

    public static native void sort(int[] arr);

    private static native void localRef();

    private static native void createGlobalRef(String str);

    private static native String getGlobalRef();

    private static native void delGlobalRef();

}
