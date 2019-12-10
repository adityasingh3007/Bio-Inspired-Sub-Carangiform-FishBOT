/*
  ▪ Project Name: Bio-Inspired Sub-Carangiform FishBOT
  ▪ Team Name: Aditya Kumar Singh, Bhavy Shah
  ▪ Author List: Aditya Kumar Singh
  ▪ Filename: Remote_Control.ino
  ▪ Functions: motd(), start_radio_communication(), controller_initialisation(), prepare_data(int, int), get_controller_data(),
               send(), setup(), loop()
  ▪ Global Variables: slaveAddress[5], dataToSend[3], ackData[2], currentMillis, prevMillis, txIntervalMillis, control_x, 
                      control_y, dir_x, dir_y, connected, led_state
*/

/*
   Including necessary library files.
*/
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

RF24 radio(CE_PIN, CSN_PIN);                                    //Creating radio object to handle radio comuunication using NRF24L01

const byte slaveAddress[5] = {'P', 'I', 'S', 'Y', 'e'};         //Slave address to which this code will communicate.

char dataToSend[3] = "X0";                                      //Data which will be sent.
int ackData[2] = { -1, -1};                                     //Variable to store the acknowledged data. 

unsigned long currentMillis;                                    //To store the current time (in ms)
unsigned long prevMillis;                                       //History time(in ms)
unsigned long txIntervalMillis = 100;                           //Interval gap(in ms) after which message will be sent to receiver.

int control_x, control_y, dir_x, dir_y;                         //Variables to store the data from the two Joysticks.

bool connected = 0;                                             // Flag variable to check whether Transmitter found any suitable receiver or not.
bool led_state = 1;                                             // Flag variable to toggle the on board LED. 

/*
  ▪ Function Name: motd
  ▪ Input: None
  ▪ Output: None
  ▪ Logic: This function just prints the message of the day on the Serial line.
  ▪ Example Call: motd()
*/
void motd() {                                                   //Message of the Day
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


/*
  ▪ Function Name: start_radio_communication
  ▪ Input: None
  ▪ Output: None
  ▪ Logic: This function configures the NRF24L01 and starts the communication.
  ▪ Example Call: start_radio_communication() 
*/
void start_radio_communication() {
  Serial.println("\nIntialsing Radio Module....");
  radio.begin();                                    //Initiallising the module
  radio.setChannel(127);                            //Channel frequency to 
  radio.setDataRate( RF24_250KBPS );                //Data rate to 250Kbps
  radio.enableAckPayload();                         //Enabling auto acknowledge mode.
  radio.setRetries(3, 5);                           //Setting retries if Tx fails.
  radio.openWritingPipe(slaveAddress);              //Givng the slave addres to which it will communicate.
  Serial.println("DONE.\n");
}

/*
  ▪ Function Name: controller_initialisation
  ▪ Input: None
  ▪ Output: None
  ▪ Logic: This function sets the microcontroller in order the read data from the Joystick modules.
  ▪ Example Call: controller_initialisation()
*/
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

/*
  ▪ Function Name: prepare_data
  ▪ Input: int x -> This variable accepts the x-axis values of the Joystick 1.(Used to decide Forward/Backward)
           int y -> This variable accepts the y-axis values of the Joystick 2.(Used to decide Left/Right)
  ▪ Output: None
  ▪ Logic: This function preapres as what signal is to be send to receiver after processing the data from the Joysticks.
           There can be 4 signals for (Forward, Backward, Left, Right). In case of "Forward" the degree to which the Joystick 
           is bend, the more speed will be passed. This is controlled via the number after the main character as in 0 in 'F0'.
  ▪ Example Call: prepare_data(504, 409)
*/
void prepare_data(int x, int y) {
  char val;                                                         //Stores the maped the value from the 510 to 1024 into 0-5(0 inclusive)
  //Serial.print(x);Serial.print('\t');Serial.println(y);
  /*
    Decides the signal to be send based on the values returned from both the Joystick modules.
  */
  if (y > 500 && y < 510) {
    if (x > 500 && x < 510) {
      //Serial.println("Stable");
      dataToSend[0] = 'X';
      dataToSend[1] = '0';
    }
    else if (x >= 510) {
      //Serial.println("Forward");
      val=48+map(x,510,1024,0,5);                                  //The more Joystick is bend means more speed.
      //Serial.println(val);
      dataToSend[0] = 'F';
      dataToSend[1] = val;
    }
    else if (x <= 490) {
      //Serial.println("Backward");
      dataToSend[0] = 'B';
      dataToSend[1] = '3';
    }
  }
  else if (y >= 510) {
    //Serial.println("Right");
    val=48+map(y,510,1024,0,5);                                  //The more Joystick is bend means more speed.
    dataToSend[0] = 'R';
    dataToSend[1] = val;
  }
  else if (y <= 495) {
    //Serial.println("Left");
    val=48+map(y,495,0,0,5);                                  //The more Joystick is bend means more speed.
    dataToSend[0] = 'L';
    dataToSend[1] = val;
  }
}

/*
  ▪ Function Name: get_controller_data
  ▪ Input: None
  ▪ Output: None
  ▪ Logic: This function gets the data from the Joystick using analogRead().
  ▪ Example Call: get_controller_data()
*/
void get_controller_data() {
  dir_x = analogRead(DIR_X);              //Forward and backward motion control in Joystick 1
  control_y = analogRead(CONTROL_Y);      //Left and right control in Joystick 2
  prepare_data(dir_x, control_y);         //Process the data obtained.
}

/*
  ▪ Function Name: send
  ▪ Input: None
  ▪ Output: None
  ▪ Logic: This function sends the data to receiver and waits for the acknowledgement.
           According to the cases, LEDs are glown to show to user for succesfull transmission or failure.
  ▪ Example Call: send()
*/
void send() {
  bool rslt;                                                      //Flag variable to check whether data was Transmitted or not
  rslt = radio.write( &dataToSend, sizeof(dataToSend) );          //Sending the data
  Serial.print("Data Sent :- ");
  Serial.println(dataToSend);
  if (rslt) {                                                     //If sucessfully sent
    if ( radio.isAckPayloadAvailable() ) {                        //If acknowlege us received.
      radio.read(&ackData, sizeof(ackData));
      if (ackData[0] == 101 && ackData[1] == 101) {               //Glow green light.
        digitalWrite(RED, HIGH);
        digitalWrite(BLUE, HIGH);
        digitalWrite(GREEN, LOW);
      }
      else {                                                      //If acknowledged message is not 101, that ,eans connection is lost. Re-connect.
        Serial.println("\n================================");
        Serial.println("    CONNECTION LOST.");
        Serial.println("================================\n");
        Serial.println("Re-connecting....");
        connected = 0;
      }
    }
    else {                                                        //If acknowledge was received without any data, glow Blue light.
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, LOW);
      Serial.println("  Acknowledge but no data ");
    }
  } 
  else {                                                          //If Tx fails, glow Red light.
    digitalWrite(BLUE, HIGH);
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    Serial.println("  Tx failed");
  }
  prevMillis = millis();                                          //Store the time at which Tx was completed.
}

