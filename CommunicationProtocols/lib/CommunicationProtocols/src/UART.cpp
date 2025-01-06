#include "UART.h"
#include <avr/io.h>

#define BAUD_PRESCALE(F_CPU, speed) (((F_CPU / (speed * 16UL))) - 1)

UART::UART(uint8_t usart_number, uint32_t baudrate) 
    : usart_speed(baudrate), usart_number(usart_number) {}

void UART::init() {
    uint16_t ubrr_value = BAUD_PRESCALE(F_CPU, usart_speed);

    switch (usart_number) {
        case 0:  // USART0
            UBRR0H = (uint8_t)(ubrr_value >> 8);
            UBRR0L = (uint8_t)ubrr_value; 
            UCSR0B = (1 << TXEN0) | (1 << RXEN0);
            UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
            break;

#if defined(UBRR1H)  // Sprawdź, czy USART1 jest dostępny
        case 1:  // USART1
            UBRR1H = (uint8_t)(ubrr_value >> 8);
            UBRR1L = (uint8_t)ubrr_value;
            UCSR1B = (1 << TXEN1) | (1 << RXEN1); 
            UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
            break;
#endif

#if defined(UBRR2H)  // Sprawdź, czy USART2 jest dostępny
        case 2:  // USART2
            UBRR2H = (uint8_t)(ubrr_value >> 8); 
            UBRR2L = (uint8_t)ubrr_value; 
            UCSR2B = (1 << TXEN2) | (1 << RXEN2);
            UCSR2C = (1 << UCSZ21) | (1 << UCSZ20);
            break;
#endif

#if defined(UBRR3H)  // Sprawdź, czy USART3 jest dostępny
        case 3:  // USART3
            UBRR3H = (uint8_t)(ubrr_value >> 8); 
            UBRR3L = (uint8_t)ubrr_value;     
            UCSR3B = (1 << TXEN3) | (1 << RXEN3); 
            UCSR3C = (1 << UCSZ31) | (1 << UCSZ30);
            break;
#endif

        default:
            usart_number = 0; 
            UBRR0H = (uint8_t)(ubrr_value >> 8);
            UBRR0L = (uint8_t)ubrr_value;
            UCSR0B = (1 << TXEN0) | (1 << RXEN0);
            UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
            break;
    }
}

void UART::transmitByte(uint8_t data) {
    switch (usart_number) {
        case 0:
            while (!(UCSR0A & (1 << UDRE0)));
            UDR0 = data;
            break;

#if defined(UDR1)
        case 1:
            while (!(UCSR1A & (1 << UDRE1)));
            UDR1 = data;
            break;
#endif

#if defined(UDR2)
        case 1:
            while (!(UCSR2A & (1 << UDRE2)));
            UDR2 = data;
            break;
#endif

#if defined(UDR3)
        case 1:
            while (!(UCSR3A & (1 << UDRE3)));
            UDR3 = data;
            break;
#endif

        default:
            while (!(UCSR0A & (1 << UDRE0)));
            UDR0 = data;
            break;
    }
}

uint8_t UART::receiveByte() {
    switch (usart_number) {
        case 0:
            while (!(UCSR0A & (1 << RXC0)));
            return UDR0;

#if defined(UDR1)
        case 1:
            while (!(UCSR1A & (1 << RXC1)));
            return UDR1;
#endif

#if defined(UDR2)
        case 1:
            while (!(UCSR2A & (1 << RXC2)));
            return UDR2;
#endif

#if defined(UDR3)
        case 1:
            while (!(UCSR3A & (1 << RXC3)));
            return UDR3;
#endif

        default:
            while (!(UCSR0A & (1 << RXC0)));
            return UDR0;
            return 0;
    }
}

void UART::transmitString(const char* str) {
    while (*str != '\0') {
        transmitByte(*str);
        str++;
    }
}

void UART::receiveString(char* buffer, uint8_t maxLength) {
    uint8_t i = 0;
    char receivedChar;
    while (i < maxLength - 1) {
        receivedChar = receiveByte();
        if (receivedChar == '\n' || receivedChar == '\r') {
            break;
        }
        buffer[i++] = receivedChar;
    }
    buffer[i] = '\0';
}


