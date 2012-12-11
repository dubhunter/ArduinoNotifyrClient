#include <SPI.h>
#include <WiFly.h>
#include <WiFlyNotifyrClient.h>
#include "Credentials.h"

WiFlyNotifyrClient notifyr;

void setup() {
    Serial.begin(9600);
    
    Serial.println("Initializing WiFi...");
    WiFly.begin();
    
    Serial.print("Attempting to join: ");
    Serial.println(SSID);
    
    if (!WiFly.join(SSID, PASSPHRASE, true)) {
        Serial.println("Association failed...");
        for (;;) ; // do nothing forever
    }
    
    Serial.println("Joined!");
    Serial.println();
    
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