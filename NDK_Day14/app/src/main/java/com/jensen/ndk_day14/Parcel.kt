package com.jensen.ndk_day14

class Parcel {
    private var mNativePtr: Long = 0

    init {
        System.loadLibrary("ndk_day14")

        mNativePtr = nativeCreate();
    }

    fun writeInt(value: Int) {
        nativeWriteInt(mNativePtr, value)
    }

    fun readInt(): Int {
        return nativeReadInt(mNativePtr)
    }

    fun setDataPosition(pos: Int) {
        nativeSetDataPosition(pos)
    }




    private external fun nativeCreate(): Long
    private external fun nativeWriteInt(nativePtr: Long, value: Int)
    private external fun nativeReadInt(nativePtr: Long): Int
    private external fun nativeSetDataPosition(pos: Int)
}