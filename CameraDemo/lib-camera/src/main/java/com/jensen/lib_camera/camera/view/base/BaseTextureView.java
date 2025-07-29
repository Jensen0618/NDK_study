package com.jensen.lib_camera.camera.view.base;

import android.content.Context;
import android.graphics.Matrix;
import android.graphics.SurfaceTexture;
import android.util.AttributeSet;
import android.util.Log;
import android.view.TextureView;

import com.jensen.lib_camera.camera.ICameraManager;
import com.jensen.lib_camera.camera.callback.CameraCallback;

public abstract class BaseTextureView extends TextureView implements CameraCallback, BaseCameraView, TextureView.SurfaceTextureListener {
    private static final String TAG = BaseTextureView.class.getSimpleName();
    private Context mContext;
    private SurfaceTexture mSurfaceTexture;
    /**
     * 是否镜像
     */
    private boolean mIsMirror;
    private ICameraManager mCameraManager;
    private int mRatioWidth;
    private int mRatioHeight;
    private int mTextureWidth;
    private int mTextureHeight;
    /**
     * 是否存在摄像头显示层
     */
    private boolean mHasSurface;

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
        setSurfaceTextureListener(this);//关键回调，和SurfaceView的区别在这里，SurfaceView使用的是mSurfaceHolder.addCallback(this)
    }

    public abstract ICameraManager createCameraManager(Context context);

    @Override
    public ICameraManager getCameraManager() {
        return mCameraManager;
    }

    @Override
    public void onResume() {
        if (mHasSurface) {
            //activity暂停但并未停止的时候（从onPause中恢复），surface仍然存在，但已经释放了摄像头，需要重新打开
            openCamera();
        }
    }

    @Override
    public void onPause() {
        closeCamera();
    }

    @Override
    public void onDestroy() {

    }

    /**
     * 是否镜像
     *
     * @return
     */
    public boolean isMirror() {
        return mIsMirror;
    }

    /**
     * 设置是否镜像
     *
     * @param mirror
     */
    public void setMirror(boolean mirror) {
        mIsMirror = mirror;
        requestLayout();
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

        if (mIsMirror) {
            Matrix transform = new Matrix();
            transform.setScale(-1, 1, getMeasuredWidth() / 2, 0);
            setTransform(transform);
        } else {
            setTransform(null);
        }
    }

    @Override
    public void onOpen() {
        mCameraManager.startPreview(mSurfaceTexture);
    }

    @Override
    public void onOpenError(int error, String msg) {

    }

    @Override
    public void onPreview(int previewWidth, int previewHeight) {
        if (mTextureWidth > mTextureHeight) {
            setAspectRatio(previewWidth, previewHeight);
        } else {
            setAspectRatio(previewHeight,previewWidth);
        }
    }

    @Override
    public void onPreviewError(int error, String msg) {

    }

    @Override
    public void onClose() {

    }

    /**
     * 重写了获取表面纹理的方法，返回mSurfaceTexture
     *
     * @return
     */
    @Override
    public SurfaceTexture getSurfaceTexture() {
        return mSurfaceTexture;
    }

    /**
     * 相当于SurfaceView中的surfaceCreated，不同的是这里已经能获取到宽高了
     */
    @Override
    public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
        Log.i(TAG, "onSurfaceTextureAvailable: ");
        mTextureWidth = width;
        mTextureHeight = height;
        mSurfaceTexture = surface;
        mHasSurface = true;
        openCamera();
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

    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {
        Log.i(TAG, "onSurfaceTextureSizeChanged: ");
    }

    @Override
    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
        Log.i(TAG, "onSurfaceTextureDestroyed: ");
        closeCamera();
        mHasSurface = false;
        //返回true，释放资源
        return true;
    }

    private void closeCamera() {
        mCameraManager.releaseCamera();
    }

    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture surface) {

    }
}
