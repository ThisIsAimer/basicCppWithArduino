#include <iostream>

class vector{
    private:
    
    public:

    int x,y;


    //constructors
    vector(){ printf("\nA vector has been created");}
    vector(int _x,int _y=2){
         printf("\nA well defined vector has been created");
         x = _x;
         y = _y;
        }
 

    void print(){printf("\nthe positions of x,y is (%d,%d)",x,y);}


};

int main() {
vector a;
vector b(5,7);
vector c(1);

a.x = 10;
a.y = 20;

vector *p = &b;

a.print();
b.print();
c.print();

printf("\n");
printf("\npointer p is pointing to");

p->print(); // dereferencing operator for pointer objects

    return 0;
}