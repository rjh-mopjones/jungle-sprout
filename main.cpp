// C++ program to display "Hello World"
#include "noise/noise.h"
#include "io/bitmap_utils.h"

// Sample Perlin noise at coordinates x, y

int main()
{
    const int windowWidth = 2048;
    const int windowHeight = 1024;
    const int seed = 765;
    const int width = windowWidth;
    const int height = windowHeight;

    PerlinNoise perlinNoise(seed, height, width, 1,
                            100.0, 6, 1, 1);
    createBMP("perlin.bmp", width, height, perlinNoise.pixelData);

    VoronoiDiagram voronoiDiagram(seed, height, width, 20, 20);
    createBMP("voronoi.bmp", width, height, voronoiDiagram.pixelData);

    WorleyNoise worleyNoise(seed, height, width, 20);
    createBMP("worley.bmp", width, height, worleyNoise.pixelData);


    return 0;
}