#ifndef CIRCUITOS_RAMFILE_H
#define CIRCUITOS_RAMFILE_H

#include <Arduino.h>
#include <FS.h>
#include <FSImpl.h>

class RamFile : public fs::FileImpl {
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
	RamFile(uint8_t* data, size_t size, bool readonly = true);
	virtual ~RamFile();

	static fs::File open(uint8_t* data, size_t size, bool readonly = true);
	static fs::File open(fs::File file, bool readonly = true);
	static fs::File create(const String& filename = "");

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

	bool truncate(uint32_t size) ;

	const char* fullName() const ;

	bool isFile() const ;

	bool isDirectory() const ;

	bool seek(uint32_t pos);
	size_t write(uint8_t data);
	int read();
	int peek();
	int available();

private:
	uint8_t* data = nullptr;
	size_t dataSize;
	size_t cursor = 0;
	bool readonly;
	String filename;

};


#endif //CIRCUITOS_RAMFILE_H
