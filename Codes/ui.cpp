#include "ui.h"

Shader UI::crosshairShader;
unsigned int UI::crosshairVAO;
unsigned int UI::crosshairEBO;
int UI::crosshairWindowSizeUniformLocation;

void UI::init()
{
    crosshairShader.init("./Shaders/crosshairVertex.glsl", "./Shaders/crosshairFragment.glsl", false);

    // float crosshairVerticies[24] = {
    //     -CROSSHAIR_WIDTH / 2,  CROSSHAIR_HEIGHT / 2, // A 0
    //      CROSSHAIR_WIDTH / 2, -CROSSHAIR_HEIGHT / 2, // C 2
    //     -CROSSHAIR_WIDTH / 2, -CROSSHAIR_HEIGHT / 2, // D 3

    //     -CROSSHAIR_WIDTH / 2,  CROSSHAIR_HEIGHT / 2, // A 0
    //      CROSSHAIR_WIDTH / 2,  CROSSHAIR_HEIGHT / 2, // B 1
    //      CROSSHAIR_WIDTH / 2, -CROSSHAIR_HEIGHT / 2, // C 2

    //     -CROSSHAIR_HEIGHT / 2,  CROSSHAIR_WIDTH / 2, // E 4
    //      CROSSHAIR_HEIGHT / 2,  CROSSHAIR_WIDTH / 2, // F 5
    //      CROSSHAIR_HEIGHT / 2, -CROSSHAIR_WIDTH / 2, // G 6

    //     -CROSSHAIR_HEIGHT / 2,  CROSSHAIR_WIDTH / 2, // E 4
    //      CROSSHAIR_HEIGHT / 2, -CROSSHAIR_WIDTH / 2, // G 6
    //     -CROSSHAIR_HEIGHT / 2, -CROSSHAIR_WIDTH / 2, // H 7
    // };

    float crosshairVerticies[16] = {
        -CROSSHAIR_WIDTH / 2,  CROSSHAIR_HEIGHT / 2, // A 0
         CROSSHAIR_WIDTH / 2,  CROSSHAIR_HEIGHT / 2, // B 1
         CROSSHAIR_WIDTH / 2, -CROSSHAIR_HEIGHT / 2, // C 2
        -CROSSHAIR_WIDTH / 2, -CROSSHAIR_HEIGHT / 2, // D 3
        -CROSSHAIR_HEIGHT / 2,  CROSSHAIR_WIDTH / 2, // E 4
         CROSSHAIR_HEIGHT / 2,  CROSSHAIR_WIDTH / 2, // F 5
         CROSSHAIR_HEIGHT / 2, -CROSSHAIR_WIDTH / 2, // G 6
        -CROSSHAIR_HEIGHT / 2, -CROSSHAIR_WIDTH / 2, // H 7
    };
    unsigned int crosshairIndicies[12] = {
        0, 2, 3, 
        0, 1, 2, 
        4, 5, 6, 
        4, 6, 7
    };

    unsigned int crosshairVBO;
    glGenVertexArrays(1, &crosshairVAO);
    glGenBuffers(1, &crosshairVBO);
    glGenBuffers(1, &crosshairEBO);
    glBindVertexArray(crosshairVAO);

    glBindBuffer(GL_ARRAY_BUFFER, crosshairVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(crosshairVerticies), crosshairVerticies, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, crosshairEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(crosshairIndicies), crosshairIndicies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    glDeleteBuffers(1, &crosshairVBO);

    crosshairWindowSizeUniformLocation = glGetUniformLocation(crosshairShader.getShaderProgram(), "windowSize");
}

void UI::drawCrosshair()
{
    glUseProgram(crosshairShader.getShaderProgram());
    glUniform2f(crosshairWindowSizeUniformLocation, currentWindowWidth, currentWindowHeight);
    glBindVertexArray(crosshairVAO);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}

void UI::release()
{
    glDeleteVertexArrays(1, &crosshairVAO);
    glDeleteBuffers(1, &crosshairEBO);

    crosshairShader.release();
}