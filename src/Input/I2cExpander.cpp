#include "I2cExpander.h"

#define INPUT_REG 0x00	// input register location
#define OUTPUT_REG 0x02	// output register location
#define INVERT_REG 0x04	// polarity inversion register location
#define CONFIG_REG 0x06	// configuration register location

I2cExpander* I2cExpander::instance = nullptr;

I2cExpander::I2cExpander()
{
	instance = this;
}
I2cExpander::~I2cExpander()
{
}
bool I2cExpander::begin(uint8_t _address, uint8_t _sda, uint8_t _scl)
{
	address = _address;
	i2c->begin(_sda, _scl);

	return init();
}

bool I2cExpander::begin(uint8_t _address, TwoWire& wire)
{
	address = _address;
	i2c = &wire;

	return init();
}

bool I2cExpander::init(){
	i2c->beginTransmission(address);
	if(i2c->endTransmission() != 0){
		return false;
	}

	portWrite(0xFFFF);
	_write(0x0000, INVERT_REG);
	portConfig(0xFFFF);

	return true;
}

void I2cExpander::_write(uint16_t _portData, uint8_t reg)
{
	i2c->beginTransmission(address);
	i2c->write(reg);
	// i2c->write(_portData);
	i2c->write(_portData & 0x00FF);
	i2c->write(_portData >> 8);
	i2c->endTransmission();
}
uint16_t I2cExpander::portRead()
{
	i2c->beginTransmission(address);
	i2c->write(INPUT_REG);
	i2c->endTransmission();
	i2c->requestFrom((uint8_t) address, (uint8_t) 2);
	uint16_t readValue = i2c->read();
	readValue |= i2c->read() << 8;
	// i2c->readBytes((uint8_t*)readValue, 2);
	portState = readValue;
	return readValue;
}

bool I2cExpander::portRead(uint16_t& state){
	i2c->beginTransmission(address);
	i2c->write(INPUT_REG);
	if(i2c->endTransmission() != 0) return false;

	i2c->requestFrom((uint8_t) address, (uint8_t) 2);
	if(i2c->readBytes(reinterpret_cast<char*>(&state), 2) != 2){
		state = 0;
		return false;
	}
	portState = state;
	return true;

}

void I2cExpander::portConfig(uint16_t _portData)
{
	configState = _portData;
	_write(configState, CONFIG_REG);
}
void I2cExpander::portWrite(uint16_t writeData)
{
	outputState = writeData;
	_write(writeData, OUTPUT_REG);
}
void I2cExpander::pinMode(uint8_t pin, uint8_t mode)
{
	uint16_t configMask = 1 << pin;
	if(mode == OUTPUT)
		configState &= ~configMask;
	else
		configState |= configMask;
	
	portConfig(configState);
}
bool I2cExpander::pinRead(uint8_t pin)
{
	uint16_t _data = portRead();
	return bitRead(_data, pin);
}
void I2cExpander::pinWrite(uint8_t pin, bool state)
{
	uint16_t outputMask = 1 << pin;
	if(state)
		outputState |= outputMask;
	else
		outputState &= ~outputMask;
	portWrite(outputState);
}
I2cExpander* I2cExpander::getInstance()
{
	return instance;
}

uint16_t I2cExpander::getPortState() const{
	return portState;
}
