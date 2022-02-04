 #include "Arduino.h"

adaptor_state_t::adaptor_state_t()
    : handle{pigpio_start(nullptr, nullptr)}
    , start{std::chrono::steady_clock::now()}
{
    if (handle < 0)
        std::cerr << "SPIAdapter failed to connect to pigpiod." << std::endl;
}

void serial_t::println()
{
    std::cout << std::endl;
}

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
