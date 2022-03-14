#include "IS31FL3731.h"
#include <Wire.h>

#define ISSI_REG_CONFIG 0x00
#define ISSI_REG_CONFIG_PICTUREMODE 0x00
#define ISSI_REG_CONFIG_AUTOPLAYMODE 0x08
#define ISSI_REG_CONFIG_AUDIOPLAYMODE 0x18

#define ISSI_CONF_PICTUREMODE 0x00
#define ISSI_CONF_AUTOFRAMEMODE 0x04
#define ISSI_CONF_AUDIOMODE 0x08

#define ISSI_REG_PICTUREFRAME 0x01

#define ISSI_REG_SHUTDOWN 0x0A
#define ISSI_REG_AUDIOSYNC 0x06

#define ISSI_COMMANDREGISTER 0xFD
#define ISSI_BANK_FUNCTIONREG 0x0B // helpfully called 'page nine'

static const char* TAG = "IS31FL3731";

IS31FL3731::IS31FL3731(TwoWire& Wire, uint8_t addr) : MatrixOutput(16, 9), Wire(::Wire), addr(addr){

}

void IS31FL3731::init(){
	Wire.beginTransmission(addr);
	if(Wire.endTransmission() != 0){
		ESP_LOGE(TAG, "I2C com error");
		return;
	}

	// shutdown
	writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, 0x00);

	delay(10);

	// power on
	writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, 0x01);

	// picture mode
	writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_CONFIG, ISSI_REG_CONFIG_PICTUREMODE);

	// set frame
	writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_PICTUREFRAME, 0);

	push(MatrixPixelData(16, 9));

	// all LEDs ON
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 18; j++){
			writeRegister8(i, j, 0xff);
		}
	}

	audioSync(false);
}

void IS31FL3731::push(const MatrixPixelData& data){
	selectBank(0);

	// send in two parts
	for(int i = 0; i < 2; i++){
		Wire.beginTransmission(addr);
		Wire.write((byte) 0x24 + i * 77);

		for(int j = 0; j < 77; j++){
			int index = i * 77 + j;
			int y = index / 16;
			int x = index - y * 16;

			auto pix = data.get(x, y);
			uint8_t val = ((pix.r + pix.g + pix.b) / 3) * pix.i / 255;

			Wire.write((uint8_t) (val * getBrightness() / 255));
		}

		Wire.endTransmission();
	}
}

void IS31FL3731::audioSync(bool sync){
	if(sync){
		writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_AUDIOSYNC, 0x1);
	}else{
		writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_AUDIOSYNC, 0x0);
	}
}

void IS31FL3731::writeRegister8(uint8_t bank, uint8_t reg, uint8_t data){
	selectBank(bank);

	Wire.beginTransmission(addr);
	Wire.write((byte) reg);
	Wire.write((byte) data);
	Wire.endTransmission();
}

uint8_t IS31FL3731::readRegister8(uint8_t bank, uint8_t reg){
	selectBank(bank);

	Wire.beginTransmission(addr);
	Wire.write((byte) reg);
	Wire.endTransmission();

	Wire.requestFrom(addr, (size_t) 1);
	return Wire.read();
}

void IS31FL3731::selectBank(uint8_t bank){
	Wire.beginTransmission(addr);
	Wire.write((byte) ISSI_COMMANDREGISTER);
	Wire.write(bank);
	Wire.endTransmission();
}