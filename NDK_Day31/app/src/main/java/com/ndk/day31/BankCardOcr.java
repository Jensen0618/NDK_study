package com.ndk.day31;

import android.graphics.Bitmap;

public class BankCardOcr {

    // Used to load the 'day31' library on application startup.
    static {
        System.loadLibrary("day31");
    }

    public static native String cardOcr(Bitmap bitmap);
}
