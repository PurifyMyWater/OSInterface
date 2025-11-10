#ifndef OSINTERFACE_OSINTERFACE_BINARYSEMAPHORE_H
#define OSINTERFACE_OSINTERFACE_BINARYSEMAPHORE_H

#include <cstdint>

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

#endif // OSINTERFACE_OSINTERFACE_BINARYSEMAPHORE_H
