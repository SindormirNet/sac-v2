#ifndef CYSPI_H
#define CYSPI_H

#define READ_OFFSET  0x3F
#define WRITE_OFFSET 0x80
#define BURST_OFFSET 0x40

#include "WProgram.h" //Access to basic arduino IO, functions and datatypes

class CYSPI {
public:
    CYSPI(void);
    ~CYSPI(void);
    
    void config();    
    void init();
    byte read(byte);
    void write(byte,byte);
    byte unsafeRead(byte);
    void unsafeWrite(byte, byte);
    void fileRead(byte, byte, byte *);
    void fileWrite(byte, byte, byte *);
    
    void setSlave(boolean);
    void setClock(boolean);
    
private:
    static const uint8_t SPI_SCK  = 13;	// PORTB,5
    static const uint8_t SPI_MISO = 12; // PORTB,4
    static const uint8_t SPI_MOSI = 11; // PORTB,3
    static const uint8_t SPI_SS   = 10; // PORTB,2
};

extern CYSPI spi;

#endif 
