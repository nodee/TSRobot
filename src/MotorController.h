#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>

#define MAX_MOTOR_SPEED 255
#define MIN_MOTOR_SPEED 0

enum Directions{FWD, BACK, LEFT, RIGHT, STOP};

class MotorController{

public:
  MotorController(int leftFwdPin, int leftBckPin, int rightFwdPin, int rightBckPin);
  void setMotors(int speed, int direction);
  void setTarget(int target);
  void updateMotors(int turn);
private:
  int _target;
  int _LeftFwd;
  int _LeftBck;
  int _RightFwd;
  int _RightBck;
};

#endif
