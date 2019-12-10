int num_Measure = 128 ; // Set the number of measurements   
int pinSignal = A0; // pin connected to pin O module sound sensor   
long Sound_signal;    // Store the value read Sound Sensor   
long sum = 0 ; // Store the total value of n measurements   
long level = 0 ; // Store the average value   

int x=255;
long m=1;
void setup ()  
{   
  pinMode (pinSignal, INPUT); // Set the signal pin as input   
  pinMode (8, OUTPUT);
  pinMode (9, OUTPUT);
  pinMode (10, OUTPUT);
  digitalWrite(8,HIGH);
  Serial.begin (9600);  
}  
   
void loop ()  
{  
  if(m%200==0){
    x--;
  }
  m++;
 analogWrite(9,x);
  // Performs 128 signal readings   
  for ( int i = 0 ; i <num_Measure; i ++)  
  {  
   Sound_signal = analogRead (pinSignal);  
    sum =sum + Sound_signal;  
  }  
 
  level = sum / num_Measure; // Calculate the average value   
  Serial.print("Sound Level: ");
  Serial.println (level);  
  sum = 0 ; // Reset the sum of the measurement values  
  //delay(100);
}  
