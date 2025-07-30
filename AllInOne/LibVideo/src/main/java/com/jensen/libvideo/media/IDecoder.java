package com.jensen.libvideo.media;

import android.media.MediaFormat;

public interface IDecoder extends Runnable {
    void pause();

    void goOn();

    /**
     * 跳转到指定位置
     *
     * @param pos
     * @return 实际帧的时间
     */
    long seekTo(long pos);

    /**
     * 跳转到指定位置并播放
     *
     * @param pos
     * @return 实际帧的时间
     */
    long seekAndPlay(long pos);

    void stop();

    boolean isDecoding();

    boolean isSeeking();

    boolean isStop();

    /**
     * 设置状态监听器
     *
     * @param listener
     */
    void setStateListener(IDecoderStateListener listener);

    /**
     * 获取视频宽度
     *
     * @return
     */
    int getWidth();

    /**
     * 获取视频高度
     *
     * @return
     */
    int getHeight();

    /**
     获取视频长度
     * @return
     */
    long getDuration();

    /**
     获取视频旋转角度
     * @return
     */
    int getRotationAngle();

    /**获取音视频格式参数
     * @return
     */
    MediaFormat getMediaFormat();

    /**获取媒体轨道
     * @return
     */
    int getTrack();

    /**
     获取解码文件路径
     * @return
     */
    String getFilePath();
}
