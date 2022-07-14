#include <stdio.h>
#include <stdlib.h>
#include "SingleLib.h"

inline uint16_t change_to_2_complement(uint16_t number){
    if(0b1000000000000000 & number){
        number |= 0b0111111111111111;
        number = 0 - number;
    }
    return number;
}

vector futureMain(vector point, vector translate, uint16_t rotation){
}

int main()
{
    vector input, translation;
    input.x = 1;
    input.y = 2;
    translation.x = 1;
    translation.y = 2;

    futureMain(input, translation, 0);
}