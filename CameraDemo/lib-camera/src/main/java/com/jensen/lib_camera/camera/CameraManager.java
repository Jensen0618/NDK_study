package com.jensen.lib_camera.camera;

import android.content.Context;
import android.graphics.ImageFormat;
import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.util.Log;
import android.util.Size;
import android.view.OrientationEventListener;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.WindowManager;

import com.jensen.lib_camera.camera.callback.CameraCallback;
import com.jensen.lib_camera.camera.callback.PictureBufferCallback;
import com.jensen.lib_camera.camera.callback.PreviewBufferCallback;
import com.jensen.lib_camera.camera.callback.YUVFormat;

import java.util.ArrayList;
import java.util.List;

public class CameraManager implements ICameraManager {
    private static final String TAG = CameraManager.class.getSimpleName();
    public static final int CAMERA_ERROR_NO_ID = -1001;
    public static final int CAMERA_ERROR_OPEN = -1002;
    public static final int CAMERA_ERROR_PREVIEW = -2001;
    Context mContext;
    Camera mCamera;
    int mCameraId = 0;
    private Size mPreviewSize;
    private int mPreviewWidth = 640;
    private int mPreviewHeight = 480;

    /**
     * 预览画面高度和宽度的比值
     */
    private float mPreviewScale = mPreviewHeight * 1f / mPreviewWidth;
    private Camera.CameraInfo mCameraInfo = new Camera.CameraInfo();

    CameraCallback mCameraCallback;
    private Camera.ErrorCallback mErrorCallback = new Camera.ErrorCallback() {
        @Override
        public void onError(int error, Camera camera) {
            String msg = "";
            switch (error) {
                case Camera.CAMERA_ERROR_SERVER_DIED:
                    //Media server died. In this case, the application must release the Camera object and instantiate a new one.
                    Log.e(TAG, "Camera.CAMERA_ERROR_SERVER_DIED camera id:" + mCameraId);
                    msg = "Camera Media server died.";
                    //这里重新初始化Camera即可
                    break;
                case Camera.CAMERA_ERROR_UNKNOWN:
                    Log.e(TAG, "Camera.CAMERA_ERROR_UNKNOWN");
                    msg = "Camera unknown error.";
                    break;
            }
            onOpenError(error, msg);
            releaseCamera();
        }
    };
    private Camera.Parameters mParameters;
    private int mDisplayOrientation = -1;
    private int mOrientation = -1;
    /**
     * 这是什么？
     */
    private OrientationEventListener mOrientationEventListener;
    private int mLatestRotation = 0;

    private boolean isSupportZoom;

    private boolean isPreviewing = false;
    private List<PreviewBufferCallback> mPreviewBufferCallbacks = new ArrayList<>();
    private Camera.PreviewCallback mPreviewCallback = new Camera.PreviewCallback() {
        @Override
        public void onPreviewFrame(byte[] data, Camera camera) {
            if (!mPreviewBufferCallbacks.isEmpty()) {
                for (PreviewBufferCallback callback : mPreviewBufferCallbacks) {
                    callback.onPreviewBufferFrame(data, mPreviewWidth, mPreviewHeight, YUVFormat.NV21);
                }
            }
            mCameraBytes = data;
            //再次调用 camera.addCallbackBuffer(data) 将该缓冲区返还给相机，以便它可以被重用于未来的帧。 忘记这一步会导致回调停止触发。
            camera.addCallbackBuffer(data);
        }
    };

    private byte[] mCameraBytes = null;


    public CameraManager(Context context) {
        this.mContext = context;
        mOrientationEventListener = new OrientationEventListener(mContext) {
            @Override
            public void onOrientationChanged(int orientation) {
                Log.d(TAG, "onOrientationChanged: " + orientation);
                setPictureRotate(orientation);
            }
        };
    }