/*
  ▪ Function Name: setup
  ▪ Input: None
  ▪ Output: None
  ▪ Logic: This function setups the whole harwadre and starts the Serial communication. 
           This is automatically called from main().
  ▪ Example Call: setup()
*/
void setup() {
  Serial.begin(9600);                                             //Starting Serial communication
  motd();                                                         //Display message of the day
  controller_initialisation();                                    //Initiallises controller
  start_radio_communication();                                    //Configure NRF24L01 for communication.
}

/*
  ▪ Function Name: loop
  ▪ Input: None
  ▪ Output: None
  ▪ Logic: This function is automatically called from while(1) loop from main(). 
           It continously gets the data from the controller and then sends it to receiver.
  ▪ Example Call: loop()
*/
void loop() {
  if (connected) {                                                        //If connection is there
    currentMillis = millis();                                             //get the current time
    if (currentMillis - prevMillis >= txIntervalMillis) {                 //If the time since last data was sent goes above beyond the specifed timeGap, then again get the data and send it  
      get_controller_data();
      send();
    }
  }
  else {                                                                  //If connection is not there
    bool rslt;                                                            //Variable to flag the Tx success during establishing connection
    bool loop = 1;                                                        //Loop variable to make the loop run continously
    //Data to send "fb" to try connecting to a receiver
    dataToSend[0] = 'f';
    dataToSend[1] = 'b';
    digitalWrite(RED, LOW);                                               //Glow the RED led to show connection is not established yet
    Serial.println("Searching for BOT....");
    while (loop) {
      //Toggle the RED LED untill the communication is established.
      if (led_state) {
        digitalWrite(RED, HIGH);
        led_state = 0;
      }
      else {
        digitalWrite(RED, LOW);
        led_state = 1;
      }
      //Try connecting here
      rslt = radio.write( &dataToSend, sizeof(dataToSend) ); 
      if (rslt) {
        if ( radio.isAckPayloadAvailable() ) {
          radio.read(&ackData, sizeof(ackData));
          if (ackData[0] == 100 && ackData[1] == 100) {                        //If this acknowledged is received, then the connection is done.
            loop = 0;
            connected = 1;
            dataToSend[0] = 'X';
            dataToSend[1] = '0';
            Serial.println("\n================================");
            Serial.println("    Succesfully connected.");
            Serial.println("================================\n");
            digitalWrite(RED, HIGH);                                           //Turn off RED LED.
            digitalWrite(GREEN, LOW);                                          //Glow GREEN LED to show connection success.
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
