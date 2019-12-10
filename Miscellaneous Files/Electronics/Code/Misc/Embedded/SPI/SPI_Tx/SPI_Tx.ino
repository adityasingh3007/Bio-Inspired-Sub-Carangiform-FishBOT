#include<avr/io.h>
#include<avr/interrupt.h>
#include <util/delay.h>

#define ACK 0x7E
 
void SPI_initiallise() {
  DDRB=(1<<5)|(1<<3)|(1<<2);
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

unsigned char SPI_tranceiver(unsigned char data)
{
    PORTB&=~(1<<2);
    SPDR = data;
    while(!(SPSR & (1<<SPIF) )) {
    }
    PORTB|=(1<<2);
    return(SPDR);
}

int main(void) {
  Serial.begin(115200);
  uint8_t x=0;
  unsigned char data;
  SPI_initiallise();
  while(1){
        data = 0x00;                    //Reset ACK in "data"
        data = SPI_tranceiver(++x);     //Send "x", receive ACK in "data"
        if(data == ACK) {               //Check condition
            //If received data is the same as ACK, blink LED "x" number of times
            Serial.println("Data recieved by SLAVE");
        }
        else {
            //If received data is not ACK, then blink LED for a long time so as to determine error
            Serial.println("Data not received by SLAVE");
        }
    _delay_ms(20);
  }
}
/*
#include<SPI.h>                             //Library for SPI 
int x;
void setup (void)

{
  Serial.begin(115200);                   //Starts Serial Communication at Baud Rate 115200 
  SPI.begin();                            //Begins the SPI commnuication
  SPI.setClockDivider(SPI_CLOCK_DIV8);    //Sets clock for SPI communication at 8 (16/8=2Mhz)
  digitalWrite(SS,HIGH);                  // Setting SlaveSelect as HIGH (So master doesnt connnect with slave)
  x=0;
}

void loop(void)
{
  byte Mastersend,Mastereceive;          
  digitalWrite(SS, LOW);                  //Starts communication with Slave connected to master
  
  Mastersend = x;                            
  Mastereceive=SPI.transfer(Mastersend); //Send the mastersend value to slave also receives value from slave
  if(Mastereceive == 1)                   //Logic for setting the LED output depending upon value received from slave
  {
    Serial.println("Master LED ON");
  }
  else
  {
   Serial.println("Master LED OFF");
  }
  delay(100);
  if(x==1) {
    x=0;
  }
  else {
    x=1;
  }
}
*/
