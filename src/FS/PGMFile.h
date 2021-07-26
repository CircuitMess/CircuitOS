#ifndef CIRCUITOS_PGMFILE_H
#define CIRCUITOS_PGMFILE_H

#include <Arduino.h>
#include <FS.h>
#include <FSImpl.h>

class PGMFile : public fs::FileImpl {
public:
#ifdef ESP32
	fs::FileImplPtr openNextFile(const char* mode) override;
	void rewindDirectory() override;
	operator bool() override;
#else
	fs::FileImplPtr openNextFile(const char* mode) ;
	void rewindDirectory() ;
	operator bool() ;
#endif
	PGMFile(const uint8_t* data, size_t size);
	virtual ~PGMFile();

	static fs::File open(const uint8_t* data, size_t size);

	size_t write(const uint8_t* buf, size_t size) override;
	size_t read(uint8_t* buf, size_t size) override;
	void flush() override;
	bool seek(uint32_t pos, fs::SeekMode mode) override;
	size_t position() const override;
	size_t size() const override;
	void close() override;
	time_t getLastWrite() override;
	const char* name() const override;
	bool isDirectory();

	bool truncate(uint32_t size) override;

	const char* fullName() const override;

	bool isFile() const override;

	bool isDirectory() const override;

	bool seek(uint32_t pos);
	size_t write(uint8_t data);
	int read();
	int peek();
	int available();

private:
	const uint8_t* data;
	size_t dataSize;
	size_t cursor = 0;
};


#endif //CIRCUITOS_PGMFILE_H
