#include "Driver.hpp"
#include <Arduino.h>

 // Initialize all bytes to 0. Initially, the screen is empty.
byte DriverLCD::VIDEO_MEM[504];
float DriverLCD::VIDEO_Z_BUFFER[504] = {-1.f};

DriverLCD::DriverLCD(uint8_t rst, uint8_t ce, uint8_t dc,
uint8_t din, uint8_t clk):
m_data_command_pin(dc), m_data_in_pin(din), m_clock_pin(clk),
m_reset_pin(rst), m_chip_enable_pin(ce), clock(m_clock_pin)
{
    pinMode(m_data_command_pin, OUTPUT);
    pinMode(m_data_in_pin, OUTPUT);
    pinMode(m_clock_pin, OUTPUT);
    pinMode(m_reset_pin, OUTPUT);
    pinMode(m_chip_enable_pin, OUTPUT);

    digitalWrite(m_reset_pin, HIGH);
}

// This function sends to the MPU an 8 bit value, this value represents the state of 
// the 8 pixels in the LCD memory byte that's currently being addressed.
void DriverLCD::send_data(uint8_t px_octet) noexcept
{
    digitalWrite(m_chip_enable_pin, LOW);
    digitalWrite(m_data_command_pin, HIGH);

    for(int b = 0; b < 8; b++)
    {
        bool dbit = px_octet & (0x80 >> b);
        digitalWrite(m_data_in_pin, dbit ? HIGH : LOW);
        //delay(3);
        clock.tick();
    }

    digitalWrite(m_chip_enable_pin, HIGH);
    
}

// This function sends an 8 bit value representing an instruction for the LCD's
// MPU. This value has to be an processor-recognized operation, otherwise it will
// not do anything (essentially acting as a NOP code).
void DriverLCD::send_operation(uint8_t opcode) noexcept
{
    digitalWrite(m_chip_enable_pin, LOW);
    digitalWrite(m_data_command_pin, LOW);

    for(int b = 0; b < 8; b++)
    {
        bool dbit = opcode & (0x80 >> b);
        digitalWrite(m_data_in_pin, dbit ? HIGH : LOW);
        clock.tick();
    }

    digitalWrite(m_chip_enable_pin, HIGH);
}

void DriverLCD::init(uint8_t addr_mode)
{
    if(addr_mode == ADDRMODE_HORIZONTAL)
    {
        digitalWrite(m_reset_pin, LOW);
        digitalWrite(m_reset_pin, HIGH);
        send_operation(0x21);
        send_operation(0x84);
        send_operation(0x0C);
        send_operation(0x14);
        send_operation(0x20);
        send_operation(0x0C);
    }
    
    else
    {
        digitalWrite(m_reset_pin, LOW);
        digitalWrite(m_reset_pin, HIGH);
        send_operation(0x20);
        send_operation(0x84);
        send_operation(0x0C);
        send_operation(0x14);
        send_operation(0x20);
        send_operation(0x0C);
    }
}

void DriverLCD::draw_pixel(uint16_t coordx, uint16_t coordy)
{
    if(coordx >= 0 && coordx <= 83)
    {
        if(coordy >= 0 && coordy <= 47)
            DriverLCD::VIDEO_MEM[coordx + 84*(coordy/8)] = DriverLCD::VIDEO_MEM[coordx + 84*(coordy/8)] | (0x01 << coordy%8);
    }
}

void DriverLCD::display_mem()
{
    send_operation(0x80);
    for(uint8_t k : DriverLCD::VIDEO_MEM)
        this->send_data(k);      
}

void DriverLCD::clr_scr()
{
    for(uint8_t& px : DriverLCD::VIDEO_MEM)
        px = 0x00;
    
}

void DriverLCD::clr_z()
{
    for(float& px : DriverLCD::VIDEO_Z_BUFFER)
        px = 1.f;
    
}
