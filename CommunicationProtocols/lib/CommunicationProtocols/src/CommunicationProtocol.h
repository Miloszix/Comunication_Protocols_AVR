// Communication.h
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

class CommunicationProtocol {
public:
    virtual void init() = 0;             // Wirtualna metoda inicjalizacji
    virtual void sendData(const char* data, unsigned int length) = 0; // Wirtualna metoda wysyłania danych
    virtual void receiveData(char* buffer, unsigned int length) = 0;  // Wirtualna metoda odbierania danych

    virtual ~CommunicationProtocol() {} // Wirtualny destruktor
};

#endif // COMMUNICATION_H