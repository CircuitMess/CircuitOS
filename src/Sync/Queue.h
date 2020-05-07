#ifndef CIRCUITOS_QUEUE_H
#define CIRCUITOS_QUEUE_H

#include <Arduino.h>

#define INCLUDE_vTaskSuspend 1
#include <freertos/queue.h>

class Queue {
public:
	Queue(size_t queueSize, size_t msgSize);
	~Queue();

	/**
	 * @return The number of messages in the queue.
	 */
	int count();

	/**
	 * Remove all messages from the queue.
	 */
	void reset();

	/**
	 * Return the first message in the queue. This is a non-blocking function and will return if the queue is empty.
	 * @param buffer
	 * @return True if the message was received, false if the queue is empty or an error occurred.
	 */
	bool peek(void* buffer);

	/**
	 * Post a message to the back of the queue. This is a blocking function and will wait if the queue is full.
	 * @param msg
	 * @return True if the message was posted, false if an error occurred.
	 */
	bool send(void* msg);

	/**
	 * Retrieve a message from the front of a queue. This is a blocking function and will wait if the queue is empty.
	 * @param msg
	 * @returnTrue if the message was retrieved, false if an error occurred.
	 */
	bool receive(void* msg);

	/**
	 * Resize the queue. This clears all the messages in the queue.
	 * @param queueSize
	 */
	void resize(size_t queueSize);

	size_t getQueueSize() const;

	size_t getMsgSize() const;


private:
	QueueHandle_t queue;
	size_t queueSize;
	size_t msgSize;

};


#endif //CIRCUITOS_QUEUE_H
