#Arduino Notifyr Client

###An Arduino client for connecting to notifyr.io using the Ethernet or WiFly Shields

Notifyr is a simple cloud based service to quickly and easily add realtime push functionality to web and mobile apps.

#Installation

 * Clone (or Fork & Clone) ArduinoNotifyrClient (example `git clone git://github.com/dubhunter/ArduinoNotifyrClient.git`)
 * Copy (or Symlink) `ArduinoNotifyrClient` to `Arduino/libraries` (example `ln -s ~/Projects/ArduinoNotifyrClient ~/Documents/Arduino/libraries/ArduinoNotifyrClient`)
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

###Coming soon!

#Caveats

 * Does NOT handle multi-line payloads
 * If your payload includes `data: "`, everything will break. You can use `"data": "`

#Credits

 * Inspired by [ArduinoPusherClient](https://github.com/krohling/ArduinoPusherClient) by [krohling](https://github.com/krohling)
