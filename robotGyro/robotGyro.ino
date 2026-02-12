#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

float gyroX = 0;
float gyroY = 0;
float gyroZ = 0;

float pitch;
float roll;

void setup() {

  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("MPU6050 Stable Demo");

  if (!mpu.begin()) {
    Serial.println("MPU6050 not detected");
    while (1);
  }

  // settings for hand motion
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  Serial.println("MPU6050 Ready");
}

void loop() {

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // gyro smoothing
  gyroX = 0.9 * gyroX + 0.1 * g.gyro.x;
  gyroY = 0.9 * gyroY + 0.1 * g.gyro.y;
  gyroZ = 0.9 * gyroZ + 0.1 * g.gyro.z;

  // angle calculation
  pitch = atan2(a.acceleration.y, a.acceleration.z) * 180 / PI;
  roll  = atan2(-a.acceleration.x, sqrt(a.acceleration.y*a.acceleration.y + a.acceleration.z*a.acceleration.z)) * 180 / PI;

  // display
  Serial.print("Pitch: ");
  Serial.print(pitch);

  Serial.print("  Roll: ");
  Serial.print(roll);

  Serial.print("  GyroX: ");
  Serial.print(gyroX);

  Serial.print("  GyroY: ");
  Serial.print(gyroY);

  Serial.print("  GyroZ: ");
  Serial.println(gyroZ);

  delay(20);
}