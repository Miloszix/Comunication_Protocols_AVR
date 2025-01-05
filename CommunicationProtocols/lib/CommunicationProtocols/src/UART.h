// UART.h
#ifndef UART_H
#define UART_H

#include "CommunicationProtocol.h"

class UART : public CommunicationProtocol {
public:
    void init() override;
    void sendData(const char* data, unsigned int length) override;
    void receiveData(char* buffer, unsigned int length) override;
};

#endif // UART_H
