#include <stdio.h>
#include <stdlib.h>
#include "SingleLib.h"

//TODO - could we do that without a if?
//TODO - check if the crosscore accept the inline keyword for the C language
inline int16_t change_to_2_complement(uint16_t number){
    if(0b1000000000000000 & number){    //if the number is negative
        number = 0b0111111111111111 & number;
        number = 0 - number;            //complement of 2
    }
    return number;
}

vector futureMain(vector point, vector translate, uint16_t angle){

    //TODO - maybe it is possible to do all these processes in fewer instructions using both ALUs
    point.x     = (uint16_t) change_to_2_complement(point.x);
    point.y     = (uint16_t) change_to_2_complement(point.y);
    translate.x = (uint16_t) change_to_2_complement(translate.x);
    translate.y = (uint16_t) change_to_2_complement(translate.y);

    trigonometric rotation = sine(angle);
    rotation.cossine_fp = (uint16_t) change_to_2_complement(rotation.cossine_fp);
    rotation.sine_fp    = (uint16_t) change_to_2_complement(rotation.sine_fp);
    
    point.x = point.x - translate.x;       //Both operations can be done by a single instruction, as in page 45
    point.y = point.y - translate.y;

    vector to_ret;
    to_ret.x = point.x*rotation.cossine_fp;    //This four lines can be done by 2 instructions as in page 45 and 611 (multiply and accumulate to accumulator). It'll be nice to use the debugger to check if it's possible to code it without or with the saturation
    to_ret.y = point.x*rotation.sine_fp;
    to_ret.x -= point.y*rotation.sine_fp;
    to_ret.y += point.y*rotation.cossine_fp;
    
    //I've tried to generates a code like this for the above block, but it doesn't compile because the sources of the instructions must me the same
    //So to compile it it would have the same efficency as a C code, because of that, I decided to keep it in C 
    /*asm(
        "R0 = %4 -|- %5;"

        "%0 = %2*%6, %1= %2*%7;"
        "%0 -= %3*%7, %1 += %3*%6;"

        //constraints
        :   "=a"(to_ret.x), "=a"(to_ret.y)
        :   "+h0"(point.x), "+l0"(point.y)       //input-output operand. With the 0, I'm attribuiting them to the register 0, to do the first instruction
        :   "h1"(translate.x), "l1"(translate.y), "d"(rotation.cossine_fp), "d"(rotation.sine_fp)   //input operand        
    );*/

    //The sine and cossine returns values with 14 post-comma bits. It's necessary to eliminate this (even using the multiply and accumulate to accumulator instructions with saturation)
    //As it has 1 barrel shifter, isn't possible to do both lines at once
    to_ret.x = to_ret.x >> 14;
    to_ret.y = to_ret.y >> 14;

    //I'm not sure if this block of code must be here, or above the previous block. It would be nice to test it with a real device
    if(to_ret.x < 0)
        to_ret.x = (0 - to_ret.x) | (1 << 15);      //It's possible to use the ABS instruction to the first part of the operation
    if(to_ret.y < 0)
        to_ret.y = (0 - to_ret.y) | (1 << 15);

    return to_ret;
}

int main(){
    vector input, translation;
    input.x = 0b1000000000000001;
    input.y = 2;
    translation.x = 1;
    translation.y = 2;
    trigonometric aux;

    aux = sine((uint16_t) (32768 + (700.9 * 32)));

    int16_t debug_sine = change_to_2_complement(aux.sine_fp);
    int16_t debug_cos   = change_to_2_complement(aux.cossine_fp);

    float seno = debug_sine / 32768.0, cosseno = debug_cos / 32768.0;



    //test multiplication of 2 "negative unsigned ints"
    uint16_t a, b;
    a = (uint16_t) -1;
    b = 4;
    uint16_t c = a * b;


    return 0;

    //futureMain(input, translation, 0);
}
