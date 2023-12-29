// C++ program to display "Hello World"
#include "io/bitmap_utils.h"
#include "noise/perlin.h"
#include "noise/voronoi.h"

// Sample Perlin noise at coordinates x, y

int main()
{
    const int windowWidth = 1024;
    const int windowHeight = 1024;
    const int seed = 50;
    const int width = windowWidth;
    const int height = windowHeight;

    PerlinNoise perlinNoise(seed, height, width, 1,
                            100.0, 6, 1, 1);
    createBMP("perlin.bmp", width, height, perlinNoise.pixels);

    VoronoiDiagram voronoiDiagram(seed, height, width, 6, 6);
    createBMP("voronoi.bmp", width, height, voronoiDiagram.pixels);

    return 0;
}