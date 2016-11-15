#include "pid.h"

pid::pid(int Kp, int Ki, int Kd){
  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;
  _prev_error = 0;
  _integral_sum = 0;
}

void pid::setGains(int Kp, int Ki, int Kd){

  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;

  return;
}

int pid::calcResponse(int error, int dt)
{
  int proportional;
  float integral = 0.0;
  float derivative = 0.0;

  proportional = error;
  integral = _integral_sum + (error * dt);
  derivative = (error - _prev_error) / dt;

  error = (_Kp * proportional) + (_Ki * integral) + (_Kd * derivative);

  //add some bounds checking and correction for turn value

  _prev_error = error;

  return error;
}
