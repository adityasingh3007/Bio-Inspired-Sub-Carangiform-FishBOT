int num_Measure = 128 ;
int pinSignal = A0;   
long sum;
int level;
int state;
void setup ()  
{   
  pinMode (pinSignal, INPUT); // Set the signal pin as input   
  pinMode (8, OUTPUT);
  digitalWrite(8,HIGH);
  Serial.begin (9600);  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}  
   
void loop ()  
{  
  /*for(int i=0;i<num_Measure;i++){
    sum+=analogRead(pinSignal);
  }
  level=sum/num_Measure;
  sum=0;*/
  level=analogRead(pinSignal);
  state=digitalRead(2);
  if(state){
    digitalWrite(13,HIGH);
  }
  else{
    digitalWrite(13,LOW);
  }
  Serial.println(level);
  //Serial.println(state);
}  
