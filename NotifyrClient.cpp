/*
 NotifyrClient, a Notifyr.io client for Arduino & WiFly
 Copyright 2012 Will Mason
 http://willmason.me
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include <NotifyrClient.h>
#include <WString.h>
#include <string.h>
#include <stdlib.h>

typedef void (*EventDelegate)(String data);

#ifdef _WIFLY_
NotifyrClient::NotifyrClient() : _client("api.notifyr.io", 80) {}

bool NotifyrClient::_connect() {
	if (_client.connect()) {
		_request();
		return true;
	} else {
		return false;
	}
}
#endif

#ifndef _WIFLY_
bool NotifyrClient::_connect() {
	if (_client.connect("api.notifyr.io", 80)) {
		_request();
		return true;
	} else {
		return false;
	}
}
#endif

void NotifyrClient::_request() {
	_client.println("GET /subscribe/" + _channel + "?key=" + _key + "&always_ok.1");
	_client.println("Connection: keep-alive");
	_client.println("Host: api.notifyr.io");
	_client.println();
}

bool NotifyrClient::connect(String key, String channel) {
	_key = key;
	_channel = channel;
	
	_connect();
}

bool NotifyrClient::connected() {
	return _client.connected();
}

void NotifyrClient::disconnect() {
	_client.stop();
}

void NotifyrClient::bind(EventDelegate delegate) {
	_eventDelegate = delegate;
}

void NotifyrClient::listen() {
	// TODO: Figure out how to handle reconnect
	// Check for "update interval", reconnect if interval exceeded
	// if (!connected()) {
	// 	_connect();
	// }
	
	if (_client.available()) {
		char c = _client.read();
		
		if (c != _lastChar || c != ' ') {
			// Serial.print(c);
			
			if (_receiving && _lastChar == '\n' && c == '\n') {
				//remove newline and quote
				_buffer = _buffer.substring(0, _buffer.length() - 2);
				
				//do thing
				if (_eventDelegate != NULL) {
					_eventDelegate(_buffer);
				}
				
				//reset
				_buffer = "";
				_receiving = false;
			}
			
			_buffer += c;
			
			if (_buffer.endsWith("data: \"")) {
				// Serial.println("\nReceiving Event...");
				_buffer = "";
				_receiving = true;
			}
		}
		_lastChar = c;
	}
}