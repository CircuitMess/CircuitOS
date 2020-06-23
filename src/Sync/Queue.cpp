#include "Queue.h"

Queue::Queue(size_t queueSize, size_t msgSize) : queueSize(queueSize), msgSize(msgSize){
	queue = xQueueCreate(queueSize, msgSize);
}

Queue::~Queue(){
	vQueueDelete(queue);
}

int Queue::count(){
	return uxQueueMessagesWaiting(queue);
}

void Queue::reset(){
	xQueueReset(queue);
}

bool Queue::peek(void* buffer){
	return xQueuePeek(queue, buffer, 0);
}

bool Queue::send(void* msg){
	return xQueueSend(queue, msg, portMAX_DELAY);
}

bool Queue::receive(void* msg){
	return xQueueReceive(queue, msg, portMAX_DELAY);
}

void Queue::resize(size_t queueSize){
	vQueueDelete(queue);
	queue = xQueueCreate(queueSize, msgSize);
	this->queueSize = queueSize;
}

size_t Queue::getQueueSize() const{
	return queueSize;
}

size_t Queue::getMsgSize() const{
	return msgSize;
}

