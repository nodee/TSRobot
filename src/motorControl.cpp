#include "motorControl.h"

motorControl::motorControl(int leftFwdPin, int leftBckPin, int rightFwdPin, int rightBckPin){
  _LeftFwd = leftFwdPin;
  _LeftBck = leftBckPin;
  _RightFwd = rightFwdPin;
  _RightBck = rightBckPin;
  _target = 0;
  _direction = 1;
  _maxSpeed = 255;
  _minSpeed = 0;
}

void motorControl::setMinSpeed(int speed){
  _minSpeed = speed;

  if(_minSpeed < 0){
    _minSpeed = 0;
  }
}

void motorControl::setMaxSpeed(int speed){
  _maxSpeed = speed;

  if(_maxSpeed > 255){
    _maxSpeed = 255;
  }
}

void motorControl::rotate(int direction){

  if(direction){
    analogWrite(_LeftBck, 0);
    analogWrite(_LeftFwd, _maxSpeed);
    analogWrite(_RightFwd, 0);
    analogWrite(_RightBck, _maxSpeed);
  }
  else{
    analogWrite(_LeftFwd, 0);
    analogWrite(_LeftBck, _maxSpeed);
    analogWrite(_RightBck, 0);
    analogWrite(_RightFwd, _maxSpeed);
  }
}

void motorControl::stop(void){
  analogWrite(_LeftFwd, 0);
  analogWrite(_LeftBck, 0);
  analogWrite(_RightBck, 0);
  analogWrite(_RightFwd, 0);
}

void motorControl::updateMotors(int turn){

int leftSpeed = 0;
int rightSpeed = 0;

  leftSpeed = _target + turn;
  if(leftSpeed < 0){
    leftSpeed = 0;
  }
  else if(rightSpeed > _maxSpeed){
    leftSpeed = _maxSpeed;
  }

  rightSpeed = _target - turn;
  if(rightSpeed < 0){
    rightSpeed = 0;
  }
  else if(rightSpeed > _maxSpeed){
    rightSpeed = _maxSpeed;
  }

  if(_direction){
    analogWrite(_LeftFwd, leftSpeed);
    analogWrite(_RightFwd, rightSpeed);
  }
  else{
    analogWrite(_LeftBck, leftSpeed);
    analogWrite(_RightBck, rightSpeed);
  }

}

void motorControl::setTarget(int target){

  _target = target;

  return;
}

void motorControl::setDirection(int direction){

  _direction = direction;

  return;
}
