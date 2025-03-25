#include <iostream>
#include "mathLib_1.h"

int febonachi(const int &x) {

    if (x == 0) return 1;

    else{
        int result = 1;
        for(int i=x;i>0; i--){
            result *= i;
        }
        

        return result;
    }
}


int sumInts(const int &x) {
    int result = 0;
    for(int i=x;i>0; i--){
        result += i;
    }

    return result;
}