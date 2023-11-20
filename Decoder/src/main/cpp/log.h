#include <android/log.h>

#ifndef DEFAULT_LOG_TAG
#define DEFAULT_LOG_TAG "native_libbpg"
#define logV(...) __android_log_print(ANDROID_LOG_VERBOSE, DEFAULT_LOG_TAG, __VA_ARGS__)
#define logD(...) __android_log_print(ANDROID_LOG_DEBUG, DEFAULT_LOG_TAG, __VA_ARGS__)
#define logI(...) __android_log_print(ANDROID_LOG_INFO, DEFAULT_LOG_TAG, __VA_ARGS__)
#define logW(...) __android_log_print(ANDROID_LOG_WARN, DEFAULT_LOG_TAG, __VA_ARGS__)
#define logE(...) __android_log_print(ANDROID_LOG_ERROR, DEFAULT_LOG_TAG, __VA_ARGS__)
#endif