#include <BoltIoT-Arduino-Helper.h>
#include "HX711.h"
#include<BoltDeviceCredentials.h>
int loadpin1dout=2;
int loadpin2sck=3;
int motorPin1 = 7;
int motorPin2 = 6;
int redled  = 9;
int greenled= 8;
int button = 4;
int buz1 = 5;
int buz2=  10;
String command = "";
long val= 0;
float count=0;
int bell = 8;
long offAt = 0;
HX711 cell;
// Pulse Monitor Test Script
int sensorPin = A0;
double alpha = 0.75;
int period = 100;
double change = 0.0;
double minval = 0.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motorPin1,OUTPUT);
  pinMode(motorPin2,OUTPUT);
  pinMode(redled,OUTPUT);
  pinMode(greenled,OUTPUT);
  cell.begin(loadpin1dout,loadpin2sck);
  boltiot.begin(Serial);
  boltiot.setCommandString("LOADCELLVALUE",loadcellvalue);
  boltiot.setCommandString("FORWARD",forward);
  boltiot.setCommandString("BACKWARD",backward);
  boltiot.setCommandString("STOP",stopmotor);
  boltiot.setCommandString("BELL",bellring);
  pinMode(button, INPUT_PULLUP);
  pinMode(buz1, OUTPUT);
}

String loadcellvalue(String *data){
  String retval = "";
  int threshold = 0 ;
  count = count + 1;
  //val = ((count -1)/count)*val + (1/count)*cell.read();
  val = 0.5 * val + 0.5 * cell.read();
  Serial.println(round((val-125075)/-143109.0f * 525));

  retval=round(((val-125075)/-143109.0f * 525));
  return retval; 
  
  // zero 140553
  //calibration value is -5050.0f * 12.5
}

String forward(String *data) {
  command = "FORWARD";
  digitalWrite(greenled,LOW);
  digitalWrite(redled,HIGH);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  delay(4500); 
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
 
  
  return "Success:Forward";
}
String backward(String *data) {
  command = "BACKWARD";
  digitalWrite(redled,LOW);
  digitalWrite(greenled,HIGH);
 digitalWrite(motorPin2, LOW);
 digitalWrite(motorPin1, HIGH);
 delay(4500);
 digitalWrite(motorPin2, LOW);
 digitalWrite(motorPin1, LOW);
  return "Success:Backward";
}
String stopmotor(String *data) {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  return "Success:Stop";
}
String bellring(String *data) {
  digitalWrite(bell,HIGH);
  return "Success:Done";
}


void loop() {
boltiot.handleCommand();

    static double oldValue = 0;
    static double oldChange = 0;
 
    int rawValue = analogRead (sensorPin);
    double value = alpha * oldValue + (1 - alpha) * rawValue;
 
    Serial.print (rawValue);
    Serial.print (",");
    Serial.println (value);
    oldValue = value;
 
    delay (period);

  

  
}
