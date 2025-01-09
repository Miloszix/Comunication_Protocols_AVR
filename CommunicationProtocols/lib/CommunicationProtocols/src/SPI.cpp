#include "SPI.h"
#include <avr/io.h>

void mm::SPI::init()
{
    if (isMaster)
    {
        DDRB |= (1 << mosi_pin) | (1 << sck_pin) | (1 << ss_pin);
        DDRB &= ~(1 << miso_pin);
        SPCR = (1 << SPE) | (1 << MSTR);
    }
    else
    {
        DDRB |= (1 << miso_pin);
        DDRB &= ~((1 << mosi_pin) | (1 << sck_pin) | (1 << ss_pin));
        SPCR = (1 << SPE);
    }
}

void mm::SPI::write(uint8_t data)
{
    SPDR = data;
    while (!(SPSR & (1 << SPIF)))
        ;
}

uint8_t mm::SPI::read()
{
    SPDR = 0xFF;
    while (!(SPSR & (1 << SPIF)))
        ;
    return SPDR;
}

uint8_t mm::SPI::recive()
{
    while (!(SPSR & (1 << SPIF)))
        ;
    return SPDR;
}

void mm::SPI::writeRegister(uint8_t reg, uint8_t value)
{
    reg &= 0x7F;
    PORTB &= ~(1 << ss_pin);
    SPI::write(reg);
    SPI::write(value);
    PORTB |= (1 << ss_pin);
}

uint8_t mm::SPI::readRegister(uint8_t reg)
{
    reg |= 0x80;
    PORTB &= ~(1 << ss_pin);
    SPI::write(reg);
    return SPI::read();
    PORTB |= (1 << ss_pin);
}
