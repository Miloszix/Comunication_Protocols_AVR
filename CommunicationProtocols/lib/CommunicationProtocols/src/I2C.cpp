// I2C.cpp
#include "I2C.h"
#include <avr/io.h>

#define TWBR_VALUE 72

void I2C::init() {
    TWSR = 0x00;
    TWBR = TWBR_VALUE;
    TWCR = (1 << TWEN);
}

// Funkcja do wysyłania danych przez I2C
void I2C::start() {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

// Funkcja do zakończenia transmisji I2C
void I2C::stop() {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    while (TWCR & (1 << TWSTO));
}

// Funkcja do wysyłania bajtu przez I2C
void I2C::write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

// Funkcja do zapisu pojedynczego bajtu do urządzenia I2C bez podawania rejestru
void I2C::write_data(uint8_t slave_address, uint8_t data) {
    I2C::start();
    I2C::write(slave_address << 1);
    I2C::write(data);   
    I2C::stop();
}

// Funkcja do zapisu pojedynczego rejestru w urządzeniu I2C
void I2C::write_register(uint8_t slave_address, uint8_t reg, uint8_t data) {
    I2C::start();
    I2C::write(slave_address << 1);
    I2C::write(reg);
    I2C::write(data);
    I2C::stop();
}

// Funkcja do odbierania danych (w trybie Master)
uint8_t I2C::read(bool ack) {
    TWCR = (1 << TWINT) | (ack ? (1 << TWEA) : 0) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

// Funkcja do odczytu pojedynczego bajtu z urządzenia I2C bez podawania rejestru
uint8_t I2C::read_data(uint8_t slave_address) {
    uint8_t data;
    I2C::start();
    I2C::write(slave_address << 1);
    I2C::start();
    I2C::write((slave_address << 1) | 1);
    data = I2C::read(false);
    I2C::stop();
    return data;
}

// Funkcja do odczytu pojedynczego rejestru z urządzenia I2C
uint8_t I2C::read_register(uint8_t slave_address, uint8_t reg) {
    uint8_t data;
    I2C::start();
    I2C::write(slave_address << 1);
    I2C::write(reg);
    I2C::start();
    I2C::write((slave_address << 1) | 1);
    data = I2C::read(false);
    I2C::stop();
    return data;
}

// Funkcja do zapisu bloku danych do urządzenia I2C
void I2C::write_block(uint8_t slave_address, uint8_t reg, uint8_t* data, uint8_t size) {
    I2C::start();
    I2C::write(slave_address << 1);
    I2C::write(reg);

    for (uint8_t i = 0; i < size; i++) {
        I2C::write(data[i]);
    }

    I2C::stop();
}

// Funkcja do odczytu bloku danych z urządzenia I2C
void I2C::read_block(uint8_t slave_address, uint8_t reg, uint8_t* data, uint8_t size) {
    I2C::start();
    I2C::write(slave_address << 1);
    I2C::write(reg);
    I2C::start();
    I2C::write((slave_address << 1) | 1);

    for (uint8_t i = 0; i < size - 1; i++) {
        data[i] = I2C::read(true);
    }

    data[size - 1] = I2C::read(false);
    I2C::stop();
}