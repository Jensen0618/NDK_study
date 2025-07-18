package com.benhero.glstudio.renderer

import android.content.Context
import android.opengl.GLES20
import android.opengl.GLSurfaceView.Renderer
import com.benhero.glstudio.util.LoggerConfig
import com.benhero.glstudio.util.ShaderHelper
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * 基础概念 + 点 的绘制
 *
 * @author Benhero
 */
class L1_1_PointRenderer(private val mContext: Context) : Renderer {
    private companion object {
        //关键字 概念：
        // 1. uniform 由外部程序传递给 shader，就像是C语言里面的常量，shader 只能用，不能改；
        // 2. attribute 是只能在 vertex shader 中使用的变量；
        // 3. varying 变量是 vertex shader 和 fragment shader 之间做数据传递用的。
        // 更多说明：http://blog.csdn.net/jackers679/article/details/6848085
        /**
         * 顶点着色器：之后定义的每个都会传1次给顶点着色器
         */
        private val VERTEX_SHADER = """
                // vec4：4个分量的向量：x、y、z、w
                attribute vec4 a_Position;
                void main()
                {
                // gl_Position：GL中默认定义的输出变量，决定了当前顶点的最终位置
                    gl_Position = a_Position;
                // gl_PointSize：GL中默认定义的输出变量，决定了当前顶点的大小
                    gl_PointSize = 40.0;
                }
        """

        /**
         * 片段着色器
         * 显式声明: OpenGL ES 规范要求在片段着色器中为浮点类型声明一个默认精度，
         * 或者为每个浮点变量单独指定精度。 如果没有默认精度声明， 并且某个浮点变量没有单独指定精度， 着色器可能无法编译。
         * 代码中的含义: precision mediump float; 这行代码告诉 GLSL 编译器，在此之后的片段着色器代码中，
         * 任何未明确指定精度的 float 类型变量（包括 vec2, vec3, vec4, mat2, mat3, mat4 等基于浮点数的类型）都应该使用中等精度 (mediump)。
         */
        private val FRAGMENT_SHADER = """
                // precision关键字用于定义后续浮点数据类型的默认精度；有lowp、mediump、highp 三种，但只有部分硬件支持片段着色器使用highp。(顶点着色器默认highp)
                precision mediump float;
                uniform vec4 u_Color;
                void main()
                {
                // gl_FragColor：GL中默认定义的输出变量，决定了当前片段的最终颜色
                   gl_FragColor = u_Color;
                }
        """

        //对应着着色器中定义的变量
        private val U_COLOR = "u_Color"
        private val A_POSITION = "a_Position"

        /**
         * 顶点数据数组
         */
        private val POINT_DATA = floatArrayOf(
            // 点的x,y坐标（x，y各占1个分量）
            0f, 0f,
            1f, 0.5f
        )

        /**
         * 每个顶点数据关联的分量个数：当前案例只有x、y，故为2
         */
        private val POSITION_COMPONENT_COUNT = 2

        /**
         * Float类型占4Byte
         */
        private val BYTES_PER_FLOAT = 4
    }

    private var mProgram: Int = 0

    /**
     * 顶点坐标数据缓冲区
     */
    private val mVertexData: FloatBuffer

    /**
     * 颜色uniform在OpenGL程序中的索引
     */
    private var uColorLocation: Int = 0

    /**
     * 顶点坐标在OpenGL程序中的索引
     */
    private var aPositionLocation: Int = 0

    init {
        // 分配一个块Native内存，用于与GL通讯传递。(我们通常用的数据存在于Dalvik的内存中，1.无法访问硬件；2.会被垃圾回收)
        mVertexData = ByteBuffer
            // 分配顶点坐标分量个数 * Float占的Byte位数
            .allocateDirect(POINT_DATA.size * BYTES_PER_FLOAT)
            // 按照本地字节序排序
            .order(ByteOrder.nativeOrder())
            // Byte类型转Float类型
            .asFloatBuffer()

        // 将Dalvik的内存数据复制到Native内存中
        mVertexData.put(POINT_DATA)
    }


    override fun onSurfaceCreated(glUnused: GL10, config: EGLConfig) {
        // 设置刷新屏幕时候使用的颜色值,顺序是RGBA，值的范围从0~1。GLES20.glClear调用时使用该颜色值。
        GLES20.glClearColor(1.0f, 1.0f, 1.0f, 1.0f)
        // 步骤1：编译顶点着色器
        val vertexShader = ShaderHelper.compileVertexShader(VERTEX_SHADER)
        // 步骤2：编译片段着色器
        val fragmentShader = ShaderHelper.compileFragmentShader(FRAGMENT_SHADER)

        // 步骤3：将顶点着色器、片段着色器进行链接，组装成一个OpenGL程序
        mProgram = ShaderHelper.linkProgram(vertexShader, fragmentShader)

        if (LoggerConfig.ON) {
            ShaderHelper.validateProgram(mProgram)
        }

        // 步骤4：通知OpenGL开始使用该程序
        GLES20.glUseProgram(mProgram)

        // 步骤5：获取颜色Uniform在OpenGL程序中的索引
        uColorLocation = GLES20.glGetUniformLocation(mProgram, U_COLOR)

        // 步骤6：获取顶点坐标属性在OpenGL程序中的索引
        aPositionLocation = GLES20.glGetAttribLocation(mProgram, A_POSITION)

        // 将缓冲区的指针移动到头部，保证数据是从最开始处读取
        mVertexData.position(0)
        // 步骤7：关联顶点坐标属性（通过坐标索引aPositionLocation）和缓存数据（mVertexData，mVertexData在init方法中完成数据添加）
        // 1. 位置索引；
        // 2. 每个顶点属性需要关联的分量个数(必须为1、2、3或者4。初始值为4。)；
        // 3. 数据类型；
        // 4. 指定当被访问时，固定点数据值是否应该被归一化(GL_TRUE)或者直接转换为固定点值(GL_FALSE)(只有使用整数数据时)
        // 5. 指定连续顶点属性之间的偏移量。如果为0，那么顶点属性会被理解为：它们是紧密排列在一起的。初始值为0。
        // 6. 数据缓冲区
        GLES20.glVertexAttribPointer(
            aPositionLocation, POSITION_COMPONENT_COUNT, GLES20.GL_FLOAT,
            false, 0, mVertexData
        )

        // 步骤8：通知GL程序使用指定的顶点属性索引
        GLES20.glEnableVertexAttribArray(aPositionLocation)
    }

    override fun onSurfaceChanged(glUnused: GL10, width: Int, height: Int) {
        // Set the OpenGL viewport to fill the entire surface.
        GLES20.glViewport(0, 0, width, height)
    }

    override fun onDrawFrame(glUnused: GL10) {
        // 步骤1：使用glClearColor设置的颜色，刷新Surface
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT)

        // 步骤2：更新u_Color的值，即更新画笔颜色；用的是索引为u_Color的uniform变量；
        GLES20.glUniform4f(uColorLocation, 0.0f, 0.0f, 1.0f, 1.0f)
        // 步骤3：使用数组绘制图形：1.绘制的图形类型；2.从顶点数组读取的起点；3.从顶点数组读取的顶点个数（数组长达/分量个数）
        GLES20.glDrawArrays(GLES20.GL_POINTS, 0, POINT_DATA.size / POSITION_COMPONENT_COUNT)
    }
}