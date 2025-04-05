#include<iostream>

// C++ code
//
//defining input ports
#define INPUT_B1  8
#define INPUT_B2  9
#define INPUT_B3  10
#define INPUT_B4  11

//defining output ports
#define OUTPUT_B1  4
#define OUTPUT_B2  5
#define OUTPUT_B3  6
#define OUTPUT_B4  7




void setup()
{
    //initialising ports
  pinMode(INPUT_B1, INPUT);
  pinMode(INPUT_B2, INPUT);
  pinMode(INPUT_B3, INPUT);
  pinMode(INPUT_B4, INPUT);
  
  
  pinMode(OUTPUT_B1, OUTPUT);
  pinMode(OUTPUT_B2, OUTPUT);
  pinMode(OUTPUT_B3, OUTPUT);
  pinMode(OUTPUT_B4, OUTPUT); 
  
  Serial.begin(115200);
}

void loop()
{
  
  	// Low level GPIO port registers for each port have these registers:
	// PINx  - PINx Input Pins Register, read only, reads entire 8-bit port bits
	// PORTx - PORTx Data Register, read/write 8-bit port register(Its a buffer)
	// DDRx  - PORTx Data Direction Register - read/write the direction of the port bits

  	uint8_t dipSwitches = PINB;  
	//Serial.println( dipSwitches );  
	// write the data to PORTD, but shift bits properly
	PORTD = ~(dipSwitches << 4 ); //shift bits to left
}