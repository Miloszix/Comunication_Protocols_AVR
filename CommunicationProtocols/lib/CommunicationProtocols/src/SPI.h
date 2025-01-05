// SPI.h
#ifndef SPI_H
#define SPI_H

#include "CommunicationProtocol.h"

class SPI : public CommunicationProtocol {
public:
    void init() override;                     // Implementacja inicjalizacji
    void sendData(const char* data, unsigned int length) override;
    void receiveData(char* buffer, unsigned int length) override;
};

#endif // SPI_H
