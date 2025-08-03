package com.jensen.allinone;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.ColorFilter;
import android.graphics.ColorMatrix;
import android.graphics.ColorMatrixColorFilter;
import android.graphics.Paint;

public class BitmapUtil {
    static {
        System.loadLibrary("allinone");
    }

    /**
     * 使用矩阵转换图片颜色
     *
     * @param src
     * @return
     */
    public static Bitmap cvtColor(Bitmap src) {
        //复制一份空白的bitmap
        Bitmap temp = Bitmap.createBitmap(src.getWidth(), src.getHeight(), src.getConfig());
        //创建画布
        Canvas canvas = new Canvas(temp);
        Paint paint = new Paint();
        //启用颜色抖动，牺牲一定的性能用于优化高精度颜色向低精度设备输出时的效果
        paint.setDither(true);
        //启用抗锯齿 anti-alias 使边缘光滑；消除锯齿
        paint.setAntiAlias(true);

        //颜色矩阵
//        ColorMatrix colorMatrix = new ColorMatrix();
//        colorMatrix.setSaturation(0);//设置饱和度，0为灰度图片

        ColorMatrix colorMatrix = new ColorMatrix(new float[]{
                //底片
//                -1, 0, 0, 0, 255,
//                0, -1, 0, 0, 255,
//                0, 0, -1, 0, 255,
//                0, 0, 0, 1, 0,
                //复古
//                1 / 2f, 1 / 2f, 1 / 2f, 0, 0,
//                1 / 3f, 1 / 3f, 1 / 3f, 0, 0,
//                1 / 4f, 1 / 4f, 1 / 4f, 0, 0,
//                0, 0, 0, 1, 0,
                //红绿反色
                0, 1f, 0, 0, 0,
                1f, 0, 0, 0, 0,
                0, 0, 1f, 0, 0,
                0, 0, 0, 1f, 0,
        });


        ColorMatrixColorFilter filter = new ColorMatrixColorFilter(colorMatrix);
        paint.setColorFilter(filter);

        canvas.drawBitmap(src, 0, 0, paint);


        return temp;
    }


    /**
     * 修改像素的颜色
     *
     * @param src
     * @return dst
     */
    public static Bitmap cvtColorWithPx(Bitmap src) {
        Bitmap dst = Bitmap.createBitmap(src.getWidth(), src.getHeight(), src.getConfig());

        //新建数组，大小为图片的像素数量
        int[] pixels = new int[src.getWidth() * src.getHeight()];
        //获取像素数组
        //stride：两行像素的间隔，一般是图片宽度
        src.getPixels(pixels, 0, src.getWidth(), 0, 0, src.getWidth(), src.getHeight());
        for (int i = 0; i < pixels.length; i++) {
            int pixel = pixels[i];
            //
            int a = pixel >> 24 & 0xff;
            int r = pixel >> 16 & 0xff;
            int g = pixel >> 8 & 0xff;
            int b = pixel & 0xff;

            int gray = (int) (0.11 * b + 0.59 * g + 0.30 * r);
            pixel = a << 24 | gray << 16 | gray << 8 | b;
            pixels[i] = pixel;
        }

        dst.setPixels(pixels, 0, dst.getWidth(), 0, 0, dst.getWidth(), dst.getHeight());

        return dst;
    }

    /**
     * 修改像素的颜色
     * 复用bitmap
     *
     * @param src
     * @return 修改后的src
     */
    public static Bitmap cvtColorWithPx2(Bitmap src) {

        //新建数组，大小为图片的像素数量
        int[] pixels = new int[src.getWidth() * src.getHeight()];
        //获取像素数组
        //stride：两行像素的间隔，一般是图片宽度
        src.getPixels(pixels, 0, src.getWidth(), 0, 0, src.getWidth(), src.getHeight());
        for (int i = 0; i < pixels.length; i++) {
            int pixel = pixels[i];
            //  ARGB_8888是这样的
            int a = pixel >> 24 & 0xff;
            int r = pixel >> 16 & 0xff;
            int g = pixel >> 8 & 0xff;
            int b = pixel & 0xff;

            int gray = (int) (0.11 * b + 0.59 * g + 0.30 * r);
            pixel = a << 24 | gray << 16 | gray << 8 | gray;
            pixels[i] = pixel;
        }

        src.setPixels(pixels, 0, src.getWidth(), 0, 0, src.getWidth(), src.getHeight());

        return src;
    }

    /**
     * C++风格一般不返回对象，而是返回int表示结果
     * @param src
     * @return
     */
    public native static int cvtColorNative(Bitmap src);

}
