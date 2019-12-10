#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define ACK 0x7E
unsigned char x;
bool received=false;
void spi_init_slave (void)
{
    DDRB=(1<<4);                               
    SPCR=(1<<SPE)|(1<<SPIE);                               //Enable SPI
}

ISR(SPI_STC_vect)                        //Inerrrput routine function 
{
  x = SPDR;         // Value received from master if store in variable slavereceived
  received = true;                        //Sets received as True 
}
 
int main(void)
{
    Serial.begin(115200);
    sei();
    spi_init_slave();   
    while(1)
    {
       if(received) {
          Serial.println(x);
          SPDR=ACK;
          received=false;
       }
        _delay_ms(20);                            //Wait
    }
}

/*
#include<SPI.h>

volatile boolean received;
volatile byte Slavereceived,Slavesend;

int x;
int m;
void setup()
{
  Serial.begin(115200);
  pinMode(MISO,OUTPUT);                   //Sets MISO as OUTPUT (Have to Send data to Master IN 

  SPCR |= _BV(SPE);                       //Turn on SPI in Slave Mode
  received = false;
  SPI.attachInterrupt();                  //Interuupt ON is set for SPI commnucation
}

ISR (SPI_STC_vect)                        //Inerrrput routine function 
{
  Slavereceived = SPDR;         // Value received from master if store in variable slavereceived
  received = true;                        //Sets received as True 
  x=1;

}

void loop()
{ if(received)                            //Logic to SET LED ON OR OFF depending upon the value recerived from master
   {
      if (Slavereceived==1) 
      {
        Serial.println("Slave LED ON");
      }
      else
      {
        Serial.println("Slave LED OFF");
      }
      
  Slavesend=m;                             
  SPDR = Slavesend;                           //Sends the x value to master via SPDR 
  delay(100);
  if(m==1) {
    m=0;
  }
  else {
    m=1;
  }
}
}
*/
