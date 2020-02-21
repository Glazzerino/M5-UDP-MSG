#include <M5Stack.h>
#include <WiFiUdp.h>
#include <WiFi.h>
#include "Keyboard.h"
int status = WL_IDLE_STATUS;
const char ssid[] = "IZZI-3995";
const char passwd[] = "12345678";
const char target_ip[] = "192.168.0.16";
const int target_port = 8080;
WiFiUDP udp;
Keyboard keyboard;
void draw_taskbar() {
  M5.Lcd.setTextSize(2);
  M5.Lcd.fillRect(0,215,340,25,GREEN);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.drawCentreString("A        B        C",170,210,2);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(20,50);
  M5.Lcd.setTextColor(WHITE);
}
void setup() {
  M5.begin();
  Wire.begin();
  Serial.begin(9600);
  M5.Lcd.setBrightness(60);
  M5.Lcd.drawCentreString("UDP KEYBOARD", 160,2,2);
  M5.Lcd.setCursor(0,18);

  M5.Lcd.setTextSize(1);
  M5.Lcd.println("Connecting to WiFi..");
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid,passwd);
    Serial.println("CONNECTING");
    delay(1000);
  } 
  udp.begin(8080);
  draw_taskbar();
  M5.Lcd.setCursor(0,32);
  Serial.println("CONNECTED");
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println("CONNECTED!");
  
  M5.Lcd.println("Press A when you're ready to send the message");
  M5.Lcd.println("Press B to clear screen and message");
  M5.Lcd.println("Press C to send the message to target computer");
  M5.Lcd.println("Use keyboard to write a message");

  
  
}

void loop() {
  M5.update();
  if (keyboard.available()) {
    char data = (char)keyboard.get_char();
    if (data != 0X0D) {
      M5.Lcd.print(data);
      Serial.print(data);
      udp.beginPacket(target_ip, target_port);
      udp.write(data);
      udp.endPacket();
    }
  }
  if (M5.BtnA.wasPressed()) {
    const char *message = keyboard.get_string().c_str();
    M5.Lcd.println("Message is: ");
    Serial.println(message);
  }
  if (M5.BtnC.wasPressed()) {
    Serial.println("Sending message to server");
    udp.beginPacket(target_ip,target_port);
    const char *msg = keyboard.get_string().c_str();
    udp.write((uint8_t*)msg, sizeof(keyboard.get_string()));
    udp.endPacket();
  }
}