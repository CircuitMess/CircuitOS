#ifndef CIRCUITOS_COMPRESSEDFILE_H
#define CIRCUITOS_COMPRESSEDFILE_H

#include <Arduino.h>
#include <FS.h>
#include <FSImpl.h>

class CompressedFile : public fs::FileImpl {
public:
	CompressedFile(File& f);

	static fs::File open(File& f);

	size_t write(const uint8_t* buf, size_t size) override;
	size_t read(uint8_t* buf, size_t size) override;
	void flush() override;
	bool seek(uint32_t pos, SeekMode mode) override;
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
	File f;

};


#endif //CIRCUITOS_COMPRESSEDFILE_H
