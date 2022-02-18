#include "NullStream.h"

NullStream::NullStream(){
	setTimeout(0);     // no timeout.
}

int NullStream::available(){
	return 0;
}

int NullStream::peek(){
	return EOF;
}

int NullStream::read(){
	return EOF;
}

void NullStream::flush(){
	return;
}

size_t NullStream::write(const uint8_t data){
	bottomlessPit = data;
	return 1;
}

size_t NullStream::write(const uint8_t* buffer, size_t size){
	if(size > 0) bottomlessPit = buffer[size - 1];
	return size;
}
