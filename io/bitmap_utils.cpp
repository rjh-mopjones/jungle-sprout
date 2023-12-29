//
// Created by Rory Hedderman on 27/12/2023.
//

#include "bitmap_utils.h"

void createBMP(const char* filename, int width, int height, uint8_t** imageData) {
    // Create and fill the BMP header
    BMPHeader bmpHeader;
    bmpHeader.signature = 0x4D42; // "BM"
    bmpHeader.fileSize = sizeof(BMPHeader) + width * height * 3; // 3 bytes per pixel for RGB
    bmpHeader.reserved1 = 0;
    bmpHeader.reserved2 = 0;
    bmpHeader.dataOffset = sizeof(BMPHeader);
    bmpHeader.headerSize = 40; // Size of the header structure
    bmpHeader.width = width;
    bmpHeader.height = height;
    bmpHeader.planes = 1;
    bmpHeader.bitsPerPixel = 24; // 24 bits per pixel for RGB
    bmpHeader.compression = 0;
    bmpHeader.imageSize = width * height * 3; // 3 bytes per pixel for RGB
    bmpHeader.ppmX = 2835; // 72 pixels per inch
    bmpHeader.ppmY = 2835;
    bmpHeader.colors = 0;
    bmpHeader.importantColors = 0;

    // Open the file for writing in binary mode
    std::ofstream file(filename, std::ios::out | std::ios::binary);

    // Write the BMP header
    file.write(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHeader));

    // Write the image data
    for (int i = height - 1; i >= 0; --i) {
        for (int j = 0; j < width; ++j) {
            // Write the color values in reverse order (BGR)
            file.put(imageData[i][j * 3 + 2]); // Blue
            file.put(imageData[i][j * 3 + 1]); // Green
            file.put(imageData[i][j * 3]);     // Red
        }
    }

    // Close the file
    file.close();
}

void runBMPExample() {
    const int width = 256;
    const int height = 256;
    uint8_t** imageData = new uint8_t*[height];
    for (int i = 0; i < height; ++i) {
        imageData[i] = new uint8_t[width * 3]; // 3 bytes per pixel for RGB
        for (int j = 0; j < width * 3; ++j) {
            imageData[i][j * 3] = static_cast<uint8_t>((j * 255) / (width - 1));             // Red
            imageData[i][j * 3 + 1] = static_cast<uint8_t>((j * 255) / (width - 1));    // Blue
            imageData[i][j * 3 + 2] = static_cast<uint8_t>((255 - j * 255) / (width - 1));    // Blue
        }
    }

    // Create BMP file
    createBMP("output.bmp", width, height, imageData);

    // Clean up memory
    for (int i = 0; i < height; ++i) {
        delete[] imageData[i];
    }
    delete[] imageData;
}