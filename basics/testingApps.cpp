#include <iostream>
using std::string;

int addSums(int * a, int * b){

    return (*a+*b);
}


int main(){

    // string ty = "hey there";

    // char hat[]= "hey hat";
    // int nums[5]= {3,4,5,6,7};

    // printf(hat);

    // int i = 0;
    // while (++i<10){

    //     printf("\n%d",i);
    // }

    // printf("\n%d",i);

    //----------------------------------------------------------------------------------------------------------
    //pointer experiment
    // int nums[5]= {3,4,5,6,7};// arrays are taken as pointers

    // int *p = nums;

    // printf("%d\n",nums);
    // printf("%d\n",nums+1);
    // printf("%d\n",nums);
    // printf("%d\n",*nums);


    // for (int i = 0 ; i <5 ; i++){
    // // printf("%d, ",*nums);
    // // nums = nums +1; doesnt work
    //     printf("%d, ",*p);
    //     p++;
    // }

    //---------------------------------------------------------------------------------------------------------------------\
    //pointer functions

    int a = 100;
    int b = 200;

    int *ptrVariable = &a; // a pointer to a

    int &referanceVariable = a; // it is just a with another name in other name


    referanceVariable=200; // changing the reference variable


    printf("\na + b = %d", addSums(&a,&b));
    
    *ptrVariable = 399; // changing with pointer

    //printf("\na + b = %d", addSums((int*)a,(int*)b)); //this doesnt work
    printf("\na + b = %d", addSums(&referanceVariable,&b));


}