#ifdef __ANDROID__

#include "../log.h"

#define PIXEL_SIZE 4

extern "C" {
jobject createBitmap(JNIEnv *env, uint8_t *rgba, int width, int height);
}
#endif //__ANDROID__