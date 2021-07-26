#include "CompressedFile.h"

CompressedFile::CompressedFile(fs::File& f, uint8_t expansionBits, uint8_t lookaheadBits, size_t readBufferSize) : f(f), fileBuffer(f, readBufferSize){
	decoder = heatshrink_decoder_alloc(readBufferSize, expansionBits, lookaheadBits);
}

CompressedFile::~CompressedFile(){
	heatshrink_decoder_free(decoder);
}

fs::File CompressedFile::open(fs::File f, uint8_t expansionBits, uint8_t lookaheadBits, size_t readBufferSize){
	return File(std::make_shared<CompressedFile>(f, expansionBits, lookaheadBits, readBufferSize));
}

size_t CompressedFile::write(const uint8_t* buf, size_t size){
	return 0;
}

size_t CompressedFile::read(uint8_t* buf, size_t size){
	size_t bytesWritten = 0;
	fileBuffer.refill();

	while(bytesWritten < size){
		if(fileBuffer.available() > 0){
			size_t read = 0;
			heatshrink_decoder_sink(decoder, fileBuffer.data(), fileBuffer.available(), &read);
			fileBuffer.moveRead(read);
		}else{
			heatshrink_decoder_finish(decoder);
		}

		size_t bytesDecoded = 0;
		HSD_poll_res res = heatshrink_decoder_poll(decoder, buf + bytesWritten, size - bytesWritten, &bytesDecoded);
		bytesWritten += bytesDecoded;

		fileBuffer.refill();
		if(res == HSDR_POLL_EMPTY && fileBuffer.available() == 0){
			break;
		}
	}

	pos += bytesWritten;
	return bytesWritten;
}

void CompressedFile::flush(){
}

bool CompressedFile::seek(uint32_t pos, fs::SeekMode mode){
	if(pos == 0 && mode == SeekSet){
		this->pos = 0;
		f.seek(0);
		fileBuffer.clear();
		heatshrink_decoder_reset(decoder);
	}
}

size_t CompressedFile::position() const{
	return pos;
}

size_t CompressedFile::size() const{
	return 0;
}

void CompressedFile::close(){
	f.close();
}

time_t CompressedFile::getLastWrite(){
	return f.getLastWrite();
}

const char* CompressedFile::name() const{
	return f.name();
}

boolean CompressedFile::isDirectory(void){
	return f.isDirectory();
}

fs::FileImplPtr CompressedFile::openNextFile(const char* mode){
	return fs::FileImplPtr();
}

void CompressedFile::rewindDirectory(void){
	f.rewindDirectory();
}

CompressedFile::operator bool(){
	return (bool)(f);
}

bool CompressedFile::truncate(uint32_t size){
	return false;
}

const char* CompressedFile::fullName() const{
	return nullptr;
}

bool CompressedFile::isFile() const{
	return false;
}

bool CompressedFile::isDirectory() const{
	return false;
}
