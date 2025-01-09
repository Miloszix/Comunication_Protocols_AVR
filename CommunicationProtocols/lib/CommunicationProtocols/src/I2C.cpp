#include "I2C.h"
#include <avr/io.h>

#define BITRATE(TWSR) ((F_CPU / SCL_CLK) - 16) / (2 * ((1 << ((TWSR) & 0x03)) * (1 << ((TWSR) & 0x03))))

#ifndef SCL_CLK
#define SCL_CLK 100000UL
#endif

void mm::I2C::init()
{
    switch (prescaling)
    {
    case 1:
        TWSR = 0x0;
        break;
    case 4:
        TWSR = 0x1;
        break;
    case 16:
        TWSR = 0x2;
        break;
    case 64:
        TWSR = 0x3;
        break;
    default:
        TWSR = 0x00;
        break;
    }
    TWSR = 0x00;
    TWBR = BITRATE(TWSR);
    TWCR = (1 << TWEN);
}

void mm::I2C::start()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
}

void mm::I2C::stop()
{
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    while (TWCR & (1 << TWSTO))
        ;
}

void mm::I2C::write(uint8_t data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
}

void mm::I2C::write_data(uint8_t slave_address, uint8_t data)
{
    mm::I2C::start();
    mm::I2C::write(slave_address << 1);
    mm::I2C::write(data);
    mm::I2C::stop();
}

void mm::I2C::write_register(uint8_t slave_address, uint8_t reg, uint8_t data)
{
    mm::I2C::start();
    mm::I2C::write(slave_address << 1);
    mm::I2C::write(reg);
    mm::I2C::write(data);
    mm::I2C::stop();
}

uint8_t mm::I2C::read(bool ack)
{
    TWCR = (1 << TWINT) | (ack ? (1 << TWEA) : 0) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)))
        ;
    return TWDR;
}

uint8_t mm::I2C::read_data(uint8_t slave_address)
{
    uint8_t data;
    mm::I2C::start();
    mm::I2C::write(slave_address << 1);
    mm::I2C::start();
    mm::I2C::write((slave_address << 1) | 1);
    data = mm::I2C::read(false);
    mm::I2C::stop();
    return data;
}

uint8_t mm::I2C::read_register(uint8_t slave_address, uint8_t reg)
{
    uint8_t data;
    mm::I2C::start();
    mm::I2C::write(slave_address << 1);
    mm::I2C::write(reg);
    mm::I2C::start();
    mm::I2C::write((slave_address << 1) | 1);
    data = mm::I2C::read(false);
    mm::I2C::stop();
    return data;
}

void mm::I2C::write_block(uint8_t slave_address, uint8_t reg, uint8_t *data, uint8_t size)
{
    mm::I2C::start();
    mm::I2C::write(slave_address << 1);
    mm::I2C::write(reg);

    for (uint8_t i = 0; i < size; i++)
    {
        mm::I2C::write(data[i]);
    }

    mm::I2C::stop();
}

void mm::I2C::read_block(uint8_t slave_address, uint8_t reg, uint8_t *data, uint8_t size)
{
    mm::I2C::start();
    mm::I2C::write(slave_address << 1);
    mm::I2C::write(reg);
    mm::I2C::start();
    mm::I2C::write((slave_address << 1) | 1);

    for (uint8_t i = 0; i < size - 1; i++)
    {
        data[i] = mm::I2C::read(true);
    }

    data[size - 1] = mm::I2C::read(false);
    mm::I2C::stop();
}