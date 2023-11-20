

#ifdef __ANDROID__
#include <jni.h>
#include <android/bitmap.h>
#include <cstring>

#include "utils.h"

extern "C" {
jobject createBitmap(JNIEnv *env, uint8_t *rgba, int width, int height) {

    jclass configCls = env->FindClass("android/graphics/Bitmap$Config");
    jfieldID argb8888Field = env->GetStaticFieldID(configCls, "ARGB_8888",
                                                   "Landroid/graphics/Bitmap$Config;");
    jobject argb8888 = env->GetStaticObjectField(configCls, argb8888Field);

    jclass bitmapCls = env->FindClass("android/graphics/Bitmap");
    jmethodID createBitmapMethod = env->GetStaticMethodID(bitmapCls, "createBitmap",
                                                          "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
    jobject bitmap = env->CallStaticObjectMethod(bitmapCls, createBitmapMethod, width, height,
                                                 argb8888);

    AndroidBitmapInfo info;
    void *pixels = nullptr;

    try {
        logD("createBitmap");
        if (AndroidBitmap_getInfo(env, bitmap, &info) < 0) {
            return nullptr;
        }
        if (AndroidBitmap_lockPixels(env, bitmap, &pixels) < 0) {
            return nullptr;
        }
        if (!pixels) {
            return nullptr;
        }
        memcpy(pixels, rgba, width * height * PIXEL_SIZE);
        AndroidBitmap_unlockPixels(env, bitmap);
        return bitmap;
    } catch (...) {
        AndroidBitmap_unlockPixels(env, bitmap);
        logE("createBitmap caught unknown exception (...)");
        return nullptr;
    }
}

} // extern "C"

#endif //__ANDROID__
