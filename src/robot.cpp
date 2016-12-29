#include "robot.h"
#include "TimerOne.h"

//#define DEBUG
LineDetector ld(A5, A2, A1, A0, A4, 2);
pid PID(2.5, 0, 0.5); // PID Trails - 2.5,0,0.5 - gets round the first corner
motorControl mc(5,6,3,11);

const int Led_pin = 13;
const int userButton_pin = 12;
const int tick_time = 20;

enum RobotStates{OFF, BUTTON, INIT, CALI, FIND_LINE, RUN, BLOCKED, TURN_LEFT, TURN_RIGHT, TURN_AROUND};
enum RobotStates state = INIT;
enum RobotStates prevState = OFF;
enum ButtonStates{RELEASED = 0, PRESSED = 1};
int error = 0;
int response = 0;
int calibrateCounter = 0;
bool PIDEnabled = 0;
int sensorBinaryValue = 0;
bool tick_flag = 0;
int hwCounter_A = 0;
int findingLineState = 0;
int CalibrationComplete = 0;

void tick(){
  tick_flag = 1;
  if(hwCounter_A){
    hwCounter_A--;
  }
}

void setup()
{
  //Serial.begin(115200);
  pinMode(Led_pin, OUTPUT);
  pinMode(userButton_pin, INPUT);
  Timer1.initialize(tick_time);
  Timer1.attachInterrupt(tick);
  mc.stop();
  mc.setMaxSpeed(255);
  mc.setMinSpeed(0);
  mc.setTarget(150);
  mc.setDirection(1);
  ld.setThreshold(25);
  delay(1000);
  hwCounter_A = 50;
  //Serial.println("CALI START");
}

void loop()
{
  if(tick_flag){
    tick_flag = 0;

    if(PIDEnabled == 1){            // PID ON/OFF
      error = ld.getError();
      response = PID.calcResponse(error, 20);
      mc.updateMotors(response);
    }

    switch(state){                  // Robot State
      case OFF:{                    // OFF
        mc.stop();
        break;
      }
      case BUTTON:{                 // Wait for button press to start
        if(digitalRead(userButton_pin) == PRESSED){
          state = INIT;
          hwCounter_A = 50;
        }
        break;
      }
      case INIT:{                   // Initialise Settings
        if(!hwCounter_A){
          calibrateCounter = 0;
          CalibrationComplete = 0;
          state = CALI;
          mc.rotate(150, 1);
        }
        break;
      }
      case CALI:{                   // Rotate and calibrate sensors.
        if(!CalibrationComplete){
          if(calibrateCounter < 650){
            ld.calibrate();
            calibrateCounter++;
          }
          else{
            mc.stop();                // Calibration Complete.
            state = FIND_LINE;
            prevState = CALI;
            CalibrationComplete = 1;
            findingLineState = 0;
            hwCounter_A = 25;
          }
        }
        else{
          state = RUN;

        }
        break;
      }
      case FIND_LINE:{              // Use binary sensor readings to find line.
        if(!hwCounter_A){
          sensorBinaryValue = ld.getBoolValues();
          switch(findingLineState){
            case 0:{
              mc.rotate(45, 0);    // start rotating
              findingLineState++;
              break;
            }
            case 1:{                // find free space as a starting point.
              if(!sensorBinaryValue){
                findingLineState++;
              }
              break;
            }
            case 2:{          // wait for the furest left or right sensor to trigger
              sensorBinaryValue &= 0x00010001;  // mask off the other sensors ****might not need****
              if((sensorBinaryValue == 0b00010000) || (sensorBinaryValue == 0b00000001)){
                findingLineState++;
              }
              break;
            }
            case 3:{         // still rotating wait for the middle sensor to hit
              if(sensorBinaryValue & 0b00000100){
                findingLineState++;
              }
              break;
            }
            case 4:{        // slow the rotation and find spot between error = 5 / -5
              error = ld.getError();
              if(error < -5){
                mc.rotate(20, 0);
              }
              else if(error > 5){
                mc.rotate(20, 1);
              }
              else{       // line found, stop, go to prev state.
                mc.stop();
                findingLineState = 0;
                state = prevState;
              }
              break;
            }
          }
        }
        break;
      }
      case RUN:{                    // Normal line following mode
        PIDEnabled = 1;
        break;
      }
      case BLOCKED:{                // Proximit sensor tripped.
        mc.stop();
        // determine if need to turn left, right or around.
        break;
      }
      case TURN_AROUND:{            // Evasive Actions.
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
