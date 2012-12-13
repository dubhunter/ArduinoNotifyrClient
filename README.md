#Arduino Notifyr Client

###An Arduino client for connecting to notifyr.io using the Ethernet or WiFly Shields

Notifyr is a simple cloud based service to quickly and easily add realtime push functionality to web and mobile apps.

#Installation

 * Clone (or Fork & Clone) ArduinoNotifyrClient
   * example: `git clone git://github.com/dubhunter/ArduinoNotifyrClient.git`
 * Copy (or Symlink) `ArduinoNotifyrClient` to `Arduino/libraries`
   * example: `ln -s ~/Projects/ArduinoNotifyrClient ~/Documents/Arduino/libraries/ArduinoNotifyrClient`
 * Restart Arduino IDE

###Example

    mkdir -p ~/Projects/ && cd ~/Projects/
    git clone git://github.com/dubhunter/ArduinoNotifyrClient.git
    ln -s ~/Projects/ArduinoNotifyrClient ~/Documents/Arduino/libraries/ArduinoNotifyrClient

#Configuration

###Enabling WiFly Shield

 * Uncomment `#define _WIFLY_` in `NotifyrClient.h`
 * Restart Arduino IDE

#Examples

Included with this library are two simple examples `NotifyrSerial` and `NotifyrSerialWiFly` for the Ethernet Shield and WiFly Shield respectively.
They both do the same thing: Connect to `my-channel` channel and print all events to `Serial`.

###Instantiation

    //Create a NotifyrClient (which will have its own Ethernet or WiFly client)
    NotifyrClient notifyr;

###Connect & Bind

    if (notifyr.connect(NOTIFYR_KEY, "my-channel")) {
        notifyr.bind(handleEvent);
    } else {
        //failed to connect
    }

###Listen

    void loop() {
        //listen for incoming events
        notifyr.listen();
    }

###EventDelegate

    void handleEvent(String data) {
        //do something with your data
        Serial.println(data);
    }

###Debug (or just see cool info)

    begin() {
        Serial.begin(9600);
        NotifyrClient::debug();
        
        //connect & bind...
    }

#API

The `NotifyrClient` exposes a very simple API.

###bool NotifyrClient::connect(String key, String channel);

Connect to Notifyr on a specific channel. Automatic re-connects are attempted if we miss two heartbeats.

###bool NotifyrClient::connected();

Check to see if you are currently connected to Notifyr.

###void NotifyrClient::disconnect();

Disconnect from Notifyr.

###void NotifyrClient::bind(EventDelegate delegate);

Once you have connected, bind your event delegate to be called when an event is received.
`EventDelegate`'s have the signature `void myDelegate(String data);`

###void NotifyrClient::listen();

Listen for incoming events. This MUST be placed in your `loop()` function.

###NotifyrClient::debug();

Turn on logging (`Serial.begin()` required);

#Caveats

 * I do not know C++
 * Does NOT handle multi-line payloads.
 * If your payload includes `data: "`, everything will break. You can use `"data": "` for more complex payloads.
 * If you hold the main `loop()` for more than 60 seconds, you may cause the heartbeats to be missed, and cause a reconnect attempt.
   * If this is a problem, change `NotifyrClient::HEARTBEAT_THRESHHOLD` to something higher in `NotifyrClient.h`

#Credits

 * Inspired by [ArduinoPusherClient](https://github.com/krohling/ArduinoPusherClient) by [krohling](https://github.com/krohling)
