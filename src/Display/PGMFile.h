#ifndef CIRCUITOS_PGMFILE_H
#define CIRCUITOS_PGMFILE_H

#include <FS.h>

class PGMFile : public fs::File {
public:
	PGMFile(const uint8_t* data, size_t size);
	virtual ~PGMFile();

	size_t write(uint8_t data) override;
	size_t write(const uint8_t* buf, size_t size) override;
	int available() override;
	int read() override;
	int peek() override;
	void flush() override;
	size_t readBytes(char *buffer, size_t length);
	size_t read(uint8_t* buf, size_t size);
	bool seek(uint32_t pos, fs::SeekMode mode);
	bool seek(uint32_t pos);

	size_t position() const;
	size_t size() const;
	void close();
	operator bool() const;

	boolean isDirectory(void);

private:
	const uint8_t* data;
	size_t dataSize;
	size_t cursor = 0;
};


#endif //CIRCUITOS_PGMFILE_H
