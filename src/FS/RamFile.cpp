#include "RamFile.h"

RamFile::RamFile(uint8_t* data, size_t size, bool readonly) : data(data), dataSize(size), readonly(readonly){

}

RamFile::~RamFile(){
	RamFile::close();
}

fs::File RamFile::open(uint8_t* data, size_t size, bool readonly){
	return File(std::make_shared<RamFile>(data, size, readonly));
}

fs::File RamFile::open(fs::File file, bool readonly){
	uint8_t* data;
#ifdef CONFIG_SPIRAM_SUPPORT
	data = static_cast<uint8_t*>(ps_malloc(file.size()));
#else
	data = static_cast<uint8_t*>(malloc(file.size()));
#endif

	file.seek(0);
	file.readBytes(reinterpret_cast<char*>(data), file.size());

	auto f = std::make_shared<RamFile>(data, file.size(), readonly);

	f->filename = file.name();

	return File(f);
}

fs::File RamFile::create(const String& filename){
	auto f = std::make_shared<RamFile>(nullptr, 0, false);
	f->filename = filename;
	return File(f);
}

size_t RamFile::write(uint8_t data){
	if(readonly) return 0;

	if(cursor == dataSize){
		dataSize++;
	}

	this->data[cursor++] = data;
	return 1;
}

size_t RamFile::write(const uint8_t* buf, size_t size){
	if(readonly) return 0;
	if(size == 0) return 0;

	if(cursor + size > dataSize){
		dataSize = size + cursor;
#ifdef CONFIG_SPIRAM_SUPPORT
		data = static_cast<uint8_t*>(ps_realloc(data, dataSize));
#else
		data = static_cast<uint8_t*>(realloc(data, dataSize));
#endif
	}

	memcpy(data + cursor, buf, size);
	cursor += size;

	return size;
}

int RamFile::available(){
	return dataSize - cursor;
}

int RamFile::read(){
	return *(data + cursor++);
}

int RamFile::peek(){
	return *(data + cursor);
}

void RamFile::flush(){

}

bool RamFile::seek(uint32_t pos, fs::SeekMode mode){
	if(mode == fs::SeekSet){
		cursor = pos;
	}else if(mode == fs::SeekEnd){
		cursor = dataSize - pos;
	}else if(mode == fs::SeekCur){
		cursor += pos;
	}
	return true;
}

bool RamFile::seek(uint32_t pos){
	return seek(pos, SeekSet);
}

RETURN_TYPE RamFile::read(uint8_t* buf, size_t size){
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
	delete data;

	data = nullptr;
	dataSize = 0;
	filename = "";
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
	return filename.c_str();
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
