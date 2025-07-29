package com.jensen.lib_camera.camera.view.base;

import android.content.Context;
import android.graphics.PixelFormat;
import android.util.AttributeSet;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.jensen.lib_camera.camera.ICameraManager;
import com.jensen.lib_camera.camera.callback.CameraCallback;

public abstract class BaseSurfaceView extends SurfaceView implements SurfaceHolder.Callback, CameraCallback, BaseCameraView {

    private static final String TAG = BaseSurfaceView.class.getSimpleName();
    private Context mContext;
    private SurfaceHolder mSurfaceHolder;
    /**
     * 是否存在摄像头显示层
     */
    private boolean mHasSurface;
    private ICameraManager mCameraManager;
    /**
     * 相机设置的预览宽度
     */
    private int mRatioWidth;
    /**
     * 相机设置的预览高度
     */
    private int mRatioHeight;
    protected int mSurfaceWidth;
    protected int mSurfaceHeight;

    public BaseSurfaceView(Context context) {
        super(context);
        init(context);
    }

    public BaseSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public BaseSurfaceView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    private void init(Context context) {
        mContext = context;
        //Looper.getMainLooper() 和 context.getMainLooper() 都用于获取主线程（UI 线程）的 Looper 对象
        mSurfaceHolder = getHolder();
        mSurfaceHolder.setFormat(PixelFormat.TRANSPARENT);
        mSurfaceHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
        mSurfaceHolder.addCallback(this);//关键回调
        mCameraManager = createCameraManager(context);
        mCameraManager.setCameraCallback(this);
    }

    public abstract ICameraManager createCameraManager(Context context);

    @Override
    public ICameraManager getCameraManager() {
        return mCameraManager;
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        Log.i(TAG, "surfaceCreated: ");
        if (!mHasSurface && holder != null) {
            mHasSurface = true;
            openCamera();
        }
    }

    private void openCamera() {
        if (mSurfaceHolder == null) {
            Log.e(TAG, "openCamera: surfaceHolder is null");
            return;
        }
        if (mCameraManager.isOpen()) {
            Log.w(TAG, "openCamera: Camera is opened!");
            return;
        }
        mCameraManager.openCamera();

    }

    /**
     * surfaceChanged的宽高就是SurfaceView的渲染宽高
     *
     * @param holder The SurfaceHolder whose surface has changed.
     * @param format The new PixelFormat of the surface.
     * @param width  The new width of the surface.
     * @param height The new height of the surface.
     */
    @Override
    public abstract void surfaceChanged(SurfaceHolder holder, int format, int width, int height);

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        Log.i(TAG, "surfaceDestroyed: ");
        closeCamera();
        mHasSurface = false;
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
    }

    private void closeCamera() {
        mCameraManager.releaseCamera();
    }

    @Override
    public abstract void onOpen();

    @Override
    public void onOpenError(int error, String msg) {
        Log.d(TAG, "onOpenError: ");
    }

    @Override
    public void onPreview(int previewWidth, int previewHeight) {
        Log.d(TAG, "onPreview: [" + previewWidth + "," + previewHeight + "]");
//        if (mSurfaceWidth == 0 || mSurfaceHeight == 0) {
//            return;
//        }
//        if (mSurfaceWidth > mSurfaceHeight) {
//            setAspectRatio(previewWidth, previewHeight);
//        } else {
//            setAspectRatio(previewHeight, previewWidth);
//        }
        setAspectRatio(previewWidth, previewHeight);
    }

    @Override
    public void onPreviewError(int error, String msg) {

    }

    @Override
    public void onClose() {

    }

    public SurfaceHolder getSurfaceHolder() {
        return mSurfaceHolder;
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

    private void setAspectRatio(int width, int height) {
        Log.d(TAG, "setAspectRatio: [" + width + "," + height + "]");
        if (width < 0 || height < 0) {
            throw new IllegalArgumentException("Size cannot be negative.");
        }
        mRatioWidth = width;
        mRatioHeight = height;
        requestLayout();
    }
}
