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
        #define CC_COMPILER_NAME "Unknown"
        #define CC_COMPILER CC_COMPILER_UNKNOWN
    #endif

    #if CC_COMPILER == CC_COMPILER_MSVC
        #define CC_COMPILER_VERSION_MAJOR _MSC_VER
        #define CC_COMPILER_VERSION_MINOR 0
        #define CC_COMPILER_VERSION_PATCH 0
    #elif CC_COMPILER == CC_COMPILER_CLANG
        #ifdef __clang_major__
            #define CC_COMPILER_VERSION_MAJOR __clang_major__
            #define CC_COMPILER_VERSION_MINOR __clang_minor__
            #define CC_COMPILER_VERSION_PATCH __clang_patchlevel__
        #else
            #define CC_COMPILER_VERSION_MAJOR 0
            #define CC_COMPILER_VERSION_MINOR 0
            #define CC_COMPILER_VERSION_PATCH 0
        #endif
    #elif CC_COMPILER == CC_COMPILER_GCC
        #ifdef __GNUC__
            #define CC_COMPILER_VERSION_MAJOR __GNUC__
            #define CC_COMPILER_VERSION_MINOR __GNUC_MINOR__
            #define CC_COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__
        #else
            #define CC_COMPILER_VERSION_MAJOR 0
            #define CC_COMPILER_VERSION_MINOR 0
            #define CC_COMPILER_VERSION_PATCH 0
        #endif
    #else
        #define CC_COMPILER_VERSION_MAJOR 0
        #define CC_COMPILER_VERSION_MINOR 0
        #define CC_COMPILER_VERSION_PATCH 0
    #endif

    #define CC_PLATFORM_UNKNOWN 0
    #define CC_PLATFORM_WINDOWS 1
    #define CC_PLATFORM_MACOS 2
    #define CC_PLATFORM_LINUX 3
    #define CC_PLATFORM_IOS 4
    #define CC_PLATFORM_ANDROID 5

    #if defined(_WIN32) || defined(_WIN64)
        #define CC_PLATFORM_NAME "Windows"
        #define CC_PLATFORM CC_PLATFORM_WINDOWS
    #elif defined(__APPLE__) && defined(__MACH__)
        #include <TargetConditionals.h>

        #if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
            #define CC_PLATFORM_NAME "iOS"
            #define CC_PLATFORM CC_PLATFORM_IOS
        #else
            #define CC_PLATFORM_NAME "MacOS"
            #define CC_PLATFORM CC_PLATFORM_MACOS
        #endif
    #elif defined(__ANDROID__)
        #define CC_PLATFORM_NAME "Android"
        #define CC_PLATFORM CC_PLATFORM_ANDROID
    #elif defined(__linux__)
        #define CC_PLATFORM_NAME "Linux"
        #define CC_PLATFORM CC_PLATFORM_LINUX
    #else
        #define CC_PLATFORM_NAME "Unknown"
        #define CC_PLATFORM CC_PLATFORM_UNKNOWN
    #endif

    #define CC_ARCH_UNKNOWN 0
    #define CC_ARCH_X86 1
    #define CC_ARCH_X64 2
    #define CC_ARCH_ARM32 3
    #define CC_ARCH_ARM64 4

    #if defined(_M_X64) || defined(__x86_64__) || defined(__amd64__)
        #define CC_ARCH_NAME "x64"
        #define CC_ARCH CC_ARCH_X64
    #elif defined(_M_IX86) || defined(__i386__)
        #define CC_ARCH_NAME "x86"
        #define CC_ARCH CC_ARCH_X86
    #elif defined(_M_ARM64) || defined(__aarch64__)
        #define CC_ARCH_NAME "ARM64"
        #define CC_ARCH CC_ARCH_ARM64
    #elif defined(_M_ARM) || defined(__arm__)
        #define CC_ARCH_NAME "ARM32"
        #define CC_ARCH CC_ARCH_ARM32
    #else
        #define CC_ARCH_NAME "Unknown"
        #define CC_ARCH CC_ARCH_UNKNOWN
    #endif

    #if defined(__cplusplus)
        #define CC_LANG_CPP 1
        #define CC_LANG_C 0
    #else
        #define CC_LANG_CPP 0
        #define CC_LANG_C 1
    #endif

    #if defined(CC_SHIPPING)
        #define CC_BUILD_SHIPPING 1
        #define CC_BUILD_RELEASE 0
        #define CC_BUILD_DEBUG 0
    #elif defined(CC_RELEASE)
        #define CC_BUILD_SHIPPING 0
        #define CC_BUILD_RELEASE 1
        #define CC_BUILD_DEBUG 0
    #elif defined(NDEBUG)
        #define CC_BUILD_SHIPPING 0
        #define CC_BUILD_RELEASE 1
        #define CC_BUILD_DEBUG 0
    #else
        #define CC_BUILD_SHIPPING 0
        #define CC_BUILD_RELEASE 0
        #define CC_BUILD_DEBUG 1
    #endif

#endif
