#include <SPI.h>
#include <Ethernet.h>
#include <NotifyrClient.h>
#include "Credentials.h"

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xF0, 0x0D };
NotifyrClient notifyr;

void setup() {
    Serial.begin(9600);
    
    Serial.println("Initializing Ethernet...");
    Ethernet.begin(mac);
    
    Serial.print("Connecting to Notifyr (");
    Serial.print(NOTIFYR_KEY);
    Serial.println(")...");
    
    if (notifyr.connect(NOTIFYR_KEY, "my-channel")) {
        Serial.println("Connected!");
        notifyr.bind(handleEvent);
    } else {
        Serial.println("Connection failed...");
        for (;;) ; // do nothing forever
    }
}

void loop() {
    notifyr.listen();
}

void handleEvent(String data) {
    Serial.println("Event!!!");
    Serial.println(data);
}