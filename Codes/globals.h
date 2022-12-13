#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

enum Dir
{
    TOP, BOTTOM, LEFT, RIGHT, FORWARD, BACKWARD
};

struct Pos
{
    int x = 0;
    int y = 0;
    int z = 0;
};

const unsigned int INIT_WINDOW_WIDTH = 800;
const unsigned int INIT_WINDOW_HEIGHT = 500;
const int INIT_WINDOW_POS_X = 200;
const int INIT_WINDOW_POS_Y = 50;

const float FPS_CAP = 60;

extern int currentWindowWidth;
extern int currentWindowHeight;

extern bool thirdPersonView;
extern bool wireframeMode;
extern bool flying;
extern bool mouseLock;
extern bool bloom;
extern bool physics;
extern bool ssao;

extern glm::mat4 projectionMat;
extern glm::mat4 viewMat;

bool isMax(float num1, float num2, float num3);
bool isMin(float num1, float num2, float num3);
int mod(int num1, int num2);

#endif