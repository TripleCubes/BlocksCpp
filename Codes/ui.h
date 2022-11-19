#ifndef UI_H
#define UI_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vectormath.h"
#include "shaders.h"
#include "globals.h"
#include "frameBuffers.h"

const float CROSSHAIR_WIDTH = 2;
const float CROSSHAIR_HEIGHT = 14;

class UI
{
    private:
        static Shader crosshairShader;
        static unsigned int crosshairVAO;
        static unsigned int crosshairEBO;
        static int crosshairWindowSizeUniformLocation;

    public:
        static void init();
        static void drawCrosshair(unsigned int screenTexture);
        static void release();
};

#endif