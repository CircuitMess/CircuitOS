#include "Net.h"
#include <WiFi.h>
#include "../Loop/LoopManager.h"
#include <HTTPClient.h>
#include <ESP32Ping.h>

NetImpl Net;

NetImpl::NetImpl(){
	WiFi.enableSTA(true);
}

void NetImpl::set(const char* ssid, const char* pass){
	this->ssid = ssid;
	this->pass = pass;
}

void NetImpl::setState(wl_status_t state){
	if(this->state != state){
		this->state = state;

		checkRemoveListeners();

		for(const auto& listener : stateListeners){
			listener->state(state);
		}

		for(const auto& callback : stateCallbacks){
			callback(state);
		}

		checkRemoveListeners();
	}
}

void NetImpl::connect(NetImpl::NetStateCallback* resultCallback){
	if(connecting) return;

	connectResultCallback = resultCallback;

	state = WL_DISCONNECTED;

	LoopManager::addListener(this);

	connectRetries = 0;
	connecting = true;
	tryConnect();
}

void NetImpl::tryConnect(){
	WiFi.disconnect(true);
	WiFi.persistent(false);
	WiFi.begin(ssid, pass);
	WiFi.setSleep(false);

	connectTime = millis();
}

void NetImpl::retryConnect(){
	if(++connectRetries == 3){
		connecting = false;

		setState(WL_DISCONNECTED);

		if(connectResultCallback){
			NetStateCallback* callback = connectResultCallback;
			connectResultCallback = nullptr;
			callback(WL_DISCONNECTED);
		}

		LoopManager::removeListener(this);
		return;
	}

	tryConnect();
}

void NetImpl::loop(uint micros){
	if(!connecting) return;

	wl_status_t status = WiFi.status();

	if(!status || status >= WL_DISCONNECTED){
		int timeout = connectRetries >= (sizeof(timeouts) / sizeof(timeouts[0])) ? timeouts[(sizeof(timeouts) / sizeof(timeouts[0])) - 1] : timeouts[connectRetries];

		// still connecting
		if(millis() - connectTime >= timeout){ // 5 sec timeout
			retryConnect();
		}
	}else{
		// WiFi can get messed up sometimes, so retry if failed after only one try
		if(status != WL_CONNECTED && connectRetries == 0){
			retryConnect();
			return;
		}

		// done connecting, process result
		connecting = false;
		LoopManager::removeListener(this);

		setState(status);

		if(connectResultCallback){
			NetStateCallback* callback = connectResultCallback;
			connectResultCallback = nullptr;
			callback(status);
		}
	}
}

void NetImpl::addStateCallback(NetStateCallback* callback){
	stateCallbacks.push_back(callback);
}

void NetImpl::addStateListener(NetStateListener* listener){
	stateListeners.push_back(listener);
}

void NetImpl::removeStateListener(NetStateListener* listener){
	removeStateListeners.push_back(listener);
}

void NetImpl::checkRemoveListeners(){
	for(NetStateListener* listener : removeStateListeners){
		uint i = stateListeners.indexOf(listener);
		if(i == (uint) -1) return;
		stateListeners.remove(i);
	}

	removeStateListeners.clear();
}

bool NetImpl::checkConnection(const char *url){
	while(connecting){
		delay(100);
	}

	if(WiFi.status() != WL_CONNECTED){
		setState(WL_DISCONNECTED);
		lastError = WIFI;
		return false;
	}

	bool internet = Ping.ping(IPAddress(8, 8, 8, 8));
	if(!internet){
		lastError = NET;
		setState(WL_DISCONNECTED);
		return false;
	}

	HTTPClient client;
	client.setConnectTimeout(2000);
	client.useHTTP10(true);
	client.setReuse(false);

	if(!client.begin(url)){
		client.end();
		client.getStream().flush();
		lastError = SERVICE;
		setState(WL_DISCONNECTED);
		return false;
	}

	client.setUserAgent("ESP32HTTPClient");

	int code = client.GET();
	if(code != 200){
		client.end();
		client.getStream().flush();
		lastError = SERVICE;
		setState(WL_DISCONNECTED);
		return false;
	}

	String data = client.getString();
	client.end();
	client.getStream().flush();

	if(data.substring(0, 2) != "OK"){
		lastError = SERVICE;
		setState(WL_DISCONNECTED);
		return false;
	}

	lastError = OK;
	setState(WL_CONNECTED);
	return true;
}

bool NetImpl::reconnect(){
	int retries = 0;

	while(WiFi.status() != WL_CONNECTED && retries++ < 2){
		tryConnect();

		while(WiFi.status() != WL_CONNECTED){
			delay(500);
			if(millis() - connectTime >= 7000) break;
		}
	}

	if(WiFi.status() == WL_CONNECTED && Ping.ping(IPAddress(8, 8, 8, 8))){
		setState(WL_CONNECTED);
	}else{
		setState(WL_DISCONNECTED);
	}

	return state == WL_CONNECTED;
}

wl_status_t NetImpl::getState() const{
	return state;
}

NetImpl::NetError NetImpl::getLastError() const{
	return lastError;
}
