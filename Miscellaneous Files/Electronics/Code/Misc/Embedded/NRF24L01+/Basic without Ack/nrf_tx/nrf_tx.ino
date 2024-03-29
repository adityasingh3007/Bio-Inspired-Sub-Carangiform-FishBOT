#include<avr/io.h>
#include<util/delay.h>                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
#include "NRF24l01.h"


#define SCK 5
#define MISO 4
#define MOSI 3
#define CSN 2
#define CE  1

#define HIGH 1
#define LOW 0

#define W 1
#define R 0
#define NOP 0xFF

void change_state(int pin, bool state) {
  if (state) {
    PORTB |= (1 << pin);
  }
  else {
    PORTB &= ~(1 << pin);
  }
}

void SPI_init() {
  DDRB |= (1 << SCK) | (1 << MOSI) | (1 << CSN) | (1 << CE);
  SPCR |= (1 << SPE) | (1 << MSTR);
  change_state(CSN, HIGH);
  change_state(CE, LOW);
}

uint8_t SPI_transceive(uint8_t data) {
  SPDR = data;
  while (!((SPSR) & (1 << SPIF)));
  return SPDR;
}

uint8_t *ExecuteCommand(uint8_t ReadWrite, uint8_t reg, uint8_t *val, uint8_t index) {
  if (ReadWrite == W) {
    reg = W_REG | reg;
  }
  else {
    reg = R_REG | reg;
  }

  static uint8_t ret[32];

  _delay_us(10);
  change_state(CSN, LOW);
  _delay_us(10);
  SPI_transceive(reg);
  _delay_us(10);

  int i;
  for (i = 0; i < index; i++) {
    if (ReadWrite == R && reg != TX_PAYLOAD) {
      ret[i] = SPI_transceive(NOP);
      _delay_us(10);
    }
    else {
      SPI_transceive(val[i]);
      _delay_us(10);
    }
  }
  change_state(CSN, HIGH);
  return ret;
}

void reset_(void) {
  uint8_t val[5];
  val[0] = 0x70;
  ExecuteCommand(W, STATUS, val, 1);
}

void Transmit_data(uint8_t *W_buff) {
  uint8_t *data;
  Serial.println("\nTransmitting...");
  ExecuteCommand(R, FLUSH_TX, W_buff, 0);
  ExecuteCommand(R, TX_PAYLOAD, W_buff, 5);
  data= ExecuteCommand(R, FIFO_STATUS, data, 1);
  Serial.println(*data, HEX);
  _delay_ms(10);
  change_state(CE, HIGH);
  _delay_us(20);
  change_state(CE, LOW);
  _delay_ms(10);
  data= ExecuteCommand(R, FIFO_STATUS, data, 1);
  Serial.println(*data, HEX);
  if(*data==0x11){
    Serial.print("Transmission Succesfull  ");
    data=ExecuteCommand(R, RX_PAYLOAD, data, 5);
    Serial.println(*data);
  }
  data= ExecuteCommand(R, STATUS, data, 1);
}

void NRF_init() {
  _delay_ms(100);
  uint8_t addr[5] = {'e', 'Y', 'S', 'I', 'P'};
  uint8_t val[5];
  SPI_init();
  //Resetiing the module
  val[0] = 0x70;
  ExecuteCommand(W, STATUS, val, 1);
  Serial.println("Finding NRF24l01 module.....");
  uint8_t *data;
  data = ExecuteCommand(R, STATUS, data, 1);
  Serial.println(*data, HEX);
  if (*data == 0x0E) {
    Serial.println("\tModule found.....");
    Serial.println("\tConfiguring the module....\n");
  }
  else {
    Serial.println("Module Not Found...");
    Serial.println("Exiting..");
    return;
  }
  Serial.print("\nEnable Auto Ack: ");
  //Enable Auto Ack
  val[0] = 0x01;
  ExecuteCommand(W, EN_AA, val, 1);
  data=ExecuteCommand(R, EN_AA, data, 1);
  Serial.println(*data, HEX);

  Serial.print("\nRetries and Delay: ");
  //Set retries and delay
  val[0] = 0x2F;
  ExecuteCommand(W, SETUP_RETR, val, 1);
  data=ExecuteCommand(R, SETUP_RETR, data, 1);
  Serial.println(*data, HEX);

  Serial.print("\nNo of pipes: ");
  //Chosse number of enabled pipes
  val[0] = 0x01;
  ExecuteCommand(W, EN_RXADDR, val, 1);
  data=ExecuteCommand(R, EN_RXADDR, data, 1);
  Serial.println(*data, HEX);

  Serial.print("\nRf addr width: ");
  //RF_Address widh setup
  val[0] = 0x03;
  ExecuteCommand(W, SETUP_AW, val, 1);
  data=ExecuteCommand(R, SETUP_AW, data, 1);
  Serial.println(*data, HEX);

  Serial.print("\nRF channel: ");
  //RF Channel setup
  val[0] = 0x01;
  ExecuteCommand(W, RF_CH, val, 1);
  data=ExecuteCommand(R, RF_CH, data, 1);
  Serial.println(*data, HEX);

  Serial.print("\nRF setup: ");
  //RF setup
  val[0] = 0x26;
  ExecuteCommand(W, RF_SETUP, val, 1);
  data=ExecuteCommand(R, RF_SETUP, data, 1);
  Serial.println(*data, HEX);

  //RX RF_Address setup
  ExecuteCommand(W, RX_ADDR_P0, addr, 5);

  //Tx RF_Address setup
  ExecuteCommand(W, TX_ADDR, addr, 5);

  Serial.print("\npayload width: ");
  //Payload widdth setup
  val[0] = 5;
  ExecuteCommand(W, RX_PW_P0, val, 1);
  data=ExecuteCommand(R, RX_PW_P0, data, 1);
  Serial.println(*data, HEX);

  Serial.print("\nCONFIG: ");
  //CONFIG REG setup
  val[0] = 0x3E;
  ExecuteCommand(W, CONFIG, val, 1);
  data=ExecuteCommand(R, CONFIG, data, 1);
  Serial.println(*data, HEX);

  _delay_ms(100);
}

int main(void) {
  Serial.begin(9600);
  NRF_init();
  int i = 1;
  uint8_t W_buffer[5];
  for(i=0;i<5;i++){
    W_buffer[i]=0x80;
  }
  i=0;
  while (1) {
    Transmit_data(W_buffer);
    _delay_ms(130);
    reset_();
    /*
    Serial.print("aw");
    if(i<40){
      Serial.print("a");
    }
    else {
      break;
    }
    i++;*/
  }
  return 0;
}

