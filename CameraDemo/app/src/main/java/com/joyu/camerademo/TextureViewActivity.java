package com.joyu.camerademo;

import android.animation.ObjectAnimator;
import android.animation.PropertyValuesHolder;
import android.graphics.PixelFormat;
import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.TextureView;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import java.io.IOException;

/**
 * 使用SurfaceView预览Camera数据
 */
public class TextureViewActivity extends AppCompatActivity implements TextureView.SurfaceTextureListener {
    private static final String TAG = TextureViewActivity.class.getSimpleName();
    TextureView textureView;
    private Camera camera;
    private Camera.Parameters parameters;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_texture_view);
        textureView = findViewById(R.id.texture);
        textureView.setSurfaceTextureListener(this);
    }



    /**
     * SurfaceView预览相机视图不支持透明度，可以设置缩放旋转属性。
     * 如果需要做动画特效的话不推荐使用SurfaceView显示视图。可以使用下面的TextureView或者GlSurfaceView来显示。
     * @param view
     */
    public void onAnimationClick(View view) {
        PropertyValuesHolder valuesHolder = PropertyValuesHolder.ofFloat("translationX", 0.0f, 0.0f);
        PropertyValuesHolder valuesHolder1 = PropertyValuesHolder.ofFloat("scaleX", 1.0f, 0.3f,1.0f);
        PropertyValuesHolder valuesHolder4 = PropertyValuesHolder.ofFloat("scaleY", 1.0f, 0.3f,1.0f);
        PropertyValuesHolder valuesHolder2 = PropertyValuesHolder.ofFloat("rotationX", 0.0f, 2 * 360.0f, 0.0F);
        PropertyValuesHolder valuesHolder5 = PropertyValuesHolder.ofFloat("rotationY", 0.0f, 2 * 360.0f, 0.0F);
        PropertyValuesHolder valuesHolder3 = PropertyValuesHolder.ofFloat("alpha", 1.0f, 0.7f, 1.0F);
        ObjectAnimator objectAnimator = ObjectAnimator.ofPropertyValuesHolder(textureView, valuesHolder, valuesHolder1, valuesHolder2, valuesHolder3,valuesHolder4,valuesHolder5);
        objectAnimator.setDuration(5000).start();
    }

    /**
     * 开始预览时回调
     * @param surface The surface returned by
     *                {@link android.view.TextureView#getSurfaceTexture()}
     * @param width   The width of the surface
     * @param height  The height of the surface
     */
    @Override
    public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
        Log.d(TAG, "onSurfaceTextureAvailable: ");
        try {
            camera = Camera.open(0);
            camera.setDisplayOrientation(0);
            camera.setPreviewTexture(textureView.getSurfaceTexture());
            camera.startPreview();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * 没看到回调
     * @param surface The surface returned by
     *                {@link android.view.TextureView#getSurfaceTexture()}
     * @param width   The new width of the surface
     * @param height  The new height of the surface
     */
    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {
        //没进到这里
        Log.d(TAG, "onSurfaceTextureSizeChanged: ");
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
    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
        Log.d(TAG, "onSurfaceTextureDestroyed: ");
        if (camera == null) {
            camera.stopPreview();
            camera.release();
            camera = null;
        }
        return false;
    }

    /**
     * 一直在回调，应该是在刷新摄像头数据
     * @param surface The surface just updated
     */
    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture surface) {
        Log.d(TAG, "onSurfaceTextureUpdated: ");
    }
}