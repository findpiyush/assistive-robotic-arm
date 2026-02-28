#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

// flex sensor pins
int flexsensorpin1 = A0;
int flexsensorpin2 = A2;

// led
int red1 = 10;
int red2 = 11;
int red3 = 12;

int green1 = 7;
int green2 = 8;
int green3 = 9;

// raw flex values
int sensor1;
int sensor2;

// smooth flex values
float flex1Smooth = 900;
float flex2Smooth = 900;

// deadzone memory
int flex1Last = 900;
int flex2Last = 900;

// MPU variables
float gyroX=0;
float gyroY=0;
float gyroZ=0;

float pitch;
float roll;

void setup() {

Serial.begin(115200);

pinMode(red1,OUTPUT);
pinMode(red2,OUTPUT);
pinMode(red3,OUTPUT);

pinMode(green1,OUTPUT);
pinMode(green2,OUTPUT);
pinMode(green3,OUTPUT);

if (!mpu.begin()) {
  while(1);
}

mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
mpu.setGyroRange(MPU6050_RANGE_250_DEG);
mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
}

void loop() {

sensors_event_t a, g, temp;
mpu.getEvent(&a, &g, &temp);

// gyro smoothing
gyroX = 0.9 * gyroX + 0.1 * g.gyro.x;
gyroY = 0.9 * gyroY + 0.1 * g.gyro.y;
gyroZ = 0.9 * gyroZ + 0.1 * g.gyro.z;

// angles
pitch = atan2(a.acceleration.y, a.acceleration.z) * 180 / PI;

roll = atan2(
-a.acceleration.x,
sqrt(a.acceleration.y*a.acceleration.y + a.acceleration.z*a.acceleration.z)
) * 180 / PI;

// read flex sensor
sensor1 = analogRead(flexsensorpin1);
sensor2 = analogRead(flexsensorpin2);

// filter flex sensor
flex1Smooth = 0.8 * flex1Smooth + 0.2 * sensor1;
flex2Smooth = 0.8 * flex2Smooth + 0.2 * sensor2;

int flex1 = flex1Smooth;
int flex2 = flex2Smooth;

// deadzone
if(abs(flex1 - flex1Last) < 4) flex1 = flex1Last;
if(abs(flex2 - flex2Last) < 4) flex2 = flex2Last;

flex1Last = flex1;
flex2Last = flex2;

// led logic sensor 1
// 968 - 928 
//tweak these values depending on the mood of the flex sensor on the day
if(flex1 > 960){
  digitalWrite(red1,HIGH);
  digitalWrite(red2,HIGH);
  digitalWrite(red3,HIGH);
}
else if(flex1 > 950){
  digitalWrite(red1,HIGH);
  digitalWrite(red2,HIGH);
  digitalWrite(red3,LOW);
}
else if(flex1 > 930){
  digitalWrite(red1,HIGH);
  digitalWrite(red2,LOW);
  digitalWrite(red3,LOW);
}
else{
  digitalWrite(red1,LOW);
  digitalWrite(red2,LOW);
  digitalWrite(red3,LOW);
}

// led logic sensor 1
// 1000 - 970
//tweak these values depending on the mood of the flex sensor on the day
if(flex2 > 1000){
  digitalWrite(green1,HIGH);
  digitalWrite(green2,HIGH);
  digitalWrite(green3,HIGH);
}
else if(flex2 > 990){
  digitalWrite(green1,HIGH);
  digitalWrite(green2,HIGH);
  digitalWrite(green3,LOW);
}
else if(flex2 > 980){
  digitalWrite(green1,HIGH);
  digitalWrite(green2,LOW);
  digitalWrite(green3,LOW);
}
else{
  digitalWrite(green1,LOW);
  digitalWrite(green2,LOW);
  digitalWrite(green3,LOW);
}

// send data to UNO
Serial.print((int)pitch);
Serial.print(",");

Serial.print((int)roll);
Serial.print(",");

Serial.print(flex1);
Serial.print(",");

Serial.println(flex2);

delay(15);
}