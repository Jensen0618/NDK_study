package com.joyu.camerademo;

import android.hardware.Camera;
import android.os.Bundle;
import android.view.SurfaceHolder;

import androidx.appcompat.app.AppCompatActivity;

import com.jensen.lib_camera.camera.view.base.BaseSurfaceView;

/**
 * 使用SurfaceView预览Camera数据
 */
public class CameraSurfaceViewActivity extends AppCompatActivity {
    private static final String TAG = CameraSurfaceViewActivity.class.getSimpleName();
    BaseSurfaceView surfaceView;
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