#include "Keyboard.h"

Keyboard::Keyboard() {
    
    pinMode(KEY_INT, INPUT_PULLUP);
}

uint8_t Keyboard::get_char() {
    uint8_t data = 0x00;
    if (digitalRead(KEY_INT) == LOW) {
        Wire.requestFrom(KEY_ADDR,1);
        while (Wire.available()) {
            data = Wire.read();
            if (data != 0) {
                if (data == 0x0D){
                    data = (uint8_t)'\n';
                }
            }
        }
    }
    return data;
}

void Keyboard::update() {
    char newchar = (char)this->get_char();
    this->line.push_back(newchar);
}

const char* Keyboard::get_line() {
    return this->line.c_str();
}