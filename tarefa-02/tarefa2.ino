#include "SevSeg.h"

#define flexSensor A0
#define IRsensor 11

SevSeg sevseg;

void estado1(){
  sevseg.blank();
}

void estado2(){
  int flex = analogRead(flexSensor);
  Serial.println(flex);
  flex = map(flex, 400, 1000, 0, 9);
  sevseg.setNumber(flex);
  sevseg.refreshDisplay();
}

void setup() {
   byte numDigits = 1;
   byte digitPins[] = {};
   byte segmentPins[] = {6, 5, 2, 3, 4, 7, 8, 9};
   bool resistorsOnSegments = true;
   byte hardwareConfig = COMMON_CATHODE; 
   sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
   sevseg.setBrightness(90);
   sevseg.setNumber(0);
   sevseg.refreshDisplay();

   pinMode(IRsensor, INPUT);

   Serial.begin(9600); 

}

void loop() {
  int estado = digitalRead(IRsensor);
  
  if(!estado){ 
    estado1();
  }
  else {
    estado2();
  }
}