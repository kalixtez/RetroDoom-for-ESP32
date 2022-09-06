#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>

struct Clock
{
    private:
        const int pin;
        const int freq;

    public:
        Clock(uint8_t clk_pin):
        pin(clk_pin), freq(1000000)
        {}

        void tick()
        {
            digitalWrite(pin, HIGH);
            digitalWrite(pin, LOW);  
        }
};


#endif