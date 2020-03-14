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
  servo_LeftMotor.writeMicroseconds(straightSpeed);
  servo_RightMotor.writeMicroseconds(straightSpeed);

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

  else if (millis() - prevMil > ninetyPeriod) {
    servo_LeftMotor.writeMicroseconds(ci_Left_Motor_Stop);
    servo_RightMotor.writeMicroseconds(ci_Right_Motor_Stop);
  }
}

void moveTurnAround() {
  if (turnNinety) {
    turnNinety = false;
    prevMil = millis();
    servo_LeftMotor.writeMicroseconds(leftSpeed);
    servo_RightMotor.writeMicroseconds(rightSpeed);
  }

  else if (millis() - prevMil > turnAroundPeriod) {
    servo_LeftMotor.writeMicroseconds(ci_Left_Motor_Stop);
    servo_RightMotor.writeMicroseconds(ci_Right_Motor_Stop);
  }

}

void moveScan() {

  if (turnNinety) {
    turnNinety = false;
    prevMil = millis();
    servo_LeftMotor.writeMicroseconds(leftSpeed);
    servo_RightMotor.writeMicroseconds(rightSpeed);


  }

  if (firstScan) {
    if ((millis() - prevMil) > (scanPeriod / 2)) {
      firstScan = false;
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
  else {
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
}

void moveScanFull() {
  servo_LeftMotor.writeMicroseconds(leftSpeedFull);
  servo_RightMotor.writeMicroseconds(rightSpeedFull);
}

void moveMiddle() {
  if (goOnce) {
    goOnce = false;
    prevMil = millis();
    servo_LeftMotor.writeMicroseconds(straightSpeed);
    servo_RightMotor.writeMicroseconds(straightSpeed);


  }

  else if ((millis() - prevMil) > middlePeriod) {

    servo_LeftMotor.writeMicroseconds(ci_Left_Motor_Stop);
    servo_RightMotor.writeMicroseconds(ci_Right_Motor_Stop);
    startScan = true;
    goOnceMain = false;




  }


}

void  moveBack() {
  if (moveBackOnce) {
    moveBackOnce = false;
    prevMil = millis();
    servo_LeftMotor.writeMicroseconds(backSpeed);
    servo_RightMotor.writeMicroseconds(backSpeed);
    Serial.println("BACK");

  }

  else {
    if ((millis() - prevMil) > backPeriod) {
      moveScanFull();


    }

  }

}

void touchCheck1() {
  pingFront();

  if (pingFront() <= 25 && pingFront() >= 0) {
    backProt = true;
  }
  else {
    if (touchedBeac) {

      moveStraight();
    }

  }

  if (backProt) {

    moveBack();
    touchedBeac = false;
  }




}
void touchCheck2() {
  pingFront();

  if (pingFront() <=  25 && pingFront() >= 0) {
    moveStop();
  }
  else {

      moveStraight();
    

  }

}
