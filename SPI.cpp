#include "SPI.h"

SPISettings::SPISettings(unsigned speed, unsigned order, unsigned mode)
    : speed{speed}
    , order{order}
    , mode{mode}
{}

void SPIAdapter::beginTransaction(SPISettings settings)
{
    handle = spi_open(adaptor_state.handle, spiChannel, settings.speed, settings.order | settings.mode);
}

void SPIAdapter::endTransaction()
{
    spi_close(adaptor_state.handle, handle);
}

byte SPIAdapter::transfer(uint8_t data)
{
    byte result{0};
    auto rx = reinterpret_cast<char*>(&result);
    auto tx = reinterpret_cast<char*>(&data);
    spi_xfer(adaptor_state.handle, handle, tx, rx, 1U);
    return result;
}
