void ActiveFunction() {
  //Generate random value withib index range for WAV sounds: indexActivating, indexFoundTarget, indexLostTarget, indexSearching, indexDistress, indexSleeping
  int indexActivating = round(random(3,9)), indexFoundTarget = round(random(9,18)), indexLostTarget = round(random(18,22)), indexSearching = round(random(22,27)), indexDistress = round(random(27,34)), indexSleeping = round(random(34,40));
  //Length of files in miliiseconds in var currentSonarReadInCm
  SonarPulse();

  //If counterSleep passes thresholdSleep AND searchServo is in start position THEN turret sleepmode active
  if (counterSleep >= thresholdSleep && searchServoCurrentAngle == searchServoStartAngle) {
    Serial.print("Active Function - Activated sleepmode");Serial.println();
    isActive = false;  
    counterSleep = 0;
    counterFire = 0;
    PlayWav(indexSleeping);  
    delay (delayForWavFileInMilisecArray[indexSleeping]);
    //PlayWav(2); 
    handsMode();//Close Hands
  }
  
  //If sonar can't sense somesone then target lost
  else if (currentSonarReadInCm >= cmAlert && counterFire >= thresholdFire) {
    Serial.print("Active Function - Target lost");Serial.println();
    PlayWav(indexLostTarget);  
    delay (delayForWavFileInMilisecArray[indexLostTarget]);
    counterFire = 0;
    counterSleep = 0;//Reset counterSleep
    delay(100);
  }

  //Searching for target
  else if (currentSonarReadInCm > cmAlert) {
    counterFire = 0;
    Serial.print("Active Function - Searching target");Serial.println();
    ServoMotion();
    counterSleep += 1;//If searching and not finding THEN Activate sleepmode 
  }

  //Sensed target long enough and start firing + Playin WAV file
  else if (counterFire == thresholdFire) {
    Serial.print("Active Function - Found Target");Serial.println();
    PlayWav(indexFoundTarget);  
    delay (delayForWavFileInMilisecArray[indexFoundTarget]);
    counterFire += 1;
    counterSleep = 0;//Reset counterSleep
  }
  
  //Sensed target long enough and start firing
  else if (counterFire > thresholdFire) {
    Serial.print("Active Function - Firing");Serial.println();
    PlayWav(1); //play Fire.wav on repeat as long as target is infront of the turret
    counterSleep = 0;//Reset counterSleep
  }

  //This is an instance that sonar sensed something but threshold was still not achived AND the reading from the sonar is not negative
  else if (currentSonarReadInCm > 0) {
    Serial.print("Active Function - Detecting Target");Serial.println();
    ServoMotion();
    counterFire += 1;
    counterSleep = 0; //Reset counterSleep
  }
  
  Serial.print("counterFire ");Serial.print(counterFire);Serial.println();
  Serial.print("searchServoCurrentAngle ");Serial.print(searchServoCurrentAngle);Serial.println();
  Serial.print("------------------------------");Serial.println();
  delay(delayTime);
}
