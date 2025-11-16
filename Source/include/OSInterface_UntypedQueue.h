#ifndef OSINTERFACE_OSINTERFACE_UNTYPEDQUEUE_H
#define OSINTERFACE_OSINTERFACE_UNTYPEDQUEUE_H

#include <cstdint>
#include "OSInterface.h"

class OSInterface_UntypedQueue
{
public:
    virtual ~OSInterface_UntypedQueue() = default;

    /**
     * @brief Get the number of messages currently in the queue
     *
     * @return int Number of messages in the queue
     */
    virtual uint32_t length() = 0;

    /**
     * @brief Get the number of slots in the queue
     *
     * @return int Number of slots in the queue
     */
    virtual uint32_t size() = 0;

    /**
     * @brief Get the number of empty slots in the queue
     *
     * @return int Number of empty slots in the queue
     */
    virtual uint32_t available() = 0;

    /**
     * @brief Check if the queue is empty
     *
     * @return true if the queue is empty, false otherwise
     */
    virtual bool isEmpty() = 0;

    /**
     * @brief Check if the queue is full
     *
     * @return true if the queue is full, false otherwise
     */
    virtual bool isFull() = 0;

    /**
     * @brief Reset the queue, removing all messages
     */
    virtual void reset() = 0;

    /**
     * @brief Receive a message from the queue
     *
     * @param message Reference to store the received message. The message buffer must be of size messageSize specified
     * during queue creation.
     * @param maxTimeToWait_ms Maximum time to wait in milliseconds
     * @return true if a message was received, false if the timeout was reached
     */
    virtual bool receive(void* message, uint32_t maxTimeToWait_ms) = 0;

    /**
     * @brief Receive a message from the queue from an ISR
     *
     * @param message Reference to store the received message. The message buffer must be of size messageSize specified
     * during queue creation.
     * @return true if a message was received, false otherwise
     */
    virtual bool receiveFromISR(void* message) = 0;

    /**
     * @brief Send a message to the back of the queue
     *
     * @param message Message to send. Must be of size messageSize specified during queue creation.
     * @param maxTimeToWait_ms Maximum time to wait in milliseconds
     * @return true if the message was sent, false if the timeout was reached
     */
    virtual bool sendToBack(const void* message, uint32_t maxTimeToWait_ms) = 0;

    /**
     * @brief Send a message to the back of the queue from an ISR
     *
     * @param message Message to send. Must be of size messageSize specified during queue creation.
     * @return true if the message was sent, false otherwise
     */
    virtual bool sendToBackFromISR(const void* message) = 0;

    /**
     * @brief Send a message to the front of the queue
     *
     * @param message Message to send. Must be of size messageSize specified during queue creation.
     * @param maxTimeToWait_ms Maximum time to wait in milliseconds
     * @return true if the message was sent, false if the timeout was reached
     */
    virtual bool sendToFront(const void* message, uint32_t maxTimeToWait_ms) = 0;

    /**
     * @brief Send a message to the front of the queue from an ISR
     *
     * @param message Message to send. Must be of size messageSize specified during queue creation.
     * @return true if the message was sent, false otherwise
     */
    virtual bool sendToFrontFromISR(const void* message) = 0;
};

#endif // OSINTERFACE_OSINTERFACE_UNTYPEDQUEUE_H
