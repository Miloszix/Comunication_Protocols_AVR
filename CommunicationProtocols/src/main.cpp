#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "sensor.h"
#include "communication.h"
//#include "sensorSPI.h"

#define SCL_CLK 100000UL 

int main() {
    double temperature;
    double humidity;
    double pressure;

    mm::UART uart;
    uart.init();

    mm::I2C i2c;
    i2c.init();

    // mm::SPI spi;
    // spi.init();

    uart.transmitString("Hello, UART!\n");
    initBME280();
    char buffer[20];

    while(1){
        readRawData(); 

        temperature = getTemp();
        humidity = getHum(); 
        pressure = getPress();

        dtostrf(temperature, 0, 2, buffer); // Convert temperature to string with 2 decimal places
        uart.transmitString("Tempreture: ");
        uart.transmitString(buffer);
        uart.transmitString(" C\n");

        dtostrf(humidity, 0, 2, buffer); // Convert humidity to string with 2 decimal places
        uart.transmitString("Humidity: ");
        uart.transmitString(buffer);
        uart.transmitString(" %\n");

        dtostrf(pressure, 0, 2, buffer); // Convert pressure to string with 2 decimal places
        uart.transmitString("Pressure: ");
        uart.transmitString(buffer);
        uart.transmitString(" hPa\n");

        _delay_ms(1000);
    }
}