    /**
     * 打开Camera
     */
    @Override
    public synchronized void openCamera() {
        Log.i(TAG, "Camera open #" + mCameraId);
        if (mCamera == null) {
            if (mCameraId >= Camera.getNumberOfCameras()) {
                onOpenError(CAMERA_ERROR_NO_ID, "No camera.");
                return;
            }
            try {
                mCamera = Camera.open(mCameraId);
                Camera.getCameraInfo(mCameraId, mCameraInfo);
                mCamera.setErrorCallback(mErrorCallback);
                initCamera();
                onOpen();
                mOrientationEventListener.enable();
            } catch (Exception e) {
                onOpenError(CAMERA_ERROR_OPEN, e.getMessage());
            }
        }
    }

    @Override
    public void releaseCamera() {
        Log.v(TAG, "releaseCamera.");
        if (null != mCamera) {
            stopPreview();
            try {
                mCamera.release();
                mCamera = null;
                mCameraBytes = null;
                mDisplayOrientation = -1;
            } catch (Exception e) {
                Log.e(TAG, "releaseCamera: ", e);
            }
            onClose();
        }
    }

    @Override
    public void startPreview(SurfaceHolder holder) {
        Log.i(TAG, "startPreview...");
        if (isPreviewing) {
            return;
        }

        if (mCamera != null) {
            try {
                //设置在哪里显示实时预览；SurfaceHolder对象通常从SurfaceView获取
                mCamera.setPreviewDisplay(holder);
                if (!mPreviewBufferCallbacks.isEmpty()) {
                    //分配缓冲区，供相机写入预览帧数据
                    //缓冲区的大小计算为 mPreviewWidth * mPreviewHeight * 3 / 2。这个计算对于 NV21 格式的图像（这是 Android 相机的默认预览格式）是典型的。在 NV21 格式中，每个像素平均使用 12 位（1.5 字节）（Y 分量每像素使用 1 字节，U/V 分量被二次采样，组合起来每像素使用 0.5 字节）。
                    mCamera.addCallbackBuffer(new byte[mPreviewWidth * mPreviewHeight * 3 / 2]);
                    //与addCallbackBuffer结合使用
                    //当新的预览帧准备好并且有一个可用的缓冲区（ 来自通过 addCallbackBuffer() 添加的那些）时，mPreviewCallback 的 onPreviewFrame(byte[] data, Camera camera) 方法将被调用。data 参数将是包含帧图像数据的字节数组。
                    //在 onPreviewFrame 中处理完数据后，你必须再次调用 camera.addCallbackBuffer(data) 将该缓冲区返还给相机，以便它可以被重用于未来的帧。 忘记这一步会导致回调停止触发。
                    mCamera.setPreviewCallbackWithBuffer(mPreviewCallback);
                }
                mCamera.startPreview();
                onPreview(mPreviewWidth, mPreviewHeight);
            } catch (Exception e) {
                onPreviewError(CAMERA_ERROR_PREVIEW, e.getMessage());
            }
        }
    }

    @Override
    public void startPreview(SurfaceTexture surfaceTexture) {

    }

