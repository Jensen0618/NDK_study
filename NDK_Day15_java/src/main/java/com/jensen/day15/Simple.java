package com.jensen.day15;

public class Simple {
    public static String name;

    public static void main(String[] args) {
//        //1. 数组排序
//        int[] arr = {5, 9, 0, -5, 999, -1};
//        sort(arr);
//
//        for (int i : arr) {
//            System.out.println(i);
//        }
//        2. 局部引用和全局引用
        //本地引用
        localRef();

        //全局引用
        createGlobalRef("Hello jni");
        System.out.println(getGlobalRef());

        delGlobalRef();

//        System.out.println(getGlobalRef());
//        3. static 缓存策略
        staticLocalCache("Jensen");
        System.out.println("name=" + name);

        staticLocalCache("Tom");
        System.out.println("name=" + name);

        staticLocalCache("Jerry");
        System.out.println("name=" + name);

        try {
            nativeException();
        } catch (NoSuchFieldException e) {
//            e.printStackTrace();
        }
        System.out.println("name=" + name);

    }


    static {
        System.load("D:\\Ndk\\NDK_Day15_c\\x64\\Debug\\NDK_Day15_c.dll");
    }

    public static native void sort(int[] arr);

    private static native void localRef();

    private static native void createGlobalRef(String str);

    private static native String getGlobalRef();

    private static native void delGlobalRef();

    private static native void staticLocalCache(String name);

    private static native void nativeException() throws NoSuchFieldException;//exception才能try，error不行的


}
