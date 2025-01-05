// I2C.h
#ifndef I2C_H
#define I2C_H

#include "CommunicationProtocol.h"

#ifndef SCL_CLK
#define SCL_CLK 100000UL
#endif

class I2C : public CommunicationProtocol {
public:
    void init() override;
    void start() override;
    void stop() override;
    void write(uint8_t data);
    void write_data(uint8_t slave_address, uint8_t data);
    void write_register(uint8_t slave_address, uint8_t reg, uint8_t data);
    uint8_t read(bool ack);
    uint8_t read_data(uint8_t slave_address);
    uint8_t read_register(uint8_t slave_Address, uint8_t reg);
    void write_block(uint8_t slave_address, uint8_t reg, uint8_t* data, uint8_t size);
    void read_block(uint8_t slave_address, uint8_t reg, uint8_t* data, uint8_t size);
};

#endif // I2C_H
