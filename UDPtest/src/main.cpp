#include <M5Stack.h>
#include <WiFiUdp.h>
#include <WiFi.h>
#include "Keyboard.h"
int status = WL_IDLE_STATUS;
const char ssid[] = "IZZI-3995";
const char passwd[] = "12345678";
Keyboard keyboard;
void setup() {
 M5.begin();
 Wire.begin();
 Serial.begin(9600);
 M5.Lcd.setBrightness(30);
 M5.Lcd.drawCentreString("UDP KEYBOARD", 160,2,2);
 M5.Lcd.setCursor(0,18);
 M5.Lcd.println("Connecting to WiFi..");
 while (status != WL_CONNECTED) {
   status = WiFi.begin(ssid,passwd);
   Serial.println("CONNECTING");
   delay(1000);
   
 } 
 Serial.println("CONNECTED");
 M5.Lcd.setTextColor(GREEN);
M5.Lcd.println("CONNECTED!");


}

void loop() {
  if (keyboard.available()) {
    M5.Lcd.print((char)keyboard.get_char());
  }
}