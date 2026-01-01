#ifndef OSINTERFACE_OSINTERFACE_LOG_H
#define OSINTERFACE_OSINTERFACE_LOG_H

#ifndef EXPAND_TO_STRING
    #define EXPAND_TO_STRING(x) #x
#endif

#ifndef TOSTRING
    #define TOSTRING(x) EXPAND_TO_STRING(x)
#endif

#ifndef AT
    #define AT "AT " __FILE__ ":" TOSTRING(__LINE__) ": "
#endif

#include <cstdio>

#ifndef OSInterfaceLogVerbose
    #define OSInterfaceLogVerbose(tag, format, ...)                                                                    \
        do                                                                                                             \
        {                                                                                                              \
            printf("Verbose - %s: " format "\n", tag, ##__VA_ARGS__);                                                  \
            fflush(stdout);                                                                                            \
        }                                                                                                              \
        while (0)
#endif

#ifndef OSInterfaceLogDebug
    #define OSInterfaceLogDebug(tag, format, ...)                                                                      \
        do                                                                                                             \
        {                                                                                                              \
            printf("Debug - %s: " format "\n", tag, ##__VA_ARGS__);                                                    \
            fflush(stdout);                                                                                            \
        }                                                                                                              \
        while (0)
#endif

#ifndef OSInterfaceLogInfo
    #define OSInterfaceLogInfo(tag, format, ...)                                                                       \
        do                                                                                                             \
        {                                                                                                              \
            printf("Info - %s: " format "\n", tag, ##__VA_ARGS__);                                                     \
            fflush(stdout);                                                                                            \
        }                                                                                                              \
        while (0)
#endif

#ifndef OSInterfaceLogWarning
    #define OSInterfaceLogWarning(tag, format, ...)                                                                    \
        do                                                                                                             \
        {                                                                                                              \
            printf("Warning " AT " - %s: " format "\n", tag, ##__VA_ARGS__);                                           \
            fflush(stdout);                                                                                            \
        }                                                                                                              \
        while (0)
#endif

#ifndef OSInterfaceLogError
    #define OSInterfaceLogError(tag, format, ...)                                                                      \
        do                                                                                                             \
        {                                                                                                              \
            printf("Error: " AT " - %s: " format "\n", tag, ##__VA_ARGS__);                                            \
            fflush(stdout);                                                                                            \
        }                                                                                                              \
        while (0)
#endif

#ifndef OSInterfaceSetLogLevel
    #define OSInterfaceSetLogLevel(tag, level)                                                                         \
        do                                                                                                             \
        {                                                                                                              \
            printf("Mock: Set log level of tag '%s' to '%s'\n", tag, OSInterfaceLogLevelToString(level));              \
            fflush(stdout);                                                                                            \
        }                                                                                                              \
        while (0)
#endif

#ifndef OSInterfaceGetLogLevel
    #define OSInterfaceGetLogLevel(tag) OSInterface_LOG_INFO
#endif

using OSInterfaceLogLevel = enum {
    OSInterface_LOG_NONE  = 0, /*!< No log output */
    OSInterface_LOG_ERROR = 1, /*!< Critical errors, software module cannot recover on its own */
    OSInterface_LOG_WARN  = 2, /*!< Error conditions from which recovery measures have been taken */
    OSInterface_LOG_INFO  = 3, /*!< Information messages, which describe normal flow of events */
    OSInterface_LOG_DEBUG =
        4, /*!< Extra information, which is not necessary for normal use (values, pointers, sizes, etc). */
    OSInterface_LOG_VERBOSE =
        5, /*!< Bigger chunks of debugging information, or frequent messages, which can potentially flood the output. */
    OSInterface_LOG_MAX = 6, /*!< Number of levels supported */
};

const char* OSInterfaceLogLevelToString(OSInterfaceLogLevel level);

#endif // OSINTERFACE_OSINTERFACE_LOG_H
