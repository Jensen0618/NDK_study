package com.jensen.lib_camera.camera.callback;

public interface CameraCallback {
    void onOpen();

    void onOpenError(int error, String msg);

    /**
     * 开始预览回调
     * @param previewWidth 预览宽度
     * @param previewHeight 预览高度
     */
    void onPreview(int previewWidth, int previewHeight);

    void onPreviewError(int error, String msg);

    void onClose();
}
