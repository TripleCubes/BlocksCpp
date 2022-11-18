#ifndef RAYCAST_H
#define RAYCAST_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaders.h"
#include "vectormath.h"
#include "globals.h"
#include "player.h"
#include "globals.h"
#include "chunkLoader.h"

class Raycast
{
    private:
        static Shader blockSelectionShader;
        static unsigned int blockSelectionVAO;
        static unsigned int blockSelectionEBO;
        
        static Pos selectedBlock;
        static Pos blockPlacingPosition;
        static float raycastRange;
        static bool blockInRange;

    public:
        static void init();
        static void setRange(float range);
        static bool blockIsInRange();
        static Pos getSelectedBlock();
        static Pos getBlockPlacingPosition();
        static void update();
        static void drawBlockSelection();
        static void release();
};

#endif