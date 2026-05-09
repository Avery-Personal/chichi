#if (defined(CHICHI_IMPLEMENTATION) && !defined(CHICHI_LOG_IMPLEMENTATION)) || (defined(CC_IMPLEMENTATION) && !defined(CHICHI_LOG_IMPLEMENTATION))
    #define CHICHI_LOG_IMPLEMENTATION
#endif

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

        #if defined(__clang__) || defined(__GNUC__)
            typedef __builtin_va_list CCVAList;

            #define CCVAStart __builtin_va_start
            #define CCVAArgument __builtin_va_arg
            #define CCVAEnd __builtin_va_end
            #define CCVACopy __builtin_va_copy
        #else
            typedef unsigned char *CCVAList;

            #define CC_VA_ALIGN(Type) (((sizeof(Type) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))
            #define CCVAStart(ArgumentPointer, Last) ((ArgumentPointer) = ((CCVAList) & (Last) + CC_VA_ALIGN(Last)))
            #define CCVAArgument(ArgumentPointer, Type) (*(Type *)(((ArgumentPointer) += CC_VA_ALIGN(Type)) - CC_VA_ALIGN(Type)))
            #define CCVAEnd(ArgumentPointer) ((ArgumentPointer) = (CCVAList) 0)
            #define CCVACopy(Destination, Source) ((Destination) = (Source))
        #endif
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

        void *UserData;
    } CCLogSink;
    
    typedef struct CCLogger {
        CCLogLevel MinimumLevel;

        CCBool EnableConsole;
        CCBool EnableColors;
        CCBool EnableTimestamp;

        CCLogSink Sinks[CC_LOG_MAX_SINKS];

        CCu32 SinkCount;
    } CCLogger;

    CC_LOG_API extern CCLogger gCCLogger;

    CC_LOG_API void CCLogInitialize(void);
    CC_LOG_API void CCLogShutdown(void);

    CC_LOG_API void CCLogSetLevel(CCLogLevel Level);

    CC_LOG_API void CCLogEnableConsole(CCBool Enabled);
    CC_LOG_API void CCLogEnableColors(CCBool Enabled);
    CC_LOG_API void CCLogEnableTimestamp(CCBool Enabled);

    CC_LOG_API CCBool CCLogAddSink(CCLogSinkFunction Callback, void *UserData);
    CC_LOG_API void CCLogClearSinks(void);

    const char *CCLogLevelString(CCLogLevel Level);

    #ifndef CHICHI_LOG_IMPLEMENTATION
        #ifndef CC_LOG_NO_COLOR
            #define CC_LOG_COLOR_TRACE "\x1b[90m"
            #define CC_LOG_COLOR_DEBUG "\x1b[36m"
            #define CC_LOG_COLOR_INFO "\x1b[32m"
            #define CC_LOG_COLOR_WARN "\x1b[33m"
            #define CC_LOG_COLOR_ERROR "\x1b[31m"
            #define CC_LOG_COLOR_FATAL "\x1b[35m"
            #define CC_LOG_COLOR_RESET "\x1b[0m"
        #endif

        CCLogger gCCLogger = {CC_LOG_LEVEL_TRACE, CC_TRUE, CC_TRUE, CC_TRUE, {0}, 0};

        static const char *CHICHI__LogLevelColor(CCLogLevel Level) {
            #ifndef CC_LOG_NO_COLOR
                switch (Level) {
                    case CC_LOG_LEVEL_TRACE: return CC_LOG_COLOR_TRACE;
                    case CC_LOG_LEVEL_DEBUG: return CC_LOG_COLOR_DEBUG;
                    case CC_LOG_LEVEL_INFO: return CC_LOG_COLOR_INFO;
                    case CC_LOG_LEVEL_WARN: return CC_LOG_COLOR_WARN;
                    case CC_LOG_LEVEL_ERROR: return CC_LOG_COLOR_ERROR;
                    case CC_LOG_LEVEL_FATAL: return CC_LOG_COLOR_FATAL;

                    default: return CC_LOG_COLOR_RESET;
                }
            #else
                (void) Level;

                return "";
            #endif
        }

        void CCLogInitialize(void) {
            gCCLogger.MinimumLevel = CC_LOG_LEVEL_TRACE;
            gCCLogger.EnableConsole = CC_TRUE;
            gCCLogger.EnableColors = CC_TRUE;
            gCCLogger.EnableTimestamp  = CC_TRUE;
            gCCLogger.SinkCount = 0;
        }

        void CCLogShutdown(void) {
            gCCLogger.SinkCount = 0;
        }

        void CCLogSetLevel(CCLogLevel Level) {
            gCCLogger.MinimumLevel = Level;
        }

        void CCLogEnableConsole(CCBool Enabled) {
            gCCLogger.EnableConsole = Enabled;
        }

        void CCLogEnableColors(CCBool Enabled) {
            gCCLogger.EnableColors = Enabled;
        }

        void CCLogEnableTimestamp(CCBool Enabled) {
            gCCLogger.EnableTimestamp = Enabled;
        }

        CCBool CCLogAddSink(CCLogSinkFunction Callback, void *UserData) {
            if (gCCLogger.SinkCount >= CC_LOG_MAX_SINKS)
                return CC_FALSE;

            CCLogSink *Sink = &gCCLogger.Sinks[gCCLogger.SinkCount++];

            Sink -> Callback = Callback;
            Sink -> UserData = UserData;

            return CC_TRUE;
        }

        void CCLogClearSinks(void) {
            gCCLogger.SinkCount = 0;
        }

        const char *CCLogLevelString(CCLogLevel Level) {
            switch (Level) {
                case CC_LOG_LEVEL_TRACE: return "TRACE";
                case CC_LOG_LEVEL_DEBUG: return "DEBUG";
                case CC_LOG_LEVEL_INFO: return "INFO";
                case CC_LOG_LEVEL_WARN: return "WARN";
                case CC_LOG_LEVEL_ERROR: return "ERROR";
                case CC_LOG_LEVEL_FATAL: return "FATAL";

                default: return "UNKNOWN";
            }
        }
    #endif
    
    CC_EXTERN_C_END

#endif
