#ifndef SINGLELIB_H_INCLUDED
#define SINGLELIB_H_INCLUDED

#include <stdint.h>
#include <inttypes.h>
//TODO - implement my own lobrary for the sine
//#include <math.h>


typedef struct{
    uint16_t x, y;
} vector;

typedef struct{
    uint16_t sine_fp;
    uint16_t cossine_fp;
}trigonometric;

trigonometric sine(uint16_t original_angle);

uint16_t sine_16_fp(uint16_t angle);



#endif // SINGLELIB_H_INCLUDED
