#ifndef TEXTURES_H
#define TEXTURES_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "stb_image.h"

enum FilterType
{
    LINEAR, NEAREST
};

const float BLOCK_PIXEL_WH = 160;

class Texture
{
    private:
        int width, height, numberOfColorChannels;
        unsigned int texture;

    public:
        void load(std::string path, FilterType filterType);
        unsigned int getTexture();
        int getWidth();
        int getHeight();
        void release();
};

#endif