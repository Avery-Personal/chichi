#if (defined(CHICHI_IMPLEMENTATION) && !defined(CHICHI_NET_IMPLEMENTATION)) || (defined(CC_IMPLEMENTATION) && !defined(CHICHI_NET_IMPLEMENTATION))
    #define CHICHI_NET_IMPLEMENTATION
#endif

#ifndef CHICHI_NET_H
#define CHICHI_NET_H

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

    CC_EXTERN_C_BEGIN

    

    CC_EXTERN_C_END

#endif
