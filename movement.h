void moveStop() {
  servo_LeftMotor.writeMicroseconds(ci_Left_Motor_Stop);
  servo_RightMotor.writeMicroseconds(ci_Right_Motor_Stop);
}

void moveLeft() {
  servo_LeftMotor.writeMicroseconds(ci_Left_Motor_Stop);
  servo_RightMotor.writeMicroseconds(ci_Right_Motor_Stop);


}

void moveRight() {
  servo_LeftMotor.writeMicroseconds(ci_Left_Motor_Stop);
  servo_RightMotor.writeMicroseconds(ci_Right_Motor_Stop);

}

void moveStraight() {
  servo_LeftMotor.writeMicroseconds(1800);
  servo_RightMotor.writeMicroseconds(1800);

}

void moveFind() {
  servo_LeftMotor.writeMicroseconds(1400);
  servo_RightMotor.writeMicroseconds(1600);
}

int modeCheck(){
  //code to check the mode (north or south west) based on the intial measurements of the ultrasonic sensor
  return 0;
}
