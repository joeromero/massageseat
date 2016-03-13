/* * MichelAngelo 
 * Massage SEAT
 * Date : 2016, 03, 13
 * Time : 9:30h
 * 
 * Massage sit simulation activate by monitoring the user emotions
 * 
 * Hardware used::
 * 
 *    1- Freaduino UNO V1.8.1 Board (http://www.elecfreaks.com/estore/freaduino-uno-rev1-8-mb-efuno-645.html)
 *    2- Servos Emax ES08A11 (http://www.headsuphobby.com/Emax-8g-ES08AII-Sub-Micro-Servo-B-545.htm)
 *    1- Grove GSR V1.1 Sensor (http://www.seeedstudio.com/wiki/Grove_-_GSR_Sensor)
 * 
 * Other Device:
 *    1- Usb to microUsb adaptor
 *    1- Power suply : 9V-1A
 * 
 * Arduino software (https://www.arduino.cc/en/Main/Software): 
 *    arduino-1.6.7  (lenguaje programación : C)
 */

#include <Servo.h>

// Servos' variables
Servo myservo1;  // create servo object to control servo1
Servo myservo2;  // create servo object to control servo2

int pos = 0;        // Actual servo position
int initPos = 0;     // Initial servo position
int finalPos = 180; // Final servo position
int servo1_pin = 10;// Arduino pin for servo1
int servo2_pin = 11;// Arduino pin for servo2

// Grove GSR sensor's variables
const int GSR=A1;   //Arduino pin Analog Input for Grove GSR sensor

int threshold=0;
int gsrSensorValue;    //Variable for writing GSR lectures

//Threshold Value
const int JOSEPTHRESHOLD = 300;  // Threshold for JosepRomero
int userThreshold = JOSEPTHRESHOLD;

void massage(){
  for(pos=initPos; pos < finalPos; pos +=1)
  {
    myservo1.write(pos);
    myservo2.write(pos);
    delay(25);
  }
  for(pos = finalPos; pos>=1; pos-=1)
  {
    myservo1.write(pos);
    myservo2.write(pos);
    delay(25);
  }
}
void setup(){
  long sum=0;       //Variable for Threshold caculation
  Serial.begin(9600);

  // Attach servos's conexion to Arcuino
  myservo1.attach(servo1_pin);
  myservo2.attach(servo2_pin);

  // SetUp Servo initial position
  myservo1.write(initPos);
  myservo2.write(initPos);

  Serial.print("userThreshold =");
  Serial.println(userThreshold);
}

void loop(){
  gsrSensorValue=analogRead(GSR); // Lecture from GSR sensor
  //Print lecture values
  Serial.print("userThresholdValue=");
  Serial.print(userThreshold);
  Serial.print("   sensorValue=");
  Serial.print(gsrSensorValue);
  //Evaluation for Massage
  if (gsrSensorValue < userThreshold) {    // Massage if gsrSensorValue < userThreshold
    Serial.print("  MASSAGE RELAX!!!!!!");
    massage();
  }
  Serial.println("");
  delay(500);
}
