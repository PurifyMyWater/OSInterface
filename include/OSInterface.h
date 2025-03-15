#ifndef OSInterface_h
#define OSInterface_h

#include <cstdint>
#include <cstdio>

#define EXPAND_TO_STRING(x) #x
#define TOSTRING(x) EXPAND_TO_STRING(x)
#define AT "AT " __FILE__ ":" TOSTRING(__LINE__) ": "

#define OSInterfaceLogVerbose(tag, format, ...) printf("Verbose - %s: " format "\n", tag, ##__VA_ARGS__)
#define OSInterfaceLogDebug(tag, format, ...) printf("Debug - %s: " format "\n", tag, ##__VA_ARGS__)
#define OSInterfaceLogInfo(tag, format, ...) printf("Info - %s: " format "\n", tag, ##__VA_ARGS__)
#define OSInterfaceLogWarning(tag, format, ...) printf("Warning - %s: " format "\n", tag, ##__VA_ARGS__)
#define OSInterfaceLogError(tag, format, ...) printf("Error - %s: " format "\n", tag, ##__VA_ARGS__)
#define OSInterfaceSetLogLevel(tag, level) printf("Mock: Set log level of tag '%s' to '%d'\n", tag, level)
#define OSInterfaceGetLogLevel(tag) OSInterface_LOG_INFO

using OSInterfaceLogLevel = enum {
    OSInterface_LOG_NONE = 0, /*!< No log output */
    OSInterface_LOG_ERROR = 1, /*!< Critical errors, software module can not recover on its own */
    OSInterface_LOG_WARN = 2, /*!< Error conditions from which recovery measures have been taken */
    OSInterface_LOG_INFO = 3, /*!< Information messages which describe normal flow of events */
    OSInterface_LOG_DEBUG = 4, /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
    OSInterface_LOG_VERBOSE = 5, /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
    OSInterface_LOG_MAX = 6, /*!< Number of levels supported */
};

class OSInterface_Mutex
{
public:
    virtual ~OSInterface_Mutex() = default;
    virtual void signal() = 0;
    virtual bool wait(uint32_t max_time_to_wait_ms) = 0;
};

/**
 * This implementation assumes that once created, the semaphore needs to be signaled before it can be waited on. (The initial value is 0)
 */
class OSInterface_BinarySemaphore
{
public:
    virtual ~OSInterface_BinarySemaphore() = default;
    virtual void signal() = 0;
    virtual bool wait(uint32_t max_time_to_wait_ms) = 0;
};

class OSInterface
{
public:
    virtual void osSleep(uint32_t ms) = 0;
    virtual uint32_t osMillis() = 0;
    virtual OSInterface_Mutex* osCreateMutex() = 0;
    virtual OSInterface_BinarySemaphore* osCreateBinarySemaphore() = 0;

    virtual void* osMalloc(uint32_t size) = 0;
    virtual void osFree(void* ptr) = 0;

    virtual ~OSInterface() = default;
};

#endif // OSInterface_h
