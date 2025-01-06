#define SCL_CLK 100000UL  // 100 kHz I2C Clock

#include <avr/io.h>
#include <util/delay.h>

#include "UART.h"
#include "I2C.h"

// void setup(){
    
// }

int main() {
    UART uart(0, 9600); // USART0 z prędkością 9600
    uart.init();

    uart.transmitString("Hello, UART!\n");

    char buffer[50];
    uart.receiveString(buffer, 50);
    
    while (1) {
    }
}