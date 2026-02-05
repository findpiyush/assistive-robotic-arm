#include <Servo.h>

Servo base;
Servo servo1;
Servo servo2;
Servo servo3;
Servo endEff;

int l1 = 50;
int u1 = 130;

int l2 = 50;
int u2 = 130;

int l3 = 0;
int u3 = 60;

void setup() {

  base.attach(2);
  servo1.attach(3);
  servo2.attach(4);
  servo3.attach(5);
  endEff.attach(6);

  base.write(0);
  servo1.write(l1);
  servo2.write(l2);
  servo3.write(l3);
  endEff.write(70);
}

void loop() {

  for(int i = 0; i <= 60; i += 5)
  {
    base.write(i);
    servo1.write(l1 + i);
    servo2.write(l2 + i);
    servo3.write(i);

    delay(200);
  }

  for(int i = 60; i >= 0; i -= 5)
  {
    base.write(i);
    servo1.write(l1 + i);
    servo2.write(l2 + i);
    servo3.write(i);

    delay(200);
  }

}