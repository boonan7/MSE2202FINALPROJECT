/*
  MSE 2202 MSEBot base code for Labs 3 and 4
  Language: Arduino
  Authors: Michael Naish and Eugen Porter
  Date: 16/01/17
  Rev 1 - Initial version
  Rev 2 - Update for MSEduino v. 2
*/

#include "source.h"
#include "header.h"
#include "IRsensor.h"
#include "movement.h"

boolean bt_Motors_Enabled = true;
boolean bt_Heartbeat = true;
boolean bt_3_S_Time_Up = false;
boolean bt_Do_Once = false;
boolean bt_Cal_Initialized = false;


boolean goMid = false;
boolean goUp = true;
boolean gang = false;

// Uncomment keywords to enable debugging output
//#define DEBUG_MODE_DISPLAY
//#define DEBUG_MOTORS
//#define DEBUG_LINE_TRACKERS
//#define DEBUG_ENCODERS
//#define DEBUG_ULTRASONIC
//#define DEBUG_LINE_TRACKER_CALIBRATION
//#define DEBUG_MOTOR_CALIBRATION
//#define LAB_3_COURSE
//#define LAB_4_COURSE
//#define PLEASE_WORK
//#define DEBUG_IR

void setup() {
  Wire.begin(); // Wire library required for I2CEncoder library
  Serial.begin(9600);
  CharliePlexM::setBtn(ci_Charlieplex_LED1, ci_Charlieplex_LED2,
                       ci_Charlieplex_LED3, ci_Charlieplex_LED4, ci_Mode_Button);

  mySerial.begin(2400);

  Serial.print("initializing");

  // set up ultrasonic
  pinMode(ci_Ultrasonic1_Ping, OUTPUT);
  pinMode(ci_Ultrasonic1_Data, INPUT);
  pinMode(ci_Ultrasonic2_Ping, OUTPUT);
  pinMode(ci_Ultrasonic2_Data, INPUT);

  // set up drive motors
  pinMode(ci_Right_Motor, OUTPUT);
  servo_RightMotor.attach(ci_Right_Motor);
  pinMode(ci_Left_Motor, OUTPUT);
  servo_LeftMotor.attach(ci_Left_Motor);


  // set up motor enable switch
  pinMode(ci_Motor_Enable_Switch, INPUT);

  // set up encoders. Must be initialized in order that they are chained together,
  // starting with the encoder directly connected to the Arduino. See I2CEncoder docs
  // for more information
  encoder_LeftMotor.init(1.0 / 3.0 * MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
  encoder_LeftMotor.setReversed(false); // adjust for positive count when moving forward
  encoder_RightMotor.init(1.0 / 3.0 * MOTOR_393_SPEED_ROTATIONS, MOTOR_393_TIME_DELTA);
  encoder_RightMotor.setReversed(true); // adjust for positive count when moving forward


  // read saved values from EEPROM
  b_LowByte = EEPROM.read(ci_Left_Motor_Offset_Address_L);
  b_HighByte = EEPROM.read(ci_Left_Motor_Offset_Address_H);
  ui_Left_Motor_Offset = word(b_HighByte, b_LowByte);
  b_LowByte = EEPROM.read(ci_Right_Motor_Offset_Address_L);
  b_HighByte = EEPROM.read(ci_Right_Motor_Offset_Address_H);
  ui_Right_Motor_Offset = word(b_HighByte, b_LowByte);




}

void loop()
{
  if ((millis() - ul_3_Second_timer) > 3000)
  {
    bt_3_S_Time_Up = true;
  }
  // button-based mode selection
  if (CharliePlexM::ui_Btn)
  {
    if (bt_Do_Once == false)
    {
      bt_Do_Once = true;
      ui_Robot_State_Index++;
      ui_Robot_State_Index = ui_Robot_State_Index & 7;
      ul_3_Second_timer = millis();
      bt_3_S_Time_Up = false;
      bt_Cal_Initialized = false;
      ui_Cal_Cycle = 0;
    }
  }
  else
  {
    bt_Do_Once = LOW;
  }

  // check if drive motors should be powered
  bt_Motors_Enabled = digitalRead(ci_Motor_Enable_Switch);

  // modes
  // 0 = default after power up/reset
  // 1 = Press mode button once to enter. Run robot.
  // 2 = Press mode button twice to enter. Testing surface 1.
  // 3 = Press mode button three times to enter. Testing surface 2.
  // 4 = Press mode button four times to enter. Calibrate motor speeds to drive straight.

  switch (ui_Robot_State_Index)
  {
    case 0: //Robot stopped
      {
        pingFront();
        pingLeft();
        modeCheck();
        servo_LeftMotor.writeMicroseconds(ci_Left_Motor_Stop);
        servo_RightMotor.writeMicroseconds(ci_Right_Motor_Stop);
        encoder_LeftMotor.zero();
        encoder_RightMotor.zero();
        ui_Mode_Indicator_Index = 0;
        
        mode = modeCheck();       //allows the robot to know what corner it is in
                                  //modeCheck(); allows us to figure out the orientation of the robot

        break;
      }
    case 1: //Robot Run after 3 seconds
      {

        if (bt_3_S_Time_Up)
        {
#ifdef DEBUG_ENCODERS
          l_Left_Motor_Position = encoder_LeftMotor.getRawPosition();
          l_Right_Motor_Position = encoder_RightMotor.getRawPosition();
          Serial.print("Encoders L: ");
          Serial.print(l_Left_Motor_Position);
          Serial.print(", R: ");
          Serial.println(l_Right_Motor_Position);
#endif
          // set motor speeds
          ui_Left_Motor_Speed = constrain(ui_Motors_Speed + ui_Left_Motor_Offset, 1600, 2100);
          ui_Right_Motor_Speed = constrain(ui_Motors_Speed + ui_Right_Motor_Offset, 1600, 2100);
         
          if (bt_Motors_Enabled)
          {

            switch (mode) {
              case 1: {   //NORTHWEST AKA LEFT START
                  pingFront();
                  pingLeft();
                  if (goUp) {

                    if (pingFront() > 22) {
                      moveStraight();
                    }
                    else {
                      moveStop();
                      goUp = false;
                    }
                  }

                  if (goMid) {
                    turnNinety = true;
                    turnRight();


                  }

                  break;
                }

              case 2: {   //SOUTHWEST AKA RIGHT START

                }
            }




         

            //IF IT SENSES AN IR
            if (mySerial.available()) {
              switch (IRSense()) {
                case 0: {
                    Serial.println("zero ");
                    //moveStraight();
                    break;
                  }

                case 5: {
                    Serial.println("five ");
                    //moveStraight();
                    break;
                  }
              }
            }
            else {
              //              // when it does NOT sense IR Sensor
              //              Serial.println("cant find nothin");
              //              moveFind();
            }






          }





#ifdef DEBUG_MOTORS
          Serial.print("Motors enabled: ");
          Serial.print(bt_Motors_Enabled);
          Serial.print(", Default: ");
          Serial.print(ui_Motors_Speed);
          MSE 2202—Laboratory 3 14
          Serial.print(", Left = ");
          Serial.print(ui_Left_Motor_Speed);
          Serial.print(", Right = ");
          Serial.println(ui_Right_Motor_Speed);
#endif
          ui_Mode_Indicator_Index = 1;
        }
        break;
      }
    case 2: //Calibrate line tracker light levels after 3 seconds
      {
        if (bt_3_S_Time_Up)
        {





          if (goOnceMain) {
            moveMiddle();
          }

          if (startScan) {

            if (mySerial.available()) {

              switch (IRSense()) {
                case 0: {
                    touchCheck1();
                    break;
                  }

                case 5: {
                    touchCheck2();
                    break;
                  }
              }

            }

            else {
              moveScan();
            }


          }


        }
        break;
      }
    case 3: // Calibrate line tracker dark levels after 3 seconds
      {
        if (bt_3_S_Time_Up)
        {
          Serial.println(pingFront());
          touchCheck1();
        }


        break;
      }
    case 4: //Calibrate motor straightness after 3 seconds.
      {
        if (bt_3_S_Time_Up)
        {
          if (!bt_Cal_Initialized)
          {
            bt_Cal_Initialized = true;
            encoder_LeftMotor.zero();
            encoder_RightMotor.zero();
            ul_Calibration_Time = millis();
            servo_LeftMotor.writeMicroseconds(ui_Motors_Speed);
            servo_RightMotor.writeMicroseconds(ui_Motors_Speed);
          }
          else if ((millis() - ul_Calibration_Time) > ci_Motor_Calibration_Time)
          {
            servo_LeftMotor.writeMicroseconds(ci_Left_Motor_Stop);
            servo_RightMotor.writeMicroseconds(ci_Right_Motor_Stop);
            l_Left_Motor_Position = encoder_LeftMotor.getRawPosition();
            l_Right_Motor_Position = encoder_RightMotor.getRawPosition();
            if (l_Left_Motor_Position > l_Right_Motor_Position)
            {
              // May have to update this if different calibration time is used
              ui_Right_Motor_Offset = 0;
              ui_Left_Motor_Offset = (l_Left_Motor_Position - l_Right_Motor_Position) / 4;
            }
            else
            {
              // May have to update this if different calibration time is used
              ui_Right_Motor_Offset = (l_Right_Motor_Position - l_Left_Motor_Position) / 4;
              ui_Left_Motor_Offset = 0;
            }
#ifdef DEBUG_MOTOR_CALIBRATION
            Serial.print("Motor Offsets: Left = ");
            Serial.print(ui_Left_Motor_Offset);
            Serial.print(", Right = ");
            Serial.println(ui_Right_Motor_Offset);
#endif
            EEPROM.write(ci_Right_Motor_Offset_Address_L, lowByte(ui_Right_Motor_Offset));
            EEPROM.write(ci_Right_Motor_Offset_Address_H, highByte(ui_Right_Motor_Offset));
            EEPROM.write(ci_Left_Motor_Offset_Address_L, lowByte(ui_Left_Motor_Offset));
            EEPROM.write(ci_Left_Motor_Offset_Address_H, highByte(ui_Left_Motor_Offset));
            ui_Robot_State_Index = 0; // go back to Mode 0
          }
#ifdef DEBUG_MOTOR_CALIBRATION
          Serial.print("Encoders L: ");
          Serial.print(encoder_LeftMotor.getRawPosition());
          Serial.print(", R: ");
          Serial.println(encoder_RightMotor.getRawPosition());
          MSE 2202—Laboratory 3 17
#endif
          ui_Mode_Indicator_Index = 4;
        }
        break;
      }
  }
  if ((millis() - ul_Display_Time) > ci_Display_Time)
  {
    ul_Display_Time = millis();
#ifdef DEBUG_MODE_DISPLAY
    Serial.print("Mode: ");
    Serial.println(ui_Mode_Indicator[ui_Mode_Indicator_Index], DEC);
#endif
    bt_Heartbeat = !bt_Heartbeat;
    CharliePlexM::Write(ci_Heartbeat_LED, bt_Heartbeat);
    digitalWrite(13, bt_Heartbeat);
    Indicator();
  }
}
