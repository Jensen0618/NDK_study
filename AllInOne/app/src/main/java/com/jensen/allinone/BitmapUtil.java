package com.jensen.allinone;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.ColorFilter;
import android.graphics.ColorMatrix;
import android.graphics.ColorMatrixColorFilter;
import android.graphics.Paint;

public class BitmapUtil {
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
        ColorMatrix colorMatrix = new ColorMatrix();
        colorMatrix.setSaturation(0);//设置饱和度，0为灰度图片

        ColorMatrixColorFilter filter = new ColorMatrixColorFilter(colorMatrix);
        paint.setColorFilter(filter);

        canvas.drawBitmap(src, 0, 0, paint);


        return temp;
    }
}
