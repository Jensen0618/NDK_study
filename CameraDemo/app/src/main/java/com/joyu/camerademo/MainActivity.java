package com.joyu.camerademo;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


    public void onSurfaceClick(View view) {
        startActivity(new Intent(this, SurfaceViewActivity.class));
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
}