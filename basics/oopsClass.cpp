#include <iostream>
#include <cstring>

class vector{
    private:

    
    public:

    static int idNum;

    int id = idNum;
    int x,y;

    char *name = nullptr;


    //constructors
    vector(){

        idNum++;
        printf("\nThe id of new vector is: %d ", id);
        
        printf("\nA vector has been created");

        //dinamically allocates memory
        name = new char [32] ;
        strcpy(name,"hey how are you!");

        }


    vector(int _x,int _y=2){

        idNum++;
        printf("\nThe id of new vector is: %d ", id);

        //dinamically allocates memory
        name = new char [32];
        strcpy(name,"hey how are you!");
        printf("\nA well defined vector has been created");
        x = _x;
        y = _y;
        }

    //operator overloading
    vector operator+(vector &a){
        vector result;
        result.x = x+ a.x;
        result.y = y+ a.y;

        return(result);
    }
 

    void print(){
        printf("\nthe positions of x,y is (%d,%d)",x,y);
    }


    //distructor
    ~vector() {
        delete [] name;
        name = nullptr;
        printf("\nDestructor for id: %d\n", id);
        printf("name: %s", name);
    }

};

int vector::idNum = 1;




int main() {
    vector a;
    vector b(5,7);
    vector c = {1};

    a.x = 10;
    a.y = 20;

    vector *p = &a;

    a.print();
    b.print();
    c.print();

    printf("\n");
    printf("\npointer p is pointing to");

    // dereferencing operator for pointer objects
    p->x = 100;
    p->print();


    vector sum(1,2);
    
    sum = b + a;
    printf("\n\nvector sum is: ");
    sum.print();


    // manual distructor calls
    a.~vector();
    b.~vector();
    c.~vector();

    //vector sum is not getting distructed for some reason
    sum.~vector();

    return 0;
}