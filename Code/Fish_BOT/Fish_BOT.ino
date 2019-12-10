/*
  ▪ Project Name: Bio-Inspired Sub-Carangiform FishBOT
  ▪ Team Name: Aditya Kumar Singh, Bhavy Shah
  ▪ Author List: Aditya Kumar Singh
  ▪ Filename: Fish_BOT.ino
  ▪ Functions: motd(), start_radio_communication(), get_Data(), updateReplyData(), get_controller_data(), execute_motion(),
               Timer_init(), setup(), loop()
  ▪ Global Variables: timer_counter, listen, thisSlaveAddress[5], dataReceived[3], ackData[2],counter, frequency, a, b, c, num_segments,
                      gamma, beta, amplitude, offset_0, offset_1, offset_2, delayTimeovements, startPause, connected
*/

/*
   Including necessary library files.
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define pi 3.14159

#define CE_PIN   9
#define CSN_PIN 10

volatile int timer_counter=0;                                            //Variable to count then number of times TIMER2_COMPA occurs.
bool listen = false;                                                     //Flag variable to make the BOT listen to remote signals

/*
  ▪ Function Name: ISR(TIMER2_COMPA_vect)
  ▪ Input: None
  ▪ Output: None
  ▪ Logic: This interrupt routine is called whenever Timer 2 counter matches OCR2A. Listen variable makes the BOT to listen to signal.
           So, for every 3 times matches occur, the BOT will isten to signal and then process it.
  ▪ Example Call: Called automatically.
*/
ISR(TIMER2_COMPA_vect) {
  timer_counter++;              
  if(timer_counter>=3){
    listen = true;
    timer_counter=0;                                                     //Reset back to 0
  }
}

/*
 Creating servo objects 
*/ 
Servo s1;                                                               //Handles mid body servo
Servo s2;                                                               //Handles posteriror body servo
Servo s3;                                                               //Handles caudal fin servo

RF24 radio(CE_PIN, CSN_PIN);                                            //Creating radio object to handle radio comuunication using NRF24L01

const byte thisSlaveAddress[5] = {'P', 'I', 'S', 'Y', 'e'};             //Slave address in which the BOT will listen.

char dataReceived[3];                                                   //Variable to store the data which will come from Transmitter.
int ackData[2] = {100, 100};                                            //Data which will be acknowledged back once a data is received.

/*
  SERPENTINE MOTION 
*/
int counter = 0;                                                        // Loop counter variable (will go from 0 to 360)
int frequency = 3 ;                                                     // Variable to control freqeuncy of the oscilation of the joints
float a = 50;                                                           //Amplitude coeffecient of the motion
float b = 1 * pi;                                                       //Curve Coeffecient of the motion
float c = 0;                                                            //Turn Coeffecient of the motion
int num_segments = 3;                                                   //Number of joints (in our BOT its 3)

float gamma = -c / num_segments;                                        //Turn according to turn coeffecient
float beta = b / num_segments;                                          //Curve ccording to Curve coeffecient.
float amplitude = a * abs(sin(beta / 2));                               //Amplitude of the motion using Amplitude coeffecient.

/*
  Offset angles for respective servo joint
 */
float offset_0 = -5;                                                    
float offset_1 = 10; 
float offset_2 = -3;

int delayTime = 5;                                                     // Delay between limb movements
int startPause = 100;                                                  // Delay time to position robot once the robot is powered

bool connected = 0;                                                    //Flag variable to check the connectivity status

/*
  ▪ Function Name: motd
  ▪ Input: None
  ▪ Output: None
  ▪ Logic: This function just prints the message of the day on the Serial line.
  ▪ Example Call: motd()
*/
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

