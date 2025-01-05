// UART.h
#ifndef UART_H
#define UART_H

#include "CommunicationProtocol.h"

class UART : public CommunicationProtocol {
public:
    void init() override;

};

#endif // UART_H
