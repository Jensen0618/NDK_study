package com.ndk.day01;

import android.content.Context;

public class SignatureUtils {
    // Used to load the 'day01' library on application startup.
    static {
        System.loadLibrary("day01");
    }

    public static native String signatureParams(String params);

    public static native void signatureVerify(Context context);
}
