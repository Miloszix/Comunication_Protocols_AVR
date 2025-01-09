/**
 * @file UART.h
 * @brief Header file for the UART communication protocol.
 * 
 * This file defines the `UART` class, which provides methods for initializing and operating 
 * the UART protocol, including communication with UART devices (transmitting and receiving 
 * data, and transmitting strings).
 * 
 * @note This class inherits from the `CommunicationProtocol` class.
 * 
 * @see CommunicationProtocol
 */

#ifndef UART_H
#define UART_H

#include "CommunicationProtocol.h"

namespace mm
{
    /**
     * @class UART
     * @brief Class for UART communication protocol.
     * 
     * This class provides functions to initialize the UART communication, 
     * transmit and receive data, and manage string communication.
     * 
     * It supports a configurable speed and USART number for different 
     * UART instances.
     * 
     * @note The class assumes a default speed of 9600 and USART number 0 if no values are provided.
     */
    class UART : public CommunicationProtocol
    {
    private:
        uint32_t usart_speed; ///< speed for UART communication.
        uint8_t usart_number; ///< USART instance number.

    public:
        /**
         * @brief Constructs a UART object with specified USART number and speed.
         * 
         * Initializes the UART interface with a specific USART number and speed.
         * 
         * @param usart_number The USART instance number.
         * @param speed The speed for UART communication.
         */
        UART(uint8_t usart_number, uint32_t speed) 
            : usart_speed(speed), usart_number(usart_number) {}

        /**
         * @brief Default constructor for the UART class.
         * 
         * Initializes the UART with a default speed of 9600 and USART number 0.
         */
        UART(){
            usart_speed = 9600;
            usart_number = 0;
        }

        /**
         * @brief Initializes the UART communication protocol.
         * 
         * This method configures the UART interface, including the speed 
         * and the USART instance.
         */
        void init() override;

        /**
         * @brief Transmits a single byte of data over UART.
         * 
         * This function sends a single byte of data over the UART communication channel.
         * 
         * @param data The byte of data to transmit.
         */
        void transmitByte(uint8_t data);

        /**
         * @brief Receives a single byte of data via UART.
         * 
         * This function reads a byte of data from the UART communication channel.
         * 
         * @return The byte of data received from UART.
         */
        uint8_t receiveByte();

        /**
         * @brief Transmits a string of characters over UART.
         * 
         * This function sends a null-terminated string over the UART communication channel.
         * 
         * @param str The string of characters to transmit.
         */
        void transmitString(const char *str);

        /**
         * @brief Receives a string of characters via UART.
         * 
         * This function reads characters from the UART communication channel until 
         * the specified maximum length is reached or a null terminator is encountered.
         * 
         * @param buffer A pointer to the buffer to store the received string.
         * @param maxLength The maximum number of characters to receive.
         */
        void receiveString(char *buffer, uint8_t maxLength);
    };
}

#endif // UART_H
