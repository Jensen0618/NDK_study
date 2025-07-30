package com.jensen.lib_camera.camera.callback;

public interface CameraCallback {
    void onOpen();

    void onOpenError(int error, String msg);

    /**
     * 开始预览回调，在mCamera.startPreview()之后调用
     * @param previewWidth 相机实际设置的预览宽度
     * @param previewHeight 相机实际设置的预览高度
     */
    void onPreview(int previewWidth, int previewHeight);

    void onPreviewError(int error, String msg);

    void onClose();
}
