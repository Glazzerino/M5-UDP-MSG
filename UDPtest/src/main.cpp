#include <M5Stack.h>
#include <WiFiUdp.h>
#include <WiFi.h>
#include <Keyboard.h>
Keyboard keyboard;
WiFiUDP UDP;
int status = WL_IDLE_STATUS;
const char ssid[] = "IZZI-3995";
const char passphrase[] = "12345678";
const char remoteip[] = "192.168.0.9";
const int remoteport = 8080;
char  ReplyBuffer[] = "Hello Edgy Machine!";
void screenPrelude() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.fillRect(0,0,320,18,WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(BLACK);
  M5.Lcd.drawCentreString("UDP TEST",160,2,1);
  M5.Lcd.setCursor(1,20);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.print("Connecting to WiFi");
}

void setup() {
  M5.begin();
  M5.Lcd.setBrightness(30);
  screenPrelude();
  int repcount =0;
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid,passphrase);
    M5.Lcd.print(".");
    if (status == WL_CONNECTED) {
      M5.Lcd.println("\n");
    }
    repcount++;
    if ((repcount % 3) == 0) {
      screenPrelude();
    }
    delay(1000);
  }
  M5.Lcd.println("Connection succesful!");  
  M5.Lcd.println("UDP setting up");
  M5.Lcd.println("UDP ready");
  UDP.begin(8080);
  
}

void loop() {
  M5.update();
  if (M5.BtnB.wasPressed()) {
    M5.Lcd.println("Packet sent");
    UDP.beginPacket(remoteip, remoteport);
    UDP.write((const uint8_t*)ReplyBuffer,sizeof(ReplyBuffer));
    UDP.endPacket();
  }
}