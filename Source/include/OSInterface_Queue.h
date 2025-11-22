#ifndef OSINTERFACE_OSINTERFACE_QUEUE_H
#define OSINTERFACE_OSINTERFACE_QUEUE_H

#include <cstdint>
#include "OSInterface.h"
#include "OSInterface_UntypedQueue.h"

/**
 * @brief Template wrapper for inter-process, thread-safe message queues
 *
 * @warning Methods of this class MUST NOT be called if the constructor failed (result is false).
 *          Calling methods on a queue that failed to construct will result in undefined behavior.
 *          Always check the result parameter from the constructor before using the queue.
 *
 * @tparam T The type of messages to store in the queue
 */
template <typename T> class OSInterface::OSInterface_Queue
{
public:
    /**
     * @brief Create an inter-thread, thread-safe message queue
     *
     * @param osInterface Reference to the OSInterface to use for creating the queue
     * @param maxMessages Maximum number of messages in the queue
     * @param result Reference to store the result of the queue creation. True if the queue was created successfully,
     * false otherwise. MUST be checked before calling any other methods on this object.
     */
    OSInterface_Queue(OSInterface& osInterface, uint32_t maxMessages, bool& result) :
        queue(osInterface.osCreateUntypedQueue(maxMessages, sizeof(T)))
    {
        result = (queue != nullptr);
    }

    // Delete copy constructor and copy assignment operator to prevent double-delete issues
    OSInterface_Queue(const OSInterface_Queue&)            = delete;
    OSInterface_Queue& operator=(const OSInterface_Queue&) = delete;

    // Delete move constructor and move assignment operator to prevent ownership transfer issues
    OSInterface_Queue(OSInterface_Queue&&)            = delete;
    OSInterface_Queue& operator=(OSInterface_Queue&&) = delete;

    ~OSInterface_Queue()
    {
        delete queue;
    }

    /**
     * @brief Get the number of messages currently in the queue
     *
     * @pre Queue must have been successfully constructed (constructor result was true)
     * @return int Number of messages in the queue
     */
    uint32_t length()
    {
        return queue->length();
    }

    /**
     * @brief Get the number of slots in the queue
     *
     * @pre Queue must have been successfully constructed (constructor result was true)
     * @return int Number of slots in the queue
     */
    uint32_t size()
    {
        return queue->size();
    }

    /**
     * @brief Get the number of empty slots in the queue
     *
     * @pre Queue must have been successfully constructed (constructor result was true)
     * @return int Number of empty slots in the queue
     */
    uint32_t available()
    {
        return queue->available();
    }

    /**
     * @brief Check if the queue is empty
     *
     * @pre Queue must have been successfully constructed (constructor result was true)
     * @return true if the queue is empty, false otherwise
     */
    bool isEmpty()
    {
        return queue->isEmpty();
    }

    /**
     * @brief Check if the queue is full
     *
     * @pre Queue must have been successfully constructed (constructor result was true)
     * @return true if the queue is full, false otherwise
     */
    bool isFull()
    {
        return queue->isFull();
    }

    /**
     * @brief Reset the queue, removing all messages
     *
     * @pre Queue must have been successfully constructed (constructor result was true)
     */
    void reset()
    {
        queue->reset();
    }

    /**
     * @brief Receive a message from the queue
     *
     * @pre Queue must have been successfully constructed (constructor result was true)
     * @param message Reference to store the received message
     * @param maxTimeToWait_ms Maximum time to wait in milliseconds
     * @return true if a message was received, false if the timeout was reached
     */
    bool receive(T& message, uint32_t maxTimeToWait_ms)
    {
        return queue->receive(&message, maxTimeToWait_ms);
    }

    /**
     * @brief Receive a message from the queue from an ISR
     *
     * @pre Queue must have been successfully constructed (constructor result was true)
     * @param message Reference to store the received message
     * @return true if a message was received, false otherwise
     */
    bool receiveFromISR(T& message)
    {
        return queue->receiveFromISR(&message);
    }

    /**
     * @brief Send a message to the back of the queue
     *
     * @pre Queue must have been successfully constructed (constructor result was true)
     * @param message Message to send
     * @param maxTimeToWait_ms Maximum time to wait in milliseconds
     * @return true if the message was sent, false if the timeout was reached
     */
    bool sendToBack(const T& message, uint32_t maxTimeToWait_ms)
    {
        return queue->sendToBack(&message, maxTimeToWait_ms);
    }

    /**
     * @brief Send a message to the back of the queue from an ISR
     *
     * @pre Queue must have been successfully constructed (constructor result was true)
     * @param message Message to send
     * @return true if the message was sent, false otherwise
     */
    bool sendToBackFromISR(const T& message)
    {
        return queue->sendToBackFromISR(&message);
    }

    /**
     * @brief Send a message to the front of the queue
     *
     * @pre Queue must have been successfully constructed (constructor result was true)
     * @param message Message to send
     * @param maxTimeToWait_ms Maximum time to wait in milliseconds
     * @return true if the message was sent, false if the timeout was reached
     */
    bool sendToFront(const T& message, uint32_t maxTimeToWait_ms)
    {
        return queue->sendToFront(&message, maxTimeToWait_ms);
    }

    /**
     * @brief Send a message to the front of the queue from an ISR
     *
     * @pre Queue must have been successfully constructed (constructor result was true)
     * @param message Message to send
     * @return true if the message was sent, false otherwise
     */
    bool sendToFrontFromISR(const T& message)
    {
        return queue->sendToFrontFromISR(&message);
    }

private:
    OSInterface_UntypedQueue* queue;
};

#endif // OSINTERFACE_OSINTERFACE_QUEUE_H
