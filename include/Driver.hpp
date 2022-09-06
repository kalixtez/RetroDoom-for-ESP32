#ifndef DRIVER_H
#define DRIVER_H

#include <cinttypes>
#include <Clock.hpp>
#include <Arduino.h>
// Define addressing modes:
#define ADDRMODE_VERTICAL 1
#define ADDRMODE_HORIZONTAL 0
#define INIT_HOR 0b00000010
#define INIT_VER 0b00000010

// pin defines for the analog joystick
#define VX_ANALOG 39
#define VY_ANALOG 36
#define ANALOG_PRESS 5

// pin defines for the nokia lcd
#define CLK_SIGNAL 33
#define DIN_I2C 25
#define DATA_COMMAND 32
#define CHIP_ENABLE 26
#define RESET_LCD 27

struct Point
{
    int x_coord;
    int y_coord;
    float z_depth;
};

// This class will be in charge of the communication with the LCD's chipset.
// It provides an interface of low-level functions to enable a data output from
// the MCU to the screen.


class DriverLCD
{
    public:
        DriverLCD();
        DriverLCD(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
        static byte VIDEO_MEM[504];
        static float VIDEO_Z_BUFFER[504];

    private:
        const uint8_t m_data_command_pin;
        const uint8_t m_data_in_pin;
        const uint8_t m_clock_pin;
        const uint8_t m_reset_pin;
        const uint8_t m_chip_enable_pin;

        Clock clock;
        //const uint32_t m_clockrate;

    public:
        void init(uint8_t);
        static void draw_pixel(uint16_t, uint16_t);
        void clr_scr();
        void clr_z();
        void display_mem();

    private:
        void send_data(uint8_t) noexcept;
        void send_operation(uint8_t) noexcept;


};

#endif