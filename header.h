
// measure distance to target using ultrasonic sensor
//#define DEBUG_LINE_TRACKERS
int pingFront()       //front ultrasonic
{
  //Ping Ultrasonic
  //Send the Ultrasonic Range Finder a 10 microsecond pulse per tech spec
  digitalWrite(ci_Ultrasonic1_Ping, HIGH);

  delayMicroseconds(10); //The 10 microsecond pause where the pulse in "high"
  digitalWrite(ci_Ultrasonic1_Ping, LOW);
  //use command pulseIn to listen to Ultrasonic_Data pin to record the
  //time that it takes from when the Pin goes HIGH until it goes LOW
  ul_Echo_Time = pulseIn(ci_Ultrasonic1_Data, HIGH, 10000);
  //MIGHT HAVE TO CHANGE TO 25000

  return ul_Echo_Time ;

  // Print Sensor Readings
#ifdef DEBUG_ULTRASONIC
  Serial.print("Time (microseconds): ");
  Serial.print(ul_Echo_Time, DEC);
  Serial.print(", Inches: ");
  Serial.print(ul_Echo_Time / 148); //divide time by 148 to get distance in inches
  Serial.print(", cm: ");
  Serial.println(ul_Echo_Time / 58); //divide time by 58 to get distance in cm
#endif
}

int pingLeft()    //Left ultrasonic
{
  digitalWrite(ci_Ultrasonic2_Ping, HIGH);
  delayMicroseconds(10); //The 10 microsecond pause where the pulse in "high"
  digitalWrite(ci_Ultrasonic2_Ping, LOW);

  ul_Echo_Time2 = pulseIn(ci_Ultrasonic2_Data, HIGH, 10000);
  //MIGHT HAVE TO CHANGE TO 25000

  return ul_Echo_Time2;
  //div by 29 since i think vex already divides it by 2




}

int updatePingFront() {   //updates ultrasonic only at specific times
  if ((millis() - ul_Echo_Mil) >= 60) {
  ul_Echo_Mil = millis();
    return pingFront();


  }
}

int modeCheck() {       //checking to see which corner the robot is at
  pingLeft();
  pingFront();

  if (pingFront() > pingLeft()) {
    return 1;
    //NORTHWEST AKA LEFT START
  }
  else {
    return 2;
    //SOUTHWEST AKA RIGHT START
  }
}





// set mode indicator LED state
void Indicator()
{
  //display routine, if true turn on led
  CharliePlexM::Write(ci_Indicator_LED, !(ui_Mode_Indicator[ui_Mode_Indicator_Index] &
                                          (iArray[iArrayIndex])));
  iArrayIndex++;
  iArrayIndex = iArrayIndex & 15;
}
