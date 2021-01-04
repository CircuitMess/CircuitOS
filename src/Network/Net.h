#ifndef SPENCER_NET_H
#define SPENCER_NET_H

#include <WiFi.h>
#include "../Loop/LoopListener.h"
#include "../Util/Vector.h"

class NetStateListener {
private: virtual void state(wl_status_t) = 0;
friend class NetImpl;
};

class NetImpl : public LoopListener {
public:
	NetImpl();

	enum NetError { OK, WIFI, NET, SERVICE };

	void set(const char* ssid, const char* pass);

	/**
	 * A void function that takes a wl_status_t argument.
	 */
	typedef void (NetStateCallback)(wl_status_t);

	/**
	 * Connects to the WiFi in a non-blocking fashion, in the loop thread. 3 tries, 5s timeout.
	 * Starts the WiFi animation. Will not trigger disconnect callbacks/listeners. Always check
	 * Net.connected() before making network requests.
	 *
	 * @see Net.connect()
	 *
	 * @param resultCallback will be called in the Loop thread
	 */
	void connect(NetStateCallback* resultCallback = nullptr);

	void loop(uint micros) override;

	/**
	 * Register a state callback. This will not trigger when the network goes down for reconnection.
	 * Always check Net.connected() before making network requests.
	 * @param callback Will be called when connection goes up or down.
	 */
	void addStateCallback(NetStateCallback* callback);

	/**
	 * Register a state listener. This will not trigger when the network goes down for reconnection.
	 * Always check Net.checkConnection() before making network requests.
	 * @param NetEventListener::state will be called when connection goes up or down.
	 */
	void addStateListener(NetStateListener* listener);

	void removeStateListener(NetStateListener* listener);

	/**
	 * Checks if a working Internet connection is established. First, by checking if the WiFi is connected,
	 * and then trying to establish a connection to specified URL (defaults to spencer.circuitmess.com). This is a blocking function.
	 * @param url URL to be pinged. Defaults to spencer.circuitmess.com
	 * @return True is all OK, false otherwise
	 */
	bool checkConnection(const char* url = "http://spencer.circuitmess.com:7979/index");

	/**
	 * Reconnects the WiFi in a blocking fashion. 2 tries, 5s timeout
	 * @return True if succeeded, false otherwise
	 */
	bool reconnect();

	wl_status_t getState() const;

	NetError getLastError() const;

private:
	const uint timeouts[3] = { 3000, 7000, 10000 };

	const char* ssid;
	const char* pass;

	void checkRemoveListeners();
	Vector<NetStateListener*> stateListeners;
	Vector<NetStateListener*> removeStateListeners;
	std::vector<NetStateCallback*> stateCallbacks;

	NetStateCallback* connectResultCallback = nullptr;

	void setState(wl_status_t state);

	void tryConnect();
	void retryConnect();
	bool connecting = false;
	uint connectTime;
	uint8_t connectRetries;

	wl_status_t state = WL_DISCONNECTED;

	NetError lastError = OK;
};

extern NetImpl Net;

#endif //SPENCER_NET_H
