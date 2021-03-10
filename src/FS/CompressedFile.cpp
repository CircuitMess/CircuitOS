#include "CompressedFile.h"

CompressedFile::CompressedFile(File& f) : f(f){

}

fs::File CompressedFile::open(File& f){
	return File(std::make_shared<CompressedFile>(f));
}

size_t CompressedFile::write(const uint8_t* buf, size_t size){
	return f.write(buf, size);
}

size_t CompressedFile::read(uint8_t* buf, size_t size){
	// TODO
}

void CompressedFile::flush(){
	f.flush(); // TODO
}

bool CompressedFile::seek(uint32_t pos, SeekMode mode){
	return f.seek(pos, mode); // TODO
}

size_t CompressedFile::position() const{
	return 0;
}

size_t CompressedFile::size() const{
	return 0;
}

void CompressedFile::close(){

}

time_t CompressedFile::getLastWrite(){
	return 0;
}

const char* CompressedFile::name() const{
	return nullptr;
}

boolean CompressedFile::isDirectory(void){
	return 0;
}

fs::FileImplPtr CompressedFile::openNextFile(const char* mode){
	return fs::FileImplPtr();
}

void CompressedFile::rewindDirectory(void){

}

CompressedFile::operator bool(){
	return false;
}
