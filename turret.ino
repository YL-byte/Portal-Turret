#include <ServoTimer2.h>  // IMPORTANT TO USE THIS LIBRARY INSTEAD OF Servo.h - in order to run the MP3 player and the servos on different clocks
#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <redmp3.h>

//Logic Setup----------------------------------------------------
//Check during loop if turret is active or not
bool isActive = false;

//Used to delay readings from time-of-flight(tof) sensor and writing to the servo
const int delayTime = 20; 

//Used to delay WAV sounds from speaker
const int wavDelayTime = 300; 

//Counting reads from sonar till Firing
const int thresholdFire = 5;
int counterFire = 0; 

//Counting reads from sonar till SleepMode
const int thresholdSleep = 100;
int counterSleep = 0; 

//Counting reads from sonar till SleepMode
const int thresholdToActivate = 10;
int counterToActivate = 0;

//Maximum distance which the sensor detects
const int cmAlert = 25; 

//Eye Setup------------------------------------------------------
/*
Used a 32Tip transistor to turn on/off the LED which is located in the eye socket.
USE A 2.2K RESISTOR TO CONNECT THE BASE OF THE TRANSISTOR TO THE ARDUINO
*/
#define transistorPin 6 

//Speaker Setup--------------------------------------------------
#define ardunioTx 7//connect to RX of the Serial MP3 Player module
#define arduinoRx 8//connect to TX of the Serial MP3 Player module

//Volume
int volume = 16;

MP3 myMP3(ardunioTx, arduinoRx);

//The following is a list of milisecs corresponding to the WAV files and pre-calculated via python
int delayForWavFileInMilisecArray[] = {319, 406, 371, 1486, 1667, 1195, 1164, 1709, 563, 1146, 962, 956, 3149, 753, 1963, 1373, 1707, 1987, 1627, 2587, 2493, 1373, 1154, 895, 830, 2653, 1504, 1145, 1359, 1132, 2205, 2048, 847, 2082, 848, 1200, 1701, 2345, 2290, 805};

//Servo Setup----------------------------------------------------

//USE A POWER SOURCE DESIGNATED ONLY FOR THE SERVOS
#define searchServoPin 11 //Not a continuous servo
#define handServoPin 4 //Continuous servo

ServoTimer2 searchServo, handServo; //searchServo is the base servo and handServo is for the hands
/*
In the Non-Continuous servo
750 = 0 degrees 
1500 = 90 degrees
2000 = 180 degrees

In the Continuous servo
750 = Clock Wise rotation
1500 = no motion
2000 = Counter Clock Wise rotation
*/

//The servo responsible for opening and closing the hands
const int closedHandServoAngle = 1500, clockWiseHandServo = 750, counterClockWiseHandServo = 2250;
const int handServoDelayTime = 400;//How long should the hand servo spin; The larger the value the wider the hand span is

//The servo responsible for rotating the body
const int searchServoStartAngle = 1600, seachServoSpan = 500, servoMaxAngle = searchServoStartAngle + seachServoSpan, servoMinAngle = searchServoStartAngle - seachServoSpan;
const int searchServoAngleChange = 20; //How much change to Positive Values are CounterClockWise
int searchServoCurrentAngle = searchServoStartAngle;
bool searchServoIsclockwise = false;

//Sonar Sensor Setup---------------------------------------------
/*
Pin connection
VL53L0X Pin  Arduino Pin
VCC         3.3V
GND         GND
SDA         A4 or SDA if available
SCL         A5 or SCL if available
GPIO1       leave it unconnected
XSHUT       D12
*/
#define vl_pin 12 //XSHUT

VL53L0X vl_sensor;

long duration, currentSonarReadInCm;
