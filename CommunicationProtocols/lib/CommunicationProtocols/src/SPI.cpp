// SPI.cpp
#include "SPI.h"
#include <avr/io.h> // Biblioteka AVR

void SPI::init() {
    // Przykład konfiguracji SPI
    SPCR = (1 << SPE) | (1 << MSTR); // Włącz SPI, ustaw jako master
}

void SPI::sendData(const char* data, unsigned int length) {
    for (unsigned int i = 0; i < length; ++i) {
        SPDR = data[i];
        while (!(SPSR & (1 << SPIF))); // Czekaj na zakończenie transmisji
    }
}

void SPI::receiveData(char* buffer, unsigned int length) {
    for (unsigned int i = 0; i < length; ++i) {
        SPDR = 0xFF; // Wyślij dummy byte
        while (!(SPSR & (1 << SPIF))); // Czekaj na dane
        buffer[i] = SPDR;
    }
}
