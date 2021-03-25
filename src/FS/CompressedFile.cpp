#include "CompressedFile.h"
#include "../Buffer/FSBuffer.h"

CompressedFile::CompressedFile(fs::File& f, uint8_t expansionBits, uint8_t lookaheadBits) : f(f){
	decoder = heatshrink_decoder_alloc(FSBUFFER_SIZE, expansionBits, lookaheadBits);
	fileBuffer = new FSBuffer(f, FSBUFFER_SIZE);
}

CompressedFile::~CompressedFile(){
	heatshrink_decoder_free(decoder);
	delete fileBuffer;
}

fs::File CompressedFile::open(fs::File f, uint8_t expansionBits, uint8_t lookaheadBits){
	return File(std::make_shared<CompressedFile>(f, expansionBits, lookaheadBits));
}

size_t CompressedFile::write(const uint8_t* buf, size_t size){
	return 0;
}

size_t CompressedFile::read(uint8_t* buf, size_t size){

	size_t polledBytes = 0;

	//use leftover polling buffer from earlier
	if(pollLeft){
		size_t singlePollSize = 0;
		HSD_poll_res pollRes = heatshrink_decoder_poll(decoder, buf + polledBytes, size - polledBytes, &singlePollSize);
		polledBytes+=singlePollSize;
		pollLeft = (pollRes == HSDR_POLL_MORE);
	}

	while(polledBytes < size){
		size_t singleSinkSize = 0;
		bool moreSink = fileBuffer->refill();
		if(moreSink){
			heatshrink_decoder_sink(decoder, (uint8_t*)fileBuffer->data(), fileBuffer->available(), &singleSinkSize);
			fileBuffer->moveRead(singleSinkSize);
		}else{
			heatshrink_decoder_finish(decoder);
		}

		size_t singlePollSize = 0;
		HSD_poll_res pollRes = heatshrink_decoder_poll(decoder, buf + polledBytes, size - polledBytes, &singlePollSize);
		polledBytes+=singlePollSize;
		pollLeft = (pollRes == HSDR_POLL_MORE);
		if(!pollLeft && !moreSink) break; //reached end of file and decoder output is empty
	}
	decodedCursor+=polledBytes;
	return polledBytes;
}

void CompressedFile::flush(){
}

bool CompressedFile::seek(uint32_t pos, fs::SeekMode mode){
}

size_t CompressedFile::position() const{
	return 0;
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
