// UART.cpp
#include "UART.h"
#include <avr/io.h>

void UART::init() {
    // Przykład konfiguracji UART
    UBRR0H = 0;
    UBRR0L = 103; // Ustawienie dla 9600 baud przy 16 MHz
    UCSR0B = (1 << TXEN0) | (1 << RXEN0); // Włącz transmisję i odbiór
}
