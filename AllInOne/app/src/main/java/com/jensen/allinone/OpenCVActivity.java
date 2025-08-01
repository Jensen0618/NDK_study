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

        mIvSrc.setImageResource(R.mipmap.photo);

        Bitmap src = BitmapFactory.decodeResource(getResources(), R.mipmap.photo);
        Bitmap dst = BitmapUtil.cvtColor(src);
        mIvDst.setImageBitmap(dst);

    }
}