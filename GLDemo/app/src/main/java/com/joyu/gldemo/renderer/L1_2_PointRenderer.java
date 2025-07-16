package com.joyu.gldemo.renderer;

import android.content.Context;
import android.opengl.GLES20;

import com.joyu.gldemo.BufferUtil;

import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class L1_2_PointRenderer extends BaseRenderer {
    private static final String VERTEX_SHADER = "\n" +
            "attribute vec4 a_Position;" +
            "void main(){" +
            "    gl_Position = a_Position;" +
            "    gl_PointSize = 40.0;" +
            "}";
    private static final String FRAGMENT_SHADER = "\n" +
            "precision mediump float;" +
            "uniform vec4 u_Color;" +
            "void main(){" +
            "    gl_FragColor = u_Color;" +
            "}";
    private static float[] pointData = {0f, 0f};
    private static final int POSITION_COMPONENT_COUNT = 2;
    private static final int BYTES_PER_FLOAT = 4;
    private FloatBuffer vertexData;
    private int uColorLocation;



    public L1_2_PointRenderer(Context ctx) {
        super(ctx);
        vertexData = BufferUtil.createFloatBuffer(pointData);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        makeProgram(VERTEX_SHADER, FRAGMENT_SHADER);
        GLES20.glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        int aPosition = getAttribute("a_Position");
        uColorLocation = getUniform("u_Color");

        vertexData.position(0);
        GLES20.glVertexAttribPointer(aPosition, POSITION_COMPONENT_COUNT, GLES20.GL_FLOAT, false, 0, vertexData);
        GLES20.glEnableVertexAttribArray(aPosition);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        super.onSurfaceChanged(gl, width, height);
        GLES20.glViewport(0, 0, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
        GLES20.glUniform4f(uColorLocation, 1.0f, 0f, 0f, 1.0f);
        GLES20.glDrawArrays(GLES20.GL_POINTS, 0, 1);
    }
}
