package com.joyu.gldemo;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.joyu.gldemo.renderer.L1_1_PointRenderer;

public class MainActivity extends AppCompatActivity {

    private GLSurfaceView glSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        glSurfaceView = new GLSurfaceView(this);
        glSurfaceView.setEGLContextClientVersion(2);
        L1_1_PointRenderer renderer = new L1_1_PointRenderer();
        glSurfaceView.setRenderer(renderer);
//        glSurfaceView.setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
        setContentView(glSurfaceView);

    }

    @Override
    protected void onResume() {
        super.onResume();
        if (glSurfaceView!=null) {
            glSurfaceView.onResume();
        }
    }

    @Override
    protected void onPause() {
        if (glSurfaceView!=null) {
            glSurfaceView.onPause();
        }
        super.onPause();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }
}