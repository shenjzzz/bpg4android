package com.bpgdecoder.library;

import android.graphics.Bitmap;

import androidx.annotation.Keep;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

@Keep
public class BpgDecoder {

    static {
        System.loadLibrary("bpgDecoder");
    }

    public static Bitmap decode(InputStream inputStream) {

        try (ByteArrayOutputStream bos = new ByteArrayOutputStream()) {
            byte[] array = new byte[512];
            int size;
            while ((size = inputStream.read(array)) != -1) {
                bos.write(array, 0, size);
            }
            return decode(bos.toByteArray());
        } catch (IOException e) {
            e.printStackTrace();
        }

        return null;
    }

    public static Bitmap decode(byte[] data) {
        return nativeDecode(data);
    }

    private static native Bitmap nativeDecode(byte[] data);
}
