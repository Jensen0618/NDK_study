package com.ndk.day35;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.ndk.day35.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'day35' library on application startup.
    static {
        System.loadLibrary("day35");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'day35' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}