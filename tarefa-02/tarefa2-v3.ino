#include "SevSeg.h"

#define flexSensor A0
#define IRsensor 8

SevSeg sevseg;

void estado1(){
  sevseg.blank();
}

void estado2(){
  ADCSRA |= (1 << ADSC);
  while(ADCSRA & (1 << ADSC));
  int flex = ADCL;
  flex += (ADCH << 8);
  //int flex = analogRead(flexSensor);
  //Serial.println(flex);
  flex = map(flex, 400, 1000, 0, 9);
  sevseg.setNumber(flex);
  sevseg.refreshDisplay();
}

void setup() {
   byte numDigits = 1;
   byte digitPins[] = {};
   byte segmentPins[] = {6, 5, 2, 3, 4, 7, 10, 9};
   bool resistorsOnSegments = true;
   byte hardwareConfig = COMMON_CATHODE; 
   sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
   sevseg.setBrightness(90);
   sevseg.setNumber(0);
   sevseg.refreshDisplay();
  //time capture
  TCCR1A = 0;
  TCCR1B = 0b00000001;
  TIMSK1 = 0b00100000;

   pinMode(IRsensor, INPUT);
    //analogic read setup
    ADMUX = 0;
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN);
  
  Serial.begin(9600); 

}

void loop() {
  int estado = digitalRead(IRsensor);
  unsigned int x = ICR1L + (ICR1H << 8);
  Serial.println(x);

  if(!estado){ 
    estado1();
  }
  else {
    estado2();
  }
}