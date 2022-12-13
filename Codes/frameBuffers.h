#ifndef FRAMEBUFFERS_H
#define FRAMEBUFFERS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "globals.h"

class FrameBuffer
{
    private:
        unsigned int FBO;
        unsigned int texture;
        unsigned int texture2;

    public:
        void init(bool multisample, int numberOfTextures = 1);
        unsigned int getFrameBufferObject();
        unsigned int getTexture();
        unsigned int getTexture2();
        void release();
};

extern FrameBuffer screenFrameBuffer; 

#endif