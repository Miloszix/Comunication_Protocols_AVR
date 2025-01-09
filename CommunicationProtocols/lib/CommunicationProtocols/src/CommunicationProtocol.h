/**
 * @file Communication.h
 * @brief Header file for the CommunicationProtocol class.
 * 
 * This file defines the `CommunicationProtocol` abstract base class, which provides
 * the interface for different communication protocols (I2C, SPI, UART).
 * 
 * @note This class serves as a base for all communication protocol classes.
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <avr/io.h>

namespace mm
{
    /**
     * @class CommunicationProtocol
     * @brief Abstract base class for communication protocols.
     * 
     * This class provides the basic interface for initializing and managing communication
     * with peripheral devices. It is intended to be inherited by specific protocol classes 
     * such as I2C, SPI, or UART, which implement the actual communication logic.
     * 
     * @note This class cannot be instantiated directly and serves only as a base class.
     */
    class CommunicationProtocol
    {
    public:
        /**
         * @brief Initializes the communication protocol.
         * 
         * This pure virtual function must be implemented by derived classes to initialize
         * the specific communication protocol.
         * 
         * @note Derived classes must provide their own implementation of this method.
         */
        virtual void init() = 0;
    };
}

#endif // COMMUNICATION_H
