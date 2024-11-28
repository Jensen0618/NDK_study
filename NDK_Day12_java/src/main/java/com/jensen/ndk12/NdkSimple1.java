package com.jensen.ndk12;

import java.util.UUID;

public class NdkSimple1 {
    public String name = "Jensen";
    public static int age = 20;

    static {
        System.load("D:\\Workspace\\C++\\NDK_Day12\\x64\\Debug\\NDK_Day12.dll");
    }

    public static String getUUID() {
        return UUID.randomUUID().toString();
    }

    //改变属性
    public native void changeName();

    public static native int changeInt();

    public static native String getJavaUUID();

    //native构建java对象
    public native Person createPerson();

    public static void main(String[] args) {
        NdkSimple1 ndkSimple1 = new NdkSimple1();
//        System.out.println("修改前 name=" + ndkSimple1.name + ", age=" + NdkSimple1.age);
//        ndkSimple1.changeName();
//        int i = NdkSimple1.changeInt();
//        System.out.println("i="+i);
//        System.out.println("修改后 name=" + ndkSimple1.name + ", age=" + NdkSimple1.age);

//        String uuid = getUUID();
//        System.out.println(uuid);
//        String javaUUID = NdkSimple1.getJavaUUID();
//        System.out.println(javaUUID);

        Person person = ndkSimple1.createPerson();
//        System.out.println(person.toString());

    }
}
