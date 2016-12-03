#include "robot.h"
#include "TimerOne.h"

//#define DEBUG
LineDetector ld(A5, A2, A1, A0, A4, 2);
pid PID(2.5, 0, 0.5); // PID Trails - 2.5,0,0.5 - gets round the first corner
motorControl mc(5,6,3,11);

const int Led_pin = 13;

enum RobotStates{OFF, BUTTON, INIT, CALI, FIND_LINE, RUN, BLOCKED, TURN_LEFT, TURN_RIGHT, TURN_AROUND};
enum RobotStates state = OFF;
enum ButtonStates{RELEASED, PRESSED};
enum ButtonStates userButton = RELEASED;
int error = 0;
int response = 0;
int calibrateCounter = 0;
bool PIDEnabled = 0;
bool sensorsBinaryEnabled = 0;
int sensorBinaryValue = 0;
bool tick_20ms = 0;

void tick(){
  tick_20ms = 1;
}

void setup()
{
  pinMode(Led_pin, OUTPUT);
  Timer1.initialize(20);
  Timer1.attachInterrupt(tick);
  mc.setMaxSpeed(255);
  mc.setMinSpeed(0);
  mc.setTarget(127);
  mc.setDirection(1);
  delay(1000);
}

void loop()
{
  if(tick_20ms){
    tick_20ms = 0;

    if(PIDEnabled == 1){
      error = ld.getError();
      response = PID.calcResponse(error, 20);
      mc.updateMotors(response);
    }
    if(sensorsBinaryEnabled == 1){
      sensorBinaryValue = ld.getBoolValues();
    }
    switch(state){
      case OFF:{
        mc.stop();
        break;
      }
      case BUTTON:{
        if(digitalRead(userButton) == PRESSED){
          state = INIT;
        }
        break;
      }
      case INIT:{
        delay(1000);
        state = CALI;
        mc.rotate(1, 150);
        break;
      }
      case CALI:{
        // rotate and spam calibrate sensors.
        if(calibrateCounter < 2000){
          ld.calibrateAll();
          calibrateCounter++;
        }
        else{
          mc.stop();
          state = FIND_LINE;
          delay(500);
        }

        break;
      }
      case FIND_LINE:{
        // rotate and use binary sensor readings to find the line.
        break;
      }
      case RUN:{
        PIDEnabled = 1;
        if(prox.detect() == 1){
          state = BLOCKED;
        }
        break;
      }
      case BLOCKED:{
        mc.stop();
        // determine if need to turn left, right or around.
        break;
      }
      case TURN_AROUND:{
        // rotate 180 using the binary line detection
        break;
      }
      case TURN_LEFT:{
        // roatate 90 left using the binary line detection
        break;
      }
      case TURN_RIGHT:{
        // roatate 90 right using the binary line detection
        break;
      }
    }// switch
  }// if tick
}
