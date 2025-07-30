package com.jensen.lib_camera.gles.filter;

public interface AFilter {
    void surfaceCreated();

    void surfaceChanged(int width, int height);

    int draw(int textureId, float[] matrix);

    void release();
}
