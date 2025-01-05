// I2C.cpp
#include "I2C.h"
#include <avr/io.h>

void I2C::init() {
    // Przykład konfiguracji I2C
    TWSR = 0;
    TWBR = 32; // Ustawienie bitrate dla I2C
    TWCR = (1 << TWEN); // Włącz I2C
}

void I2C::sendData(const char* data, unsigned int length) {
    for (unsigned int i = 0; i < length; ++i) {
        TWDR = data[i];
        TWCR = (1 << TWINT) | (1 << TWEN);
        while (!(TWCR & (1 << TWINT))); // Czekaj na zakończenie transmisji
    }
}

void I2C::receiveData(char* buffer, unsigned int length) {
    for (unsigned int i = 0; i < length; ++i) {
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
        while (!(TWCR & (1 << TWINT))); // Czekaj na dane
        buffer[i] = TWDR;
    }
}
