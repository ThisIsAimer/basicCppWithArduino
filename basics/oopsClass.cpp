#include <iostream>
#include <cstring>

class vector{
    private:
    public:

    static int idNum;

    int id = idNum;
    int x,y;

    char *name = nullptr;


    //constructors 1
    vector(){

        idNum++;
        printf("\nThe id of new vector is: %d ", id);
        
        printf("\nA vector has been created");

        //dinamically allocates memory
        name = new char [32] ;
        strcpy(name,"hey how are you!");

        }
    
    //constructors 2
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

    //copy constructor
    vector(const vector &copy){

        idNum++;
        printf("\nThe id of new vector is: %d ", id);

        //dinamically allocates memory
        name = new char [32];
        strcpy(name,copy.name);
        printf("\nA copied vector has been created");
        this->x = copy.x;
        this->y = copy.y;
        }

    
    //operator overloading
    vector operator+(const vector &a){
        vector result;
        result.x = x+ a.x;
        result.y = y+ a.y;

        return(result);
    }


    //= operator overload
    // here adding a reference makes the code efficient and 
    //makes it so there is no unnecessary copes of the objects
    vector & operator=(const vector &i){
        this->x = i.x;
        this->y = i.y;

        strcpy(name,i.name);

        return *this; // in a=b=c it after evaluationg b=c, it gives reference 
                      // to b, so that it can operate to a.

    }
 

    void print(){
        printf("\nthe positions of x,y is (%d,%d)",x,y);
    }


    //destructor
    ~vector() {
        delete [] name;
        name = nullptr;
        printf("\nDestructor for id: %d\n", id);
        printf("name: %s", name);
    }

};

int vector::idNum = 1;


vector a;
vector b(5,7);
vector c = {1};


int main() {
    a.x = 10;
    a.y = 20;

    vector *p = &a;

    a.print();
    b.print();
    c.print();

    {
    printf("\n");
    vector copy(a);
    printf("\n");
    }

    printf("\n");
    printf("\npointer p is pointing to");

    // dereferencing operator for pointer objects
    p->x = 100;
    p->print();


    vector sum(1,2);
    
    sum = b + a;
    printf("\n\nvector sum is: ");
    sum.print();


    return 0;
}