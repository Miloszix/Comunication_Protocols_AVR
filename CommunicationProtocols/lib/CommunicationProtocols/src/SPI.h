// SPI.h
#ifndef SPI_H
#define SPI_H

#include "CommunicationProtocol.h"

class SPI : public CommunicationProtocol {
public:
    void init() override;                     // Implementacja inicjalizacji
};

#endif // SPI_H
