#include "RingBuffer.h"

RingBuffer::RingBuffer(size_t size) : size(size + 1){
#ifdef CONFIG_SPIRAM_SUPPORT
	if(psramFound()){
		buffer = static_cast<uint8_t*>(ps_malloc(size));
	}else{
		buffer = static_cast<uint8_t*>(malloc(size));
	}
#else
	buffer = static_cast<uint8_t*>(malloc(size));
#endif
}

RingBuffer::~RingBuffer(){
	free(buffer);
}

size_t RingBuffer::writeAvailable(){
	if(end >= beginning) return size + beginning - end - 1;
	else return beginning - end - 1;
}

size_t RingBuffer::readAvailable(){
	if(end >= beginning) return end - beginning;
	else return size + end - beginning;
}

size_t RingBuffer::read(uint8_t* destination, size_t n){
	n = min(n, readAvailable());
	if(n == 0) return 0;

	if(end > beginning){
		memcpy(destination, buffer + beginning, n);
	}else{
		size_t first = min(size - beginning, n);
		memcpy(destination, buffer + beginning, first);
		memcpy(destination + first, buffer, n - first);
	}

	beginning = (beginning + n) % size;
	return n;
}

size_t RingBuffer::write(uint8_t* source, size_t n){
	n = min(n, writeAvailable());
	if(n == 0) return 0;

	if(beginning > end){
		memcpy(buffer + end, source, n);
	}else{
		size_t first = min(size - end, n);
		memcpy(buffer + end, source, first);
		memcpy(buffer, source + first, n - first);
	}

	end = (end + n) % size;
	return n;
}

void RingBuffer::clear(){
	beginning = end = 0;
}
