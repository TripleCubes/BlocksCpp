#include "player.h"

Vec3 playerPos = {0, 20, 0};
Vec3 lookDir = {0, 0, -1};
Vec3 playerFrontDir = {0, 0, -1};

unsigned int Player::VAO;

void Player::init()
{
    float verticies[216] = {
        -0.5,  1, -0.5,   0,  1,  0, // A
         0.5,  1,  0.5,   0,  1,  0, // C
        -0.5,  1,  0.5,   0,  1,  0, // D

        -0.5,  1, -0.5,   0,  1,  0, // A
         0.5,  1, -0.5,   0,  1,  0, // B
         0.5,  1,  0.5,   0,  1,  0, // C

        -0.5, -1, -0.5,   0, -1,  0, // E
        -0.5, -1,  0.5,   0, -1,  0, // H
         0.5, -1,  0.5,   0, -1,  0, // G

        -0.5, -1, -0.5,   0, -1,  0, // E
         0.5, -1,  0.5,   0, -1,  0, // G
         0.5, -1, -0.5,   0, -1,  0, // F


        -0.5,  1, -0.5,  -1,  0,  0, // A
        -0.5,  1,  0.5,  -1,  0,  0, // D
        -0.5, -1,  0.5,  -1,  0,  0, // H

        -0.5,  1, -0.5,  -1,  0,  0, // A
        -0.5, -1,  0.5,  -1,  0,  0, // H
        -0.5, -1, -0.5,  -1,  0,  0, // E

         0.5,  1, -0.5,   1,  0,  0, // B
         0.5, -1,  0.5,   1,  0,  0, // G
         0.5,  1,  0.5,   1,  0,  0, // C

         0.5,  1, -0.5,   1,  0,  0, // B
         0.5, -1, -0.5,   1,  0,  0, // F
         0.5, -1,  0.5,   1,  0,  0, // G

                
        -0.5,  1,  0.5,   0,  0,  1, // D
         0.5,  1,  0.5,   0,  0,  1, // C
        -0.5, -1,  0.5,   0,  0,  1, // H

         0.5,  1,  0.5,   0,  0,  1, // C
         0.5, -1,  0.5,   0,  0,  1, // G
        -0.5, -1,  0.5,   0,  0,  1, // H

        -0.5,  1, -0.5,   0,  0, -1, // A
        -0.5, -1, -0.5,   0,  0, -1, // E
         0.5,  1, -0.5,   0,  0, -1, // B

         0.5,  1, -0.5,   0,  0, -1, // B
        -0.5, -1, -0.5,   0,  0, -1, // E
         0.5, -1, -0.5,   0,  0, -1, // F
    };
    // -0.5,  1, -0.5, // A
    //  0.5,  1, -0.5, // B
    //  0.5,  1,  0.5, // C
    // -0.5,  1,  0.5, // D
    // -0.5, -1, -0.5, // E
    //  0.5, -1, -0.5, // F
    //  0.5, -1,  0.5, // G
    // -0.5, -1,  0.5, // H

    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    glDeleteBuffers(1, &VBO);
}

void Player::draw()
{
    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, toGlmVec3(playerPos));
    
    glUseProgram(defaultShader.getShaderProgram());
    glUniformMatrix4fv(defaultShader.getModelMatUniformLocation(), 1, GL_FALSE, glm::value_ptr(modelMat));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 216/6);
}

void Player::release()
{
    glDeleteVertexArrays(1, &VAO);
}