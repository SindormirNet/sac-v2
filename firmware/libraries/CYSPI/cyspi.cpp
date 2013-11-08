#include "cyspi.h"

CYSPI::CYSPI() {

}

CYSPI::~CYSPI() {

}

void CYSPI::config() {
  pinMode(SPI_MOSI,      OUTPUT);
  pinMode(SPI_MISO,      INPUT);
  pinMode(SPI_SCK,       OUTPUT);
  pinMode(SPI_SS,        OUTPUT);  
}

void CYSPI::init() {
  byte garbage;

  //digitalWrite(SPI_SS,HIGH); 
  PORTB |= B00000100;	     //Disable module
  delay(6);                  //Needed for the cywm6935 module to work

  //Max clock for CYWM6935 = 2Mhz
  SPCR = ( (0<<SPIE) | (1<<SPE) | (0<<DORD) | (1<<MSTR)| (0<<CPOL)| (1<<CPHA)| (0<<SPR1) | (1<<SPR0)); //Don't change this

  garbage = SPSR;  //Clear status register
  garbage = SPDR;  //Clear data register
}


byte CYSPI::unsafeRead(byte reg) {
  byte reply;

  //digitalWrite(SPI_SS,LOW);
  PORTB &= B11111011;

  SPDR = reg & READ_OFFSET;
  while (!(SPSR & (1 << SPIF)));
  SPDR = 0x00;
  while (!(SPSR & (1 << SPIF)));
  reply = SPDR;
  //digitalWrite(SPI_SS,HIGH);
  PORTB |= B00000100;
  return reply;
}

byte CYSPI::read(byte reg) {
  byte reply;
  byte reply2;

  //digitalWrite(SPI_SS,LOW);
  PORTB &= B11111011;

  SPDR = reg & READ_OFFSET;
  while (!(SPSR & (1 << SPIF)));
  SPDR = 0x00;
  while (!(SPSR & (1 << SPIF)));
  reply = SPDR;
  //digitalWrite(SPI_SS,HIGH);
  PORTB |= B00000100;
  delayMicroseconds(1);

  //digitalWrite(SPI_SS,LOW);
  PORTB &= B11111011;

  SPDR = reg & READ_OFFSET;
  while (!(SPSR & (1 << SPIF)));
  SPDR = 0x00;
  while (!(SPSR & (1 << SPIF)));
  reply2 = SPDR;
  //digitalWrite(SPI_SS,HIGH);  
  PORTB |= B00000100;

  if (reply!=reply2) reply=spi.read(reg);
  return reply;
}

void CYSPI::unsafeWrite(byte reg, byte msg) {
  //digitalWrite(SPI_SS,LOW);
  PORTB &= B11111011;
  

  SPDR = reg | WRITE_OFFSET;
  while (!(SPSR & (1 << SPIF)));

  SPDR = msg;
  while (!(SPSR & (1 << SPIF)));

  //digitalWrite(SPI_SS,HIGH);
  PORTB |= B00000100;

}

void CYSPI::write(byte reg, byte msg) {
  byte read_data;

  do {    
    spi.unsafeWrite(reg,msg);
    read_data = spi.read(reg);
  } 
  while (read_data != msg);
}

void CYSPI::fileRead(byte reg, byte len, byte *dest) {
  byte i;
  //digitalWrite(SPI_SS,LOW);
  PORTB &= B11111011;

  SPDR = reg & READ_OFFSET | BURST_OFFSET; 
  while (!(SPSR & (1 << SPIF)));
  for (i=0; i<len; i++, dest++) {
    SPDR = 0x00;
    while (!(SPSR & (1 << SPIF)));
    *(byte *)dest = SPDR;
  }
  //digitalWrite(SPI_SS,HIGH);
  PORTB |= B00000100;
}

void CYSPI::fileWrite(byte reg, byte len, byte *src) {
  byte i;
  byte data;

  //digitalWrite(SPI_SS,LOW);
  PORTB &= B11111011;

  SPDR = reg | WRITE_OFFSET | BURST_OFFSET; 
  while (!(SPSR & (1 << SPIF)));
  for (i=0; i<len; i++, src++) {
    data= *(byte *)src;
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));
  }
  //digitalWrite(SPI_SS,HIGH);
  PORTB |= B00000100;
} 

void CYSPI::setSlave(boolean status) {
  if (status)
    PORTB |= B00000100;
  else
    PORTB &= B11111011;
}

void CYSPI::setClock(boolean status) {
  if (status)
    PORTB |= B00100000;
  else
    PORTB &= B11011111;
}


/*
    static const uint8_t SPI_SCK  = 13; // PORTB,5
    static const uint8_t SPI_MISO = 12; // PORTB,4
    static const uint8_t SPI_MOSI = 11; // PORTB,3
    static const uint8_t SPI_SS   = 10; // PORTB,2

//SS
PORTB |= B00000100;
PORTB &= B11111011;

//MOSI
PORTB |= B00001000;
PORTB &= B11110111;

//MISO
PORTB |= B00010000;
PORTB &= B11101111;

//SCK
PORTB |= B00100000;
PORTB &= B11011111;

*/
