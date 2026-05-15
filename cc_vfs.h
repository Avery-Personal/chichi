#if (defined(CHICHI_IMPLEMENTATION) && !defined(CHICHI_VFS_IMPLEMENTATION)) || (defined(CC_IMPLEMENTATION) && !defined(CHICHI_VFS_IMPLEMENTATION))
    #define CHICHI_VFS_IMPLEMENTATION
#endif

#ifndef CHICHI_VFS_H
#define CHICHI_VFS_H

    #ifdef CHICHI_BASE_H
        #define CC_NET_HAS_BASE 1
    #else
        #define CC_NET_HAS_BASE 0
    #endif

    #if !CC_NET_HAS_BASE
        #ifdef __cplusplus
            #define CC_EXTERN_C_BEGIN extern "C" {
            #define CC_EXTERN_C_END }
        #else
            #define CC_EXTERN_C_BEGIN
            #define CC_EXTERN_C_END
        #endif

        #if defined(_WIN32)
            #if defined(CC_NET_BUILD_DLL)
                #define CC_NET_API __declspec(dllexport)
            #elif defined(CC_NET_USE_DLL)
                #define CC_NET_API __declspec(dllimport)
            #else
                #define CC_NET_API
            #endif
        #else
            #define CC_NET_API
        #endif

        #ifndef CC_TRUE
            #define CC_TRUE 1
        #endif

        #ifndef CC_FALSE
            #define CC_FALSE 0
        #endif

        typedef unsigned char CCBool;
        typedef unsigned int CCu32;
    #else
        #define CC_NET_API CC_API
    #endif

    #ifdef CHICHI_VFS_H
        #define CC_VFS_HAS_VFS 1
    #else
        #define CC_VFS_HAS_VFS 0
    #endif

    #if !CC_VFS_HAS_VFS
        #ifndef CC_VFS_TRACE
            #define CC_VFS_TRACE(...) ((void) 0)
        #endif

        #ifndef CC_VFS_DEBUG
            #define CC_VFS_DEBUG(...) ((void) 0)
        #endif

        #ifndef CC_VFS_INFO
            #define CC_VFS_INFO(...) ((void) 0)
        #endif

        #ifndef CC_VFS_WARN
            #define CC_VFS_WARN(...) ((void) 0)
        #endif

        #ifndef CC_VFS_ERROR
            #define CC_VFS_ERROR(...) ((void) 0)
        #endif

        #ifndef CC_VFS_FATAL
            #define CC_VFS_FATAL(...) ((void) 0)
        #endif
    #else
        #define CC_VFS_TRACE(...) CC_TRACE(__VA_ARGS__)
        #define CC_VFS_DEBUG(...) CC_DEBUG(__VA_ARGS__)
        #define CC_VFS_INFO(...)  CC_INFO(__VA_ARGS__)
        #define CC_VFS_WARN(...)  CC_WARN(__VA_ARGS__)
        #define CC_VFS_ERROR(...) CC_ERROR(__VA_ARGS__)
        #define CC_VFS_FATAL(...) CC_FATAL(__VA_ARGS__)
    #endif

    CC_EXTERN_C_BEGIN

    

    CC_EXTERN_C_END

#endif
