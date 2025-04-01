#include <stdio.h>


extern "C"{
  void TurnLEDOn();
  void TurnLEDOff();
}



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  TurnLEDOn();
  delay(100);


  TurnLEDOff();
  delay(100);

}
