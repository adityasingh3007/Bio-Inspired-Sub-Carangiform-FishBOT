#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

#define DIR_X A0
#define DIR_Y A1
#define DIR_SW 2

#define CONTROL_X A2
#define CONTROL_Y A3
#define CONTROL_SW 3

#define RED 4
#define GREEN 5
#define BLUE 6

RF24 radio(CE_PIN, CSN_PIN);

const byte slaveAddress[5] = {'P', 'I', 'S', 'Y', 'e'};

char dataToSend[3] = "X0";
int ackData[2] = { -1, -1};

unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 100;

int control_x, control_y, dir_x, dir_y;

bool connected = 0;
bool led_state = 1;

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
  radio.enableAckPayload();
  radio.setRetries(3, 5);
  radio.openWritingPipe(slaveAddress);
  Serial.println("DONE.\n");
}

void controller_initialisation() {
  Serial.println("\nIntialsing Controller....");
  pinMode(CONTROL_X, INPUT);
  pinMode(CONTROL_Y, INPUT);
  pinMode(CONTROL_SW, INPUT);
  pinMode(DIR_X, INPUT);
  pinMode(DIR_Y, INPUT);
  pinMode(DIR_SW, INPUT);

  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, HIGH);

  Serial.println("DONE.\n");
}

void prepare_data(int x, int y) {
  char val;
  //Serial.print(x);Serial.print('\t');Serial.println(y);
  if (y > 500 && y < 510) {
    if (x > 500 && x < 510) {
      //Serial.println("Stable");
      dataToSend[0] = 'X';
      dataToSend[1] = '0';
    }
    else if (x >= 510) {
      //Serial.println("Forward");
      val=48+map(x,510,1024,0,5);
      Serial.println(val);
      dataToSend[0] = 'F';
      dataToSend[1] = val;
    }
    else if (x <= 500) {
      //Serial.println("Backward");
      dataToSend[0] = 'B';
    }
  }
  else if (y >= 510) {
    //Serial.println("Right");
    dataToSend[0] = 'R';
  }
  else if (y <= 500) {
    //Serial.println("Left");
    dataToSend[0] = 'L';
  }
}

void get_controller_data() {
  dir_x = analogRead(DIR_X);              //Forward and backward motion control
  control_y = analogRead(CONTROL_Y);      //Left and right control
  prepare_data(dir_x, control_y);
}

void send() {
  bool rslt;
  rslt = radio.write( &dataToSend, sizeof(dataToSend) );
  Serial.print("Data Sent :- ");
  Serial.println(dataToSend);
  if (rslt) {
    if ( radio.isAckPayloadAvailable() ) {
      radio.read(&ackData, sizeof(ackData));
      if (ackData[0] == 101 && ackData[1] == 101) {
        digitalWrite(RED, HIGH);
        digitalWrite(BLUE, HIGH);
        digitalWrite(GREEN, LOW);
      }
      else {
        Serial.println("\n================================");
        Serial.println("    CONNECTION LOST.");
        Serial.println("================================\n");
        Serial.println("Re-connecting....");
        connected = 0;
      }
    }
    else {
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, LOW);
      Serial.println("  Acknowledge but no data ");
    }
  }
  else {
    digitalWrite(BLUE, HIGH);
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    Serial.println("  Tx failed");
  }
  prevMillis = millis();
}


void setup() {
  Serial.begin(9600);
  motd();
  controller_initialisation();
  start_radio_communication();
}

void loop() {
  if (connected) {
    currentMillis = millis();
    if (currentMillis - prevMillis >= txIntervalMillis) {
      get_controller_data();
      send();
    }
  }
  else {
    bool rslt;
    bool loop = 1;
    dataToSend[0] = 'f';
    dataToSend[1] = 'b';
    digitalWrite(RED, LOW);
    Serial.println("Searching for BOT....");
    while (loop) {
      if (led_state) {
        digitalWrite(RED, HIGH);
        led_state = 0;
      }
      else {
        digitalWrite(RED, LOW);
        led_state = 1;
      }
      rslt = radio.write( &dataToSend, sizeof(dataToSend) );
      if (rslt) {
        if ( radio.isAckPayloadAvailable() ) {
          radio.read(&ackData, sizeof(ackData));
          if (ackData[0] == 100 && ackData[1] == 100) {
            loop = 0;
            connected = 1;
            dataToSend[0] = 'X';
            dataToSend[1] = '0';
            Serial.println("\n================================");
            Serial.println("    Succesfully connected.");
            Serial.println("================================\n");
            digitalWrite(RED, HIGH);
            digitalWrite(GREEN, LOW);
          }
        }
        else {
          Serial.println("FishBOT of same kind found but can't establish communication.");
        }
      }
      else {
        Serial.println("Error communicating with the BOT, Retrying..");
      }
      delay(100);
    }
  }
}
