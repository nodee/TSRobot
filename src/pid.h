#ifndef PID_H
#define PID_H

#include <Arduino.h>

class pid{
  public:
    int calcResponse(int error, int ms);
    void setTarget(int target);
    void setGains(int Kp, int Ki, int Kd);
  private:
    int _target;
    int _prev_error;
    int _integral_sum;
};

#endif
