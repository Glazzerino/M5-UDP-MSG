#include <M5Stack.h>
#include <WiFiUdp.h>
#include <WiFi.h>
#include "Keyboard.h"
int status = WL_IDLE_STATUS;
const char ssid[] = "IZZI-3995";
const char passwd[] = "12345678";
Keyboard keyboard;
void draw_taskbar() {
  M5.Lcd.setTextSize(2);
  M5.Lcd.fillRect(0,215,340,25,GREEN);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.drawCentreString("A        B        C",170,210,2);
  M5.Lcd.setTextSize(1);
}
void setup() {
  M5.begin();
  Wire.begin();
  Serial.begin(9600);
  M5.Lcd.setBrightness(60);
  M5.Lcd.drawCentreString("UDP KEYBOARD", 160,2,2);
  M5.Lcd.setCursor(0,18);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("Connecting to WiFi..");
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid,passwd);
    Serial.println("CONNECTING");
    delay(1000);
  } 
  Serial.println("CONNECTED");
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println("CONNECTED!");
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("Press A when you're ready to send the message");
  M5.Lcd.println("Press B to clear screen and message");
  M5.Lcd.println("Press C to send the message to target computer");
  M5.Lcd.println("Use keyboard to write a message");

  draw_taskbar();
}

void loop() {
  if (keyboard.available()) {
    char data = (char)keyboard.get_char();
    if (data == 0x0D) {
      M5.Lcd.println("");
      // M5.Lcd.println("");
    } else {
      M5.Lcd.print(data);
    }
  }
}