#include "FSBuffer.h"

FSBuffer::FSBuffer(const File& file, const size_t size) : file(file), size(size){
	buffer = static_cast<uint8_t*>(malloc(size));
}

FSBuffer::~FSBuffer(){
	free(buffer);
}

size_t FSBuffer::available(){
	return size - cursor;
}

bool FSBuffer::moveRead(size_t amount){
	if(cursor + amount > size) return false;
	cursor += amount;
	return true;
}

void FSBuffer::refill(){
	if(cursor != size){
		memmove(buffer, buffer + cursor, size - cursor);
	}

	file.read(buffer + cursor, size - cursor);
	cursor = 0;
}

void FSBuffer::clear(){
	cursor = 0;
}

const uint8_t* FSBuffer::data(){
	return buffer + cursor;
}
