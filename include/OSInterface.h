#ifndef OSInterface_h
#define OSInterface_h

#include <cstdint>
#include <cstdio>

#define EXPAND_TO_STRING(x) #x
#define TOSTRING(x) EXPAND_TO_STRING(x)
#define AT "AT " __FILE__ ":" TOSTRING(__LINE__) ": "

#ifdef NDEBUG
    #define ASSERT_SAFE(expression, condition) expression
#else
    #define ASSERT_SAFE(expression, condition) assert(expression condition)
#endif

#define OSInterfaceLogVerbose(tag, format, ...) do{printf("Verbose - %s: " format "\n", tag, ##__VA_ARGS__);fflush(stdout);}while(0)
#define OSInterfaceLogDebug(tag, format, ...) do{printf("Debug - %s: " format "\n", tag, ##__VA_ARGS__);fflush(stdout);}while(0)
#define OSInterfaceLogInfo(tag, format, ...) do{printf("Info - %s: " format "\n", tag, ##__VA_ARGS__);fflush(stdout);}while(0)
#define OSInterfaceLogWarning(tag, format, ...) do{printf("Warning " AT " - %s: " format "\n", tag, ##__VA_ARGS__);fflush(stdout);}while(0)
#define OSInterfaceLogError(tag, format, ...) do{printf("Error: " AT " - %s: " format "\n", tag, ##__VA_ARGS__);fflush(stdout);}while(0)
#define OSInterfaceSetLogLevel(tag, level) do{printf("Mock: Set log level of tag '%s' to '%d'\n", tag, level);fflush(stdout);}while(0)
#define OSInterfaceGetLogLevel(tag) OSInterface_LOG_INFO

using OSInterfaceLogLevel = enum {
    OSInterface_LOG_NONE  = 0, /*!< No log output */
    OSInterface_LOG_ERROR = 1, /*!< Critical errors, software module can not recover on its own */
    OSInterface_LOG_WARN  = 2, /*!< Error conditions from which recovery measures have been taken */
    OSInterface_LOG_INFO  = 3, /*!< Information messages which describe normal flow of events */
    OSInterface_LOG_DEBUG =
        4, /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
    OSInterface_LOG_VERBOSE =
        5, /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
    OSInterface_LOG_MAX = 6, /*!< Number of levels supported */
};

using OSInterfaceProcess = void (*)(void* arg);

class OSInterface_Mutex
{
public:
    virtual ~OSInterface_Mutex() = default;

    /**
     * @brief Signal the mutex
     *
     * @note This will unlock the mutex.
     */
    virtual void signal() = 0;

    /**
     * @brief Wait for the mutex to be available
     *
     * @param max_time_to_wait_ms Maximum time to wait in milliseconds
     * @return true if the mutex was acquired, false if the timeout was reached
     */
    virtual bool wait(uint32_t max_time_to_wait_ms) = 0;
};

/**
 * This implementation assumes that once created, the semaphore needs to be signaled before it can be waited on. (The
 * initial value is 0)
 */
class OSInterface_BinarySemaphore
{
public:
    virtual ~OSInterface_BinarySemaphore() = default;

    /**
     * @brief Signal the semaphore
     *
     * @note This will signal the semaphore.
     */
    virtual void signal() = 0;

    /**
     * @brief Wait for the semaphore to be available
     *
     * @param max_time_to_wait_ms Maximum time to wait in milliseconds
     * @return true if the semaphore was acquired, false if the timeout was reached
     */
    virtual bool wait(uint32_t max_time_to_wait_ms) = 0;
};

class OSInterface
{
public:
    /**
     * @brief Sleep for a given number of milliseconds
     *
     * @param ms Number of milliseconds to sleep
     */
    virtual void osSleep(uint32_t ms) = 0;

    /**
     * @brief Get the current time in milliseconds
     *
     * @return uint32_t Current time in milliseconds
     */
    virtual uint32_t osMillis() = 0;

    /**
     * @brief Create a mutex
     *
     * @return OSInterface_Mutex* Pointer to the created mutex
     * @note The mutex is created in the unlocked state.
     * @note The mutex needs to be freed with delete.
     */
    virtual OSInterface_Mutex* osCreateMutex() = 0;

    /**
     * @brief Create a binary semaphore
     *
     * @return OSInterface_BinarySemaphore* Pointer to the created binary semaphore
     * @note The semaphore is created with the initial value of 0.
     * @note The semaphore needs to be freed with delete.
     */
    virtual OSInterface_BinarySemaphore* osCreateBinarySemaphore() = 0;

    /**
     * @brief Allocate memory
     *
     * @param size Size of the memory to allocate
     * @return void* Pointer to the allocated memory
     * @note If size is 0, the function will return null pointer.
     */
    virtual void* osMalloc(uint32_t size) = 0;

    /**
     * @brief Free memory
     *
     * @param ptr Pointer to the memory to free
     * @note If ptr is null, the function will do nothing.
     */
    virtual void osFree(void* ptr) = 0;

    /**
     * @brief Run a process in a separate thread
     *
     * @param process Process to run
     * @param arg Argument to pass to the process
     * @note The process will be run in a separate thread.
     */
    /**
     * @brief Run a process in a separate thread
     *
     * @param process Process to run
     * @param processName (Optional) Name of the process. Defaults to nullptr.
     * @param arg Argument to pass to the process
     * @note The process will be run in a separate thread.
     */
    virtual void osRunProcess(OSInterfaceProcess process, const char* processName = nullptr, void* arg) = 0;

    virtual ~OSInterface() = default;
};

#endif // OSInterface_h
