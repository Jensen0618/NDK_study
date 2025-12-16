package com.jensen.allinone;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

import com.jensen.libopencv.CVType;
import com.jensen.libopencv.Mat;
import com.jensen.libopencv.OpenCVUtil;

public class OpenCVActivity extends AppCompatActivity {

    private ImageView mIvSrc;
    private ImageView mIvDst;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_opencv);
        mIvSrc = findViewById(R.id.iv_src);
        mIvDst = findViewById(R.id.iv_dst);

        mIvSrc.setImageResource(R.mipmap.photo2);

        //在原bitmap上修改，复用bitmap，需用设置inMutable属性为true
        BitmapFactory.Options opts = new BitmapFactory.Options();
        opts.inMutable = true;
//        opts.inPreferredConfig = Bitmap.Config.RGB_565;

        Bitmap src = BitmapFactory.decodeResource(getResources(), R.mipmap.photo2, opts);

//        Bitmap dst = BitmapUtil.cvtColor(src);//使用ColorMatrix转换
//        Bitmap dst = BitmapUtil.cvtColorWithPx2(src);//修改像素
//        mIvDst.setImageBitmap(dst);


//        BitmapUtil.cvtColorNative(src);
//        mIvDst.setImageBitmap(src);

//        OpenCVUtil.mirrorNative(src);


        //ndk封装C++类
        Mat matSrc = new Mat(src.getHeight(), src.getWidth(), CVType.CV_8UC4);
        OpenCVUtil.bitmap2mat(src, matSrc.nativePtr);

        int size = 3;
        Mat kennel = new Mat(size, size, CVType.CV_32FC1);
        kennel.put(0, 0, 0);
        kennel.put(0, 1, -1);
        kennel.put(0, 2, 0);
        kennel.put(1, 0, -1);
        kennel.put(1, 1, 5);
        kennel.put(1, 2, -1);
        kennel.put(2, 0, 0);
        kennel.put(2, 1, -1);
        kennel.put(2, 2, 0);

        Mat matDst = new Mat();
        OpenCVUtil.filter2D(matSrc, matDst, kennel);

        OpenCVUtil.mat2bitmap(matDst.nativePtr, src);


        mIvDst.setImageBitmap(src);


    }
}