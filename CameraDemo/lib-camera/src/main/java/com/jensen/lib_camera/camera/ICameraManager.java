package com.jensen.lib_camera.camera;

import android.graphics.SurfaceTexture;
import android.util.Size;
import android.view.SurfaceHolder;

import com.jensen.lib_camera.camera.callback.CameraCallback;
import com.jensen.lib_camera.camera.callback.PictureBufferCallback;
import com.jensen.lib_camera.camera.callback.PreviewBufferCallback;

public interface ICameraManager {

    /**
     * 打开Camera
     */
    void openCamera();

    /**
     * 关闭释放Camera
     */
    void releaseCamera();

    /**
     * SurfaceView
     * 开启预览
     *
     * @param surfaceHolder
     */
    void startPreview(SurfaceHolder surfaceHolder);

    /**
     * TextureView
     * 开启预览
     *
     * @param surfaceTexture
     */
    void startPreview(SurfaceTexture surfaceTexture);

    /**
     * 停止预览
     */
    void stopPreview();

    /**
     * 设置CameraID
     * 0 彩色摄像头
     * 1 黑白摄像头
     * 2 证件摄像头
     *
     * @param cameraId
     */
    void setCameraId(int cameraId);

    /**
     * 获取当前CameraID
     *
     * @return
     */
    int getCameraId();

    /**
     * Camera是否打开
     *
     * @return
     */
    boolean isOpen();

    /**
     * 获取当前预览尺寸
     *
     * @return
     */
    Size getPreviewSize();

    /**
     * 设置预览尺寸
     *
     * @param size
     */
    void setPreviewSize(Size size);

    /**
     * 获取Camera预览数据方法？
     *
     * @return
     */
    int getOrientation();

    /**
     * 获取Camera预览方向？
     *
     * @return
     */
    int getDisplayOrientation();

    /**
     * 设置摄像头回调
     *
     * @param cameraCallback
     */
    void setCameraCallback(CameraCallback cameraCallback);

    /**
     * 设置预览数据回调
     *
     * @param previewBufferCallback
     */
    void addPreviewBufferCallback(PreviewBufferCallback previewBufferCallback);

    /**
     * 拍照接口
     *
     * @param pictureBufferCallback
     */
    void takePicture(PictureBufferCallback pictureBufferCallback);

    /**
     * 切换摄像头
     */
    void switchCamera();
}
