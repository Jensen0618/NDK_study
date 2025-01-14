package com.ndk.day05;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.ndk.day05.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {



    private ActivityMainBinding binding;

    private FaceUtil mFaceUtil;
    private Bitmap mBpFace;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        mBpFace = BitmapFactory.decodeResource(getResources(), R.mipmap.images);
        binding.iv.setImageBitmap(mBpFace);
        mFaceUtil = new FaceUtil();

    }

    public void onImage(View view) {

        mFaceUtil.dectFace(mBpFace);
        binding.iv.setImageBitmap(mBpFace);
    }
}