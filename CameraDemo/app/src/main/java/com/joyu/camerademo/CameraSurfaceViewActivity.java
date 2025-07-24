package com.joyu.camerademo;

import android.animation.ObjectAnimator;
import android.animation.PropertyValuesHolder;
import android.graphics.PixelFormat;
import android.hardware.Camera;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import com.jensen.lib_camera.camera.view.CameraSurfaceView;

import java.io.IOException;

/**
 * 使用SurfaceView预览Camera数据
 */
public class CameraSurfaceViewActivity extends AppCompatActivity {
    private static final String TAG = CameraSurfaceViewActivity.class.getSimpleName();
    CameraSurfaceView surfaceView;
    private SurfaceHolder holder;
    private Camera camera;
    private Camera.Parameters parameters;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera_surface_view);
        surfaceView = findViewById(R.id.camera_view);
    }

    @Override
    protected void onResume() {
        super.onResume();
        surfaceView.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        surfaceView.onPause();
    }
}