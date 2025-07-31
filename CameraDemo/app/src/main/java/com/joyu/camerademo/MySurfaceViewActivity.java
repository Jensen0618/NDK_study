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

import java.io.IOException;

/**
 * 使用SurfaceView预览Camera数据
 */
public class SurfaceViewActivity extends AppCompatActivity implements SurfaceHolder.Callback {
    private static final String TAG = SurfaceViewActivity.class.getSimpleName();
    SurfaceView surfaceView;
    private SurfaceHolder holder;
    private Camera camera;
    private Camera.Parameters parameters;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_surface_view);
        surfaceView = findViewById(R.id.mSurface);
        holder = surfaceView.getHolder();
        holder.addCallback(this);
        holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
    }

    /**
     * 创建时调用
     * @param holder The SurfaceHolder whose surface is being created.
     */
    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        Log.d(TAG, "surfaceCreated: ");
        try {
            camera = Camera.open(0);
            camera.setDisplayOrientation(0);
            camera.setPreviewDisplay(holder);
            camera.startPreview();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }


    /**
     * surfaceCreated之后回调一次
     * @param holder The SurfaceHolder whose surface has changed.
     * @param format The new PixelFormat of the surface.
     * @param width  The new width of the surface.
     * @param height The new height of the surface.
     */
    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        Log.d(TAG, "surfaceChanged: ");
        camera.autoFocus(new Camera.AutoFocusCallback() {
            @Override
            public void onAutoFocus(boolean success, Camera camera) {
                if (success) {
                    parameters = camera.getParameters();
                    parameters.setPictureFormat(PixelFormat.JPEG);//图片输出格式
                    parameters.setFocusMode(Camera.Parameters.FOCUS_MODE_CONTINUOUS_PICTURE);//持续对焦模式
                    camera.setParameters(parameters);
                    camera.startPreview();
                    camera.cancelAutoFocus();
                }
            }
        });
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        Log.d(TAG, "surfaceDestroyed: ");
        if (camera == null) {
            camera.stopPreview();
            camera.release();
            camera = null;
        }
    }

    /**
     * SurfaceView预览相机视图不支持透明度，可以设置缩放旋转属性。
     * 如果需要做动画特效的话不推荐使用SurfaceView显示视图。可以使用下面的TextureView或者GlSurfaceView来显示。
     * @param view
     */
    public void onAnimationClick(View view) {
        PropertyValuesHolder valuesHolder2 = PropertyValuesHolder.ofFloat("rotationX", 0.0f, 360.0f, 0.0F);
        PropertyValuesHolder valuesHolder = PropertyValuesHolder.ofFloat("rotationY", 0.0f, 360.0f, 0.0F);
        PropertyValuesHolder valuesHolder1 = PropertyValuesHolder.ofFloat("scaleX", 1.0f, 0.5f,1.0f);
        PropertyValuesHolder valuesHolder3 = PropertyValuesHolder.ofFloat("scaleY", 1.0f, 0.5f,1.0f);
        ObjectAnimator objectAnimator = ObjectAnimator.ofPropertyValuesHolder(surfaceView,  valuesHolder,valuesHolder1,valuesHolder3,valuesHolder2);
        objectAnimator.setDuration(5000).start();
    }
}