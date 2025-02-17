#ifndef OSInterface_h
#define OSInterface_h

#include <cstdint>
#include <cstdio>

#ifdef ESP_PLATFORM
#warning "MOVE THIS CODE TO ESP PLATFORM IMPLEMENTATION"

#include "esp_log.h"

#ifndef OSInterfaceVerbose
#define OSInterfaceVerbose(tag, format, ...) ESP_LOGV(tag, format, ##__VA_ARGS__)
#endif

#ifndef OSInterfaceDebug
#define OSInterfaceDebug(tag, format, ...) ESP_LOGD(tag, format, ##__VA_ARGS__)
#endif

#ifndef OSInterfaceInfo
#define OSInterfaceInfo(tag, format, ...) ESP_LOGI(tag, format, ##__VA_ARGS__)
#endif

#ifndef OSInterfaceWarning
#define OSInterfaceWarning(tag, format, ...) ESP_LOGW(tag, format, ##__VA_ARGS__)
#endif

#ifndef OSInterfaceError
#define OSInterfaceError(tag, format, ...) ESP_LOGE(tag, format, ##__VA_ARGS__)
#endif

#endif

#define OSInterfaceVerbose(tag, format, ...) printf("Verbose - %s: " format "\n", tag, ##__VA_ARGS__)
#define OSInterfaceDebug(tag, format, ...) printf("Debug - %s: " format "\n", tag, ##__VA_ARGS__)
#define OSInterfaceInfo(tag, format, ...) printf("Info - %s: " format "\n", tag, ##__VA_ARGS__)
#define OSInterfaceWarning(tag, format, ...) printf("Warning - %s: " format "\n", tag, ##__VA_ARGS__)
#define OSInterfaceError(tag, format, ...) printf("Error - %s: " format "\n", tag, ##__VA_ARGS__)

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
