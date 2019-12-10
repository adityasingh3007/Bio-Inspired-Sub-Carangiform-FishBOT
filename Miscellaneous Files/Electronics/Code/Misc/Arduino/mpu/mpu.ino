#include<Wire.h>

const int MPU_addr=0x68;  // I2C address of the MPU-6050

int16_t AcX,AcY,AcZ;
int16_t Temp;
int16_t Gx,Gy,Gz;
double acX,acY,acZ,temp,gx,gy,gz;
void setup(){
  Serial.begin(9600);
  Serial.println("Initiallising.....");
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  //Gyro config
  Wire.beginTransmission(MPU_addr);           //begin, Send the slave adress (in this case 68) 
  Wire.write(0x1B);                       //We want to write to the GYRO_CONFIG register (1B hex)
  Wire.write(0x18);                       //Set the register bits as 00011000 (2000dps full scale)
  Wire.endTransmission(true);             //End the transmission with the gyro
  //Acc config
  Wire.beginTransmission(MPU_addr);           //Start communication with the address found during search.
  Wire.write(0x1C);                       //We want to write to the ACCEL_CONFIG register
  Wire.write(0x18);                       //Set the register bits as 00011000 (+/- 16g full scale range)
  Wire.endTransmission(true);
  Serial.println("SENSOR READY.");
  Serial.println("Ready to Go. Move the sensor to adjust the brightness.");
  Serial.println(" ");
  delay(1000);
}

void get_sensor_values() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  //Getting raw values from registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Temp=Wire.read()<<8|Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  Gx=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)     
  Gy=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  Gz=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  //Converting these raw datas to actual value
  temp=(Temp/(340.00))+36.50;
  acX=AcX*0.000488;
  acY=AcY*0.000488;
  acZ=AcZ*0.000488;
  gx=Gx*0.06103;
  gy=Gy*0.06103;
  gz=Gz*0.06103;
}


void loop(){
  get_sensor_values();
  /*Serial.print("Raw : AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Temp = ");Serial.print(Temp);
  Serial.print(" | GX = "); Serial.print(Gx);
  Serial.print(" | GY = "); Serial.print(Gy);
  Serial.print(" | GZ = "); Serial.println(Gz);*/
  Serial.print("Act : AcX = "); Serial.print(acX);
  Serial.print(" | AcY = "); Serial.print(acY);
  Serial.print(" | AcZ = "); Serial.print(acZ);
  Serial.print(" | Temp = ");Serial.print(temp);
  Serial.print(" | GX = "); Serial.print(gx);
  Serial.print(" | GY = "); Serial.print(gy);
  Serial.print(" | GZ = "); Serial.println(gz);
  Serial.println("");
  delay(100);
}
