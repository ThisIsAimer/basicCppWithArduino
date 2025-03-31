// C++ code
 //
 
 //Globals
 
 char buffer[32];
 
 
 void setup()
 {
   //serial begin
   //Serial.begin(115200);
   //Serial.write("setup is ready");
   
   //initialising output pins
   	pinMode( 8 , OUTPUT );
 	pinMode( 9 , OUTPUT );
   
   //initialising input pins
   	pinMode( 2 , INPUT );
 	pinMode( 3 , INPUT );
   
   
 }
 
 void loop()
 {        
    asm volatile("push r17\n" //push to stack
                    
                "in r17, 0x09\n"    // 0x09 is the data address of port d inputs
                "lsr r17\n"         // logic shift right 
                "lsr r17\n"    
                "com r17\n"         // inverse
                "andi r17, 0x03\n"  // and with 0b00000011 to get only 2 highs
                "out 0x05, r17\n"   // output to port b
                
                "pop r17\n"); //pop out of stack
   
 
 delay( 250 );
 
 }