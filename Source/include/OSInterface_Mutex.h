#ifndef OSINTERFACE_OSINTERFACE_MUTEX_H
#define OSINTERFACE_OSINTERFACE_MUTEX_H

#include <cstdint>

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

#endif // OSINTERFACE_OSINTERFACE_MUTEX_H
