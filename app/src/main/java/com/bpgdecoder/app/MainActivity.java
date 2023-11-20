package com.bpgdecoder.app;

import android.os.Bundle;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

import com.bpgdecoder.library.BpgDecoder;

import java.io.IOException;
import java.io.InputStream;


public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        ImageView imageView = findViewById(R.id.imageView);

        try (InputStream is = getAssets().open("lena512color.bpg")) {
            imageView.setImageBitmap(BpgDecoder.decode(is));

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}