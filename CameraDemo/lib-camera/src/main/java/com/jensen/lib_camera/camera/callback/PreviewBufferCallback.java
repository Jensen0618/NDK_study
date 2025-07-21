package com.jensen.lib_camera.camera.callback;

/**
 * 摄像头预览数据回调
 */
public interface PreviewBufferCallback {
    void onPreviewBufferFrame(byte[] data, int width, int height, YUVFormat format);
}
