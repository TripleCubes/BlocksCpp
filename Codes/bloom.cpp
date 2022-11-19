#include "bloom.h"

FrameBuffer Bloom::lightFilterFrameBuffer;
FrameBuffer Bloom::horizontalBlurFrameBuffer;
FrameBuffer Bloom::verticalBlurFrameBuffer;
Shader Bloom::lightFilterShader;
Shader Bloom::blurShader;

unsigned int Bloom::screenVAO;

void Bloom::init()
{
    lightFilterFrameBuffer.init(false);
    horizontalBlurFrameBuffer.init(false);
    verticalBlurFrameBuffer.init(false);
    lightFilterShader.init("./Shaders/Effects/Bloom/lightFilterVertex.glsl", "./Shaders/Effects/Bloom/lightFilterFragment.glsl", false);
    blurShader.init("./Shaders/Effects/Bloom/blurVertex.glsl", "./Shaders/Effects/Bloom/blurFragment.glsl", false);

    float screenVerticies[12] = {
        -1,  1,
         1,  1,
        -1, -1,
        
         1,  1,
         1, -1,
        -1, -1
    };
    unsigned int screenVBO;
    glGenVertexArrays(1, &screenVAO);
    glGenBuffers(1, &screenVBO);
    glBindVertexArray(screenVAO);

    glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenVerticies), screenVerticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    glDeleteBuffers(1, &screenVBO);
}

void Bloom::generateBlurTexture(unsigned int screenTexture)
{
    glBindFramebuffer(GL_FRAMEBUFFER, lightFilterFrameBuffer.getFrameBufferObject());                   
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(lightFilterShader.getShaderProgram());
    glBindVertexArray(screenVAO);
    glDisable(GL_DEPTH_TEST);
    glUniform1i(glGetUniformLocation(lightFilterShader.getShaderProgram(), "screenTexture"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, screenTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindFramebuffer(GL_FRAMEBUFFER, horizontalBlurFrameBuffer.getFrameBufferObject());                   
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(blurShader.getShaderProgram());
    glBindVertexArray(screenVAO);
    glUniform1i(glGetUniformLocation(blurShader.getShaderProgram(), "screenTexture"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, lightFilterFrameBuffer.getTexture());
    glUniform1i(glGetUniformLocation(blurShader.getShaderProgram(), "horizontal"), 1);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindFramebuffer(GL_FRAMEBUFFER, verticalBlurFrameBuffer.getFrameBufferObject());                   
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(screenVAO);
    glUniform1i(glGetUniformLocation(blurShader.getShaderProgram(), "screenTexture"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, horizontalBlurFrameBuffer.getTexture());
    glUniform1i(glGetUniformLocation(blurShader.getShaderProgram(), "horizontal"), 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

unsigned int Bloom::getBlurTexture()
{
    return verticalBlurFrameBuffer.getTexture();
}

void Bloom::release()
{
    lightFilterFrameBuffer.release();
    horizontalBlurFrameBuffer.release();
    verticalBlurFrameBuffer.release();
    lightFilterShader.release();
    blurShader.release();
    glDeleteVertexArrays(1, &screenVAO);
}