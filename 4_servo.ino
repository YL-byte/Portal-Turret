//Move the servo from ClockWise / Negitive to CounterClockWise / Positive until it reaches Max and Min points
void ServoMotion(){
  if (searchServoCurrentAngle >= servoMaxAngle) {
    searchServoIsclockwise = true;
    searchServo.write(searchServoCurrentAngle - searchServoAngleChange);
    Serial.print("");
  }  

  else if (searchServoCurrentAngle <= servoMinAngle) {
    searchServoIsclockwise = false;
    searchServo.write(searchServoCurrentAngle + searchServoAngleChange);
  }

  else if (searchServoIsclockwise == true){
    searchServo.write(searchServoCurrentAngle - searchServoAngleChange);
  }

  else {
    searchServo.write(searchServoCurrentAngle + searchServoAngleChange);
  }
  
  searchServoCurrentAngle = searchServo.read();
}
//--------------------------------------------------------------------------------------------------------------
void handsMode() {
  if (isActive == true) {
      //Open Hands
      handServo.write(clockWiseHandServo);
      delay(handServoDelayTime);
      handServo.write(closedHandServoAngle);

  }
  
  else {
      //Close Hands
      handServo.write(counterClockWiseHandServo);
      delay(handServoDelayTime);
      handServo.write(closedHandServoAngle);
  }
}
