void setup() {
  Serial.begin(9600); // Starting Serial Terminal-------------------------------
  
  pinMode(vl_pin, INPUT_PULLUP);
  digitalWrite(vl_pin, HIGH);
  
  Wire.begin();

  vl_sensor.init();
  vl_sensor.setTimeout(500);
  vl_sensor.startContinuous();
  
  //Servos-------------------------------------------------------------------------
  
  //Setup for Base Servo
  searchServo.attach(searchServoPin);
  searchServo.write (searchServoStartAngle); //Start Base servo at 0 Degrees
  
  //Setup for Hand Servo----------------------------------------------------------
  handServo.attach(handServoPin);
  handServo.write(closedHandServoAngle);

  //Setup for eye and transistor
  pinMode(LED_BUILTIN, OUTPUT); // Set LED_BUILTIN
  pinMode(transistorPin, OUTPUT); // Set the Led for the eye as output
  
  //Set Random Seed for WAV files index
  randomSeed(analogRead(0));
  
  //Play Open Sound
  myMP3.setVolume(volume);
  PlayWav(0);
  
  
}
/************************************loop Function*********************************/
void loop() {
  //If turret has recently spotted a target - it's active
  if (isActive == true) {
    ActiveFunction();  
  } 

  //If turret has lost a target and stopped searching for one - it's deactivated
  else {
    NotActiveFunction();  
  }
}