/*
  ▪ Function Name: start_radio_communication
  ▪ Input: None
  ▪ Output: None
  ▪ Logic: This function configures the NRF24L01 and starts the communication in Reciever mode.
  ▪ Example Call: start_radio_communication() 
*/
void start_radio_communication() {
  Serial.println("\nIntialsing Radio Module....");
  radio.begin();                                          //Initiallising the module
  radio.setChannel(127);                                  //Channel frequency to 
  radio.setDataRate( RF24_250KBPS );                      //Data rate to 250Kbps
  radio.openReadingPipe(1, thisSlaveAddress);             //Open pipe number 1 to read the data.
  radio.enableAckPayload();                               //Enabling auto acknowledge mode.
  radio.startListening();                                 //Puts the NRF to receiver mode
  radio.writeAckPayload(1, &ackData, sizeof(ackData));    // pre-load data
  Serial.println("DONE.\n");
}

/*
  ▪ Function Name: getData
  ▪ Input: None
  ▪ Output: None
  ▪ Logic: This function reads the data from NRF(if available) and store it. After that,
           it acknowledges back the transmitter with some data.
  ▪ Example Call: getData()
*/
void getData() {
  if ( radio.available() ) {
    radio.read( &dataReceived, sizeof(dataReceived) );
    if (connected) {                                                //If already connected
      if (dataReceived[0] == 'f' && dataReceived[1] == 'b') {       //But data recieved is that of attmepting to connect
        /*
            So, in this case it agains tries to connect.
        */
        ackData[0] = 100;
        ackData[1] = 100;
        connected = 0;                                              //Resetting the connection
        Serial.println("\n================================");
        Serial.println("    CONNECTION LOST.");
        Serial.println("================================\n");
        Serial.println("Re-connecting....");
      }
    }
    else {                                                          //If not connected
      if (dataReceived[0] == 'f' && dataReceived[1] == 'b') {       //Data recevived is for attempting to connect
        connected = 1;                                              //Connection succesfull
        Serial.println("\n================================");
        Serial.println("    Succesfully connected.");
        Serial.println("================================\n");
        ackData[0] = 101;                                           //Change acknowledged message
        ackData[1] = 101;
      }
      else {
        Serial.println("Searching for Transmitter..");
      }
    }
    updateReplyData();                                               //Put the Tx message to Tx buffer.
  }
}

/*
  ▪ Function Name: updateReplyData
  ▪ Input: None
  ▪ Output: None
  ▪ Logic: This function puts the acknowledge data into Tx buffer. This is to be done after every time
           reading is complete, since afte once data is acknowledged, buffer will be empty.
  ▪ Example Call: updateReplyData()
*/
void updateReplyData() {
  radio.writeAckPayload(1, &ackData, sizeof(ackData)); // load the payload for the next time
}

