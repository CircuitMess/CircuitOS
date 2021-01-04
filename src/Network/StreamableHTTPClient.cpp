#include "StreamableHTTPClient.h"

bool StreamableHTTPClient::startPOST(){
	// connect to server
	if(!connect()) {
		return false;
	}

	// send Header
	if(!sendHeader("POST")) {
		return false;
	}

	buffer.clear();
	buffer.reserve(bufferSize);

	return true;
}

bool StreamableHTTPClient::send(uint8_t* data, uint32_t size){
	int curSize = buffer.size();
	buffer.resize(curSize + size);
	memcpy(buffer.data() + curSize, data, size);

	if(buffer.size() >= bufferSize){
		return sendBuffer();
	}

	return true;
}

int StreamableHTTPClient::finish(){
	sendBuffer();
	buffer.reserve(0);
	return returnError(handleHeaderResponse());
}

bool StreamableHTTPClient::sendBuffer(){
	if(buffer.empty()) return true;

	if(_client->write(buffer.data(), buffer.size()) != buffer.size()){
		return false;
	}

	buffer.clear();
	return true;
}
