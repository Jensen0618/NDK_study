package com.jensen.lib_camera.camera.view.base;

import com.jensen.lib_camera.camera.ICameraManager;

public interface BaseCameraView {
    ICameraManager getCameraManager();

    void onResume();

    void onPause();

    void onDestroy();
}
