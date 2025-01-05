// I2C.cpp
#include "I2C.h"
#include <avr/io.h>

#define TWBR_VALUE 72  // Wartość TWBR dla żądanej prędkości (100 kHz przy F_CPU = 16 MHz)

void I2C::init() {
    // Ustawienie preskalera TWI
    TWSR = 0x00;  // Brak preskalera (preskaler = 1)

    // Ustawienie wartości TWBR (TWI Bit Rate Register)
    TWBR = TWBR_VALUE;

    // Włączenie TWI (Two-Wire Interface)
    TWCR = (1 << TWEN);  // Włącz TWI i pozwól na generowanie przerwań
}

// Funkcja do wysyłania danych przez I2C
void I2C::start() {
    // Ustawienie bitu TWINT w TWCR, aby rozpocząć transmisję
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    // Czekaj, aż bit TWINT będzie ustawiony
    while (!(TWCR & (1 << TWINT)));
}

// Funkcja do wysyłania bajtu przez I2C
void I2C::write(uint8_t data) {
    TWDR = data;  // Załaduj dane do rejestru TWI Data Register
    TWCR = (1 << TWINT) | (1 << TWEN);  // Rozpocznij transmisję
    
    // Czekaj, aż transmisja zostanie zakończona
    while (!(TWCR & (1 << TWINT)));
}

// Funkcja do zakończenia transmisji I2C
void I2C::stop() {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);  // Ustaw bit TWSTO i TWINT, aby zakończyć transmisję
    while (TWCR & (1 << TWSTO));  // Czekaj na zakończenie transmisji
}


// Funkcja do zapisu pojedynczego rejestru w urządzeniu I2C
void I2C::write_register(uint8_t slave_address, uint8_t reg, uint8_t data) {
    I2C::start();
    
    // Wysłanie adresu urządzenia I2C (z ustawionym bitem zapisu - 0)
    I2C::write(slave_address << 1);
    
    // Wysłanie adresu rejestru
    I2C::write(reg);
    
    // Wysłanie danych do rejestru
    I2C::write(data);
    
    I2C::stop();
}

// Funkcja do odczytu pojedynczego rejestru z urządzenia I2C
uint8_t I2C::read_register(uint8_t slave_address, uint8_t reg) {
    uint8_t data;
    
    I2C::start();
    
    // Wysłanie adresu urządzenia I2C (z ustawionym bitem zapisu - 0)
    I2C::write(slave_address << 1);
    
    // Wysłanie adresu rejestru
    I2C::write(reg);
    
    I2C::start();  // Ponowne wystartowanie transmisji dla odczytu
    
    // Wysłanie adresu urządzenia I2C (z ustawionym bitem odczytu - 1)
    I2C::write((slave_address << 1) | 1);
    
    // Odczyt danych z urządzenia I2C
    data = I2C::read(false);  // Odczyt bez ustawiania ACK (koniec transmisji)
    
    I2C::stop();
    
    return data;
}

// Funkcja do odbierania danych (w trybie Master)
uint8_t I2C::read(bool ack) {
    TWCR = (1 << TWINT) | (ack ? (1 << TWEA) : 0) | (1 << TWEN);  // Ustawienie ACK lub NACK
    while (!(TWCR & (1 << TWINT)));  // Czekaj na zakończenie
    return TWDR;  // Zwróć odebrane dane
}
// Funkcja do zapisu bloku danych do urządzenia I2C
void I2C::write_block(uint8_t slave_address, uint8_t reg, uint8_t* data, uint8_t size) {
    I2C::start();
    
    // Wysłanie adresu urządzenia I2C (z ustawionym bitem zapisu - 0)
    I2C::write(slave_address << 1);
    
    // Wysłanie adresu rejestru
    I2C::write(reg);
    
    // Wysłanie danych (blok)
    for (uint8_t i = 0; i < size; i++) {
        I2C::write(data[i]);
    }
    
    I2C::stop();
}

// Funkcja do odczytu bloku danych z urządzenia I2C
void I2C::read_block(uint8_t slave_address, uint8_t reg, uint8_t* data, uint8_t size) {
    I2C::start();
    
    // Wysłanie adresu urządzenia I2C (z ustawionym bitem zapisu - 0)
    I2C::write(slave_address << 1);
    
    // Wysłanie adresu rejestru
    I2C::write(reg);
    
    I2C::start();  // Ponowne wystartowanie transmisji dla odczytu
    
    // Wysłanie adresu urządzenia I2C (z ustawionym bitem odczytu - 1)
    I2C::write((slave_address << 1) | 1);
    
    // Odczyt danych z urządzenia I2C (blok danych)
    for (uint8_t i = 0; i < size - 1; i++) {
        data[i] = I2C::read(true);  // Odczyt z ACK dla każdego bajtu
    }
    data[size - 1] = I2C::read(false);  // Odczyt z NACK dla ostatniego bajtu
    
    I2C::stop();
}