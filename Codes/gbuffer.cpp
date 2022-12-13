#include "gbuffer.h"

FrameBuffer GBuffer::positionFrameBuffer;
Shader GBuffer::positionShader;

void GBuffer::init()
{
    positionFrameBuffer.init(false);
    positionShader.init("./Shaders/GBuffer/positionVertex.glsl", "./Shaders/GBuffer/positionFragment.glsl", true);
}

void GBuffer::bindPositionFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, positionFrameBuffer.getFrameBufferObject());
}

unsigned int GBuffer::getPositionTexture()
{
    return positionFrameBuffer.getTexture();
}

unsigned int GBuffer::getPositionShaderProgram()
{
    return positionShader.getShaderProgram();
}

int GBuffer::getPositionModelMatUniformLocation()
{
    return positionShader.getModelMatUniformLocation();
}

int GBuffer::getPositionViewMatUniformLocation()
{
    return positionShader.getViewMatUniformLocation();
}

int GBuffer::getPositionProjectionMatUniformLocation()
{
    return positionShader.getProjectionMatUniformLocation();
}

void GBuffer::release()
{
    positionFrameBuffer.release();
    positionShader.release();
}