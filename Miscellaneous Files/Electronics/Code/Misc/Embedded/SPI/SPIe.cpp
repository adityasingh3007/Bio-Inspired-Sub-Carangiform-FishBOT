#include "SPI.h"
#include<String.h>

#define SS PB2
#define MOSI PB3
#define MISO PB4
#define SCK PB5

#define MASTER 1
#define SLAVE 0

SPIClass SPI;

void SPIClass::begin(int mode) {
    SPCR|=(1<<SPE);
    if(mode) {                              //Master Mode
        DDRB|=(1<<SCK)|(1<<MOSI)|(1<<SS);
        SPCR|=(1<<MSTR)|(1<<SPR0);
    }
    else {
        //No extra initiallisation required in SLAVE mode for SPCR register
        DDRB=(1<<MISO);   
    }
}

void SPIClass::Master_Transceive(uint8_t data) {
    PORTB&=~(1<<SS);
    SPDR = data;
    while(!(SPSR & (1<<SPIF) )) {
    }
    PORTB|=(1<<SS);
    return(SPDR);
} 