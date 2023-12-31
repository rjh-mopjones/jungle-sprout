//
// Created by Rory Hedderman on 27/12/2023.
//

#ifndef JUNGLE_SPROUT_BITMAP_UTILS_H
#define JUNGLE_SPROUT_BITMAP_UTILS_H

#include <fstream>
#include "../noise/noise.h"

#pragma pack(push, 1) // Ensure byte alignment

struct BMPHeader {
    uint16_t signature;   // "BM" for BMP files
    uint32_t fileSize;    // Size of the BMP file in bytes
    uint16_t reserved1;   // Reserved, set to 0
    uint16_t reserved2;   // Reserved, set to 0
    uint32_t dataOffset;  // Offset to the start of image data
    uint32_t headerSize;  // Size of the header structure
    int32_t width;        // Image width in pixels
    int32_t height;       // Image height in pixels
    uint16_t planes;      // Number of color planes (must be 1)
    uint16_t bitsPerPixel;// Number of bits per pixel (e.g., 24 for RGB)
    uint32_t compression; // Compression method (usually set to 0 for uncompressed)
    uint32_t imageSize;   // Size of the raw image data
    int32_t ppmX;         // Pixels per meter in X axis
    int32_t ppmY;         // Pixels per meter in Y axis
    uint32_t colors;      // Number of voronoiCells used (0 for full color)
    uint32_t importantColors; // Number of important voronoiCells (0 for all)
};
#pragma pack(pop)
void createBMP(const char* filename, int width, int height, PixelData** imageData);

#endif //JUNGLE_SPROUT_BITMAP_UTILS_H