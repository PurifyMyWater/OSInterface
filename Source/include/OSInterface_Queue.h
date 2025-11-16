#ifndef OSINTERFACE_OSINTERFACE_QUEUE_H
#define OSINTERFACE_OSINTERFACE_QUEUE_H

#include <cstdint>
#include "OSInterface_UntypedQueue.h"
#include "OSInterface.h"

template <typename T> class OSInterface::OSInterface_Queue
{
public:
    /**
     * @brief Create an inter-process, thread-safe message queue
     *
     * @param osInterface Reference to the OSInterface to use for creating the queue
     * @param maxMessages Maximum number of messages in the queue
     * @param result Reference to store the result of the queue creation. True if the queue was created successfully, false otherwise.
     */
    OSInterface_Queue(OSInterface& osInterface, uint32_t maxMessages, bool& result)
    {
        queue = osInterface.osCreateUntypedQueue(maxMessages, sizeof(T));
        result = (queue != nullptr);
    }

    ~OSInterface_Queue()
    {
        delete queue;
    }

    /**
     * @brief Get the number of messages currently in the queue
     *
     * @return int Number of messages in the queue
     */
    uint32_t length()
    {
        return queue->length();
    }

    /**
     * @brief Get the number of slots in the queue
     *
     * @return int Number of slots in the queue
     */
    uint32_t size()
    {
        return queue->size();
    }

    /**
     * @brief Get the number of empty slots in the queue
     *
     * @return int Number of empty slots in the queue
     */
    uint32_t available()
    {
        return queue->available();
    }

    /**
     * @brief Check if the queue is empty
     *
     * @return true if the queue is empty, false otherwise
     */
    bool isEmpty()
    {
        return queue->isEmpty();
    }

    /**
     * @brief Check if the queue is full
     *
     * @return true if the queue is full, false otherwise
     */
    bool isFull()
    {
        return queue->isFull();
    }

    /**
     * @brief Reset the queue, removing all messages
     */
    void reset()
    {
        queue->reset();
    }

    /**
     * @brief Receive a message from the queue
     *
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
