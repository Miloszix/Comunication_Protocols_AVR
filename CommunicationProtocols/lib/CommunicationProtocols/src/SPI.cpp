// SPI.cpp
#include "SPI.h"
#include <avr/io.h> // Biblioteka AVR

void SPI::init() {
    // Przykład konfiguracji SPI
    SPCR = (1 << SPE) | (1 << MSTR); // Włącz SPI, ustaw jako master
}

