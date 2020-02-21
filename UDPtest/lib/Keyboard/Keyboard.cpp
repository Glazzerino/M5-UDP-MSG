#include "Keyboard.h"

//Assumes Wire.h has been already started
Keyboard::Keyboard() {
    pinMode(KEYBOARD_INT, INPUT_PULLUP);
}

bool Keyboard::available() {
    if (digitalRead(KEYBOARD_INT) == LOW) {
        return true;
    } else {
        return false;
    }
}

uint8_t Keyboard::get_char() {
    uint8_t data;
    if (digitalRead(KEYBOARD_INT) == LOW) {
        Wire.requestFrom(KEYBOARD_ADDR,1);
         while (Wire.available()) {
             data = Wire.read();
            if (data != 0) {
                cached_string.push_back((char)data);  
                return data; 
            } else if (data == 0x0D) {
                return data;
            }
        }
    }
}

std::string Keyboard::get_string() {
    return cached_string;
}