#ifndef OSInterface_h
#define OSInterface_h

#include <cassert>
#include <cstdint>
#include "OSInterface_BinarySemaphore.h"
#include "OSInterface_Log.h"
#include "OSInterface_Mutex.h"
#include "OSInterface_Timer.h"
#include "OSInterface_UntypedQueue.h"

#define EXPAND_TO_STRING(x) #x
#define TOSTRING(x) EXPAND_TO_STRING(x)
#define AT "AT " __FILE__ ":" TOSTRING(__LINE__) ": "

#ifdef NDEBUG
    #define ASSERT_SAFE(expression, condition) expression
#else
    #define ASSERT_SAFE(expression, condition) assert(expression condition)
#endif

using OSInterfaceProcess = void (*)(void* arg);

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
     * @note If there are any errors during the creation, nullptr is returned.
     */
    virtual OSInterface_Mutex* osCreateMutex() = 0;

    /**
     * @brief Create a binary semaphore
     *
     * @return OSInterface_BinarySemaphore* Pointer to the created binary semaphore
     * @note The semaphore is created with the initial value of 0.
     * @note The semaphore needs to be freed with delete.
     * @note If there are any errors during the creation, nullptr is returned.
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
     * @note The timer needs to be freed with delete.
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
     *   - To avoid deadlocks, callbacks should not attempt to acquire locks that may be held by stop() or timer
     * management code.
     */
    virtual OSInterface_Timer* osCreateTimer(uint32_t period, OSInterface_Timer::Mode mode, OSInterfaceProcess callback,
                                             void* callbackArg, const char* timerName) = 0;

    /**
     * @brief Create an inter-thread, untyped thread-safe message queue. To use typed messages, use
     * OSInterface::OSInterface_Queue<T>.
     *
     * @param maxMessages Maximum number of messages in the queue
     * @param messageSize Size of each message in bytes
     * @return OSInterface_UntypedQueue* Pointer to the created queue
     * @note The queue needs to be freed with delete.
     * @note If there are any errors during the creation, nullptr is returned.
     */
    virtual OSInterface_UntypedQueue* osCreateUntypedQueue(uint32_t maxMessages, uint32_t messageSize) = 0;

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

    template <typename T> class OSInterface_Queue;
};

#include "OSInterface_Queue.h"

#endif // OSInterface_h
