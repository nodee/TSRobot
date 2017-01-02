#include "MotorController.h"

MotorController::MotorController(int leftFwdPin, int leftBckPin, int rightFwdPin, int rightBckPin){
  _LeftFwd = leftFwdPin;
  _LeftBck = leftBckPin;
  _RightFwd = rightFwdPin;
  _RightBck = rightBckPin;
  _target = 0;
  return;
}

void MotorController::setTarget(int target){
  _target = target;
  return;
}

void MotorController::setMotors(int speed, int direction){

  switch(direction){
    case FWD:{
      analogWrite(_LeftBck, 0);
      analogWrite(_LeftFwd, speed);
      analogWrite(_RightBck, 0);
      analogWrite(_RightFwd, speed);
      break;
    }
    case BACK:{
      analogWrite(_LeftBck, speed);
      analogWrite(_LeftFwd, 0);
      analogWrite(_RightBck, speed);
      analogWrite(_RightFwd, 0);
      break;
    }
    case LEFT:{
      analogWrite(_LeftBck, 0);
      analogWrite(_LeftFwd, speed);
      analogWrite(_RightBck, speed);
      analogWrite(_RightFwd, 0);
      break;
    }
    case RIGHT:{
      analogWrite(_LeftBck, speed);
      analogWrite(_LeftFwd, 0);
      analogWrite(_RightBck, 0);
      analogWrite(_RightFwd, speed);
      break;
    }
    default:{
      analogWrite(_LeftBck, 0);
      analogWrite(_LeftFwd, 0);
      analogWrite(_RightBck, 0);
      analogWrite(_RightFwd, 0);
      break;
    }
  }
  return;
}

void MotorController::updateMotors(int turn){

  int leftSpeed = 0;
  int rightSpeed = 0;

  leftSpeed = _target + turn;
  rightSpeed = _target - turn;

  if(leftSpeed < MIN_MOTOR_SPEED){
    leftSpeed = MIN_MOTOR_SPEED;
  }
  else if(leftSpeed > MAX_MOTOR_SPEED){
    leftSpeed = MAX_MOTOR_SPEED;
  }

  if(rightSpeed < MIN_MOTOR_SPEED){
    rightSpeed = MIN_MOTOR_SPEED;
  }
  else if(rightSpeed > MAX_MOTOR_SPEED){
    rightSpeed = MAX_MOTOR_SPEED;
  }

  analogWrite(_LeftFwd, leftSpeed);
  analogWrite(_RightFwd, rightSpeed);
  return;
}
