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
  servo_LeftMotor.writeMicroseconds(1600);
  servo_RightMotor.writeMicroseconds(1600);

}

void moveFind() {
  servo_LeftMotor.writeMicroseconds(1400);
  servo_RightMotor.writeMicroseconds(1600);
}
