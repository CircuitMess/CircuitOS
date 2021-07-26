#ifndef CIRCUITOS_NET_H
#define CIRCUITOS_NET_H


#include <HTTPClient.h>
#include <Util/Vector.h>

class StreamableHTTPClient : public HTTPClient {
public:
	bool startPOST();
	bool send(uint8_t* data, uint32_t size);
	int finish();

private:
	Vector<uint8_t> buffer;
	const uint32_t bufferSize = 800;

	bool sendBuffer();
};


#endif //CIRCUITOS_NET_H
