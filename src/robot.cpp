#include "robot.h"

// Analog sensors tested OK.
// PWM tested OK.
LineDetector ld(A5, A2, A1, A0, A4, 2);
pid PID(100, 100, 100);
motorControl mc(5,6,11,3);

enum RobotStates{SETUP, CALI, NAVI, CHG_DIR};

const int Led_pin = 13;
int state = SETUP;

void setup()
{
  pinMode(Led_pin, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  switch(state){
    case SETUP:{
      // Initiate PID, MC, IR, LD to start values, wait for input to start Calibration
      break;
    }
    case CALI:{
      
      // Pause PID, just spin and spam calibrate a bunch of times
      break;
    }
    case NAVI:{
      mc.updateMotors(PID.calcResponse(ld.getError(), 1));
      // Create a time base or pass the calculaton of ms since last PID calc
      // PID Operational
      break;
    }
    case CHG_DIR:{
      // Pause PID and spin around or switch the direction. maybe with the
      // sensors trailing the wheels the PID gains need adjusting.
      break;
    }
  }
}
