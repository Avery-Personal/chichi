#ifndef CHICHI_LOGGING_H
#define CHICHI_LOGGING_H

    #include <stdio.h>

    #ifdef CHICHI_BASE_H
        #define CC_LOG_HAS_BASE 1
    #else
        #define CC_LOG_HAS_BASE 0
    #endif

    // Chichi's base is meant to stop this, that is, boilercode in headers & overall libraries/systems.
    // Though in the case of someone NOT including said base, I need to make the bare minimum for essential header data/structs.
    #if !CC_LOG_HAS_BASE
        #ifdef __cplusplus
            #define CC_EXTERN_C_BEGIN extern "C" {
            #define CC_EXTERN_C_END }
        #else
            #define CC_EXTERN_C_BEGIN
            #define CC_EXTERN_C_END
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

        #ifndef CC_TRUE
            #define CC_TRUE 1
        #endif

        #ifndef CC_FALSE
            #define CC_FALSE 0
        #endif

        typedef unsigned char CCBool;
        typedef unsigned int CCu32;
    #else
        #define CC_LOG_API CC_API
    #endif

    CC_EXTERN_C_BEGIN

    #ifndef CC_LOG_LEVEL
        #define CC_LOG_LEVEL CC_LOG_LEVEL_TRACE
    #endif

    #ifndef CC_LOG_MAX_MESSAGE
        #define CC_LOG_MAX_MESSAGE 4096
    #endif

    #ifndef CC_LOG_MAX_SINKS
        #define CC_LOG_MAX_SINKS 8
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

    typedef void (*CCLogSinkFunction)(const CCLogMessage *Message, void *UserData);

    typedef struct CCLogSink {
        CCLogSinkFunction Callback;

        void *Userdata;
    } CCLogSink;
    
    typedef struct CCLogger {
        CCLogLevel MinimumLevel;

        CCBool EnableConsole;
        CCBool EnableColors;
        CCBool EnableTimestamp;

        CCLogSink Sink[CC_LOG_MAX_SINKS];

        CCu32 SinkCount;
    } CCLogger;
    
    CC_EXTERN_C_END

#endif
