#include "LazyDataBuffer.h"

LazyDataBuffer::LazyDataBuffer(const size_t size) : size(size){
#ifdef CONFIG_SPIRAM_SUPPORT
	if(psramFound() && !local){
		buffer = static_cast<uint8_t*>(ps_malloc(size));
	}else{
		buffer = static_cast<uint8_t*>(malloc(size));
	}
#else
	buffer = static_cast<uint8_t*>(malloc(size));
#endif
}

LazyDataBuffer::~LazyDataBuffer(){
	free(buffer);
}

size_t LazyDataBuffer::readAvailable(){
	return writeCursor - readCursor;
}

bool LazyDataBuffer::readMove(size_t amount){
	if(readCursor + amount > writeCursor) return false;
	readCursor += amount;
	return true;
}

uint8_t* LazyDataBuffer::writeData(){
	return buffer + writeCursor;
}

void LazyDataBuffer::relocate(){
	size_t left = writeCursor - readCursor;
	if(left == 0){
		writeCursor = readCursor = 0;
		return;
	}

	memmove(buffer, buffer + readCursor, left);

	readCursor = 0;
	writeCursor = left;
}

void LazyDataBuffer::clear(){
	readCursor = 0;
}

const uint8_t* LazyDataBuffer::readData(){
	return buffer + readCursor;
}

size_t LazyDataBuffer::writeAvailable(){
	return size - writeCursor;
}

size_t LazyDataBuffer::potentialWriteAvailable(){
	return readCursor;
}

bool LazyDataBuffer::writeMove(size_t amount){
	if(writeCursor + amount > size) return false;
	writeCursor += amount;
	return true;
}
