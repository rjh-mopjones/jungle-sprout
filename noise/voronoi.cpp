//
// Created by Rory Hedderman on 27/12/2023.
//

#include "voronoi.h"

float VoronoiDiagram::distance(const Point& p1, const Point& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int VoronoiDiagram::findNearestPoint(const Point& p, const std::vector<Point>& points) {
    float minDist = std::numeric_limits<float>::max();
    int index = -1;

    for (size_t i = 0; i < points.size(); ++i) {
        float dist = distance(p, points[i]);
        if (dist < minDist) {
            minDist = dist;
            index = i;
        }
    }

    return index;
}

VoronoiDiagram::VoronoiDiagram(unsigned int seed, int height, int width, int iterations, int numPoints) {
    this->seed = seed;
    this->height = height;
    this->width = width;
    this->iterations = iterations;
    this->numPoints = numPoints;

    generateVoronoi();
}

void VoronoiDiagram::generateVoronoi(){
    srand(seed);
    pixels = new uint8_t*[height];

    for (int i = 0; i < numPoints ; ++i) {
        points.push_back({ static_cast<float>(std::rand() % width), static_cast<float>(std::rand() % height), i });
        colors.push_back({ static_cast<unsigned char>(std::rand() % 256), static_cast<unsigned char>(std::rand() % 256), static_cast<unsigned char>(std::rand() % 256) });
    }

    for (int y = 0; y < height; ++y) {
        pixels[y] = new uint8_t[width * 3]; // 3 bytes per pixel for RGB
        for (int x = 0; x < width; ++x) {
            Point currentPoint = { static_cast<float>(x), static_cast<float>(y), -1 };
            int nearestPointIndex = findNearestPoint(currentPoint, points);
            int pixelIndex = x * 3;
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1 ||
                findNearestPoint({ static_cast<float>(x - 1), static_cast<float>(y), -1 }, points) != nearestPointIndex ||
                findNearestPoint({ static_cast<float>(x + 1), static_cast<float>(y), -1 }, points) != nearestPointIndex ||
                findNearestPoint({ static_cast<float>(x), static_cast<float>(y - 1), -1 }, points) != nearestPointIndex ||
                findNearestPoint({ static_cast<float>(x), static_cast<float>(y + 1), -1 }, points) != nearestPointIndex) {
                // Border pixel
                pixels[y][pixelIndex] = 255;
                pixels[y][pixelIndex + 1] = 255;
                pixels[y][pixelIndex + 2] = 255;
            } else {
                // Inside the cell
                pixels[y][pixelIndex] = 0;
                pixels[y][pixelIndex + 1] = 0;
                pixels[y][pixelIndex + 2] = 0;
            }
        }
    }

    // Lloyd's relaxation algorithm: move each point to the centroid of its Voronoi cell
    for (size_t i = 0; i < points.size(); ++i) {
        float sumX = 0, sumY = 0;
        int count = 0;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int pixelIndex = x * 3;
                if (pixels[y][pixelIndex] == colors[i].r
                    && pixels[y][pixelIndex + 1] == colors[i].g
                    && pixels[y][pixelIndex + 2] == colors[i].b) {
                    sumX += static_cast<float>(x);
                    sumY += static_cast<float>(y);
                    count++;
                }
            }
        }

        if (count > 0) {
            points[i].x = sumX / count;
            points[i].y = sumY / count;
        }
    }
}