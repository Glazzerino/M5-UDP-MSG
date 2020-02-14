#include "Keyboard.h"

//Assumes Wire.h has been already started
Keyboard::Keyboard() {}

bool Keyboard::available() {
    if (digitalRead(KEYBOARD_INT) == LOW) {
        return true;
    } else {
        return false;
    }
}

uint8_t Keyboard::get_char() {
    uint8_t data;
    
        Wire.requestFrom(KEYBOARD_ADDR,1);
         while (Wire.available()) {
             data = Wire.read();
            if (data != 0) {
                return data;  
                cached_string += (char)data;  
            } else if (data == 0x0D) {
                cached_string += '\n';
                return data;
            }
    }
}

std::string Keyboard::get_string() {
    return cached_string;
}