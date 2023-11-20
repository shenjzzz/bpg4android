# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

project("bpgDecoder")

set(ANDROID_ABI arm64-v8a)


include_directories(./libbpg)
aux_source_directory(. jni)
aux_source_directory(./decoder decoder)
add_library(bpgDecoder SHARED ${jni} ${decoder})

add_subdirectory(libbpg)

find_library(loglib log)
find_library(zlib z)
find_library(graphicslib jnigraphics)
find_library(androidlib android)

target_link_libraries(
        bpgDecoder
        bpgCore
        ${loglib}
        ${graphicslib}
        ${zlib}
        ${androidlib}
)