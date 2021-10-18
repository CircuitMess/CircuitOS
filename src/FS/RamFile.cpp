#include "RamFile.h"

RamFile::RamFile(uint8_t* data, size_t size) : data(data), dataSize(size){

}

RamFile::~RamFile(){
	delete data;
}

fs::File RamFile::open(uint8_t* data, size_t size){
	return File(std::make_shared<RamFile>(data, size));
}

fs::File RamFile::open(fs::File file){
	uint8_t* data;
#ifdef CONFIG_SPIRAM_SUPPORT
	data = static_cast<uint8_t*>(ps_malloc(file.size()));
#else
	data = static_cast<uint8_t*>(malloc(file.size()));
#endif

	file.seek(0);
	file.readBytes(reinterpret_cast<char*>(data), file.size());
	return File(std::make_shared<RamFile>(data, file.size()));
}

size_t RamFile::write(uint8_t data){
	this->data[cursor++] = data;
	return 1;
}

size_t RamFile::write(const uint8_t* buf, size_t size){
	memcpy(data + cursor, buf, size);
	cursor += size;
}

int RamFile::available(){
	return cursor < dataSize;
}

int RamFile::read(){
	return pgm_read_byte(data + cursor++);
}

int RamFile::peek(){
	return pgm_read_byte(data + cursor);
}

void RamFile::flush(){

}

bool RamFile::seek(uint32_t pos, fs::SeekMode mode){
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

bool RamFile::seek(uint32_t pos){
	return seek(pos, SeekSet);
}

size_t RamFile::read(uint8_t* buf, size_t size){
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

size_t RamFile::position() const{
	return cursor;
}

size_t RamFile::size() const{
	return dataSize;
}

void RamFile::close(){
	data = nullptr;
	dataSize = 0;
}

RamFile::operator bool(){
	return data != nullptr;
}

bool RamFile::isDirectory(){
	return false;
}

time_t RamFile::getLastWrite(){
	return 0;
}

const char* RamFile::name() const {
	return nullptr;
}

void RamFile::rewindDirectory() {

}

fs::FileImplPtr RamFile::openNextFile(const char* mode){
	return fs::FileImplPtr();
}

bool RamFile::truncate(uint32_t size){
	return false;
}

const char* RamFile::fullName() const{
	return nullptr;
}

bool RamFile::isFile() const{
	return false;
}

bool RamFile::isDirectory() const{
	return false;
}
