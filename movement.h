void moveStop() {
  servo_LeftMotor.writeMicroseconds(ci_Left_Motor_Stop);
  servo_RightMotor.writeMicroseconds(ci_Right_Motor_Stop);
}

void moveLeft() {
  servo_LeftMotor.writeMicroseconds(ci_Left_Motor_Stop);
  servo_RightMotor.writeMicroseconds(1600);


}

void moveRight() {
  servo_LeftMotor.writeMicroseconds(1600);
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

void turnRight() {

  if (turnNinety) {
    turnNinety = false;
    prevMil = millis();
    servo_LeftMotor.writeMicroseconds(leftSpeed);
    servo_RightMotor.writeMicroseconds(rightSpeed);
  }

  else if (millis() - prevMil > period) {
    servo_LeftMotor.writeMicroseconds(ci_Left_Motor_Stop);
    servo_RightMotor.writeMicroseconds(ci_Right_Motor_Stop);
  }
}

void Scan() {

  if (turnNinety) {
    turnNinety = false;
    prevMil = millis();
    servo_LeftMotor.writeMicroseconds(leftSpeed);
    servo_RightMotor.writeMicroseconds(rightSpeed);
  }
  
  if ((millis() - prevMil) > scanPeriod) {
    if (scanLeft) {
      scanLeft = false;
      scanRight = true;
      prevMil = millis();
      servo_LeftMotor.writeMicroseconds(rightSpeed);
      servo_RightMotor.writeMicroseconds(leftSpeed);


    }
    else if (scanRight) {
      scanLeft = true;
      scanRight = false;
      prevMil = millis();
      servo_LeftMotor.writeMicroseconds(leftSpeed);
      servo_RightMotor.writeMicroseconds(rightSpeed);
    }
  }

}
