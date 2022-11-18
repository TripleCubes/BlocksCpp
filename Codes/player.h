#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "vectormath.h"
#include "shaders.h"

extern Vec3 playerPos;
extern Vec3 lookDir;
extern Vec3 playerFrontDir;

const float PLAYER_WIDTH = 1;
const float PLAYER_HEIGHT = 2;

class Player
{
    private:
        static unsigned int VAO;

    public:
        static void init();
        static void draw();
        static void release();
};

#endif