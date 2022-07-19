#ifndef SINGLELIB_H_INCLUDED
#define SINGLELIB_H_INCLUDED

#include <stdint.h>
#include <inttypes.h>

typedef struct{
    uint16_t x, y;
} vector;

typedef struct{
    uint16_t sine_fp;
    uint16_t cossine_fp;
}trigonometric;

//As this function is used just once, it worth to do it as inline
inline trigonometric sine_cos(uint16_t original_angle);


#endif // SINGLELIB_H_INCLUDED
