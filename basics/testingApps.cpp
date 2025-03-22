#include <iostream>
using std::string;

int main(){

    string ty = "hey there";

    char hat[]= "hey hat";
    int nums[5]= {3,4,5,6,7};

    int *p = nums;


    for (int i = 0 ; i <5 ; i++){
    // printf("%d, ",*nums);
    // nums = nums +1; doesnt work
        printf("%d, ",*p);
        p++;
    }

    // int i = 0;
    // while (++i<10){

    //     printf("\n%d",i);
    // }

    // printf("\n%d",i);

}