#ifndef _SPIe_H_INCLUDED
#define _SPIe_H_INCLUDED

#include<avr/io.h>


class SPIClass {
    public:
        static void begin(int);
        static uint8_t Master_Transceive(uint8_t); 
        
}
