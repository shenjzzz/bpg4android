#include <jni.h>
#include <malloc.h>
#include "decoder/decoder.h"

extern "C"
JNIEXPORT jobject JNICALL
decodeNative(JNIEnv *env, jclass clazz, jbyteArray jData) {
    if (jData == nullptr) {
        return nullptr;
    }
    jboolean isCopy = JNI_FALSE;
    jbyte *data = env->GetByteArrayElements(jData, &isCopy);
    jsize size = env->GetArrayLength(jData);

    BPGDecoderContext *context = nullptr;
    int width, height;
    if (prepare(&context, &width, &height, (uint8_t *) (data), size) < 0) {
        close_decoder(&context);
        return nullptr;
    }

    logD("BPG width = %d, height = %d", width, height);

    uint8_t *rgba = (uint8_t *) (malloc(width * height * PIXEL_SIZE));
    if (decode(&context, rgba, width, height) < 0) {
        close_decoder(&context);
        return nullptr;
    }

    close_decoder(&context);
    jobject bitmap = createBitmap(env, rgba, width, height);
    free(rgba);
    env->ReleaseByteArrayElements(jData, data, 0);
    return bitmap;
}


static const JNINativeMethod gMethods[] = {
        {"nativeDecode", "([B)Landroid/graphics/Bitmap;", (jobject) decodeNative}
};

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;
    if ((vm->GetEnv((void **) &env, JNI_VERSION_1_4)) != JNI_OK) {
        return JNI_FALSE;
    }
    jclass clazz = env->FindClass("com/bpgdecoder/library/BpgDecoder");
    if (clazz == nullptr) {
        return JNI_FALSE;
    }
    if ((env->RegisterNatives(clazz, gMethods, 1) < 0)) {
        return JNI_FALSE;
    }
    return JNI_VERSION_1_4;
}