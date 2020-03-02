int IRSense() { // run over and over

  if (mySerial.available() > 0)
  {
    
    //Serial.write(mySerial.read());
    Freq = (mySerial.read() - '0');
    return Freq;
    
  }
 
}

void nextIR() {
  IRSense();
  
  if (IRSense() == 5) {
    Serial.println("he suis ici a la cinq");
  }
  else if (IRSense() == 0){
    Serial.println("fuck u cunt");
  }



}
