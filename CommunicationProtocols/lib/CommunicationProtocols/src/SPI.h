/**
 * @file SPI.h
 * @brief Header file for the SPI communication protocol.
 * 
 * This file defines the `SPI` class, which provides methods for initializing and operating 
 * the SPI protocol, including communication with SPI devices (reading/writing data and 
 * registers).
 * 
 * @note This class inherits from the `CommunicationProtocol` class.
 * 
 * @see CommunicationProtocol
 */

#ifndef SPI_H
#define SPI_H

#include "CommunicationProtocol.h"

namespace mm
{
    /**
     * @class SPI
     * @brief Class for SPI communication protocol.
     * 
     * This class provides functions to initialize the SPI communication, 
     * send and receive data to/from SPI devices, and manage register-level access.
     * 
     * It supports both master and slave configurations for SPI communication.
     * 
     * @note The class assumes that the default pins are used for the SPI bus in master mode.
     */
    class SPI : public CommunicationProtocol
    {
    private:
        uint8_t mosi_pin; ///< Pin for Master Out Slave In (MOSI) signal.
        uint8_t miso_pin; ///< Pin for Master In Slave Out (MISO) signal.
        uint8_t sck_pin;  ///< Pin for Serial Clock (SCK) signal.
        uint8_t ss_pin;   ///< Pin for Slave Select (SS) signal.
        bool isMaster;    ///< Flag to indicate whether the device is in master mode.

    public:
        /**
         * @brief Constructs an SPI object with specified pin assignments and mode.
         * 
         * Initializes the SPI interface with specific pins for MOSI, MISO, SCK, and SS, 
         * and sets whether the device operates as a master.
         * 
         * @param mosi The pin number for the MOSI signal.
         * @param miso The pin number for the MISO signal.
         * @param sck The pin number for the SCK signal.
         * @param ss The pin number for the SS signal.
         * @param master Boolean value to set the device as master (true) or slave (false).
         */
        SPI(uint8_t mosi, uint8_t miso, uint8_t sck, uint8_t ss, bool master)
            : mosi_pin(mosi), miso_pin(miso), sck_pin(sck), ss_pin(ss), isMaster(master) {}

        /**
         * @brief Default constructor for the SPI class.
         * 
         * Initializes the SPI pins with default values and sets the device as master.
         */
        SPI()
        {
            mosi_pin = PB3;
            miso_pin = PB4;
            sck_pin = PB5;
            ss_pin = PB2;
            isMaster = true;
        }

        /**
         * @brief Initializes the SPI communication protocol.
         * 
         * This method configures the SPI hardware interface, including the appropriate 
         * pins, mode (master/slave).
         */
        void init() override;

        /**
         * @brief Sends a single byte of data via SPI and returns the received byte.
         * 
         * This function writes a byte of data to the SPI bus and simultaneously reads 
         * the byte that the slave sends back.
         * 
         * @param data The byte of data to send.
         * @return The byte received from the SPI slave device.
         */
        void write(uint8_t data);

        /**
         * @brief Reads a byte of data from the SPI bus.
         * 
         * This function reads a byte of data from the SPI bus (for slave mode or master 
         * receiving data from a slave).
         */
        uint8_t read();

        /**
         * @brief Receives data via SPI (slave mode).
         * 
         * This function receives a byte of data from the SPI bus when the device is in 
         * slave mode.
         * 
         * @return The byte of data received.
         */
        uint8_t recive();

        /**
         * @brief Writes a value to a specified register of an SPI device.
         * 
         * This function writes a byte value to a specified register on an SPI slave device.
         * 
         * @param reg The register address to write to.
         * @param value The byte value to write to the register.
         */
        void writeRegister(uint8_t reg, uint8_t value);

        /**
         * @brief Reads a value from a specified register of an SPI device.
         * 
         * This function reads a byte value from a specified register on an SPI slave device.
         * 
         * @param reg The register address to read from.
         * @return The byte value read from the register.
         */
        uint8_t readRegister(uint8_t reg);
    };
}
#endif // SPI_H