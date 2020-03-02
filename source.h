#include <Servo.h>
#include <EEPROM.h>
#include <uSTimer2.h>
#include <CharliePlexM.h>
#include <Wire.h>
#include <I2CEncoder.h>
#include <SoftwareSerial.h>
Servo servo_RightMotor;
Servo servo_LeftMotor;
Servo servo_ArmMotor;
Servo servo_GripMotor;
I2CEncoder encoder_RightMotor;
I2CEncoder encoder_LeftMotor;


SoftwareSerial mySerial(4, 11); // RX, TX



//port pin constants
const int ci_Ultrasonic_Ping = 2; //input plug
const int ci_Ultrasonic_Data = 3; //output plug
const int ci_Charlieplex_LED1 = 4;
const int ci_Charlieplex_LED2 = 5;
const int ci_Charlieplex_LED3 = 6;
const int ci_Charlieplex_LED4 = 7;
const int ci_Mode_Button = 7;
const int ci_Right_Motor = 8;
const int ci_Left_Motor = 9;
const int ci_Arm_Motor = 10;
const int ci_Grip_Motor = 11;
const int ci_Motor_Enable_Switch = 12;
const int ci_Right_Line_Tracker = A0;
const int ci_Middle_Line_Tracker = A1;
const int ci_Left_Line_Tracker = A2;
const int ci_Light_Sensor = A3;
const int ci_I2C_SDA = A4; // I2C data = white
const int ci_I2C_SCL = A5; // I2C clock = yellow

// Charlieplexing LED assignments
const int ci_Heartbeat_LED = 1;
const int ci_Indicator_LED = 4;
const int ci_Right_Line_Tracker_LED = 6;
const int ci_Middle_Line_Tracker_LED = 9;
const int ci_Left_Line_Tracker_LED = 12;

//constants

// EEPROM addresses
const int ci_Left_Line_Tracker_Dark_Address_L = 0;
const int ci_Left_Line_Tracker_Dark_Address_H = 1;
const int ci_Left_Line_Tracker_Light_Address_L = 2;
const int ci_Left_Line_Tracker_Light_Address_H = 3;
const int ci_Middle_Line_Tracker_Dark_Address_L = 4;
const int ci_Middle_Line_Tracker_Dark_Address_H = 5;
const int ci_Middle_Line_Tracker_Light_Address_L = 6;
const int ci_Middle_Line_Tracker_Light_Address_H = 7;
const int ci_Right_Line_Tracker_Dark_Address_L = 8;
const int ci_Right_Line_Tracker_Dark_Address_H = 9;
const int ci_Right_Line_Tracker_Light_Address_L = 10;
const int ci_Right_Line_Tracker_Light_Address_H = 11;
const int ci_Left_Motor_Offset_Address_L = 12;
const int ci_Left_Motor_Offset_Address_H = 13;
const int ci_Right_Motor_Offset_Address_L = 14;
const int ci_Right_Motor_Offset_Address_H = 15;
const int ci_Left_Motor_Stop = 1500; // 200 for brake mode; 1500 for stop
const int ci_Right_Motor_Stop = 1500;
const int ci_Grip_Motor_Open = 160; // Experiment to determine appropriate value
const int ci_Grip_Motor_Closed = 60; // "
const int ci_Arm_Servo_Retracted = 0; // "
const int ci_Arm_Servo_Extended = 55; // "
const int ci_Display_Time = 500;
const int ci_Line_Tracker_Calibration_Interval = 100;
const int ci_Line_Tracker_Cal_Measures = 20;
const int ci_Line_Tracker_Tolerance = 50; // May need to adjust this
const int ci_Motor_Calibration_Cycles = 3;
const int ci_Motor_Calibration_Time = 5000;

//variables
byte b_LowByte;
byte b_HighByte;
unsigned long ul_Echo_Time;
unsigned int ui_Left_Line_Tracker_Data;
unsigned int ui_Middle_Line_Tracker_Data;
unsigned int ui_Right_Line_Tracker_Data;
unsigned int ui_Motors_Speed = 1900; // Default run speed
unsigned int ui_Left_Motor_Speed;
unsigned int ui_Right_Motor_Speed;
long l_Left_Motor_Position;
long l_Right_Motor_Position;
unsigned long ul_3_Second_timer = 0;
unsigned long ul_Display_Time;
unsigned long ul_Calibration_Time;
unsigned long ui_Left_Motor_Offset;
unsigned long ui_Right_Motor_Offset;
unsigned int ui_Cal_Count;
unsigned int ui_Cal_Cycle;
unsigned int ui_Left_Line_Tracker_Dark;
unsigned int ui_Left_Line_Tracker_Light;
unsigned int ui_Middle_Line_Tracker_Dark;
unsigned int ui_Middle_Line_Tracker_Light;
unsigned int ui_Right_Line_Tracker_Dark;
unsigned int ui_Right_Line_Tracker_Light;
unsigned int ui_Line_Tracker_Tolerance;
unsigned int ui_Robot_State_Index = 0;

//0123456789ABCDEF
unsigned int ui_Mode_Indicator[6] = {
  0x00, //B0000000000000000, //Stop
  0x00FF, //B0000000011111111, //Run
  0x0F0F, //B0000111100001111, //Calibrate line tracker light level
  0x3333, //B0011001100110011, //Calibrate line tracker dark level
  0xAAAA, //B1010101010101010, //Calibrate motors
  0xFFFF //B1111111111111111 //Unused
};
unsigned int ui_Mode_Indicator_Index = 0;
//display Bits 0,1,2,3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
int iArray[16] = {
  1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 65536
};
int iArrayIndex = 0;


int courseStep = 1;
boolean found = false;
unsigned long darkMil = 0;
long lightMil = 0;
int Freq;
