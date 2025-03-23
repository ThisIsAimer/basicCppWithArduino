#include <iostream>
#include <cstring>

class vector{
    private:
    
    public:

    int x,y;

    char *name = nullptr;


    //constructors
    vector(){
        
        printf("\nA vector has been created");
        name = new char [32] ;
        strcpy(name,"hey how are you!");

        }


    vector(int _x,int _y=2){
        name = new char [32];
        strcpy(name,"hey how are you!");
        printf("\nA well defined vector has been created");
        x = _x;
        y = _y;
        }
 

    void print(){printf("\nthe positions of x,y is (%d,%d)",x,y);}


        //distructor
        ~vector(){ 
            // marks the memory as available for reuse, but the pointer still holds the old address
            delete [] name;
            // destroys the previously allocated string
            name = nullptr;

            printf("\ndistructor\n");
            printf("name: %s", name);
        }

};

int main() {
vector a;
vector b(5,7);
vector c = {1};

a.x = 10;
a.y = 20;

vector *p = &b;

a.print();
b.print();
c.print();

printf("\n");
printf("\npointer p is pointing to");

// dereferencing operator for pointer objects
p->x = 100;
p->print();

    return 0;
}