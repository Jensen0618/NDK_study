package com.joyu.camerademo.base;

import android.os.Bundle;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.jensen.lib_camera.camera.ICameraManager;
import com.jensen.lib_camera.camera.view.base.BaseCameraView;
import com.joyu.camerademo.R;

public abstract class BaseCameraActivity extends AppCompatActivity {
    protected ICameraManager mCameraManager;
    protected BaseCameraView mBaseCameraView;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(getLayoutId());
        //这竟然是能这么写的吗
        mBaseCameraView = findViewById(R.id.camera_view);
        mCameraManager= mBaseCameraView.getCameraManager();
    }

    public abstract int getLayoutId();

    @Override
    protected void onResume() {
        super.onResume();
        mBaseCameraView.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        mBaseCameraView.onPause();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        mBaseCameraView.onDestroy();
    }
}