    @Override
    public void stopPreview() {
        Log.v(TAG, "stopPreview.");
        if (isPreviewing && null != mCamera) {
            try {
                mCamera.setPreviewCallback(null);
                mCamera.stopPreview();
                mPreviewBufferCallbacks.clear();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        isPreviewing = false;
    }

    @Override
    public void setCameraId(int cameraId) {
        mCameraId = cameraId;
    }

    @Override
    public int getCameraId() {
        return mCameraId;
    }

    @Override
    public boolean isOpen() {
        return mCamera != null;
    }

    @Override
    public Size getPreviewSize() {
        return mPreviewSize;
    }

    @Override
    public void setPreviewSize(Size size) {
        mPreviewSize = size;
        mPreviewWidth = size.getWidth();
        mPreviewHeight = size.getHeight();
        mPreviewScale = mPreviewHeight * 1f / mPreviewWidth;
    }

    @Override
    public int getOrientation() {
        return mOrientation;
    }

    @Override
    public int getDisplayOrientation() {
        return mDisplayOrientation;
    }

    @Override
    public void setCameraCallback(CameraCallback cameraCallback) {
        mCameraCallback = cameraCallback;
    }

    @Override
    public void addPreviewBufferCallback(PreviewBufferCallback previewBufferCallback) {
        if (previewBufferCallback != null && !mPreviewBufferCallbacks.contains(previewBufferCallback)) {
            mPreviewBufferCallbacks.add(previewBufferCallback);
        }
    }

    @Override
    public void takePicture(PictureBufferCallback pictureBufferCallback) {

    }

    @Override
    public void switchCamera() {

    }


    private void initCamera() {
        if (mCamera != null) {
            mParameters = mCamera.getParameters();
            if (mDisplayOrientation == -1) {
                setCameraDisplayOrientation(mContext, mCameraId, mCamera);
            }
            // 设置预览方向
            mCamera.setDisplayOrientation(mDisplayOrientation);
            // 设置拍照方向
            mParameters.setRotation(mOrientation);

            // 如果摄像头不支持这些参数都会出错的，所以设置的时候一定要判断是否支持
            List<String> supportedFlashModes = mParameters.getSupportedFlashModes();
            if (supportedFlashModes != null && supportedFlashModes.contains(Camera.Parameters.FLASH_MODE_OFF)) {
                mParameters.setFlashMode(Camera.Parameters.FLASH_MODE_OFF); // 设置闪光模式
            }
            List<String> supportedFocusModes = mParameters.getSupportedFocusModes();
            if (supportedFocusModes != null && supportedFocusModes.contains(Camera.Parameters.FOCUS_MODE_CONTINUOUS_VIDEO)) {
                mParameters.setFocusMode(Camera.Parameters.FOCUS_MODE_CONTINUOUS_VIDEO); // 设置聚焦模式
            }
            mParameters.setPreviewFormat(ImageFormat.NV21); // 设置预览图片格式
            mParameters.setPictureFormat(ImageFormat.JPEG); // 设置拍照图片格式
            mParameters.setExposureCompensation(0); // 设置曝光强度

            //设置预览尺寸
            Camera.Size previewSize = getSuitableSize(mParameters.getSupportedPreviewSizes());
            mPreviewWidth = previewSize.width;
            mPreviewHeight = previewSize.height;
            mPreviewSize = new Size(mPreviewWidth, mPreviewHeight);
            mParameters.setPreviewSize(mPreviewWidth, mPreviewHeight);
            Log.d(TAG, "previewWidth: " + mPreviewWidth + ", previewHeight: " + mPreviewHeight);

            //设置拍照尺寸
            // TODO: 2025-07-21 为什么不选呢？
            Camera.Size pictureSize = mParameters.getPictureSize();
            mParameters.setPictureSize(pictureSize.width, pictureSize.height);
            Log.d(TAG, "pictureWidth: " + pictureSize.width + ", pictureHeight: " + pictureSize.height);

            mCamera.setParameters(mParameters);
            isSupportZoom = mParameters.isSmoothZoomSupported();
        }
    }

    public void setCameraDisplayOrientation(Context context, int cameraId,
                                            Camera camera) {
        if (context == null)
            return;
        Camera.CameraInfo info = new Camera.CameraInfo();
        Camera.getCameraInfo(cameraId, info);
        WindowManager windowManager = (WindowManager) context
                .getSystemService(Context.WINDOW_SERVICE);
        int rotation = windowManager.getDefaultDisplay().getRotation();
        int degrees = 0;
        switch (rotation) {
            case Surface.ROTATION_0:
                degrees = 0;
                break;
            case Surface.ROTATION_90:
                degrees = 90;
                break;
            case Surface.ROTATION_180:
                degrees = 180;
                break;
            case Surface.ROTATION_270:
                degrees = 270;
                break;
        }

        int result;
        if (info.facing == Camera.CameraInfo.CAMERA_FACING_FRONT) {
            result = (info.orientation + degrees) % 360;
            result = (360 - result) % 360; // compensate the mirror
        } else { // back-facing
            result = (info.orientation - degrees + 360) % 360;
        }
        camera.setDisplayOrientation(result);
        mDisplayOrientation = result;
        mOrientation = info.orientation;
        Log.d(TAG, "displayOrientation:" + mDisplayOrientation);
        Log.d(TAG, "orientation:" + mOrientation);
    }

    /**
     * 获取合适的尺寸
     *
     * @param sizes
     * @return
     */
    private Camera.Size getSuitableSize(List<Camera.Size> sizes) {
        int minDelta = Integer.MAX_VALUE; // 最小的差值，初始值应该设置大点保证之后的计算中会被重置
        int index = 0; // 最小的差值对应的索引坐标
        for (int i = 0; i < sizes.size(); i++) {
            Camera.Size size = sizes.get(i);
            Log.v(TAG, "SupportedSize, width: " + size.width + ", height: " + size.height);
            // 先判断比例是否相等 mPreviewScale=高/宽
            if (size.width * mPreviewScale == size.height) {
                //比例相等的情况下，再判断预设的宽度和参数中宽度的差值
                int delta = Math.abs(mPreviewWidth - size.width);//abs求绝对值
                if (delta == 0) {//相等，就是你了
                    return size;
                }
                if (minDelta > delta) {//不断地取差值更新的那个参数
                    minDelta = delta;
                    index = i;
                }
            }
        }
        return sizes.get(index);
    }

    /**
     * 计算拍照时需要应用的正确旋转角度
     *
     * @param orientation 设备当前方向（单位度），这个值通常来自{@link OrientationEventListener}
     */
    private void setPictureRotate(int orientation) {
        if (orientation == OrientationEventListener.ORIENTATION_UNKNOWN) return;
        //这行代码将 orientation 值“吸附”到最接近的 90 度倍数（0, 90, 180, 270）。
        //orientation + 45：加上 45 度。这会移动用于四舍五入的边界。例如，0 到 44 之间的值会变成 45 到 89。45 到 134 之间的值会变成 90 到 179。
        //90：整数除以 90。这有效地确定了移位后的值落入哪个 90 度的象限。例如，45 到 89 变成 0，90 到 179 变成 1。
        //90：将结果乘以 90。这将象限转换回度数（0, 90, 180, 270）。
        orientation = (orientation + 45) / 90 * 90;
        int rotation;
        if (mCameraInfo.facing == Camera.CameraInfo.CAMERA_FACING_FRONT) {//前置摄像头
            //公式 (传感器方向 - 设备方向 + 360) % 360 是补偿这种情况并获得正确图像旋转的一种常见方法。
            //+360是为了确保正数
            rotation = (mCameraInfo.orientation - orientation + 360) % 360;
        } else {  // back-facing camera
            //对于后置摄像头，通常使用公式 (传感器方向 + 设备方向) % 360 来确定使图像直立所需的旋转。
            rotation = (mCameraInfo.orientation + orientation) % 360;
        }
        mLatestRotation = rotation;
    }

    private void onOpen() {
        if (mCameraCallback != null) {
            mCameraCallback.onOpen();
        }
    }

    private void onOpenError(int error, String msg) {
        if (mCameraCallback != null) {
            mCameraCallback.onOpenError(error, msg);
        }
    }


    private void onPreview(int width, int height) {
        isPreviewing = true;
        if (mCameraCallback != null) {
            mCameraCallback.onPreview(width, height);
        }
    }

    private void onPreviewError(int error, String msg) {
        if (mCameraCallback != null) {
            mCameraCallback.onPreviewError(error, msg);
        }
    }

    private void onClose() {
        if (mCameraCallback != null) {
            mCameraCallback.onClose();
        }
    }
}
