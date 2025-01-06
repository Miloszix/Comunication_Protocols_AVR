// Communication.h
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <avr/io.h>

class CommunicationProtocol {
public:
    virtual void init() = 0;
    // virtual void start() = 0;
    // virtual void stop() = 0;

    virtual ~CommunicationProtocol() {}
};

#endif // COMMUNICATION_H