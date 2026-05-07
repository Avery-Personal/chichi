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

    #if CC_LANG_CPP
        #define CC_EXTERN_C_BEGIN extern "C" {
        #define CC_EXTERN_C_END }
        #define CC_EXTERN_C extern "C"
    #else
        #define CC_EXTERN_C_BEGIN
        #define CC_EXTERN_C_END
        #define CC_EXTERN_C
    #endif

    #if defined(_MSC_VER)
        #define CC_CDECLERATION __cdecl
        #define CC_STDCALL __stdcall
        #define CC_FASTCALL __fastcall
    #else
        #define CC_CDECLERATION
        #define CC_STDCALL
        #define CC_FASTCALL
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        #define CC_EXPORT __declspec(dllexport)
        #define CC_IMPORT __declspec(dllimport)
        #define CC_HIDDEN
    #elif defined(__GNUC__) || defined(__clang__)
        #define CC_EXPORT __attribute__((visibility("default")))
        #define CC_IMPORT __attribute__((visibility("default")))
        #define CC_HIDDEN __attribute__((visibility("hidden")))
    #else
        #define CC_EXPORT
        #define CC_IMPORT
        #define CC_HIDDEN
    #endif

    #if defined(CC_STATIC)
        #define CC_API
    #elif defined(CC_BUILD_DLL)
        #define CC_API CC_EXPORT
    #else
        #define CC_API CC_IMPORT
    #endif

    #if defined(_MSC_VER)
        #define CC_INLINE __inline
        #define CC_FORCE_INLINE __forceinline
        #define CC_NO_INLINE __declspec(noinline)
    #elif defined(__clang__) || defined(__GNUC__)
        #define CC_INLINE inline
        #define CC_FORCE_INLINE inline __attribute__((always_inline))
        #define CC_NO_INLINE __attribute__((noinline))
    #else
        #define CC_INLINE inline
        #define CC_FORCE_INLINE inline
        #define CC_NO_INLINE
    #endif

    #if defined(_MSC_VER)
        #define CC_ALIGN(N) __declspec(align(N))
    #elif defined(__clang__) || defined(__GNUC__)
        #define CC_ALIGN(N) __attribute__((aligned(N)))
    #else
        #define CC_ALIGN(N)
    #endif

    #if defined(_MSC_VER)
        #define CC_ALIGN_OF(T) __alignof(T)
    #elif defined(__cplusplus)
        #define CC_ALIGN_OF(T) alignof(T)
    #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
        #include <stdalign.h>

        #define CC_ALIGN_OF(T) alignof(T)
    #else
        #define CC_ALIGN_OF(T) sizeof(struct { char Character; T Type; }) - sizeof(T)
    #endif
    
    #define CC_CACHELINE_SIZE 64

    #if defined(_MSC_VER)
        #define CC_PACK_PUSH(N) __pragma(pack(push, N))
        #define CC_PACK_POP __pragma(pack(pop))
    #elif defined(__clang__) || defined(__GNUC__)
        #define CC_PACK_PUSH(N) _Pragma(CC_STRINGIFY(pack(push, N)))
        #define CC_PACK_POP _Pragma("pack(pop)")
    #else
        #define CC_PACK_PUSH(N)
        #define CC_PACK_POP
    #endif
    
    #if defined(__clang__) || defined(__GNUC__)
        #define CC_LIKELY(x) __builtin_expect(!!(x), 1)
        #define CC_UNLIKELY(x) __builtin_expect(!!(x), 0)
    #else
        #define CC_LIKELY(x) (x)
        #define CC_UNLIKELY(x) (x)
    #endif

    #if defined(__cplusplus) && (__cplusplus >= 201103L)
        #define CC_STATIC_ASSERT(Expression, Message) static_assert((Message), Message)
    #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
        #define CC_STATIC_ASSERT(Expression, Message) _Static_assert((Message), Message)
    #else
        #define CC_STATIC_ASSERT(Expression, Message) typedef char CC_CONCAT(cc_static_assert_failed_, __LINE__)[(Message) ? 1 : -1]
    #endif

    #define CC_ARRAY_COUNT(Array) (sizeof(Array) / sizeof((Array)[0]))
    #define CC_MIN(a, b) (((a) < (b)) ? (a) : (b))
    #define CC_MAX(a, b) (((a) > (b)) ? (a) : (b))
    #define CC_CLAMP(x, Low, High) (CC_MAX((Low), CC_MIN((x), (High))))

    #if defined(_MSC_VER)
        #include <intrin.h>

        #define CC_DEBUGBREAK() __debugbreak()
        #define CC_TRAP() __debugbreak()
    #elif defined(__clang__) || defined(__GNUC__)
        #define CC_DEBUGBREAK() __builtin_debugtrap()
        #define CC_TRAP() __builtin_trap()
    #else
        #include <signal.h>

        #define CC_DEBUGBREAK() raise(SIGTRAP)
        #define CC_TRAP() raise(SIGTRAP)
    #endif

    #if defined(__cplusplus) && (__cplusplus >= 201703L)
        #define CC_NODISCARD [[nodiscard]]
    #elif defined(__has_cpp_attribute)
        #if __has_cpp_attribute(nodiscard)
            #define CC_NODISCARD [[nodiscard]]
        #else
            #define CC_NODISCARD
        #endif
    #else
        #define CC_NODISCARD
    #endif

    #if defined(__has_c_attribute)
        #if __has_c_attribute(nodiscard)
            #undef CC_NODISCARD
            #define CC_NODISCARD [[nodiscard]]
        #endif
    #endif

    #if defined(__has_cpp_attribute)
        #if __has_cpp_attribute(maybe_unused)
            #define CC_MAYBE_UNUSED [[maybe_unused]]
        #else
            #define CC_MAYBE_UNUSED
        #endif
    #else
        #define CC_MAYBE_UNUSED
    #endif

    #if defined(__cplusplus)
        #if __cplusplus >= 201103L
            #define CC_NULLPTR nullptr
        #else
            #define CC_NULLPTR 0
        #endif
    #else
        #define CC_NULLPTR ((void *)0)
    #endif

#endif
