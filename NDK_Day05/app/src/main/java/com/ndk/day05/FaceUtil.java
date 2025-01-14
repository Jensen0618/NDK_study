package com.ndk.day05;

import android.graphics.Bitmap;

public class FaceUtil {
    // Used to load the 'day05' library on application startup.
    static {
        System.loadLibrary("day05");
    }

    public native int dectFace(Bitmap mBpFace);



}
