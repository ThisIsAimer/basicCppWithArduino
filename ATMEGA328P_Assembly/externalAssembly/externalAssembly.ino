#include <stdio.h>


extern "C"{
  void TurnLEDOn();
  void TurnLEDOff();
  void setLED(uint8_t value);
}



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:


  #if 0 

    TurnLEDOn();
  delay(100);


  TurnLEDOff();
  delay(100);

  #endif
//------------------------------------------------------------------------------
  
  #if 1

  setLED(HIGH);
  delay(1000);

  setLED(LOW);
  delay(1000);

  #endif

}
