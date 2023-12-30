//
// Created by Rory Hedderman on 27/12/2023.
//

#ifndef JUNGLE_SPROUT_VORONOI_H
#define JUNGLE_SPROUT_VORONOI_H


#include <vector>
#include <cmath>
#include <limits>
#include <set>

struct VoronoiCell {
    unsigned char r, g, b;
    int cellId;
};

class VoronoiDiagram {
public:
    VoronoiDiagram(unsigned int seed, int height, int width, int iterations, int numPoints);
    uint8_t** pixels;

private:
    float distance(const Point& p1, const Point& p2);
    int findNearestPoint(const Point& p, const std::vector<Point>& points);
    void generateVoronoi();

    std::vector<Point> points;
    std::vector<VoronoiCell> voronoiCells;
    unsigned int seed;
    uint8_t** pixelCell;
    int height;
    int width;
    int iterations;
    int numPoints;

};

#endif //JUNGLE_SPROUT_VORONOI_H
