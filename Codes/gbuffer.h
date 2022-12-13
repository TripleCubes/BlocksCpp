#ifndef GBUFFER_H
#define GBUFFER_H

#include "frameBuffers.h"
#include "shaders.h"

class GBuffer
{
    private:
        static FrameBuffer frameBuffer;
        static Shader shader;

    public:
        static void init();
        static void bindPositionFrameBuffer();
        static unsigned int getPositionTexture();
        static unsigned int getNormalTexture();
        static unsigned int getShaderProgram();
        static int getModelMatUniformLocation();
        static int getViewMatUniformLocation();
        static int getProjectionMatUniformLocation();
        static void release();
};

#endif