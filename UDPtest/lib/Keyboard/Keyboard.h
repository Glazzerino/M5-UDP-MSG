/**
 * Utility class wrote for the FACES Keyboard module
 * **/
#include<Wire.h>
#include <string>
class Keyboard {
    public:
        Keyboard();
        uint8_t get_char();
        const char* get_string();
        void update();
        const char* get_line();
    private:
        std::string line ="";
        const int KEY_INT = 5;
        const uint8_t KEY_ADDR = 0x08;
};