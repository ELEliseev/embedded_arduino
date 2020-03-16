#include <Wire.h>

const int MPU_addr = 0x68; // I2C address of the MPU-6050
double AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

double Summ=0;


double dissX=0;
double dissY=0;
double dissZ=0;

double accXangle; // Angle calculate using the accelerometer
double accYangle;
double accZangle;
double acc=0;
// переменные для калмана
float Mn=0 ;    // результирующее значение
float An=0;    //  исходное значение
float Gn=0;  
float Mn1=0 ;  // результат вычисления в предыдущей интерации
float k=0.1 ;    //  коэффициент стабилизации






// переменные для калмана
double timer;
double timestart;
// Функция фильтрации
float filter(float An,float Gn) {
  timer=((micros()-timestart)/1000000); 
  Gn=-(Gn/131)*timer;
  
 Mn = (1-k)*(Mn1+Gn) +k*An;
 Mn1 = Mn;
  return (Mn);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop() {
 
 
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);  // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
   Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H)  & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  accYangle = (atan2(AcX,AcZ)+PI)*RAD_TO_DEG;
  accXangle = (atan2(AcY,AcZ)+PI)*RAD_TO_DEG;



  acc=filter(((accYangle)-180), GyY);
 timestart=micros();
  
 
  Serial.println(acc);
  // Serial.print(" "); 
 //Serial.println(((accYangle)-180));
   
   
  // Serial.print();
 //  Serial.print(" "); 
//Serial.println (AcX+AcY+AcZ);
//Serial.println(diss); 
 //Serial.println(An);
 //Serial.print(" ");
// Serial.println(nsumm);
//Serial.println(timer);
//Serial.print(AcX);
 //   Serial.print(" "); 
 //   Serial.print(AcY );
 //  Serial.print(" "); 
  // Serial.println(AcZ );
  // Serial.println(P);
 delay(10);
}
