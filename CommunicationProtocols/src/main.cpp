#define F_CPU 16000000UL  // Definicja częstotliwości zegara (16 MHz)

#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PB5  // Pin wbudowanej diody LED (Arduino Uno)

int main() {
    // Ustawienie pinu PB0 jako wyjścia
    DDRB |= (1 << LED_PIN);

    while (1) {
        // Włącz diodę
        PORTB |= (1 << LED_PIN);
        _delay_ms(500);  // Opóźnienie 500 ms

        // Wyłącz diodę
        PORTB &= ~(1 << LED_PIN);
        _delay_ms(500);  // Opóźnienie 500 ms
    }

    return 0;  // Program nigdy nie dotrze tutaj
}