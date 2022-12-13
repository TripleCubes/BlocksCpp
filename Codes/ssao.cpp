#include "ssao.h"

FrameBuffer SSAO::unblurredAOFrameBuffer;
FrameBuffer SSAO::horizontalBlurredAOFrameBuffer;
FrameBuffer SSAO::verticalBlurredAOFrameBuffer;
Shader SSAO::ssaoShader;
Shader SSAO::blurShader;
unsigned int SSAO::screenVAO;

std::array<Vec3, 20> SSAO::randomPoints; 
std::array<Vec3, 16> SSAO::randomDirs;

std::random_device SSAO::randomDevice;
std::mt19937 SSAO::randomNumberGenerator(randomDevice());
std::uniform_real_distribution<> SSAO::randomDistribution(-1, 1);

void SSAO::init()
{
    unblurredAOFrameBuffer.init(false);
    horizontalBlurredAOFrameBuffer.init(false);
    verticalBlurredAOFrameBuffer.init(false);
    ssaoShader.init("./Shaders/Effects/SSAO/ssaoVertex.glsl", "./Shaders/Effects/SSAO/ssaoFragment.glsl", false);
    blurShader.init("./Shaders/Effects/SSAO/blurVertex.glsl", "./Shaders/Effects/SSAO/blurFragment.glsl", false);
    
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


    
    auto lerp = [](float a, float b, float f){
        return a + f * (b - a);
    };

    for (int i = 0; i < randomPoints.size(); i++)
    {
        glm::vec3 point(randomDistribution(randomNumberGenerator), randomDistribution(randomNumberGenerator), randomDistribution(randomNumberGenerator));
        point = glm::normalize(point);
        point *= randomDistribution(randomNumberGenerator);

        float scale = (float)i / randomPoints.size(); 
        scale   = lerp(0.1f, 1.0f, scale * scale);
        point *= scale;

        randomPoints[i] = toVec3(point);
    }

    for (int i = 0; i < randomDirs.size(); i++)
    {
        randomDirs[i] = Vec3(glm::radians(randomDistribution(randomNumberGenerator) * 180), 
                            glm::radians(randomDistribution(randomNumberGenerator) * 180), 
                            glm::radians(randomDistribution(randomNumberGenerator) * 180));
    }

    glUseProgram(ssaoShader.getShaderProgram());

    for (int i = 0; i < randomPoints.size(); i++)
    {
        std::string uniformName = "randomPoints[" + std::to_string(i) + "]";
        glUniform3f(glGetUniformLocation(ssaoShader.getShaderProgram(), uniformName.c_str()), randomPoints[i].x, randomPoints[i].y, randomPoints[i].z);
    }

    for (int i = 0; i < randomDirs.size(); i++)
    {
        std::string uniformName = "randomDirs[" + std::to_string(i) + "]";
        glUniform3f(glGetUniformLocation(ssaoShader.getShaderProgram(), uniformName.c_str()), randomDirs[i].x, randomDirs[i].y, randomDirs[i].z);
    }

    glUniformMatrix4fv(glGetUniformLocation(ssaoShader.getShaderProgram(), "projectionMat"), 1, GL_FALSE, glm::value_ptr(projectionMat));
}

void SSAO::generateSSAOTexture()
{
    if (ssao)
    {

        glBindFramebuffer(GL_FRAMEBUFFER, unblurredAOFrameBuffer.getFrameBufferObject());                   
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(ssaoShader.getShaderProgram());
        glBindVertexArray(screenVAO);
        glDisable(GL_DEPTH_TEST);
        glUniformMatrix4fv(glGetUniformLocation(ssaoShader.getShaderProgram(), "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));

        glUniform1i(glGetUniformLocation(ssaoShader.getShaderProgram(), "positionTexture"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, GBuffer::getPositionTexture());

        glUniform1i(glGetUniformLocation(ssaoShader.getShaderProgram(), "normalTexture"), 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, GBuffer::getNormalTexture());

        glDrawArrays(GL_TRIANGLES, 0, 6);



        glBindFramebuffer(GL_FRAMEBUFFER, horizontalBlurredAOFrameBuffer.getFrameBufferObject());                   
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(blurShader.getShaderProgram());
        glBindVertexArray(screenVAO);
        glUniform1i(glGetUniformLocation(blurShader.getShaderProgram(), "screenTexture"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, unblurredAOFrameBuffer.getTexture());
        glUniform1i(glGetUniformLocation(blurShader.getShaderProgram(), "horizontal"), 1);
        glDrawArrays(GL_TRIANGLES, 0, 6);



        glBindFramebuffer(GL_FRAMEBUFFER, verticalBlurredAOFrameBuffer.getFrameBufferObject());                   
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(screenVAO);
        glUniform1i(glGetUniformLocation(blurShader.getShaderProgram(), "screenTexture"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, horizontalBlurredAOFrameBuffer.getTexture());
        glUniform1i(glGetUniformLocation(blurShader.getShaderProgram(), "horizontal"), 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    else
    {
        glBindFramebuffer(GL_FRAMEBUFFER, verticalBlurredAOFrameBuffer.getFrameBufferObject());
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

unsigned int SSAO::getSSAOTexture()
{
    return verticalBlurredAOFrameBuffer.getTexture();
}

void SSAO::release()
{
    unblurredAOFrameBuffer.release();
    horizontalBlurredAOFrameBuffer.release();
    verticalBlurredAOFrameBuffer.release();
    ssaoShader.release();
    blurShader.release();
    glDeleteVertexArrays(1, &screenVAO);
}