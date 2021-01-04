#include "PGMFile.h"

PGMFile::PGMFile(const uint8_t* data, size_t size) : data(data), dataSize(size){

}

PGMFile::~PGMFile(){
	close();
}

size_t PGMFile::write(uint8_t data){
	return 0;
	// this->data[cursor++] = data;
	return 1;
}

size_t PGMFile::write(const uint8_t* buf, size_t size){
	return 0;
	//memcpy(data + cursor, buf, size);
	cursor += size;
}

int PGMFile::available(){
	return cursor < dataSize;
}

int PGMFile::read(){
	return pgm_read_byte(data + cursor++);
}

int PGMFile::peek(){
	return pgm_read_byte(data + cursor);
}

void PGMFile::flush(){

}

bool PGMFile::seek(uint32_t pos, fs::SeekMode mode){
	switch(mode){
		case fs::SeekSet:
			cursor = pos;
			break;
		case fs::SeekEnd:
			cursor = dataSize - pos - 1;
			break;
		case fs::SeekCur:
			cursor += pos;
			break;
	}
}

bool PGMFile::seek(uint32_t pos){
	return seek(pos, SeekSet);
}

size_t PGMFile::read(uint8_t* buf, size_t size){
	if(cursor >= dataSize) return 0;

	size_t availableSize;
	if(cursor + size <= dataSize){
		availableSize = size;
	}else{
		availableSize = dataSize - cursor - 1;
	}

	for(int i = 0; i < availableSize; i++){
		buf[i] = read();
	}

	return availableSize;
}

size_t PGMFile::position() const{
	return cursor;
}

size_t PGMFile::size() const{
	return dataSize;
}

void PGMFile::close(){
	data = nullptr;
	dataSize = 0;
}

PGMFile::operator bool(){
	return data != nullptr;
}

bool PGMFile::isDirectory(){
	return false;
}

time_t PGMFile::getLastWrite(){
	return 0;
}

const char* PGMFile::name() const {
	return nullptr;
}

void PGMFile::rewindDirectory() {

}

fs::FileImplPtr PGMFile::openNextFile(const char* mode){
	return fs::FileImplPtr();
}
