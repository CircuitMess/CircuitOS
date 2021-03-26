#ifndef CIRCUITOS_COMPRESSEDFILE_H
#define CIRCUITOS_COMPRESSEDFILE_H

#include <Arduino.h>
#include <FS.h>
#include <FSImpl.h>
#include <heatshrink_decoder.h>

class FSBuffer;
#define FSBUFFER_SIZE 16

class CompressedFile : public fs::FileImpl {
public:
	CompressedFile(fs::File& f, uint8_t expansionBits, uint8_t lookaheadBits);
	~CompressedFile();
	static fs::File open(fs::File f, uint8_t expansionBits, uint8_t lookaheadBits);

	size_t write(const uint8_t* buf, size_t size) override;
	size_t read(uint8_t* buf, size_t size) override;
	void flush() override;
	bool seek(uint32_t pos, fs::SeekMode mode = fs::SeekMode::SeekSet) override;
	size_t position() const override;
	size_t size() const override;
	void close() override;
	time_t getLastWrite() override;
	const char* name() const override;
	boolean isDirectory(void) override;
	fs::FileImplPtr openNextFile(const char* mode) override;
	void rewindDirectory(void) override;
	operator bool() override;

private:
	fs::File f;
	heatshrink_decoder *decoder;
	FSBuffer *fileBuffer;
	bool pollLeft = false;
	size_t decodedSize = 0;
	size_t decodedCursor = 0;
};


#endif //CIRCUITOS_COMPRESSEDFILE_H
