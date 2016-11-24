#include "pid.h"

pid::pid(float Kp, float Ki, float Kd){
  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;
  _prev_error = 0;
  _integral_sum = 0;
}

void pid::setGains(float Kp, float Ki, float Kd){

  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;

  return;
}

int pid::calcResponse(int error, int dt)
{
  float proportional;
  float integral = 0.0;
  float derivative = 0.0;
  float thisError = (float)error;

  proportional = thisError;
  integral = _integral_sum + (thisError * dt);
  derivative = (thisError - _prev_error) / dt;

  thisError = (_Kp * proportional) + (_Ki * integral) + (_Kd * derivative);

  //add some bounds checking and correction for turn value

  _prev_error = thisError;

  return (int)thisError;
}
