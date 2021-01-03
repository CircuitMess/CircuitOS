#include "SerialFlashFileAdapter.h"
#include <SerialFlash.h>

SerialFlashFileAdapter::SerialFlashFileAdapter(SerialFlashFile* _file) : file(_file){
}

SerialFlashFileAdapter::SerialFlashFileAdapter(const char* path) : file(new SerialFlashFile()){
	while(!SerialFlash.ready());
	*file = SerialFlash.open(path);
	
	if(!(*file)){
		file->close();
		Serial.println("BAD FILE");
	}
	Serial.printf("file opened %s\n", path);
	delay(5);
}

SerialFlashFileAdapter::~SerialFlashFileAdapter(){
	close();
	delete file;
}

size_t SerialFlashFileAdapter::write(uint8_t data){
	return file->write((void*)data, 1);
}

size_t SerialFlashFileAdapter::write(const uint8_t* buf, size_t size){
	return file->write(buf, size);
}

int SerialFlashFileAdapter::available(){
	return file->available();
}

int SerialFlashFileAdapter::read(){
	int output;
	if(file->read((void*)output, 1) == 0) return 0;
	return output;
}

int SerialFlashFileAdapter::peek(){
	int output;
	if(file->read((void*)output, 1) == 0) return 0;
	file->seek(file->position() - 1);
	return output;
}

void SerialFlashFileAdapter::flush(){

}

bool SerialFlashFileAdapter::seek(uint32_t pos, fs::SeekMode mode){
	switch(mode){
		case fs::SeekSet:
			file->seek(pos);
			break;
		case fs::SeekEnd:
			file->seek(file->size() - pos - 1);
			break;
		case fs::SeekCur:
			file->seek(file->position() + pos);
			break;
	}
	return true;
}

bool SerialFlashFileAdapter::seek(uint32_t pos){
	return seek(pos, fs::SeekSet);
}

size_t SerialFlashFileAdapter::read(uint8_t* buf, size_t size){
	return file->read(buf, size);
}

size_t SerialFlashFileAdapter::position() const{
	return file->position();
}

size_t SerialFlashFileAdapter::size() const{
	return file->size();
}

void SerialFlashFileAdapter::close(){
	file->close();
}

SerialFlashFileAdapter::operator bool(){
	// Serial.printf("file ok: %d", bool(*file));
	// delay(5);
	return bool(*file);
}

bool SerialFlashFileAdapter::isDirectory(){
	return false;
}

time_t SerialFlashFileAdapter::getLastWrite(){
	return 0;
}

const char* SerialFlashFileAdapter::name() const {
	return nullptr;
}

void SerialFlashFileAdapter::rewindDirectory() {

}

fs::FileImplPtr SerialFlashFileAdapter::openNextFile(const char* mode){
	return fs::FileImplPtr();
}
