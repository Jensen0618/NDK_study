package com.jensen.allinone;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

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

        Bitmap src = BitmapFactory.decodeResource(getResources(), R.mipmap.photo2, opts);

//        Bitmap dst = BitmapUtil.cvtColor(src);//使用ColorMatrix转换
//        Bitmap dst = BitmapUtil.cvtColorWithPx2(src);//修改像素
//        mIvDst.setImageBitmap(dst);


        BitmapUtil.cvtColorNative(src);
        mIvDst.setImageBitmap(src);

    }
}