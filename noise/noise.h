//
// Created by Rory Hedderman on 30/12/2023.
//

#ifndef JUNGLE_SPROUT_NOISE_H
#define JUNGLE_SPROUT_NOISE_H
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <chrono>

struct Point {
    float x, y;
    int id;
};

struct PixelData {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    bool borderPixel = false;
    int nearestPointId = -1;
};


#include "math_utils.h"
#include "perlin.h"
#include "voronoi.h"
#include "worley.h"


#endif //JUNGLE_SPROUT_NOISE_H
