#ifndef BLOOM_H
#define BLOOM_H

#include "frameBuffers.h"
#include "shaders.h"

class Bloom
{
    private:
        static FrameBuffer lightFilterFrameBuffer;
        static FrameBuffer horizontalBlurFrameBuffer;
        static FrameBuffer verticalBlurFrameBuffer;
        static Shader lightFilterShader;
        static Shader blurShader;
        static unsigned int screenVAO;

    public:
        static void init();
        static void generateBlurTexture(unsigned int screenTexture);
        static unsigned int getBlurTexture();
        static void release();
};

#endif