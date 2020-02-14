#pragma once
#include <Wire.h>
#include <string>
class Keyboard {
    public:
        Keyboard();
        bool available();
        uint8_t get_char();
        std::string get_string();
    private:
        std::string cached_string = "";
        const int KEYBOARD_INT = 5;
        const uint8_t KEYBOARD_ADDR = 0X08;
        
};