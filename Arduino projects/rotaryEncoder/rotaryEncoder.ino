
// DEFINES AND MACROS 
// input pins used for encoder output A and B
const int rotaryEncoderPinA  =  12;
const int rotaryEncoderPinB  =  11;
const int rotaryEncoderPinSW =  10;

const int encoderMAX         =  +128;  // arbitrary maximum value we want
const int encoderMIN         =  -128;  // arbitrary minimum value we want



// GLOBALS 
int encoderPosition  = 0;  // this is arbitrary, but we can assume 256 positions and pretend we start in middle
int encoderCurrState = 0;
int encoderLastState = 0;  



void setup()
{
// put your setup code here, to run once:
Serial.begin( 115200 );
Serial.write("\nThis happens one time.");

// initialize inputs to read encoder pulses
pinMode ( rotaryEncoderPinA, INPUT );
pinMode ( rotaryEncoderPinB, INPUT );
pinMode ( rotaryEncoderPinSW, INPUT_PULLUP );

// read the initial state of rotaryEncoderA pin since we are using this one for reference
encoderLastState = digitalRead( rotaryEncoderPinA );   

} // end setup

void loop() 
{
 
// your code here runs over and over
// Serial.write("\nThis should happen forever...");    

// read current state of encoder pin A
encoderCurrState = digitalRead( rotaryEncoderPinA );

// if the previous and the current state of encoder output A are different
// then a pulse has occured
if ( encoderCurrState > encoderLastState )
   {     
     // if output A and B are same, then encoder is being rotated counter-clockwise
     // if different then encoder is being rotated clockwise
    if ( encoderCurrState != digitalRead( rotaryEncoderPinB ) ) 
        {
        if ( ++encoderPosition > encoderMAX ) encoderPosition = encoderMAX;
        } // end if
    else 
        {
        if ( --encoderPosition < encoderMIN ) encoderPosition = encoderMIN;
        } // end else
    
    // print position
    Serial.print("Encoder Position: ");
    Serial.println( encoderPosition );
    
    }  // end if


// each iteration update last state with current state
encoderLastState = encoderCurrState; 


#if 0
// test button state
if ( digitalRead( rotaryEncoderPinSW ) == LOW )
  {
  // print button state
  Serial.println("Button Pressed!");
  } // end if
#endif

#if 1
static int switchCurrState          = 0;
static int switchDebounceStartTime  = 0;
static int switchLastState          = 0;

// software debounce
switchCurrState = digitalRead( rotaryEncoderPinSW );

// only test if time has elapsed since change event
if ( ( millis() - switchDebounceStartTime ) > 100 )
  {

  // has the switch changed state
  if ( switchCurrState != switchLastState )
    {
    // update time
    switchDebounceStartTime = millis();

    // update state
    switchLastState = switchCurrState;

    // send message that switch was pressed...
    Serial.print("Button State:");  
    Serial.println( switchCurrState );  
    } // end if
 
  } // end if
#endif


} // loop
