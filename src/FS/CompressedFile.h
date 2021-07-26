#ifndef CIRCUITOS_COMPRESSEDFILE_H
#define CIRCUITOS_COMPRESSEDFILE_H

#include <Arduino.h>
#include <FS.h>
#include <FSImpl.h>
#include <heatshrink_decoder.h>
#include "../Buffer/FSBuffer.h"
#include "../Buffer/DataBuffer.h"

#define FSBUFFER_SIZE 512

class CompressedFile : public fs::FileImpl {
public:
#ifdef ESP32
	boolean isDirectory(void) override;
	fs::FileImplPtr openNextFile(const char* mode) override;
	void rewindDirectory(void) override;
	operator bool() override;
#else
	boolean isDirectory(void) ;
	fs::FileImplPtr openNextFile(const char* mode) ;
	void rewindDirectory(void) ;
	operator bool() ;
#endif
	CompressedFile(fs::File& f, uint8_t expansionBits, uint8_t lookaheadBits, size_t readBufferSize = FSBUFFER_SIZE);
	~CompressedFile();
	static fs::File open(fs::File f, uint8_t expansionBits, uint8_t lookaheadBits, size_t readBufferSize = FSBUFFER_SIZE);

	size_t write(const uint8_t* buf, size_t size) override;
	size_t read(uint8_t* buf, size_t size) override;
	void flush() override;
	bool seek(uint32_t pos, fs::SeekMode mode = fs::SeekMode::SeekSet) override;
	size_t position() const override;
	size_t size() const override;
	void close() override;
	time_t getLastWrite() override;
	const char* name() const override;

	bool truncate(uint32_t size) override;

	const char* fullName() const override;

	bool isFile() const override;

	bool isDirectory() const override;

private:
	fs::File f;
	heatshrink_decoder *decoder;
	FSBuffer fileBuffer;
	size_t pos = 0;
};


#endif //CIRCUITOS_COMPRESSEDFILE_H
#ifndef CIRCUITOS_COMPRESSEDFILE_H
#define CIRCUITOS_COMPRESSEDFILE_H

#include <Arduino.h>
#include <FS.h>
#include <FSImpl.h>
#include <heatshrink_decoder.h>
#include "../Buffer/FSBuffer.h"
#include "../Buffer/DataBuffer.h"

#define FSBUFFER_SIZE 512

class CompressedFile : public fs::FileImpl {
public:
#ifdef ESP32
	boolean isDirectory(void) override;
	fs::FileImplPtr openNextFile(const char* mode) override;
	void rewindDirectory(void) override;
	operator bool() override;

#else
	boolean isDirectory(void) ;
	fs::FileImplPtr openNextFile(const char* mode) ;
	void rewindDirectory(void) ;
	operator bool() ;
#endif
	CompressedFile(fs::File& f, uint8_t expansionBits, uint8_t lookaheadBits, size_t readBufferSize = FSBUFFER_SIZE);
	~CompressedFile();
	static fs::File open(fs::File f, uint8_t expansionBits, uint8_t lookaheadBits, size_t readBufferSize = FSBUFFER_SIZE);

	size_t write(const uint8_t* buf, size_t size) override;
	size_t read(uint8_t* buf, size_t size) override;
	void flush() override;
	bool seek(uint32_t pos, fs::SeekMode mode = fs::SeekMode::SeekSet) override;
	size_t position() const override;
	size_t size() const override;
	void close() override;
	time_t getLastWrite() override;
	const char* name() const override;

private:
	fs::File f;
	heatshrink_decoder *decoder;
	FSBuffer fileBuffer;
	size_t pos = 0;
};


#endif //CIRCUITOS_COMPRESSEDFILE_H
