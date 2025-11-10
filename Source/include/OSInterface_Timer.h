#ifndef OSINTERFACE_OSINTERFACE_TIMER_H
#define OSINTERFACE_OSINTERFACE_TIMER_H

#include <cstdint>

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

#endif // OSINTERFACE_OSINTERFACE_TIMER_H
