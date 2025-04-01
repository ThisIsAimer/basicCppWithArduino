#include <stdio.h>

char buffer[23];

int16_t a = 2, b = 3;


extern "C"{
  void TurnLEDOn();
  void TurnLEDOff();
  void setLED(uint8_t value);
  int16_t multiply (int16_t num1, int16_t num2);
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.write("\nsetup \n");

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

  sprintf(buffer, "%d * %d = %d",a,b,multiply(a,b));
  Serial.println(buffer);
}
