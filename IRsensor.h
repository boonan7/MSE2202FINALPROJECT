int IRSense() { // run over and over

  if (mySerial.available() > 0)
  {
    
    //Serial.write(mySerial.read());
    Freq = (mySerial.read() - '0');
    return Freq;
    
  }
 
}
