#include "Arduino.h"

#define SPI_CHANNEL 0

#define MSBFIRST 0
#define SPI_MODE0 0

struct SPISettings
{
    SPISettings(unsigned speed, unsigned order, unsigned mode)
        : speed{speed}
        , order{order}
        , mode{mode}
    {}

    unsigned speed;
    unsigned order;
    unsigned mode;
};


struct SPIAdapter
{
    int handle;

    void beginTransaction(SPISettings settings)
    {
        handle = spi_open(adaptor_state.handle, SPI_CHANNEL, settings.speed, settings.order | settings.mode);
    }

    void endTransaction()
    {
        spi_close(adaptor_state.handle, handle);
    }

    byte transfer(uint8_t data)
    {
        byte result{0};
        auto rx = reinterpret_cast<char*>(&result);
        auto tx = reinterpret_cast<char*>(&data);
        spi_xfer(adaptor_state.handle, handle, tx, rx, 1U);
        return result;
    }
};

static SPIAdapter SPI;
