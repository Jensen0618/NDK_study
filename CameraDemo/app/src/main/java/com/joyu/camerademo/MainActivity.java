package com.joyu.camerademo;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.btn_surface).setOnClickListener(this);
        findViewById(R.id.btn_texture).setOnClickListener(this);
        findViewById(R.id.btn_glsurface).setOnClickListener(this);

    }


    public void onSurfaceClick(View view) {
        startActivity(new Intent(this, MySurfaceViewActivity.class));
    }

    public void onTextureClick(View view) {
        startActivity(new Intent(this, TextureViewActivity.class));
    }

    public void onGLSurfaceClick(View view) {
        startActivity(new Intent(this, GLSurfaceViewActivity.class));
    }

    public void onCameraSurfaceView(View view) {
        startActivity(new Intent(this, CameraSurfaceViewActivity.class));
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_surface:
                startCameraActivity(R.layout.activity_camera_surface_view);
                break;
            case R.id.btn_texture:
                startCameraActivity(R.layout.activity_camera_texture_view);
                break;
            case R.id.btn_glsurface:
                startCameraActivity(R.layout.activity_camera_glsurface_view);
                break;
        }
    }

    private void startCameraActivity(int layoutId) {
        Intent intent = new Intent(this, CameraActivity.class);
        intent.putExtra(CameraActivity.EXTRA_LAYOUT_ID, layoutId);
        startActivity(intent);
    }
}