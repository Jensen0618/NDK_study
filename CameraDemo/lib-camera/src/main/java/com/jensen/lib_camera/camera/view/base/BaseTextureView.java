package com.jensen.lib_camera.camera.view.base;

import android.content.Context;
import android.util.AttributeSet;
import android.view.TextureView;

import com.jensen.lib_camera.camera.ICameraManager;
import com.jensen.lib_camera.camera.callback.CameraCallback;

public abstract class BaseTextureView extends TextureView implements CameraCallback {
    private static final String TAG = BaseTextureView.class.getSimpleName();
    private Context mContext;
    private ICameraManager mCameraManager;

    public BaseTextureView(Context context) {
        super(context);
        init(context);
    }


    public BaseTextureView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public BaseTextureView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    private void init(Context context) {
        mContext = context;
        mCameraManager = createCameraManager(context);
        mCameraManager.setCameraCallback(this);

    }

    public abstract ICameraManager createCameraManager(Context context);

    public ICameraManager getCameraManager() {
        return mCameraManager;
    }

    @Override
    public void onOpen() {

    }

    @Override
    public void onOpenError(int error, String msg) {

    }

    @Override
    public void onPreview(int previewWidth, int previewHeight) {

    }

    @Override
    public void onPreviewError(int error, String msg) {

    }

    @Override
    public void onClose() {

    }
}
