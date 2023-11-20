extern "C" {
#include "../libbpg/libbpg.h"
}

#include "../log.h"
#include "utils.h"

extern "C" {
int prepare(BPGDecoderContext **context, int *width, int *height, uint8_t *data, int size);
int decode(BPGDecoderContext **context, uint8_t *rgba, int width, int height);
void close_decoder(BPGDecoderContext **context);
}
