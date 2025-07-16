package com.joyu.gldemo.renderer;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;

import com.joyu.gldemo.ShaderHelper;

import java.nio.ByteBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public abstract class BaseRenderer implements GLSurfaceView.Renderer {
    Context context;
    protected int program;
    protected int outputWidth;
    protected int outputHeight;
    public RendererCallback rendererCallback;
    public boolean isReadCurrentFrame;

    /**
     * 渲染完毕回调接口
     */
    public interface RendererCallback {
        void onRendererDone(ByteBuffer buffer, int width, int height);
    }

    public BaseRenderer(Context ctx) {
        context = ctx;
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        outputWidth = width;
        outputHeight = height;
    }

    /**
     * 创建OpenGL程序对象
     *
     * @param vertexShader   顶点着色器代码
     * @param fragmentShader 片段着色器代码
     */
    protected void makeProgram(String vertexShader, String fragmentShader) {
        // 步骤1：编译顶点着色器
        int vertexShaderId = ShaderHelper.compileVertexShader(vertexShader);
        // 步骤2：编译片段着色器
        int fragmentShaderId = ShaderHelper.compileFragmentShader(fragmentShader);
        // 步骤3：将顶点着色器、片段着色器进行链接，组装成一个OpenGL程序
        program = ShaderHelper.linkProgram(vertexShaderId, fragmentShaderId);
        // 验证OpenGL程序可用性
        ShaderHelper.validateProgram(program);
        // 步骤4：通知OpenGL开始使用该程序
        GLES20.glUseProgram(program);
    }

    /**
     * 获取uniform在OpenGL程序中的索引
     *
     * @param name 变量名
     * @return
     */
    protected int getUniform(String name) {
        return GLES20.glGetUniformLocation(program, name);
    }

    /**
     * 获取attribute在OpenGL程序中的索引
     *
     * @param name 变量名
     * @return
     */
    protected int getAttribute(String name) {
        return GLES20.glGetAttribLocation(program, name);
    }

    protected void onReadPixel(int x, int y, int width, int height) {

    }

}
