package com.jensen.lib_camera.camera.view.base;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Handler;
import android.util.AttributeSet;

import com.jensen.lib_camera.camera.ICameraManager;
import com.jensen.lib_camera.camera.callback.CameraCallback;

import java.lang.ref.WeakReference;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public abstract class BaseGLSurfaceView extends GLSurfaceView implements CameraCallback {
    private Context mContext;
    private CameraHandler mCameraHandler;
    private ICameraManager mCameraManager;
    private boolean mHasSurface; // 是否存在摄像头显示层


    public BaseGLSurfaceView(Context context) {
        super(context);
        init(context);
    }


    public BaseGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    private void init(Context context) {
        mContext = context;
        mCameraHandler = new CameraHandler(this);

        mCameraManager = createCameraManager(context);
        mCameraManager.setCameraCallback(this);

        setEGLContextClientVersion(2);

    }

    public abstract ICameraManager createCameraManager(Context context);

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

    static class CameraHandler extends Handler {
        public static final int MSG_SET_SURFACE_TEXTURE = 0;
        public static final int MSG_SURFACE_CHANGED = 1;
        private WeakReference<BaseGLSurfaceView> mWeakGLSurfaceView;

        public CameraHandler(BaseGLSurfaceView view) {
            this.mWeakGLSurfaceView = new WeakReference<>(view);
        }
    }

    static class CameraSurfaceRender implements Renderer{
        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {

        }

        @Override
        public void onDrawFrame(GL10 gl) {

        }
    }
}