/*
  ▪ Function Name: execute_motion
  ▪ Input: None
  ▪ Output: None
  ▪ Logic: This function executes the motion according to the data received.
  ▪ Example Call: execute_motion() 
*/
void  execute_motion() {
  int val;                                              //To store the speed for the data
  if (dataReceived[0] != 'X' && connected) {
    val=int(dataReceived[1])-48;                       //Get the actual number(0-4)
    frequency = 1 + 0.8*val;                        //Update the freqeuncy
    if (dataReceived[0] == 'F') {                       //Forward
      switch(val){                                      //According  the spped, amplitude and Curve have to adjusted.
        case 0 : a = 50;
                 //b = 1.1* pi;
                 c=0;
                 break;
        case 1 : a = 55;
                 //b = 1.2* pi;
                 break;
        case 2 : a = 60;
                 //b = 1.5* pi;
                  c=0;
                 break;
        case 3 : a = 65;
                 //b = 1.7* pi;
                 break;
        case 4 : a = 70;
                 //b = 2* pi;
                  c=0;
                 break;          
      }
      //Updating the coeffecients
      gamma = -c / num_segments;                                        
      beta = b / num_segments;                                          
      amplitude = a * abs(sin(beta / 2));
      //Writing the angles to servo motors
      s1.write(90 + offset_0 + amplitude * sin(frequency * counter * pi / 180 + 0 * beta) + gamma);
      s2.write(90 + offset_1 + amplitude * sin(frequency * counter * pi / 180 + 1 * beta + pi / 2) + gamma);
      s3.write(90 + offset_2 + amplitude * sin(frequency * counter * pi / 180 + 2 * beta) + gamma);
    }
    else if (dataReceived[0] == 'L') {                 //Left        
      a = 60;
      b=1*pi;
      c=20*pi;
      //Updating the coeffecients
      gamma = -c / num_segments;                                        
      beta = b / num_segments;                                          
      amplitude = a * abs(sin(beta / 2));
      //Writing the angles to servo motors
      s1.write(60);
      s2.write(90 + offset_1 + amplitude * sin(frequency * counter * pi / 180 + 1 * beta + pi / 2) + gamma);
      s3.write(90 + offset_2 + amplitude * sin(frequency * counter * pi / 180 + 2 * beta) + gamma);
    }
    else if (dataReceived[0] == 'R') {                 //Right   
      a = 60;
      b=1*pi;
      c=-20*pi;
      //Updating the coeffecients
      gamma = -c / num_segments;                                        
      beta = b / num_segments;                                          
      amplitude = a * abs(sin(beta / 2));
      //Writing the angles to servo motors
      s1.write(120);
      s2.write(90 + offset_1 + amplitude * sin(frequency * counter * pi / 180 + 1 * beta + pi / 2) + gamma);
      s3.write(90 + offset_2 + amplitude * sin(frequency * counter * pi / 180 + 2 * beta) + gamma);
    }
    else if (dataReceived[0] == 'B') {                 //Left
      frequency = 3;          
      a = 50;
      b=1*pi;
      c=0;
      //Updating the coeffecients
      gamma = -c / num_segments;                                        
      beta = b / num_segments;                                          
      amplitude = a * abs(sin(beta / 2));
      //Writing the angles to servo motors
      s3.write(90 + offset_0 + amplitude * sin(frequency * counter * pi / 180 + 0 * beta) + gamma);
      s2.write(90 + offset_1 + amplitude * sin(frequency * counter * pi / 180 + 1 * beta + pi / 2) + gamma);
      s1.write(90 + offset_2 + amplitude * sin(frequency * counter * pi / 180 + 2 * beta) + gamma);
    }
      delay(delayTime);                                //Wait for some time to let servo go to their setted position.
      counter++;                           
      if(counter>360){                                 //If counter goes above 360, reset it to 0
      counter=0;
      }
  }
}

/*
  ▪ Function Name: Timer_init
  ▪ Input: None
  ▪ Output: None
  ▪ Logic: This function initallises timer 2 and sets the delay after which the BOT will listen to commands.
  ▪ Example Call: Timer_init()
*/
void Timer_init() {
  //Resetting registers
  TCCR2A = 0;                                           
  TCCR2B = 0;
  TCNT2  = 0;
  OCR2A = 255;                                          //Compare at OVF
  TCCR2A |= (1 << WGM21);                               //CTC mode   
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);    //1024 prescaling  
  TIMSK2 |= (1 << OCIE2A);                              //Interrupt at compare match
}

/*
  ▪ Function Name: setup
  ▪ Input: None
  ▪ Output: None
  ▪ Logic: This function setups the whole harwadre and starte the Serial communication. 
           This is automatically called from main().
  ▪ Example Call: setup()
*/
void setup() {
  Serial.begin(9600);                                   //Starting Serial communication
  cli();                                                //Clear interrupts
  motd();                                               //Display message of the day
  Timer_init();                                         //Initiallising timer 2
  start_radio_communication();                          //Configure NRF24L01 for communication.
  //Attaching servos
  s1.attach(2);
  s2.attach(3);
  s3.attach(4);
  //Bringing all servos to 90 deg initially.
  s1.write(90 + offset_0);
  s2.write(90 + offset_1);
  s3.write(90 + offset_2);
  sei();                                                //Interrupts enabled
  delay(startPause);                                    //Holds the progrma for small time.
}

/*
  ▪ Function Name: loop
  ▪ Input: None
  ▪ Output: None
  ▪ Logic: This function is automatically called from while(1) loop from main(). 
           It execute the motion and gets the data once the timer 2 counts upto the setted delay. 
  ▪ Example Call: loop()
*/
void loop() {
  if(listen){                                           //If delay is over, listen to remote
    getData();                                          //Get the data
    listen= false;                                      //Reset flag again
  }
  execute_motion();                                     //Execute the motion
}

