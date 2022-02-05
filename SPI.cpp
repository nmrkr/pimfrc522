#include "SPI.h"

SPISettings::SPISettings(unsigned speed, unsigned order, unsigned mode)
    : speed{speed}
    , order{order}
    , mode{mode}
{}

void SPIAdaptor::beginTransaction(SPISettings settings)
{
    handle = spi_open(adaptor_state.handle, spiChannel, settings.speed, settings.order | settings.mode);
    if (handle < 0)
        std::cerr << "Arduino adaptor: Error opening SPI channel." << std::endl;
}

void SPIAdaptor::endTransaction()
{
    spi_close(adaptor_state.handle, handle);
}

byte SPIAdaptor::transfer(byte data)
{
    byte result{0};
    auto rx = reinterpret_cast<char*>(&result);
    auto tx = reinterpret_cast<char*>(&data);
    spi_xfer(adaptor_state.handle, handle, tx, rx, 1U);
    return result;
}
