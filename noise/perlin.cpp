//
// Created by Rory Hedderman on 26/12/2023.
//

#include "perlin.h"
#include "math_utils.h"

PerlinNoise::PerlinNoise(unsigned int seed, int height, int width, float amplitude,
                         float resolution, int octaves, float contrast, float frequency) {

    this->seed = seed;
    this->height = height;
    this->width = width;
    this->resolution = resolution;
    this->octaves = octaves;
    this->contrast = contrast;
    this->frequency = frequency;
    this->amplitude = amplitude;

    // Initialize permutation table with a random seed
    for (int i = 0; i < 256; ++i) {
        p[i] = p[i + 256] = rand() % 256;
    }

    // Shuffle the array based on the seed
    srand(seed);
    for (int i = 0; i < 256; ++i) {
        int j = rand() % 256;
        std::swap(p[i], p[j]);
    }
    generatePerlin();
}

double PerlinNoise::fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::linearInterpolation(double t, double a, double b) {
    return a + t * (b - a);
}

double PerlinNoise::grad(int hash, double x, double y) {
    int h = hash & 3;
    double u = h < 2 ? x : y;
    double v = h < 1 ? y : x;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double PerlinNoise::noise(double x, double y) {
    // Find the unit square that contains the point
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;

    // Find relative x, y of point in the square
    x -= floor(x);
    y -= floor(y);

    // Compute fade curves for each coordinate
    double u = fade(x);
    double v = fade(y);

    // Hash coordinates of the 4 square corners
    int A = p[X] + Y;
    int B = p[X + 1] + Y;

    // And add blended results from the 4 corners of the square
    return linearInterpolation(v, linearInterpolation(u, grad(p[A], x, y), grad(p[B], x - 1, y)),
                               linearInterpolation(u, grad(p[A + 1], x, y - 1), grad(p[B + 1], x - 1, y - 1)));
}

void PerlinNoise::generatePerlin() {

    pixels = new uint8_t*[height];

    float value;
    float initFreq = frequency;
    float initAmp = amplitude;

    double totalAmplitude = 0.0;
    for (int i = 0; i < octaves; ++i) {
        totalAmplitude += pow(1/amplitude, i);
    }

    for (int y = 0; y < height; ++y) {
        this->pixels[y] = new uint8_t[width * 3]; // 3 bytes per pixel for RGB
        for (int x = 0; x < width; ++x) {

            // Generate Perlin noise values
            value = 0;

            float runningFreq = initFreq;
            float runningAmp = initAmp;

            for (int i = 0; i < octaves; i++)
            {
                value += noise((y * frequency) / resolution, (x * frequency) / resolution) * amplitude;

                runningFreq*= 2;
                runningAmp/= 2;

            }

            value *= contrast;
            value /= totalAmplitude;

            if (value > 1.0f)
                value = 1.0f;
            else if (value < -1.0f)
                value = -1.0f;

            // Map the noise value to grayscale color
            int color = (int)(((value + 1.0f) * 0.5f) * 255);

            int pixelIndex = x * 3;
            // Set pixel color
            pixels[y][pixelIndex] = color;
            pixels[y][pixelIndex + 1] = color;
            pixels[y][pixelIndex + 2] = color;
        }
    }
}