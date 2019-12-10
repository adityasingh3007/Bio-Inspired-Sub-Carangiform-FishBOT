#include<avr/io.h>
#include<util/delay.h>
#include<util/twi.h>

uint8_t MPU_addr = 0x68;

#define TW_STATUS_MASK_    (_BV(TWS7)|_BV(TWS6)|_BV(TWS5)|_BV(TWS4)|_BV(TWS3))
        
#define TW_STATUS_   (TWSR & TW_STATUS_MASK_)

void i2c_init() {
  TWSR = 0;
  TWBR = 0x48;
  TWCR = (1<<TWEN)|(1<<TWEA)|(1<<TWINT);
}

void i2c_start() {
   TWCR =(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  while ((TWCR & (1<<TWINT)) == 0);
}

void i2c_stop() {
  TWCR = (1<<TWSTO)|(1<<TWEN)|(1<<TWINT);
}

void i2c_write(unsigned char data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
}

uint8_t i2c_read(unsigned char isLast) {
  if (isLast == 0) {
    TWCR = (1<<TWEN)|(1<<TWEA)|(1<<TWINT);
  }
  else {
    TWCR = (1<<TWEN)|(1<<TWINT);
  }
  while ((TWCR & (1<<TWINT)) == 0);
  return TWDR;
}

int main() {
  Serial.begin(9600);
  i2c_init();
  i2c_start();
  i2c_write(((MPU_addr <<1)| TW_WRITE));
  i2c_write(0x6B);
  i2c_write(0x00);
  i2c_stop();
  
  _delay_ms(200);
  Serial.println(" ");
  uint16_t x,y;
  int X,Y;
  while (1) {
    i2c_start();
  i2c_write(((MPU_addr <<1)| TW_WRITE));
  i2c_write(0x3B);
  i2c_start();
  i2c_write(((MPU_addr <<1)| TW_READ));
  x=(i2c_read(0)<<8)|i2c_read(0);
  y=(i2c_read(0)<<8)|i2c_read(1);
  i2c_stop();
  X=x/1000;
  Y=y/1000;
  if(X>32) {
    X=X-66;
  }
  if(Y>32) {
    Y=Y-66;
  }
  Serial.print("AcX= ");Serial.print(X);Serial.print('\t');
  Serial.print("AcY= ");Serial.println(Y);
  }
}

