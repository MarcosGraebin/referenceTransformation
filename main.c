#include <stdio.h>
#include <stdlib.h>
#include "SingleLib.h"

//TODO - could we do that without a if?
//As it's a small function it worth to do it as inline
inline int16_t change_to_2_complement(uint16_t number){
    if(0b1000000000000000 & number){    //if the number is negative
        number = 0b0111111111111111 & number;
        number = 0 - number;            //complement of 2
    }
    return number;
}

vector futureMain(vector point, vector translate, uint16_t angle){

    point.x     = (uint16_t) change_to_2_complement(point.x);
    point.y     = (uint16_t) change_to_2_complement(point.y);
    translate.x = (uint16_t) change_to_2_complement(translate.x);
    translate.y = (uint16_t) change_to_2_complement(translate.y);

    //obtain the trigonometric constants
    trigonometric rotation;
    rotation = sine_cos(angle);
    rotation.cossine_fp = (uint16_t) change_to_2_complement(rotation.cossine_fp);
    rotation.sine_fp    = (uint16_t) change_to_2_complement(rotation.sine_fp);

    //translate the vector
    uint32_t aux1, aux2;                //if the sum of the numbers exceeds 16 bits
    aux1 = point.x - translate.x;       //Both operations can be done by a single instruction, as in page 45
    aux2 = point.y - translate.y;

    //rotate the vector
    int32_t a, b;
    a =     aux1*(int16_t)rotation.cossine_fp;
    a +=    aux2*(int16_t)rotation.sine_fp;
    b =     aux2*(int16_t)rotation.cossine_fp;
    b -=    aux1*(int16_t)rotation.sine_fp;

    //I've tried to generates a code like this for the above two blocks, but it doesn't compile because the sources registers of the instructions must me the same
    //So to compile it, it would have the same efficency as a C code, because of that (it will need 6 instructions), I decided to keep it in C
    /*asm(
        "R0 = %4 -|- %5;"

        "%0 = %2*%6, %1= %2*%7;"
        "%0 -= %3*%7, %1 += %3*%6;"

        //constraints
        :   "=a"(to_ret.x), "=a"(to_ret.y)
           "+h0"(point.x), "+l0"(point.y)       //input-output operand. With the 0, I'm attribuiting them to the register 0, to do the first instruction
        :   "h1"(translate.x), "l1"(translate.y), "d"(rotation.cossine_fp), "d"(rotation.sine_fp)   //input operand
    );*/

    //if the result vector is too big
    if(((uint32_t) a > (1<<30 -1)) || ((uint32_t) b > (1<<30 -1)))
        return point;

    //Convert the output to the same format that the input had
    //The sine_cos returns values with 14 post-comma bits. It's necessary to eliminate this
    if(a < 0){
        a        = (0 - a);            //It's possible to use the ABS instruction to do that
        point.x  = a >> 14;
        point.x |= (1 << 15);
    }
    else
        point.x = a >> 14;
    if(b < 0){
        b        = (0 - b);
        point.y  = b >> 14;
        point.y |= (1 << 15);
    }
    else
        point.y = b >> 14;

    return point;
}

int main(){     //to test
    vector input, translation;
    input.x = (uint16_t)(1 * 32);
    input.y = (uint16_t)(1 * 32);
    translation.x = (uint16_t)(1.0 * 32)|(1<<15);
    translation.y = (uint16_t)(1 * 32);
    trigonometric aux;

    vector a = futureMain(input, translation, (90<<5));
    float x = a.x /32.0;
    float y = a.y / 32.0;

    return 0;
}
