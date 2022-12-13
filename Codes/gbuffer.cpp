#include "gbuffer.h"

FrameBuffer GBuffer::frameBuffer;
Shader GBuffer::shader;

void GBuffer::init()
{
    frameBuffer.init(false, 2);
    shader.init("./Shaders/GBuffer/gBufferVertex.glsl", "./Shaders/GBuffer/gBufferFragment.glsl", true);
}

void GBuffer::bindPositionFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer.getFrameBufferObject());
}

unsigned int GBuffer::getPositionTexture()
{
    return frameBuffer.getTexture();
}

unsigned int GBuffer::getNormalTexture()
{
    return frameBuffer.getTexture2();
}

unsigned int GBuffer::getShaderProgram()
{
    return shader.getShaderProgram();
}

int GBuffer::getModelMatUniformLocation()
{
    return shader.getModelMatUniformLocation();
}

int GBuffer::getViewMatUniformLocation()
{
    return shader.getViewMatUniformLocation();
}

int GBuffer::getProjectionMatUniformLocation()
{
    return shader.getProjectionMatUniformLocation();
}

void GBuffer::release()
{
    frameBuffer.release();
    shader.release();
}