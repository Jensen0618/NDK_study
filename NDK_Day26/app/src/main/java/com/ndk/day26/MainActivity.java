package com.ndk.day26;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.ndk.day26.databinding.ActivityMainBinding;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    // Used to load the 'day26' library on application startup.
    static {
        System.loadLibrary("day26");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        Person[] oldPersons = new Person[10];
        for (int i = 0; i < oldPersons.length; i++) {
            oldPersons[i] = new Person("Jensen", 20+i);
        }

        Person[] newPersons = new Person[10];

        arraycopy(oldPersons, 0, newPersons, 0, oldPersons.length);

        for (int i = 0; i < newPersons.length; i++) {
            Log.d(TAG, "onCreate: " + newPersons[i].toString());
        }


    }

    public static native void arraycopy(Object src, int srcPos,
                                        Object dest, int destPos,
                                        int length);


}