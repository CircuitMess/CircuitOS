#include "FSBuffer.h"

FSBuffer::FSBuffer(const File& file, const size_t size) : file(file), size(size){
	buffer = static_cast<uint8_t*>(malloc(size));
}

FSBuffer::~FSBuffer(){
	free(buffer);
}

size_t FSBuffer::available(){
	return bytesFilled - cursor;
}

bool FSBuffer::moveRead(size_t amount){
	if(cursor + amount > bytesFilled) return false;
	cursor += amount;
	return true;
}

bool FSBuffer::refill(){
	if(cursor != bytesFilled){
		memmove(buffer, buffer + cursor, max(int(bytesFilled - cursor), 0));
	}else{
		clear();
	}
	bytesFilled = file.read(buffer + cursor, (bytesFilled == 0) ? size : (bytesFilled - cursor));
	cursor = 0;

	if(bytesFilled == 0) return false;
	else return true;
}

void FSBuffer::clear(){
	cursor = 0;
}

const uint8_t* FSBuffer::data(){
	return buffer + cursor;
}

File& FSBuffer::getFile(){
	return file;
}