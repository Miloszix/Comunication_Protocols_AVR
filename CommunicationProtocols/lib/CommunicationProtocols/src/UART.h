#ifndef UART_H
#define UART_H

#include "CommunicationProtocol.h"

class UART : public CommunicationProtocol {
private:
    uint32_t usart_speed; 
    uint8_t usart_number;  

public:
    UART(uint8_t usart_number = 0, uint32_t speed = 9600);

    void init() override;
    void transmitByte(uint8_t data);
    uint8_t receiveByte();
    void transmitString(const char* str);
    void receiveString(char* buffer, uint8_t maxLength);

    void operator delete(void*) {
    // Empty operator becouse there was an error involving delete
    }
};



#endif // UART_H