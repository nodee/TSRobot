#ifndef PID_H
#define PID_H

#include <Arduino.h>

class pid{
  public:
    pid(int Kp, int Ki, int Kd);
    int calcResponse(int error, int ms);
    void setGains(int Kp, int Ki, int Kd);
  private:
    int _prev_error;
    int _integral_sum;
    int _Kp;
    int _Ki;
    int _Kd;
};

#endif
