#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

// flex sensor
int flexsensorpin1 = A0;
int sensor1;

int flexsensorpin2 = A2;
int sensor2;

// led pins
int red1 = 10;
int red2 = 11;
int red3 = 12;

int green1 = 7;
int green2 = 8;
int green3 = 9;

// mpu variables
float gyroX = 0;
float gyroY = 0;
float gyroZ = 0;

float pitch;
float roll;

void setup() {

  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("MPU6050 + Flex Sensor System");

  // mpu setup
  if (!mpu.begin()) {
    Serial.println("MPU6050 not detected");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  Serial.println("MPU6050 Ready");

  // led setup
  pinMode(red1,OUTPUT);
  pinMode(red2,OUTPUT);
  pinMode(red3,OUTPUT);

  pinMode(green1,OUTPUT);
  pinMode(green2,OUTPUT);
  pinMode(green3,OUTPUT);
}

void loop() {

  // read MPU6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // gyro smoothing
  gyroX = 0.9 * gyroX + 0.1 * g.gyro.x;
  gyroY = 0.9 * gyroY + 0.1 * g.gyro.y;
  gyroZ = 0.9 * gyroZ + 0.1 * g.gyro.z;

  // angle calculation
  pitch = atan2(a.acceleration.y, a.acceleration.z) * 180 / PI;
  roll  = atan2(-a.acceleration.x, sqrt(a.acceleration.y*a.acceleration.y + a.acceleration.z*a.acceleration.z)) * 180 / PI;

  // flex sensor 1
  sensor1 = analogRead(flexsensorpin1);

  if(sensor1 > 900){
    digitalWrite(red1,HIGH);
    digitalWrite(red2,HIGH);
    digitalWrite(red3,HIGH);
  }
  else if(sensor1 > 850){
    digitalWrite(red1,HIGH);
    digitalWrite(red2,HIGH);
    digitalWrite(red3,LOW);
  }
  else if(sensor1 > 800){
    digitalWrite(red1,HIGH);
    digitalWrite(red2,LOW);
    digitalWrite(red3,LOW);
  }
  else{
    digitalWrite(red1,LOW);
    digitalWrite(red2,LOW);
    digitalWrite(red3,LOW);
  }

  // flex sensor 2
  sensor2 = analogRead(flexsensorpin2);

  if(sensor2 > 980){
    digitalWrite(green1,HIGH);
    digitalWrite(green2,HIGH);
    digitalWrite(green3,HIGH);
  }
  else if(sensor2 > 965){
    digitalWrite(green1,HIGH);
    digitalWrite(green2,HIGH);
    digitalWrite(green3,LOW);
  }
  else if(sensor2 > 950){
    digitalWrite(green1,HIGH);
    digitalWrite(green2,LOW);
    digitalWrite(green3,LOW);
  }
  else{
    digitalWrite(green1,LOW);
    digitalWrite(green2,LOW);
    digitalWrite(green3,LOW);
  }

  // display
  Serial.print("Pitch: ");
  Serial.print(pitch);

  Serial.print("  Roll: ");
  Serial.print(roll);

  Serial.print("  GyroX: ");
  Serial.print(gyroX);

  Serial.print("  Flex1: ");
  Serial.print(sensor1);

  Serial.print("  Flex2: ");
  Serial.println(sensor2);

  delay(20);
}