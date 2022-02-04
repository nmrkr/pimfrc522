#ifndef ARDUINO_H
#define ARDUINO_H

#include <chrono>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <ios>
#include <string>
#include <thread>

#include <pigpiod_if2.h>

#define PROGMEM
#define F
#define __FlashStringHelper char

#define SS 8

#define LOW PI_OFF
#define HIGH PI_ON
#define INPUT PI_INPUT
#define OUTPUT PI_OUTPUT

#define HEX true
#define DEC false

using byte = uint8_t;

static
struct adaptor_state_t
{
    const int handle;
    const std::chrono::time_point<std::chrono::steady_clock> start;

    adaptor_state_t();

} adaptor_state;

static
struct serial_t
{
    template<typename T>
    void print(T value)
    {
        std::cout << value;
    }

    template<typename T>
    void print(T value, bool hex)
    {
        std::ios current{nullptr};
        current.copyfmt(std::cout);
        std::cout << (hex ? std::hex : std::dec) << +value;
        std::cout.copyfmt(current);
    }

    template<typename T>
    void println(T value)
    {
        print(value);
        println();
    }

    template<typename T>
    void println(T value, bool hex)
    {
        print(value, hex);
        println();
    }

    void println();
} Serial;

void pinMode(byte pin, byte mode);
int digitalRead(byte pin);
void digitalWrite(byte pin, byte level);

long millis();
void delay(unsigned ms);
void delayMicroseconds(unsigned us);

void yield();

byte pgm_read_byte(const byte* addr);

#endif
