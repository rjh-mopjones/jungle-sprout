// C++ program to display "Hello World"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "noise.h"

// Sample Perlin noise at coordinates x, y


int main()
{
    const int windowWidth = 1000;
    const int windowHeight = 1000;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight, 32), "Perlin");

    sf::Uint8* pixels = new sf::Uint8[windowWidth * windowHeight * 4];

    int* pixels2 = new int[windowWidth * windowHeight * 4];


    const int GRID_SIZE = 100;


    for (int x = 0; x < windowWidth; x++)
    {
        for (int y = 0; y < windowHeight; y++)
        {
            int index = (y * windowWidth + x) * 4;


            float val = 0;

            float freq = 1;
            float amp = 1;

            for (int i = 0; i < 12; i++)
            {
                val += perlin(x * freq / GRID_SIZE, y * freq / GRID_SIZE) * amp;

                freq *= 2;
                amp /= 2;

            }

            // Contrast
//            val *= 1.2;

            // Clipping
//            if (val > 1.0f)
//                val = 1.0f;
//            else if (val < -1.0f)
//                val = -1.0f;

            // Convert 1 to -1 into 255 to 0
            int color = (int)(((val + 1.0f) * 0.5f) * 2055);

            // Set pixel color
            pixels[index] = color;
            pixels[index + 1] = color;
            pixels[index + 2] = color;
            pixels[index + 3] = 255;

            pixels2[index] = color;
            pixels2[index + 1] = color;
            pixels2[index + 2] = color;
            pixels2[index + 3] = 255;
        }
    }

    sf::Texture texture;
    sf::Sprite sprite;

    texture.create(windowWidth, windowHeight);

    texture.update(pixels);

    sprite.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);

        window.display();
    }

    return 0;
}