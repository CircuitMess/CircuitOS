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


IS31FL3731::IS31FL3731(uint width, uint height) : MatrixOutput(width, height){
	setI2C();
}

void IS31FL3731::init(){
	Wire.begin(sda, scl, _i2caddr);
	Wire.setClock(400000);

	_frame = 0;

	// A basic scanner, see if it ACK's
	Wire.beginTransmission(_i2caddr);
	if(Wire.endTransmission() != 0){
		return;
	}

	// shutdown
	writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, 0x00);

	delay(10);

	// out of shutdown
	writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, 0x01);

	// picture mode
	writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_CONFIG,
				   ISSI_REG_CONFIG_PICTUREMODE);

	displayFrame(_frame);
	audioSync(false);

}

void IS31FL3731::push(void* data){
	auto matrixBuffer = (uint8_t*)data;

	selectBank(_frame);
	for(uint8_t i = 0; i < 6; i++){
		Wire.beginTransmission(_i2caddr);
		Wire.write((byte)0x24 + i * 24);
		// write 24 bytes at once
		for(uint8_t j = 0; j < 24; j++){
			Wire.write((uint8_t)(matrixBuffer[i * 24 + j] * brightness / 255));
		}
		Wire.endTransmission();
	}

	for(uint8_t i = 0; i <= 0x11; i++){
		writeRegister8(_frame, i, 0xff); // each 8 LEDs on
	}
}

void IS31FL3731::setI2C(uint8_t sda, uint8_t scl, uint8_t addr){
	this->sda = sda;
	this->scl = scl;
	this->_i2caddr = addr;
}


/**************************************************************************/
/*!
	@brief Low level accesssor - sets a 8-bit PWM pixel value to a bank location
	does not handle rotation, x/y or any rearrangements!
	@param lednum The offset into the bank that corresponds to the LED
	@param bank The bank/frame we will set the data in
	@param pwm brightnes, from 0 (off) to 255 (max on)
*/
/**************************************************************************/
void IS31FL3731::setLEDPWM(uint8_t lednum, uint8_t pwm, uint8_t bank){
	if(lednum >= 144)
		return;
	writeRegister8(bank, 0x24 + lednum, (uint8_t)(pwm * brightness / 255));
}


/**************************************************************************/
/*!
	@brief Switch to a given bank in the chip memory for future reads
	@param bank The IS31 bank to switch to
*/
/**************************************************************************/
void IS31FL3731::selectBank(uint8_t bank){
	Wire.beginTransmission(_i2caddr);
	Wire.write((byte)ISSI_COMMANDREGISTER);
	Wire.write(bank);
	Wire.endTransmission();
}

/**************************************************************************/
/*!
	@brief Enable the audio 'sync' for brightness pulsing (not really tested)
	@param sync True to enable, False to disable
*/
/**************************************************************************/
void IS31FL3731::audioSync(bool sync){
	if(sync){
		writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_AUDIOSYNC, 0x1);
	}else{
		writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_AUDIOSYNC, 0x0);
	}
}

/**************************************************************************/
/*!
	@brief Write one byte to a register located in a given bank
	@param bank The IS31 bank to write the register location
	@param reg the offset into the bank to write
	@param data The byte value
*/
/**************************************************************************/
void IS31FL3731::writeRegister8(uint8_t bank, uint8_t reg, uint8_t data){
	selectBank(bank);

	Wire.beginTransmission(_i2caddr);
	Wire.write((byte)reg);
	Wire.write((byte)data);
	Wire.endTransmission();
	// Serial.print("$"); Serial.print(reg, HEX);
	// Serial.print(" = 0x"); Serial.println(data, HEX);
}

/**************************************************************************/
/*!
	@brief  Read one byte from a register located in a given bank
	@param   bank The IS31 bank to read the register location
	@param   reg the offset into the bank to read
	@return 1 byte value
*/
/**************************************************************************/
uint8_t IS31FL3731::readRegister8(uint8_t bank, uint8_t reg){
	uint8_t x;

	selectBank(bank);

	Wire.beginTransmission(_i2caddr);
	Wire.write((byte)reg);
	Wire.endTransmission();

	Wire.requestFrom(_i2caddr, (size_t)1);
	x = Wire.read();

	// Serial.print("$"); Serial.print(reg, HEX);
	// Serial.print(": 0x"); Serial.println(x, HEX);

	return x;
}

/**************************************************************************/
/*!
	@brief Set's this object's frame tracker (does not talk to the chip)
	@param frame Ranges from 0 - 7 for the 8 frames
*/
/**************************************************************************/
void IS31FL3731::setFrame(uint8_t frame){ _frame = frame; }

/**************************************************************************/
/*!
	@brief Have the chip set the display to the contents of a frame
	@param frame Ranges from 0 - 7 for the 8 frames
*/
/**************************************************************************/
void IS31FL3731::displayFrame(uint8_t frame){
	if(frame > 7)
		frame = 0;
	writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_PICTUREFRAME, frame);
}
