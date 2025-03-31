// C++ code
 //
 
 //Globals

int volatile counter = 0;
 
 char buffer[32];
 
 
 void setup()
 {
   //serial begin
   Serial.begin(115200);
   Serial.write("\nsetup is ready\n");
   
   
 }
 
 void loop()
 {              //push to stack
   asm volatile("push r18\n"
                "push r24\n"
                "push r25\n"
                
                "check_loop:\n"
                "lds r18, 0xc0\n" //load UCSR0A with memory addres
                "sbrs r18, 05\n"  //skips if 5th bit of the register is 1
                "rjmp check_loop\n"
                "lds r24,counter\n" // loading counter   
                "adiw r24, 1+' '\n" //add with imidiate word from 0-63
                "sts 0xc6, 24\n"  // memory address of USART I/O data register
                
                //poping initial bytes
                "pop r25\n"
                "pop r24\n"
                "pop r18\n");
   
   if (++counter > 95) counter = 0;
   
   if ((counter % 32) == 0) Serial.write("\n");
   
 
 delay( 100 );
 
 }
  