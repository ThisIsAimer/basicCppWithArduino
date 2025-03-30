// C++ code
//

//Globals
volatile int num1 = 10, num2 = 20, result; 

volatile int counter =0;

char buffer[32];


void setup()
{
  //serial begin
  //Serial.begin(115200);
  //Serial.write("setup is ready");
  
  	pinMode( 8 , OUTPUT );
	pinMode( 9 , OUTPUT );
	pinMode( 10 , OUTPUT );
	pinMode( 11 , OUTPUT );
  
  
}

void loop()
{               //pushing variables
  asm volatile("	push r16\n"
               "	push r17\n"
               
               "	ldi r16, 0x01\n"    // Load Immediate: loads a value to this register
               "	lds r17, counter\n" // Load Direct from Data Space:
                                        // loads counter into r17
               "start_loop:\n"
               "	cpi r17,0x00\n"     // Compare with Immediate: compares with value
               "	breq end_loop\n"    // break if equal
               "	lsl r16\n"          // logical shift left
               "	dec r17\n"          // decrement
               "	rjmp start_loop\n"  //reletice jump: faster
               "end_loop:\n"
               "	sts (0x05+0x20), r16\n"
                                        //Store Direct to Data Space:
                                        // 0x25 is for port b
               
               //pops data out
               "	pop r17\n"
               "	pop r16\n");
  
  if(++counter >=4){
  counter = 0;
    
    
  }

delay( 250 );
}