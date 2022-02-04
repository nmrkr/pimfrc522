#include "Arduino.h"

#define MSBFIRST 0
#define SPI_MODE0 0

struct SPISettings
{
    SPISettings(unsigned speed, unsigned order, unsigned mode);

    unsigned speed;
    unsigned order;
    unsigned mode;
};


struct SPIAdapter
{
    int handle;
    int spiChannel{0};

    void beginTransaction(SPISettings settings);
    void endTransaction();

    byte transfer(uint8_t data);
};

static SPIAdapter SPI;
