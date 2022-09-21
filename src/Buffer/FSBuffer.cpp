#include "FSBuffer.h"

FSBuffer::FSBuffer(fs::File file, const size_t size) : file(file), size(size){
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
	size_t remaining = bytesFilled - cursor;

	if(remaining != 0){
		memmove(buffer, buffer + cursor, remaining);
	}

	bytesFilled = file.read(buffer + remaining, size - remaining);
	bytesFilled += remaining;
	cursor = 0;

	return bytesFilled != 0;
}

void FSBuffer::clear(){
	cursor = 0;
}

const uint8_t* FSBuffer::data(){
	return buffer + cursor;
}

File FSBuffer::getFile() const{
	return file;
}