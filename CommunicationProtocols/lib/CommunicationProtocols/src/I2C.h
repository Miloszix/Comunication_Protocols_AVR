// I2C.h
#ifndef I2C_H
#define I2C_H

#include "CommunicationProtocol.h"

class I2C : public CommunicationProtocol {
public:
    void init() override;
    void sendData(const char* data, unsigned int length) override;
    void receiveData(char* buffer, unsigned int length) override;
};

#endif // I2C_H
