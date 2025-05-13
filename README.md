# Generic Communication Protocol Library for AVR Microcontrollers

## Overview

This project is a **generic C++ library for AVR microcontrollers**, supporting three popular communication protocols:

- **I2C**
- **SPI**
- **UART**

The library is designed for flexibility, modularity, and easy adaptation to various AVR microcontroller models. It also includes a sample implementation of the **BME280 environmental sensor**, communicating via I2C and transmitting data via UART.

## Features

- Unified interface using a base abstract class
- Support for master/slave mode in SPI
- Read/write support for bytes and registers (SPI, I2C)
- Device address handling in I2C
- Buffered string support for UART
- Modular architecture for easy extension

## Project Structure

```
/src
│
├── CommunicationProtocol.h     # Base class for all protocols
├── SPI.h / SPI.cpp             # SPI implementation
├── I2C.h / I2C.cpp             # I2C implementation
├── UART.h / UART.cpp           # UART implementation
└── Communication.h             # Aggregated interface for use in user code
```

## Class Descriptions

### CommunicationProtocol (abstract base class)

- `virtual void init() = 0;`  
Provides a unified interface for initializing each protocol.

### SPI

- Constructor accepts:
  - Pin definitions
  - Master/Slave mode
- Functions:
  - `writeByte()`, `readByte()`
  - `writeRegister()`, `readRegister()`

### I2C

- Constructor allows setting:
  - Clock speed
  - Prescaler
- Functions:
  - `start()`, `stop()`
  - `writeByte()`, `readByte()`
  - `writeRegister()`, `readRegister()`
  - Extended: Read/write sequences of registers

### UART

- Constructor supports:
  - Interface selection (e.g., USART0)
  - Baud rate setup
- Functions:
  - `sendByte()`, `readByte()`
  - `sendString()`, `readString()`

## Example Use Case

- BME280 sensor connected via I2C
- Sensor readings transmitted over UART

This implementation serves as a demonstration of how to integrate the library into a real-world sensor application.

## Requirements

- AVR-compatible development environment (e.g., Atmel Studio or PlatformIO)
- AVR microcontroller with support for I2C, SPI, UART

## Author

- **Miłosz Mynarczuk**
- Project for **AGH University of Science and Technology**
- Course: *Object-Oriented Programming Languages*, EiT Year 3
- Instructor: *Jakub Zimnol*

## License

This project is academic in nature. License terms can be added as needed.
