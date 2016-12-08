#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>

class motorControl{

public:
  motorControl(int leftFwdPin, int leftBckPin, int rightFwdPin, int rightBckPin);
  void setTarget(int target);
  void setDirection(int direction);
  void setMaxSpeed(int speed);
  void setMinSpeed(int speed);
  void updateMotors(int turn);
  void rotate(int speed, int direction);
  void stop(void);
private:
  int _direction;
  int _target;
  int _maxSpeed;
  int _minSpeed;
  int _LeftFwd;
  int _LeftBck;
  int _RightFwd;
  int _RightBck;
};

#endif
