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

    adaptor_state_t()
        : handle{pigpio_start(nullptr, nullptr)}
        , start{std::chrono::steady_clock::now()}
    {
        if (handle < 0)
            std::cerr << "SPIAdapter failed to connect to pigpiod." << std::endl;
    }

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
        std::cout << (hex ? std::hex : std::dec) << value;
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

    void println()
    {
        std::cout << std::endl;
    }
} Serial;

void pinMode(byte pin, byte mode)
{
    set_mode(adaptor_state.handle, pin, mode);
}

int digitalRead(byte pin)
{
    return gpio_read(adaptor_state.handle, pin);
}

void digitalWrite(byte pin, byte level)
{
    gpio_write(adaptor_state.handle, pin, level);
}

long millis()
{
    using namespace std::chrono;
    const auto span = steady_clock::now() - adaptor_state.start;
    return duration_cast<milliseconds>(span).count();
}

void delay(unsigned ms)
{
    using namespace std::chrono;
    std::this_thread::sleep_for(milliseconds(ms));
}

void delayMicroseconds(unsigned us)
{
    using namespace std::chrono;
    std::this_thread::sleep_for(microseconds(us));
}

void yield()
{
    std::this_thread::yield();
}

byte pgm_read_byte(const byte* addr)
{
    return *addr;
}

#endif
