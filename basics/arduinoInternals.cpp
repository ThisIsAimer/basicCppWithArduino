#include <iostream>
// arduino hidden files simulation

/*use 
using namespace std; 

and you dont need to write 
std:: 
every time.

*/
std::string name;
void setup();
void loop();


int main(){

    //other internal functions

    setup();


    for(;;){

        // other trevial functions like serial

        loop();
    }
}


void setup(){
    //this is for arduino setup function.
    printf("\nThis is setup");
    
}

void loop(){

    // this is for arduino loop function
    std:: cout<< "\nPlease enter your name: ";

    std:: cin>> name;
    std:: cout<< "your name is: "<<name;

}

