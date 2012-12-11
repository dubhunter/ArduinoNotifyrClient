/*
 WiFlyNotifyrClient, a Notifyr.io client for Arduino & WiFly
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

#ifndef WIFLYNOTIFYRCLIENT_H
#define WIFLYNOTIFYRCLIENT_H_

#include <string.h>
#include <stdlib.h>
#include <WString.h>
#include "Arduino.h"
#include <WiFly.h>

class WiFlyNotifyrClient {

	public:
		WiFlyNotifyrClient();
		typedef void (*EventDelegate)(String data);
		bool connect(String key, String channel);
		bool connected();
		void disconnect();
		void bind(EventDelegate delegate);
		void listen();
	private:
		bool _connect();
		String _key;
		String _channel;
		String _buffer;
		char _lastChar;
		bool _receiving;
		WiFlyClient _client;
		EventDelegate _eventDelegate;
};

#endif
