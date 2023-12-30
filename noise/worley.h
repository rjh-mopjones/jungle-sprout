//
// Created by Rory Hedderman on 30/12/2023.
//

#ifndef JUNGLE_SPROUT_WORLEY_H
#define JUNGLE_SPROUT_WORLEY_H


#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

class WorleyNoise {
public:

    WorleyNoise(unsigned int seed, int height, int width, int numPoints);

    uint8_t** pixels;
private:

    float noise(float x, float y);
    float distance(float x1, float y1, float x2, float y2);
    void generateWorley();

    unsigned int seed;
    int width;
    int height;
    int numPoints;
    std::vector<Point> points;
};


#endif //JUNGLE_SPROUT_WORLEY_H
