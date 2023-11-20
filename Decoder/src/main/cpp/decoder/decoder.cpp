//
// Created by ShenJian on 2023/11/19.
//

#include <jni.h>
#include <cstdint>
#include <malloc.h>
#include <cstring>
#include "decoder.h"

extern "C" {
int prepare(BPGDecoderContext **context, int *width, int *height, uint8_t *data, int size) {
    *context = bpg_decoder_open();
    if (*context == nullptr) {
        logE("BPG decoder open failed\n");
        return -1;
    }

    if (bpg_decoder_decode(*context, data, size) < 0) {
        logE("Decode image failed\n");
        return -1;
    }
    BPGImageInfo imageInfo;
    if (bpg_decoder_get_info(*context, &imageInfo) < 0) {
        return -1;
    }
    *width = imageInfo.width;
    *height = imageInfo.height;
    return 0;
}

int decode(BPGDecoderContext **context, uint8_t *rgba, int width, int height) {
    if (bpg_decoder_start(*context, BPG_OUTPUT_FORMAT_RGBA32) < 0) {
        return -1;
    }
    size_t line_size = width * PIXEL_SIZE;
    void *line = malloc(line_size);
    for (int y = 0; y < height; y++) {
        bpg_decoder_get_line(*context, line);
        memcpy(rgba + y * line_size, line, line_size);
    }
    free(line);
    return 0;
}

void close_decoder(BPGDecoderContext **context) {
    bpg_decoder_close(*context);
}
}