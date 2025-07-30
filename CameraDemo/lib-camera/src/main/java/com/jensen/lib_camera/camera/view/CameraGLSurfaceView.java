package com.jensen.lib_camera.camera.view;

import android.content.Context;
import android.util.AttributeSet;

import com.jensen.lib_camera.camera.CameraManager;
import com.jensen.lib_camera.camera.ICameraManager;
import com.jensen.lib_camera.camera.view.base.BaseGLSurfaceView;

public class CameraGLSurfaceView extends BaseGLSurfaceView {
    public CameraGLSurfaceView(Context context) {
        super(context);
    }

    public CameraGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public ICameraManager createCameraManager(Context context) {
        return new CameraManager(context);
    }
}
