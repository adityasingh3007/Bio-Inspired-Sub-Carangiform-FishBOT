/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Servo myservo1;
int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo1.attach(2);
  myservo1.write(90);  
}

void loop() {
  for(pos=0;pos<=180;pos++){
     myservo.write(pos);
     delay(5);
  }
  for(pos=180;pos>=0;pos--){
     myservo.write(pos);
     delay(5);
  }
  
}

