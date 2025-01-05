// I2C.h
#ifndef I2C_H
#define I2C_H

#include "CommunicationProtocol.h"

class I2C : public CommunicationProtocol {
private:
    uint32_t bitrate;      // Prędkość transmisji I2C
    uint8_t prescaler;     // Przeskalowanie zegara TWI
    uint8_t slaveAddress;  // Adres urządzenia I2C
    bool isMaster;         // Czy tryb Master (true) czy Slave (false)

public:
    void init() override;
    void start() override;
    void stop() override;
    void write(uint8_t data);
    void write_register(uint8_t slave_address, uint8_t reg, uint8_t data);
    uint8_t read_register(uint8_t slaveAddress, uint8_t reg);
    uint8_t read(bool ack);
    void write_block(uint8_t slave_address, uint8_t reg, uint8_t* data, uint8_t size);
    void read_block(uint8_t slave_address, uint8_t reg, uint8_t* data, uint8_t size);
    

    void setBitrate(uint32_t b) {
        bitrate = b;
        init();  // Zainicjuj ponownie po zmianie bitrate
    }

    // Setter dla preskalera
    void setPrescaler(uint8_t p) {
        prescaler = p;
        init();  // Zainicjuj ponownie po zmianie preskalera
    }

    // Setter dla adresu Slave
    void setSlaveAddress(uint8_t address) {
        slaveAddress = address;
        if (!isMaster) {
            TWAR = (slaveAddress << 1);  // Ustaw adres Slave
        }
    }

    // Setter dla trybu Master/Slave
    void setMode(bool master) {
        isMaster = master;
        init();  // Zainicjuj ponownie po zmianie trybu
    }

    uint32_t getBitrate() const {
        return bitrate;
    }

    // Getter dla preskalera
    uint8_t getPrescaler() const {
        return prescaler;
    }

    // Getter dla adresu Slave
    uint8_t getSlaveAddress() const {
        return slaveAddress;
    }

    // Getter dla trybu Master/Slave
    bool getMode() const {
        return isMaster;
    }
};

#endif // I2C_H
