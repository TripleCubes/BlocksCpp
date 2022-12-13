#ifndef GBUFFER_H
#define GBUFFER_H

#include "frameBuffers.h"
#include "shaders.h"

class GBuffer
{
    private:
        static FrameBuffer positionFrameBuffer;
        static Shader positionShader;

    public:
        static void init();
        static void bindPositionFrameBuffer();
        static unsigned int getPositionTexture();
        static unsigned int getPositionShaderProgram();
        static int getPositionModelMatUniformLocation();
        static int getPositionViewMatUniformLocation();
        static int getPositionProjectionMatUniformLocation();
        static void release();
};

#endif