package com.joyu.gldemo.renderer;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.util.Log;


import com.joyu.gldemo.ShaderHelper;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class L1_1_PointRenderer implements GLSurfaceView.Renderer {
    private static final String TAG = L1_1_PointRenderer.class.getSimpleName();
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

    private static final String U_COLOR = "u_Color";
    private static final String A_POSITION = "a_Position";

    private float[] pointData = {0f, 0f};
    private static final int POSITION_COMPONENT_COUNT = 2;
    private static final int BYTES_PER_FLOAT = 4;
    private int program;
    private FloatBuffer vertexData;
    private int uColor;
    private int aPosition;

    public L1_1_PointRenderer(Context ctx) {
        vertexData = ByteBuffer.allocateDirect(pointData.length * BYTES_PER_FLOAT)
                .order(ByteOrder.nativeOrder())
                .asFloatBuffer()
                .put(pointData);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        Log.d(TAG, "onSurfaceCreated: ");
        // 设置刷新屏幕时候使用的颜色值,顺序是RGBA，值的范围从0~1。GLES20.glClear调用时使用该颜色值。
        GLES20.glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        // 步骤1：编译顶点着色器
        int vertexShader = ShaderHelper.compileVertexShader(VERTEX_SHADER);
        // 步骤2：编译片段着色器
        int fragmentShader = ShaderHelper.compileFragmentShader(FRAGMENT_SHADER);
        // 步骤3：将顶点着色器、片段着色器进行链接，组装成一个OpenGL程序
        program = ShaderHelper.linkProgram(vertexShader, fragmentShader);
        // 验证OpenGL程序可用性
        ShaderHelper.validateProgram(program);
        // 步骤4：通知OpenGL开始使用该程序
        GLES20.glUseProgram(program);
        // 步骤5：获取程序中的属性位置
        aPosition = GLES20.glGetAttribLocation(program, A_POSITION);
        // 步骤6:获取颜色Uniform在OpenGL程序中的索引
        uColor = GLES20.glGetUniformLocation(program, U_COLOR);
        // 将缓冲区的指针移动到头部，保证数据是从最开始处读取
        vertexData.position(0);
        // 步骤7：关联顶点坐标属性（通过坐标索引aPositionLocation）和缓存数据（mVertexData，mVertexData在init方法中完成数据添加）
        // 1. 位置索引；
        // 2. 每个顶点属性需要关联的分量个数(必须为1、2、3或者4。初始值为4。)；
        // 3. 数据类型；
        // 4. 指定当被访问时，固定点数据值是否应该被归一化(GL_TRUE)或者直接转换为固定点值(GL_FALSE)(只有使用整数数据时)
        // 5. 指定连续顶点属性之间的偏移量。如果为0，那么顶点属性会被理解为：它们是紧密排列在一起的。初始值为0。
        // 6. 数据缓冲区
        GLES20.glVertexAttribPointer(aPosition, POSITION_COMPONENT_COUNT, GLES20.GL_FLOAT, false, 0, vertexData);
        // 步骤8:通知GL程序使用指定的顶点属性索引
        GLES20.glEnableVertexAttribArray(aPosition);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.d(TAG, "onSurfaceChanged: ");
        GLES20.glViewport(0, 0, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        Log.d(TAG, "onDrawFrame: ");
        // 步骤1：使用glClearColor设置的颜色，刷新Surface
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
        // 步骤2：更新u_Color的值，即更新画笔颜色；用的是索引为u_Color的uniform变量；
        GLES20.glUniform4f(uColor,0.0f,0.0f,1.0f,1.0f);
        GLES20.glDrawArrays(GLES20.GL_POINTS,0,pointData.length/POSITION_COMPONENT_COUNT);
    }
}
