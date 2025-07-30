package com.jensen.lib_camera.camera.view.base;

import android.content.Context;
import android.graphics.SurfaceTexture;
import android.opengl.GLSurfaceView;
import android.os.Handler;
import android.os.Message;
import android.util.AttributeSet;
import android.util.Log;

import com.jensen.lib_camera.camera.ICameraManager;
import com.jensen.lib_camera.camera.callback.CameraCallback;
import com.jensen.lib_camera.gles.GLESUtils;
import com.jensen.lib_camera.gles.filter.CameraFilter;

import java.lang.ref.WeakReference;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * SurfaceView+OpenGL ES
 */
public abstract class BaseGLSurfaceView extends GLSurfaceView implements CameraCallback, SurfaceTexture.OnFrameAvailableListener, BaseCameraView {
    private static final String TAG = BaseGLSurfaceView.class.getSimpleName();
    private Context mContext;
    private SurfaceTexture mSurfaceTexture;
    private CameraHandler mCameraHandler;
    private ICameraManager mCameraManager;
    private boolean mHasSurface; // 是否存在摄像头显示层
    private CameraSurfaceRender mRenderer;
    /**
     * 相机设置的预览宽度
     */
    private int mRatioWidth;
    /**
     * 相机设置的预览高度
     */
    private int mRatioHeight;
    /**
     * 在handleSurfaceChanged中赋值
     */
    protected int mGLSurfaceWidth, mGLSurfaceHeight;
    private int mPreviewWidth;
    private int mPreviewHeight;


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
        mRenderer = new CameraSurfaceRender(mCameraHandler);
        setRenderer(mRenderer);
        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);

    }

    //region BaseCameraView
    @Override
    public void onResume() {
        super.onResume();
        if (mHasSurface) {
            openCamera();
        }
    }

    @Override
    public void onPause() {
        super.onPause();
        closeCamera();
    }

    public void onDestroy() {
        mCameraHandler.invalidateHandler();
    }

    @Override
    public ICameraManager getCameraManager() {
        return mCameraManager;
    }
    //endregion

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
        int width = MeasureSpec.getSize(widthMeasureSpec);
        int height = MeasureSpec.getSize(heightMeasureSpec);
        Log.d(TAG, "onMeasure: [" + width + "," + height + "]");
        if (0 == mRatioWidth || 0 == mRatioHeight) {
            setMeasuredDimension(width, height * 4 / 3);//
        } else {
            if (width < height * mRatioWidth / mRatioHeight) {
                setMeasuredDimension(width, width * mRatioHeight / mRatioWidth);
            } else {
                setMeasuredDimension(height * mRatioWidth / mRatioHeight, height);
            }
        }
    }

    public SurfaceTexture getSurfaceTexture() {
        return mSurfaceTexture;
    }

    private void setAspectRatio(int width, int height) {
        Log.d(TAG, "setAspectRatio: [" + width + "," + height + "]");
        if (width < 0 || height < 0) {
            throw new IllegalArgumentException("Size cannot be negative.");
        }
        mRatioWidth = width;
        mRatioHeight = height;
        requestLayout();
    }

    private void setAspectRatio() {
        if (mGLSurfaceWidth > mGLSurfaceHeight) {
            setAspectRatio(mPreviewWidth, mPreviewHeight);
        } else {
            setAspectRatio(mPreviewHeight, mPreviewWidth);
        }
    }


    public abstract ICameraManager createCameraManager(Context context);

    //region CameraCallback
    @Override
    public void onOpen() {
        mCameraManager.startPreview(mSurfaceTexture);
    }

    @Override
    public void onOpenError(int error, String msg) {

    }

    @Override
    public void onPreview(int previewWidth, int previewHeight) {
        Log.i(TAG, "onPreview: [" + previewWidth + "," + previewHeight + "]");
        queueEvent(new Runnable() {
            @Override
            public void run() {
                mRenderer.setCameraPreviewSize(previewWidth, previewHeight);
            }
        });
        mPreviewWidth = previewWidth;
        mPreviewHeight = previewHeight;
        setAspectRatio();
    }

    @Override
    public void onPreviewError(int error, String msg) {

    }

    @Override
    public void onClose() {

    }
    //endregion


    //region SurfaceTexture.OnFrameAvailableListener
    @Override
    public void onFrameAvailable(SurfaceTexture surfaceTexture) {
        //请求每一帧数据进行渲染，Camera的预览需要我们自己绘制完成
        requestRender();
    }
    //endregion

    static class CameraHandler extends Handler {
        public static final int MSG_SET_SURFACE_TEXTURE = 0;
        public static final int MSG_SURFACE_CHANGED = 1;
        private WeakReference<BaseGLSurfaceView> mWeakGLSurfaceView;

        public CameraHandler(BaseGLSurfaceView view) {
            this.mWeakGLSurfaceView = new WeakReference<>(view);
        }

        /**
         * 释放引用
         */
        public void invalidateHandler() {
            mWeakGLSurfaceView.clear();
        }

        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            int what = msg.what;
            BaseGLSurfaceView view = mWeakGLSurfaceView.get();
            if (view == null) {
                return;
            }
            switch (what) {
                case MSG_SET_SURFACE_TEXTURE:
                    view.handleSetSurfaceTexture((SurfaceTexture) msg.obj);
                    break;
                case MSG_SURFACE_CHANGED:
                    view.handleSurfaceChanged(msg.arg1, msg.arg2);
                    break;
                default:
                    throw new RuntimeException("unknown msg " + what);
            }

        }


    }

    private void handleSetSurfaceTexture(SurfaceTexture surfaceTexture) {
        Log.i(TAG, "handleSetSurfaceTexture: ");
        mSurfaceTexture = surfaceTexture;
        mHasSurface = true;
        mSurfaceTexture.setOnFrameAvailableListener(this);
        openCamera();
    }

    private void handleSurfaceChanged(int width, int height) {
        Log.i(TAG, "handleSurfaceChanged: ");
        mGLSurfaceWidth = width;
        mGLSurfaceHeight = height;
        setAspectRatio();
    }


    private void openCamera() {
        if (mSurfaceTexture == null) {
            Log.e(TAG, "openCamera: mSurfaceTexture is null");
            return;
        }
        if (mCameraManager.isOpen()) {
            Log.w(TAG, "openCamera: Camera is opened!");
            return;
        }
        mCameraManager.openCamera();
    }

    private void closeCamera() {
        mCameraManager.releaseCamera();
        queueEvent(new Runnable() {
            @Override
            public void run() {
                mRenderer.notifyPausing();
            }
        });
        mSurfaceTexture = null;
    }

    static class CameraSurfaceRender implements Renderer {
        private CameraHandler mCameraHandler;

        private final float[] mDisplayProjectionMatrix = new float[16];
        private CameraFilter mCameraFilter;
        private boolean mSizeUpdated;
        private int mCameraPreviewWidth;
        private int mCameraPreviewHeight;
        private int mTextureId;
        private SurfaceTexture mSurfaceTexture;

        public CameraSurfaceRender(CameraHandler handler) {
            mCameraHandler = handler;
            mTextureId = -1;
            mSizeUpdated = false;
            mCameraPreviewWidth = mCameraPreviewHeight = -1;
            mCameraFilter = new CameraFilter();
        }

        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            Log.i(TAG, "onSurfaceCreated: " + Thread.currentThread().getName());
            //创建外部纹理ID
            mTextureId = GLESUtils.createOESTexture();
            //着色器程序执行相应的方法
            mCameraFilter.surfaceCreated();
            //在此EGL上下文中创建具有外部纹理的SurfaceTexture
            mSurfaceTexture = new SurfaceTexture(mTextureId);
            //将SurfaceTexture传递给UI线程，通知handle添加帧回调监听，开启摄像头
            mCameraHandler.sendMessage(mCameraHandler.obtainMessage(
                    CameraHandler.MSG_SET_SURFACE_TEXTURE, mSurfaceTexture));
        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            mCameraFilter.surfaceChanged(width, height);
            mCameraHandler.sendMessage(mCameraHandler.obtainMessage(
                    CameraHandler.MSG_SURFACE_CHANGED, width, height
            ));
        }

        @Override
        public void onDrawFrame(GL10 gl) {
            if (mSurfaceTexture == null) return;
            // 把摄像头的数据先输出来
            // 更新纹理，然后我们才能够使用opengl从SurfaceTexture当中获得数据 进行渲染
            mSurfaceTexture.updateTexImage();
            if (mCameraPreviewWidth <= 0 || mCameraPreviewHeight <= 0) {
                return;
            }
            if (mSizeUpdated) {
                mSizeUpdated = false;
            }
            mSurfaceTexture.getTransformMatrix(mDisplayProjectionMatrix);
            mCameraFilter.draw(mTextureId, mDisplayProjectionMatrix);
        }

        public void notifyPausing() {
            if (mSurfaceTexture != null) {
                Log.d(TAG, "notifyPausing: renderer pausing -- releasing SurfaceTexture");
                mSurfaceTexture.release();
                mSurfaceTexture = null;
            }
            if (mCameraFilter != null) {
                mCameraFilter.release();
            }
            mCameraPreviewWidth = mCameraPreviewHeight = -1;
        }

        public void setCameraPreviewSize(int previewWidth, int previewHeight) {
            mCameraPreviewWidth = previewWidth;
            mCameraPreviewHeight = previewHeight;
            mSizeUpdated = true;
        }
    }
}
