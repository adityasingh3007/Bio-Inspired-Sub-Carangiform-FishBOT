#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define pi 3.14159

#define CE_PIN   9
#define CSN_PIN 10

volatile int timer_counter=0;
bool listen = false;

ISR(TIMER2_COMPA_vect) {
  timer_counter++;
  if(timer_counter>=3){
    listen = true;
    timer_counter=0;
  }
}
Servo s1;
Servo s2;
Servo s3;

RF24 radio(CE_PIN, CSN_PIN);

const byte thisSlaveAddress[5] = {'P', 'I', 'S', 'Y', 'e'};

char dataReceived[3];
int ackData[2] = {100, 100};

int counter = 0;            // Loop counter variable
int frequency = 3 ;          // Oscillation frequency of segments.
float a = 50;               //Amplitude coeff
float b = 1 * pi;           //Curve Coeff
float c = 0;                //Turn Coeff
int num_segments = 3;       //Number of joints
float gamma = -c / num_segments;
float beta = b / num_segments;
float amplitude = a * abs(sin(beta / 2));

float offset_0 = -5;
float offset_1 = 10;
float offset_2 = -3;

int delayTime = 5;          // Delay between limb movements
int startPause = 100;      // Delay time to position robot

bool connected = 0;

void motd() {
  Serial.println("Intialising........");
  delay(100);
  Serial.println("====================================================");
  delay(50);
  Serial.println("      ______ _     _     ____   ____ _______ ");
  delay(50);
  Serial.println("     |  ____(_)   | |   |  _ \\ / __ \\__   __|");
  delay(50);
  Serial.println("     | |__   _ ___| |__ | |_) | |  | | | |  ");
  delay(50);
  Serial.println("     |  __| | / __| \'_ \\|  _ <| |  | | | | ");
  delay(50);
  Serial.println("     | |    | \\__ \\ | | | |_) | |__| | | |  ");
  delay(50);
  Serial.println("     |_|    |_|___/_| |_|____/ \\____/  |_| ");
  delay(50);
  Serial.println("");
  delay(50);
  Serial.println("====================================================");
}

void start_radio_communication() {
  Serial.println("\nIntialsing Radio Module....");
  radio.begin();
  radio.setChannel(127);
  radio.setDataRate( RF24_250KBPS );
  radio.openReadingPipe(1, thisSlaveAddress);
  radio.enableAckPayload();
  radio.startListening();
  radio.writeAckPayload(1, &ackData, sizeof(ackData)); // pre-load data
  Serial.println("DONE.\n");
}

void getData() {
  if ( radio.available() ) {
    radio.read( &dataReceived, sizeof(dataReceived) );
    if (connected) {
      if (dataReceived[0] == 'f' && dataReceived[1] == 'b') {
        ackData[0] = 100;
        ackData[1] = 100;
        connected = 0;
        Serial.println("\n================================");
        Serial.println("    CONNECTION LOST.");
        Serial.println("================================\n");
        Serial.println("Re-connecting....");
      }
    }
    else {
      if (dataReceived[0] == 'f' && dataReceived[1] == 'b') {
        connected = 1;
        Serial.println("\n================================");
        Serial.println("    Succesfully connected.");
        Serial.println("================================\n");
        ackData[0] = 101;
        ackData[1] = 101;
      }
      else {
        Serial.println("Searching for Transmitter..");
      }
    }
    updateReplyData();
  }
}

void updateReplyData() {
  radio.writeAckPayload(1, &ackData, sizeof(ackData)); // load the payload for the next time
}

void  execute_motion() {
  int val;
  if (dataReceived[0] != 'X' && connected) {
    if (dataReceived[0] == 'F') {
      val=int(dataReceived[1])-48;
      frequency = 1 + val;
      switch(val){
        case 0 : a = 60;
                 b = 1.5* pi;
                 break;
        case 1 : a = 60;
                 b = 2* pi;
                 break;
        case 2 : a = 70;
                 b = 2.5* pi;
                 break;
        case 3 : a = 80;
                 b = 3* pi;
                 break;
        case 4 : a = 90;
                 b = 3.5* pi;
                 break;          
      }
      a = 50;
      b = 1* pi;
      c = 0;
    }
    else if (dataReceived[0] == 'L') {
      a = 50;
      b = 1 * pi;
      c = -4 * pi;
    }
    else if (dataReceived[0] == 'R') {
      a = 50;
      b = 1 * pi;
      c = 4 * pi;
    }
      s1.write(90 + offset_0 + amplitude * sin(frequency * counter * pi / 180 + 0 * beta) + gamma);
      s2.write(90 + offset_1 + amplitude * sin(frequency * counter * pi / 180 + 1 * beta + pi / 2) + gamma);
      s3.write(90 + offset_2 + amplitude * sin(frequency * counter * pi / 180 + 2 * beta) + gamma);
      delay(delayTime);
      counter++;
      if(counter>360){
      counter=0;
      }
  }
}

void Timer_init() {
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;
  OCR2A = 255;
  TCCR2A |= (1 << WGM21);
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);   
  TIMSK2 |= (1 << OCIE2A);
}
void setup() {
  Serial.begin(9600);
  cli();
  motd();
  Timer_init();
  start_radio_communication();
  s1.attach(2);
  s2.attach(3);
  s3.attach(4);
  s1.write(90 + offset_0);
  s2.write(90 + offset_1);
  s3.write(90 + offset_2);
  sei();
  delay(startPause);
}

void loop() {
  if(listen){
    getData();
    listen= false;
  }
  execute_motion();
}

