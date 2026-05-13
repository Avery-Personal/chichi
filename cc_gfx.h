#if (defined(CHICHI_IMPLEMENTATION) && !defined(CHICHI_GFX_IMPLEMENTATION)) || (defined(CC_IMPLEMENTATION) && !defined(CHICHI_GFX_IMPLEMENTATION))
    #define CHICHI_GFX_IMPLEMENTATION
#endif

#ifndef CHICHI_GFX_H
#define CHICHI_GFX_H

    #ifdef CHICHI_BASE_H
        #define CC_GFX_HAS_BASE 1
    #else
        #define CC_GFX_HAS_BASE 0
    #endif

    #ifdef CHICHI_LOGGING_H
        #define CC_GFX_HAS_LOG 1
    #else
        #define CC_GFX_HAS_LOG 0
    #endif

    #if !CC_GFX_HAS_BASE
        #ifdef __cplusplus
            #define CC_EXTERN_C_BEGIN extern "C" {
            #define CC_EXTERN_C_END }
        #else
            #define CC_EXTERN_C_BEGIN
            #define CC_EXTERN_C_END
        #endif

        #if defined(_WIN32)
            #if defined(CC_GFX_BUILD_DLL)
                #define CC_GFX_API __declspec(dllexport)
            #elif defined(CC_GFX_USE_DLL)
                #define CC_GFX_API __declspec(dllimport)
            #else
                #define CC_GFX_API
            #endif
        #else
            #define CC_GFX_API
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
        #define CC_GFX_API CC_API
    #endif

    #if !CC_GFX_HAS_LOG
        #ifndef CC_GFX_TRACE
            #define CC_GFX_TRACE(...) ((void) 0)
        #endif

        #ifndef CC_GFX_DEBUG
            #define CC_GFX_DEBUG(...) ((void) 0)
        #endif

        #ifndef CC_GFX_INFO
            #define CC_GFX_INFO(...) ((void) 0)
        #endif

        #ifndef CC_GFX_WARN
            #define CC_GFX_WARN(...) ((void) 0)
        #endif

        #ifndef CC_GFX_ERROR
            #define CC_GFX_ERROR(...) ((void) 0)
        #endif

        #ifndef CC_GFX_FATAL
            #define CC_GFX_FATAL(...) ((void) 0)
        #endif
    #else
        #define CC_GFX_TRACE(...) CC_TRACE(__VA_ARGS__)
        #define CC_GFX_DEBUG(...) CC_DEBUG(__VA_ARGS__)
        #define CC_GFX_INFO(...)  CC_INFO(__VA_ARGS__)
        #define CC_GFX_WARN(...)  CC_WARN(__VA_ARGS__)
        #define CC_GFX_ERROR(...) CC_ERROR(__VA_ARGS__)
        #define CC_GFX_FATAL(...) CC_FATAL(__VA_ARGS__)
    #endif

    CC_EXTERN_C_BEGIN



    CC_EXTERN_C_END

#endif
