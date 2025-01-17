package com.ndk.day31;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.ndk.day31.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {


    private static final String TAG = "MainActivity";
    private ActivityMainBinding binding;
    private Bitmap bitmap;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.card2);

        binding.ivCard.setImageBitmap(bitmap);

        String path = Environment.getExternalStorageDirectory().getAbsolutePath();
        Log.d(TAG, "onCreate: " + path);

    }

    public void onOcr(View view) {
        binding.ivCard2.setImageBitmap(null);
        String cardNo = BankCardOcr.cardOcr(bitmap);
        binding.ivCard2.setImageBitmap(bitmap);
        binding.tvCardNo.setText(cardNo);
    }
}