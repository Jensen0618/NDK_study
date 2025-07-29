package com.jensen.lib_camera.camera.view;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.SurfaceHolder;

import com.jensen.lib_camera.camera.CameraManager;
import com.jensen.lib_camera.camera.ICameraManager;
import com.jensen.lib_camera.camera.view.base.BaseSurfaceView;

public class CameraSurfaceView extends BaseSurfaceView {
    private static final String TAG = CameraSurfaceView.class.getSimpleName();

    public CameraSurfaceView(Context context) {
        super(context);
    }

    public CameraSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public CameraSurfaceView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    @Override
    public ICameraManager createCameraManager(Context context) {
        return new CameraManager(context);
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        Log.i(TAG, "surfaceChanged: [" + width + ", " + height + "]");
        mSurfaceWidth = width;
        mSurfaceHeight = height;
    }

    @Override
    public void onOpen() {
        Log.d(TAG, "onOpen: ");
        getCameraManager().startPreview(getSurfaceHolder());
    }
}
