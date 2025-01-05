// I2C.h
#ifndef I2C_H
#define I2C_H

#include "CommunicationProtocol.h"

class I2C : public CommunicationProtocol {
private:
    uint32_t bitrate;      // Prędkość transmisji I2C
    uint8_t prescaler;     // Przeskalowanie zegara TWI

public:

    //napisać konstruktor

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
    
    void setBitrate(uint32_t b) {
        bitrate = b;
        init();
    }

    // Setter dla preskalera
    void setPrescaler(uint8_t p) {
        prescaler = p;
        init();
    }

    uint32_t getBitrate() const {
        return bitrate;
    }

    // Getter dla preskalera
    uint8_t getPrescaler() const {
        return prescaler;
    }
};

#endif // I2C_H
