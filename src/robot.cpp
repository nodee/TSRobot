#include "robot.h"
#include "TimerOne.h"

//#define DEBUG

// Analog sensors tested OK.
// PWM tested OK.
LineDetector ld(A5, A2, A1, A0, A4, 2);
pid PID(2.5, 0, 0.5);
// PID Trails:
// 2.5,0,0.5 - gets round the first corner
motorControl mc(5,6,3,11);

enum RobotStates{SETUP, CALI, NAVI, CHG_DIR};

const int Led_pin = 13;
int calcError = 0;
int response = 0;
int state = SETUP;
int initCounter = 0;
bool tick_20ms = 0;

void tick(){
  tick_20ms = 1;
}

void setup()
{
  pinMode(Led_pin, OUTPUT);
  //Serial.begin(115200);
  Timer1.initialize(20);
  Timer1.attachInterrupt(tick);
  mc.setMaxSpeed(255);
  mc.setMinSpeed(0);
  mc.setTarget(127);
  mc.setDirection(1);
}

void loop()
{
  if(tick_20ms){
    tick_20ms = 0;
    switch(state){
      case SETUP:{
        // Initiate PID, MC, IR, LD to start values, wait for input to start Calibration
        mc.rotate(60, 1);
        //Serial.println("CALI...");
        state = CALI;
        break;
      }
      case CALI:{
        if(initCounter < 600){
          ld.calibrateAll();
          initCounter++;
        }
        else{
            //Serial.println("DONE.");
            mc.stop();
            state = NAVI;
        }
        break;
      }
      case NAVI:{
        //long start = millis();
        calcError = ld.getError();
      //  Serial.print("Error: ");
        //Serial.print(calcError);
        response = PID.calcResponse(calcError, 20);
        //Serial.print(" Response: ");
        //Serial.print(response);
        mc.updateMotors(response);
        //Serial.print(" millis: ");
        //Serial.println(millis() - start);
         //Create a time base or pass the calculaton of ms since last PID calc
         //PID Operational
        break;
      }
      case CHG_DIR:{
        // Pause PID and spin around or switch the direction. maybe with the
        // sensors trailing the wheels the PID gains need adjusting.
        break;
      }
    }
  }
  else{

  }
}

void findTrack(){
  int state = 0;
  int found = 0;
  int error = 0;

  while(!found){
    error = ld.getError();
    switch(state){
      case 0:{
        mc.rotate(100, 1);
        state = 1;
        break;
      }
      case 1:{  // wait for higher than 40
        if(error > 40){
          state = 2;
        }
        break;
      }
      case 2:{  // keep going untill the error is on the way down
        if((error < 40) && (error > 20)){
          state = 3;
        }
        break;
      }
      case 3:{
        if((error < 10) && (error > -10)){
          mc.stop();
          found = 1;
        }
        break;
      }
    }
  }
}
