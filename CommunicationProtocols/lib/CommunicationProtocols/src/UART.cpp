// UART.cpp
#include "UART.h"
#include <avr/io.h>

void UART::init() {
    // Przykład konfiguracji UART
    UBRR0H = 0;
    UBRR0L = 103; // Ustawienie dla 9600 baud przy 16 MHz
    UCSR0B = (1 << TXEN0) | (1 << RXEN0); // Włącz transmisję i odbiór
}

void UART::sendData(const char* data, unsigned int length) {
    for (unsigned int i = 0; i < length; ++i) {
        while (!(UCSR0A & (1 << UDRE0))); // Czekaj na wolny rejestr
        UDR0 = data[i];
    }
}

void UART::receiveData(char* buffer, unsigned int length) {
    for (unsigned int i = 0; i < length; ++i) {
        while (!(UCSR0A & (1 << RXC0))); // Czekaj na odebranie danych
        buffer[i] = UDR0;
    }
}
