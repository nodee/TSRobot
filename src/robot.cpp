#include "robot.h"
#include "TimerOne.h"

#define DEBUG 1
LineDetector ld(A5, A2, A1, A0, A4, 2);
ProxDetector pd(A7, A6, A3, 2);
PIDController pid;
MotorController mc(5,6,3,11);

const int Led_pin = 13;
const int userButton_pin = 12;

const int tick_time_us = 10000;
const int tick_time_ms = 10;
bool tick_flag = 0;

enum RobotStates{OFF, BUTTON, INIT, CALI, RUN, LINE, PROX};
enum RobotStates state = INIT;

enum ButtonStates{RELEASED = 0, PRESSED = 1};

int error = 0;
int response = 0;
long lastMillis = 0;
long thisMillis = 0;

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
  #endif
  pinMode(Led_pin, OUTPUT);
  pinMode(userButton_pin, INPUT);
  Timer1.initialize(tick_time_us);
  Timer1.attachInterrupt(tick);

  pid.setGains(2.5, 0, 0.5);   // PID Trails - 2.5,0,0.5 - gets round the first corner
  ld.setThreshold(25);         // Line detector threshold values
  pd.setThreshold(300);        // Proximity detector threshold values
  mc.setMotors(0, STOP);
  mc.setTarget(150);
  delay(1000);
}

void loop()
{
#if DEBUG

    if(digitalRead(userButton_pin) == PRESSED){
      Serial.println("Button Pressed");
    }

    digitalWrite(2, HIGH);
    delay(10);

    Serial.println("Line Sensors.");
    Serial.print("Left : "); Serial.println(analogRead(A5));
    Serial.print("Mid L: "); Serial.println(analogRead(A6));
    Serial.print("Mid  : "); Serial.println(analogRead(A1));
    Serial.print("Mid R: "); Serial.println(analogRead(A0));
    Serial.print("Right: "); Serial.println(analogRead(A4));

    Serial.println("Proximity Sensors.");
    Serial.print("Left : "); Serial.println(analogRead(A7));
    Serial.print("Front: "); Serial.println(analogRead(A6));
    Serial.print("Right: "); Serial.println(analogRead(A3));

    digitalWrite(2, LOW);

    delay(333);

#else
    switch(state){                  // Robot State
      case OFF:{                    // OFF
        mc.setMotors(0, STOP);
        state = BUTTON;
        break;
      }
      case BUTTON:{                 // Wait for button press to start
        if(digitalRead(userButton_pin) == PRESSED){
          hwCounter_A = 25;
          state = INIT;
        }
        break;
      }
      case INIT:{                   // Initialise Settings
        if(!hwCounter_A){
          pd.caliThreshold();       // Calibrate proximity sensors
          mc.setMotors(150, LEFT);  // rotate left
          hwCounter_A = 500;
          state = CALI;
        }
        break;
      }
      case CALI:{                   // Rotate and calibrate sensors.
        if(hwCounter_A){
          ld.calibrate();           // calibrate line sensors
        }
        else{
          mc.setMotors(0, STOP);    // Calibration Complete.
          hwCounter_A = 500;
          state = RUN;
        }
        break;
      }
      case RUN:{                    // Normal Running Mode
        thisMillis = millis();
        error = ld.getError();
        response = pid.calcResponse(error, (thisMillis - lastMillis));
        mc.updateMotors(response);
        lastMillis = thisMillis;
        state = LINE;
        break;
      }
      case LINE:{
        ldBoolValues = ld.getBoolValues();
        switch (ldBoolValues) {
          case 0b00000000:{
            mc.setMotors(150, LEFT);
            break;
          }
          case 0b00011000:{
            mc.setMotors(150, LEFT);
            break;
          }
          case 0b00010000:{
            mc.setMotors(220, LEFT);
            break;
          }
          case 0b00000011:{
            mc.setMotors(150, RIGHT);
            break;
          }
          case 0b00000001:{
            mc.setMotors(220, RIGHT);
            break;
          }
          default:{
            state = RUN;
          }
        }
        break;
      }
      /*case PROX:{
        pdBoolValues = pd.getBoolValues();
        if(pdBoolValues){
          mc.setMotors(0, STOP);
          switch(pdBoolValue)
        }
        else{
          state = RUN;
        }
        break;
      }*/
      default:{
        state = OFF;
        break;
      }
    }// switch
#endif
}
