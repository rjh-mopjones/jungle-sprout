//
// Created by Rory Hedderman on 30/12/2023.
//


#include "noise.h"

WorleyNoise::WorleyNoise(unsigned int seed, int height, int width, int numPoints) {

    this->seed = seed;
    this->height = height;
    this->width = width;
    this->numPoints = numPoints;
    srand(seed);
    for (int i = 0; i < numPoints; ++i) {
        points.push_back({ static_cast<float>(std::rand() % width) / width,
                           static_cast<float>(std::rand() % height) / height,
                           i
        });
    }
    this->pixelData= new PixelData *[height];

    for (int y = 0; y < height; ++y) {
        this->pixelData[y] = new PixelData[width];
    }
    generateWorley();
}

float WorleyNoise::distance(float x1, float y1, float x2, float y2) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    return std::sqrt(dx * dx + dy * dy);
}

float WorleyNoise::noise(float x, float y) {
    float minDist = std::numeric_limits<float>::max();

    for (const auto& point : points) {
        float dist = distance(x, y, point.x, point.y);
        minDist = std::min(minDist, dist);
    }

    return minDist;
}

//TODO add relaxation
void WorleyNoise::generateWorley() {

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float noiseValue = noise(static_cast<float>(x) / width, static_cast<float>(y) / height);

            // Map the noise value to a grayscale color
            int color = static_cast<int>(noiseValue * 255);

            // Set pixel color
            pixelData[y][x].r = color;
            pixelData[y][x].g = color;
            pixelData[y][x].b = color;
        }
    }
}
