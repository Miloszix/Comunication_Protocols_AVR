/**
 * @file I2C.h
 * @brief Header file for the I2C communication protocol.
 * 
 * This file defines the `I2C` class, which provides methods for initializing and operating 
 * the I2C protocol, including communication with I2C devices.
 * 
 * @note This class inherits from the `CommunicationProtocol` class.
 * 
 * @see CommunicationProtocol
 */

#ifndef I2C_H
#define I2C_H

#include "CommunicationProtocol.h"

namespace mm
{
    /**
     * @class I2C
     * @brief Class for I2C communication protocol.
     * 
     * This class provides functions to initialize the I2C communication, 
     * send and receive data to/from I2C devices, and manage register-level access.
     * 
     * It supports single byte and block write/read operations as well as the 
     * ability to communicate with I2C slave devices by their address.
     * 
     * @note The class assumes that the prescaling value is provided or defaults to 1.
     */
    class I2C : public CommunicationProtocol
    {
    private:
        uint8_t prescaling; ///< Prescaling value for the communication speed.

    public:
        /**
         * @brief Constructs an I2C object with a specified prescaling value.
         * 
         * Initializes the I2C interface with a specific prescaler value.
         * 
         * @param prs The prescaling value to set the communication speed(1, 4, 16, 64).
         */
        I2C(uint32_t prs)
            : prescaling(prs) {}

        /**
         * @brief Default constructor for the I2C class.
         * 
         * Initializes the prescaling value to 1 if no argument is provided.
         */
        I2C()
        {
            prescaling = 1;
        }

        /**
         * @brief Initializes the I2C communication protocol.
         * 
         * This method configures the I2C hardware interface and prepares it for communication.
         */
        void init() override;

        /**
         * @brief Starts an I2C communication session.
         * 
         * Initiates the I2C start condition to signal the beginning of communication.
         */
        void start();

        /**
         * @brief Stops an ongoing I2C communication session.
         * 
         * Sends the I2C stop condition to end communication with the current device.
         */
        void stop();

        /**
         * @brief Sends a single byte of data over I2C.
         * 
         * This function sends a single byte of data on the I2C bus.
         * 
         * @param data The byte of data to transmit.
         */
        void write(uint8_t data);

        /**
         * @brief Writes a byte of data to a specified I2C slave device.
         * 
         * This function writes a single byte of data to a specified I2C slave address.
         * 
         * @param slave_address The address of the I2C slave device.
         * @param data The byte of data to write to the slave.
         */
        void write_data(uint8_t slave_address, uint8_t data);

        /**
         * @brief Writes data to a specific register of an I2C slave device.
         * 
         * This function writes a byte of data to a specified register of an I2C slave device.
         * 
         * @param slave_address The address of the I2C slave device.
         * @param reg The register address where data should be written.
         * @param data The byte of data to write.
         */
        void write_register(uint8_t slave_address, uint8_t reg, uint8_t data);

        /**
         * @brief Reads a byte of data from the I2C bus.
         * 
         * This function reads a byte of data from the I2C bus with an optional acknowledgment.
         * 
         * @param ack Boolean value to control whether to send an ACK (true) or NACK (false) after reading.
         * @return The byte of data read from the bus.
         */
        uint8_t read(bool ack);

        /**
         * @brief Reads a byte of data from an I2C slave device.
         * 
         * This function reads a byte of data from the specified I2C slave device.
         * 
         * @param slave_address The address of the I2C slave device.
         * @return The byte of data read from the slave device.
         */
        uint8_t read_data(uint8_t slave_address);

        /**
         * @brief Reads a byte of data from a specific register of an I2C slave device.
         * 
         * This function reads a byte of data from the specified register of an I2C slave device.
         * 
         * @param slave_address The address of the I2C slave device.
         * @param reg The register address to read from.
         * @return The byte of data read from the register.
         */
        uint8_t read_register(uint8_t slave_Address, uint8_t reg);

        /**
         * @brief Writes a block of data to an I2C slave device.
         * 
         * This function sends multiple bytes of data to a specified I2C slave device,
         * starting from a specific register.
         * 
         * @param slave_address The address of the I2C slave device.
         * @param reg The starting register address.
         * @param data Pointer to the data block to write.
         * @param size The number of bytes to write.
         */
        void write_block(uint8_t slave_address, uint8_t reg, uint8_t *data, uint8_t size);

        /**
         * @brief Reads a block of data from an I2C slave device.
         * 
         * This function reads multiple bytes of data from a specified I2C slave device,
         * starting from a specific register.
         * 
         * @param slave_address The address of the I2C slave device.
         * @param reg The starting register address.
         * @param data Pointer to a buffer to store the received data.
         * @param size The number of bytes to read.
         */
        void read_block(uint8_t slave_address, uint8_t reg, uint8_t *data, uint8_t size);
    };
}
#endif // I2C_H