#include <Stepper.h>

const int stepsPerRevolution = 2048;

// IN1, IN2, IN3, IN4
Stepper motor(stepsPerRevolution, 36, 38, 37, 39);

const float angle1 = 0;
const float angle2 = -360;

int currentAngle = angle1;

void setup() {
  motor.setSpeed(10);
}

void loop() {

  int stepsForward = (angle2 - currentAngle) * stepsPerRevolution / 360.0;
  motor.step(stepsForward);
  currentAngle = angle2;

  delay(1000);

  int stepsBackward = (angle1 - currentAngle) * stepsPerRevolution / 360.0;
  motor.step(stepsBackward);
  currentAngle = angle1;

  delay(1000);
}