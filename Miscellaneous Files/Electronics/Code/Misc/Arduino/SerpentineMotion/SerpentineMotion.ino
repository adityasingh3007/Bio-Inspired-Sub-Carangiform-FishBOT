#include <Servo.h> 
#define pi 3.14159

Servo s1; 
Servo s2;
Servo s3;
Servo s4; 
  
int counter = 0;            // Loop counter variable
int frequency = 6 ;          // Oscillation frequency of segments.
float a = 70;               //Amplitude coeff
float b = 1*pi;             //Curve Coeff 
float c = 0 ;                //Turn Coeff
int num_segments = 3;       //Number of joints
float gamma = -c/num_segments;
float beta = b/num_segments;
float amplitude=a*abs(sin(beta/2));

float offset_0=-5;
float offset_1=1;
float offset_2=5;

int delayTime = 7;          // Delay between limb movements
int startPause = 3000;      // Delay time to position robot

int test = -3;              // Test varialble takes values from -6 to +5
  
void setup() 
{ 
  
// Attach segments to pins  
   s1.attach(2);
   s2.attach(3);
   s3.attach(4);
 
// Put snake in starting position
   s1.write(90+offset_0);
   s2.write(90+offset_1); 
   s3.write(90+offset_2);
  delay(startPause);  // Pause to position robot
} 
  
  
void loop() 
{
  //Forward
   for(counter = 0; counter < 360; counter += 1)  {
      delay(delayTime);
      s1.write(90+offset_0+amplitude*sin(frequency*counter*pi/180+0*beta)+gamma);
      s2.write(90+offset_1+amplitude*sin(frequency*counter*pi/180+1*beta+ pi/2)+gamma);
      s3.write(90+offset_2+amplitude*sin(frequency*counter*pi/180+2*beta)+gamma);
    }
  //Left
   s1.write(60);
  for(counter = 0; counter < 360; counter += 1)  {
      delay(delayTime);
      s2.write(90+offset_1+amplitude*sin(frequency*counter*pi/180+1*beta+ pi/2)+gamma);
      s3.write(90+offset_2+amplitude*sin(frequency*counter*pi/180+2*beta)+gamma);
    }
 //Right
  s1.write(120);
  for(counter = 0; counter < 360; counter += 1)  {
      delay(delayTime);
      s2.write(90+offset_1+amplitude*sin(frequency*counter*pi/180+1*beta+ pi/2)+gamma);
      s3.write(90+offset_2+amplitude*sin(frequency*counter*pi/180+2*beta)+gamma);
 }
 
}
