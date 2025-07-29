package com.jensen.lib_camera.camera.view;

import android.content.Context;
import android.util.AttributeSet;

import com.jensen.lib_camera.camera.CameraManager;
import com.jensen.lib_camera.camera.ICameraManager;
import com.jensen.lib_camera.camera.view.base.BaseTextureView;

public class CameraTextureView extends BaseTextureView {
    public CameraTextureView(Context context) {
        super(context);
    }

    public CameraTextureView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public CameraTextureView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    @Override
    public ICameraManager createCameraManager(Context context) {
        return new CameraManager(context);
    }
}
