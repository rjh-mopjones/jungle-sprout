//
// Created by Rory Hedderman on 26/12/2023.
//

#ifndef JUNGLE_SPROUT_PERLIN_H
#define JUNGLE_SPROUT_PERLIN_H

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

class PerlinNoise {
public:
    PerlinNoise(unsigned int seed, int height, int width, float amplitude,
                float resolution, int octaves, float contrast, float frequency);

    uint8_t** pixels;

private:
    double fade(double t);
    double noise(double x, double y);
    double linearInterpolation(double t, double a, double b);
    double grad(int hash, double x, double y);
    void generatePerlin();

    int p[512];
    unsigned int seed;
    float frequency;
    float amplitude;
    int octaves;
    int height;
    int width;
    float resolution;
    float contrast;

};

#endif //JUNGLE_SPROUT_PERLIN_H
