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

    public:
        void init(bool multisample);
        unsigned int getFrameBufferObject();
        unsigned int getTexture();
        void release();
};

extern FrameBuffer screenFrameBuffer; 

#endif