#ifndef CHICHI_BASE_H
#define CHICHI_BASE_H

    #define CC_BASE_VERSION_MAJOR 1
    #define CC_BASE_VERSION_MINOR 0
    #define CC_BASE_VERSION_PATCH 0
    #define CC_BASE_VERSION ((CC_BASE_VERSION_MAJOR * 10000) + (CC_BASE_VERSION_MINOR * 100) + CC_BASE_VERSION_PATCH)

    #define CC_STRINGIFY_IMPLEMENTATION(x) #x
    #define CC_STRINGIFY(x) CC_STRINGIFY_IMPLEMENTATION(x)

    #define CC_CONCAT_IMPLEMENTATION(a, b) a##b
    #define CC_CONCAT(a, b) CC_CONCAT_IMPLEMENTATION(a, b)

    #define CC_COMPILER_UNKNOWN 0
    #define CC_COMPILER_MSVC 1
    #define CC_COMPILER_CLANG 2
    #define CC_COMPILER_GCC 3

    #if defined(_MSC_VER)
        #define CC_COMPILER_NAME "MSVC"
        #define CC_COMPILER_MSVC_ACTIVE 1
    #else
        #define CC_COMPILER_MSVC_ACTIVE 0
    #endif

    #if defined(__clang__)
        #undef CC_COMPILER
        #define CC_COMPILER CC_COMPILER_CLANG
        #define CC_COMPILER_NAME "Clang"
        #define CC_COMPILER_CLANG_ACTIVE 1
    #else
        #define CC_COMPILER_CLANG_ACTIVE 0
    #endif

    #if defined(__GNUC__) && !defined(__clang__)
        #undef CC_COMPILER
        #define CC_COMPILER CC_COMPILER_GCC
        #define CC_COMPILER_NAME "GCC"
        #define CC_COMPILER_GCC_ACTIVE 1
    #else
        #define CC_COMPILER_GCC_ACTIVE 0
    #endif

    #ifndef CC_COMPILER
        #define CC_COMPILER CC_COMPILER_UNKNOWN
        #define CC_COMPILER_NAME "Unknown"
    #endif

#endif
