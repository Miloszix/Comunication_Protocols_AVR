// Communication.h
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <avr/io.h>

class CommunicationProtocol {
public:
    virtual void init() = 0;             // Wirtualna metoda inicjalizacji
    virtual void start() = 0;
    virtual void stop() = 0;

    virtual ~CommunicationProtocol() {} // Wirtualny destruktor
};

#endif // COMMUNICATION_H