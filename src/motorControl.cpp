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
  return;
}

void motorControl::setTarget(int target){
  _target = target;
  //Serial.print("_target: "); Serial.println(_target);
  return;
}
void motorControl::setDirection(int direction){
  _direction = direction;
  //Serial.print("_direction: "); Serial.println(_direction);
  return;
}
void motorControl::setMinSpeed(int speed){
  _minSpeed = speed;

  if(_minSpeed < 0){
    _minSpeed = 0;
  }
  //Serial.print("_minSpeed: "); Serial.println(_minSpeed);
  return;
}
void motorControl::setMaxSpeed(int speed){
  _maxSpeed = speed;

  if(_maxSpeed > 255){
    _maxSpeed = 255;
  }
  //Serial.print("_maxSpeed: "); Serial.println(_maxSpeed);
  return;
}

void motorControl::rotate(int speed, int direction){

  if(direction){
    analogWrite(_LeftBck, 0);
    analogWrite(_LeftFwd, speed);
    analogWrite(_RightFwd, 0);
    analogWrite(_RightBck, speed);
  }
  else{
    analogWrite(_LeftFwd, 0);
    analogWrite(_LeftBck, speed);
    analogWrite(_RightBck, 0);
    analogWrite(_RightFwd, speed);
  }
  //Serial.print("Direction: "); Serial.print(direction);
  //Serial.print(". Leftbck:"); Serial.print(_LeftBck);
  //Serial.print(". Leftfwd:"); Serial.print(_LeftFwd);
  //Serial.print(". Rightbck:"); Serial.print(_RightBck);
  //Serial.print(". Rightfwd:"); Serial.println(_RightFwd);
  return;
}

void motorControl::stop(void){
  analogWrite(_LeftFwd, 0);
  analogWrite(_LeftBck, 0);
  analogWrite(_RightBck, 0);
  analogWrite(_RightFwd, 0);
  return;
}

void motorControl::updateMotors(int turn){

int leftSpeed = 0;
int rightSpeed = 0;

  leftSpeed = _target + turn;
  if(leftSpeed < 0){
    leftSpeed = 0;
  }
  else if(leftSpeed > _maxSpeed){
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
  return;
}
