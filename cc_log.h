#ifndef CHICHI_LOGGING_H
#define CHICHI_LOGGING_H

    #ifdef __cplusplus
        extern "C" {
    #endif

    #ifndef CC_LOG_LEVEL
        #define CC_LOG_LEVEL CC_LOG_LEVEL_TRACE
    #endif

    #if defined(_WIN32)
        #if defined(CC_LOG_BUILD_DLL)
            #define CC_LOG_API __declspec(dllexport)
        #elif defined(CC_LOG_USE_DLL)
            #define CC_LOG_API __declspec(dllimport)
        #else
            #define CC_LOG_API
        #endif
    #else
        #define CC_LOG_API
    #endif

    typedef enum CCLogLevel {
        CC_LOG_LEVEL_TRACE = 0,
        CC_LOG_LEVEL_DEBUG,
        CC_LOG_LEVEL_INFO,
        CC_LOG_LEVEL_WARN,
        CC_LOG_LEVEL_ERROR,
        CC_LOG_LEVEL_FATAL
    } CCLogLevel;

    typedef struct CCLogMessage {
        CCLogLevel Level;

        const char *File;
        const char *Function;

        int Line;

        const char *Message;
    } CCLogMessage;
    
    #ifdef __cplusplus
        }
    #endif

#endif
