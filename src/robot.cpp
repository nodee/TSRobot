#include "robot.h"
#include "TimerOne.h"

#define DEBUG 1
//#define PRINTOUT 1
//#define MOTORS_EN 1
LineDetector ld(A3, A2, A1, A0, 2);
ProxDetector pd(A7, A6, A5, 2);
PIDController pid;
MotorController mc(6,5,3,11);

const int Led_pin = 13;
const int userButton_pin = 4;

const int tick_time_us = 10000;
const int tick_time_ms = 10;
bool tick_flag = 0;

enum RobotStates{OFF, BUTTON, INIT, CALI, RUN, LINE, PROX};
enum RobotStates state = OFF;
enum RobotStates prev_state = OFF;

enum ButtonStates{RELEASED = 0, PRESSED = 1};

int error = 0;
int response = 0;
long lastMillis = 0;
long thisMillis = 0;

float voltage = 0;

int ldBoolValues = 0;

int pdBoolValues = 0;

int hwCounter_A = 0;


void tick(){
  tick_flag = 1;
  if(hwCounter_A){
    hwCounter_A--;
  }
}

void setup()
{
  #if DEBUG
  Serial.begin(115200);
  Serial.println("DEBUG ENABLED");
  #endif
  #if PRINTOUT
  Serial.begin(115200);
  #endif
  pinMode(Led_pin, OUTPUT);
  pinMode(userButton_pin, INPUT);
  Timer1.initialize(tick_time_us);
  Timer1.attachInterrupt(tick);

  pid.setGains(2.7, 0, 0.5);   // PID Trails - 2.5,0,0.5 - gets round the first corner
  ld.setThreshold(40);         // Line detector threshold values
  pd.setThreshold(300);        // Proximity detector threshold values
#ifdef MOTORS_EN
  mc.setMotors(0, STOP);
  mc.setTarget(150);
#endif
  delay(1000);
}

void loop()
{
#if PRINTOUT
    ld.calibrate();           // calibrate line sensors
    ld.printInfo();
    ldBoolValues = ld.getBoolValues();
    Serial.print("BV: ");Serial.println(ldBoolValues, BIN);
    voltage = analogRead(A4);
    Serial.println(voltage);
    voltage = voltage * (4.68 / 1023.0);
    Serial.print(2 * voltage);Serial.println("V");
#else
    switch(state){                  // Robot State
      case OFF:{                    // OFF
#ifdef MOTORS_EN
        mc.setMotors(0, STOP);
#endif
        state = BUTTON;
        break;
      }
      case BUTTON:{                 // Wait for button press to start
        if(digitalRead(userButton_pin) == PRESSED){
          hwCounter_A = 40;
          state = INIT;
        }
        break;
      }
      case INIT:{                   // Initialise Settings
        if(!hwCounter_A){
          pd.caliThreshold();       // Calibrate proximity sensors
#ifdef MOTORS_EN
          mc.setMotors(150, LEFT);  // rotate left
#endif
          hwCounter_A = 800;
          state = CALI;
#ifdef DEBUG
          Serial.println("CAL..");
#endif
        }
        break;
      }
      case CALI:{                   // Rotate and calibrate sensors.
        if(hwCounter_A){
          ld.calibrate();           // calibrate line sensors
        }
        else{
#ifdef MOTORS_EN
          mc.setMotors(0, STOP);    // Calibration Complete.
#endif
          hwCounter_A = 500;
          state = RUN;
#ifdef DEBUG
          Serial.println("DONE.");
#endif
        }
        break;
      }
      case RUN:{                    // Normal Running Mode
        ldBoolValues = ld.getBoolValues();
        ldBoolValues = ~ldBoolValues;
        ldBoolValues &= 0x0F;
#ifdef DEBUG
        if(ldBoolValues & 0x08){Serial.print(1);}
        else{Serial.print(0);}
        if(ldBoolValues & 0x04){Serial.print(1);}
        else{Serial.print(0);}
        if(ldBoolValues & 0x02){Serial.print(1);}
        else{Serial.print(0);}
        if(ldBoolValues & 0x01){Serial.println(1);}
        else{Serial.println(0);}
#endif
        switch(ldBoolValues){
          case 0b00000000:{
            response = 100;
          }
          case 0b00001100: {
            response = 50;
          }
          case 0b00001000: {
            response = 100;
            break;
          }
          case 0b00000011: {
            response = -50;
          }
          case 0b00000001: {
            response = -100;
            break;
          }
          default:{
            thisMillis = millis();
            error = ld.getError();
            response = pid.calcResponse(error, (thisMillis - lastMillis));
#ifdef DEBUG
            Serial.print("ERR: ");Serial.println(error);
            Serial.print("RES: ");Serial.println(response);
#endif
            lastMillis = thisMillis;
            break;
          }
        }
        #ifdef MOTORS_EN
        mc.updateMotors(response);
        #endif
        break;
      }
      default:{
        state = OFF;
        break;
      }
    }// switch
#endif
}
