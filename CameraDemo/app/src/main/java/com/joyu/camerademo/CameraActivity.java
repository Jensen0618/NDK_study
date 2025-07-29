package com.joyu.camerademo;

import android.content.Intent;

import com.joyu.camerademo.base.BaseCameraActivity;

public class CameraActivity extends BaseCameraActivity {
    public static final String EXTRA_LAYOUT_ID = "EXTRA_LAYOUT_ID";


    @Override
    public int getLayoutId() {
        Intent intent = getIntent();
        return intent.getIntExtra(EXTRA_LAYOUT_ID, R.layout.activity_camera_surface_view);
    }
}
