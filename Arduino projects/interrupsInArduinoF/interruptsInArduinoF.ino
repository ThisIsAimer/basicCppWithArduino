const uint8_t button1_pin = 2; // INT0
const uint8_t button2_pin = 3; // INT1
const uint8_t LED1_pin    = 8; 
const uint8_t LED2_pin    = 9; 

volatile uint8_t led1State = 0, led2State = 0;
volatile uint16_t interruptCounter = 0;

char stringBuffer[128];


void Button1_ISR()
{
// toggle LED state
led1State = !led1State;

// increase counter
interruptCounter++;

} // end Button1_ISR

////////////////////////////////////////////////////////////////////////////////////////

void Button2_ISR()
{
// toggle LED state
led2State = !led2State;

// increase counter
interruptCounter++;

} // end Button2_ISR

////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////

void setup() {
    // the setup function runs once when you press reset or power the board  

    // initialize serial port
    Serial.begin(115200);
    Serial.write( "\n\rSetup.\n\r" );

    // setup GPIO pins
    pinMode( button1_pin, INPUT_PULLUP );
    pinMode( button2_pin, INPUT_PULLUP );
    pinMode( LED1_pin,    OUTPUT );
    pinMode( LED2_pin,    OUTPUT );

    // now attach ISRs to external interrupt using arduino API
    // attachInterrupt(digitalPinToInterrupt(pin), ISR, mode)
    // where: pin  - is the pin you want to attach to, on uno only 2,3 work they are connected to INT0 and INT1 respectively.
    //        ISR  - is a function pointer to the ISR function you want to be called, must return void and void for parms.
    //        mode - select the pin change that activates the interrupt. The following constants are supported uno:
    //
    //        LOW     to trigger the interrupt whenever the pin is low,
    //        CHANGE  to trigger the interrupt whenever the pin changes value
    //        RISING  to trigger when the pin goes from low to high,
    //        FALLING to trigger when the pin goes from high to low.

    // attach interrupts, set to falling since our button(s) grounds the pin when pressed
    //we use the arduino api
    attachInterrupt( digitalPinToInterrupt( 2 ), Button1_ISR, FALLING );
    attachInterrupt( digitalPinToInterrupt( 3 ), Button2_ISR, FALLING );


 }

////////////////////////////////////////////////////////////////////////////////////////

void loop(){
  
 //code can work without the roop things
	static int count = 0; // counter to track iterations
	uint8_t button1State, button2State;

	// read input buttons
	button1State = digitalRead( button1_pin );
	button2State = digitalRead( button1_pin );

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