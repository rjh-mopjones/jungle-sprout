//
// Created by Rory Hedderman on 26/12/2023.
//

#ifndef JUNGLE_SPROUT_MATH_UTILS_H
#define JUNGLE_SPROUT_MATH_UTILS_H
#include <math.h>


typedef struct {
    float x, y;
} vector2;


vector2 randomGradient(int ix, int iy);
float dotGridGradient(int ix, int iy, float x, float y);
float interpolate(float a0, float a1, float w);


#endif //JUNGLE_SPROUT_MATH_UTILS_H
