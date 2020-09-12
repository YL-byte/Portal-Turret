void NotActiveFunction() 
{
  //Shutdown Eye via transistor
  digitalWrite(transistorPin, LOW);
  
  //Generate random value withib index range for WAV sounds: indexActivating, indexFoundTarget, indexLostTarget, indexSearching, indexDistress, indexSleeping
  int indexActivating = round(random(3,9)), indexFoundTarget = round(random(9,18)), indexLostTarget = round(random(18,22)), indexSearching = round(random(22,27)), indexDistress = round(random(27,34)), indexSleeping = round(random(34,40));
  //Length of files in miliiseconds in var currentSonarReadInCm
  SonarPulse();

  //If sonar read is negative reset counter
  if (currentSonarReadInCm < 0){
    Serial.print("Sleepmode - sonar Read Is Negative");Serial.println();
    counterToActivate = 0;
  }
  
  //If sonar read target AND counter still below threshold THEN add to counter
  else if (currentSonarReadInCm <= cmAlert && counterToActivate < thresholdToActivate) {
    Serial.print("Sleepmode - Detecting Target");Serial.println();
    counterToActivate += 1;
  }
  
  //If sonar read target AND counter reaches threshold THEN ACTIVATE TURRET
  else if (currentSonarReadInCm <= cmAlert && counterToActivate >= thresholdToActivate) {
    Serial.print("Sleepmode - Activate Turret");Serial.println();
    isActive = true;  
    //Activate Eye via transistor
    digitalWrite(transistorPin, HIGH);
    //PlayWav(0);  
    PlayWav(indexActivating);  
    delay (delayForWavFileInMilisecArray[indexActivating]);
    handsMode();//Open Hands
    counterToActivate = 0;
  }
  
  //If target lost THEN reset counter
  else {
    Serial.print("Sleepmode - Lost Target");Serial.println();
    counterToActivate = 0;
  }
  Serial.print("counterToActivate ");Serial.print(counterToActivate);Serial.println();
  Serial.print("------------------------------");Serial.println();

}
