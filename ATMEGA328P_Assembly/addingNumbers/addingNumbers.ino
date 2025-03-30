// C++ code
//

//Globals
volatile int num1 = 10, num2 = 20, result; 

char buffer[32];


void setup()
{
  //serial begin
  Serial.begin(115200);
  Serial.write("setup is ready");


  // registers are storage components in the cpu used to urgent processing.

  // we use volatile to let the compiler to not try to optimise anything and do
  // what we want it to do
  asm volatile("push r16\n"         // push register 16 to stack
               "push r17\n"         // push register 17 to stack
               "lds r16, num1\n"    // stores num1 to r16
               "lds r17, num2\n"    // stores num2 to r17
               "add r17, r16\n"     // adds r16 and r17 and saves it to r17
               "sts result, r17\n"  // stores the value in r17 to result
               "pop r17\n"          //  pops the initials value of r17
               "pop r16\n");        //  pops the initials value of r17
  
  sprintf(buffer,"\n %d + %d = %d",num1,num2,result);
  
  Serial.write(buffer);
  
  
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}