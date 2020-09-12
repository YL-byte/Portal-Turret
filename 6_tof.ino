//This Function sends out a signal of 10 miliseconds
int SonarPulse () {
  int distance_in_mm = vl_sensor.readRangeContinuousMillimeters();
  currentSonarReadInCm = (distance_in_mm - 50 ) * 0.1; // -50 is a result of measurment of real distance v.s measured distance
  
  //Print to Serial
  Serial.println();
  Serial.print("currentSonarReadInCm ");
  Serial.print(currentSonarReadInCm);
  Serial.print(" cm");
  Serial.println();
  delay(delayTime);
}
