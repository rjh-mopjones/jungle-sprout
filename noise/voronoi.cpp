//
// Created by Rory Hedderman on 27/12/2023.
//

#include "noise.h"

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
    for (int x = 0; x < height; ++x) {


    }
    this->pixelData= new PixelData *[height];

    for (int y = 0; y < height; ++y) {
        this->pixelData[y] = new PixelData[width];
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
                    int nearestPointIndex = findNearestPoint(currentPoint, points);
                    pixelData[y][x].nearestPointId = voronoiCells[nearestPointIndex].cellId;

                    if (iter == iterations -1 &&
                            (findNearestPoint({ static_cast<float>(x - 1), static_cast<float>(y), -1 }, points) != nearestPointIndex ||
                            findNearestPoint({ static_cast<float>(x + 1), static_cast<float>(y), -1 }, points) != nearestPointIndex ||
                            findNearestPoint({ static_cast<float>(x), static_cast<float>(y - 1), -1 }, points) != nearestPointIndex ||
                            findNearestPoint({ static_cast<float>(x), static_cast<float>(y + 1), -1 }, points) != nearestPointIndex)) {
                        //border
                        pixelData[y][x].borderPixel = true;
                    }
                }
        }

        // Lloyd's relaxation algorithm: move each point to the centroid of its Voronoi cell
        for (size_t i = 0; i < points.size(); ++i) {
            float sumX = 0, sumY = 0;
            int count = 0;

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    if (voronoiCells[i].cellId == pixelData[y][x].nearestPointId){
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
                int dy = y + b;
                if (dy>0 && dx>0 && dx < width && dy < height && pixelData[y][x].borderPixel) {
                    pixelData[dy][dx].r = 255;
                    pixelData[dy][dx].g = 255;
                    pixelData[dy][dx].b = 255;
                }
            }
        }
    }
}
