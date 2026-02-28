#include <Servo.h>

Servo base;
Servo servo1;
Servo servo2;
Servo endEff;

// servo limits
int l1 = 50;
int u1 = 130;

int l2 = 50;
int u2 = 130;

int lE = 0;
int uE = 70;

// target positions
int baseTarget = 90;
int servo1Target = 90;
int servo2Target = 90;
int endEffTarget = 90;

// current positions
int baseCurrent = 90;
int servo1Current = 90;
int servo2Current = 90;
int endEffCurrent = 0;

// previous flex values (for deadband)
int lastFlex1 = 0;
int lastFlex2 = 0;

void setup() {

  Serial.begin(115200);

  base.attach(2);
  servo1.attach(3);
  servo2.attach(4);
  endEff.attach(7);

  base.write(baseCurrent);
  servo1.write(servo1Current);
  servo2.write(servo2Current);
  endEff.write(endEffCurrent);
}

void loop() {

  if (Serial.available())
  {

    int pitch = Serial.parseInt();
    int roll  = Serial.parseInt();
    int flex1 = Serial.parseInt();
    int flex2 = Serial.parseInt();

    // flex deadzone
    if(abs(flex1 - lastFlex1) < 5) flex1 = lastFlex1;
    if(abs(flex2 - lastFlex2) < 5) flex2 = lastFlex2;

    lastFlex1 = flex1;
    lastFlex2 = flex2;

    // map sensors

    baseTarget = map(pitch, -45, 45, 0, 180);

    servo1Target = map(roll, 45, -45, l1, u1);

    servo2Target = map(flex1, 968, 920, l2, u2);

    // end effector
    endEffTarget = map(flex2, 993, 1010, lE, uE);

    // apply limits

    baseTarget = constrain(baseTarget, 0, 180);
    servo1Target = constrain(servo1Target, l1, u1);
    servo2Target = constrain(servo2Target, l2, u2);
    endEffTarget = constrain(endEffTarget, lE, uE);
  }

  // smooth movement
  smoothMove(base, baseCurrent, baseTarget);
  smoothMove(servo1, servo1Current, servo1Target);
  smoothMove(servo2, servo2Current, servo2Target);
  smoothMove(endEff, endEffCurrent, endEffTarget);

  delay(10);
}

void smoothMove(Servo &s, int &current, int target)
{
  if(current == target) return;

  if(current < target) current += 2;
  if(current > target) current -= 2;

  s.write(current);
}