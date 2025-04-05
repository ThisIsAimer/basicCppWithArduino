const uint8_t button1_pin = 2; 
const uint8_t button2_pin = 3; 
const uint8_t LED1_pin    = 8; 
const uint8_t LED2_pin    = 9; 

//for monitoring
volatile uint8_t led1State = 0, led2State = 0;
volatile uint16_t interruptCounter = 0;

char stringBuffer[130];


//interrupt calls
ISR( INT0_vect )// at pin 2
{
  // toggle LED state
  led1State = !led1State;

  // increase counter
  interruptCounter++;

}

////////////////////////////////////////////////////////////////////////////////////////

ISR( INT1_vect )// at pin 3
{
  // toggle LED state
  led2State = !led2State;

  // increase counter
  interruptCounter++;

}

////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{
  // the setup function runs once when you press reset or power the board  

  // initialize serial port
  Serial.begin(115200);
  Serial.write( "\n\rSetup.\n\r" );

  // setup GPIO pins
  pinMode( button1_pin, INPUT_PULLUP );
  pinMode( button2_pin, INPUT_PULLUP );
  pinMode( LED1_pin,    OUTPUT );
  pinMode( LED2_pin,    OUTPUT );


  cli();// disables interrupts

  // set the type of interrupt we want for both INT0 and INT1, in this case falling edge code "01"
  // EICRA (0x69) – External Interrupt Control Register A.

  // set falling edge bits "01" for both INT1 and INT0
  EICRA = 0b00001010;

  // next, we have to set the external interrupt mask register to enable INT1 and/or INT0
  // a HIGH enables the interrupt, a LOW disables.
  // EIMSK (0x1D | 0x03D) – External Interrupt Mask Register.
  // enable both INT1 and INT0 with a "1"
  EIMSK = 0b00000011; 

  // EIFR – External Interrupt Flag Register
  // this register will be set by hardware when an interrupt occurs on INT0 or INT1, IFF we have enabled and masked 
  // the interrupt. Writing a "1" to each bit actually resets/clears any pending interrupt, so we don't get any funny 
  // business. 
EIFR  = 0b00000011;

// enable interrupts
sei();

}


void loop() 
{
  static int count = 0; // counter to track iterations
  uint8_t button1State, button2State;

  // read input buttons
  //button1State = digitalRead( button1_pin );
  //button2State = digitalRead( button1_pin );

  // write out LED states to buttons
  digitalWrite( LED1_pin, led1State );
  digitalWrite( LED2_pin, led2State );


  // print something...
  sprintf(stringBuffer, "\ncount = %d, interruptCounter = %d, LED1 = %d, LED2 = %d, Button 1 = %d, Button 2 = %d", 
                         count++, interruptCounter, led1State, led2State, button1State, button2State  );

  // print out status
  Serial.write( stringBuffer );


  // pause a moment
  delay( 100 );

}