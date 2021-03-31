#include "DataBuffer.h"

DataBuffer::DataBuffer(const size_t size, bool local) : size(size){
	if(psramFound() && !local){
		buffer = static_cast<uint8_t*>(ps_malloc(size));
	}else{
		buffer = static_cast<uint8_t*>(malloc(size));
	}
}

DataBuffer::~DataBuffer(){
	free(buffer);
}

size_t DataBuffer::readAvailable(){
	return writeCursor - readCursor;
}

bool DataBuffer::readMove(size_t amount){
	if(readCursor + amount > writeCursor) return false;
	readCursor += amount;
	return true;
}

uint8_t* DataBuffer::writeData(){
	if(writeCursor == 0) return buffer;

	size_t left = writeCursor - readCursor;
	if(left == 0){
		writeCursor = readCursor = 0;
		return buffer;
	}

	memmove(buffer, buffer + readCursor, left);
	readCursor = 0;
	writeCursor = left;

	return buffer + writeCursor;
}

void DataBuffer::clear(){
	readCursor = 0;
	writeCursor = 0;
}

const uint8_t* DataBuffer::readData(){
	return buffer + readCursor;
}

size_t DataBuffer::writeAvailable(){
	return readCursor + (size - writeCursor);
}

bool DataBuffer::writeMove(size_t amount){
	if(writeCursor + amount > size) return false;
	writeCursor += amount;
	return true;
}
