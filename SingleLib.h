#ifndef SINGLELIB_H_INCLUDED
#define SINGLELIB_H_INCLUDED

#include <stdint.h>
#include <inttypes.h>
//TODO - implement my own lobrary for the sine
#include <math.h>

typedef struct{
    uint16_t x, y;
} vector;

uint16_t sine(uint16_t original_angle);



#endif // SINGLELIB_H_INCLUDED
