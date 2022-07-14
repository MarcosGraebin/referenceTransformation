#include <stdio.h>
#include <stdlib.h>
#include "SingleLib.h"

//TODO - could we do that without a if?
//TODO - check if the crosscore accept the inline keyword for the C language
int16_t change_to_2_complement(uint16_t number){
    if(0b1000000000000000 & number){    //if the number is negative
        number = 0b0111111111111111 & number;
        number = 0 - number;            //complement of 2
    }
    return number;
}

vector futureMain(vector point, vector translate, uint16_t rotation){

    //TODO - maybe it is possible to do all these processes in fewer instructions using both ALUs
    point.x = (uint16_t) change_to_2_complement(point.x);
    point.y = (uint16_t) change_to_2_complement(point.y);
    translate.x = (uint16_t) change_to_2_complement(translate.x);
    translate.y = (uint16_t) change_to_2_complement(translate.y);

    uint16_t sin = sine(rotation);


    return point;
}

int main(){
    vector input, translation;
    input.x = 0b1000000000000001;
    input.y = 2;
    translation.x = 1;
    translation.y = 2;

    futureMain(input, translation, 0);
}