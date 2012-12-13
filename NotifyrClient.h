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

#ifndef NOTIFYRCLIENT_H
#define NOTIFYRCLIENT_H

#include <string.h>
#include <stdlib.h>
#include <WString.h>
#include "Arduino.h"
#include <Ethernet.h>
#include <WiFly.h>

// Uncomment to enable WiFlyClient
// #define _WIFLY_

class NotifyrClient {

	public:
		static const unsigned long HEARTBEAT_THRESHHOLD = 60000; //heartbeat is 30 seconds, if we miss a second beat, reconnect
	#ifdef _WIFLY_
		NotifyrClient();
	#endif
		typedef void (*EventDelegate)(String data);
		bool connect(String key, String channel);
		bool connected();
		void disconnect();
		void bind(EventDelegate delegate);
		void listen();
		static void debug();
	private:
		bool _connect();
		void _request();
		static void _log(String message);
		String _key;
		String _channel;
		String _buffer;
		bool _receiving;
		char _lastChar;
		unsigned long _lastHeartbeat;
		static bool _debug;
	#ifdef _WIFLY_
		WiFlyClient _client;
	#endif
	#ifndef _WIFLY_
		EthernetClient _client;
	#endif
		EventDelegate _eventDelegate;
};

#endif
