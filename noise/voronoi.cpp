//
// Created by Rory Hedderman on 27/12/2023.
//

#include <iostream>
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
    pixelCell = new uint8_t*[height];
    for (int y = 0; y < height; ++y) {
        pixels[y] = new uint8_t[width * 3]; // 3 bytes per pixel for RGB
        pixelCell[y] = new uint8_t[width * 3]; // 3 bytes per not needed
    }



    for (int i = 0; i < numPoints ; ++i) {
        points.push_back({ static_cast<float>(std::rand() % width),
                           static_cast<float>(std::rand() % height),
                           i
        });
        voronoiCells.push_back({static_cast<unsigned char>(0),
                                static_cast<unsigned char>(0),
                                static_cast<unsigned char>(0),
                                i
        });
    }

    for (int iter = 0; iter < iterations; ++iter) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    Point currentPoint = { static_cast<float>(x), static_cast<float>(y), -1 };
                    std::pair<int,int> coords = std::pair<int,int>(x, y);
                    int nearestPointIndex = findNearestPoint(currentPoint, points);
                    int pixelIndex = x * 3;
                    pixels[y][pixelIndex] = voronoiCells[nearestPointIndex].r;
                    pixels[y][pixelIndex + 1] = voronoiCells[nearestPointIndex].g;
                    pixels[y][pixelIndex + 2] = voronoiCells[nearestPointIndex].b;
                    pixelCell[y][pixelIndex] = voronoiCells[nearestPointIndex].cellId;
                    pixelCell[y][pixelIndex + 1 ] = 0;

                    if (iter == iterations -1 &&
                            (findNearestPoint({ static_cast<float>(x - 1), static_cast<float>(y), -1 }, points) != nearestPointIndex ||
                            findNearestPoint({ static_cast<float>(x + 1), static_cast<float>(y), -1 }, points) != nearestPointIndex ||
                            findNearestPoint({ static_cast<float>(x), static_cast<float>(y - 1), -1 }, points) != nearestPointIndex ||
                            findNearestPoint({ static_cast<float>(x), static_cast<float>(y + 1), -1 }, points) != nearestPointIndex)) {
                        //border
                        pixelCell[y][pixelIndex + 1] = 1;
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
                    if (voronoiCells[i].cellId == pixelCell[y][pixelIndex]){
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
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        std::cout << "time of iteration "<< iter << ", duration in ms: " << duration.count() << std::endl;

    }

    int borderThickness = 4;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int normThickness = borderThickness/2;
            for (int b = -normThickness; b < normThickness; b++){
                int dx = x + b;
                int pixelIndex = dx*3;
                int dy = y + b;
                if (dy>0 && dx>0 && dx < width && dy < height && pixelCell[y][pixelIndex + 1]) {
                    pixels[dy][pixelIndex] = 255;
                    pixels[dy][pixelIndex + 1] = 255;
                    pixels[dy][pixelIndex + 2] = 255;
                }
            }
        }
    }
}
