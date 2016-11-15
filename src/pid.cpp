#include "pid.h"

void pid::setTarget(int target){

  _target = target;

  return;
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
  int integral;
  int derivative;

  proportional = _Kp * error;
  integral = _Ki * (_integral_sum + (error * dt));
  derivative = _Kd * ((error – _prev_error) / dt)

  error = proportional + integral + derivative;

  //add some bounds checking and correction for turn value

  _prev_error = error;

  return error;
}
