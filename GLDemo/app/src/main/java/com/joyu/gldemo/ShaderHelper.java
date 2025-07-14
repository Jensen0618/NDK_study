package com.joyu.gldemo;

import android.opengl.GLES20;
import android.util.Log;

public class ShaderHelper {
    private static final String TAG = ShaderHelper.class.getSimpleName();

    public static int compileVertexShader(String source) {
        return compileShader(GLES20.GL_VERTEX_SHADER, source);
    }

    public static int compileFragmentShader(String source) {
        return compileShader(GLES20.GL_FRAGMENT_SHADER, source);
    }


    private static int compileShader(int type, String source) {
        int shader = GLES20.glCreateShader(type);
        if (shader == 0) {
            Log.w(TAG, "compileShader: Could not create new shader.");
            return 0;
        }
        GLES20.glShaderSource(shader, source);
        GLES20.glCompileShader(shader);

        int[] compileStatus = new int[1];
        GLES20.glGetShaderiv(shader, GLES20.GL_COMPILE_STATUS, compileStatus, 0);
        Log.d(TAG, "compileShader: Result of compiling source" + "\n" + source + "\n:" + GLES20.glGetShaderInfoLog(shader));

        if (compileStatus[0] == 0) {
            GLES20.glDeleteShader(shader);
            Log.w(TAG, "compileShader: Compilation of shader failed");
            return 0;
        }
        return shader;
    }

    /**
     * 创建OpenGL程序：通过链接顶点着色器、片段着色器
     *
     * @param vertexShaderId   顶点着色器ID
     * @param fragmentShaderId 片段着色器ID
     * @return OpenGL程序ID
     */
    public static int linkProgram(int vertexShaderId, int fragmentShaderId) {
        // 1.创建一个OpenGL程序对象
        int programId = GLES20.glCreateProgram();
        // 2.获取创建状态
        if (programId == 0) {
            Log.w(TAG, "linkProgram: Counld not create new program");
            return 0;
        }
        // 3.将顶点着色器关联到OpenGL程序对象
        GLES20.glAttachShader(programId, vertexShaderId);
        // 3.将片段着色器关联到OpenGL程序对象
        GLES20.glAttachShader(programId, fragmentShaderId);
        // 4.将两个做四起链接到OpenGL程序对象
        GLES20.glLinkProgram(programId);
        // 5.获取连接状态
        // OpenGL将想要获取的值放入长度为1的数组
        int[] linkStatus = new int[1];
        GLES20.glGetProgramiv(programId, GLES20.GL_LINK_STATUS, linkStatus, 0);
        Log.d(TAG, "linkProgram: Results of linking program:\n" + GLES20.glGetProgramInfoLog(programId));
        // 6.验证链接状态
        if (linkStatus[0] == 0) {
            GLES20.glDeleteProgram(programId);
            Log.d(TAG, "linkProgram: Linking of program failed.");
            return 0;
        }

        return programId;
    }

    public static boolean validateProgram(int programId) {
        GLES20.glValidateProgram(programId);

        int[] validateStatus = new int[1];
        // 通过API获取程序的验证状态
        GLES20.glGetProgramiv(programId, GLES20.GL_VALIDATE_STATUS, validateStatus, 0);
        Log.d(TAG, "validateProgram: Results of validating program: " + validateStatus[0]
                + "\nLog:" + GLES20.glGetProgramInfoLog(programId));

        return validateStatus[0] != 0;
    }
}
