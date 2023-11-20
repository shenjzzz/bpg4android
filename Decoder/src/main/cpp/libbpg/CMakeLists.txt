# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

project("bpgCore")

#See https://github.com/mirrorer/libbpg/blob/master/Makefile
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -Wall -MMD -fno-asynchronous-unwind-tables -fdata-sections -ffunction-sections -fno-math-errno -fno-signed-zeros -fno-tree-vectorize -fomit-frame-pointer")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_REENTRANT")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_ISOC99_SOURCE -D_POSIX_C_SOURCE=200112 -D_XOPEN_SOURCE=600 -DHAVE_AV_CONFIG_H -std=c99 -D_GNU_SOURCE=1 -DUSE_VAR_BIT_DEPTH -DUSE_PRED")

set(ANDROID_ABI arm64-v8a)

include_directories(.)

#See https://github.com/mirrorer/libbpg/blob/master/Makefile
add_library(bpgCore STATIC libbpg.c
        libavcodec/hevc_cabac.c
        libavcodec/hevc_filter.c
        libavcodec/hevc.c
        libavcodec/hevcpred.c
        libavcodec/hevc_refs.c
        libavcodec/hevcdsp.c
        libavcodec/hevc_mvs.c
        libavcodec/hevc_ps.c
        libavcodec/hevc_sei.c
        libavcodec/utils.c
        libavcodec/cabac.c
        libavcodec/golomb.c
        libavcodec/videodsp.c
        libavutil/mem.c
        libavutil/buffer.c
        libavutil/log2_tab.c
        libavutil/frame.c
        libavutil/pixdesc.c
        libavutil/md5.c)

target_link_libraries(
        bpgCore
)