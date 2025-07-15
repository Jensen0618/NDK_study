package com.joyu.gldemo;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.View;
import android.widget.RelativeLayout;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.joyu.gldemo.renderer.L1_1_PointRenderer;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    private Context context;
    private GLSurfaceView glSurfaceView;
    private RecyclerView recyclerView;
    private RelativeLayout root;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        context = this;
        setContentView(R.layout.activity_main);

        root = findViewById(R.id.root);
        recyclerView = findViewById(R.id.rv);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));

        ArrayList<HomeItem> homeItems = new ArrayList<>();
        homeItems.add(new HomeItem("L1_1_基础框架", L1_1_PointRenderer.class));

        HomeAdapter adapter = new HomeAdapter(homeItems);
        adapter.setOnItemClickListener(new OnItemClickListener() {
            @Override
            public void onItemClick(View view, int position) {
                glSurfaceView = new GLSurfaceView(context);
                root.addView(glSurfaceView);
                glSurfaceView.setEGLContextClientVersion(2);
                glSurfaceView.setEGLConfigChooser(false);
                Class renderClass = homeItems.get(position).renderClass;
                try {
                    GLSurfaceView.Renderer renderer = (GLSurfaceView.Renderer) renderClass.newInstance();
                    glSurfaceView.setRenderer(renderer);
                    glSurfaceView.setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
                } catch (InstantiationException e) {
                    e.printStackTrace();
                } catch (IllegalAccessException e) {
                }
            }
        });
        recyclerView.setAdapter(adapter);


    }

    @Override
    protected void onResume() {
        super.onResume();
        if (glSurfaceView != null) {
            glSurfaceView.onResume();
        }
    }

    @Override
    protected void onPause() {
        if (glSurfaceView != null) {
            glSurfaceView.onPause();
        }
        super.onPause();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }
}