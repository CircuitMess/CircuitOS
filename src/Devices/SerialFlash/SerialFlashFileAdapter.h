#ifndef CIRCUITOS_SERIALFLASHFILEADAPTER_H
#define CIRCUITOS_SERIALFLASHFILEADAPTER_H

#include <Arduino.h>
#include <FS.h>
#include <FSImpl.h>
#include <memory>

class SerialFlashFile;
/**
 * Class to adapt SerialFlashFile class from the SerialFlash lib by Paul Stoffregen (https://github.com/PaulStoffregen/SerialFlash)
 * to the File interface from esp8266/esp32 FS core.
 */
class SerialFlashFileAdapter : public fs::FileImpl {
public:
	SerialFlashFileAdapter(SerialFlashFile* _file);
	SerialFlashFileAdapter(const char* path);
	virtual ~SerialFlashFileAdapter();

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
	fs::FileImplPtr openNextFile(const char* mode) override;
	void rewindDirectory() override;
	operator bool() override;

	bool seek(uint32_t pos);
	size_t write(uint8_t data);
	int read();
	int peek();
	int available();

private:
	SerialFlashFile* file;
};


#endif //CIRCUITOS_SERIALFLASHFILEADAPTER_H
