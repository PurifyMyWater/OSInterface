#ifndef OSInterface_h
#define OSInterface_h

#include <cstdint>
#include <cstdio>
#include <cassert>

#define EXPAND_TO_STRING(x) #x
#define TOSTRING(x) EXPAND_TO_STRING(x)
#define AT "AT " __FILE__ ":" TOSTRING(__LINE__) ": "

#ifdef NDEBUG
    #define ASSERT_SAFE(expression, condition) expression
#else
    #define ASSERT_SAFE(expression, condition) assert(expression condition)
#endif

#define OSInterfaceLogVerbose(tag, format, ...)                                                                        \
    do                                                                                                                 \
    {                                                                                                                  \
        printf("Verbose - %s: " format "\n", tag, ##__VA_ARGS__);                                                      \
        fflush(stdout);                                                                                                \
    }                                                                                                                  \
    while (0)
#define OSInterfaceLogDebug(tag, format, ...)                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
        printf("Debug - %s: " format "\n", tag, ##__VA_ARGS__);                                                        \
        fflush(stdout);                                                                                                \
    }                                                                                                                  \
    while (0)
#define OSInterfaceLogInfo(tag, format, ...)                                                                           \
    do                                                                                                                 \
    {                                                                                                                  \
        printf("Info - %s: " format "\n", tag, ##__VA_ARGS__);                                                         \
        fflush(stdout);                                                                                                \
    }                                                                                                                  \
    while (0)
#define OSInterfaceLogWarning(tag, format, ...)                                                                        \
    do                                                                                                                 \
    {                                                                                                                  \
        printf("Warning " AT " - %s: " format "\n", tag, ##__VA_ARGS__);                                               \
        fflush(stdout);                                                                                                \
    }                                                                                                                  \
    while (0)
#define OSInterfaceLogError(tag, format, ...)                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
        printf("Error: " AT " - %s: " format "\n", tag, ##__VA_ARGS__);                                                \
        fflush(stdout);                                                                                                \
    }                                                                                                                  \
    while (0)
#define OSInterfaceSetLogLevel(tag, level)                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        printf("Mock: Set log level of tag '%s' to '%s'\n", tag, OSInterfaceLogLevelToString(level));                  \
        fflush(stdout);                                                                                                \
    }                                                                                                                  \
    while (0)
#define OSInterfaceGetLogLevel(tag) OSInterface_LOG_INFO

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
     * @param maxTimeToWait_ms Maximum time to wait in milliseconds
     * @return True if the mutex was acquired, false if the timeout was reached.
     */
    virtual bool wait(uint32_t maxTimeToWait_ms) = 0;
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
     * @param maxTimeToWait_ms Maximum time to wait in milliseconds
     * @return True if the semaphore was acquired, false if the timeout was reached.
     */
    virtual bool wait(uint32_t maxTimeToWait_ms) = 0;
};

class OSInterface_Timer
{
public:
    using Mode = enum { ONE_SHOT, PERIODIC };

    virtual ~OSInterface_Timer() = default;

    /**
     * @brief Start the timer
     *
     * @return True if the timer was started, false if there was an error.
     * @note If the timer is already running, the timer will re-evaluate its expiry time so that its period starts from
     * the beginning.
     */
    virtual bool start() = 0;

    /**
     * @brief Stop the timer
     *
     * @return True if the timer was stopped, false if there was an error.
     * @note If the timer is not running, this function does nothing.
     */
    virtual bool stop() = 0;

    /**
     * @brief Check if the timer is running
     *
     * @return True if the timer is running, false otherwise.
     */
    [[nodiscard]] virtual bool isRunning() const = 0;

    /**
     * @brief Change the timer period
     *
     * @param newPeriod_ms New timer period in milliseconds
     * @return True if the period was changed, false if there was an error.
     * @note If the timer is running, the timer will re-evaluate its expiry time so that its period starts from the
     * beginning.
     * @note If the timer is not running, the timer will start with the new period after this call.
     */
    virtual bool setPeriod(uint32_t newPeriod_ms) = 0;

    /**
     * @brief Get the timer period
     *
     * @return uint32_t Timer period in milliseconds
     */
    [[nodiscard]] virtual uint32_t getPeriod() const = 0;

    /**
     * @brief Get the timer mode
     *
     * @return The timer mode (one-shot or periodic)
     */
    [[nodiscard]] virtual Mode getMode() const = 0;

    /**
     * @brief Get the timer timeout value
     *
     * @return uint32_t Timer timeout value in milliseconds
     * @note This is the time remaining until the timer expires. If the timer is not running, this value is undefined.
     */
    [[nodiscard]] virtual uint32_t getTimeout() const = 0;

    /**
     * @brief Get the absolute time when the timer will expire
     *
     * @return uint32_t Absolute time in milliseconds when the timer will expire.
     * @note This is the absolute time (as returned by osMillis()) when the timer will expire. If the timer is not
     * running, this value is undefined.
     */
    [[nodiscard]] virtual uint32_t getTimeoutTime() const = 0;
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
     * @brief Create a timer
     *
     * @param period Timer period in milliseconds
     * @param mode Timer mode (one-shot or periodic)
     * @param callback Function to call when the timer expires
     * @param callbackArg Argument to pass to the callback function
     * @param timerName Name of the timer (can be nullptr)
     * @return OSInterface_Timer* Pointer to the created timer
     * @note If there are any errors during the creation, nullptr is returned.
     *
     * @note **Callback Execution Context and Thread-Safety:**
     *   - The callback is invoked from the context determined by the OSInterface implementation.
     *     Typically, this is a worker thread, not an interrupt service routine (ISR), but this may vary.
     *   - Callbacks for periodic timers cannot be invoked again before a previous invocation completes
     *     (i.e., callbacks must not overlap/reenter) unless otherwise specified by the implementation.
     *   - The thread-safety of the callback and any resources it accesses is the responsibility of the caller.
     *   - If the timer is stopped (via stop()), whether stop() waits for an in-flight callback to complete
     *     is implementation-defined. Users should consult the implementation or avoid assuming stop() blocks.
     *   - To avoid deadlocks, callbacks should not attempt to acquire locks that may be held by stop() or timer management code.
     */
    virtual OSInterface_Timer* osCreateTimer(uint32_t period, OSInterface_Timer::Mode mode, OSInterfaceProcess callback,
                                             void* callbackArg, const char* timerName) = 0;

    /**
     * @brief Allocate memory
     *
     * @param size Size of the memory to allocate
     * @return Void* Pointer to the allocated memory
     * @note If the size is 0, the function will return a null pointer.
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
    virtual void osRunProcess(OSInterfaceProcess process, void* arg) = 0;

    /**
     * @brief Run a process in a separate thread with a name
     *
     * @param process Process to run
     * @param processName Name of the process
     * @param arg Argument to pass to the process
     * @note The process will be run in a separate thread.
     */
    virtual void osRunProcess(OSInterfaceProcess process, const char* processName, void* arg) = 0;

    virtual ~OSInterface() = default;
};

#endif // OSInterface_h
